#include <string.h>
#include <stdio.h>

#include "cube.h"
#include "sol.h"
#include "cubestat.h"
#include "comb.h"
#include "pack.h"
#include "transf.h"
#include "prune.h"
#include "turn.h"

static char *ed_str[] = {  // edges with all orientations
  "UF", "UR", "UB", "UL", "DF", "DR", "DB", "DL", "FR", "FL", "BR", "BL",
  "FU", "RU", "BU", "LU", "FD", "RD", "BD", "LD", "RF", "LF", "RB", "LB"};

static char *cr_str[] = {  // corners with all orientations
  "UFR", "URB", "UBL", "ULF", "DRF", "DFL", "DLB", "DBR",
  "FRU", "RBU", "BLU", "LFU", "RFD", "FLD", "LBD", "BRD",
  "RUF", "BUR", "LUB", "FUL", "FDR", "LDF", "BDL", "RDB",
  // for easier input is orientation determined only by the first character
  "URF", "UBR", "ULB", "UFL", "DFR", "DLF", "DBL", "DRB",
  "FUR", "RUB", "BUL", "LUF", "RDF", "FDL", "LDB", "BDR",
  "RFU", "BRU", "LBU", "FLU", "FRD", "LFD", "BLD", "RBD"};

// =========================================================================
// The functions for processing the cube:
// - reading from the standard input
// - testing of the correctness and validity of the given configuration
// - computing of the particular characteristics of the given cube
// =========================================================================
   int  Cube::init(struct options o, char* pos)
// -------------------------------------------------------------------------
{
  int stat;

  opts = o;
  stat = enter(pos);
  if (stat == 2) {
    if (readkey())
      return 1;
  }
  else {
    if (stat)
      return stat;
    if ((stat = check()))
      return stat;
    preprocess();
  }
  return 0;
}

// =========================================================================
   void  Cube::solve()
// -------------------------------------------------------------------------
{
  Transform_table *tr = new Transform_table(state, opts.opt_search);
  Turn_table      *tn = new Turn_table(opts.metric);
  Pruning_table   *pr = new Pruning_table(tr, tn, state, opts.opt_search);
  TwistList_table *ls = new TwistList_table();

  sol = new Solution(tr, pr, tn, ls);
  sol->solve(state, &opts);

  delete sol;
  delete tr;
  delete tn;
  delete pr;
  delete ls;
}

// =========================================================================
   int  Cube::enter(char *pos)
