#ifndef H_SOL_H_
#define H_SOL_H_

#include "const.h"
#include "ac.h"
#include "cubestat.h"
#include "turn.h"
#include "transf.h"
#include "prune.h"

// =========================================================================
// this module handles the basic algorithms for the solution of the cube
// the solution is divided into two phases
// because of the speed the functions that are defined recursively
// are implemented as non recursively using the explicit stack
// =========================================================================

struct Phase_node {
  // universal values for all phases
  int  r_d;  // the rest depth
  int  tw;   // the twist number
  Word twl;  // the next moves possibilities
};

struct Phase1_node : Phase_node {
  // the values for the phase 1
  Word ct;   // the twists of the corners
  Long ef;   // the flips of the edges
  Word el;   // the unordered locations of the middle layer edges
  Word cp;   // the permutation of the corners (mainly for the optimal solving)
  Word u_se; // the positions of the upper edges
  Word d_se; // the positions of the lower edges
  Word m_se; // the positions of the middle edges
};

struct Phase2_node : Phase_node {
  // the values for the phase 2
  Word cp;   // the permutation of the corners
  Word ep;   // the permutation of the upper and lower edges
  Word mp;   // the permutation of the middle edges
};


class Solution {
  Transform_table  *tr;
  Pruning_table    *pr;
  Turn_table       *tn;   // the table of move lengths
  TwistList_table  *ls;   // the table of valid sequences of moves
  struct CubeState state; // the cube state values

  int         min_sol;    // a length of a shortest solution
  int         ph2_sol;    // the maximal allowed depth for the phase 2
  Phase1_node s1[BIG + 1];// the move and state stack for the phase 1
  Phase2_node s2[BIG + 1];// the move and state stack for the phase 2
  int         n1;         // the current size of the stack for the phase 1
  int         n2;         // the current size of the stack for the phase 2
  int         metric;
  int         all_search; // search for all moves on the current depth
  int         opt_search; // only search for the optimal sequences 
  int         slice_turn; // slice moves allowed?
  // some statistics variables
  Long        sol2, sol2x;
  Long        aprn, bprn, apry, bpry;

  void p1_solve();
  void op_search(int);
  void p1_search(int);
  inline void p2_solve();
  inline void p2_search(int);
  void output();

 public:
  void solve(struct CubeState st, struct options *opt) {
    state      = st;              // the initial cube state
    metric     = opt->metric;
    all_search = opt->all_search;
    opt_search = opt->opt_search;
    slice_turn = opt->slice_turn;
    p1_solve();                   // the phase 1 entry
  }
  Solution(Transform_table *tr, Pruning_table *pr,
           Turn_table *tn, TwistList_table *ls):
          tr(tr), pr(pr), tn(tn), ls(ls) {}
};

#endif
