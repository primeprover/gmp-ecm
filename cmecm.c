/* cmecm.c - ECM with CM curves for specific numbers
   Author: F. Morain
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <gmp.h> /* GMP header file */

#include "ecm.h" /* ecm header file */
#include "ecm-impl.h"
#include "ecm-ecm.h"
#include "mpmod.h"

#include "addlaws.h"
#include "torsions.h"
#include "cmecm.h"

static int
adjust_CM(mpz_t f, ec_curve_t E, ec_point_t P, mpz_t N, mpz_t j)
{
    mpz_t k;
    long x0;
    int ret = ECM_NO_FACTOR_FOUND;

    /* k = j/(1728-j) */
    mpz_init_set_si(k, 1728);
    mpz_sub(k, k, j);
    mpz_mod(k, k, N);
    if(mpz_invert(f, k, N) == 0){
	printf("# factor found (adjust_CM)\n");
	mpz_gcd(f, k, N);
	ret = ECM_FACTOR_FOUND_STEP1;
    }
    else{
	mpz_mul(k, f, j);
	mpz_mod(k, k, N);
	/* a = 3*k, b = 2*k */
	mpz_set(E->A, k);
	mpz_add(j, k, k);
	mpz_mod(j, j, N);
	mpz_add(E->A, E->A, j);
	mpz_mod(E->A, E->A, N);
	x0 = 0;
	ec_force_point(E, P, j, &x0, N);
    }
    return ret;
}

