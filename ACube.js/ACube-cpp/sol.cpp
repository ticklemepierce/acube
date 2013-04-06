
#include <stdio.h>
#include <signal.h>
//#include <setjmp.h>
#include <string.h>
#include "sol.h"
#include "const.h"
#include "cubestat.h"
#include "pack.h"
#include "transf.h"
#include "prune.h"
#include "turn.h"

static char *at_str[] = {  // twists' names for the phase 1
  "F", "F2", "F'", "L", "L2", "L'",
  "U", "U2", "U'", "B", "B2", "B'",
  "R", "R2", "R'", "D", "D2", "D'",
  "F B'", "F2 B2", "F' B",
  "R L'", "R2 L2", "R' L",
  "U D'", "U2 D2", "U' D"};

static char *at_strs[] = {  // (slice) twists' names for the phase 1
  "F", "F2", "F'", "L", "L2", "L'",
  "U", "U2", "U'", "B", "B2", "B'",
  "R", "R2", "R'", "D", "D2", "D'",
  "S'", "S2", "S", "M", "M2", "M'", "E", "E2", "E'"};

static char *bt_str[] = {  // twists' names for the phase 2
  "F2", "L2", "U", "U2", "U'", "B2", "R2", "D", "D2", "D'",
  "F2 B2", "R2 L2", "U D'", "U2 D2", "U' D"};

static char *bt_strs[] = {  // (slice) twists' names for the phase 2
  "F2", "L2", "U", "U2", "U'", "B2", "R2", "D", "D2", "D'",
  "S2", "M2", "E", "E2", "E'"};

//static jmp_buf jump_env;

static void (*os)(int);

// =========================================================================
   static void  user_interrupt(int x)
// -------------------------------------------------------------------------
// serves for handling ^C signal
// this is realy dangerous in C++: destructors of locals are not called
{
  fprintf(stderr, "\n*** break ***\n");
  //longjmp(jump_env, 1);
}


// =========================================================================
// The 2-phase IDA* algorithm follows
// the functions *_solve initialize the particular phase
// the functions *_search depth-first search for the particular phase
// =========================================================================
   void  Solution::p1_solve()
// -------------------------------------------------------------------------
// initializations and searching starting with increasing depth
{
  int mx_d, i;

  // if (setjmp(jump_env) == 0) {  // break signal handling
    os = signal(SIGINT, user_interrupt);

    min_sol = state.min_sol; // the minimal length found
    aprn = bprn = 0; // statistics
    apry = bpry = 0;
    sol2 = sol2x = 0;
    // the initial configuration to the root of the tree
    s1[0].ct   = state.ct;
    s1[0].ef   = state.ef;
    s1[0].el   = state.el;
    s1[0].cp   = state.cp;
    s1[0].u_se = state.u_se;
    s1[0].d_se = state.d_se;
    s1[0].m_se = state.m_se;

    s1[0].twl  = TWL_BEGIN; // all moves allowed
    s1[0].tw   = -1;        // no previous twist
    // on which depth we can start
    if (opt_search)
      mx_d = pr->a_dist(state.ct, state.ef, state.el, state.cp,
                        state.u_se, state.d_se, state.m_se);
    else
      mx_d = pr->a_dist(state.ct, state.ef, state.el);
    if (mx_d < state.depth)
      mx_d = state.depth;
    for (i = mx_d; i <= min_sol; i++) {
      fprintf(stderr, "computing depth %i...\n", i);
      if (all_search)
        ph2_sol = min_sol - i;     // all moves at the given depth
      else
        ph2_sol = min_sol - i - 1; // decrease depth in the phase 2
      if (ph2_sol < 0)             // we are behind the optimal solution
        break;

      if (opt_search)
        op_search(i); // ignore the phase 2
      else
        p1_search(i);
    }
  // }
  // else { // the break signal was been caught
  //   printf("\nThe continuation key: ");
  //   printf("%lu %lu %i %lu %i %i %i %i %i",
  //     state.co, state.eo,
  //     state.ct, state.ef, state.el, state.cp,
  //     state.u_se, state.d_se, state.m_se);
  //   printf(" %i %i %i", min_sol, s1[0].r_d, n1);
  //   for (i = 1; i <= n1; i++)
  //     printf(" %i", s1[i].tw);
  //   printf("\n\n");
  // }

  //signal(SIGINT, os); // dissable the break signal handling
  // print out some statistics
  if (opt_search) {
    fprintf(stderr, "Done. (%lu solutions found)\n", sol2);
    if (aprn > 0)
      fprintf(stderr, " (%lu%% save... %lu of %lu entries)\n",
        aprn < 10000 ? apry * 100 / aprn : apry / (aprn / 100),
        apry, aprn);
  }
  else {
    fprintf(stderr, "Done. (%lu entries to phase 2 (%lu tries))\n",
      sol2, sol2x);
    if (aprn > 0)
      fprintf(stderr, " (%lu%% save in phase 1... %lu of %lu entries)\n",
        aprn < 10000 ? apry * 100 / aprn : apry / (aprn / 100),
        apry, aprn);
    if (bprn > 0)
      fprintf(stderr, " (%lu%% save in phase 2... %lu of %lu entries)\n",
        bprn < 10000 ? bpry * 100 / bprn : bpry / (bprn / 100),
        bpry, bprn);
  }
  printf("\n"); // terminate the output by 1 empty line
}

