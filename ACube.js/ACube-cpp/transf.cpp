
#include <stdio.h>
#include "const.h"
#include "transf.h"
#include "pack.h"
#include "cubestat.h"

// =========================================================================
   Transform_table::Transform_table(struct CubeState state, int opt)
// -------------------------------------------------------------------------
{
  fprintf(stderr, "\nBuilding transformation tables...\n");

  ct = new Transform_table_ct(state.co);
  ef = new Transform_table_ef(state.eo);
  el = new Transform_table_el(state.e1);

  cp = new Transform_table_cp(state.c1);
  if (opt) {
    ep = 0;
    mp = 0;
  }
  else {
    ep = new Transform_table_ep(state.e1);
    mp = new Transform_table_mp(state.e1);
  }

  se = new Transform_table_se(state.e1, opt);

  fprintf(stderr, "Transformation tables done.\n");
}

// =========================================================================
   Transform_table::~Transform_table()
// -------------------------------------------------------------------------
{
  delete ct;
  delete ef;
  delete el;

  delete cp;
  delete ep;
  delete mp;

  delete se;
}


// =========================================================================
   Transform_table_ct::Transform_table_ct(int co): co(co)
// -------------------------------------------------------------------------
// transformation table for corner twists
{
  int c;
  Pack_ct pc(co);
  int n = pc.len();

  fprintf(stderr, " - twists of corners...");
  fflush(stderr);
  for (c = 0; c < n; c++) {
    a[A_TW_U1][c] = t_u(c);
    a[A_TW_F1][c] = t_f(c);
    a[A_TW_R1][c] = t_r(c);
    a[A_TW_D1][c] = t_d(c);
    a[A_TW_B1][c] = t_b(c);
    a[A_TW_L1][c] = t_l(c);
  }
  for (c = 0; c < n; c++) {
    a[A_TW_U2][c] = a[A_TW_U1][a[A_TW_U1][c]];
    a[A_TW_F2][c] = a[A_TW_F1][a[A_TW_F1][c]];
    a[A_TW_R2][c] = a[A_TW_R1][a[A_TW_R1][c]];
    a[A_TW_D2][c] = a[A_TW_D1][a[A_TW_D1][c]];
    a[A_TW_B2][c] = a[A_TW_B1][a[A_TW_B1][c]];
    a[A_TW_L2][c] = a[A_TW_L1][a[A_TW_L1][c]];
  }
  for (c = 0; c < n; c++) {
    a[A_TW_U3][c] = a[A_TW_U2][a[A_TW_U1][c]];
    a[A_TW_F3][c] = a[A_TW_F2][a[A_TW_F1][c]];
    a[A_TW_R3][c] = a[A_TW_R2][a[A_TW_R1][c]];
    a[A_TW_D3][c] = a[A_TW_D2][a[A_TW_D1][c]];
    a[A_TW_B3][c] = a[A_TW_B2][a[A_TW_B1][c]];
    a[A_TW_L3][c] = a[A_TW_L2][a[A_TW_L1][c]];
  }
  for (c = 0; c < n; c++) {
    a[A_TW_US][c]  = a[A_TW_D3][a[A_TW_U1][c]];
    a[A_TW_FS][c]  = a[A_TW_B3][a[A_TW_F1][c]];
    a[A_TW_RS][c]  = a[A_TW_L3][a[A_TW_R1][c]];
    a[A_TW_US2][c] = a[A_TW_D2][a[A_TW_U2][c]];
    a[A_TW_FS2][c] = a[A_TW_B2][a[A_TW_F2][c]];
    a[A_TW_RS2][c] = a[A_TW_L2][a[A_TW_R2][c]];
    a[A_TW_DS][c]  = a[A_TW_U3][a[A_TW_D1][c]];
    a[A_TW_BS][c]  = a[A_TW_F3][a[A_TW_B1][c]];
    a[A_TW_LS][c]  = a[A_TW_R3][a[A_TW_L1][c]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_ef::Transform_table_ef(int eo): eo(eo)
// -------------------------------------------------------------------------
// transformation table for edge flips
{
  int e;
  Pack_ef pe(eo);
  int n = pe.len();

  fprintf(stderr, " - flips of edges...");
  fflush(stderr);
  for (e = 0; e < n; e++) {
    a[A_TW_U1][e] = t_u(e);
    a[A_TW_F1][e] = t_f(e);
    a[A_TW_R1][e] = t_r(e);
    a[A_TW_D1][e] = t_d(e);
    a[A_TW_B1][e] = t_b(e);
    a[A_TW_L1][e] = t_l(e);
  }
  for (e = 0; e < n; e++) {
    a[A_TW_U2][e] = a[A_TW_U1][a[A_TW_U1][e]];
    a[A_TW_F2][e] = a[A_TW_F1][a[A_TW_F1][e]];
    a[A_TW_R2][e] = a[A_TW_R1][a[A_TW_R1][e]];
    a[A_TW_D2][e] = a[A_TW_D1][a[A_TW_D1][e]];
    a[A_TW_B2][e] = a[A_TW_B1][a[A_TW_B1][e]];
    a[A_TW_L2][e] = a[A_TW_L1][a[A_TW_L1][e]];
  }
  for (e = 0; e < n; e++) {
    a[A_TW_U3][e] = a[A_TW_U2][a[A_TW_U1][e]];
    a[A_TW_F3][e] = a[A_TW_F2][a[A_TW_F1][e]];
    a[A_TW_R3][e] = a[A_TW_R2][a[A_TW_R1][e]];
    a[A_TW_D3][e] = a[A_TW_D2][a[A_TW_D1][e]];
    a[A_TW_B3][e] = a[A_TW_B2][a[A_TW_B1][e]];
    a[A_TW_L3][e] = a[A_TW_L2][a[A_TW_L1][e]];
  }
  for (e = 0; e < n; e++) {
    a[A_TW_US][e]  = a[A_TW_D3][a[A_TW_U1][e]];
    a[A_TW_FS][e]  = a[A_TW_B3][a[A_TW_F1][e]];
    a[A_TW_RS][e]  = a[A_TW_L3][a[A_TW_R1][e]];
    a[A_TW_US2][e] = a[A_TW_D2][a[A_TW_U2][e]];
    a[A_TW_FS2][e] = a[A_TW_B2][a[A_TW_F2][e]];
    a[A_TW_RS2][e] = a[A_TW_L2][a[A_TW_R2][e]];
    a[A_TW_DS][e]  = a[A_TW_U3][a[A_TW_D1][e]];
    a[A_TW_BS][e]  = a[A_TW_F3][a[A_TW_B1][e]];
    a[A_TW_LS][e]  = a[A_TW_R3][a[A_TW_L1][e]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_el::Transform_table_el(int e1): e1(e1)
// -------------------------------------------------------------------------
// transformation table for unordered placements of the middle layer edges
// the goal of the phase 1 is placing 4 middle layer edges to that layer
{
  int e;
  Pack_el pe(e1);
  int n = pe.len();

  fprintf(stderr, " - locations of middle edges...");
  fflush(stderr);
  for (e = 0; e < n; e++) {
    a[A_TW_F1][e] = t_f(e);
    a[A_TW_L1][e] = t_l(e);
    a[A_TW_U1][e] = t_u(e);
    a[A_TW_B1][e] = t_b(e);
    a[A_TW_R1][e] = t_r(e);
    a[A_TW_D1][e] = t_d(e);
  }
  for (e = 0; e < n; e++) {
    a[A_TW_U2][e] = a[A_TW_U1][a[A_TW_U1][e]];
    a[A_TW_F2][e] = a[A_TW_F1][a[A_TW_F1][e]];
    a[A_TW_R2][e] = a[A_TW_R1][a[A_TW_R1][e]];
    a[A_TW_D2][e] = a[A_TW_D1][a[A_TW_D1][e]];
    a[A_TW_B2][e] = a[A_TW_B1][a[A_TW_B1][e]];
    a[A_TW_L2][e] = a[A_TW_L1][a[A_TW_L1][e]];
  }
  for (e = 0; e < n; e++) {
    a[A_TW_U3][e] = a[A_TW_U2][a[A_TW_U1][e]];
    a[A_TW_F3][e] = a[A_TW_F2][a[A_TW_F1][e]];
    a[A_TW_R3][e] = a[A_TW_R2][a[A_TW_R1][e]];
    a[A_TW_D3][e] = a[A_TW_D2][a[A_TW_D1][e]];
    a[A_TW_B3][e] = a[A_TW_B2][a[A_TW_B1][e]];
    a[A_TW_L3][e] = a[A_TW_L2][a[A_TW_L1][e]];
  }
  for (e = 0; e < n; e++) {
    a[A_TW_US][e]  = a[A_TW_D3][a[A_TW_U1][e]];
    a[A_TW_FS][e]  = a[A_TW_B3][a[A_TW_F1][e]];
    a[A_TW_RS][e]  = a[A_TW_L3][a[A_TW_R1][e]];
    a[A_TW_US2][e] = a[A_TW_D2][a[A_TW_U2][e]];
    a[A_TW_FS2][e] = a[A_TW_B2][a[A_TW_F2][e]];
    a[A_TW_RS2][e] = a[A_TW_L2][a[A_TW_R2][e]];
    a[A_TW_DS][e]  = a[A_TW_U3][a[A_TW_D1][e]];
    a[A_TW_BS][e]  = a[A_TW_F3][a[A_TW_B1][e]];
    a[A_TW_LS][e]  = a[A_TW_R3][a[A_TW_L1][e]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_cp::Transform_table_cp(int c1): c1(c1)
// -------------------------------------------------------------------------
// transformation table for the corner permutations
// this table is used in both phases
{
  int c;
  Pack_cp pc(c1);
  int n = pc.len();

  b[B_TW_U1] =  A_TW_U1;
  b[B_TW_U2] =  A_TW_U2;
  b[B_TW_U3] =  A_TW_U3;
  b[B_TW_D1] =  A_TW_D1;
  b[B_TW_D2] =  A_TW_D2;
  b[B_TW_D3] =  A_TW_D3;
  b[B_TW_F2] =  A_TW_F2;
  b[B_TW_R2] =  A_TW_R2;
  b[B_TW_B2] =  A_TW_B2;
  b[B_TW_L2] =  A_TW_L2;
  b[B_TW_US] =  A_TW_US;
  b[B_TW_US2] = A_TW_US2;
  b[B_TW_DS] =  A_TW_DS;
  b[B_TW_FS2] = A_TW_FS2;
  b[B_TW_RS2] = A_TW_RS2;

  fprintf(stderr, " - permutations of corners...");
  fflush(stderr);
  for (c = 0; c < n; c++) {
    a[A_TW_U1][c] = t_u(c);
    a[A_TW_F1][c] = t_f(c);
    a[A_TW_R1][c] = t_r(c);
    a[A_TW_D1][c] = t_d(c);
    a[A_TW_B1][c] = t_b(c);
    a[A_TW_L1][c] = t_l(c);
  }
  for (c = 0; c < n; c++) {
    a[A_TW_U2][c] = a[A_TW_U1][a[A_TW_U1][c]];
    a[A_TW_F2][c] = a[A_TW_F1][a[A_TW_F1][c]];
    a[A_TW_R2][c] = a[A_TW_R1][a[A_TW_R1][c]];
    a[A_TW_D2][c] = a[A_TW_D1][a[A_TW_D1][c]];
    a[A_TW_B2][c] = a[A_TW_B1][a[A_TW_B1][c]];
    a[A_TW_L2][c] = a[A_TW_L1][a[A_TW_L1][c]];
  }
  for (c = 0; c < n; c++) {
    a[A_TW_U3][c] = a[A_TW_U2][a[A_TW_U1][c]];
    a[A_TW_F3][c] = a[A_TW_F2][a[A_TW_F1][c]];
    a[A_TW_R3][c] = a[A_TW_R2][a[A_TW_R1][c]];
    a[A_TW_D3][c] = a[A_TW_D2][a[A_TW_D1][c]];
    a[A_TW_B3][c] = a[A_TW_B2][a[A_TW_B1][c]];
    a[A_TW_L3][c] = a[A_TW_L2][a[A_TW_L1][c]];
  }
  for (c = 0; c < n; c++) {
    a[A_TW_US][c]  = a[A_TW_D3][a[A_TW_U1][c]];
    a[A_TW_FS][c]  = a[A_TW_B3][a[A_TW_F1][c]];
    a[A_TW_RS][c]  = a[A_TW_L3][a[A_TW_R1][c]];
    a[A_TW_US2][c] = a[A_TW_D2][a[A_TW_U2][c]];
    a[A_TW_FS2][c] = a[A_TW_B2][a[A_TW_F2][c]];
    a[A_TW_RS2][c] = a[A_TW_L2][a[A_TW_R2][c]];
    a[A_TW_DS][c]  = a[A_TW_U3][a[A_TW_D1][c]];
    a[A_TW_BS][c]  = a[A_TW_F3][a[A_TW_B1][c]];
    a[A_TW_LS][c]  = a[A_TW_R3][a[A_TW_L1][c]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_ep::Transform_table_ep(int e1): e1(e1)
// -------------------------------------------------------------------------
// transformation table for permutation of 8 U & D layer edges
// this table is used only in phase 2
// we need find out what EP we have between the phases
// (we don't remember entire cube and we don't have enough memory
// for all edges permutation (12! = 479001600))
// so we remember placing of 4 U SE edges and of 4 D SE ones
// theese 8 edges can be combined to EP before phase 2...
{
  int e;
  Pack_ep pe(e1);
  int n = pe.len();

  fprintf(stderr, " - permutations of up and down edges...");
  fflush(stderr);
  for (e = 0; e < n; e++) {
    a[B_TW_U1][e] = t_u(e);
    a[B_TW_F2][e] = t_f2(e);
    a[B_TW_R2][e] = t_r2(e);
    a[B_TW_D1][e] = t_d(e);
    a[B_TW_B2][e] = t_b2(e);
    a[B_TW_L2][e] = t_l2(e);
  }
  for (e = 0; e < n; e++) {
    a[B_TW_U2][e] = a[B_TW_U1][a[B_TW_U1][e]];
    a[B_TW_D2][e] = a[B_TW_D1][a[B_TW_D1][e]];
  }
  for (e = 0; e < n; e++) {
    a[B_TW_U3][e] = a[B_TW_U2][a[B_TW_U1][e]];
    a[B_TW_D3][e] = a[B_TW_D2][a[B_TW_D1][e]];
  }
  for (e = 0; e < n; e++) {
    a[B_TW_US][e]  = a[B_TW_D3][a[B_TW_U1][e]];
    a[B_TW_US2][e] = a[B_TW_D2][a[B_TW_U2][e]];
    a[B_TW_DS][e]  = a[B_TW_U3][a[B_TW_D1][e]];
    a[B_TW_FS2][e] = a[B_TW_B2][a[B_TW_F2][e]];
    a[B_TW_RS2][e] = a[B_TW_L2][a[B_TW_R2][e]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_mp::Transform_table_mp(int e1): e1(e1)
// -------------------------------------------------------------------------
// transformation table for 4 middle layer edges permutation
// moves of the 2nd phase affects only permutation of the middle-layer edges
// in the middle layer
// since there are all middle-layer edges in that layer after phase 1
// so we need to corectly place them in that layer
// we need to find out the permutation after phase 1 and EL is not enough
// so we also remember ordered placing SE of that edges and then after phase 1
// we can transform this SE to the MP
{
  int m;
  Pack_mp pm(e1);
  int n = pm.len();

  fprintf(stderr, " - permutations of middle edges...");
  fflush(stderr);
  for (m = 0; m < n; m++) {
    a[B_TW_U1][m] = t_u(m);
    a[B_TW_F2][m] = t_f2(m);
    a[B_TW_R2][m] = t_r2(m);
    a[B_TW_D1][m] = t_d(m);
    a[B_TW_B2][m] = t_b2(m);
    a[B_TW_L2][m] = t_l2(m);
  }
  for (m = 0; m < n; m++) {
    a[B_TW_U2][m] = a[B_TW_U1][a[B_TW_U1][m]];
    a[B_TW_D2][m] = a[B_TW_D1][a[B_TW_D1][m]];
  }
  for (m = 0; m < n; m++) {
    a[B_TW_U3][m] = a[B_TW_U2][a[B_TW_U1][m]];
    a[B_TW_D3][m] = a[B_TW_D2][a[B_TW_D1][m]];
  }
  for (m = 0; m < n; m++) {
    a[B_TW_US][m]  = a[B_TW_D3][a[B_TW_U1][m]];
    a[B_TW_US2][m] = a[B_TW_D2][a[B_TW_U2][m]];
    a[B_TW_DS][m]  = a[B_TW_U3][a[B_TW_D1][m]];
    a[B_TW_FS2][m] = a[B_TW_B2][a[B_TW_F2][m]];
    a[B_TW_RS2][m] = a[B_TW_L2][a[B_TW_R2][m]];
  }
  fprintf(stderr, " %i items per move.\n", n);
}

// =========================================================================
   Transform_table_se::Transform_table_se(int e1, int opt): e1(e1)
// -------------------------------------------------------------------------
// transformation table for ordered placing of the 4 particular edges
// theese tables are used before the phase 1 and the numbers MP and EP
// are computed from them
{
  int s;
  Pack_use use(e1);
  int usn = use.len();
  Pack_dse dse(e1);
  int dsn = dse.len();
  Pack_mse mse(e1);
  int msn = mse.len();

  fprintf(stderr, " - locations of slice edges...\n   - up...    ");
  fflush(stderr);
  for (s = 0; s < usn; s++) {
    ua[A_TW_U1][s] = tu_u(s);
    ua[A_TW_F1][s] = tu_f(s);
    ua[A_TW_R1][s] = tu_r(s);
    ua[A_TW_D1][s] = tu_d(s);
    ua[A_TW_B1][s] = tu_b(s);
    ua[A_TW_L1][s] = tu_l(s);
  }
  for (s = 0; s < usn; s++) {
    ua[A_TW_U2][s] = ua[A_TW_U1][ua[A_TW_U1][s]];
    ua[A_TW_F2][s] = ua[A_TW_F1][ua[A_TW_F1][s]];
    ua[A_TW_R2][s] = ua[A_TW_R1][ua[A_TW_R1][s]];
    ua[A_TW_D2][s] = ua[A_TW_D1][ua[A_TW_D1][s]];
    ua[A_TW_B2][s] = ua[A_TW_B1][ua[A_TW_B1][s]];
    ua[A_TW_L2][s] = ua[A_TW_L1][ua[A_TW_L1][s]];
  }
  for (s = 0; s < usn; s++) {
    ua[A_TW_U3][s] = ua[A_TW_U2][ua[A_TW_U1][s]];
    ua[A_TW_F3][s] = ua[A_TW_F2][ua[A_TW_F1][s]];
    ua[A_TW_R3][s] = ua[A_TW_R2][ua[A_TW_R1][s]];
    ua[A_TW_D3][s] = ua[A_TW_D2][ua[A_TW_D1][s]];
    ua[A_TW_B3][s] = ua[A_TW_B2][ua[A_TW_B1][s]];
    ua[A_TW_L3][s] = ua[A_TW_L2][ua[A_TW_L1][s]];
  }
  for (s = 0; s < usn; s++) {
    ua[A_TW_US][s]  = ua[A_TW_D3][ua[A_TW_U1][s]];
    ua[A_TW_FS][s]  = ua[A_TW_B3][ua[A_TW_F1][s]];
    ua[A_TW_RS][s]  = ua[A_TW_L3][ua[A_TW_R1][s]];
    ua[A_TW_US2][s] = ua[A_TW_D2][ua[A_TW_U2][s]];
    ua[A_TW_FS2][s] = ua[A_TW_B2][ua[A_TW_F2][s]];
    ua[A_TW_RS2][s] = ua[A_TW_L2][ua[A_TW_R2][s]];
    ua[A_TW_DS][s]  = ua[A_TW_U3][ua[A_TW_D1][s]];
    ua[A_TW_BS][s]  = ua[A_TW_F3][ua[A_TW_B1][s]];
    ua[A_TW_LS][s]  = ua[A_TW_R3][ua[A_TW_L1][s]];
  }
  fprintf(stderr, " %i items per move.\n   - down...  ", usn);
  fflush(stderr);
  for (s = 0; s < dsn; s++) {
    da[A_TW_U1][s] = td_u(s);
    da[A_TW_F1][s] = td_f(s);
    da[A_TW_R1][s] = td_r(s);
    da[A_TW_D1][s] = td_d(s);
    da[A_TW_B1][s] = td_b(s);
    da[A_TW_L1][s] = td_l(s);
  }
  for (s = 0; s < dsn; s++) {
    da[A_TW_U2][s] = da[A_TW_U1][da[A_TW_U1][s]];
    da[A_TW_F2][s] = da[A_TW_F1][da[A_TW_F1][s]];
    da[A_TW_R2][s] = da[A_TW_R1][da[A_TW_R1][s]];
    da[A_TW_D2][s] = da[A_TW_D1][da[A_TW_D1][s]];
    da[A_TW_B2][s] = da[A_TW_B1][da[A_TW_B1][s]];
    da[A_TW_L2][s] = da[A_TW_L1][da[A_TW_L1][s]];
  }
  for (s = 0; s < dsn; s++) {
    da[A_TW_U3][s] = da[A_TW_U2][da[A_TW_U1][s]];
    da[A_TW_F3][s] = da[A_TW_F2][da[A_TW_F1][s]];
    da[A_TW_R3][s] = da[A_TW_R2][da[A_TW_R1][s]];
    da[A_TW_D3][s] = da[A_TW_D2][da[A_TW_D1][s]];
    da[A_TW_B3][s] = da[A_TW_B2][da[A_TW_B1][s]];
    da[A_TW_L3][s] = da[A_TW_L2][da[A_TW_L1][s]];
  }
  for (s = 0; s < dsn; s++) {
    da[A_TW_US][s]  = da[A_TW_D3][da[A_TW_U1][s]];
    da[A_TW_FS][s]  = da[A_TW_B3][da[A_TW_F1][s]];
    da[A_TW_RS][s]  = da[A_TW_L3][da[A_TW_R1][s]];
    da[A_TW_US2][s] = da[A_TW_D2][da[A_TW_U2][s]];
    da[A_TW_FS2][s] = da[A_TW_B2][da[A_TW_F2][s]];
    da[A_TW_RS2][s] = da[A_TW_L2][da[A_TW_R2][s]];
    da[A_TW_DS][s]  = da[A_TW_U3][da[A_TW_D1][s]];
    da[A_TW_BS][s]  = da[A_TW_F3][da[A_TW_B1][s]];
    da[A_TW_LS][s]  = da[A_TW_R3][da[A_TW_L1][s]];
  }
  fprintf(stderr, " %i items per move.\n   - middle...", dsn);
  fflush(stderr);
  for (s = 0; s < msn; s++) {
    ma[A_TW_U1][s] = tm_u(s);
    ma[A_TW_F1][s] = tm_f(s);
    ma[A_TW_R1][s] = tm_r(s);
    ma[A_TW_D1][s] = tm_d(s);
    ma[A_TW_B1][s] = tm_b(s);
    ma[A_TW_L1][s] = tm_l(s);
  }
  for (s = 0; s < msn; s++) {
    ma[A_TW_U2][s] = ma[A_TW_U1][ma[A_TW_U1][s]];
    ma[A_TW_F2][s] = ma[A_TW_F1][ma[A_TW_F1][s]];
    ma[A_TW_R2][s] = ma[A_TW_R1][ma[A_TW_R1][s]];
    ma[A_TW_D2][s] = ma[A_TW_D1][ma[A_TW_D1][s]];
    ma[A_TW_B2][s] = ma[A_TW_B1][ma[A_TW_B1][s]];
    ma[A_TW_L2][s] = ma[A_TW_L1][ma[A_TW_L1][s]];
  }
  for (s = 0; s < msn; s++) {
    ma[A_TW_U3][s] = ma[A_TW_U2][ma[A_TW_U1][s]];
    ma[A_TW_F3][s] = ma[A_TW_F2][ma[A_TW_F1][s]];
    ma[A_TW_R3][s] = ma[A_TW_R2][ma[A_TW_R1][s]];
    ma[A_TW_D3][s] = ma[A_TW_D2][ma[A_TW_D1][s]];
    ma[A_TW_B3][s] = ma[A_TW_B2][ma[A_TW_B1][s]];
    ma[A_TW_L3][s] = ma[A_TW_L2][ma[A_TW_L1][s]];
  }
  for (s = 0; s < msn; s++) {
    ma[A_TW_US][s]  = ma[A_TW_D3][ma[A_TW_U1][s]];
    ma[A_TW_FS][s]  = ma[A_TW_B3][ma[A_TW_F1][s]];
    ma[A_TW_RS][s]  = ma[A_TW_L3][ma[A_TW_R1][s]];
    ma[A_TW_US2][s] = ma[A_TW_D2][ma[A_TW_U2][s]];
    ma[A_TW_FS2][s] = ma[A_TW_B2][ma[A_TW_F2][s]];
    ma[A_TW_RS2][s] = ma[A_TW_L2][ma[A_TW_R2][s]];
    ma[A_TW_DS][s]  = ma[A_TW_U3][ma[A_TW_D1][s]];
    ma[A_TW_BS][s]  = ma[A_TW_F3][ma[A_TW_B1][s]];
    ma[A_TW_LS][s]  = ma[A_TW_R3][ma[A_TW_L1][s]];
  }
  fprintf(stderr, " %i items per move.\n", msn);

// table for conversion U & D slice-edges to EP
// the reason why it is not the sam case as the corner permutation is that
// number of edges is 12 and number of their permutation is 12! = 479e6
// that is too much for storing in memory...
// so we have to do following:
//  - we remember positions of the 4 U edges on 12 possible positions
//    (V(12, 4) = 11880 cases, we call it USE
//  - the same is done for D edges, DSE
//  - theese edges are in the U & D layers after the phase 1
//  - so we could reduce theese USE & DSE to UHE & DHE and then to one EP
  if (!opt) {
    int uh, dh;
    Pack_uhe uhe(e1);
    int uhn = uhe.len();
    Pack_dhe dhe(e1);
    int dhn = dhe.len();

    fprintf(stderr, " - up and down edges' transformations..");
    fflush(stderr);
    for (uh = 0; uh < uhn; uh++) {
      if ((uh & 0xFF) == 0) {
        fprintf(stderr, ".");
        fflush(stderr);
      }
      for (dh = 0; dh < dhn; dh++)
        ea[uh][dh] = uhe.to_ep(uh, dh);
    }
    fprintf(stderr, " %i x %i items.\n", uhn, dhn);

    fprintf(stderr, " - slice edges' transformations...\n   - up...    ");
    fflush(stderr);
    for (s = 0; s < usn; s++) {
      uha[s] = use.to_uhe(s);
    }
    fprintf(stderr, " %i items.\n   - down...  ", usn);
    fflush(stderr);
    for (s = 0; s < dsn; s++) {
      dha[s] = dse.to_dhe(s);
    }
    fprintf(stderr, " %i items.\n   - middle...", dsn);
    fflush(stderr);
    for (s = 0; s < msn; s++) {
      mea[s] = mse.to_mp(s);
    }
    fprintf(stderr, " %i items.\n", msn);

    fprintf(stderr, " - slice edges' characters for phase 2...\n   - up...  ");
    fflush(stderr);
    for (s = 0; s < usn; s++) {
      p2u[s] = use.is_p2(s);
    }
    fprintf(stderr, " %i items.\n   - down...", usn);
    fflush(stderr);
    for (s = 0; s < dsn; s++) {
      p2d[s] = dse.is_p2(s);
    }
    fprintf(stderr, " %i items.\n", dsn);
  }
}


// =========================================================================
// Metody pro vyplneni transformacnich tabulek
// =========================================================================

int  Transform_table_ct::t_u(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_UFR, A_CR_URB, A_CR_UBL, A_CR_ULF);
    return p.pk();
}

int  Transform_table_ct::t_f(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_DFL, A_CR_DRF, A_CR_UFR, A_CR_ULF);
    p.adjust(A_CR_DFL, A_CR_DRF, A_CR_UFR, A_CR_ULF);
    return p.pk();
}

int  Transform_table_ct::t_r(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_DRF, A_CR_DBR, A_CR_URB, A_CR_UFR);
    p.adjust(A_CR_DRF, A_CR_DBR, A_CR_URB, A_CR_UFR);
    return p.pk();
}

int  Transform_table_ct::t_d(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_DFL, A_CR_DLB, A_CR_DBR, A_CR_DRF);
    return p.pk();
}

int  Transform_table_ct::t_b(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_DBR, A_CR_DLB, A_CR_UBL, A_CR_URB);
    p.adjust(A_CR_DBR, A_CR_DLB, A_CR_UBL, A_CR_URB);
    return p.pk();
}

int  Transform_table_ct::t_l(int c) {
    Pack_ct p(co);
    p.unpk(c);
    p.cycle( A_CR_DLB, A_CR_DFL, A_CR_ULF, A_CR_UBL);
    p.adjust(A_CR_DLB, A_CR_DFL, A_CR_ULF, A_CR_UBL);
    return p.pk();
}

// =========================================================================

int  Transform_table_ef::t_u(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_UR, A_ED_UB, A_ED_UL, A_ED_UF);
    return p.pk();
}

int  Transform_table_ef::t_f(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    p.adjust(A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    return p.pk();
}

int  Transform_table_ef::t_r(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_FR, A_ED_DR, A_ED_BR, A_ED_UR);
    return p.pk();
}

int  Transform_table_ef::t_d(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_DL, A_ED_DB, A_ED_DR, A_ED_DF);
    return p.pk();
}

int  Transform_table_ef::t_b(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    p.adjust(A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    return p.pk();
}

int  Transform_table_ef::t_l(int e) {
    Pack_ef p(eo);
    p.unpk(e);
    p.cycle( A_ED_BL, A_ED_DL, A_ED_FL, A_ED_UL);
    return p.pk();
}

// =========================================================================

int  Transform_table_el::t_u(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_UF, A_ED_UR, A_ED_UB, A_ED_UL);
    return p.pk();
}

int  Transform_table_el::t_f(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    return p.pk();
}

int  Transform_table_el::t_r(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_FR, A_ED_DR, A_ED_BR, A_ED_UR);
    return p.pk();
}

int  Transform_table_el::t_d(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_DF, A_ED_DL, A_ED_DB, A_ED_DR);
    return p.pk();
}

int  Transform_table_el::t_b(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    return p.pk();
}

int  Transform_table_el::t_l(int e) {
    Pack_el p(e1);
    p.unpk(e);
    p.cycle(A_ED_BL, A_ED_DL, A_ED_FL, A_ED_UL);
    return p.pk();
}

// =========================================================================

int  Transform_table_cp::t_u(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_URB, B_CR_UBL, B_CR_ULF, B_CR_UFR);
    return p.pk();
}

int  Transform_table_cp::t_f(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_DFL, B_CR_DRF, B_CR_UFR, B_CR_ULF);
    return p.pk();
}

int  Transform_table_cp::t_r(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_DRF, B_CR_DBR, B_CR_URB, B_CR_UFR);
    return p.pk();
}

int  Transform_table_cp::t_d(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_DFL, B_CR_DLB, B_CR_DBR, B_CR_DRF);
    return p.pk();
}

int  Transform_table_cp::t_b(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_DBR, B_CR_DLB, B_CR_UBL, B_CR_URB);
    return p.pk();
}

int  Transform_table_cp::t_l(int c) {
    Pack_cp p(c1);
    p.unpk(c);
    p.cycle(B_CR_DLB, B_CR_DFL, B_CR_ULF, B_CR_UBL);
    return p.pk();
}

// =========================================================================

int  Transform_table_ep::t_u(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_UR, B_ED_UB, B_ED_UL, B_ED_UF);
    return p.pk();
}

