#include "ntt-impl.h"

#define NC 54

static uint32_t 
ntt35_get_num_const(void)
{
  return NC;
}

extern void ntt5_init(spv_t out, sp_t p, sp_t d, 
			sp_t primroot, sp_t order);

extern void ntt7_init(spv_t out, sp_t p, sp_t d, 
			sp_t primroot, sp_t order);

void
ntt35_init(spv_t out, sp_t p, sp_t d, 
	  sp_t primroot, sp_t order)
{
  uint32_t i, j;
  uint32_t num5 = 6;
  uint32_t num7 = 9;
  spv_t root5 = (spv_t)alloca(num5 * sizeof(sp_t));
  spv_t root7 = (spv_t)alloca(num7 * sizeof(sp_t));

  ntt5_init(root5, p, d, primroot, order);
  ntt7_init(root7, p, d, primroot, order);

  for (i = 0; i < num5; i++)
    for (j = 0; j < num7; j++)
      out[num7 * i + j] = sp_mul(root5[i], root7[j], p, d);
}

static void
ntt35_run(spv_t x, spv_size_t stride,
	  sp_t p, sp_t d, spv_t ntt_const)
{
  sp_t a00, a01, a02, a03, a04, a05, a06, 
       a07, a08, a09, a10, a11, a12, a13, 
       a14, a15, a16, a17, a18, a19, a20, 
       a21, a22, a23, a24, a25, a26, a27, 
       a28, a29, a30, a31, a32, a33, a34, 
       a35, a36, a37, a38, a39, a40, a41;

  {
    sp_t t1, t2, t3, t4;

    sp_t x0 = x[ 0 * stride];
    sp_t x1 = x[ 7 * stride];
    sp_t x4 = x[14 * stride];
    sp_t x2 = x[21 * stride];
    sp_t x3 = x[28 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a01 = sp_add(t1, t2, p);
    a02 = sp_sub(t1, t2, p);
    a03 = t3;
    a04 = t4;
    a05 = sp_add(t3, t4, p);

    a00 = sp_add(x0, a01, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x0 = x[ 5 * stride];
    sp_t x1 = x[12 * stride];
    sp_t x4 = x[19 * stride];
    sp_t x2 = x[26 * stride];
    sp_t x3 = x[33 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a07 = sp_add(t1, t2, p);
    a08 = sp_sub(t1, t2, p);
    a09 = t3;
    a10 = t4;
    a11 = sp_add(t3, t4, p);

    a06 = sp_add(x0, a07, p);
  }
  {
    sp_t t0, t1, t2, t3, t4, t5, t6, t7;

    sp_t x3 = x[ 3 * stride];
    sp_t x0 = x[10 * stride];
    sp_t x1 = x[17 * stride];
    sp_t x4 = x[24 * stride];
    sp_t x2 = x[31 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a13 = sp_add(t1, t2, p);
    a14 = sp_sub(t1, t2, p);
    a15 = t3;
    a16 = t4;
    a17 = sp_add(t3, t4, p);

    a12 = sp_add(x0, a13, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x2 = x[ 1 * stride];
    sp_t x3 = x[ 8 * stride];
    sp_t x0 = x[15 * stride];
    sp_t x1 = x[22 * stride];
    sp_t x4 = x[29 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a19 = sp_add(t1, t2, p);
    a20 = sp_sub(t1, t2, p);
    a21 = t3;
    a22 = t4;
    a23 = sp_add(t3, t4, p);

    a18 = sp_add(x0, a19, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x2 = x[ 6 * stride];
    sp_t x3 = x[13 * stride];
    sp_t x0 = x[20 * stride];
    sp_t x1 = x[27 * stride];
    sp_t x4 = x[34 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a25 = sp_add(t1, t2, p);
    a26 = sp_sub(t1, t2, p);
    a27 = t3;
    a28 = t4;
    a29 = sp_add(t3, t4, p);

    a24 = sp_add(x0, a25, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x4 = x[ 4 * stride];
    sp_t x2 = x[11 * stride];
    sp_t x3 = x[18 * stride];
    sp_t x0 = x[25 * stride];
    sp_t x1 = x[32 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a31 = sp_add(t1, t2, p);
    a32 = sp_sub(t1, t2, p);
    a33 = t3;
    a34 = t4;
    a35 = sp_add(t3, t4, p);

    a30 = sp_add(x0, a31, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x1 = x[ 2 * stride];
    sp_t x4 = x[ 9 * stride];
    sp_t x2 = x[16 * stride];
    sp_t x3 = x[23 * stride];
    sp_t x0 = x[30 * stride];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a37 = sp_add(t1, t2, p);
    a38 = sp_sub(t1, t2, p);
    a39 = t3;
    a40 = t4;
    a41 = sp_add(t3, t4, p);

    a36 = sp_add(x0, a37, p);
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a00;
    sp_t x1 = a06;
    sp_t x5 = a12;
    sp_t x6 = a18;
    sp_t x3 = a24;
    sp_t x2 = a30;
    sp_t x4 = a36;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p1 = sp_mul(p1, ntt_const[1], p, d);
    p2 = sp_mul(p2, ntt_const[2], p, d);
    p3 = sp_mul(p3, ntt_const[3], p, d);
    p4 = sp_mul(p4, ntt_const[4], p, d);
    p5 = sp_mul(p5, ntt_const[5], p, d);
    p6 = sp_mul(p6, ntt_const[6], p, d);
    p7 = sp_mul(p7, ntt_const[7], p, d);
    p8 = sp_mul(p8, ntt_const[8], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a00 = p0;
    a06 = t6;
    a12 = t4;
    a18 = t5;
    a24 = t2;
    a30 = t1;
    a36 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a01;
    sp_t x1 = a07;
    sp_t x5 = a13;
    sp_t x6 = a19;
    sp_t x3 = a25;
    sp_t x2 = a31;
    sp_t x4 = a37;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p0 = sp_mul(p0, ntt_const[9], p, d);
    p1 = sp_mul(p1, ntt_const[10], p, d);
    p2 = sp_mul(p2, ntt_const[11], p, d);
    p3 = sp_mul(p3, ntt_const[12], p, d);
    p4 = sp_mul(p4, ntt_const[13], p, d);
    p5 = sp_mul(p5, ntt_const[14], p, d);
    p6 = sp_mul(p6, ntt_const[15], p, d);
    p7 = sp_mul(p7, ntt_const[16], p, d);
    p8 = sp_mul(p8, ntt_const[17], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a01 = p0;
    a07 = t6;
    a13 = t4;
    a19 = t5;
    a25 = t2;
    a31 = t1;
    a37 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a02;
    sp_t x1 = a08;
    sp_t x5 = a14;
    sp_t x6 = a20;
    sp_t x3 = a26;
    sp_t x2 = a32;
    sp_t x4 = a38;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p0 = sp_mul(p0, ntt_const[18], p, d);
    p1 = sp_mul(p1, ntt_const[19], p, d);
    p2 = sp_mul(p2, ntt_const[20], p, d);
    p3 = sp_mul(p3, ntt_const[21], p, d);
    p4 = sp_mul(p4, ntt_const[22], p, d);
    p5 = sp_mul(p5, ntt_const[23], p, d);
    p6 = sp_mul(p6, ntt_const[24], p, d);
    p7 = sp_mul(p7, ntt_const[25], p, d);
    p8 = sp_mul(p8, ntt_const[26], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a02 = p0;
    a08 = t6;
    a14 = t4;
    a20 = t5;
    a26 = t2;
    a32 = t1;
    a38 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a03;
    sp_t x1 = a09;
    sp_t x5 = a15;
    sp_t x6 = a21;
    sp_t x3 = a27;
    sp_t x2 = a33;
    sp_t x4 = a39;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p0 = sp_mul(p0, ntt_const[27], p, d);
    p1 = sp_mul(p1, ntt_const[28], p, d);
    p2 = sp_mul(p2, ntt_const[29], p, d);
    p3 = sp_mul(p3, ntt_const[30], p, d);
    p4 = sp_mul(p4, ntt_const[31], p, d);
    p5 = sp_mul(p5, ntt_const[32], p, d);
    p6 = sp_mul(p6, ntt_const[33], p, d);
    p7 = sp_mul(p7, ntt_const[34], p, d);
    p8 = sp_mul(p8, ntt_const[35], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a03 = p0;
    a09 = t6;
    a15 = t4;
    a21 = t5;
    a27 = t2;
    a33 = t1;
    a39 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a04;
    sp_t x1 = a10;
    sp_t x5 = a16;
    sp_t x6 = a22;
    sp_t x3 = a28;
    sp_t x2 = a34;
    sp_t x4 = a40;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p0 = sp_mul(p0, ntt_const[36], p, d);
    p1 = sp_mul(p1, ntt_const[37], p, d);
    p2 = sp_mul(p2, ntt_const[38], p, d);
    p3 = sp_mul(p3, ntt_const[39], p, d);
    p4 = sp_mul(p4, ntt_const[40], p, d);
    p5 = sp_mul(p5, ntt_const[41], p, d);
    p6 = sp_mul(p6, ntt_const[42], p, d);
    p7 = sp_mul(p7, ntt_const[43], p, d);
    p8 = sp_mul(p8, ntt_const[44], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a04 = p0;
    a10 = t6;
    a16 = t4;
    a22 = t5;
    a28 = t2;
    a34 = t1;
    a40 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a05;
    sp_t x1 = a11;
    sp_t x5 = a17;
    sp_t x6 = a23;
    sp_t x3 = a29;
    sp_t x2 = a35;
    sp_t x4 = a41;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add(t5, t6, p);

    p0 = sp_mul(p0, ntt_const[45], p, d);
    p1 = sp_mul(p1, ntt_const[46], p, d);
    p2 = sp_mul(p2, ntt_const[47], p, d);
    p3 = sp_mul(p3, ntt_const[48], p, d);
    p4 = sp_mul(p4, ntt_const[49], p, d);
    p5 = sp_mul(p5, ntt_const[50], p, d);
    p6 = sp_mul(p6, ntt_const[51], p, d);
    p7 = sp_mul(p7, ntt_const[52], p, d);
    p8 = sp_mul(p8, ntt_const[53], p, d);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a05 = p0;
    a11 = t6;
    a17 = t4;
    a23 = t5;
    a29 = t2;
    a35 = t1;
    a41 = t3;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a00;
    sp_t p1 = a01;
    sp_t p2 = a02;
    sp_t p3 = a03;
    sp_t p4 = a04;
    sp_t p5 = a05;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 0 * stride] = p0;
    x[ 7 * stride] = p3;
    x[14 * stride] = p2;
    x[21 * stride] = p4;
    x[28 * stride] = p1;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a06;
    sp_t p1 = a07;
    sp_t p2 = a08;
    sp_t p3 = a09;
    sp_t p4 = a10;
    sp_t p5 = a11;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 1 * stride] = p4;
    x[ 8 * stride] = p1;
    x[15 * stride] = p0;
    x[22 * stride] = p3;
    x[29 * stride] = p2;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a12;
    sp_t p1 = a13;
    sp_t p2 = a14;
    sp_t p3 = a15;
    sp_t p4 = a16;
    sp_t p5 = a17;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 2 * stride] = p3;
    x[ 9 * stride] = p2;
    x[16 * stride] = p4;
    x[23 * stride] = p1;
    x[30 * stride] = p0;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a18;
    sp_t p1 = a19;
    sp_t p2 = a20;
    sp_t p3 = a21;
    sp_t p4 = a22;
    sp_t p5 = a23;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 3 * stride] = p1;
    x[10 * stride] = p0;
    x[17 * stride] = p3;
    x[24 * stride] = p2;
    x[31 * stride] = p4;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a24;
    sp_t p1 = a25;
    sp_t p2 = a26;
    sp_t p3 = a27;
    sp_t p4 = a28;
    sp_t p5 = a29;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 4 * stride] = p2;
    x[11 * stride] = p4;
    x[18 * stride] = p1;
    x[25 * stride] = p0;
    x[32 * stride] = p3;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a30;
    sp_t p1 = a31;
    sp_t p2 = a32;
    sp_t p3 = a33;
    sp_t p4 = a34;
    sp_t p5 = a35;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 5 * stride] = p0;
    x[12 * stride] = p3;
    x[19 * stride] = p2;
    x[26 * stride] = p4;
    x[33 * stride] = p1;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a36;
    sp_t p1 = a37;
    sp_t p2 = a38;
    sp_t p3 = a39;
    sp_t p4 = a40;
    sp_t p5 = a41;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[ 6 * stride] = p4;
    x[13 * stride] = p1;
    x[20 * stride] = p0;
    x[27 * stride] = p3;
    x[34 * stride] = p2;
  }
}

#ifdef HAVE_SSE2
static void
ntt35_run_simd(spv_t x, spv_size_t stride,
	  sp_t p, sp_t d, spv_t ntt_const)
{
  sp_simd_t a00, a01, a02, a03, a04, a05, a06, 
       a07, a08, a09, a10, a11, a12, a13, 
       a14, a15, a16, a17, a18, a19, a20, 
       a21, a22, a23, a24, a25, a26, a27, 
       a28, a29, a30, a31, a32, a33, a34, 
       a35, a36, a37, a38, a39, a40, a41;

  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x0 = sp_simd_gather(x +  0 * stride);
    sp_simd_t x1 = sp_simd_gather(x +  7 * stride);
    sp_simd_t x4 = sp_simd_gather(x + 14 * stride);
    sp_simd_t x2 = sp_simd_gather(x + 21 * stride);
    sp_simd_t x3 = sp_simd_gather(x + 28 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a01 = sp_simd_add(t1, t2, p);
    a02 = sp_simd_sub(t1, t2, p);
    a03 = t3;
    a04 = t4;
    a05 = sp_simd_add(t3, t4, p);

    a00 = sp_simd_add(x0, a01, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x0 = sp_simd_gather(x +  5 * stride);
    sp_simd_t x1 = sp_simd_gather(x + 12 * stride);
    sp_simd_t x4 = sp_simd_gather(x + 19 * stride);
    sp_simd_t x2 = sp_simd_gather(x + 26 * stride);
    sp_simd_t x3 = sp_simd_gather(x + 33 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a07 = sp_simd_add(t1, t2, p);
    a08 = sp_simd_sub(t1, t2, p);
    a09 = t3;
    a10 = t4;
    a11 = sp_simd_add(t3, t4, p);

    a06 = sp_simd_add(x0, a07, p);
  }
  {
    sp_simd_t t0, t1, t2, t3, t4, t5, t6, t7;

    sp_simd_t x3 = sp_simd_gather(x +  3 * stride);
    sp_simd_t x0 = sp_simd_gather(x + 10 * stride);
    sp_simd_t x1 = sp_simd_gather(x + 17 * stride);
    sp_simd_t x4 = sp_simd_gather(x + 24 * stride);
    sp_simd_t x2 = sp_simd_gather(x + 31 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a13 = sp_simd_add(t1, t2, p);
    a14 = sp_simd_sub(t1, t2, p);
    a15 = t3;
    a16 = t4;
    a17 = sp_simd_add(t3, t4, p);

    a12 = sp_simd_add(x0, a13, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x2 = sp_simd_gather(x +  1 * stride);
    sp_simd_t x3 = sp_simd_gather(x +  8 * stride);
    sp_simd_t x0 = sp_simd_gather(x + 15 * stride);
    sp_simd_t x1 = sp_simd_gather(x + 22 * stride);
    sp_simd_t x4 = sp_simd_gather(x + 29 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a19 = sp_simd_add(t1, t2, p);
    a20 = sp_simd_sub(t1, t2, p);
    a21 = t3;
    a22 = t4;
    a23 = sp_simd_add(t3, t4, p);

    a18 = sp_simd_add(x0, a19, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x2 = sp_simd_gather(x +  6 * stride);
    sp_simd_t x3 = sp_simd_gather(x + 13 * stride);
    sp_simd_t x0 = sp_simd_gather(x + 20 * stride);
    sp_simd_t x1 = sp_simd_gather(x + 27 * stride);
    sp_simd_t x4 = sp_simd_gather(x + 34 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a25 = sp_simd_add(t1, t2, p);
    a26 = sp_simd_sub(t1, t2, p);
    a27 = t3;
    a28 = t4;
    a29 = sp_simd_add(t3, t4, p);

    a24 = sp_simd_add(x0, a25, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x4 = sp_simd_gather(x +  4 * stride);
    sp_simd_t x2 = sp_simd_gather(x + 11 * stride);
    sp_simd_t x3 = sp_simd_gather(x + 18 * stride);
    sp_simd_t x0 = sp_simd_gather(x + 25 * stride);
    sp_simd_t x1 = sp_simd_gather(x + 32 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a31 = sp_simd_add(t1, t2, p);
    a32 = sp_simd_sub(t1, t2, p);
    a33 = t3;
    a34 = t4;
    a35 = sp_simd_add(t3, t4, p);

    a30 = sp_simd_add(x0, a31, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x1 = sp_simd_gather(x +  2 * stride);
    sp_simd_t x4 = sp_simd_gather(x +  9 * stride);
    sp_simd_t x2 = sp_simd_gather(x + 16 * stride);
    sp_simd_t x3 = sp_simd_gather(x + 23 * stride);
    sp_simd_t x0 = sp_simd_gather(x + 30 * stride);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a37 = sp_simd_add(t1, t2, p);
    a38 = sp_simd_sub(t1, t2, p);
    a39 = t3;
    a40 = t4;
    a41 = sp_simd_add(t3, t4, p);

    a36 = sp_simd_add(x0, a37, p);
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a00;
    sp_simd_t x1 = a06;
    sp_simd_t x5 = a12;
    sp_simd_t x6 = a18;
    sp_simd_t x3 = a24;
    sp_simd_t x2 = a30;
    sp_simd_t x4 = a36;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p1 = sp_simd_mul(p1, ntt_const[1], p, d);
    p2 = sp_simd_mul(p2, ntt_const[2], p, d);
    p3 = sp_simd_mul(p3, ntt_const[3], p, d);
    p4 = sp_simd_mul(p4, ntt_const[4], p, d);
    p5 = sp_simd_mul(p5, ntt_const[5], p, d);
    p6 = sp_simd_mul(p6, ntt_const[6], p, d);
    p7 = sp_simd_mul(p7, ntt_const[7], p, d);
    p8 = sp_simd_mul(p8, ntt_const[8], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a00 = p0;
    a06 = t6;
    a12 = t4;
    a18 = t5;
    a24 = t2;
    a30 = t1;
    a36 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a01;
    sp_simd_t x1 = a07;
    sp_simd_t x5 = a13;
    sp_simd_t x6 = a19;
    sp_simd_t x3 = a25;
    sp_simd_t x2 = a31;
    sp_simd_t x4 = a37;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p0 = sp_simd_mul(p0, ntt_const[9], p, d);
    p1 = sp_simd_mul(p1, ntt_const[10], p, d);
    p2 = sp_simd_mul(p2, ntt_const[11], p, d);
    p3 = sp_simd_mul(p3, ntt_const[12], p, d);
    p4 = sp_simd_mul(p4, ntt_const[13], p, d);
    p5 = sp_simd_mul(p5, ntt_const[14], p, d);
    p6 = sp_simd_mul(p6, ntt_const[15], p, d);
    p7 = sp_simd_mul(p7, ntt_const[16], p, d);
    p8 = sp_simd_mul(p8, ntt_const[17], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a01 = p0;
    a07 = t6;
    a13 = t4;
    a19 = t5;
    a25 = t2;
    a31 = t1;
    a37 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a02;
    sp_simd_t x1 = a08;
    sp_simd_t x5 = a14;
    sp_simd_t x6 = a20;
    sp_simd_t x3 = a26;
    sp_simd_t x2 = a32;
    sp_simd_t x4 = a38;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p0 = sp_simd_mul(p0, ntt_const[18], p, d);
    p1 = sp_simd_mul(p1, ntt_const[19], p, d);
    p2 = sp_simd_mul(p2, ntt_const[20], p, d);
    p3 = sp_simd_mul(p3, ntt_const[21], p, d);
    p4 = sp_simd_mul(p4, ntt_const[22], p, d);
    p5 = sp_simd_mul(p5, ntt_const[23], p, d);
    p6 = sp_simd_mul(p6, ntt_const[24], p, d);
    p7 = sp_simd_mul(p7, ntt_const[25], p, d);
    p8 = sp_simd_mul(p8, ntt_const[26], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a02 = p0;
    a08 = t6;
    a14 = t4;
    a20 = t5;
    a26 = t2;
    a32 = t1;
    a38 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a03;
    sp_simd_t x1 = a09;
    sp_simd_t x5 = a15;
    sp_simd_t x6 = a21;
    sp_simd_t x3 = a27;
    sp_simd_t x2 = a33;
    sp_simd_t x4 = a39;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p0 = sp_simd_mul(p0, ntt_const[27], p, d);
    p1 = sp_simd_mul(p1, ntt_const[28], p, d);
    p2 = sp_simd_mul(p2, ntt_const[29], p, d);
    p3 = sp_simd_mul(p3, ntt_const[30], p, d);
    p4 = sp_simd_mul(p4, ntt_const[31], p, d);
    p5 = sp_simd_mul(p5, ntt_const[32], p, d);
    p6 = sp_simd_mul(p6, ntt_const[33], p, d);
    p7 = sp_simd_mul(p7, ntt_const[34], p, d);
    p8 = sp_simd_mul(p8, ntt_const[35], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a03 = p0;
    a09 = t6;
    a15 = t4;
    a21 = t5;
    a27 = t2;
    a33 = t1;
    a39 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a04;
    sp_simd_t x1 = a10;
    sp_simd_t x5 = a16;
    sp_simd_t x6 = a22;
    sp_simd_t x3 = a28;
    sp_simd_t x2 = a34;
    sp_simd_t x4 = a40;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p0 = sp_simd_mul(p0, ntt_const[36], p, d);
    p1 = sp_simd_mul(p1, ntt_const[37], p, d);
    p2 = sp_simd_mul(p2, ntt_const[38], p, d);
    p3 = sp_simd_mul(p3, ntt_const[39], p, d);
    p4 = sp_simd_mul(p4, ntt_const[40], p, d);
    p5 = sp_simd_mul(p5, ntt_const[41], p, d);
    p6 = sp_simd_mul(p6, ntt_const[42], p, d);
    p7 = sp_simd_mul(p7, ntt_const[43], p, d);
    p8 = sp_simd_mul(p8, ntt_const[44], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a04 = p0;
    a10 = t6;
    a16 = t4;
    a22 = t5;
    a28 = t2;
    a34 = t1;
    a40 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a05;
    sp_simd_t x1 = a11;
    sp_simd_t x5 = a17;
    sp_simd_t x6 = a23;
    sp_simd_t x3 = a29;
    sp_simd_t x2 = a35;
    sp_simd_t x4 = a41;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add(t5, t6, p);

    p0 = sp_simd_mul(p0, ntt_const[45], p, d);
    p1 = sp_simd_mul(p1, ntt_const[46], p, d);
    p2 = sp_simd_mul(p2, ntt_const[47], p, d);
    p3 = sp_simd_mul(p3, ntt_const[48], p, d);
    p4 = sp_simd_mul(p4, ntt_const[49], p, d);
    p5 = sp_simd_mul(p5, ntt_const[50], p, d);
    p6 = sp_simd_mul(p6, ntt_const[51], p, d);
    p7 = sp_simd_mul(p7, ntt_const[52], p, d);
    p8 = sp_simd_mul(p8, ntt_const[53], p, d);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a05 = p0;
    a11 = t6;
    a17 = t4;
    a23 = t5;
    a29 = t2;
    a35 = t1;
    a41 = t3;
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a00;
    sp_simd_t p1 = a01;
    sp_simd_t p2 = a02;
    sp_simd_t p3 = a03;
    sp_simd_t p4 = a04;
    sp_simd_t p5 = a05;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p0, x +  0 * stride);
    sp_simd_scatter(p3, x +  7 * stride);
    sp_simd_scatter(p2, x + 14 * stride);
    sp_simd_scatter(p4, x + 21 * stride);
    sp_simd_scatter(p1, x + 28 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a06;
    sp_simd_t p1 = a07;
    sp_simd_t p2 = a08;
    sp_simd_t p3 = a09;
    sp_simd_t p4 = a10;
    sp_simd_t p5 = a11;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p4, x +  1 * stride);
    sp_simd_scatter(p1, x +  8 * stride);
    sp_simd_scatter(p0, x + 15 * stride);
    sp_simd_scatter(p3, x + 22 * stride);
    sp_simd_scatter(p2, x + 29 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a12;
    sp_simd_t p1 = a13;
    sp_simd_t p2 = a14;
    sp_simd_t p3 = a15;
    sp_simd_t p4 = a16;
    sp_simd_t p5 = a17;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p3, x +  2 * stride);
    sp_simd_scatter(p2, x +  9 * stride);
    sp_simd_scatter(p4, x + 16 * stride);
    sp_simd_scatter(p1, x + 23 * stride);
    sp_simd_scatter(p0, x + 30 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a18;
    sp_simd_t p1 = a19;
    sp_simd_t p2 = a20;
    sp_simd_t p3 = a21;
    sp_simd_t p4 = a22;
    sp_simd_t p5 = a23;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p1, x +  3 * stride);
    sp_simd_scatter(p0, x + 10 * stride);
    sp_simd_scatter(p3, x + 17 * stride);
    sp_simd_scatter(p2, x + 24 * stride);
    sp_simd_scatter(p4, x + 31 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a24;
    sp_simd_t p1 = a25;
    sp_simd_t p2 = a26;
    sp_simd_t p3 = a27;
    sp_simd_t p4 = a28;
    sp_simd_t p5 = a29;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p2, x +  4 * stride);
    sp_simd_scatter(p4, x + 11 * stride);
    sp_simd_scatter(p1, x + 18 * stride);
    sp_simd_scatter(p0, x + 25 * stride);
    sp_simd_scatter(p3, x + 32 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a30;
    sp_simd_t p1 = a31;
    sp_simd_t p2 = a32;
    sp_simd_t p3 = a33;
    sp_simd_t p4 = a34;
    sp_simd_t p5 = a35;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p0, x +  5 * stride);
    sp_simd_scatter(p3, x + 12 * stride);
    sp_simd_scatter(p2, x + 19 * stride);
    sp_simd_scatter(p4, x + 26 * stride);
    sp_simd_scatter(p1, x + 33 * stride);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a36;
    sp_simd_t p1 = a37;
    sp_simd_t p2 = a38;
    sp_simd_t p3 = a39;
    sp_simd_t p4 = a40;
    sp_simd_t p5 = a41;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_scatter(p4, x +  6 * stride);
    sp_simd_scatter(p1, x + 13 * stride);
    sp_simd_scatter(p0, x + 20 * stride);
    sp_simd_scatter(p3, x + 27 * stride);
    sp_simd_scatter(p2, x + 34 * stride);
  }
}
#endif

static void
ntt35_twiddle_run(spv_t x, spv_size_t stride,
	  spv_size_t num_transforms,
	  sp_t p, sp_t d, spv_t ntt_const)
{
  spv_size_t i = 0;

#ifdef HAVE_SSE2
  spv_size_t num_simd = SP_SIMD_VSIZE * (num_transforms / SP_SIMD_VSIZE);

  for (i = 0; i < num_simd; i += SP_SIMD_VSIZE)
      ntt35_run_simd(x + i, stride, p, d, ntt_const);
#endif

  for (; i < num_transforms; i++)
    ntt35_run(x + i, stride, p, d, ntt_const);
}


static void
ntt35_pfa_run_core(spv_t x, spv_size_t start,
	  spv_size_t inc, spv_size_t n,
	  sp_t p, spv_t ntt_const)
{
  spv_size_t j00, j01, j02, j03, j04, j05, j06, j07,
	     j08, j09, j10, j11, j12, j13, j14, j15,
	     j16, j17, j18, j19, j20, j21, j22, j23,
	     j24, j25, j26, j27, j28, j29, j30, j31,
	     j32, j33, j34;

  sp_t a00, a01, a02, a03, a04, a05, a06, 
       a07, a08, a09, a10, a11, a12, a13, 
       a14, a15, a16, a17, a18, a19, a20, 
       a21, a22, a23, a24, a25, a26, a27, 
       a28, a29, a30, a31, a32, a33, a34, 
       a35, a36, a37, a38, a39, a40, a41;

  #ifdef HAVE_PARTIAL_MOD
  p *= 2;
  #endif

  j00 = start;
  j01 = sp_array_inc(j00, inc, n);
  j02 = sp_array_inc(j00, 2 * inc, n);
  j03 = sp_array_inc(j00, 3 * inc, n);
  j04 = sp_array_inc(j00, 4 * inc, n);
  j05 = sp_array_inc(j00, 5 * inc, n);
  j06 = sp_array_inc(j00, 6 * inc, n);
  j07 = sp_array_inc(j00, 7 * inc, n);
  j08 = sp_array_inc(j00, 8 * inc, n);
  j09 = sp_array_inc(j00, 9 * inc, n);
  j10 = sp_array_inc(j00, 10 * inc, n);
  j11 = sp_array_inc(j00, 11 * inc, n);
  j12 = sp_array_inc(j00, 12 * inc, n);
  j13 = sp_array_inc(j00, 13 * inc, n);
  j14 = sp_array_inc(j00, 14 * inc, n);
  j15 = sp_array_inc(j00, 15 * inc, n);
  j16 = sp_array_inc(j00, 16 * inc, n);
  j17 = sp_array_inc(j00, 17 * inc, n);
  j18 = sp_array_inc(j00, 18 * inc, n);
  j19 = sp_array_inc(j00, 19 * inc, n);
  j20 = sp_array_inc(j00, 20 * inc, n);
  j21 = sp_array_inc(j00, 21 * inc, n);
  j22 = sp_array_inc(j00, 22 * inc, n);
  j23 = sp_array_inc(j00, 23 * inc, n);
  j24 = sp_array_inc(j00, 24 * inc, n);
  j25 = sp_array_inc(j00, 25 * inc, n);
  j26 = sp_array_inc(j00, 26 * inc, n);
  j27 = sp_array_inc(j00, 27 * inc, n);
  j28 = sp_array_inc(j00, 28 * inc, n);
  j29 = sp_array_inc(j00, 29 * inc, n);
  j30 = sp_array_inc(j00, 30 * inc, n);
  j31 = sp_array_inc(j00, 31 * inc, n);
  j32 = sp_array_inc(j00, 32 * inc, n);
  j33 = sp_array_inc(j00, 33 * inc, n);
  j34 = sp_array_inc(j00, 34 * inc, n);

  {
    sp_t t1, t2, t3, t4;

    sp_t x0 = x[j00];
    sp_t x1 = x[j07];
    sp_t x4 = x[j14];
    sp_t x2 = x[j21];
    sp_t x3 = x[j28];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a01 = sp_add(t1, t2, p);
    a02 = sp_sub(t1, t2, p);
    a03 = t3;
    a04 = t4;
    a05 = sp_add(t3, t4, p);

    a00 = sp_add(x0, a01, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x0 = x[j05];
    sp_t x1 = x[j12];
    sp_t x4 = x[j19];
    sp_t x2 = x[j26];
    sp_t x3 = x[j33];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a07 = sp_add(t1, t2, p);
    a08 = sp_sub(t1, t2, p);
    a09 = t3;
    a10 = t4;
    a11 = sp_add(t3, t4, p);

    a06 = sp_add(x0, a07, p);
  }
  {
    sp_t t0, t1, t2, t3, t4, t5, t6, t7;

    sp_t x3 = x[j03];
    sp_t x0 = x[j10];
    sp_t x1 = x[j17];
    sp_t x4 = x[j24];
    sp_t x2 = x[j31];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a13 = sp_add(t1, t2, p);
    a14 = sp_sub(t1, t2, p);
    a15 = t3;
    a16 = t4;
    a17 = sp_add(t3, t4, p);

    a12 = sp_add(x0, a13, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x2 = x[j01];
    sp_t x3 = x[j08];
    sp_t x0 = x[j15];
    sp_t x1 = x[j22];
    sp_t x4 = x[j29];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a19 = sp_add(t1, t2, p);
    a20 = sp_sub(t1, t2, p);
    a21 = t3;
    a22 = t4;
    a23 = sp_add(t3, t4, p);

    a18 = sp_add(x0, a19, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x2 = x[j06];
    sp_t x3 = x[j13];
    sp_t x0 = x[j20];
    sp_t x1 = x[j27];
    sp_t x4 = x[j34];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a25 = sp_add(t1, t2, p);
    a26 = sp_sub(t1, t2, p);
    a27 = t3;
    a28 = t4;
    a29 = sp_add(t3, t4, p);

    a24 = sp_add(x0, a25, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x4 = x[j04];
    sp_t x2 = x[j11];
    sp_t x3 = x[j18];
    sp_t x0 = x[j25];
    sp_t x1 = x[j32];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a31 = sp_add(t1, t2, p);
    a32 = sp_sub(t1, t2, p);
    a33 = t3;
    a34 = t4;
    a35 = sp_add(t3, t4, p);

    a30 = sp_add(x0, a31, p);
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t x1 = x[j02];
    sp_t x4 = x[j09];
    sp_t x2 = x[j16];
    sp_t x3 = x[j23];
    sp_t x0 = x[j30];

    t1 = sp_add(x1, x3, p);
    t3 = sp_sub(x1, x3, p);
    t2 = sp_add(x2, x4, p);
    t4 = sp_sub(x2, x4, p);

    a37 = sp_add(t1, t2, p);
    a38 = sp_sub(t1, t2, p);
    a39 = t3;
    a40 = t4;
    a41 = sp_add(t3, t4, p);

    a36 = sp_add(x0, a37, p);
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a00;
    sp_t x1 = a06;
    sp_t x5 = a12;
    sp_t x6 = a18;
    sp_t x3 = a24;
    sp_t x2 = a30;
    sp_t x4 = a36;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p1 = sp_ntt_mul(p1, ntt_const[1], ntt_const[NC+1], p);
    p2 = sp_ntt_mul(p2, ntt_const[2], ntt_const[NC+2], p);
    p3 = sp_ntt_mul(p3, ntt_const[3], ntt_const[NC+3], p);
    p4 = sp_ntt_mul(p4, ntt_const[4], ntt_const[NC+4], p);
    p5 = sp_ntt_mul(p5, ntt_const[5], ntt_const[NC+5], p);
    p6 = sp_ntt_mul(p6, ntt_const[6], ntt_const[NC+6], p);
    p7 = sp_ntt_mul(p7, ntt_const[7], ntt_const[NC+7], p);
    p8 = sp_ntt_mul(p8, ntt_const[8], ntt_const[NC+8], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a00 = p0;
    a06 = t6;
    a12 = t4;
    a18 = t5;
    a24 = t2;
    a30 = t1;
    a36 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a01;
    sp_t x1 = a07;
    sp_t x5 = a13;
    sp_t x6 = a19;
    sp_t x3 = a25;
    sp_t x2 = a31;
    sp_t x4 = a37;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p0 = sp_ntt_mul(p0, ntt_const[9], ntt_const[NC+9], p);
    p1 = sp_ntt_mul(p1, ntt_const[10], ntt_const[NC+10], p);
    p2 = sp_ntt_mul(p2, ntt_const[11], ntt_const[NC+11], p);
    p3 = sp_ntt_mul(p3, ntt_const[12], ntt_const[NC+12], p);
    p4 = sp_ntt_mul(p4, ntt_const[13], ntt_const[NC+13], p);
    p5 = sp_ntt_mul(p5, ntt_const[14], ntt_const[NC+14], p);
    p6 = sp_ntt_mul(p6, ntt_const[15], ntt_const[NC+15], p);
    p7 = sp_ntt_mul(p7, ntt_const[16], ntt_const[NC+16], p);
    p8 = sp_ntt_mul(p8, ntt_const[17], ntt_const[NC+17], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a01 = p0;
    a07 = t6;
    a13 = t4;
    a19 = t5;
    a25 = t2;
    a31 = t1;
    a37 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a02;
    sp_t x1 = a08;
    sp_t x5 = a14;
    sp_t x6 = a20;
    sp_t x3 = a26;
    sp_t x2 = a32;
    sp_t x4 = a38;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p0 = sp_ntt_mul(p0, ntt_const[18], ntt_const[NC+18], p);
    p1 = sp_ntt_mul(p1, ntt_const[19], ntt_const[NC+19], p);
    p2 = sp_ntt_mul(p2, ntt_const[20], ntt_const[NC+20], p);
    p3 = sp_ntt_mul(p3, ntt_const[21], ntt_const[NC+21], p);
    p4 = sp_ntt_mul(p4, ntt_const[22], ntt_const[NC+22], p);
    p5 = sp_ntt_mul(p5, ntt_const[23], ntt_const[NC+23], p);
    p6 = sp_ntt_mul(p6, ntt_const[24], ntt_const[NC+24], p);
    p7 = sp_ntt_mul(p7, ntt_const[25], ntt_const[NC+25], p);
    p8 = sp_ntt_mul(p8, ntt_const[26], ntt_const[NC+26], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a02 = p0;
    a08 = t6;
    a14 = t4;
    a20 = t5;
    a26 = t2;
    a32 = t1;
    a38 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a03;
    sp_t x1 = a09;
    sp_t x5 = a15;
    sp_t x6 = a21;
    sp_t x3 = a27;
    sp_t x2 = a33;
    sp_t x4 = a39;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p0 = sp_ntt_mul(p0, ntt_const[27], ntt_const[NC+27], p);
    p1 = sp_ntt_mul(p1, ntt_const[28], ntt_const[NC+28], p);
    p2 = sp_ntt_mul(p2, ntt_const[29], ntt_const[NC+29], p);
    p3 = sp_ntt_mul(p3, ntt_const[30], ntt_const[NC+30], p);
    p4 = sp_ntt_mul(p4, ntt_const[31], ntt_const[NC+31], p);
    p5 = sp_ntt_mul(p5, ntt_const[32], ntt_const[NC+32], p);
    p6 = sp_ntt_mul(p6, ntt_const[33], ntt_const[NC+33], p);
    p7 = sp_ntt_mul(p7, ntt_const[34], ntt_const[NC+34], p);
    p8 = sp_ntt_mul(p8, ntt_const[35], ntt_const[NC+35], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a03 = p0;
    a09 = t6;
    a15 = t4;
    a21 = t5;
    a27 = t2;
    a33 = t1;
    a39 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a04;
    sp_t x1 = a10;
    sp_t x5 = a16;
    sp_t x6 = a22;
    sp_t x3 = a28;
    sp_t x2 = a34;
    sp_t x4 = a40;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p0 = sp_ntt_mul(p0, ntt_const[36], ntt_const[NC+36], p);
    p1 = sp_ntt_mul(p1, ntt_const[37], ntt_const[NC+37], p);
    p2 = sp_ntt_mul(p2, ntt_const[38], ntt_const[NC+38], p);
    p3 = sp_ntt_mul(p3, ntt_const[39], ntt_const[NC+39], p);
    p4 = sp_ntt_mul(p4, ntt_const[40], ntt_const[NC+40], p);
    p5 = sp_ntt_mul(p5, ntt_const[41], ntt_const[NC+41], p);
    p6 = sp_ntt_mul(p6, ntt_const[42], ntt_const[NC+42], p);
    p7 = sp_ntt_mul(p7, ntt_const[43], ntt_const[NC+43], p);
    p8 = sp_ntt_mul(p8, ntt_const[44], ntt_const[NC+44], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a04 = p0;
    a10 = t6;
    a16 = t4;
    a22 = t5;
    a28 = t2;
    a34 = t1;
    a40 = t3;
  }
  {
    sp_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_t x0 = a05;
    sp_t x1 = a11;
    sp_t x5 = a17;
    sp_t x6 = a23;
    sp_t x3 = a29;
    sp_t x2 = a35;
    sp_t x4 = a41;

    p1 = sp_add(x1, x4, p);
    p2 = sp_add(x2, x5, p);
    p3 = sp_add(x3, x6, p);
    p4 = sp_sub(x1, x4, p);
    p5 = sp_sub(x2, x5, p);
    p6 = sp_sub(x3, x6, p);

    t1 = sp_add(p1, p2, p);
    t1 = sp_add(t1, p3, p);
    t2 = sp_sub(p1, p3, p);
    t3 = sp_sub(p2, p3, p);
    t4 = sp_sub(p4, p5, p);
    t4 = sp_add_partial(t4, p6, p);
    t5 = sp_sub(p4, p6, p);
    t6 = sp_add(p5, p6, p);

    p0 = sp_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_add_partial(t5, t6, p);

    p0 = sp_ntt_mul(p0, ntt_const[45], ntt_const[NC+45], p);
    p1 = sp_ntt_mul(p1, ntt_const[46], ntt_const[NC+46], p);
    p2 = sp_ntt_mul(p2, ntt_const[47], ntt_const[NC+47], p);
    p3 = sp_ntt_mul(p3, ntt_const[48], ntt_const[NC+48], p);
    p4 = sp_ntt_mul(p4, ntt_const[49], ntt_const[NC+49], p);
    p5 = sp_ntt_mul(p5, ntt_const[50], ntt_const[NC+50], p);
    p6 = sp_ntt_mul(p6, ntt_const[51], ntt_const[NC+51], p);
    p7 = sp_ntt_mul(p7, ntt_const[52], ntt_const[NC+52], p);
    p8 = sp_ntt_mul(p8, ntt_const[53], ntt_const[NC+53], p);

    t1 = sp_add(p0, p1, p);
    t2 = sp_add(p2, p4, p);
    t3 = sp_add(p3, p4, p);
    t4 = p5;
    t5 = sp_add(p6, p8, p);
    t6 = sp_add(p7, p8, p);

    p1 = sp_add(t1, t2, p);
    p2 = sp_add(t1, t3, p);
    p3 = sp_sub(t1, t2, p);
    p3 = sp_sub(p3, t3, p);
    p4 = sp_add(t4, t5, p);
    p5 = sp_sub(t6, t4, p);
    p6 = sp_sub(t4, t5, p);
    p6 = sp_add(p6, t6, p);

    t1 = sp_add(p1, p4, p);
    t2 = sp_add(p2, p5, p);
    t3 = sp_add(p3, p6, p);
    t4 = sp_sub(p1, p4, p);
    t5 = sp_sub(p2, p5, p);
    t6 = sp_sub(p3, p6, p);

    a05 = p0;
    a11 = t6;
    a17 = t4;
    a23 = t5;
    a29 = t2;
    a35 = t1;
    a41 = t3;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a00;
    sp_t p1 = a01;
    sp_t p2 = a02;
    sp_t p3 = a03;
    sp_t p4 = a04;
    sp_t p5 = a05;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j00] = p0;
    x[j07] = p3;
    x[j14] = p2;
    x[j21] = p4;
    x[j28] = p1;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a06;
    sp_t p1 = a07;
    sp_t p2 = a08;
    sp_t p3 = a09;
    sp_t p4 = a10;
    sp_t p5 = a11;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j01] = p4;
    x[j08] = p1;
    x[j15] = p0;
    x[j22] = p3;
    x[j29] = p2;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a12;
    sp_t p1 = a13;
    sp_t p2 = a14;
    sp_t p3 = a15;
    sp_t p4 = a16;
    sp_t p5 = a17;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j02] = p3;
    x[j09] = p2;
    x[j16] = p4;
    x[j23] = p1;
    x[j30] = p0;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a18;
    sp_t p1 = a19;
    sp_t p2 = a20;
    sp_t p3 = a21;
    sp_t p4 = a22;
    sp_t p5 = a23;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j03] = p1;
    x[j10] = p0;
    x[j17] = p3;
    x[j24] = p2;
    x[j31] = p4;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a24;
    sp_t p1 = a25;
    sp_t p2 = a26;
    sp_t p3 = a27;
    sp_t p4 = a28;
    sp_t p5 = a29;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j04] = p2;
    x[j11] = p4;
    x[j18] = p1;
    x[j25] = p0;
    x[j32] = p3;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a30;
    sp_t p1 = a31;
    sp_t p2 = a32;
    sp_t p3 = a33;
    sp_t p4 = a34;
    sp_t p5 = a35;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j05] = p0;
    x[j12] = p3;
    x[j19] = p2;
    x[j26] = p4;
    x[j33] = p1;
  }
  {
    sp_t t1, t2, t3, t4;

    sp_t p0 = a36;
    sp_t p1 = a37;
    sp_t p2 = a38;
    sp_t p3 = a39;
    sp_t p4 = a40;
    sp_t p5 = a41;

    p1 = sp_add(p0, p1, p);

    t1 = sp_add(p1, p2, p);
    t2 = sp_sub(p1, p2, p);
    t3 = sp_add(p3, p5, p);
    t4 = sp_add(p4, p5, p);

    p1 = sp_add(t1, t3, p);
    p2 = sp_add(t2, t4, p);
    p3 = sp_sub(t1, t3, p);
    p4 = sp_sub(t2, t4, p);

    x[j06] = p4;
    x[j13] = p1;
    x[j20] = p0;
    x[j27] = p3;
    x[j34] = p2;
  }
}

#ifdef HAVE_SSE2
static void
ntt35_pfa_run_core_simd(spv_t x, spv_size_t start,
	  spv_size_t inc, spv_size_t inc2, spv_size_t n,
	  sp_t p, spv_t ntt_const)
{
  spv_size_t j00, j01, j02, j03, j04, j05, j06, j07,
	     j08, j09, j10, j11, j12, j13, j14, j15,
	     j16, j17, j18, j19, j20, j21, j22, j23,
	     j24, j25, j26, j27, j28, j29, j30, j31,
	     j32, j33, j34;

  sp_simd_t a00, a01, a02, a03, a04, a05, a06, 
            a07, a08, a09, a10, a11, a12, a13, 
            a14, a15, a16, a17, a18, a19, a20, 
            a21, a22, a23, a24, a25, a26, a27, 
            a28, a29, a30, a31, a32, a33, a34, 
            a35, a36, a37, a38, a39, a40, a41;

  #ifdef HAVE_PARTIAL_MOD
  p *= 2;
  #endif

  j00 = start;
  j01 = sp_array_inc(j00, inc, n);
  j02 = sp_array_inc(j00, 2 * inc, n);
  j03 = sp_array_inc(j00, 3 * inc, n);
  j04 = sp_array_inc(j00, 4 * inc, n);
  j05 = sp_array_inc(j00, 5 * inc, n);
  j06 = sp_array_inc(j00, 6 * inc, n);
  j07 = sp_array_inc(j00, 7 * inc, n);
  j08 = sp_array_inc(j00, 8 * inc, n);
  j09 = sp_array_inc(j00, 9 * inc, n);
  j10 = sp_array_inc(j00, 10 * inc, n);
  j11 = sp_array_inc(j00, 11 * inc, n);
  j12 = sp_array_inc(j00, 12 * inc, n);
  j13 = sp_array_inc(j00, 13 * inc, n);
  j14 = sp_array_inc(j00, 14 * inc, n);
  j15 = sp_array_inc(j00, 15 * inc, n);
  j16 = sp_array_inc(j00, 16 * inc, n);
  j17 = sp_array_inc(j00, 17 * inc, n);
  j18 = sp_array_inc(j00, 18 * inc, n);
  j19 = sp_array_inc(j00, 19 * inc, n);
  j20 = sp_array_inc(j00, 20 * inc, n);
  j21 = sp_array_inc(j00, 21 * inc, n);
  j22 = sp_array_inc(j00, 22 * inc, n);
  j23 = sp_array_inc(j00, 23 * inc, n);
  j24 = sp_array_inc(j00, 24 * inc, n);
  j25 = sp_array_inc(j00, 25 * inc, n);
  j26 = sp_array_inc(j00, 26 * inc, n);
  j27 = sp_array_inc(j00, 27 * inc, n);
  j28 = sp_array_inc(j00, 28 * inc, n);
  j29 = sp_array_inc(j00, 29 * inc, n);
  j30 = sp_array_inc(j00, 30 * inc, n);
  j31 = sp_array_inc(j00, 31 * inc, n);
  j32 = sp_array_inc(j00, 32 * inc, n);
  j33 = sp_array_inc(j00, 33 * inc, n);
  j34 = sp_array_inc(j00, 34 * inc, n);

  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x0 = sp_simd_pfa_gather(x, j00, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j07, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j14, inc2, n);
    sp_simd_t x2 = sp_simd_pfa_gather(x, j21, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j28, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a01 = sp_simd_add(t1, t2, p);
    a02 = sp_simd_sub(t1, t2, p);
    a03 = t3;
    a04 = t4;
    a05 = sp_simd_add(t3, t4, p);

    a00 = sp_simd_add(x0, a01, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x0 = sp_simd_pfa_gather(x, j05, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j12, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j19, inc2, n);
    sp_simd_t x2 = sp_simd_pfa_gather(x, j26, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j33, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a07 = sp_simd_add(t1, t2, p);
    a08 = sp_simd_sub(t1, t2, p);
    a09 = t3;
    a10 = t4;
    a11 = sp_simd_add(t3, t4, p);

    a06 = sp_simd_add(x0, a07, p);
  }
  {
    sp_simd_t t0, t1, t2, t3, t4, t5, t6, t7;

    sp_simd_t x3 = sp_simd_pfa_gather(x, j03, inc2, n);
    sp_simd_t x0 = sp_simd_pfa_gather(x, j10, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j17, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j24, inc2, n);
    sp_simd_t x2 = sp_simd_pfa_gather(x, j31, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a13 = sp_simd_add(t1, t2, p);
    a14 = sp_simd_sub(t1, t2, p);
    a15 = t3;
    a16 = t4;
    a17 = sp_simd_add(t3, t4, p);

    a12 = sp_simd_add(x0, a13, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x2 = sp_simd_pfa_gather(x, j01, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j08, inc2, n);
    sp_simd_t x0 = sp_simd_pfa_gather(x, j15, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j22, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j29, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a19 = sp_simd_add(t1, t2, p);
    a20 = sp_simd_sub(t1, t2, p);
    a21 = t3;
    a22 = t4;
    a23 = sp_simd_add(t3, t4, p);

    a18 = sp_simd_add(x0, a19, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x2 = sp_simd_pfa_gather(x, j06, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j13, inc2, n);
    sp_simd_t x0 = sp_simd_pfa_gather(x, j20, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j27, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j34, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a25 = sp_simd_add(t1, t2, p);
    a26 = sp_simd_sub(t1, t2, p);
    a27 = t3;
    a28 = t4;
    a29 = sp_simd_add(t3, t4, p);

    a24 = sp_simd_add(x0, a25, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x4 = sp_simd_pfa_gather(x, j04, inc2, n);
    sp_simd_t x2 = sp_simd_pfa_gather(x, j11, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j18, inc2, n);
    sp_simd_t x0 = sp_simd_pfa_gather(x, j25, inc2, n);
    sp_simd_t x1 = sp_simd_pfa_gather(x, j32, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a31 = sp_simd_add(t1, t2, p);
    a32 = sp_simd_sub(t1, t2, p);
    a33 = t3;
    a34 = t4;
    a35 = sp_simd_add(t3, t4, p);

    a30 = sp_simd_add(x0, a31, p);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t x1 = sp_simd_pfa_gather(x, j02, inc2, n);
    sp_simd_t x4 = sp_simd_pfa_gather(x, j09, inc2, n);
    sp_simd_t x2 = sp_simd_pfa_gather(x, j16, inc2, n);
    sp_simd_t x3 = sp_simd_pfa_gather(x, j23, inc2, n);
    sp_simd_t x0 = sp_simd_pfa_gather(x, j30, inc2, n);

    t1 = sp_simd_add(x1, x3, p);
    t3 = sp_simd_sub(x1, x3, p);
    t2 = sp_simd_add(x2, x4, p);
    t4 = sp_simd_sub(x2, x4, p);

    a37 = sp_simd_add(t1, t2, p);
    a38 = sp_simd_sub(t1, t2, p);
    a39 = t3;
    a40 = t4;
    a41 = sp_simd_add(t3, t4, p);

    a36 = sp_simd_add(x0, a37, p);
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a00;
    sp_simd_t x1 = a06;
    sp_simd_t x5 = a12;
    sp_simd_t x6 = a18;
    sp_simd_t x3 = a24;
    sp_simd_t x2 = a30;
    sp_simd_t x4 = a36;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p1 = sp_simd_ntt_mul(p1, ntt_const[1], ntt_const[NC+1], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[2], ntt_const[NC+2], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[3], ntt_const[NC+3], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[4], ntt_const[NC+4], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[5], ntt_const[NC+5], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[6], ntt_const[NC+6], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[7], ntt_const[NC+7], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[8], ntt_const[NC+8], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a00 = p0;
    a06 = t6;
    a12 = t4;
    a18 = t5;
    a24 = t2;
    a30 = t1;
    a36 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a01;
    sp_simd_t x1 = a07;
    sp_simd_t x5 = a13;
    sp_simd_t x6 = a19;
    sp_simd_t x3 = a25;
    sp_simd_t x2 = a31;
    sp_simd_t x4 = a37;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p0 = sp_simd_ntt_mul(p0, ntt_const[9], ntt_const[NC+9], p);
    p1 = sp_simd_ntt_mul(p1, ntt_const[10], ntt_const[NC+10], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[11], ntt_const[NC+11], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[12], ntt_const[NC+12], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[13], ntt_const[NC+13], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[14], ntt_const[NC+14], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[15], ntt_const[NC+15], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[16], ntt_const[NC+16], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[17], ntt_const[NC+17], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a01 = p0;
    a07 = t6;
    a13 = t4;
    a19 = t5;
    a25 = t2;
    a31 = t1;
    a37 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a02;
    sp_simd_t x1 = a08;
    sp_simd_t x5 = a14;
    sp_simd_t x6 = a20;
    sp_simd_t x3 = a26;
    sp_simd_t x2 = a32;
    sp_simd_t x4 = a38;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p0 = sp_simd_ntt_mul(p0, ntt_const[18], ntt_const[NC+18], p);
    p1 = sp_simd_ntt_mul(p1, ntt_const[19], ntt_const[NC+19], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[20], ntt_const[NC+20], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[21], ntt_const[NC+21], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[22], ntt_const[NC+22], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[23], ntt_const[NC+23], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[24], ntt_const[NC+24], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[25], ntt_const[NC+25], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[26], ntt_const[NC+26], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a02 = p0;
    a08 = t6;
    a14 = t4;
    a20 = t5;
    a26 = t2;
    a32 = t1;
    a38 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a03;
    sp_simd_t x1 = a09;
    sp_simd_t x5 = a15;
    sp_simd_t x6 = a21;
    sp_simd_t x3 = a27;
    sp_simd_t x2 = a33;
    sp_simd_t x4 = a39;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p0 = sp_simd_ntt_mul(p0, ntt_const[27], ntt_const[NC+27], p);
    p1 = sp_simd_ntt_mul(p1, ntt_const[28], ntt_const[NC+28], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[29], ntt_const[NC+29], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[30], ntt_const[NC+30], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[31], ntt_const[NC+31], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[32], ntt_const[NC+32], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[33], ntt_const[NC+33], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[34], ntt_const[NC+34], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[35], ntt_const[NC+35], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a03 = p0;
    a09 = t6;
    a15 = t4;
    a21 = t5;
    a27 = t2;
    a33 = t1;
    a39 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a04;
    sp_simd_t x1 = a10;
    sp_simd_t x5 = a16;
    sp_simd_t x6 = a22;
    sp_simd_t x3 = a28;
    sp_simd_t x2 = a34;
    sp_simd_t x4 = a40;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p0 = sp_simd_ntt_mul(p0, ntt_const[36], ntt_const[NC+36], p);
    p1 = sp_simd_ntt_mul(p1, ntt_const[37], ntt_const[NC+37], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[38], ntt_const[NC+38], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[39], ntt_const[NC+39], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[40], ntt_const[NC+40], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[41], ntt_const[NC+41], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[42], ntt_const[NC+42], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[43], ntt_const[NC+43], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[44], ntt_const[NC+44], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a04 = p0;
    a10 = t6;
    a16 = t4;
    a22 = t5;
    a28 = t2;
    a34 = t1;
    a40 = t3;
  }
  {
    sp_simd_t     t1, t2, t3, t4, t5, t6, t7, t8;
    sp_simd_t p0, p1, p2, p3, p4, p5, p6, p7, p8;

    sp_simd_t x0 = a05;
    sp_simd_t x1 = a11;
    sp_simd_t x5 = a17;
    sp_simd_t x6 = a23;
    sp_simd_t x3 = a29;
    sp_simd_t x2 = a35;
    sp_simd_t x4 = a41;

    p1 = sp_simd_add(x1, x4, p);
    p2 = sp_simd_add(x2, x5, p);
    p3 = sp_simd_add(x3, x6, p);
    p4 = sp_simd_sub(x1, x4, p);
    p5 = sp_simd_sub(x2, x5, p);
    p6 = sp_simd_sub(x3, x6, p);

    t1 = sp_simd_add(p1, p2, p);
    t1 = sp_simd_add(t1, p3, p);
    t2 = sp_simd_sub(p1, p3, p);
    t3 = sp_simd_sub(p2, p3, p);
    t4 = sp_simd_sub(p4, p5, p);
    t4 = sp_simd_add_partial(t4, p6, p);
    t5 = sp_simd_sub(p4, p6, p);
    t6 = sp_simd_add(p5, p6, p);

    p0 = sp_simd_add_partial(x0, t1, p);
    p1 = t1;
    p2 = t2;
    p3 = t3;
    p4 = sp_simd_add_partial(t2, t3, p);
    p5 = t4;
    p6 = t5;
    p7 = t6;
    p8 = sp_simd_add_partial(t5, t6, p);

    p0 = sp_simd_ntt_mul(p0, ntt_const[45], ntt_const[NC+45], p);
    p1 = sp_simd_ntt_mul(p1, ntt_const[46], ntt_const[NC+46], p);
    p2 = sp_simd_ntt_mul(p2, ntt_const[47], ntt_const[NC+47], p);
    p3 = sp_simd_ntt_mul(p3, ntt_const[48], ntt_const[NC+48], p);
    p4 = sp_simd_ntt_mul(p4, ntt_const[49], ntt_const[NC+49], p);
    p5 = sp_simd_ntt_mul(p5, ntt_const[50], ntt_const[NC+50], p);
    p6 = sp_simd_ntt_mul(p6, ntt_const[51], ntt_const[NC+51], p);
    p7 = sp_simd_ntt_mul(p7, ntt_const[52], ntt_const[NC+52], p);
    p8 = sp_simd_ntt_mul(p8, ntt_const[53], ntt_const[NC+53], p);

    t1 = sp_simd_add(p0, p1, p);
    t2 = sp_simd_add(p2, p4, p);
    t3 = sp_simd_add(p3, p4, p);
    t4 = p5;
    t5 = sp_simd_add(p6, p8, p);
    t6 = sp_simd_add(p7, p8, p);

    p1 = sp_simd_add(t1, t2, p);
    p2 = sp_simd_add(t1, t3, p);
    p3 = sp_simd_sub(t1, t2, p);
    p3 = sp_simd_sub(p3, t3, p);
    p4 = sp_simd_add(t4, t5, p);
    p5 = sp_simd_sub(t6, t4, p);
    p6 = sp_simd_sub(t4, t5, p);
    p6 = sp_simd_add(p6, t6, p);

    t1 = sp_simd_add(p1, p4, p);
    t2 = sp_simd_add(p2, p5, p);
    t3 = sp_simd_add(p3, p6, p);
    t4 = sp_simd_sub(p1, p4, p);
    t5 = sp_simd_sub(p2, p5, p);
    t6 = sp_simd_sub(p3, p6, p);

    a05 = p0;
    a11 = t6;
    a17 = t4;
    a23 = t5;
    a29 = t2;
    a35 = t1;
    a41 = t3;
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a00;
    sp_simd_t p1 = a01;
    sp_simd_t p2 = a02;
    sp_simd_t p3 = a03;
    sp_simd_t p4 = a04;
    sp_simd_t p5 = a05;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p0, x, j00, inc2, n);
    sp_simd_pfa_scatter(p3, x, j07, inc2, n);
    sp_simd_pfa_scatter(p2, x, j14, inc2, n);
    sp_simd_pfa_scatter(p4, x, j21, inc2, n);
    sp_simd_pfa_scatter(p1, x, j28, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a06;
    sp_simd_t p1 = a07;
    sp_simd_t p2 = a08;
    sp_simd_t p3 = a09;
    sp_simd_t p4 = a10;
    sp_simd_t p5 = a11;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p4, x, j01, inc2, n);
    sp_simd_pfa_scatter(p1, x, j08, inc2, n);
    sp_simd_pfa_scatter(p0, x, j15, inc2, n);
    sp_simd_pfa_scatter(p3, x, j22, inc2, n);
    sp_simd_pfa_scatter(p2, x, j29, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a12;
    sp_simd_t p1 = a13;
    sp_simd_t p2 = a14;
    sp_simd_t p3 = a15;
    sp_simd_t p4 = a16;
    sp_simd_t p5 = a17;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p3, x, j02, inc2, n);
    sp_simd_pfa_scatter(p2, x, j09, inc2, n);
    sp_simd_pfa_scatter(p4, x, j16, inc2, n);
    sp_simd_pfa_scatter(p1, x, j23, inc2, n);
    sp_simd_pfa_scatter(p0, x, j30, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a18;
    sp_simd_t p1 = a19;
    sp_simd_t p2 = a20;
    sp_simd_t p3 = a21;
    sp_simd_t p4 = a22;
    sp_simd_t p5 = a23;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p1, x, j03, inc2, n);
    sp_simd_pfa_scatter(p0, x, j10, inc2, n);
    sp_simd_pfa_scatter(p3, x, j17, inc2, n);
    sp_simd_pfa_scatter(p2, x, j24, inc2, n);
    sp_simd_pfa_scatter(p4, x, j31, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a24;
    sp_simd_t p1 = a25;
    sp_simd_t p2 = a26;
    sp_simd_t p3 = a27;
    sp_simd_t p4 = a28;
    sp_simd_t p5 = a29;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p2, x, j04, inc2, n);
    sp_simd_pfa_scatter(p4, x, j11, inc2, n);
    sp_simd_pfa_scatter(p1, x, j18, inc2, n);
    sp_simd_pfa_scatter(p0, x, j25, inc2, n);
    sp_simd_pfa_scatter(p3, x, j32, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a30;
    sp_simd_t p1 = a31;
    sp_simd_t p2 = a32;
    sp_simd_t p3 = a33;
    sp_simd_t p4 = a34;
    sp_simd_t p5 = a35;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p0, x, j05, inc2, n);
    sp_simd_pfa_scatter(p3, x, j12, inc2, n);
    sp_simd_pfa_scatter(p2, x, j19, inc2, n);
    sp_simd_pfa_scatter(p4, x, j26, inc2, n);
    sp_simd_pfa_scatter(p1, x, j33, inc2, n);
  }
  {
    sp_simd_t t1, t2, t3, t4;

    sp_simd_t p0 = a36;
    sp_simd_t p1 = a37;
    sp_simd_t p2 = a38;
    sp_simd_t p3 = a39;
    sp_simd_t p4 = a40;
    sp_simd_t p5 = a41;

    p1 = sp_simd_add(p0, p1, p);

    t1 = sp_simd_add(p1, p2, p);
    t2 = sp_simd_sub(p1, p2, p);
    t3 = sp_simd_add(p3, p5, p);
    t4 = sp_simd_add(p4, p5, p);

    p1 = sp_simd_add(t1, t3, p);
    p2 = sp_simd_add(t2, t4, p);
    p3 = sp_simd_sub(t1, t3, p);
    p4 = sp_simd_sub(t2, t4, p);

    sp_simd_pfa_scatter(p4, x, j06, inc2, n);
    sp_simd_pfa_scatter(p1, x, j13, inc2, n);
    sp_simd_pfa_scatter(p0, x, j20, inc2, n);
    sp_simd_pfa_scatter(p3, x, j27, inc2, n);
    sp_simd_pfa_scatter(p2, x, j34, inc2, n);
  }
}
#endif

static void
ntt35_pfa_run(spv_t x, spv_size_t cofactor,
	  sp_t p, spv_t ntt_const)
{
  spv_size_t i = 0;
  spv_size_t incstart = 0;
  spv_size_t n = 35 * cofactor;
  spv_size_t inc = cofactor;
  spv_size_t inc2 = 35;

#ifdef HAVE_SSE2
  spv_size_t num_simd = SP_SIMD_VSIZE * (cofactor / SP_SIMD_VSIZE);

  for (i = 0; i < num_simd; i += SP_SIMD_VSIZE)
    {
      ntt35_pfa_run_core_simd(x, incstart, inc, inc2, n, p, ntt_const);
      incstart += SP_SIMD_VSIZE * inc2;
    }
#endif

  for (; i < cofactor; i++, incstart += inc2)
    ntt35_pfa_run_core(x, incstart, inc, n, p, ntt_const);

}

const nttconfig_t ntt35_config = 
{
  35,
  ntt35_get_num_const,
  ntt35_init,
  ntt35_run,
  ntt35_pfa_run,
  ntt35_twiddle_run
};
