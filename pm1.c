/* Pollard 'P-1' algorithm.

Copyright 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011
Paul Zimmermann and Alexander Kruppa.

This file is part of the ECM Library.

The ECM Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The ECM Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the ECM Library; see the file COPYING.LIB.  If not, see
http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */

#include <math.h>
#include <stdlib.h>
#include "ecm-impl.h"

#define CASCADE_THRES 3
#define CASCADE_MAX 50000000.0
#ifndef POWM_THRESHOLD
#define POWM_THRESHOLD 100
#endif

typedef struct {
  unsigned int size;
  mpz_t *val;
} mul_casc;

/******************************************************************************
*                                                                             *
*                                  Stage 1                                    *
*                                                                             *
******************************************************************************/

/* prime powers are accumulated up to about n^L1 */
#define L1 16

/*** Cascaded multiply ***/

/* return NULL if an error occurred */
static mul_casc *
mulcascade_init (void)
{
  mul_casc *t;

  t = (mul_casc *) malloc (sizeof (mul_casc));
  if (t == NULL)
    {
      outputf (OUTPUT_ERROR, "mulcascade_init: could not allocate memory\n");
      return NULL;
    }
  t->val = (mpz_t*) malloc (sizeof (mpz_t));
  if (t->val == NULL)
    {
      outputf (OUTPUT_ERROR, "mulcascade_init: could not allocate memory\n");
      free (t);
      return NULL;
    }
  mpz_init (t->val[0]);
  t->size = 1;
  return t;
}

static void 
mulcascade_free (mul_casc *c)
{
  unsigned int i;

  for (i = 0; i < c->size; i++)
    mpz_clear (c->val[i]);
  free (c->val);
  free (c);
}

static mul_casc * 
mulcascade_mul_d (mul_casc *c, const double n, ATTRIBUTE_UNUSED mpz_t t)
{
  unsigned int i;

  if (mpz_sgn (c->val[0]) == 0)
    {
      mpz_set_d (c->val[0], n);
      return c;
    }

  mpz_mul_d (c->val[0], c->val[0], n, t);
  if (mpz_size (c->val[0]) <= CASCADE_THRES)
    return c;
  
  for (i = 1; i < c->size; i++) 
    {
      if (mpz_sgn (c->val[i]) == 0) 
        {
          mpz_set (c->val[i], c->val[i-1]);
          mpz_set_ui (c->val[i-1], 0);
          return c;
        }
      else
	{
          mpz_mul (c->val[i], c->val[i], c->val[i-1]);
          mpz_set_ui (c->val[i-1], 0);
        }
    }
  
  /* Allocate more space for cascade */
  
  i = c->size++;
  c->val = (mpz_t*) realloc (c->val, c->size * sizeof (mpz_t));
  if (c->val == NULL)
    {
      fprintf (stderr, "Cannot allocate memory in mulcascade_mul_d\n");
      exit (1);
    }
  mpz_init (c->val[i]);
  mpz_swap (c->val[i], c->val[i-1]);

  return c;
}

static mul_casc * 
mulcascade_mul (mul_casc *c, mpz_t n)
{
  unsigned int i;

  if (mpz_sgn (c->val[0]) == 0)
    {
      mpz_set (c->val[0], n);
      return c;
    }

  mpz_mul (c->val[0], c->val[0], n);
  if (mpz_size (c->val[0]) <= CASCADE_THRES)
    return c;
  
  for (i = 1; i < c->size; i++) 
    {
      if (mpz_sgn (c->val[i]) == 0) 
        {
          mpz_set (c->val[i], c->val[i-1]);
          mpz_set_ui (c->val[i-1], 0);
          return c;
        } else {
          mpz_mul (c->val[i], c->val[i], c->val[i-1]);
          mpz_set_ui (c->val[i-1], 0);
        }
    }
  
  /* Allocate more space for cascade */
  
  i = c->size++;
  c->val = (mpz_t*) realloc (c->val, c->size * sizeof (mpz_t));
  if (c->val == NULL)
    {
      fprintf (stderr, "Cannot allocate memory in mulcascade_mul\n");
      exit (1);
    }
  mpz_init (c->val[i]);
  mpz_swap (c->val[i], c->val[i-1]);

  return c;
}