int  Transform_table_ep::t_d(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_DL, B_ED_DB, B_ED_DR, B_ED_DF);
    return p.pk();
}

int  Transform_table_ep::t_f2(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_UF, B_ED_DF);
    return p.pk();
}

int  Transform_table_ep::t_r2(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_UR, B_ED_DR);
    return p.pk();
}

int  Transform_table_ep::t_b2(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_UB, B_ED_DB);
    return p.pk();
}

int  Transform_table_ep::t_l2(int e) {
    Pack_ep p(e1);
    p.unpk(e);
    p.cycle(B_ED_UL, B_ED_DL);
    return p.pk();
}

// =========================================================================

int  Transform_table_mp::t_u(int m) {
    return m;  //  !
}

int  Transform_table_mp::t_d(int m) {
    return m;  //  !
}

int  Transform_table_mp::t_f2(int m) {
    Pack_mp p(e1);
    p.unpk(m);
    p.cycle(B_MD_FR, B_MD_FL);
    return p.pk();
}

int  Transform_table_mp::t_r2(int m) {
    Pack_mp p(e1);
    p.unpk(m);
    p.cycle(B_MD_FR, B_MD_BR);
    return p.pk();
}

int  Transform_table_mp::t_b2(int m) {
    Pack_mp p(e1);
    p.unpk(m);
    p.cycle(B_MD_BR, B_MD_BL);
    return p.pk();
}

