#ifndef H_AC_H_
#define H_AC_H_

struct options {
  int metric;       // metrics (lengths of moves)
  int all_search;   // whether to search for all shortest sequences or only for 1
  int opt_search;   // whether to search only for optimal sequences or not
  int slice_turn;   // whether the slice-turns are allowed
};

#endif
