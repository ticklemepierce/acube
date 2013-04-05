#ifndef H_TRANSF_H_
#define H_TRANSF_H_

#include "const.h"
#include "cubestat.h"

// =========================================================================
// this module handles transformation processing
// input of the transformation is state of a part of the cube and a move
// output is a new state
// =========================================================================


class Transform_table_ct {
  Word a[A_N_TW][A_M_CT]; // 27 x 20412 = 551124 (1102248)
  int co;

  inline int t_f(int);
  inline int t_r(int);
  inline int t_u(int);
  inline int t_b(int);
  inline int t_l(int);
  inline int t_d(int);
 public:
  inline int a_do_tw(int t, int e) { return a[t][e]; }
  Transform_table_ct(int co);
};


class Transform_table_ef {
  Long a[A_N_TW][A_M_EF]; // 27 x 126720 = 3421440 (13685760) // oh no!
  int eo;

  inline int t_f(int);
  inline int t_r(int);
  inline int t_u(int);
  inline int t_b(int);
  inline int t_l(int);
  inline int t_d(int);
 public:
  inline int a_do_tw(int t, int e) { return a[t][e]; }
  Transform_table_ef(int eo);
};


class Transform_table_el {
  Word a[A_N_TW][A_N_EL]; // 27 x 495 = 13365 (26730)
  int e1;

  inline int t_f(int);
  inline int t_r(int);
  inline int t_u(int);
  inline int t_b(int);
  inline int t_l(int);
  inline int t_d(int);
 public:
  inline int a_do_tw(int t, int e) { return a[t][e]; }
  Transform_table_el(int e1);
};


class Transform_table_cp {
  Word a[A_N_TW][B_N_CP]; // 27 x 40320 = 1088640 (2177280)
  Byte b[A_N_TW];
  int c1;

  inline int t_f(int);
  inline int t_r(int);
  inline int t_u(int);
  inline int t_b(int);
  inline int t_l(int);
  inline int t_d(int);
 public:
  inline int a_do_tw(int t, int e) { return a[t][e]; }
  inline int b_do_tw(int t, int e) { return a[b[t]][e]; }
  Transform_table_cp(int c1);
};


class Transform_table_ep {
  Word a[B_N_TW][B_N_EP]; // 15 x 40320 = 640800 (1209600)
  int e1;

  inline int t_f2(int);
  inline int t_r2(int);
  inline int t_u(int);
  inline int t_b2(int);
  inline int t_l2(int);
  inline int t_d(int);
 public:
  inline int b_do_tw(int t, int e) { return a[t][e]; }
  Transform_table_ep(int e1);
};


class Transform_table_mp {
  Word a[B_N_TW][B_N_MP]; // 15 x 24 = 360 (720)
  int e1;

  inline int t_f2(int);
  inline int t_r2(int);
  inline int t_u(int);
  inline int t_b2(int);
  inline int t_l2(int);
  inline int t_d(int);
 public:
  inline int b_do_tw(int t, int e) { return a[t][e]; }
  Transform_table_mp(int e1);
};


class Transform_table_se {
  // used memory: 3844080 (7664400)
  Word ua[A_N_TW][N_SE]; // 27 x 11880 = 320760 (641520)
  Word da[A_N_TW][N_SE]; // 27 x 11880 = 320760 (641520)
  Word ma[A_N_TW][N_SE]; // 27 x 11880 = 320760 (641520)
  Word ea[N_HE][N_HE];   // 1680 x 1680 = 2822400 (5644800) grrr
  Word uha[N_SE];        // 11880 = 11880 (23760)
  Word dha[N_SE];        // 11880 = 11880 (23760)
  Word mea[N_SE];        // 11880 = 11880 (23760)
  Byte p2u[N_SE];         // 11880 = 11880  (11880)
  Byte p2d[N_SE];         // 11880  = 11880 (11880)
  int e1;

  inline int tu_f(int);
  inline int tu_r(int);
  inline int tu_u(int);
  inline int tu_b(int);
  inline int tu_l(int);
  inline int tu_d(int);
  inline int td_f(int);
  inline int td_r(int);
  inline int td_u(int);
  inline int td_b(int);
  inline int td_l(int);
  inline int td_d(int);
  inline int tm_f(int);
  inline int tm_r(int);
  inline int tm_u(int);
  inline int tm_b(int);
  inline int tm_l(int);
  inline int tm_d(int);
 public:
  inline int a_do_u_tw(int t, int e) { return ua[t][e]; }
  inline int a_do_d_tw(int t, int e) { return da[t][e]; }
  inline int a_do_m_tw(int t, int e) { return ma[t][e]; }
  inline int se_to_mp(int ms) { return mea[ms]; }
  // the first param. is coded U edges, the second D edges...
  inline int se_to_ep(int us, int ds) { return ea[uha[us]][dha[ds]]; }
  inline int is_p2_u(int s) { return p2u[s]; }
  inline int is_p2_d(int s) { return p2d[s]; }
  Transform_table_se(int e1, int opt);
};

class Transform_table {
 public:
  // all used memory: 25866738
  Transform_table_ct *ct;
  Transform_table_ef *ef;
  Transform_table_el *el;
  Transform_table_cp *cp;
  Transform_table_ep *ep;
  Transform_table_mp *mp;
  Transform_table_se *se;

  Transform_table(struct CubeState state, int opt);
  ~Transform_table();
};

#endif