int  Transform_table_mp::t_l2(int m) {
    Pack_mp p(e1);
    p.unpk(m);
    p.cycle(B_MD_FL, B_MD_BL);
    return p.pk();
}

// =========================================================================

int  Transform_table_se::tu_u(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_UR, A_ED_UB, A_ED_UL, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::tu_f(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::tu_r(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_FR, A_ED_DR, A_ED_BR, A_ED_UR);
    return p.pk();
}

int  Transform_table_se::tu_d(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_DL, A_ED_DB, A_ED_DR, A_ED_DF);
    return p.pk();
}

int  Transform_table_se::tu_b(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    return p.pk();
}

int  Transform_table_se::tu_l(int s) {
    Pack_use p(e1);
    p.unpk(s);
    p.cycle(A_ED_BL, A_ED_DL, A_ED_FL, A_ED_UL);
    return p.pk();
}

int  Transform_table_se::td_u(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_UR, A_ED_UB, A_ED_UL, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::td_f(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::td_r(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_FR, A_ED_DR, A_ED_BR, A_ED_UR);
    return p.pk();
}

int  Transform_table_se::td_d(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_DL, A_ED_DB, A_ED_DR, A_ED_DF);
    return p.pk();
}

int  Transform_table_se::td_b(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    return p.pk();
}

int  Transform_table_se::td_l(int s) {
    Pack_dse p(e1);
    p.unpk(s);
    p.cycle(A_ED_BL, A_ED_DL, A_ED_FL, A_ED_UL);
    return p.pk();
}

int  Transform_table_se::tm_u(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_UR, A_ED_UB, A_ED_UL, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::tm_f(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_FL, A_ED_DF, A_ED_FR, A_ED_UF);
    return p.pk();
}

int  Transform_table_se::tm_r(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_FR, A_ED_DR, A_ED_BR, A_ED_UR);
    return p.pk();
}

int  Transform_table_se::tm_d(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_DL, A_ED_DB, A_ED_DR, A_ED_DF);
    return p.pk();
}

int  Transform_table_se::tm_b(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_BR, A_ED_DB, A_ED_BL, A_ED_UB);
    return p.pk();
}

int  Transform_table_se::tm_l(int s) {
    Pack_mse p(e1);
    p.unpk(s);
    p.cycle(A_ED_BL, A_ED_DL, A_ED_FL, A_ED_UL);
    return p.pk();
}