// -------------------------------------------------------------------------
// This is not the ideal way of the defining of the cube state
// but I have not seen any better way for a terminal
{
  char *es[12], *cs[8];
  int i, j, stat;

  fprintf(stderr, "\nEnter cube (this is the solved one) or Q(quit), N(new), K(key):\n");
  fprintf(stderr, "UF UR UB UL DF DR DB DL FR FL BR BL  UFR URB UBL ULF DRF DFL DLB DBR\n");
  fprintf(stderr, "You can use also:\n"
                  " '!'(or.) '+!'(cw.) '-!'(c-cw.) '@!'(unor.) - on right pos.\n"
                  " '?' '+?' '-?' '@?' - unknown cubie on pos.\n"
                  " '!!' '@!!' '??' '@??' - repeat to the end of corners/edges\n"
                  " 'UF'(='-FU') 'FU'(='-UF') '@UF'(='@FU')\n"
                  " 'UFR'(='URF') 'FRU' 'RUF' '@UFR' '-UFR' '+UFR' ...\n");

  //sscanf("%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s")

  char str[256];
  strcpy(str, pos);

  // reading of the textual representation of the 12 edges
  for (i = 0; i < 12; i++) {
    if (i == 0)
      es[i] = strtok(str, " ");
    else
      es[i] = strtok(NULL, " ");

    printf("%s ", es[i]);
    fflush(stdout);

    if (strcmp(es[i], "Q") == 0 || strcmp(es[i], "q") == 0)
      return -1;
    if (strcmp(es[i], "K") == 0 || strcmp(es[i], "k") == 0)
      return 2;
    if (strcmp(es[i], "N") == 0 || strcmp(es[i], "n") == 0)
      return 1;
    if (strcmp(es[i], "!!") == 0) {
      for (j = i; j < 12; j++)
        strcpy(es[j], "!");
      break;
    }
    if (strcmp(es[i], "@!!") == 0) {
      for (j = i; j < 12; j++)
        strcpy(es[j], "@!");
      break;
    }
    if (strcmp(es[i], "??") == 0) {
      for (j = i; j < 12; j++)
        strcpy(es[j], "?");
      break;
    }
    if (strcmp(es[i], "@??") == 0) {
      for (j = i; j < 12; j++)
        strcpy(es[j], "@?");
      break;
    }
  }
  // reading of the textual representation of the 8 corners
  for (i = 0; i < 8; i++) {

    cs[i] = strtok(NULL, " ");

    printf("%s ", cs[i]);
    fflush(stdout);

    if (strcmp(cs[i], "Q") == 0 || strcmp(cs[i], "q") == 0)
      return -1;
    if (strcmp(es[i], "K") == 0 || strcmp(es[i], "k") == 0)
      return 2;
    if (strcmp(es[i], "N") == 0 || strcmp(es[i], "n") == 0)
      return 1;
    if (strcmp(cs[i], "!!") == 0) {
      for (j = i; j < 8; j++)
        strcpy(cs[j], "!");
      break;
    }
    if (strcmp(cs[i], "@!!") == 0) {
      for (j = i; j < 8; j++)
        strcpy(cs[j], "@!");
      break;
    }
    if (strcmp(cs[i], "??") == 0) {
      for (j = i; j < 8; j++)
        strcpy(cs[j], "?");
      break;
    }
    if (strcmp(cs[i], "@??") == 0) {
      for (j = i; j < 8; j++)
        strcpy(cs[j], "@?");
      break;
    }
  }

  stat = 0; // no error yet

  // filling of the locations and orientations of the edges
  // of the arrays e[12], eo*[12], ep*[12]
  // eo1[] is not completely filled (we don't know which edge is '@?')
  // so we fill a locations that are not set
  for (i = 0; i < 12; i++) {
    e[i] = 0;
    ep[i] = 0;
    eo[i] = 0;
    ep1[i] = 1;
    eo1[i] = -1;
  }
  for (i = 0; i < 12; i++) {
    if (strcmp(es[i], "!") == 0) {  // the correct edge on the correct place
      e[i] = i + 1;
      ep[i] = i + 1;
      eo[i] = 1;
      ep1[i] = 0;
      eo1[i] = 0;
      continue;
    }
    if (strcmp(es[i], "@!") == 0) { // the unoriented edge on the correct place
      e[i] = i + 1;
      ep[i] = i + 1;
      //eo[i] = 0;
      ep1[i] = 0;
      eo1[i] = 1;
      continue;
    }
    if (strcmp(es[i], "-!") == 0) { // the flipped edge on the correct place
      e[i] = i + 12 + 1;
      ep[i] = i + 1;
      eo[i] = 2;
      ep1[i] = 0;
      eo1[i] = 0;
      continue;
    }
    if (strcmp(es[i], "?") == 0) {  // an oriented unknown edge
      //e[i] = 0;
      //ep[i] = 0;
      eo[i] = 1;
      //ep1[?] = 1; // - ok
      //eo1[?] = 0; // - we will fix it later...
      continue;
    }
    if (strcmp(es[i], "@?") == 0) { // an unknown edge
      //e[i] = 0;
      //ep[i] = 0;
      //eo[i] = 0;
      //ep1[?] = 1; // - ok
      //eo1[?] = 1; // - we will fix it later...
      continue;
    }
    if (strcmp(es[i], "-?") == 0) { // an flipped unknown edge
      //e[i] = 0;
      //ep[i] = 0;
      eo[i] = 2;
      //ep1[?] = 1; // - ok
      //eo1[?] = 0; // - we will fix it later...
      continue;
    }
    if (es[i][0] == '@') {       // any orientation of the edge
      for (j = 0; j < 24; j++) { // get the edge's number
        if (strcmp(es[i] + 1, ed_str[j]) == 0) {
          e[i] = j % 12 + 1;
          ep[i] = (e[i] - 1) % 12 + 1;
          //eo[i] = 0;
          ep1[ep[i] - 1] = 0;
          eo1[ep[i] - 1] = 1;
          break;
        }
      }
      if (j == 24) { // no match
        fprintf(stderr, "Improper edge cubie: %s\n", es[i]);
        stat = 1; // error
      }
      continue;
    }
    if (es[i][0] == '-') {       // the edge is flipped
      for (j = 0; j < 24; j++) { // get the edge's number
        if (strcmp(es[i] + 1, ed_str[j]) == 0) {
          e[i] = (j + 12) % 24 + 1;
          ep[i] = (e[i] - 1) % 12 + 1;
          eo[i] = (e[i] - 1) / 12 + 1;
          ep1[ep[i] - 1] = 0;
          eo1[ep[i] - 1] = 0;
          break;
        }
      }
      if (j == 24) { // no match
        fprintf(stderr, "Improper edge cubie: %s\n", es[i]);
        stat = 1; // error
      }
      continue;
    }
    for (j = 0; j < 24; j++) {   // get the edge's number
      if (strcmp(es[i], ed_str[j]) == 0) {
        e[i] = j + 1;
        ep[i] = (e[i] - 1) % 12 + 1;
        eo[i] = (e[i] - 1) / 12 + 1;
        ep1[ep[i] - 1] = 0;
        eo1[ep[i] - 1] = 0;
        break;
      }
    }
    if (j == 24) { // no match
      fprintf(stderr, "Improper edge cubie: %s\n", es[i]);
      stat = 1; // error
    }
  }
  // this fixes the rest of the array eo1[]
  // it is not realy correct because this then represents
  // only one state from many states
  // but it is then correctly handled by the solving algorithm
  for (i = 0; i < 12; i++) {
    if (!ep[i]) {  // where we did not know the index to the eo1[]
      if (eo[i]) { // and the edge is oriented
        for (j = 0; j < 12 && eo1[j] != -1; j++);
        if (j == 12) {
          fprintf(stderr, "Bad edge format. (Mail me the input please.)\n");
          stat = 1;
        }
        else
          eo1[j] = 0;
      }
      else {       // where the edge is not oriented
        for (j = 0; j < 12 && eo1[j] != -1; j++);
        if (j == 12) {
          fprintf(stderr, "Bad edge format. (Mail me the input please.)\n");
          stat = 1;
        }
        else
          eo1[j] = 1;
      }
    }
  }
  for (i = 0; i < 12 && eo1[i] != -1; i++);
  if (i < 12) {
    fprintf(stderr, "Bad edge format. (Mail me the input please.)\n");
    stat = 1;
  }

  // filling of the locations and orientations of the corners
  // of the arrays c[8], co*[8], cp*[8]
  // co1[] is not completely filled (we don't know which corner is '@?')
  // so we fill a locations that are not set
  for (i = 0; i < 8; i++) {
    c[i] = 0;
    cp[i] = 0;
    co[i] = 0;
    cp1[i] = 1;
    co1[i] = -1;
  }
  for (i = 0; i < 8; i++) {
    if (strcmp(cs[i], "!") == 0) {  // the correct corner on the correct place
      c[i] = i + 1;
      cp[i] = i + 1;
      co[i] = 1;
      cp1[i] = 0;
      co1[i] = 0;
      continue;
    }
    if (strcmp(cs[i], "@!") == 0) { // the unoriented corner on the correct place
      c[i] = i + 1;
      cp[i] = i + 1;
      //co[i] = 0;
      cp1[i] = 0;
      co1[i] = 1;
      continue;
    }
    if (strcmp(cs[i], "+!") == 0) { // the twisted corner on the correct place
      c[i] = i + 8 + 1;
      cp[i] = i + 1;
      co[i] = 2;
      cp1[i] = 0;
      co1[i] = 0;
      continue;
    }
    if (strcmp(cs[i], "-!") == 0) { // the twisted corner on the correct place
      c[i] = i + 16 + 1;
      cp[i] = i + 1;
      co[i] = 3;
      cp1[i] = 0;
      co1[i] = 0;
      continue;
    }
    if (strcmp(cs[i], "?") == 0) {  // an oriented unknown corner
      //c[i] = 0;
      //cp[i] = 0;
      co[i] = 1;
      //cp1[?] = 1; // - ok
      //co1[?] = 0; // - we will fix it later
      continue;
    }
    if (strcmp(cs[i], "@?") == 0) { // an unknown corner
      //c[i] = 0;
      //cp[i] = 0;
      //co[i] = 0;
      //cp1[?] = 1; // - ok
      //co1[?] = 1; // - we will fix it later...
      continue;
    }
    if (strcmp(cs[i], "+?") == 0) { // an twisted unknown corner
      //c[i] = 0;
      //cp[i] = 0;
      co[i] = 2;
      //cp1[?] = 1; // - ok
      //co1[?] = 0; // - we will fix it later...
      continue;
    }
    if (strcmp(cs[i], "-?") == 0) { // an twisted unknown corner
      //c[i] = 0;
      //cp[i] = 0;
      co[i] = 3;
      //cp1[?] = 1; // - ok
      //co1[?] = 0; // - we will fix it later...
      continue;
    }
    if (cs[i][0] == '@') {       // any orientation of the corner
      for (j = 0; j < 48; j++) { // get the corner's number
        if (strcmp(cs[i] + 1, cr_str[j]) == 0) {
          c[i] = j % 24 % 8 + 1;
          cp[i] = (c[i] - 1) % 8 + 1;
          //co[i] = 0;
          cp1[cp[i] - 1] = 0;
          co1[cp[i] - 1] = 1;
          break;
        }
      }
      if (j == 48) { // no match
        fprintf(stderr, "Improper corner cubie: %s\n", cs[i]);
        stat = 1; // error
      }
      continue;
    }
    if (cs[i][0] == '+') {       // the corner is twisted
      for (j = 0; j < 48; j++) { // get the corner's number
        if (strcmp(cs[i] + 1, cr_str[j]) == 0) {
          c[i] = (j + 8) % 24 + 1;
          cp[i] = (c[i] - 1) % 8 + 1;
          co[i] = (c[i] - 1) / 8 + 1;
          cp1[cp[i] - 1] = 0;
          co1[cp[i] - 1] = 0;
          break;
        }
      }
      if (j == 48) { // no match
        fprintf(stderr, "Improper corner cubie: %s\n", cs[i]);
        stat = 1; // error
      }
      continue;
    }
    if (cs[i][0] == '-') {       // the corner is twisted
      for (j = 0; j < 48; j++) { // get the corner's number
        if (strcmp(cs[i] + 1, cr_str[j]) == 0) {
          c[i] = (j + 16) % 24 + 1;
          cp[i] = (c[i] - 1) % 8 + 1;
          co[i] = (c[i] - 1) / 8 + 1;
          cp1[cp[i] - 1] = 0;
          co1[cp[i] - 1] = 0;
          break;
        }
      }
      if (j == 48) { // no match
        fprintf(stderr, "Improper corner cubie: %s\n", cs[i]);
        stat = 1; // error
      }
      continue;
    }
    for (j = 0; j < 48; j++) {   // get the corner's number
      if (strcmp(cs[i], cr_str[j]) == 0) {
        c[i] = j % 24 + 1;
        cp[i] = (c[i] - 1) % 8 + 1;
        co[i] = (c[i] - 1) / 8 + 1;
        cp1[cp[i] - 1] = 0;
        co1[cp[i] - 1] = 0;
        break;
      }
    }
    if (j == 48) { // no match
      fprintf(stderr, "Improper corner cubie: %s\n", cs[i]);
      stat = 1; // error
    }
  }
  // this fixes the rest of the array co1[]
  // it is not realy correct because this then represents
  // only one state from many states
  // but it is then correctly handled by the solving algorithm
  for (i = 0; i < 8; i++) {
    if (!cp[i]) {  // where we didn't know the index to the co1[]
      if (co[i]) { // and the corner is oriented
        for (j = 0; j < 8 && co1[j] != -1; j++);
        if (j == 8) {
          fprintf(stderr, "Bad corner format. (Mail me the input please.)\n");
          stat = 1;
        }
        else
          co1[j] = 0;
      }
      else {       // where the corner is not oriented
        for (j = 0; j < 8 && co1[j] != -1; j++);
        if (j == 8) {
          fprintf(stderr, "Bad corner format. (Mail me the input please.)\n");
          stat = 1;
        }
        else
          co1[j] = 1;
      }
    }
  }
  for (i = 0; i < 8 && cp[i] != -1; i++);
  if (i < 8) {
    fprintf(stderr, "Bad corner format. (Mail me the input please.)\n");
    stat = 1;
  }

  printf("\n");
  fflush(stdout);

  return stat;
}

