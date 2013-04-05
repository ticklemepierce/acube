
#include <stdio.h>
#include "prune.h"
#include "const.h"
#include "cubestat.h"
#include "pack.h"
#include "turn.h"
#include "transf.h"

// =========================================================================
   Pruning_table::
   Pruning_table(Transform_table *tr, Turn_table *tn, struct CubeState state, int opt)
// -------------------------------------------------------------------------
{
  Pack_ef pef(state.eo);
  Pack_ct pct(state.co);

  fprintf(stderr, "\nBuilding pruning tables...\n");
  ef_big = ct_big = 0;
  if (pef.len() > A_N_EF)
    ef_big = 1;
  if (pct.len() > A_N_CT)
    ct_big = 1;
  fprintf(stderr, " - edge flips number: %s, corner twists number: %s\n",
    ef_big ? "big" : "small", ct_big ? "big" : "small");

  ct_el = new Pruning_table_ct_el(tr, tn, state.co, state.e1);
  if (ef_big) {
    ef_xx = new Pruning_table_ef_xx(tr, tn, state.eo);
    fprintf(stderr, "\n - edge flips - middle edge locations (phase 1): none\n");
    ef_el = 0;
    fprintf(stderr, "\n - corner twists - edge flips (phase 1): none\n");
    ct_ef = 0;
  }
  else {
    fprintf(stderr, "\n - edge flips (phase 1): none\n");
    ef_xx = 0;
    ef_el = new Pruning_table_ef_el(tr, tn, state.eo, state.e1);
    if (ct_big) {
      fprintf(stderr, "\n - corner twists - edge flips (phase 1): none\n");
      ct_ef = 0;
    }
    else {
      ct_ef = new Pruning_table_ct_ef(tr, tn, state.co, state.eo);
    }
  }
  if (opt) { // do not use phase 2
    cp_xx = new Pruning_table_cp_xx(tr, tn, state.c1);
    us_el = new Pruning_table_us_el(tr, tn, state.e1);
    ds_el = new Pruning_table_ds_el(tr, tn, state.e1);
    ms_xx = new Pruning_table_ms_xx(tr, tn, state.e1);
    fprintf(stderr, "\n - middle edge permutations - corner permutations (phase 2): none\n");
    mp_cp = 0;
    fprintf(stderr, "\n - middle edge - updown edge permutations (phase 2): none\n");
    mp_ep = 0;
  }
  else { // use phase 2
    fprintf(stderr, "\n - corner permutations (phase 1): none\n");
    cp_xx = 0;
    fprintf(stderr, "\n - upslice edge positions - middle edge locations (phase 1): none\n");
    us_el = 0;
    fprintf(stderr, "\n - downslice edge positions - middle edge locations (phase 1): none\n");
    ds_el = 0;
    fprintf(stderr, "\n - middle slice edge positions (phase 1): none\n");
    ms_xx = 0;
    mp_cp = new Pruning_table_mp_cp(tr, tn, state.e1, state.c1);
    mp_ep = new Pruning_table_mp_ep(tr, tn, state.e1);
  }
  fprintf(stderr, "Pruning tables done.\n");
}

// =========================================================================
   Pruning_table::~Pruning_table()
// -------------------------------------------------------------------------
{
  delete ef_xx;
  delete ct_ef;
  delete ct_el;
  delete ef_el;
  delete cp_xx;
  delete us_el;
  delete ds_el;
  delete ms_xx;
  delete mp_cp;
  delete mp_ep;
}

// =========================================================================
   Pruning_table_ct_ef::
   Pruning_table_ct_ef(Transform_table *tr, Turn_table *tn, int co, int eo):
   co(co), eo(eo)