/* Curves are built mod N, not in nres */
int
build_curves_with_CM(mpz_t f, int *nE, ec_curve_t *tE, ec_point_t *tP, 
		     int disc, mpmod_t n, mpz_t *sqroots)
{
    mpz_t j, tmp;
    long x0;
    int i, ret = ECM_NO_FACTOR_FOUND, imax;

    ec_curve_init(tE[0], n);
    ec_point_init(tP[0], tE[0], n);
    tE[0]->disc = disc;
    mpz_init_set_ui(tE[0]->sq[0], 1);
    *nE = 1;
    if(disc == -3){
	/* D = -3 => E: Y^2 = X^3 + 8 has rank 1, generator (2 : 4 : 1)
	   f4 = P2*P4, disc(P2) = 3*2^4
	*/
	imax = (sqroots == NULL ? 1 : 6);

	for(i = 0; i < imax; i++){
	    if(i > 0){
		ec_curve_init(tE[i], n);
		ec_point_init(tP[i], tE[i], n);
	    }
	    tE[i]->type = ECM_EC_TYPE_WEIERSTRASS;
	    mpz_set_ui(tE[i]->A, 0);
	    tE[i]->disc = -3;
	}
	mpz_set_si(tP[0]->x, 2);
	mpz_set_si(tP[0]->y, 4);
	mpz_set_si(tP[0]->z, 1);

	if(sqroots != NULL){
	    /* TODO: use complex twists? */
	    mpz_t zeta6;
	    /* compute zeta6 from sqrt(-3) */
	    mpz_init(zeta6);
	    mpz_init(tmp);
	    mpz_add_si(zeta6, sqroots[0], 1);
	    mod_div_2(zeta6, n->orig_modulus);
	    mpz_powm_ui(tmp, zeta6, 3, n->orig_modulus);
	    mpz_add_si(tmp, tmp, 1);
	    mpz_mod(tmp, tmp, n->orig_modulus);
	    if(mpz_sgn(tmp) != 0){
		gmp_printf("# zeta6^3+1=%Zd\n", tmp);
		exit(-1);
	    }
	    mpz_set_ui(tmp, 8);
	    for(i = 1; i < imax; i++){
		mpz_mul(tmp, tmp, zeta6);
		mpz_mod(tmp, tmp, n->orig_modulus);
		x0 = 0;
		/* works since tE[i]->A is always 0... */
		ec_force_point(tE[i], tP[i], tmp, &x0, n->orig_modulus);
	    }
	    *nE = 6;
	    mpz_clear(zeta6);
	    mpz_clear(tmp);
            for(i = 0; i < imax; i++)
		mpz_init_set(tE[i]->sq[0], sqroots[0]);
	}
    }
    else if(disc == -4){
#if 1
	/* Y^2 = X^3 + 9 * X has rank 1 and a 4-torsion point */
	/* a generator is (4 : 10 : 1) */
	imax = (sqroots == NULL ? 1 : 4);

	for(i = 0; i < imax; i++){
	    if(i > 0){
		ec_curve_init(tE[i], n);
		ec_point_init(tP[i], tE[i], n);
	    }
	    tE[i]->type = ECM_EC_TYPE_WEIERSTRASS;
	    tE[i]->disc = -4;
	}
        mpz_set_ui(tE[0]->A, 9);
        mpz_set_si(tP[0]->x, 4);
        mpz_set_si(tP[0]->y, 10);
        mpz_set_si(tP[0]->z, 1);
	if(sqroots != NULL){
	    /* sqroots[0] = sqrt(-1) */
	    mpz_init(tmp);
	    mpz_mul(tmp, sqroots[0], sqroots[0]);
	    mpz_add_si(tmp, tmp, 1);
	    mpz_mod(tmp, tmp, n->orig_modulus);
	    if(mpz_sgn(tmp) != 0){
		gmp_printf("# zeta4^2+1=%Zd\n", tmp);
		exit(-1);
	    }
	    for(i = 1; i < imax; i++){
		mpz_mul(tmp, tE[i-1]->A, sqroots[0]);
		mpz_mod(tE[i]->A, tmp, n->orig_modulus);
		x0 = 1; /* x0 = 0 is bad, since this is a 2-torsion point */
		mpz_set_si(tmp, 0);
		ec_force_point(tE[i], tP[i], tmp, &x0, n->orig_modulus);
	    }
	    *nE = 4;
	    mpz_clear(tmp);
	    for(i = 0; i < imax; i++)
		mpz_init_set(tE[i]->sq[0], sqroots[0]);
	}
#else /* one day, use this? */
	/* => 1/3*y^2 = x^3 + x, gen = (4/3, 10/3) */
	tE[0]->type = ECM_EC_TYPE_MONTGOMERY;
	mpres_set_ui(tE[0]->A, 0, n);
	mod_from_rat_str(f, "4/3", n->orig_modulus);
	mpres_set_z(tP[0]->x, f, n);
#endif
    }
    else if(disc == -7){
	/* E = y^2 = x^3 - 2222640*x - 1568294784
	           = x^3 - 5*7*(2^2*3^2*7)^2*x - 2*7^2*(2^2*3^2*7)^3
	   P = (2052 : 50112 : 1) */
	tE[0]->type = ECM_EC_TYPE_WEIERSTRASS;
	mpz_set_si(tE[0]->A, -2222640);
        mpz_set_si(tP[0]->x, 2052);
        mpz_set_si(tP[0]->y, 50112);
        mpz_set_si(tP[0]->z, 1);
    }
    else if(disc == -8){
	/* D = -8: E_c: Y^2 = X^3+4*c*X^2+2*c^2*X => Montgomery when 2 = z^2 
	   c = 1 => rank = 1, generator is (-1 : -1 : 1)
	   alt.: [-2*3*5*cc^2, 2^3*7*cc^3], here with cc=12
	*/
	tE[0]->type = ECM_EC_TYPE_WEIERSTRASS;
	mpz_set_si(tE[0]->A, -4320);
        mpz_set_si(tP[0]->x, 12);
        mpz_set_si(tP[0]->y, -216);
        mpz_set_si(tP[0]->z, 1);
    }
    else if(disc == -11){
	/*     E:=EllipticCurve([0, 0, 0, -2^5*3*11, 2^4*7*11^2]);
	       [ (33 : 121 : 1) ] */
	tE[0]->type = ECM_EC_TYPE_WEIERSTRASS;
	mpz_set_si(tE[0]->A, -1056);
	mpz_set_si(tP[0]->x, 33);
        mpz_set_si(tP[0]->y, 121);
        mpz_set_si(tP[0]->z, 1);
    }
    /* class number 2 */
    else if(disc == -15){
	/* it must be that sqroots[0] contains sqrt(5) mod N */
	/* j = -(191025+85995*sqrt(5))/2 */
	tE[0]->type = ECM_EC_TYPE_WEIERSTRASS;
	mpz_set(tE[0]->sq[0], sqroots[0]);
	mpz_init_set_si(j, 85995);
	mpz_mul(j, j, sqroots[0]);
	mpz_add_si(j, j, 191025);
	mpz_neg(j, j);
	mpz_mod(j, j, n->orig_modulus);
	mod_div_2(j, n->orig_modulus);
	ret = adjust_CM(f, tE[0], tP[0], n->orig_modulus, j);
	mpz_clear(j);
    }
    else{
	printf("Unknown discriminant: %d\n", disc);
	ret = ECM_ERROR;
    }
    return ret;
}

