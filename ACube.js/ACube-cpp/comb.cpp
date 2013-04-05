
#include <stdio.h>
#include "comb.h"

// =========================================================================
   Comb::Comb(int n): n(n), k(n),
   _f_n(_fac_n(n)), _f_k(_fac_n(n)), _c_nk(_comb_nk(n, n)), _v_nk(_var_nk(n, n))
// -------------------------------------------------------------------------
{
  clear();
}

// =========================================================================
   Comb::Comb(int n, int k): n(n), k(k),
   _f_n(_fac_n(n)), _f_k(_fac_n(k)), _c_nk(_comb_nk(n, k)), _v_nk(_var_nk(n, k))
// -------------------------------------------------------------------------
{
  clear();
}

// =========================================================================
   void  Comb::print()
// -------------------------------------------------------------------------
{
  int i;
  printf("%2i:", n);
  for (i = 0; i < n; i++)
    printf(" %2i", a[i]);
}

// =========================================================================
   void  Comb::clear()
// -------------------------------------------------------------------------
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = 0;
}

// =========================================================================
   void  Comb::fill(int b[])
// -------------------------------------------------------------------------
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = b[i];
}

// =========================================================================
   int  Comb::_fac_n(int n)
// -------------------------------------------------------------------------
// computes factorial of n (n!)
{
  int i, x = 1;

  for (i = n; i > 1; i--)
    x *= i;
  return x;
}

// =========================================================================
   int  Comb::_comb_nk(int n, int k)
// -------------------------------------------------------------------------
// computes combinational number n over k (n!/((n-k)!*k!)
{
  int i, j, x = 1, y = 1;

  for (i = n, j = k; j > 0; i--, j--) {
    x *= i;
    y *= j;
  }
  return x / y;
}

// =========================================================================
   int  Comb::_var_nk(int n, int k)
// -------------------------------------------------------------------------
// computes variational number n over k (n!/(n-k)!)
{
  int i, j, x = 1;

  for (i = n, j = k; j > 0; i--, j--) {
    x *= i;
  }
  return x;
}

// =========================================================================
   int  Comb::fac_n()
// -------------------------------------------------------------------------
// computes factorial of n (n!) (it is already precomputed)
{
  return _f_n;
}

// =========================================================================
   int  Comb::fac_k()
// -------------------------------------------------------------------------
// computes factorial of k (k!) (it is already precomputed)
{
  return _f_k;
}

// =========================================================================
   int  Comb::comb_nk()
// -------------------------------------------------------------------------
// computes combination of n over k (n!/((n-k)!*k!) (it is already precomputed)
{
  return _c_nk;
}

// =========================================================================
   int  Comb::var_nk()
// -------------------------------------------------------------------------
// computes variation of n over k (n!/(n-k)!) (it is already precomputed)
{
  return _v_nk;
}

// =========================================================================
   int  Comb::perm_n_pk()
// -------------------------------------------------------------------------
// maps int array to the permutation order
// the least number: 0123...; the largest one: ...3210
{
  int i, j, x = 0;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++)
      if (a[j] < a[i])
        x++;
    x *= n - i - 1;
  }
  return x;
}

// =========================================================================
   void  Comb::perm_n_unpk(int x)
// -------------------------------------------------------------------------
// maps order of permutation to the permutation array of numbers 0,1,..,n-1
{
  int i, j;

  a[n - 1] = 0;
  for (i = n - 2; i >= 0; i--) {
    a[i] = x % (n - i);
    x /= n - i;
    for (j = n - 1; j > i; j--)
      if (a[j] >= a[i])
        a[j]++;
  }
}

// =========================================================================
   int  Comb::mix_perm_n_pk()
// -------------------------------------------------------------------------
// the same as perm_n_pk but packs only non-zero numbers
{
  int i, j, x = 0, m;

  for (i = 0; i < n - 1; i++) {
    if (a[i] == 0)
      continue;
    m = 0;
    for (j = i + 1; j < n; j++)
      if (a[j]) {
        m++;
        if (a[j] < a[i])
          x++;
      }
    if (m <= 1) // only one item remains and it doesn't affect the result
      return x;
    x *= m;
  }
  return 0;     // if we have only zeroes in a[i]
}

// =========================================================================
   void  Comb::mix_perm_n_unpk(int x)
