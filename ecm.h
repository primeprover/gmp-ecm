/* ecm.h - header file for gmp-ecm
 
  Copyright 2001, 2002, 2003 Paul Zimmermann and Alexander Kruppa.
 
  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.
 
  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.
 
  You should have received a copy of the GNU General Public License along
  with this program; see the file COPYING.  If not, write to the Free
  Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA.
*/

#ifndef __ECM_H
#define __ECM_H

/* Warnings about unused parameters by gcc can be suppressed by prefixing 
   parameter with UNUSED when parameter can't be removed, i.e. for
   interface consistency reasons */
#ifdef __GNUC__
#define UNUSED __attribute__ ((unused))
#else
#define UNUSED
#endif

#ifdef __GNUC__
#define INLINE inline
#else
#define INLINE
#endif

/* either one of POLYEVAL or POLYEVALTELLEGEN should be defined */
#define POLYEVALTELLEGEN /* use polyeval_tellegen() routine */

/* use Kronecker-Scho"nhage's multiplication */
#define KS_MULTIPLY

/* define top-level multiplication */
#define KARA 2
#define TOOM3 3
#define TOOM4 4
#define KS 5

/* compile with -DMULT=2 to override default */
#ifndef MULT
#ifdef KS_MULTIPLY
#define MULT KS
#else
#define MULT TOOM4
#endif
#endif

#ifdef POLYEVALTELLEGEN
#define POLYEVAL
#define USE_SHORT_PRODUCT
#endif

/* Use George Woltman's GWNUM library */
/* Should be defined via -DHAVE_GWNUM by Makefile
#define HAVE_GWNUM
*/

#ifdef HAVE_GWNUM
/* Only Fermat numbers with exponent >= GWTHRESHOLD are multiplied with 
   Woltman's DWT */
#define GWTHRESHOLD 1024
#endif

#include <stdio.h>
#include <gmp.h>

#if WANT_ASSERT
#include <assert.h>
#define ASSERT(expr)   assert (expr)
#else
#define ASSERT(expr)   do {} while (0)
#endif

/* thresholds */
#ifndef MUL_KARATSUBA_THRESHOLD
#define MUL_KARATSUBA_THRESHOLD 32
#endif

#ifndef DIV_DC_THRESHOLD
#define DIV_DC_THRESHOLD    (3 * MUL_KARATSUBA_THRESHOLD)
#endif

#define MPZMOD_THRESHOLD_DEFAULT (3 * DIV_DC_THRESHOLD / 2)
#define REDC_THRESHOLD_DEFAULT   (2 * DIV_DC_THRESHOLD)

/* base2mod is used when size(2^n+/-1) <= BASE2_THRESHOLD * size(cofactor) */
#define BASE2_THRESHOLD 1.4

/* default number of probable prime tests */
#define PROBAB_PRIME_TESTS 1

/* kronecker_schonhage() is used instead of toomcook4()
   when bitsize(poly) >= KS_MUL_THRESHOLD */
#define KS_MUL_THRESHOLD  1e6
/* same for median product */
#define KS_TMUL_THRESHOLD 8e5

#define ABS(x) ((x) >= 0 ? (x) : -(x))

/* maximal stage 1 bound = 2^53 + 4, the next prime being 2^53 + 5 */
#define MAX_B1 9007199254740996.0
#define DEFAULT_B1_DONE 1.0
#define IS_DEFAULT_B1_DONE(x) (x <= 1.0)

/* stage 2 bound */
#define DEFAULT_B2 -1.0
#define IS_DEFAULT_B2(x) (x < 0.0)

/* getprime */
#define FREE_PRIME_TABLE -1.0
#define WANT_FREE_PRIME_TABLE(p) (p < 0.0)

/* The checksum for savefile is the product of all mandatory fields, modulo
   the greatest prime below 2^32 */
#define CHKSUMMOD 4294967291U