static void 
mulcascade_get_z (mpz_t r, mul_casc *c) 
{
  unsigned int i;
  
  if (c->size == 0)
    {
      mpz_set_ui (r, 1); /* Empty product */
      return;
    }

  mpz_set_ui (r, 1);
  
  for (i = 0; i < c->size; i++)
    if (mpz_sgn (c->val[i]) != 0)
      mpz_mul (r, r, c->val[i]);
}


/* Input:  a is the generator (sigma)
           n is the number to factor
           B1 is the stage 1 bound
	   B1done: stage 1 was already done up to that limit
	   go is the group order to preload
   Output: f is the factor found, a is the value at end of stage 1
	   B1done is set to B1 if stage 1 completed normally,
	   or to the largest prime processed if interrupted, but never
	   to a smaller value than B1done was upon function entry.
   Return value: non-zero iff a factor was found (or an error occurred).
*/

static int
pm1_stage1 (mpz_t f, mpres_t a, mpmod_t n, double B1, double *B1done, 
            mpz_t go, int (*stop_asap)(void), char *chkfilename)
{
  double p, q, r, cascade_limit, last_chkpnt_p;
  mpz_t g, d;
  int youpi = ECM_NO_FACTOR_FOUND;
  unsigned int size_n, max_size;
  unsigned int smallbase = 0;
  mul_casc *cascade;
  long last_chkpnt_time;
  const double B0 = sqrt (B1);

  mpz_init (g);
  mpz_init (d);

  size_n = mpz_sizeinbase (n->orig_modulus, 2);
  max_size = L1 * size_n;

  mpres_get_z (g, a, n);
  if (mpz_fits_uint_p (g))
    smallbase = mpz_get_ui (g);

  /* suggestion from Peter Montgomery: start with exponent n-1,
     since any prime divisor of b^m-1 which does not divide any
     algebraic factor of b^m-1 must be of the form km+1 [Williams82].
     Do this only when n is composite, otherwise all tests with prime
     n factor of a Cunningham number will succeed in stage 1.

     Since mpz_probab_prime_p and a^(n-1) mod n require about lg(n) modular
     multiplications, and P-1 perform about B1 modular multiplications,
     to ensure small overhead, use that trick only when lg(n) <= sqrt(B1).
  */
  /* For now, this p^N-1 is left in.  We might want it out at a later time */
  if ((double) size_n <= B0 &&
      mpz_probab_prime_p (n->orig_modulus, PROBAB_PRIME_TESTS) == 0)
    {
      mpz_sub_ui (g, n->orig_modulus, 1);
      mpres_pow (a, a, g, n);
    }
  else
    mpz_set_ui (g, 1);

  /* Set a limit of roughly 10000 * log_10(N) for the primes that are 
     multiplied up in the exponent, i.e. 1M for a 100 digit number, 
     but limit to CASCADE_MAX to avoid problems with stack allocation */
  
  cascade_limit = 3000.0 * (double) size_n;

  if (cascade_limit > CASCADE_MAX)
    cascade_limit = CASCADE_MAX;
  
  if (cascade_limit > B1)
    cascade_limit = B1;

  cascade = mulcascade_init ();
  if (cascade == NULL)
    {
      youpi = ECM_ERROR;
      goto clear_pm1_stage1;
    }

  /* since B0 = sqrt(B1), we can have B0 > cascade_limit only when
     B1 > cascade_limit^2. This cannot happen when cascade_limit=B1,
     thus we need B1 > min(CASCADE_MAX, 3000*sizeinbase(n,2))^2.
     For sizeinbase(n,2) <= CASCADE_MAX/3000 (less than 5017 digits 
     for CASCADE_MAX=5e7) this means B1 > 9e6*sizeinbase(n,2)^2.
     For sizeinbase(n,2) > CASCADE_MAX/3000, this means B1 > CASCADE_MAX^2,
     i.e. B1 > 25e14 for CASCADE_MAX=5e7.
  */

  /* if the user knows that P-1 has a given divisor, he can supply it */
  if (mpz_cmp_ui (go, 1) > 0)
    cascade = mulcascade_mul (cascade, go);
  
  last_chkpnt_time = cputime ();
  last_chkpnt_p = 2.;
  
  /* Fill the multiplication cascade with the product of small stage 1 
     primes */
  /* Add small primes <= MIN(sqrt(B1), cascade_limit) in the appropriate 
     power to the cascade */
  for (p = 2.; p <= MIN(B0, cascade_limit); p = getprime ())
    {
      for (q = 1., r = p; r <= B1; r *= p)
        if (r > *B1done) q *= p;
      cascade = mulcascade_mul_d (cascade, q, d);
    }

  /* If B0 < cascade_limit, we can add some primes > sqrt(B1) with 
     exponent 1 to the cascade */
  for ( ; p <= cascade_limit; p = getprime ())
    if (p > *B1done)
      cascade = mulcascade_mul_d (cascade, p, d);

  /* Now p > cascade_limit, flush cascade and exponentiate */
  mulcascade_get_z (g, cascade);
  mulcascade_free (cascade);
  outputf (OUTPUT_DEVVERBOSE, "Exponent has %u bits\n", 
           mpz_sizeinbase (g, 2));
  
  if (smallbase)
    {
      outputf (OUTPUT_DEVVERBOSE, "Using mpres_ui_pow, base %u\n", smallbase);
      mpres_ui_pow (a, smallbase, g, n);
    }
  else
    {
      mpres_pow (a, a, g, n);
    }
  mpz_set_ui (g, 1);

  /* If B0 > cascade_limit, we need to process the primes 
     cascade_limit < p < B0 in the appropriate exponent yet */
  for ( ; p <= B0; p = getprime ())
    {
      for (q = 1, r = p; r <= B1; r *= p)
        if (r > *B1done) q *= p;
      mpz_mul_d (g, g, q, d);
      if (mpz_sizeinbase (g, 2) >= max_size)
        {
          mpres_pow (a, a, g, n);
          mpz_set_ui (g, 1);
        if (stop_asap != NULL && (*stop_asap) ())
          {
            outputf (OUTPUT_NORMAL, "Interrupted at prime %.0f\n", p);
            if (p > *B1done)
              *B1done = p;
            goto clear_pm1_stage1;
          }
        }
    }

  /* All primes sqrt(B1) < p <= B1 appear in exponent 1. All primes <= B1done
     are already included in exponent of at least 1, so it's save to skip  
     ahead to B1done+1 */
     
  if (*B1done > p)
    {
      getprime_seek ((*B1done) + 1.);
      p = getprime ();
    }

  /* then remaining primes > max(sqrt(B1), cascade_limit) and taken 
     with exponent 1 */
  for (; p <= B1; p = getprime ())
  {
    mpz_mul_d (g, g, p, d);
    if (mpz_sizeinbase (g, 2) >= max_size)
      {
        mpres_pow (a, a, g, n);
        mpz_set_ui (g, 1);
        if (stop_asap != NULL && (*stop_asap) ())
          {
            outputf (OUTPUT_NORMAL, "Interrupted at prime %.0f\n", p);
             if (p > *B1done)
              *B1done = p;
            goto clear_pm1_stage1;
          }
        if (chkfilename != NULL && p > last_chkpnt_p + 10000. &&
            elltime (last_chkpnt_time, cputime ()) > CHKPNT_PERIOD)
          {
            writechkfile (chkfilename, ECM_PM1, p, n, NULL, a, NULL);
            last_chkpnt_p = p;
            last_chkpnt_time = cputime ();
          }
      }
  }

  mpres_pow (a, a, g, n);
  
  /* If stage 1 finished normally, p is the smallest prime >B1 here.
     In that case, set to B1 */
  if (p > B1)
      p = B1;
  
  if (p > *B1done)
    *B1done = p;
  
  mpres_sub_ui (a, a, 1, n);
  mpres_gcd (f, a, n);
  if (mpz_cmp_ui (f, 1) > 0)
    youpi = ECM_FACTOR_FOUND_STEP1;
  mpres_add_ui (a, a, 1, n);

 clear_pm1_stage1:
  if (chkfilename != NULL)
    writechkfile (chkfilename, ECM_PM1, *B1done, n, NULL, a, NULL);
  getprime_clear (); /* free the prime tables, and reinitialize */
  mpz_clear (d);
  mpz_clear (g);

  return youpi;
}


