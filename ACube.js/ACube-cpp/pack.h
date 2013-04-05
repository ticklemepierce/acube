#ifndef H_PACK_H_
#define H_PACK_H_

#include "const.h"
#include "comb.h"

// =========================================================================
// this module handles packing and depacking of the specific parts of
// the cube with the particular properties
// it uses module 'comb'
// =========================================================================

// corner twists
class Pack_ct : public Comb {  // upto A_N_CT / A_M_CT
  int o; // which corners are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int c);
  void adjust(int, int, int, int);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_ct(int o): Comb(8, act(o)), o(o) {}
};

// edge flips
class Pack_ef : public Comb {  // upto A_N_EF / A_M_EF
  int o; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int e);
  void adjust(int, int, int, int);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_ef(int o): Comb(12, act(o)), o(o) {}
};

// middle layer edge locations
class Pack_el : public Comb {  // upto A_N_EL
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int e);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_el(int p): Comb(12, act(p)), p(p) {}
};

// corner permutations
class Pack_cp : public Comb {  // upto B_N_CP
  int p; // which corners are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int c);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_cp(int p): Comb(8, act(p)), p(p) {}
};

// top and bottom layer edge permutations
class Pack_ep : public Comb {  // upto B_N_EP
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int e);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_ep(int p): Comb(8, act(p)), p(p) {}
  friend class Pack_uhe;
  friend class Pack_dhe;
};

// middle layer edge permutations
class Pack_mp : public Comb {  // upto B_N_MP
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int m);
  int  len();
  int  startlen();
  int  start(int x);
  Pack_mp(int p): Comb(4, act(p)), p(p) {}
  //friend class Pack_uhe;
  //friend class Pack_dhe;
};

// top layer edges ordered placing
class Pack_use : public Comb {  // upto N_SE
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int s);
  int  len();
  int  startlen();
  int  start(int x);
  int  to_uhe(int s); // to_mp: (N_SE) --> (N_HE)
  int  is_p2(int s);
  Pack_use(int p): Comb(12, act(p)), p(p) {}
};

// bottom layer edges ordered placing
class Pack_dse : public Comb {  // upto N_SE
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int s);
  int  len();
  int  startlen();
  int  start(int x);
  int  to_dhe(int s); // to_he: (N_SE) --> (N_HE)
  int  is_p2(int s);
  Pack_dse(int p): Comb(12, act(p)), p(p) {}
};

// middle layer edges ordered placing
class Pack_mse : public Comb {  // upto N_SE
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int s);
  int  len();
  int  startlen();
  int  start(int x);
  int  to_mp(int s); // to_mp: (N_SE) --> (N_ME = B_N_MP)
  Pack_mse(int p): Comb(12, act(p)), p(p) {}
};

// top layer edges ordered placing in the top and bottom layers
class Pack_uhe : public Comb {  // upto N_HE
  int p; // which edges are specified
  static int act(int x);
 public:
  int  pk();
  void unpk(int m);
  int  len();
  int  startlen();
  int  start(int x);
  int  to_ep(int uh, int dh); // to_ep: (N_HE x N_HE) --> (N_EP)
  Pack_uhe(int p): Comb(8, act(p)), p(p) {}
  //friend class Pack_dhe;
};

// bottom layer edges ordered placing in the top and bottom layers
class Pack_dhe : public Comb {  // upto N_HE
  int p;
  static int act(int x);
 public:
  int  pk();
  void unpk(int h);
  int  len();
  int  startlen();
  int  start(int x);
  //int  to_ep(int dh, int uh); // to_ep: (N_HE x N_HE) --> (N_EP)
  Pack_dhe(int p): Comb(8, act(p)), p(p) {}
  //friend class Pack_uhe;
};

#endif