// =========================================================================
   int  Cube::check()
// -------------------------------------------------------------------------
{
  Comb pc(8), pe(12);
  int  i, f, t, stat, cp2, ep2;

  pc.fill(cp);
  pe.fill(ep);

  if (pc.check_var_n() || pe.check_var_n()) { // correct variations?
    fprintf(stderr, "Bad cubies.\n");
    return 1;
  }

  stat = 0;
  cp2 = pc.parity_of_var_n(); // parity of corner permutation (0, 1, -1, -2)
  ep2 = pe.parity_of_var_n(); // parity of edge permutation (0, 1, -1, -2)
  // for completely specified state parities must be the same
  // else must not depend on positions of min. 2 cubies of the same type
  if (cp2 == -1) {
    fprintf(stderr, "Specify position of last corner cubie!\n");
    stat = 1;
  }
  if (ep2 == -1) {
    fprintf(stderr, "Specify position of last edge cubie!\n");
    stat = 1;
  }
  if (cp2 >= 0 && ep2 >= 0 && cp2 != ep2) {
    fprintf(stderr, "Swap any two edge cubies or any two corner cubies!\n");
    stat = 1;
  }

  f = 0;
  for (i = 0; i < 12; i++) { // number of flips of edges
    if (!eo[i]) {
      f = -1;
      break;
    }
    f += eo[i] - 1;
  }
  if (f >= 0 && f & 1) { // must be even (edges are fliped in pairs)
    fprintf(stderr, "Flip any edge cubie!\n");
    stat = 1;
  }

  t = 0;
  for (i = 0; i < 8; i++) { // number of clockwise twists of corners
    if (!co[i]) {
      t = -1;
      break;
    }
    t += co[i] - 1;
  }
  if (t >= 0 && t % 3) { // t mod 3 must be 0
    fprintf(stderr, "Twist any corner cubie %sclockwise!\n",
      t % 3 == 1 ? "counter-" : "");
    stat = 1;
  }

  return stat;
}

