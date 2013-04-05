#ifndef H_COMB_H_
#define H_COMB_H_

#ifndef MAX_COMB_N
#define MAX_COMB_N 12
#endif

// =========================================================================
// this module handles common algorithms for packing and unpacking
// permutations, variations and combinations of int arrays
// so as their representation is as compact and efficient as it can
// =========================================================================

class Comb {
 public:
  int a[MAX_COMB_N];

 protected:
  const int n; // number of items
  const int k; // number of chosen items

 private:
  const int _f_n, _f_k, _c_nk, _v_nk; // precomputed values

 public:
  void print();
  void clear();
  void fill(int []);
  static int  _fac_n(int n);
  static int  _comb_nk(int n, int k);
  static int  _var_nk(int n, int k);
  int  fac_n();
  int  fac_k();
  int  comb_nk();
  int  var_nk();
  int  perm_n_pk();
  void perm_n_unpk(int);
  int  mix_perm_n_pk();
  void mix_perm_n_unpk(int);
  int  comb_nk_pk();
  void comb_nk_unpk(int);
  int  var_nk_pk();
  void var_nk_unpk(int);

  int  check_perm_n();
  int  check_var_n();
  int  parity_of_perm_n();
  int  parity_of_var_n();

  void cycle(int, int);
  void cycle(int, int, int, int);

  Comb(int n);
  Comb(int n, int k);
};

#endif