/******************** Stage 2 ********************/

/* General idea: we want to match [U]P = [V][omega]P, where 
   4*B1 < U^2+D*V^2 <= 4*B2.
   F could have all ([u]P)_x as roots;
   G could have all ([v][omega]P)_x.
   We do not need to test Gcd(F, F').
*/

/********** NAIVE version **********/

/* Find if some x_u = xt_v where [u]P=(x_u, ...), [v]Q=(xt_v, ...). 
   A priori, #v < #u, so we precompute all v.
   One looks for u^2+d*v^2 with umin <= u <= umax, vmin <= v <= vmax,
   where umax = sqrt(cof*B2-d*vmin^2), vmax = sqrt((cof*B2-umin^2)/d).
*/
static
int LoopCM(mpz_t f, ec_curve_t E, ec_point_t P, ec_point_t Q,
	   mpmod_t modulus, mpz_t B2, int cof, int d, mpres_t omega,
	   unsigned long umin, unsigned long du,
	   unsigned long vmin, unsigned long dv)
{
    int ret = ECM_NO_FACTOR_FOUND, compute_uP = 1;
    ec_point_t uP, duP, vQ, dvQ;
    mpz_ptr xtv, ztv; /* suboptimal? */
    mpz_t tmp, xu, zu, tmp2, omega5;
    long tp = cputime();
    unsigned long umax, vmax, u, v, iv, vsup, nv;

    mpz_init(tmp);
    mpz_init(tmp2);
    /* u <= sqrt(cof*B2-d*vmin^2) */
    mpz_set(tmp, B2);
    mpz_mul_si(tmp, tmp, cof);
    mpz_set_ui(tmp2, vmin);
    mpz_mul_ui(tmp2, tmp2, vmin);
    mpz_mul_ui(tmp2, tmp2, d);
    mpz_sub(tmp, tmp, tmp2);
    mpz_sqrt(tmp, tmp);
    gmp_printf("# umax=%Zd\n", tmp);
    if(mpz_fits_ulong_p(tmp) == 0)
	gmp_printf("#!# Gasp: umax=%Zd too large\n", tmp);
    umax = mpz_get_ui(tmp);
    /* v <= sqrt((cof*B2-umin^2)/d) */
    mpz_set(tmp, B2);
    mpz_mul_si(tmp, tmp, cof);
    mpz_set_ui(tmp2, umin);
    mpz_mul_ui(tmp2, tmp2, umin);
    mpz_sub(tmp, tmp, tmp2);
    mpz_fdiv_q_ui(tmp, tmp, d);
    mpz_sqrt(tmp, tmp);
    gmp_printf("# vmax=%Zd\n", tmp);
    if(mpz_fits_ulong_p(tmp) == 0)
	gmp_printf("#!# Gasp: vmax=%Zd too large\n", tmp);
    vmax = mpz_get_ui(tmp);

    /* precompute all v's */
    nv = 1 + ((vmax-vmin)/dv);
    xtv = (mpz_ptr)malloc(nv * sizeof(__mpz_struct));
    ztv = (mpz_ptr)malloc(nv * sizeof(__mpz_struct));
    ec_point_init(vQ, E, modulus);
    mpz_set_ui(tmp, vmin);
    ec_point_mul(vQ, tmp, Q, E, modulus);
    ec_point_init(dvQ, E, modulus);
    mpz_set_ui(tmp, dv);
    ec_point_mul(dvQ, tmp, Q, E, modulus);
    for(v = vmin, iv = 0; v <= vmax; v += dv, iv++){
	mpz_init(xtv+iv);
	mpres_get_z(xtv+iv, vQ->x, modulus);
	mpz_init(ztv+iv);
	mpres_get_z(ztv+iv, vQ->z, modulus);
	ec_point_add(vQ, vQ, dvQ, E, modulus);
    }
    ec_point_clear(vQ, E, modulus);
    ec_point_clear(dvQ, E, modulus);
    printf("# computing %lu (// %lu) additions: %ldms\n", iv, nv,
	   elltime(tp, cputime()));

    /* compute all uP */
    tp = cputime();
    compute_uP = !(d == 3 && du == 1 && dv == 1);
    ec_point_init(uP, E, modulus);
    mpz_set_ui(tmp, umin);
    ec_point_mul(uP, tmp, P, E, modulus);
    ec_point_init(duP, E, modulus);
    mpz_set_ui(tmp, du);
    ec_point_mul(duP, tmp, P, E, modulus);
    if(compute_uP == 0){
	/* omega5 = omega^5 = 1/omega */
	mpz_init(omega5);
	mpres_get_z(omega5, omega, modulus);
	mpz_powm_ui(omega5, omega5, 5, modulus->orig_modulus);
    }

    mpz_init(xu);
    mpz_init(zu);
    mpz_set_ui(f, 1);
    for(u = umin; u <= umax; u += du){
	if(compute_uP || u > vmax){
	    mpres_get_z(xu, uP->x, modulus);
	    mpres_get_z(zu, uP->z, modulus);
	}
	else{
	    /* [omega5]Q = [omega^6]P = P */
	    mpz_set(xu, xtv+(u-1));
	    mpz_mul(xu, xu, omega5);
	    mpz_mod(xu, xu, modulus->orig_modulus);
	    mpz_set(zu, ztv+(u-1));
	}
	/* d*v^2 <= B2-u^2 */
	mpz_set_ui(tmp, u);
	mpz_mul_ui(tmp, tmp, u);
	mpz_sub(tmp, B2, tmp);
	if(d != 1)
	    mpz_fdiv_q_ui(tmp, tmp, d);
	mpz_sqrt(tmp, tmp);
	if(mpz_fits_ulong_p(tmp) == 0)
	    gmp_printf("#!# Gasp: vmax=%Zd too large\n", tmp);
	vsup = mpz_get_ui(tmp);
	/*	printf("# u = %lu => vsup = %lu\n", u, vsup);*/
	for(v = vmin, iv = 0; v <= vsup; v += dv, iv++){
	    /* xu/zu = xtv/ztv <=> xu*ztv-xtv*zu = 0 */
	    mpz_mul(tmp, xu, ztv+iv);
	    mpz_mul(tmp2, zu, xtv+iv);
	    mpz_sub(tmp, tmp, tmp2);
	    if(mpz_sgn(tmp) == 0){
		printf("[%ld]P = [%ld]Q?\n", u, v);
		ec_curve_print(E, modulus);
		exit(-1);
	    }
	    mpz_mul(f, f, tmp);
	    mpz_mod(f, f, modulus->orig_modulus);
	}
	mpz_gcd(f, f, modulus->orig_modulus);
	if(mpz_cmp_ui(f, 1) != 0){
	    gmp_printf("# Youpi: u=%ld, f=%Zd\n", u, f);
	    ret = ECM_FACTOR_FOUND_STEP2;
	    break;
	}
	if(compute_uP || u > vmax)
	    ec_point_add(uP, uP, duP, E, modulus);
	if(compute_uP == 0 && u == (vmax+1)){
	    /* compute next point */
	    mpz_set_ui(tmp, vmax+1);
	    ec_point_mul(uP, tmp, P, E, modulus);
	}
    }
    mpz_clear(xu);
    mpz_clear(zu);
    mpz_clear(tmp);
    mpz_clear(tmp2);
    ec_point_clear(uP, E, modulus);
    ec_point_clear(duP, E, modulus);
    if(compute_uP == 0)
	mpz_clear(omega5);
    for(v = vmin, iv = 0; v <= vmax; v += dv, iv++){
	mpz_clear(xtv+iv);
	mpz_clear(ztv+iv);
    }
    free(xtv);
    free(ztv);
    printf("# using all [u]P: %ldms\n", elltime(tp, cputime()));
    return ret;
}