// =========================================================================
   void  Cube::preprocess()
// -------------------------------------------------------------------------
{
  int i;
  int ea[12];
  int co2 = 0, eo2 = 0;
  int cp2 = 0, ep2 = 0;

  // new state (no continuation)
  state.min_sol = BIG;
  state.depth = 0;
  state.length = 0;
  for (i = 0; i < BIG; i++)
    state.twist[i] = -1;

  // corner-twist processing
  for (i = 0; i < 8; i++) {
    co2 |= co1[i] << i;
    cp2 |= cp1[i] << i;
  }
  // we have to specify which oriented corners are not located
  co2 |= cp2 << 8;
  state.co = co2;
  state.c1 = cp2;
  Pack_ct pct(co2);
  pct.fill(co);
  state.ct = pct.pk();

  // edge-flip processing
  for (i = 0; i < 12; i++) {
    eo2 |= eo1[i] << i;
    ep2 |= ep1[i] << i;
  }
  // we have to specify which oriented edges are not located
  eo2 |= ep2 << 12;
  state.eo = eo2;
  state.e1 = ep2;
  Pack_ef pef(eo2);
  pef.fill(eo);
  state.ef = pef.pk();

  // middle-slice-edge-location processing
  for (i = 0; i < 12; i++)
    if (ep[i])
      ea[i] = (ep[i] - 1) / 8; // values 0, 1 - enum dependent!!
    else
      ea[i] = 0;
  Pack_el pel(ep2);
  pel.fill(ea);
  state.el = pel.pk();

  // corner-permutation processing
  Pack_cp pcp(cp2);
  pcp.fill(cp);
  state.cp = pcp.pk();

  // middle-slice-edge-permutation processing
  for (i = 0; i < 12; i++) {
    if (ep[i]) {
      switch (ep[i] - 1) {
       case A_ED_FR:
        ea[i] = 1;
        break;
       case A_ED_FL:
        ea[i] = 2 - (ep2 >> A_ED_FR & 1);
        break;
       case A_ED_BR:
        ea[i] = 3 - (ep2 >> A_ED_FR & 1) - (ep2 >> A_ED_FL & 1);
        break;
       case A_ED_BL:
        ea[i] = 4 - (ep2 >> A_ED_FR & 1) - (ep2 >> A_ED_FL & 1) - (ep2 >> A_ED_BR & 1);
        break;
       default:
        ea[i] = 0;
      }
    }
    else
      ea[i] = 0;
  }
  Pack_mse mse(ep2);
  mse.fill(ea);
  state.m_se = mse.pk();

  // up-slice-edge-permutation processing
  for (i = 0; i < 12; i++) {
    if (ep[i]) {
      switch (ep[i] - 1) {
       case A_ED_UF:
        ea[i] = 1;
        break;
       case A_ED_UR:
        ea[i] = 2 - (ep2 >> A_ED_UF & 1);
        break;
       case A_ED_UB:
        ea[i] = 3 - (ep2 >> A_ED_UF & 1) - (ep2 >> A_ED_UR & 1);
        break;
       case A_ED_UL:
        ea[i] = 4 - (ep2 >> A_ED_UF & 1) - (ep2 >> A_ED_UR & 1) - (ep2 >> A_ED_UB & 1);
        break;
       default:
        ea[i] = 0;
      }
    }
    else
      ea[i] = 0;
  }
  Pack_use use(ep2);
  use.fill(ea);
  state.u_se = use.pk();

  // down-slice-edge-permutation processing
  for (i = 0; i < 12; i++) {
    if (ep[i]) {
      switch (ep[i] - 1) {
       case A_ED_DF:
        ea[i] = 1;
        break;
       case A_ED_DR:
        ea[i] = 2 - (ep2 >> A_ED_DF & 1);
        break;
       case A_ED_DB:
        ea[i] = 3 - (ep2 >> A_ED_DF & 1) - (ep2 >> A_ED_DR & 1);
        break;
       case A_ED_DL:
        ea[i] = 4 - (ep2 >> A_ED_DF & 1) - (ep2 >> A_ED_DR & 1) - (ep2 >> A_ED_DB & 1);
        break;
       default:
        ea[i] = 0;
      }
    }
    else
      ea[i] = 0;
  }
  Pack_dse dse(ep2);
  dse.fill(ea);
  state.d_se = dse.pk();
}

// =========================================================================
   int  Cube::readkey()
// -------------------------------------------------------------------------
{
  int i;

  state.min_sol = BIG;
  state.depth = 0;
  state.length = 0;
  for (i = 0; i < BIG; i++)
    state.twist[i] = -1;
  fprintf(stderr, "Enter the key (make sure the input is correct):\n");
  if (scanf("%lu%lu%hu%lu%hu%hu%hu%hu%hu", &state.co, &state.eo,
      &state.ct, &state.ef, &state.el, &state.cp,
      &state.u_se, &state.d_se, &state.m_se) != 9)
    return 1;
  state.c1 = (state.co >> 8) & 0xFF;
  state.e1 = (state.eo >> 12) & 0xFFF;
  if (scanf("%i", &state.min_sol) != 1)
    return 1;
  if (scanf("%i", &state.depth) != 1)
    return 1;
  if (scanf("%i", &state.length) != 1)
    return 1;
  for (i = 0; i < state.length; i++)
    if (scanf("%i", &state.twist[i]) != 1)
      return 1;
  return 0;
}

