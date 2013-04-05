#ifndef H_PRUNE_H_
#define H_PRUNE_H_

#include "const.h"
#include "turn.h"
#include "transf.h"
#include "cubestat.h"

// =========================================================================
// this module handles state tree pruning using lowerbound heuristic
// function
// =========================================================================

class Pruning_table_ef_xx {
  Byte a[A_M_EF];
  int eo;
 public:
  int dist(int ef) { return a[ef]; }
  Pruning_table_ef_xx(Transform_table *tr, Turn_table *tn, int eo);
};

class Pruning_table_ct_ef {
  Byte a[A_N_CT][A_N_EF];
  int co, eo;
 public:
  int dist(int ct, int ef) { return a[ct][ef]; }
  Pruning_table_ct_ef(Transform_table *tr, Turn_table *tn, int co, int eo);
};

class Pruning_table_ct_el {
  Byte a[A_M_CT][A_N_EL];
  int co, e1;
 public:
  int dist(int ct, int el) { return a[ct][el]; }
  Pruning_table_ct_el(Transform_table *tr, Turn_table *tn, int co, int e1);
};

class Pruning_table_ef_el {
  Byte a[A_N_EF][A_N_EL];
  int eo, e1;
 public:
  int dist(int ef, int el) { return a[ef][el]; }
  Pruning_table_ef_el(Transform_table *tr, Turn_table *tn, int eo, int e1);
};


class Pruning_table_cp_xx {
  Byte a[A_N_CP];
  int c1;
 public:
  int dist(int cp) { return a[cp]; }
  Pruning_table_cp_xx(Transform_table *tr, Turn_table *tn, int c1);
};

class Pruning_table_us_el {
  Byte a[A_N_SE][A_N_EL];
  int e1;
 public:
  int dist(int us, int el) { return a[us][el]; }
  Pruning_table_us_el(Transform_table *tr, Turn_table *tn, int e1);
};

class Pruning_table_ds_el {
  Byte a[A_N_SE][A_N_EL];
  int e1;
 public:
  int dist(int ds, int el) { return a[ds][el]; }
  Pruning_table_ds_el(Transform_table *tr, Turn_table *tn, int e1);
};

class Pruning_table_ms_xx {
  Byte a[A_N_SE];
  int e1;
 public:
  int dist(int ms) { return a[ms]; }
  Pruning_table_ms_xx(Transform_table *tr, Turn_table *tn, int e1);
};


class Pruning_table_mp_cp {
  Byte a[B_N_MP][B_N_CP];
  int e1, c1;
 public:
  int dist(int mp, int cp) { return a[mp][cp]; }
  Pruning_table_mp_cp(Transform_table *tr, Turn_table *tn, int e1, int c1);
};

class Pruning_table_mp_ep {
  Byte a[B_N_MP][B_N_EP];
  int e1;
 public:
  int dist(int mp, int ep) { return a[mp][ep]; }
  Pruning_table_mp_ep(Transform_table *tr, Turn_table *tn, int e1);
};


class Pruning_table {
  int ct_big, ef_big;
  Pruning_table_ef_xx *ef_xx;
  Pruning_table_ct_ef *ct_ef;
  Pruning_table_ct_el *ct_el;
  Pruning_table_ef_el *ef_el;
  Pruning_table_cp_xx *cp_xx;
  Pruning_table_us_el *us_el;
  Pruning_table_ds_el *ds_el;
  Pruning_table_ms_xx *ms_xx;
  Pruning_table_mp_cp *mp_cp;
  Pruning_table_mp_ep *mp_ep;

  inline int max(int a, int b) {
    return a > b ? a : b;
  }
  inline int max(int a, int b, int c) {
    return max(max(a, b), c);
  }
  inline int max(int a, int b, int c, int d) {
    return max(max(a, b), max(c, d));
  }
 public:
  inline int a_dist(int ct, int ef, int el) {
    if (ef_big)
      return max(ct_el->dist(ct, el), ef_xx->dist(ef));
    if (ct_big)
      return max(ct_el->dist(ct, el), ef_el->dist(ef, el));
    return max(ct_el->dist(ct, el), ef_el->dist(ef, el), ct_ef->dist(ct, ef));
  }
  inline int a_dist(int ct, int ef, int el, int cp, int us, int ds, int ms) {
    return max(a_dist(ct, ef, el),
               max(cp_xx->dist(cp), ms_xx->dist(ms),
                   us_el->dist(us, el), ds_el->dist(ds, el)));
  }
  inline int b_dist(int cp, int ep, int mp) {
    return max(mp_cp->dist(mp, cp), mp_ep->dist(mp, ep));
  }
  inline bool a_bigger(int ct, int ef, int el, int d) {
    if (ct_el->dist(ct, el) > d) return 1;
    if (ef_big) {
      if (ef_xx->dist(ef) > d) return 1;
      return 0;
    }
    if (ef_el->dist(ef, el) > d) return 1;
    if (ct_big) return 0;
    if (ct_ef->dist(ct, ef) > d) return 1;
    return 0;
  }
  inline bool a_bigger(int ct, int ef, int el, int cp,
                       int us, int ds, int ms, int d) {
    if (a_bigger(ct, ef, el, d)) return 1;
    if (cp_xx->dist(cp) > d) return 1;
    if (us_el->dist(us, el) > d) return 1;
    if (ds_el->dist(ds, el) > d) return 1;
    if (ms_xx->dist(ms) > d) return 1;
    return 0;
  }
  inline bool b_bigger(int cp, int ep, int mp, int d) {
    if (mp_cp->dist(mp, cp) > d) return 1;
    if (mp_ep->dist(mp, ep) > d) return 1;
    return 0;
  }
  Pruning_table(Transform_table *, Turn_table *, struct CubeState, int);
  ~Pruning_table();
};

#endif