/* Testing CM stage2 in a very naive way, for the time being. */
int stage2_CM(mpz_t f, ec_curve_t E, ec_point_t P, mpmod_t modulus, 
	      unsigned long dF, mpz_t B2, mpz_t B2min)
{
    int ret = ECM_NO_FACTOR_FOUND;
    ec_point_t Q;
    mpz_t tmp;
    unsigned long umin, du, vmin, dv;
    mpres_t omega;

    printf("PE:="); ec_point_print(P, E, modulus); printf(";\n");
    if (dF == 0)
	return ECM_NO_FACTOR_FOUND;

    mpz_init(tmp);
    if(E->disc == -3){
	/* case where pi = U+V*omega, U and V with the same parity */
	/* omega = (1+sqrt(-3))/2 */
	mpres_init(omega, modulus);
	mpres_set(omega, E->sq[0], modulus);
	mpres_add_ui(omega, omega, 1, modulus);
	mpres_div_2exp(omega, omega, 1, modulus);
	/* 1st case: u^2+3*v^2 <= B2, no restriction on u, v */
	/* we can easily compute [v][omega]P as [omega]([v]P) */
	umin = 1;
	du = 1;
	vmin = 1;
	dv = 1;

	/* Q = [omega](P) = [omega*P.x, P.y, 1] */
	gmp_printf("N:=%Zd;\n", modulus->orig_modulus);
	printf("zeta3:=");print_mpz_from_mpres(E->sq[0],modulus);printf(";\n");
	ec_point_init(Q, E, modulus);
	mpres_mul(Q->x, P->x, omega, modulus);
	mpres_set(Q->y, P->y, modulus);
	mpres_set_ui(Q->z, 1, modulus);
	ret = LoopCM(f,E,P,Q,modulus,B2,1,3,omega,umin,du,vmin,dv);

	if(ret == ECM_NO_FACTOR_FOUND){
	    /* 2nd case: u^2+3*v^2 <= 4*B2, u and v odd */
	    /* we can easily compute [v][omega]P as [omega]([v]P) */
	}
	ec_point_clear(Q, E, modulus);
	mpres_clear(omega, modulus);
    }
    else if(E->disc == -4){
	/* case where pi = u+v*zeta4, u odd, v even */
	umin = 1;
	du = 2;
	vmin = 2;
	dv = 2;

	/* Q = [zeta4](P) = [-P.x, zeta4*P.y, 1] */
	gmp_printf("N:=%Zd;\n", modulus->orig_modulus);
	printf("zeta4:=");print_mpz_from_mpres(E->sq[0],modulus);printf(";\n");
	ec_point_init(Q, E, modulus);
	mpres_neg(Q->x, P->x, modulus);
	mpres_mul(Q->y, P->y, E->sq[0], modulus);
	mpres_set_ui(Q->z, 1, modulus);
	ret = LoopCM(f,E,P,Q,modulus,B2,1,1,E->sq[0],umin,du,vmin,dv);
	ec_point_clear(Q, E, modulus);
    }
    else{
	printf("# stage2_CM not ready for disc=%d\n", E->disc);
    }
    mpz_clear(tmp);
    return ret;
}