// =========================================================================
   void  Solution::op_search(int i)
// -------------------------------------------------------------------------
// searches the state tree only for optimal sequences
{
  int t;

  n1        = 0;  // depth of stack is 0
  s1[0].r_d = i;  // the rest depth is the largest allowed
  s1[1].tw  = -1; // no twist was done

  if (state.length > 0) { // we continue with breaked solution
    n1 = state.length;
    s1[0].r_d = state.depth;
    for (t = 1; t <= n1; t++) {
      s1[t].tw   = state.twist[t - 1];
      s1[t].twl  = ls->a_next(s1[t].tw, s1[t - 1].twl);
      s1[t].r_d  = s1[t - 1].r_d - tn->a_len(s1[t].tw);
      s1[t].ct   = tr->ct->a_do_tw(s1[t].tw, s1[t - 1].ct);
      s1[t].ef   = tr->ef->a_do_tw(s1[t].tw, s1[t - 1].ef);
      s1[t].el   = tr->el->a_do_tw(s1[t].tw, s1[t - 1].el);
      s1[t].cp   = tr->cp->a_do_tw(s1[t].tw, s1[t - 1].cp);
      s1[t].u_se = tr->se->a_do_u_tw(s1[t].tw, s1[t - 1].u_se);
      s1[t].d_se = tr->se->a_do_d_tw(s1[t].tw, s1[t - 1].d_se);
      s1[t].m_se = tr->se->a_do_m_tw(s1[t].tw, s1[t - 1].m_se);
      state.twist[t - 1] = -1;
    }
    s1[n1 + 1].tw = -1;
    state.length = 0; // now it is not breaked
    state.depth = 0;
  }

  while (n1 >= 0) {        // while we have not returned back to the root
    if (s1[n1].r_d == 0) { // maximal depth have been reached
      output();            // move print
      min_sol = s1[0].r_d; // new minimal move length
      sol2++;
      if (!all_search)
        return;            // this depth was successful so return
      n1--;                // go back from leaf to the tree
    }
    else {                 // we are still not on a leaf
      Phase1_node *s  = &s1[n1];
      Phase1_node *ns = &s1[n1 + 1];
      for (t = ns->tw + 1; t < A_N_TW; t++) {
        if (ls->a_invalid(t, s->twl))         // is the move allowed
          continue;
        ns->r_d  = s->r_d - tn->a_len(t);     // decrease the rest depth
        if (ns->r_d < 0)
          continue;
        ns->ct   = tr->ct->a_do_tw(t, s->ct); // make new configuration
        ns->ef   = tr->ef->a_do_tw(t, s->ef); // out of the old one
        ns->el   = tr->el->a_do_tw(t, s->el); // using the twist
        ns->cp   = tr->cp->a_do_tw(t, s->cp);
        ns->u_se = tr->se->a_do_u_tw(t, s->u_se);
        ns->d_se = tr->se->a_do_d_tw(t, s->d_se);
        ns->m_se = tr->se->a_do_m_tw(t, s->m_se);

        aprn++; // statistics
        // we cut the branch of the tree if we find out
        // that the length of a path from current configuration
        // to the goal state (coordinate (0, 0, 0, 0, 0, 0, 0, 0))
        // is longer than the r_d
        if (pr->a_bigger(ns->ct, ns->ef, ns->el, ns->cp,
                         ns->u_se, ns->d_se, ns->m_se, ns->r_d)) {
          apry++;
          continue;
        }
        ns->tw   = t;                         // save the twist
        ns->twl  = ls->a_next(t, s->twl);     // get list of next valid twists
        break;                                // continue with next depth
      }
      if (t == A_N_TW)      // if we have used all possible twists
        n1--;               // then decrease the current depth
      else {
        n1++;               // else increase the current depth
        s1[n1 + 1].tw = -1; // no move have been done on the next depth
      }
    }
  }
}