static void
print_prob (double B1, const mpz_t B2, unsigned long dF, unsigned long k, 
            int S, const mpz_t go)
{
  double prob;
  int i;
  char sep;

  outputf (OUTPUT_VERBOSE, "Probability of finding a factor of n digits:\n");
  if (go != NULL && mpz_cmp_ui (go, 1UL) <= 0)
    outputf (OUTPUT_VERBOSE, 
             "(Use -go parameter to specify known factors in P-1)\n");
  outputf (OUTPUT_VERBOSE, "20\t25\t30\t35\t40\t45\t50\t55\t60\t65\n");
  for (i = 20; i <= 65; i += 5)
    {
      sep = (i < 65) ? '\t' : '\n';
      prob = pm1prob (B1, mpz_get_d (B2),
                      pow (10., i - .5), (double) dF * dF * k, S, go);
      outputf (OUTPUT_VERBOSE, "%.2g%c", prob, sep);
    }
}



/******************************************************************************
*                                                                             *
*                                Pollard P-1                                  *
*                                                                             *
******************************************************************************/

/* Input: p is the initial generator (sigma), if 0, generate it at random.
          N is the number to factor
	  B1 is the stage 1 bound
	  B2 is the stage 2 bound
	  B1done is the stage 1 limit to which supplied residue has 
	    already been computed
          k is the number of blocks for stage 2
          verbose is the verbosity level
   Output: f is the factor found, p is the residue at end of stage 1
   Return value: non-zero iff a factor is found (1 for stage 1, 2 for stage 2)
*/
int
pm1 (mpz_t f, mpz_t p, mpz_t N, mpz_t go, double *B1done, double B1,
     mpz_t B2min_parm, mpz_t B2_parm, double B2scale, unsigned long k, 
     int verbose, int repr, int use_ntt, FILE *os, FILE *es, 
     char *chkfilename, char *TreeFilename, double maxmem, 
     gmp_randstate_t rng, int (*stop_asap)(void))
{
  int youpi = ECM_NO_FACTOR_FOUND;
  int base2 = 0;
  int Nbits, smallbase;
  long st;
  mpmod_t modulus;
  mpres_t x;
  mpz_t B2min, B2; /* Local B2, B2min to avoid changing caller's values */
  faststage2_param_t params;

  set_verbose (verbose);
  ECM_STDOUT = (os == NULL) ? stdout : os;
  ECM_STDERR = (es == NULL) ? stdout : es;

  /* if n is even, return 2 */
  if (mpz_divisible_2exp_p (N, 1))
    {
      mpz_set_ui (f, 2);
      return ECM_FACTOR_FOUND_STEP1;
    }

  st = cputime ();

  if (mpz_cmp_ui (p, 0) == 0)
    pm1_random_seed (p, N, rng);
  
  mpz_init_set (B2min, B2min_parm);
  mpz_init_set (B2, B2_parm);
  
  /* Set default B2. See ecm.c for comments */
  if (ECM_IS_DEFAULT_B2(B2))
    mpz_set_d (B2, B2scale * pow (B1 * PM1FS2_COST, 
               PM1FS2_DEFAULT_B2_EXPONENT));
  
  /* set B2min */
  if (mpz_sgn (B2min) < 0)
    mpz_set_d (B2min, B1);

  if (repr != ECM_MOD_DEFAULT && repr != ECM_MOD_NOBASE2)
    {
      if (repr == ECM_MOD_MODMULN)
        mpmod_init_MODMULN (modulus, N);
      else if (repr == ECM_MOD_REDC)
        mpmod_init_REDC (modulus, N);
      else if (abs (repr) > 16)
        {
          if (mpmod_init_BASE2 (modulus, repr, N) == ECM_ERROR)
            return ECM_ERROR;
        }
      else
        mpmod_init_MPZ (modulus, N);
    }
  else /* automatic choice */
    {
      /* Find a good arithmetic for this number */
      Nbits = mpz_sizeinbase (N, 2);
      base2 = (repr == 0) ? isbase2 (N, BASE2_THRESHOLD) : 0;
      smallbase = mpz_fits_uint_p (p);

      /* TODO: make dependent on Nbits and base2 */
      if (base2)
        {
          mpmod_init_BASE2 (modulus, base2, N);
        }

      else if (mpz_size (N) <= 2 * POWM_THRESHOLD && smallbase && B1 <= 1e6)
      /* Below POWM_THRESHOLD, mpz_powm uses MODMULN reduction, too, but 
         without special code for small bases which makes our MODMULN
         faster. Above POWM_THRESHOLD mpz_powm uses faster mod reduction,
         at about 2*POWM_THRESHOLD it catches up with our smallbase-MODMULN
         and then is faster until REDC takes over. */
        {
	  outputf (OUTPUT_VERBOSE, "Using MODMULN\n");
          mpmod_init_MODMULN (modulus, N);
        }
      else if (Nbits > 50000 ||  (Nbits > 3500 && smallbase))
        {
	  outputf (OUTPUT_VERBOSE, "Using REDC\n");
          mpmod_init_REDC (modulus, N);
        }
      else
        {
	  outputf (OUTPUT_VERBOSE, "Using mpz_powm\n");
          mpmod_init_MPZ (modulus, N);
        }
    }
  

  /* Determine parameters (polynomial degree etc.) */

    {
      long P_ntt, P_nontt;
      const unsigned long lmax = 1UL << 30; /* An upper bound */
      unsigned long lmax_NTT, lmax_noNTT;
      faststage2_param_t params_ntt, params_nontt, *better_params;
      mpz_t effB2min_ntt, effB2_ntt, effB2min_nontt, effB2_nontt;

      mpz_init (params.m_1);
      params.l = 0;
      mpz_init (params_ntt.m_1);
      params_ntt.l = 0;
      mpz_init (params_nontt.m_1);
      params_nontt.l = 0;
      mpz_init (effB2min_ntt);
      mpz_init (effB2_ntt);
      mpz_init (effB2min_nontt);
      mpz_init (effB2_nontt);

      /* Find out what the longest transform length is we can do at all.
	 If no maxmem is given, the non-NTT can theoretically do any length. */

      lmax_NTT = 0;
      if (use_ntt)
	{
	  unsigned long t;
	  /* See what transform length the NTT can handle (due to limited 
	     primes and limited memory) */
	  t = mpzspm_max_len (N);
	  lmax_NTT = MIN (lmax, t);
	  if (maxmem != 0.)
	    {
	      t = pm1fs2_maxlen (double_to_size (maxmem), N, use_ntt);
	      lmax_NTT = MIN (lmax_NTT, t);
	    }
	  outputf (OUTPUT_DEVVERBOSE, "NTT can handle lmax <= %lu\n", lmax_NTT);
          P_ntt = choose_P (B2min, B2, lmax_NTT, k, &params_ntt, 
                            effB2min_ntt, effB2_ntt, 1, ECM_PM1);
          if (P_ntt != ECM_ERROR)
            outputf (OUTPUT_DEVVERBOSE,
	             "Parameters for NTT: P=%" PRId64 ", l=%lu\n", 
	             params_ntt.P, params_ntt.l);
	}
      else
        P_ntt = 0; /* or GCC complains about uninitialized var */
      
      /* See what transform length the non-NTT code can handle */
      lmax_noNTT = lmax;
      if (maxmem != 0.)
	{
	  unsigned long t;
	  t = pm1fs2_maxlen (double_to_size (maxmem), N, 0);
	  lmax_noNTT = MIN (lmax_noNTT, t);
	  outputf (OUTPUT_DEVVERBOSE, "non-NTT can handle lmax <= %lu\n", 
		   lmax_noNTT);
	}
      if (use_ntt != 2)
        P_nontt = choose_P (B2min, B2, lmax_noNTT, k, &params_nontt, 
                            effB2min_nontt, effB2_nontt, 0, ECM_PM1);
      else
        P_nontt = ECM_ERROR;
      if (P_nontt != ECM_ERROR)
        outputf (OUTPUT_DEVVERBOSE,
                 "Parameters for non-NTT: P=%" PRId64 ", l=%lu\n", 
                 params_nontt.P, params_nontt.l);
      
      if (((!use_ntt || P_ntt == ECM_ERROR) && P_nontt == ECM_ERROR) ||
          (use_ntt == 2 && P_ntt == ECM_ERROR))
        {
          outputf (OUTPUT_ERROR, 
                   "Error: cannot choose suitable P value for your stage 2 "
                   "parameters.\nTry a shorter B2min,B2 interval.\n");
          mpz_clear (params.m_1);
          mpz_clear (params_ntt.m_1);
          mpz_clear (params_nontt.m_1);
          return ECM_ERROR;
        }

      /* Now decide whether to take NTT or non-NTT. Since the non-NTT code
         uses more memory, we only use it when -no-ntt was given, or when
         we can't find good parameters for the NTT code. */
      if (use_ntt == 0 || P_ntt == ECM_ERROR)
        {
          better_params = &params_nontt;
          mpz_set (B2min, effB2min_nontt);
          mpz_set (B2, effB2_nontt);
          use_ntt = 0;
        }
      else
        {
          better_params = &params_ntt;
          mpz_set (B2min, effB2min_ntt);
          mpz_set (B2, effB2_ntt);
          use_ntt = 1;
        }

      params.P = better_params->P;
      params.s_1 = better_params->s_1;
      params.s_2 = better_params->s_2;
      params.l = better_params->l;
      mpz_set (params.m_1, better_params->m_1);
      params.file_stem = TreeFilename;

      mpz_clear (params_ntt.m_1);
      mpz_clear (params_nontt.m_1);
      mpz_clear (effB2min_ntt);
      mpz_clear (effB2_ntt);
      mpz_clear (effB2min_nontt);
      mpz_clear (effB2_nontt);
      
      if (maxmem != 0.)
	  outputf (OUTPUT_VERBOSE, "Using lmax = %lu with%s NTT which takes "
		   "about %luMB of memory\n", params.l, 
		   (use_ntt) ? "" : "out", 
		   pm1fs2_memory_use (params.l, N, use_ntt)/1048576);
    }
  
  /* Print B1, B2, polynomial and x0 */
  print_B1_B2_poly (OUTPUT_NORMAL, ECM_PM1, B1, *B1done, B2min_parm, B2min, 
		    B2, 1, p, 0, NULL, 0, 0);

  /* If we do a stage 2, print its parameters */
  if (mpz_cmp (B2, B2min) >= 0)
    {
      /* can't mix 64-bit types and mpz_t on win32 for some reason */
      outputf (OUTPUT_VERBOSE, "P = %" PRId64 ", l = %lu"
                    ", s_1 = %" PRId64 ", k = s_2 = %" PRId64 ,
             params.P, params.l,
             params.s_1,params.s_2);
      outputf (OUTPUT_VERBOSE, ", m_1 = %Zd\n", params.m_1);
    }

  if (test_verbose (OUTPUT_VERBOSE))
    {
      if (mpz_sgn (B2min_parm) >= 0)
        {
          outputf (OUTPUT_VERBOSE, 
            "Can't compute success probabilities for B1 <> B2min\n");
        }
      else
        {
          rhoinit (256, 10);
          print_prob (B1, B2, 0, k, 1, go);
        }
    }


  mpres_init (x, modulus);
  mpres_set_z (x, p, modulus);

  st = cputime ();

  if (B1 > *B1done)
    youpi = pm1_stage1 (f, x, modulus, B1, B1done, go, stop_asap, chkfilename);

  st = elltime (st, cputime ());

  outputf (OUTPUT_NORMAL, "Step 1 took %ldms\n", st);
  if (test_verbose (OUTPUT_RESVERBOSE))
    {
      mpz_t tx;
      mpz_init (tx);
      mpres_get_z (tx, x, modulus);
      outputf (OUTPUT_RESVERBOSE, "x=%Zd\n", tx);
      mpz_clear (tx);
    }

  if (stop_asap != NULL && (*stop_asap) ())
    goto clear_and_exit;

  if (youpi == ECM_NO_FACTOR_FOUND && mpz_cmp (B2, B2min) >= 0)
    {
      if (use_ntt)
        youpi = pm1fs2_ntt (f, x, modulus, &params);
      else
        youpi = pm1fs2 (f, x, modulus, &params);
    }

  if (test_verbose (OUTPUT_VERBOSE))
    {
      if (mpz_sgn (B2min_parm) < 0)
        rhoinit (1, 0); /* Free memory of rhotable */
    }

clear_and_exit:
  mpres_get_z (p, x, modulus);
  mpres_clear (x, modulus);
  mpmod_clear (modulus);
  mpz_clear (params.m_1);
  mpz_clear (B2);
  mpz_clear (B2min);

  return youpi;
}