/********** fast version **********/

unsigned long
compute_dF_CM(mpz_t B2, int disc)
{
    mpz_t tmp;
    unsigned long umax, dF = 0;

    if(disc == -4){
	/* u^2 + v^2 <= B2, u odd, v even */
	mpz_init_set(tmp, B2);
	mpz_sub_si(tmp, tmp, 4);
	mpz_sqrt(tmp, tmp);
	umax = mpz_get_ui(tmp);
	/* largest u must be odd */
	if(umax % 2 == 0)
	    umax--;
	/* 1 <= u <= umax => 0 <= (u-1)/2 <= (umax-1)/2 */
	dF = 1 + (umax>>1);
	mpz_clear(tmp);
    }
    return dF;
}

/* F[i] <- ([i*dk]P)_x for kmin <= k <= kmax. */
int all_multiples(mpz_t f, listz_t F, unsigned long dF, 
		  ec_curve_t E, ec_point_t P, mpmod_t modulus,
		  unsigned long kmin, unsigned long kmax, unsigned long dk)
{
    int ret = ECM_NO_FACTOR_FOUND;
    ec_point_t kP, dkP;
    unsigned long k, ik;
    mpz_t tmp;

    mpz_init(tmp);
    ec_point_init(kP, E, modulus);
    mpz_set_ui(tmp, kmin);
    if(ec_point_mul(kP, tmp, P, E, modulus) == 0){
	printf("# factor found at strange place 1\n");
	mpz_set(f, kP->x);
	ret = ECM_FACTOR_FOUND_STEP2;
	goto end_of_all_multiples;
    }
    ec_point_init(dkP, E, modulus);
    mpz_set_ui(tmp, dk);
    if(ec_point_mul(dkP, tmp, P, E, modulus) == 0){
	printf("# factor found at strange place 2\n");
	mpz_set(f, dkP->x);
	ret = ECM_FACTOR_FOUND_STEP2;
	goto end_of_all_multiples;
    }
    for(k = kmin, ik = 0; k <= kmax; k += dk, ik++){
	/* F[ik] <= kP_x */
	assert(ik < dF);
	mpres_get_z(F[ik], kP->x, modulus);
	if(ec_point_add(kP, kP, dkP, E, modulus) == 0){
	    printf("# factor found when adding dkP\n");
	    mpz_set(f, kP->x);
	    ret = ECM_FACTOR_FOUND_STEP2;
	    break;
	}
    }
    ec_point_clear(dkP, E, modulus);
 end_of_all_multiples:
    ec_point_clear(kP, E, modulus);
    mpz_clear(tmp);
    return ret;
}

