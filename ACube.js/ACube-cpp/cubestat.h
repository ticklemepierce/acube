#ifndef H_CUBESTAT_H
#define H_CUBESTAT_H

// the structure describing the complete state of the cube
struct CubeState {
  Long co;       // wich corners are oriented
  Long eo;       // wich edges are oriented
  Word c1;       // which corners are placed
  Word e1;       // which edges are placed
  Word ct;       // corner orientations for phase 1
  Long ef;       // edge orientations for phase 1
  Word el;       // unordered placements of the middle-layer edges for phase 1
  Word cp;       // corner permutation for phase 2
  Word m_se;     // placements of the middle edges for computing the middle edges permutation for phase 2
  Word u_se;     // dtto but for ud-layers edge permutation for phase 2
  Word d_se;
  // values used for continuation of breaked computation
  int  min_sol;
  int  length;
  int  depth;
  int  twist[BIG];
};

#endif