/* different methods implemented */
#define EC_METHOD 0
#define PM1_METHOD 1
#define PP1_METHOD 2

#define MOD_PLAIN 0
#define MOD_BASE2 1
#define MOD_MODMULN 2
#define MOD_REDC 3

typedef mpz_t mpres_t;

typedef mpz_t* listz_t;

typedef struct
{
  mpres_t x;
  mpres_t y;
} __point_struct;
typedef __point_struct point;

typedef struct
{
  mpres_t x;
  mpres_t y;
  mpres_t A;
} __curve_struct;
typedef __curve_struct curve;

typedef struct
{
  unsigned int size_fd; /* How many entries .fd has, always nr * (S+1) */
  unsigned int nr;     /* How many separate progressions there are */
  unsigned int next;   /* From which progression to take the next root */
  unsigned int S;      /* Degree of the polynomials */
  unsigned int dsieve; /* Values not coprime to dsieve are skipped */
  unsigned int rsieve; /* Which residue mod dsieve current .next belongs to */
  int dickson_a;       /* Parameter for Dickson polynomials */
  point *fd;
  mpres_t *T;          /* For temp values. FIXME: should go! */
  curve *X;            /* The curve the points are on */
} __ecm_roots_state;
typedef __ecm_roots_state ecm_roots_state;

typedef struct
{
  unsigned int size_fd; /* How many entries .fd has, always nr * (S+1) */
  unsigned int nr;     /* How many separate progressions there are */
  unsigned int next;   /* From which progression to take the next root */
  unsigned int S;      /* Degree of the polynomials */
  unsigned int dsieve; /* Values not coprime to dsieve are skipped */
  unsigned int rsieve; /* Which residue mod dsieve current .next belongs to */
  int dickson_a;       /* Parameter for Dickson polynomials */
  mpres_t *fd;
  int invtrick;
} __pm1_roots_state;
typedef __pm1_roots_state pm1_roots_state;

typedef struct
{
  mpres_t fd[4];
  unsigned int dsieve; /* Values not coprime to dsieve are skipped */
  unsigned int rsieve; /* Which residue mod dsieve current .next belongs to */
} __pp1_roots_state;
typedef __pp1_roots_state pp1_roots_state;

typedef struct
{
  int alloc;
  int degree;
  listz_t coeff;
} __polyz_struct;
typedef __polyz_struct polyz_t[1];

typedef struct 
{
  int repr;           /* 0: plain modulus, possibly normalized
                         1: base 2 number
                         2: MODMULN
                         3: REDC representation */
  int bits;           /* in case of a base 2 number, 2^k[+-]1, bits = [+-]k
                         in case of MODMULN or REDC representation, nr. of 
                         bits b so that 2^b > orig_modulus and 
                         mp_bits_per_limb | b */
  int Fermat;         /* If repr = 1 (base 2 number): If modulus is 2^(2^m)+1, 
                         i.e. bits = 2^m, then Fermat = 2^m, 0 otherwise.
                         If repr != 1, undefined */
  mp_limb_t Nprim;    /* For MODMULN */
  mpz_t orig_modulus; /* The original modulus */
  mpz_t aux_modulus;  /* The auxiliary modulus value (i.e. normalized 
                         modulus, or -1/N (mod 2^bits) for REDC */
  mpz_t multiple;     /* The smallest multiple of N that is larger or
			 equal to 2^bits for REDC/MODMULN */
  mpz_t R2, R3;       /* For MODMULN and REDC, R^2 and R^3 (mod orig_modulus), 
                         where R = 2^bits. */
  mpz_t temp1, temp2; /* Temp values used during multiplication etc. */
} __mpmod_struct;
typedef __mpmod_struct mpmod_t[1];

/* Structure for candidate usage.  This is much more powerful than using a
   simple mpz_t to hold the candidate.  This structure also houses the 
   expression (in raw form), and will modify the expression as factors 
   are found (if in looping modes).  Also, since we are warehousing all
   of the data associated with the candidate, we also store whether the
   candidate is PRP here (so testing will cease), along with the length
   of the candidate.  As each factor is found, the candidate will also
   have the factor removed from it */