// =========================================================================
   void  Solution::p1_search(int i)
// -------------------------------------------------------------------------
// for description see the op_search() function
{
  int t;

  n1        = 0;
  s1[0].r_d = i;
  s1[1].tw  = -1;

  if (state.length > 0) { // we continue with breaked solution
    n1 = state.length;
    s1[0].r_d = state.depth;
    for (t = 1; t <= n1; t++) {
      s1[t].tw   = state.twist[t - 1];
      s1[t].twl  = ls->a_next(s1[t].tw, s1[t - 1].twl);
      s1[t].r_d  = s1[t - 1].r_d - tn->a_len(s1[t].tw);
      s1[t].ct   = tr->ct->a_do_tw(s1[t].tw, s1[t - 1].ct);
      s1[t].ef   = tr->ef->a_do_tw(s1[t].tw, s1[t - 1].ef);
      s1[t].el   = tr->el->a_do_tw(s1[t].tw, s1[t - 1].el);
      state.twist[t - 1] = -1;
    }
    s1[n1 + 1].tw = -1;
    state.length = 0; // now it is not breaked
    state.depth = 0;
  }

  while (n1 >= 0) {
    if (s1[n1].r_d == 0) {
      p2_solve(); // enter to the phase 2
      n1--;
    }
    else {
      Phase1_node *s  = &s1[n1];
      Phase1_node *ns = &s1[n1 + 1];
      for (t = ns->tw + 1; t < A_N_TW; t++) {
        if (ls->a_invalid(t, s->twl))
          continue;
        ns->r_d  = s->r_d - tn->a_len(t);
        if (ns->r_d < 0)
          continue;
        ns->ct   = tr->ct->a_do_tw(t, s->ct);
        ns->ef   = tr->ef->a_do_tw(t, s->ef);
        ns->el   = tr->el->a_do_tw(t, s->el);

        aprn++;
        // the pruning function
        if (pr->a_bigger(ns->ct, ns->ef, ns->el, ns->r_d)) {
          apry++;
          continue;
        }
        ns->tw   = t;
        ns->twl  = ls->a_next(t, s->twl);
        break;
      }
      if (t == A_N_TW)
        n1--;
      else {
        n1++;
        s1[n1 + 1].tw = -1;
      }
    }
  }
}

// =========================================================================
   void  Solution::p2_solve()
// -------------------------------------------------------------------------
// initialization of the phase 2 and processing of the values from the phase 1
{
  int i, mx_d, cp, m_se, u_se, d_se;

  sol2x++; // statistics

  cp   = state.cp;
  m_se = state.m_se; // this values were not computed in the phase 1
  u_se = state.u_se; // but we have enough information for computing them
  d_se = state.d_se; // from the initial state and phase 1 moves

  for (i = 1; i <= n1; i++) {
    cp   = tr->cp->a_do_tw(s1[i].tw, cp);
    u_se = tr->se->a_do_u_tw(s1[i].tw, u_se);
    d_se = tr->se->a_do_d_tw(s1[i].tw, d_se);
    m_se = tr->se->a_do_m_tw(s1[i].tw, m_se);
  }

  // entry to the phase 2 may not be correct if the middle edges
  // are not completely defined and some up or down edges
  // are in their places
  if (!tr->se->is_p2_u(u_se) || !tr->se->is_p2_d(d_se))
    return;

  sol2++;

  s2[0].cp = cp;
  s2[0].ep = tr->se->se_to_ep(u_se, d_se);
  s2[0].mp = tr->se->se_to_mp(m_se);

  mx_d = pr->b_dist(cp, s2[0].ep, s2[0].mp);

  bprn++;
  if (mx_d > ph2_sol) {    // check the maximal depth for phase 2
    bpry++;                // against minimal depth with some sense
    return;
  }
  s2[0].twl = s1[n1].twl;  // only valid moves follows in phase 2
  s2[0].tw  = s1[n1].tw;   // useless
  // searching on trees with increasing depth
  for (i = mx_d; i <= ph2_sol; i++)
    p2_search(i);
}