// -------------------------------------------------------------------------
// the same as perm_n_unpk but depacks only to non-zero items of a[]
{
  int i, j, m = 0;

  for (i = n - 1; i >= 0; i--) {
    if (a[i] == 0)
      continue;
    m++;
    a[i] = x % m + 1;
    x /= m;
    for (j = n - 1; j > i; j--)
      if (a[j] && a[j] >= a[i])
        a[j]++;
  }
}

// =========================================================================
   int Comb::comb_nk_pk()
// -------------------------------------------------------------------------
// packs the binary array with k 1s to its order (C(n,k))
// the least number: 00..01..11; the largest one: 11..10..00
{
  int i, j, x = 0;

  for (i = 0, j = k; i < n - j; i++)
    if (a[i])
      x += _comb_nk(n - i - 1, j--);
  return x;
}

// =========================================================================
   void  Comb::comb_nk_unpk(int x)
// -------------------------------------------------------------------------
// depacks order of comb. to the binary array with k 1s
{
  int i, j, c;

  for (i = 0, j = k; i < n; i++) {
    if ((c = _comb_nk(n - i - 1, j)) <= x) {
      x -= c;
      a[i] = 1;
      j--;
    }
    else
      a[i] = 0;
  }
}

// =========================================================================
   int  Comb::var_nk_pk()
// -------------------------------------------------------------------------
// packs variation of k numbers 0..k-1 to its order
// the least number: ..0012.., .., ..00..21; the largest one: ..2100..
{
  return comb_nk_pk() * fac_k() + mix_perm_n_pk();
  // combination x k! + (sub)permutation
}

// =========================================================================
   void  Comb::var_nk_unpk(int x)
// -------------------------------------------------------------------------
// depakuje poradi variace V(n,k) do pole 'a'
{
  comb_nk_unpk(x / fac_k());      // order of combination
  mix_perm_n_unpk(x % fac_k());   // order of (sub)permutation
}

// =========================================================================
   int  Comb::check_perm_n()
// -------------------------------------------------------------------------
// checks whether a[] contains proper permutation of the numbers 0..n-1
// 1 - bad permutation, 0 - good one
{
  int i, c[MAX_COMB_N];

  for (i = 0; i < n; i++)
    c[i] = 0;
  for (i = 0; i < n; i++) {
    if (a[i] < 0 || a[i] >= n) // the numbers must be in this range
      return 1;
    c[a[i]]++;
  }
  for (i = 0; i < n; i++) // each number must appear exactly once
    if (c[i] != 1)
      return 1;
  return 0;
}

// =========================================================================
   int  Comb::check_var_n()
// -------------------------------------------------------------------------
// checks whether a[] contains proper variation of the numbers > 0
// 1 - bad variation, 0 - good one
{
  int i, c[MAX_COMB_N];

  for (i = 0; i < n; i++)
    c[i] = 0;
  for (i = 0; i < n; i++) {
    if (a[i] < 0 || a[i] > n)
      return 1;
    if (a[i])
      c[a[i] - 1]++;
  }
  for (i = 0; i < n; i++) // each number must appear at most once
    if (c[i] > 1)
      return 1;
  return 0;
}

// =========================================================================
   int  Comb::parity_of_perm_n()
// -------------------------------------------------------------------------
// even number of swaps... 0, odd... 1
{
  int i, j, p = 0;

  for (i = 0; i < n - 1; i++)   // how many pairs are not in the right order
    for (j = i + 1; j < n; j++) // modulo 2
      if (a[i] > a[j])
        p = 1 - p;
  return p;
}

// =========================================================================
   int  Comb::parity_of_var_n()
// -------------------------------------------------------------------------
// even number of swaps... 0, odd... 1, ?... -1, any... -2
{
  int i, j, p = 0;

  for (i = 0; i < n; i++)
    if (a[i] == 0)
      if (p == -1)
        return -2;
      else
        p = -1;
  if (p == -1)
    return -1;
  // next code is the same as for the previous function
  for (i = 0; i < n - 1; i++)
    for (j = i + 1; j < n; j++)
      if (a[i] > a[j])
        p = 1 - p;
  return p;
}

// =========================================================================
   void  Comb::cycle(int i0, int i1)
// -------------------------------------------------------------------------
{
  int t = a[i0];
  a[i0] = a[i1];
  a[i1] = t;
}

// =========================================================================
   void  Comb::cycle(int i0, int i1, int i2, int i3) // 0<1<2<3<0
// -------------------------------------------------------------------------
{
  int t = a[i0];
  a[i0] = a[i1];
  a[i1] = a[i2];
  a[i2] = a[i3];
  a[i3] = t;
}

