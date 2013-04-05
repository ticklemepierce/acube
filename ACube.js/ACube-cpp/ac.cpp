// =========================================================================
//  implementation of the kociemba's sub-optimal 2-phase algorithm
// =========================================================================
//  programmed by Jelinek Josef as the university project in 2001
//  email: gloom@email.cz
//  www:   http://cube.misto.cz
// =========================================================================
//  programmed in the DJGPP development environment for M$ D0$
// =========================================================================
//  name: "ACube", ver: 2.5 (08/27/2001)
// =========================================================================
//  known bug: ! ! ! ! @? @? @? @? !! +! ! ! ! @? @? @? @? doesn't work...
//  this is now fixed
// =========================================================================

#include <stdio.h>
#include <stdlib.h>
#include "ac.h"
#include "const.h"
#include "cube.h"

// =========================================================================
   void  options(struct options *opts, int c, char *s[])
// -------------------------------------------------------------------------
// reading of the command-line arguments
{
  int i, j;

  opts->metric = FACE_TURN_METRIC;
  opts->all_search = 0;
  opts->opt_search = 0;
  opts->slice_turn = 0;

  for (i = 1; i < c; i++) {
    for (j = 0; s[i][j]; j++) {
      switch (s[i][j]) {
        case '?':
        case 'h':
          fprintf(stderr, "options:\n"
            " q - quarter-turn metrics\n"
            " f - face-turn metrics (default)\n"
            " s - slice-turn metrics\n"
            " c - slice-turns allowed\n"
            " a - search for all sequences\n"
            " o - search only for optimal sequences\n");
          exit(0);
          break;
        case 'a':
          opts->all_search = 1;
          fprintf(stderr, "All search ON.\n");
          break;
        case 'o':
          opts->opt_search = 1;
          fprintf(stderr, "Optimal search ON.\n");
          break;
        case 'q':
          opts->metric = QUARTER_TURN_METRIC;
          fprintf(stderr, "Quarter-turn metrics ON.\n");
          break;
        case 'f':
          opts->metric = FACE_TURN_METRIC;
          fprintf(stderr, "Face-turn metrics ON.\n");
          break;
        case 's':
          opts->metric = SLICE_TURN_METRIC;
          fprintf(stderr, "Slice-turn metrics ON.\n");
          break;
        case 'c':
          opts->slice_turn = 1;
          fprintf(stderr, "Slice-turns ON.\n");
          break;
        default:
          fprintf(stderr, "Invalid option '%c'.\n", *s[i]);
      }
    }
  }
  fprintf(stderr, "\n");
}

// Shared state!
static struct options opts;

extern "C" void solve(char* pos) {
  Cube cube;
  cube.init(opts, pos);
  cube.solve(); // search for the solution
}

extern "C" void solve_wrap() {
  char *pos = "UF UR UB UL DF DR DB DL FR FL BR BL UFR URB UBL ULF DRF DFL DLB DBR";
  solve(pos);
}

// =========================================================================
int  main(int argc, char *argv[])
// -------------------------------------------------------------------------
{

  // creating of the new cube structure
  // read command-line arguments to the opts structure
  options(&opts, argc, argv);
  //go_wrap();
  printf("Initialized.");
  return 0;
}

