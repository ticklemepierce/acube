#ifndef H_TURN_H_
#define H_TURN_H_

#include "const.h"

// =========================================================================
// this module handles:
//  - support for different metrics
//  - which move is allowed after which move
//  - support for slice-turns outputs
// =========================================================================

class Turn_table {
  Byte a_l[A_N_TW];
  Byte b_l[B_N_TW];
  bool is_2[A_N_TW];
 public:
  inline int a_len(int t) { return a_l[t]; }
  inline int b_len(int t) { return b_l[t]; }
  inline int is_p2(int t) { return is_2[t]; }
  Turn_table(int metric);
};

class TwistList_table {
  Byte a_tl[A_N_TW][N_TWL];
  Byte b_tl[B_N_TW][N_TWL];
 public:
  inline bool a_invalid(int t, int l) { return TWL_INVALID == a_tl[t][l]; }
  inline bool b_invalid(int t, int l) { return TWL_INVALID == b_tl[t][l]; }
  inline int a_next(int t, int l) { return a_tl[t][l]; }
  inline int b_next(int t, int l) { return b_tl[t][l]; }
  TwistList_table();
};

class SliceTurnTransform_table {
  static Byte sttr[N_SYM][A_N_TW];  // outputs table
  static Byte sttd[N_SYM][A_N_TW];  // transitions table
  static Byte a[A_N_TW];            // conversion from phase 1 to 2
  static Byte b[B_N_TW];            // conversion from phase 2 to 1
  static int init_done;
  int i;                            // current state
 public:
  inline int a_get_do_tw(int t) {
    int u = sttr[i][t]; // return value
    i = sttd[i][t];     // transition to the next state (symetry)
    return u;
  }
  inline int b_get_do_tw(int t) { return a[a_get_do_tw(b[t])]; }
  SliceTurnTransform_table();
};

#endif