// -------------------------------------------------------------------------
// the memory tables are used for state tree pruning where
// indices are characteristic numbers of the cube and value is number
// that specifies the least length to the goal state that
// can be proven
// this length is at most the same as the right one
// setting of the tables are done as BFS (wave algorithm) on the graph
{
  int n, d, mx = 0;
  int ct, ef, t;
  unsigned int sm;
  Pack_ct pct(co);
  int Nct = pct.len();
  int Sct = pct.startlen();
  Pack_ef pef(eo);
  int Nef = pef.len();
  int Sef = pef.startlen();

  // set all distances as large
  for (ct = 0; ct < Nct; ct++)
    for (ef = 0; ef < Nef; ef++)
      a[ct][ef] = BIG;
  // get the maximal length of a single move in the particular metrics
  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t); // phase 1 only

  fprintf(stderr, "\n - corner twists - edge flips (phase 1, %i x %i goal/s):\n", Sct, Sef);
  // set all goal positions to the length 0
  for (ct = 0; ct < Sct; ct++)
    for (ef = 0; ef < Sef; ef++)
      a[pct.start(ct)][pef.start(ef)] = 0;
  d = 0;
  n = Sct * Sef; // number of all found configurations at the given depth
  sm = 0;        // all found configurations upto now
  // here starts 'wave' algorithm for graph searching
  // where vertices are different configurations
  // and edges are transitions between them
  while (n) {  // while still something have changed do again
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ct = 0; ct < Nct; ct++) {
      for (ef = 0; ef < Nef; ef++) {
        // process only field with value from d - mx to d - 1 (included)
        if (d <= a[ct][ef] || d > a[ct][ef] + mx)
          continue;
        // try all transitions from the actual state
        for (t = 0; t < A_N_TW; t++) {
          // we need to get exactly to the length d
          if (d == a[ct][ef] + tn->a_len(t)) {
            // we compute indices of new state after the transition 't'
            int nct = tr->ct->a_do_tw(t, ct);
            int nef = tr->ef->a_do_tw(t, ef);
            // if new length is shorter then write it
            if (a[nct][nef] > d) {
              a[nct][nef] = d;
              n++; // change have happend
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_ef_xx::
   Pruning_table_ef_xx(Transform_table *tr, Turn_table *tn, int eo):
   eo(eo)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int ef, t;
  unsigned int sm = 0;
  Pack_ef pef(eo);
  int Nef = pef.len();
  int Sef = pef.startlen();

  for (ef = 0; ef < Nef; ef++)
    a[ef] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - edge flips (phase 1, %i goal/s):\n", Sef);

  for (ef = 0; ef < Sef; ef++)
    a[pef.start(ef)] = 0;
  d = 0;
  n = Sef;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ef = 0; ef < Nef; ef++) {
      if (d <= a[ef] || d > a[ef] + mx)
        continue;
      for (t = 0; t < A_N_TW; t++) {
        if (d == a[ef] + tn->a_len(t)) {
          int nef = tr->ef->a_do_tw(t, ef);
          if (a[nef] > d) {
            a[nef] = d;
            n++;
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_ct_el::
   Pruning_table_ct_el(Transform_table *tr, Turn_table *tn, int co, int e1):
   co(co), e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int ct, el, t;
  unsigned int sm = 0;
  Pack_ct pct(co);
  int Nct = pct.len();
  int Sct = pct.startlen();
  Pack_el pel(e1);
  int Nel = pel.len();
  int Sel = pel.startlen();

  for (ct = 0; ct < Nct; ct++)
    for (el = 0; el < Nel; el++)
      a[ct][el] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - corner twists - middle edge locations (phase 1, %i x %i goal/s):\n", Sct, Sel);

  for (ct = 0; ct < Sct; ct++)
    for (el = 0; el < Sel; el++)
      a[pct.start(ct)][pel.start(el)] = 0;
  d = 0;
  n = Sct * Sel;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ct = 0; ct < Nct; ct++) {
      for (el = 0; el < Nel; el++) {
        if (d <= a[ct][el] || d > a[ct][el] + mx)
          continue;
        for (t = 0; t < A_N_TW; t++) {
          if (d == a[ct][el] + tn->a_len(t)) {
            int nct = tr->ct->a_do_tw(t, ct);
            int nel = tr->el->a_do_tw(t, el);
            if (a[nct][nel] > d) {
              a[nct][nel] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_ef_el::
   Pruning_table_ef_el(Transform_table *tr, Turn_table *tn, int eo, int e1):
   eo(eo), e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int ef, el, t;
  unsigned int sm = 0;
  Pack_ef pef(eo);
  int Nef = pef.len();
  int Sef = pef.startlen();
  Pack_el pel(e1);
  int Nel = pel.len();
  int Sel = pel.startlen();

  for (ef = 0; ef < Nef; ef++)
    for (el = 0; el < Nel; el++)
      a[ef][el] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - edge flips - middle edge locations (phase 1, %i x %i goal/s):\n", Sef, Sel);

  for (ef = 0; ef < Sef; ef++)
    for (el = 0; el < Sel; el++)
      a[pef.start(ef)][pel.start(el)] = 0;
  d = 0;
  n = Sef * Sel;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ef = 0; ef < Nef; ef++) {
      for (el = 0; el < Nel; el++) {
        if (d <= a[ef][el] || d > a[ef][el] + mx)
          continue;
        for (t = 0; t < A_N_TW; t++) {
          if (d == a[ef][el] + tn->a_len(t)) {
            int nef = tr->ef->a_do_tw(t, ef);
            int nel = tr->el->a_do_tw(t, el);
            if (a[nef][nel] > d) {
              a[nef][nel] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_cp_xx::
   Pruning_table_cp_xx(Transform_table *tr, Turn_table *tn, int c1):
   c1(c1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int cp, t;
  unsigned int sm = 0;
  Pack_cp pcp(c1);
  int Ncp = pcp.len();
  int Scp = pcp.startlen();

  for (cp = 0; cp < Ncp; cp++)
    a[cp] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - corner permutations (phase 1, %i goal/s):\n", Scp);

  for (cp = 0; cp < Scp; cp++)
    a[pcp.start(cp)] = 0;
  d = 0;
  n = Scp;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (cp = 0; cp < Ncp; cp++) {
      if (d <= a[cp] || d > a[cp] + mx)
        continue;
      for (t = 0; t < A_N_TW; t++) {
        if (d == a[cp] + tn->a_len(t)) {
          int ncp = tr->cp->a_do_tw(t, cp);
          if (a[ncp] > d) {
            a[ncp] = d;
            n++;
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_us_el::
   Pruning_table_us_el(Transform_table *tr, Turn_table *tn, int e1):
   e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int us, el, t;
  unsigned int sm = 0;
  Pack_use pus(e1);
  int Nus = pus.len();
  int Sus = pus.startlen();
  Pack_el pel(e1);
  int Nel = pel.len();
  int Sel = pel.startlen();

  for (us = 0; us < Nus; us++)
    for (el = 0; el < Nel; el++)
      a[us][el] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - upslice edge positions - middle edge locations (phase 1, %i x %i goal/s):\n", Sus, Sel);

  for (us = 0; us < Sus; us++)
    for (el = 0; el < Sel; el++)
      a[pus.start(us)][pel.start(el)] = 0;
  d = 0;
  n = Sus * Sel;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (us = 0; us < Nus; us++) {
      for (el = 0; el < Nel; el ++) {
        if (d <= a[us][el] || d > a[us][el] + mx)
          continue;
        for (t = 0; t < A_N_TW; t++) {
          if (d == a[us][el] + tn->a_len(t)) {
            int nus = tr->se->a_do_u_tw(t, us);
            int nel = tr->el->a_do_tw(t, el);
            if (a[nus][nel] > d) {
              a[nus][nel] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_ds_el::
   Pruning_table_ds_el(Transform_table *tr, Turn_table *tn, int e1):
   e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int ds, el, t;
  unsigned int sm = 0;
  Pack_dse pds(e1);
  int Nds = pds.len();
  int Sds = pds.startlen();
  Pack_el pel(e1);
  int Nel = pel.len();
  int Sel = pel.startlen();

  for (ds = 0; ds < Nds; ds++)
    for (el = 0; el < Nel; el++)
      a[ds][el] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - downslice edge positions - middle edge locations (phase 1, %i x %i goal/s):\n", Sds, Sel);

  for (ds = 0; ds < Sds; ds++)
    for (el = 0; el < Sel; el++)
      a[pds.start(ds)][pel.start(el)] = 0;
  d = 0;
  n = Sds * Sel;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ds = 0; ds < Nds; ds++) {
      for (el = 0; el < Nel; el++) {
        if (d <= a[ds][el] || d > a[ds][el] + mx)
          continue;
        for (int t = 0; t < A_N_TW; t++) {
          if (d == a[ds][el] + tn->a_len(t)) {
            int nds = tr->se->a_do_d_tw(t, ds);
            int nel = tr->el->a_do_tw(t, el);
            if (a[nds][nel] > d) {
              a[nds][nel] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_ms_xx::
   Pruning_table_ms_xx(Transform_table *tr, Turn_table *tn, int e1):
   e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int ms, t;
  unsigned int sm = 0;
  Pack_mse pms(e1);
  int Nms = pms.len();
  int Sms = pms.startlen();

  for (ms = 0; ms < Nms; ms++)
    a[ms] = BIG;

  for (t = 0; t < A_N_TW; t++)
    if (mx < tn->a_len(t))
      mx = tn->a_len(t);

  fprintf(stderr, "\n - middle slice edge positions (phase 1, %i goal/s):\n", Sms);

  for (ms = 0; ms < Sms; ms++)
    a[pms.start(ms)] = 0;
  d = 0;
  n = Sms;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (ms = 0; ms < Nms; ms++) {
      if (d <= a[ms] || d > a[ms] + mx)
        continue;
      for (t = 0; t < A_N_TW; t++) {
        if (d == a[ms] + tn->a_len(t)) {
          int nms = tr->se->a_do_m_tw(t, ms);
          if (a[nms] > d) {
            a[nms] = d;
            n++;
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_mp_cp::
   Pruning_table_mp_cp(Transform_table *tr, Turn_table *tn, int e1, int c1):
   e1(e1), c1(c1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int mp, cp, t;
  unsigned int sm = 0;
  Pack_mp pmp(e1);
  int Nmp = pmp.len();
  int Smp = pmp.startlen();
  Pack_cp pcp(c1);
  int Ncp = pcp.len();
  int Scp = pcp.startlen();

  for (mp = 0; mp < Nmp; mp++)
    for (cp = 0; cp < Ncp; cp++)
      a[mp][cp] = BIG;

  for (t = 0; t < B_N_TW; t++)
    if (mx < tn->b_len(t))
      mx = tn->b_len(t);

  fprintf(stderr, "\n - middle edge permutations - corner permutations (phase 2, %i x %i goal/s):\n", Smp, Scp);

  for (mp = 0; mp < Smp; mp++)
    for (cp = 0; cp < Scp; cp++)
      a[pmp.start(mp)][pcp.start(cp)] = 0;
  d = 0;
  n = Smp * Scp;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (mp = 0; mp < Nmp; mp++) {
      for (cp = 0; cp < Ncp; cp++) {
        if (d <= a[mp][cp] || d > a[mp][cp] + mx)
          continue;
        for (t = 0; t < B_N_TW; t++) {
          if (d == a[mp][cp] + tn->b_len(t)) {
            int nmp = tr->mp->b_do_tw(t, mp);
            int ncp = tr->cp->b_do_tw(t, cp);
            if (a[nmp][ncp] > d) {
              a[nmp][ncp] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

// =========================================================================
   Pruning_table_mp_ep::
   Pruning_table_mp_ep(Transform_table *tr, Turn_table *tn, int e1):
   e1(e1)
// -------------------------------------------------------------------------
{
  int n, d, mx = 0;
  int mp, ep, t;
  unsigned int sm = 0;
  Pack_mp pmp(e1);
  int Nmp = pmp.len();
  int Smp = pmp.startlen();
  Pack_ep pep(e1);
  int Nep = pep.len();
  int Sep = pep.startlen();

  for (mp = 0; mp < Nmp; mp++)
    for (ep = 0; ep < Nep; ep++)
      a[mp][ep] = BIG;

  for (t = 0; t < B_N_TW; t++)
    if (mx < tn->b_len(t))
      mx = tn->b_len(t);

  fprintf(stderr, "\n - middle edge - updown edge permutations (phase 2, %i x %i):\n", Smp, Sep);

  for (mp = 0; mp < Smp; mp++)
    for (ep = 0; ep < Sep; ep++)
      a[pmp.start(mp)][pep.start(ep)] = 0;
  d = 0;
  n = Smp * Sep;
  while (n) {
    fprintf(stderr,"   %2i %8i %10u\n", d, n, sm += n);
    n = 0;
    d++;
    for (mp = 0; mp < Nmp; mp++) {
      for (ep = 0; ep < Nep; ep++) {
        if (d <= a[mp][ep] || d > a[mp][ep] + mx)
          continue;
        for (t = 0; t < B_N_TW; t++) {
          if (d == a[mp][ep] + tn->b_len(t)) {
            int nmp = tr->mp->b_do_tw(t, mp);
            int nep = tr->ep->b_do_tw(t, ep);
            if (a[nmp][nep] > d) {
              a[nmp][nep] = d;
              n++;
            }
          }
        }
      }
    }
  }
}

