#ifndef H_CUBE_H_
#define H_CUBE_H_

#include "const.h"
#include "ac.h"
#include "cubestat.h"
#include "sol.h"

// =========================================================================
// This module handles input of the cube state from standard input
// and preprocessing of the cube state
// =========================================================================

class Cube {
  int e[12];   // locations and orientations of the edges
  int c[8];    // locations and orientations of the corners
  int ep[12];  // locations of the edges
  int cp[8];   // locations of the corners
  int eo[12];  // orientations of the edges
  int co[8];   // orientations of the corners
  int ep1[12]; // mark of locations of the edges
  int cp1[8];  // mark of locations of the corners
  int eo1[12]; // mark of orientations of the edges
  int co1[8];  // mark of orientations of the corners
  Solution *sol;          // 2-phase solving algorithm
  struct CubeState state; // characteristic values of the cube state
  struct options opts;    // various options

  int   enter(char *);       // fills e*[], c*[]
  int   check();       // tests e*[], c*[]
  void  preprocess();  // fills state from e*[], c*[]
  int   readkey();     // read the key code for continuation

 public:
  int  init(struct options, char* pos); // reading, testing and preprocessing of the cube
  void solve();              // searching of the solution
};

#endif