int ecm_rootsF_CM(mpz_t f, listz_t F, unsigned long dF, curve *C, 
		  mpmod_t modulus, double B1, mpz_t B2)
{
    int ret = ECM_NO_FACTOR_FOUND;
    ec_curve_t E;
    ec_point_t P;
    unsigned long umax;
    mpz_t tmp;

    printf("# Entering ecm_rootsF_CM\n");
    ec_curve_init(E, modulus);
    E->type = ECM_EC_TYPE_WEIERSTRASS;
    mpres_set(E->A, C->A, modulus);
    ec_point_init(P, E, modulus);
    mpres_set(P->x, C->x, modulus);
    mpres_set(P->y, C->y, modulus);
    if(C->disc == -4){
	/* u odd, v even, B1 < u^2+v^2 <= B2 */
	/* 1 <= u^2 <= B2-4 */
	mpz_init_set(tmp, B2);
	mpz_sub_si(tmp, tmp, 4);
	mpz_sqrt(tmp, tmp);
	if(mpz_fits_ulong_p(tmp) == 0){
            gmp_printf("#!# Gasp: umax=%Zd too large\n", tmp);
	    ret = ECM_ERROR;
	}
	else{
	    umax = mpz_get_ui(tmp);
	    ret = all_multiples(f, F, dF, E, P, modulus, 1, umax, 2);
	}
	mpz_clear(tmp);
    }
    ec_point_clear(P, E, modulus);
    ec_curve_clear(E, modulus);

    exit(-1);

    return ret;
}