// =========================================================================
   void  Solution::p2_search(int i)
// -------------------------------------------------------------------------
// for description see the op_search() function
{
  int t;

  n2        = 0;
  s2[0].r_d = i;
  s2[1].tw  = -1;

  while (n2 >= 0) {
    if (s2[n2].r_d == 0) {
      output();
      min_sol = s1[0].r_d + s2[0].r_d;
      if (!all_search) {
        ph2_sol = s2[0].r_d - 1;
        return;
      }
      ph2_sol = s2[0].r_d;
      n2--;
    }
    else {
      Phase2_node *s  = &s2[n2];
      Phase2_node *ns = &s2[n2 + 1];
      for (t = ns->tw + 1; t < B_N_TW; t++) {
        if (ls->b_invalid(t, s->twl))
          continue;
        ns->r_d = s->r_d - tn->b_len(t);
        if (ns->r_d < 0)
          continue;
        ns->mp  = tr->mp->b_do_tw(t, s->mp);
        ns->cp  = tr->cp->b_do_tw(t, s->cp);
        ns->ep  = tr->ep->b_do_tw(t, s->ep);

        bprn++;
        // the pruning function
        if (pr->b_bigger(ns->cp, ns->ep, ns->mp, ns->r_d)) {
          bpry++;
          continue;
        }
        ns->tw  = t;
        ns->twl = ls->b_next(t, s->twl);
        break;
      }
      if (t == B_N_TW)
        n2--;
      else {
        n2++;
        s2[n2 + 1].tw = -1;
      }
    }
  }
}

// =========================================================================
   void  Solution::output()
// -------------------------------------------------------------------------
// prints the found solution to the standard output
{
  int i, t, ql = 0, fl = 0, sl = 0;
  // tables of different move lengths
  Turn_table tnq(QUARTER_TURN_METRIC);
  Turn_table tnf(FACE_TURN_METRIC);
  Turn_table tns(SLICE_TURN_METRIC);
  // modification of the twists when slice turns are allowed
  SliceTurnTransform_table sttt;

  for (i = 1; i <= n1; i++) { // rint out the phase 1 part
    t = s1[i].tw;
    if (slice_turn) {
      t = sttt.a_get_do_tw(t); // transformation for slice-turn
      printf("%s ", at_strs[t]);
    }
    else
      printf("%s ", at_str[t]);
    ql += tnq.a_len(t);
    fl += tnf.a_len(t);
    sl += tns.a_len(t);
  }
  if (!opt_search || n2 == 0) {
    printf(". "); // delimit by dot
    for (i = 1; i <= n2; i++) { // print out the phase 2 part
      t = s2[i].tw;
      if (slice_turn) {
        t = sttt.b_get_do_tw(t); // transformation for slice-turn
        printf("%s ", bt_strs[t]);
      }
      else
        printf("%s ", bt_str[t]);
      ql += tnq.b_len(t);
      fl += tnf.b_len(t);
      sl += tns.b_len(t);
    }
  }
  // print out the lengths in different metrics
  if (opt_search) {
    switch (metric) {
      case QUARTER_TURN_METRIC:
        printf("(%iq*, %if, %is)\n", ql, fl, sl);
        break;
      case FACE_TURN_METRIC:
        printf("(%iq, %if*, %is)\n", ql, fl, sl);
        break;
      case SLICE_TURN_METRIC:
        printf("(%iq, %if, %is*)\n", ql, fl, sl);
        break;
    }
  }
  else
    printf("(%iq, %if, %is)\n", ql, fl, sl);
}