typedef struct
{
#if defined (CANDI_DEBUG)
  unsigned long magic;	/* used for debugging purposes while writing this code */
#endif
  char *cpExpr;		/* if non-NULL, then this is a "simpler" expression than the 
			   decimal output of n */
  mpz_t n;		/* the cofactor candidate currently being used to find factors from */
  unsigned ndigits;	/* the number of digits (decimal) in n */
  unsigned nexprlen;	/* strlen of expression, 0 if there is NO expression */
  int isPrp;		/* usually 0, but turns 1 if factor found, and the cofactor is PRP, 
			   OR if the original candidate was PRP and the user asked to prp check */
} mpcandi_t;

typedef struct
{
  int  Valid;           /* Is ONLY set to 1 if there is a proper -go <integer> switch.  Otherwise is 0
                           and if 0, then PM1, PP1 and ECM all ignore it */
  char *cpOrigExpr;	/* if non-NULL, then this is a "simpler" expression than the 
			   decimal output of n */
  mpcandi_t Candi;      /* The value after expression checked */
  int containsN;        /* 0 for simple number or expression.  1 if the expression "contains" N as
                           that expression will have to be built for each candidate */
} mpgocandi_t;

#if defined (__cplusplus)
extern "C" {
#endif  

  /* getprime.c */
double   getprime       (double);

/* auxi.c */
unsigned int nb_digits  (const mpz_t);
unsigned int gcd        (unsigned int, unsigned int);
void         mpz_sub_si (mpz_t, mpz_t, int);
void         mpz_divby3_1op (mpz_t);
unsigned int ceil_log2  (unsigned int);
void *       xmalloc    (size_t);
int          cputime    (void);
unsigned int get_random_ui (void);

/* pm1.c */
void    pm1_random_seed  (mpz_t, mpz_t, gmp_randstate_t);
int          pm1         (mpz_t, mpz_t, mpz_t, mpz_t, double, double, double, 
                          double, double, unsigned int, int, int, int);
int     pm1_rootsF       (mpz_t, listz_t, unsigned int, unsigned int, unsigned int,
                          mpres_t *, listz_t, int, mpmod_t, int);
pm1_roots_state *
        pm1_rootsG_init  (mpres_t *, double, unsigned int, unsigned int, int, 
                          int, mpmod_t);
void    pm1_rootsG_clear (pm1_roots_state *, mpmod_t);
int     pm1_rootsG       (mpz_t, listz_t, unsigned int, pm1_roots_state *, 
                          listz_t, mpmod_t, int);



/* ecm.c */
int ecm (mpz_t, mpz_t, mpz_t, mpz_t, mpz_t, double, double,
	 double, double, double, unsigned int, int, int, int, int);

/* bestd.c */
unsigned long phi (unsigned long);
void     bestD (double, double, unsigned int, unsigned int *, unsigned int *, 
                unsigned int *);
void     bestD_po2 (double, double, unsigned int *, unsigned int *, 
                         unsigned int *);

/* trial.c */
int trial_factor (mpcandi_t *n, double maxfact, int deep);

/* ecm2.c */
int     ecm_rootsF       (mpz_t, listz_t, unsigned int, unsigned int, 
                          unsigned int, curve *, int, mpmod_t, int);
ecm_roots_state * 
	ecm_rootsG_init  (mpz_t, curve *, double, unsigned int, unsigned int,
                          unsigned int, unsigned int, int, mpmod_t, int);
void    ecm_rootsG_clear (ecm_roots_state *, int, mpmod_t);
int     ecm_rootsG       (mpz_t, listz_t, unsigned int, ecm_roots_state *, 
                          mpmod_t, int);

/* lucas.c */
void  pp1_mul_prac     (mpres_t, unsigned long, mpmod_t, mpres_t, mpres_t,
                        mpres_t, mpres_t, mpres_t);

/* pp1.c */
void  pp1_random_seed  (mpz_t, mpz_t, gmp_randstate_t);
int   pp1              (mpz_t, mpz_t, mpz_t, mpz_t, double, double, double, 
                        double, double, unsigned int, unsigned int, int, int);
int   pp1_rootsF       (listz_t, unsigned int, unsigned int, unsigned int,
                        mpres_t *, listz_t, mpmod_t, int);
pp1_roots_state *
      pp1_rootsG_init  (mpres_t *, double, unsigned int, unsigned int, mpmod_t);
void  pp1_rootsG_clear (pp1_roots_state *, mpmod_t);
int   pp1_rootsG       (listz_t, unsigned int, pp1_roots_state *, mpmod_t, int);


/* stage2.c */
int          stage2     (mpz_t, void *, mpmod_t, double, double, unsigned int,
                         int, int, int, int);
void  fin_diff_coeff    (listz_t, double, double, unsigned int, int);
listz_t init_progression_coeffs 
			(double, unsigned int, unsigned int, unsigned int, 
			 unsigned int, unsigned int, int);
void clear_progression_coeffs 
			(listz_t, unsigned int, unsigned int, unsigned int, unsigned int);
void init_roots_state   (ecm_roots_state *, int, unsigned int, unsigned int, 
                         double);
                  

/* listz.c */
int          list_mul_mem (unsigned int);
listz_t      init_list  (unsigned int);
void         clear_list (listz_t, unsigned int);
void         print_list (listz_t, unsigned int);
void         print_list2 (listz_t, unsigned int);
void         list_set   (listz_t, listz_t, unsigned int);
void         list_revert (listz_t, unsigned int);
void         list_swap  (listz_t, listz_t, unsigned int);
void         list_neg   (listz_t, listz_t, unsigned int, mpz_t);
void         list_mod   (listz_t, listz_t, unsigned int, mpz_t);
void         list_add   (listz_t, listz_t, listz_t, unsigned int);
void         list_sub   (listz_t, listz_t, listz_t, unsigned int);
void         list_mul_z (listz_t, listz_t, mpz_t, unsigned int, mpz_t);
int          list_gcd   (mpz_t, listz_t, unsigned int, mpz_t);
void         list_zero  (listz_t, unsigned int);
int          list_zerop (listz_t, unsigned int);
int          list_check (listz_t, unsigned int, mpz_t);
void      list_mul_high (listz_t, listz_t, listz_t, unsigned int, listz_t);
int       toomcook4_low (listz_t, listz_t, listz_t, unsigned int, listz_t);
int      toomcook4_high (listz_t, listz_t, listz_t, unsigned int, listz_t);
void         karatsuba  (listz_t, listz_t, listz_t, unsigned int, listz_t);
void         list_mul   (listz_t, listz_t, unsigned int, int, listz_t,
                         unsigned int, int, listz_t);
void        list_mulmod (listz_t, listz_t, listz_t, listz_t, unsigned int,
                         listz_t, mpz_t);
void      PolyFromRoots (listz_t, listz_t, unsigned int, listz_t, int, mpz_t,
                         char, listz_t*, unsigned int);
void         PolyInvert (listz_t, listz_t, unsigned int, listz_t, mpz_t);
void  RecursiveDivision (listz_t, listz_t, listz_t, unsigned int,
                         listz_t, mpz_t, int);
void  PrerevertDivision (listz_t, listz_t, listz_t, unsigned int, listz_t,
                         mpz_t);
int          list_invert (listz_t, listz_t, unsigned int, mpz_t, mpmod_t);

/* polyeval.c */
void polyeval (listz_t, unsigned int, listz_t*, listz_t, mpz_t, int,
               unsigned int);
void
polyeval_tellegen (listz_t b, unsigned int k, listz_t *Tree, listz_t T,
                   unsigned int sizeT, listz_t invF, mpz_t n, unsigned int sh);

/* toomcook.c */
void          toomcook3 (listz_t, listz_t, listz_t, unsigned int, listz_t);
void          toomcook4 (listz_t, listz_t, listz_t, unsigned int, listz_t);

/* ks-multiply.c */
void kronecker_schonhage (listz_t, listz_t, listz_t, unsigned int, listz_t);
unsigned int TMulKS     (listz_t, unsigned int, listz_t, unsigned int, listz_t,
                         unsigned int, mpz_t, int);
unsigned int ks_wrapmul_m (unsigned int, unsigned int, mpz_t);
unsigned int ks_wrapmul (listz_t, unsigned int, listz_t, unsigned int,
                         listz_t, unsigned int, mpz_t);

/* mpmod.c */
int isbase2 (mpz_t, double);
void mpmod_init (mpmod_t, mpz_t, int, int);
void mpmod_init_MPZ (mpmod_t, mpz_t);
void mpmod_init_BASE2 (mpmod_t, int, mpz_t);
void mpmod_init_MODMULN (mpmod_t, mpz_t);
void mpmod_init_REDC (mpmod_t, mpz_t);
void mpmod_clear (mpmod_t);
void mpres_pow(mpres_t, mpres_t, mpres_t, mpmod_t);
void mpres_ui_pow (mpres_t, unsigned int, mpres_t, mpmod_t);
void mpres_mul(mpres_t, mpres_t, mpres_t, mpmod_t);
void mpres_div_2exp(mpres_t, mpres_t, unsigned int, mpmod_t);
void mpres_add_ui (mpres_t, mpres_t, unsigned int, mpmod_t);
void mpres_add (mpres_t, mpres_t, mpres_t, mpmod_t);
void mpres_sub_ui (mpres_t, mpres_t, unsigned int, mpmod_t);
void mpres_sub (mpres_t, mpres_t, mpres_t, mpmod_t);
void mpres_set_z (mpres_t, mpz_t, mpmod_t);
void mpres_get_z (mpz_t, mpres_t, mpmod_t);
void mpres_set_ui (mpres_t, unsigned int, mpmod_t);
void mpres_init (mpres_t, mpmod_t);
void mpres_realloc (mpres_t, mpmod_t);
void mpres_mul_ui (mpres_t, mpres_t, unsigned int, mpmod_t);
void mpres_neg (mpres_t, mpres_t, mpmod_t);
int  mpres_invert (mpres_t, mpres_t, mpmod_t);
void mpres_gcd (mpz_t, mpres_t, mpmod_t);
void mpres_out_str (FILE *, unsigned int, mpres_t, mpmod_t);
int  mpres_is_zero (mpres_t, mpmod_t);
#define mpres_clear(a,n) mpz_clear (a)
#define mpres_set(a,b,n) mpz_set (a, b)
#define mpres_swap(a,b,n) mpz_swap (a, b)

/* mul_lo.c */
void mpn_mul_lo_n (mp_ptr, mp_srcptr, mp_srcptr, mp_size_t);

/* resume.c */
int  facceptstr (FILE *, char *);
int  freadstrn (FILE *, char *, char, unsigned int);
int  read_resumefile_line (int *, mpz_t, mpcandi_t *, mpz_t, mpz_t, mpz_t, double *,
                           char *, char *, char *, char *, FILE *);
void write_resumefile_line (FILE *, int, double, mpz_t, mpz_t, mpz_t, mpcandi_t *, 
                            mpz_t, const char *);
void write_temp_resumefile (int method, double B1, mpz_t sigma, mpz_t A, mpz_t x, mpz_t n, mpz_t orig_X0, int);
void kill_temp_resume_file (void);

/* main.c */
int read_number (mpcandi_t *n, FILE *, int primetest);
void usage (void);

/* eval.c */
int eval (mpcandi_t *n, FILE *fd, int bPrp);
int eval_str (mpcandi_t *n, char *cp, int primetest, char **EndChar); /* EndChar can be NULL */
void init_expr (void);
void free_expr (void);

/* candi.c */
void mpcandi_t_init (mpcandi_t *n);  /* damn, a C++ class sure would have been nice :(  */
void mpcandi_t_free (mpcandi_t *n);
int  mpcandi_t_copy (mpcandi_t *to, mpcandi_t *from);
int  mpcandi_t_add_candidate (mpcandi_t *n, mpz_t c, const char *cpExpr, int bPrp);
int  mpcandi_t_addfoundfactor (mpcandi_t *n, mpz_t f, int displaywarning);
int  mpcandi_t_addfoundfactor_d (mpcandi_t *n, double f);
/* candi.c   Group Order candidate functions.  */
void mpgocandi_t_init(mpgocandi_t *go);
void mpgocandi_t_free(mpgocandi_t *go);
int  mpgocandi_fixup_with_N(mpgocandi_t *go, mpcandi_t *n);


/* smartprp.c */
int smart_probab_prime_p(mpz_t const n, int c);

/* Options for using an external PRPer rather than internal GMP */
extern char *externalprp; /* call out to external program  */  
extern char *externallog; /* where to find output */
extern char *externalinputprpfile; /* Used to place the n value (a temp file). Is deleted after system */
extern char *externalisprp; /* what to match output against */
extern char *externaliscomposite; /* ditto */
extern int externalprplen; /* length where we go external */
extern int externalprpval; /* exit value meaning it's prp, -1 is impossible */

/* b1_ainc.c */
double calc_B1_AutoIncrement(double cur_B1, double incB1val, int calcInc);

/* median.c */
unsigned int
TMulGen (listz_t, unsigned int, listz_t, unsigned int, listz_t, 
         unsigned int, listz_t, mpz_t);
unsigned int
TKarMul_space (unsigned int n, unsigned int m, unsigned int l);
unsigned int
TMulGen_space (unsigned int n, unsigned int m, unsigned int l);
unsigned int muls_tkara (unsigned int n);

/* schoen_strass.c */

#define DEFAULT 0
#define MONIC 1
#define NOPAD 2
unsigned int F_mul (mpz_t *, mpz_t *, mpz_t *, unsigned int, int, unsigned int, mpz_t *);
unsigned int F_mul_trans (mpz_t *, mpz_t *, mpz_t *, unsigned int, unsigned int, mpz_t *);

/* rho.c */

void   rhoinit (int, int);
double ecmprob (double, double, double, double, int);

/* memory.c */
#ifdef MEMORY_DEBUG
void __gmp_default_free (void *, size_t);
void *__gmp_default_allocate (size_t);
void *__gmp_default_reallocate (void *, size_t, size_t);
void tests_memory_start (void);
void tests_memory_end   (void);
void tests_memory_reset (void);
void tests_free (void *, size_t);
void tests_memory_status (void);
#define FREE(ptr,size) tests_free(ptr,size)
#else
#define FREE(ptr,size) free(ptr)
#endif

#if defined (__cplusplus)
}
#endif  

/* a <- b * c where a and b are mpz, c is a double, and t an auxiliary mpz */
#if (BITS_PER_MP_LIMB >= 53)
#define mpz_mul_d(a, b, c, t) \
   mpz_mul_ui (a, b, (unsigned long int) c);
#else
#if (BITS_PER_MP_LIMB >= 32)
#define mpz_mul_d(a, b, c, t) \
   if (c < 4294967296.0) \
      mpz_mul_ui (a, b, (unsigned long int) c); \
   else { \
   mpz_set_d (t, c); \
   mpz_mul (a, b, t); }
#else
#define mpz_mul_d(a, b, c, t) \
   mpz_set_d (t, c); \
   mpz_mul (a, b, t);
#endif
#endif

#endif /* __ECM_H */
