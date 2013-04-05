#include "turn.h"
#include "const.h"

// =========================================================================
   Turn_table::Turn_table(int metric)
// -------------------------------------------------------------------------
// sets lengths depending on metrics
{
  a_l[A_TW_F1] = a_l[A_TW_F3] =
  a_l[A_TW_L1] = a_l[A_TW_L3] =
  a_l[A_TW_U1] = a_l[A_TW_U3] =
  a_l[A_TW_B1] = a_l[A_TW_B3] =
  a_l[A_TW_R1] = a_l[A_TW_R3] =
  a_l[A_TW_D1] = a_l[A_TW_D3] = 1;
  b_l[B_TW_U1] = b_l[B_TW_U3] =
  b_l[B_TW_D1] = b_l[B_TW_D3] = 1;
  switch (metric) {
   case QUARTER_TURN_METRIC:
    a_l[A_TW_F2] =  a_l[A_TW_L2] =
    a_l[A_TW_U2] =  a_l[A_TW_B2] =
    a_l[A_TW_R2] =  a_l[A_TW_D2] =  2;
    a_l[A_TW_FS] =  a_l[A_TW_LS] =
    a_l[A_TW_US] =  a_l[A_TW_BS] =
    a_l[A_TW_RS] =  a_l[A_TW_DS] =  2;
    a_l[A_TW_FS2] = a_l[A_TW_RS2] = a_l[A_TW_US2] = 4;
    b_l[B_TW_F2] =  b_l[B_TW_L2] =
    b_l[B_TW_U2] =  b_l[B_TW_B2] =
    b_l[B_TW_R2] =  b_l[B_TW_D2] =  2;
    b_l[B_TW_US] =  b_l[B_TW_DS] =  2;
    b_l[B_TW_FS2] = b_l[B_TW_RS2] = b_l[B_TW_US2] = 4;
    break;
   case FACE_TURN_METRIC:
    a_l[A_TW_F2] =  a_l[A_TW_L2] =
    a_l[A_TW_U2] =  a_l[A_TW_B2] =
    a_l[A_TW_R2] =  a_l[A_TW_D2] = 1;
    a_l[A_TW_FS] =  a_l[A_TW_LS] =
    a_l[A_TW_US] =  a_l[A_TW_BS] =
    a_l[A_TW_RS] =  a_l[A_TW_DS] =  2;
    a_l[A_TW_FS2] = a_l[A_TW_RS2] = a_l[A_TW_US2] = 2;
    b_l[B_TW_F2] =  b_l[B_TW_L2] =
    b_l[B_TW_U2] =  b_l[B_TW_B2] =
    b_l[B_TW_R2] =  b_l[B_TW_D2] = 1;
    b_l[B_TW_US] =  b_l[B_TW_DS] =  2;
    b_l[B_TW_FS2] = b_l[B_TW_RS2] = b_l[B_TW_US2] = 2;
    break;
   case SLICE_TURN_METRIC:
    a_l[A_TW_F2] =  a_l[A_TW_L2] =
    a_l[A_TW_U2] =  a_l[A_TW_B2] =
    a_l[A_TW_R2] =  a_l[A_TW_D2] = 1;
    a_l[A_TW_FS] =  a_l[A_TW_LS] =
    a_l[A_TW_US] =  a_l[A_TW_BS] =
    a_l[A_TW_RS] =  a_l[A_TW_DS] =  1;
    a_l[A_TW_FS2] = a_l[A_TW_RS2] = a_l[A_TW_US2] = 1;
    b_l[B_TW_F2] =  b_l[B_TW_L2] =
    b_l[B_TW_U2] =  b_l[B_TW_B2] =
    b_l[B_TW_R2] =  b_l[B_TW_D2] = 1;
    b_l[B_TW_US] =  b_l[B_TW_DS] =  1;
    b_l[B_TW_FS2] = b_l[B_TW_RS2] = b_l[B_TW_US2] = 1;
    break;
  }
  is_2[A_TW_F1] =  is_2[A_TW_F3] =
  is_2[A_TW_L1] =  is_2[A_TW_L3] =
  is_2[A_TW_B1] =  is_2[A_TW_B3] =
  is_2[A_TW_R1] =  is_2[A_TW_R3] =  0;
  is_2[A_TW_FS] =  is_2[A_TW_LS] =
  is_2[A_TW_BS] =  is_2[A_TW_RS] =  0;
  is_2[A_TW_F2] =  is_2[A_TW_L2] =
  is_2[A_TW_U1] =  is_2[A_TW_U2] =  is_2[A_TW_U3] =
  is_2[A_TW_B2] =  is_2[A_TW_R2] =
  is_2[A_TW_D1] =  is_2[A_TW_D2] =  is_2[A_TW_D3] = 1;
  is_2[A_TW_FS2] = is_2[A_TW_US2] = is_2[A_TW_RS2] =
  is_2[A_TW_US] =  is_2[A_TW_DS] =  1;
}

// =========================================================================
   TwistList_table::TwistList_table()
// -------------------------------------------------------------------------
// sets which moves are allowed after which moves
{
  int i;

  for (i = 0; i < N_TWL; i++) {
    a_tl[A_TW_F1][i] = TWL_F1;
    a_tl[A_TW_L1][i] = TWL_L1;
    a_tl[A_TW_U1][i] = TWL_U1;
    a_tl[A_TW_B1][i] = TWL_B1;
    a_tl[A_TW_R1][i] = TWL_R1;
    a_tl[A_TW_D1][i] = TWL_D1;
    a_tl[A_TW_F2][i] = TWL_F2;
    a_tl[A_TW_L2][i] = TWL_L2;
    a_tl[A_TW_U2][i] = TWL_U2;
    a_tl[A_TW_B2][i] = TWL_B2;
    a_tl[A_TW_R2][i] = TWL_R2;
    a_tl[A_TW_D2][i] = TWL_D2;
    a_tl[A_TW_F3][i] = TWL_F3;
    a_tl[A_TW_L3][i] = TWL_L3;
    a_tl[A_TW_U3][i] = TWL_U3;
    a_tl[A_TW_B3][i] = TWL_B3;
    a_tl[A_TW_R3][i] = TWL_R3;
    a_tl[A_TW_D3][i] = TWL_D3;
    a_tl[A_TW_FS][i] = a_tl[A_TW_FS2][i] = a_tl[A_TW_BS][i] = TWL_FB;
    a_tl[A_TW_RS][i] = a_tl[A_TW_RS2][i] = a_tl[A_TW_LS][i] = TWL_RL;
    a_tl[A_TW_US][i] = a_tl[A_TW_US2][i] = a_tl[A_TW_DS][i] = TWL_UD;
  }
  for (i = 0; i < A_N_TW; i++)
    a_tl[i][TWL_INVALID] = TWL_INVALID;

  a_tl[A_TW_U1][TWL_U1] = a_tl[A_TW_U1][TWL_U2] = a_tl[A_TW_U1][TWL_U3] =
  a_tl[A_TW_U1][TWL_D1] = a_tl[A_TW_U1][TWL_D2] = a_tl[A_TW_U1][TWL_D3] =
  a_tl[A_TW_U1][TWL_UD] = TWL_INVALID;
  a_tl[A_TW_U2][TWL_U1] = a_tl[A_TW_U2][TWL_U2] = a_tl[A_TW_U2][TWL_U3] =
  a_tl[A_TW_U2][TWL_D1] = a_tl[A_TW_U2][TWL_D2] = a_tl[A_TW_U2][TWL_D3] =
  a_tl[A_TW_U2][TWL_UD] = TWL_INVALID;
  a_tl[A_TW_U3][TWL_U1] = a_tl[A_TW_U3][TWL_U2] = a_tl[A_TW_U3][TWL_U3] =
  a_tl[A_TW_U3][TWL_D1] = a_tl[A_TW_U3][TWL_D2] = a_tl[A_TW_U3][TWL_D3] =
  a_tl[A_TW_U3][TWL_UD] = TWL_INVALID;

  a_tl[A_TW_F1][TWL_F1] = a_tl[A_TW_F1][TWL_F2] = a_tl[A_TW_F1][TWL_F3] =
  a_tl[A_TW_F1][TWL_B1] = a_tl[A_TW_F1][TWL_B2] = a_tl[A_TW_F1][TWL_B3] =
  a_tl[A_TW_F1][TWL_FB] = TWL_INVALID;
  a_tl[A_TW_F2][TWL_F1] = a_tl[A_TW_F2][TWL_F2] = a_tl[A_TW_F2][TWL_F3] =
  a_tl[A_TW_F2][TWL_B1] = a_tl[A_TW_F2][TWL_B2] = a_tl[A_TW_F2][TWL_B3] =
  a_tl[A_TW_F2][TWL_FB] = TWL_INVALID;
  a_tl[A_TW_F3][TWL_F1] = a_tl[A_TW_F3][TWL_F2] = a_tl[A_TW_F3][TWL_F3] =
  a_tl[A_TW_F3][TWL_B1] = a_tl[A_TW_F3][TWL_B2] = a_tl[A_TW_F3][TWL_B3] =
  a_tl[A_TW_F3][TWL_FB] = TWL_INVALID;

  a_tl[A_TW_R1][TWL_L1] = a_tl[A_TW_R1][TWL_L2] = a_tl[A_TW_R1][TWL_L3] =
  a_tl[A_TW_R1][TWL_R1] = a_tl[A_TW_R1][TWL_R2] = a_tl[A_TW_R1][TWL_R3] =
  a_tl[A_TW_R1][TWL_RL] = TWL_INVALID;
  a_tl[A_TW_R2][TWL_L1] = a_tl[A_TW_R2][TWL_L2] = a_tl[A_TW_R2][TWL_L3] =
  a_tl[A_TW_R2][TWL_R1] = a_tl[A_TW_R2][TWL_R2] = a_tl[A_TW_R2][TWL_R3] =
  a_tl[A_TW_R2][TWL_RL] = TWL_INVALID;
  a_tl[A_TW_R3][TWL_L1] = a_tl[A_TW_R3][TWL_L2] = a_tl[A_TW_R3][TWL_L3] =
  a_tl[A_TW_R3][TWL_R1] = a_tl[A_TW_R3][TWL_R2] = a_tl[A_TW_R3][TWL_R3] =
  a_tl[A_TW_R3][TWL_RL] = TWL_INVALID;

  a_tl[A_TW_D1][TWL_U1] = a_tl[A_TW_D1][TWL_U2] = TWL_UD;
  a_tl[A_TW_D1][TWL_D1] = a_tl[A_TW_D1][TWL_D2] = a_tl[A_TW_D1][TWL_D3] =
  a_tl[A_TW_D1][TWL_U3] = a_tl[A_TW_D1][TWL_UD] = TWL_INVALID;
  a_tl[A_TW_D2][TWL_U1] = a_tl[A_TW_D2][TWL_U3] = TWL_UD;
  a_tl[A_TW_D2][TWL_D1] = a_tl[A_TW_D2][TWL_D2] = a_tl[A_TW_D2][TWL_D3] =
  a_tl[A_TW_D2][TWL_U2] = a_tl[A_TW_D2][TWL_UD] = TWL_INVALID;
  a_tl[A_TW_D3][TWL_U2] = a_tl[A_TW_D3][TWL_U3] = TWL_UD;
  a_tl[A_TW_D3][TWL_D1] = a_tl[A_TW_D3][TWL_D2] = a_tl[A_TW_D3][TWL_D3] =
  a_tl[A_TW_D3][TWL_U1] = a_tl[A_TW_D3][TWL_UD] = TWL_INVALID;

  a_tl[A_TW_B1][TWL_F1] = a_tl[A_TW_B1][TWL_F2] = TWL_FB;
  a_tl[A_TW_B1][TWL_B1] = a_tl[A_TW_B1][TWL_B2] = a_tl[A_TW_B1][TWL_B3] =
  a_tl[A_TW_B1][TWL_F3] = a_tl[A_TW_B1][TWL_FB] = TWL_INVALID;
  a_tl[A_TW_B2][TWL_F1] = a_tl[A_TW_B2][TWL_F3] = TWL_FB;
  a_tl[A_TW_B2][TWL_B1] = a_tl[A_TW_B2][TWL_B2] = a_tl[A_TW_B2][TWL_B3] =
  a_tl[A_TW_B2][TWL_F2] = a_tl[A_TW_B2][TWL_FB] = TWL_INVALID;
  a_tl[A_TW_B3][TWL_F2] = a_tl[A_TW_B3][TWL_F3] = TWL_FB;
  a_tl[A_TW_B3][TWL_B1] = a_tl[A_TW_B3][TWL_B2] = a_tl[A_TW_B3][TWL_B3] =
  a_tl[A_TW_B3][TWL_F1] = a_tl[A_TW_B3][TWL_FB] = TWL_INVALID;

  a_tl[A_TW_L1][TWL_R1] = a_tl[A_TW_L1][TWL_R2] = TWL_RL;
  a_tl[A_TW_L1][TWL_L1] = a_tl[A_TW_L1][TWL_L2] = a_tl[A_TW_L1][TWL_L3] =
  a_tl[A_TW_L1][TWL_R3] = a_tl[A_TW_L1][TWL_RL] = TWL_INVALID;
  a_tl[A_TW_L2][TWL_R1] = a_tl[A_TW_L2][TWL_R3] = TWL_RL;
  a_tl[A_TW_L2][TWL_L1] = a_tl[A_TW_L2][TWL_L2] = a_tl[A_TW_L2][TWL_L3] =
  a_tl[A_TW_L2][TWL_R2] = a_tl[A_TW_L2][TWL_RL] = TWL_INVALID;
  a_tl[A_TW_L3][TWL_R2] = a_tl[A_TW_L3][TWL_R3] = TWL_RL;
  a_tl[A_TW_L3][TWL_L1] = a_tl[A_TW_L3][TWL_L2] = a_tl[A_TW_L3][TWL_L3] =
  a_tl[A_TW_L3][TWL_R1] = a_tl[A_TW_L3][TWL_RL] = TWL_INVALID;

  a_tl[A_TW_US][TWL_U1] = a_tl[A_TW_US][TWL_U2] =
  a_tl[A_TW_US][TWL_U3] = a_tl[A_TW_US][TWL_UD] =
  a_tl[A_TW_US][TWL_D1] = a_tl[A_TW_US][TWL_D2] =
  a_tl[A_TW_US][TWL_D3] = TWL_INVALID;
  a_tl[A_TW_US2][TWL_U1] = a_tl[A_TW_US2][TWL_U2] =
  a_tl[A_TW_US2][TWL_U3] = a_tl[A_TW_US2][TWL_UD] =
  a_tl[A_TW_US2][TWL_D1] = a_tl[A_TW_US2][TWL_D2] =
  a_tl[A_TW_US2][TWL_D3] = TWL_INVALID;
  a_tl[A_TW_DS][TWL_U1] = a_tl[A_TW_DS][TWL_U2] =
  a_tl[A_TW_DS][TWL_U3] = a_tl[A_TW_DS][TWL_UD] =
  a_tl[A_TW_DS][TWL_D1] = a_tl[A_TW_DS][TWL_D2] =
  a_tl[A_TW_DS][TWL_D3] = TWL_INVALID;

  a_tl[A_TW_FS][TWL_F1] = a_tl[A_TW_FS][TWL_F2] =
  a_tl[A_TW_FS][TWL_F3] = a_tl[A_TW_FS][TWL_FB] =
  a_tl[A_TW_FS][TWL_B1] = a_tl[A_TW_FS][TWL_B2] =
  a_tl[A_TW_FS][TWL_B3] = TWL_INVALID;
  a_tl[A_TW_FS2][TWL_F1] = a_tl[A_TW_FS2][TWL_F2] =
  a_tl[A_TW_FS2][TWL_F3] = a_tl[A_TW_FS2][TWL_FB] =
  a_tl[A_TW_FS2][TWL_B1] = a_tl[A_TW_FS2][TWL_B2] =
  a_tl[A_TW_FS2][TWL_B3] = TWL_INVALID;
  a_tl[A_TW_BS][TWL_F1] = a_tl[A_TW_BS][TWL_F2] =
  a_tl[A_TW_BS][TWL_F3] = a_tl[A_TW_BS][TWL_FB] =
  a_tl[A_TW_BS][TWL_B1] = a_tl[A_TW_BS][TWL_B2] =
  a_tl[A_TW_BS][TWL_B3] = TWL_INVALID;

  a_tl[A_TW_RS][TWL_R1] = a_tl[A_TW_RS][TWL_R2] =
  a_tl[A_TW_RS][TWL_R3] = a_tl[A_TW_RS][TWL_RL] =
  a_tl[A_TW_RS][TWL_L1] = a_tl[A_TW_RS][TWL_L2] =
  a_tl[A_TW_RS][TWL_L3] = TWL_INVALID;
  a_tl[A_TW_RS2][TWL_R1] = a_tl[A_TW_RS2][TWL_R2] =
  a_tl[A_TW_RS2][TWL_R3] = a_tl[A_TW_RS2][TWL_RL] =
  a_tl[A_TW_RS2][TWL_L1] = a_tl[A_TW_RS2][TWL_L2] =
  a_tl[A_TW_RS2][TWL_L3] = TWL_INVALID;
  a_tl[A_TW_LS][TWL_R1] = a_tl[A_TW_LS][TWL_R2] =
  a_tl[A_TW_LS][TWL_R3] = a_tl[A_TW_LS][TWL_RL] =
  a_tl[A_TW_LS][TWL_L1] = a_tl[A_TW_LS][TWL_L2] =
  a_tl[A_TW_LS][TWL_L3] = TWL_INVALID;

  for (i = 0; i < N_TWL; i++) {
    b_tl[B_TW_F2][i]  = a_tl[A_TW_F2][i];
    b_tl[B_TW_B2][i]  = a_tl[A_TW_B2][i];
    b_tl[B_TW_FS2][i] = a_tl[A_TW_FS2][i];
    b_tl[B_TW_R2][i]  = a_tl[A_TW_R2][i];
    b_tl[B_TW_L2][i]  = a_tl[A_TW_L2][i];
    b_tl[B_TW_RS2][i] = a_tl[A_TW_RS2][i];
    b_tl[B_TW_U1][i]  = a_tl[A_TW_U1][i];
    b_tl[B_TW_U2][i]  = a_tl[A_TW_U2][i];
    b_tl[B_TW_U3][i]  = a_tl[A_TW_U3][i];
    b_tl[B_TW_D1][i]  = a_tl[A_TW_D1][i];
    b_tl[B_TW_D2][i]  = a_tl[A_TW_D2][i];
    b_tl[B_TW_D3][i]  = a_tl[A_TW_D3][i];
    b_tl[B_TW_US][i]  = a_tl[A_TW_US][i];
    b_tl[B_TW_US2][i] = a_tl[A_TW_US2][i];
    b_tl[B_TW_DS][i]  = a_tl[A_TW_DS][i];
  }
}

// =========================================================================
   SliceTurnTransform_table::SliceTurnTransform_table(): i(0)
// -------------------------------------------------------------------------
// initializes the transformations for enabled slice-moves
// since enabling slice-moves inside the algorithm would be very
// hard and unefficient (new cubies would be needed) so
// the move of two oposite layers in the same way is considered
// as the slice-move
// theese moves are (extept the whole cube orientation) equivalent
// so whole cube turning (permutating centers) can be resolved
// when the output is printed
// this "output formating" can be enabled or disabled and it does not have
// any influence on the solving algorithm
{
  int i, j;
  static Byte s[S_N_TW];
  static Byte trt[N_SYM][S_N_TW];
  static Byte tu[A_N_TW], tf[A_N_TW], tr[A_N_TW];
  static Byte tud[N_SYM], tfd[N_SYM], trd[N_SYM];

  if (init_done) return;

  // transformations between the two phases
  a[A_TW_U1] =  B_TW_U1;  a[A_TW_U2] =  B_TW_U2;  a[A_TW_U3] =  B_TW_U3;
  a[A_TW_D1] =  B_TW_D1;  a[A_TW_D2] =  B_TW_D2;  a[A_TW_D3] =  B_TW_D3;
  a[A_TW_F2] =  B_TW_F2;  a[A_TW_R2] =  B_TW_R2;
  a[A_TW_B2] =  B_TW_B2;  a[A_TW_L2] =  B_TW_L2;
  a[A_TW_US] =  B_TW_US;  a[A_TW_US2] = B_TW_US2; a[A_TW_DS] =  B_TW_DS;
  a[A_TW_FS2] = B_TW_FS2; a[A_TW_RS2] = B_TW_RS2;

  b[B_TW_U1] =  A_TW_U1;  b[B_TW_U2] =  A_TW_U2;  b[B_TW_U3] =  A_TW_U3;
  b[B_TW_D1] =  A_TW_D1;  b[B_TW_D2] =  A_TW_D2;  b[B_TW_D3] =  A_TW_D3;
  b[B_TW_F2] =  A_TW_F2;  b[B_TW_R2] =  A_TW_R2;
  b[B_TW_B2] =  A_TW_B2;  b[B_TW_L2] =  A_TW_L2;
  b[B_TW_US] =  A_TW_US;  b[B_TW_US2] = A_TW_US2; b[B_TW_DS] =  A_TW_DS;
  b[B_TW_FS2] = A_TW_FS2; b[B_TW_RS2] = A_TW_RS2;

  // transitions table (sym1 x tw) -> sym2; sttd[symetry][twist] to symetry:

  // conversion table from the slice-moves to the standart phase 1 moves
  s[S_TW_US] =  A_TW_US;  s[S_TW_FS] =  A_TW_FS;  s[S_TW_RS] =  A_TW_RS;
  s[S_TW_US2] = A_TW_US2; s[S_TW_FS2] = A_TW_FS2; s[S_TW_RS2] = A_TW_RS2;
  s[S_TW_DS] =  A_TW_DS;  s[S_TW_BS] =  A_TW_BS;  s[S_TW_LS] =  A_TW_LS;

  // auxiliary transformations (tramsitions) tables
  tud[SYM_ID] =     SYM_US;     tud[SYM_US] =     SYM_US2;
  tud[SYM_FS] =     SYM_US_RS;  tud[SYM_RS] =     SYM_RS_US;
  tud[SYM_US2] =    SYM_DS;     tud[SYM_FS2] =    SYM_US_RS2;
  tud[SYM_RS2] =    SYM_US_FS2; tud[SYM_DS] =     SYM_ID;
  tud[SYM_BS] =     SYM_US_LS;  tud[SYM_LS] =     SYM_US_FS;
  tud[SYM_US_FS] =  SYM_RS_FS2; tud[SYM_US_RS] =  SYM_FS_US2;
  tud[SYM_FS_RS] =  SYM_RS;     tud[SYM_RS_US] =  SYM_RS_US2;
  tud[SYM_US_FS2] = SYM_FS2;    tud[SYM_US_RS2] = SYM_RS2;
  tud[SYM_FS_US2] = SYM_FS_DS;  tud[SYM_FS_RS2] = SYM_RS_BS;
  tud[SYM_RS_US2] = SYM_FS_RS;  tud[SYM_RS_FS2] = SYM_DS_BS;
  tud[SYM_US_LS] =  SYM_FS_RS2; tud[SYM_FS_DS] =  SYM_FS;
  tud[SYM_RS_BS] =  SYM_BS;     tud[SYM_DS_BS] =  SYM_LS;

  tfd[SYM_ID] =     SYM_FS;     tfd[SYM_US] =     SYM_US_FS;
  tfd[SYM_FS] =     SYM_FS2;    tfd[SYM_RS] =     SYM_US_RS;
  tfd[SYM_US2] =    SYM_FS_RS2; tfd[SYM_FS2] =    SYM_BS;
  tfd[SYM_RS2] =    SYM_FS_US2; tfd[SYM_DS] =     SYM_FS_RS;
  tfd[SYM_BS] =     SYM_ID;     tfd[SYM_LS] =     SYM_FS_DS;
  tfd[SYM_US_FS] =  SYM_US_FS2; tfd[SYM_US_RS] =  SYM_RS_FS2;
  tfd[SYM_FS_RS] =  SYM_US_RS2; tfd[SYM_RS_US] =  SYM_US;
  tfd[SYM_US_FS2] = SYM_RS_US;  tfd[SYM_US_RS2] = SYM_DS_BS;
  tfd[SYM_FS_US2] = SYM_US2;    tfd[SYM_FS_RS2] = SYM_RS2;
  tfd[SYM_RS_US2] = SYM_US_LS;  tfd[SYM_RS_FS2] = SYM_RS_BS;
  tfd[SYM_US_LS] =  SYM_LS;     tfd[SYM_FS_DS] =  SYM_RS_US2;
  tfd[SYM_RS_BS] =  SYM_RS;     tfd[SYM_DS_BS] =  SYM_DS;

  trd[SYM_ID] =     SYM_RS;     trd[SYM_US] =     SYM_US_RS;
  trd[SYM_FS] =     SYM_FS_RS;  trd[SYM_RS] =     SYM_RS2;
  trd[SYM_US2] =    SYM_RS_FS2; trd[SYM_FS2] =    SYM_RS_US2;
  trd[SYM_RS2] =    SYM_LS;     trd[SYM_DS] =     SYM_RS_BS;
  trd[SYM_BS] =     SYM_RS_US;  trd[SYM_LS] =     SYM_ID;
  trd[SYM_US_FS] =  SYM_FS;     trd[SYM_US_RS] =  SYM_US_RS2;
  trd[SYM_FS_RS] =  SYM_FS_RS2; trd[SYM_RS_US] =  SYM_FS_US2;
  trd[SYM_US_FS2] = SYM_FS_DS;  trd[SYM_US_RS2] = SYM_US_LS;
  trd[SYM_FS_US2] = SYM_DS_BS;  trd[SYM_FS_RS2] = SYM_US_FS;
  trd[SYM_RS_US2] = SYM_US2;    trd[SYM_RS_FS2] = SYM_FS2;
  trd[SYM_US_LS] =  SYM_US;     trd[SYM_FS_DS] =  SYM_DS;
  trd[SYM_RS_BS] =  SYM_US_FS2; trd[SYM_DS_BS] =  SYM_BS;

  // transformation table representing function (sym1 x slice_tw) -> sym2
  for (i = 0; i < N_SYM; i++) {
    trt[i][S_TW_US] = tud[i];
    trt[i][S_TW_FS] = tfd[i];
    trt[i][S_TW_RS] = trd[i];
  }
  for (i = 0; i < N_SYM; i++) {
    trt[i][S_TW_US2] = trt[trt[i][S_TW_US]][S_TW_US];
    trt[i][S_TW_FS2] = trt[trt[i][S_TW_FS]][S_TW_FS];
    trt[i][S_TW_RS2] = trt[trt[i][S_TW_RS]][S_TW_RS];
  }
  for (i = 0; i < N_SYM; i++) {
    trt[i][S_TW_DS] = trt[trt[i][S_TW_US2]][S_TW_US];
    trt[i][S_TW_BS] = trt[trt[i][S_TW_FS2]][S_TW_FS];
    trt[i][S_TW_LS] = trt[trt[i][S_TW_RS2]][S_TW_RS];
  }

  // the final construction of the transition table (sym1 x tw) -> sym2
  for (i = 0; i < N_SYM; i++) {
    for (j = 0; j < A_N_TW; j++) {
      sttd[i][j] = i;                // identity for non-slice
    }
    for (j = 0; j < S_N_TW; j++) {
      sttd[i][s[j]] = trt[i][j];     // inserting of the previous table
    }
  }

  // output table (sym x tw1) -> tw2; sttr[symetry][twist] to twist

  // 3 tables repr. 3 basic slice-moves transf. tw1 -> tw2
  for (i = 0; i < A_N_TW; i++) {
    tu[i] = i; tf[i] = i; tr[i] = i;
  }
  tu[A_TW_F1] = A_TW_R1; tu[A_TW_F2] =  A_TW_R2;  tu[A_TW_F3] = A_TW_R3;
  tu[A_TW_R1] = A_TW_B1; tu[A_TW_R2] =  A_TW_B2;  tu[A_TW_R3] = A_TW_B3;
  tu[A_TW_B1] = A_TW_L1; tu[A_TW_B2] =  A_TW_L2;  tu[A_TW_B3] = A_TW_L3;
  tu[A_TW_L1] = A_TW_F1; tu[A_TW_L2] =  A_TW_F2;  tu[A_TW_L3] = A_TW_F3;
  tu[A_TW_FS] = A_TW_RS; tu[A_TW_FS2] = A_TW_RS2; tu[A_TW_BS] = A_TW_LS;
  tu[A_TW_RS] = A_TW_BS; tu[A_TW_RS2] = A_TW_FS2; tu[A_TW_LS] = A_TW_FS;

  tf[A_TW_U1] = A_TW_L1; tf[A_TW_U2] =  A_TW_L2;  tf[A_TW_U3] = A_TW_L3;
  tf[A_TW_R1] = A_TW_U1; tf[A_TW_R2] =  A_TW_U2;  tf[A_TW_R3] = A_TW_U3;
  tf[A_TW_D1] = A_TW_R1; tf[A_TW_D2] =  A_TW_R2;  tf[A_TW_D3] = A_TW_R3;
  tf[A_TW_L1] = A_TW_D1; tf[A_TW_L2] =  A_TW_D2;  tf[A_TW_L3] = A_TW_D3;
  tf[A_TW_US] = A_TW_LS; tf[A_TW_US2] = A_TW_RS2; tf[A_TW_DS] = A_TW_RS;
  tf[A_TW_RS] = A_TW_US; tf[A_TW_RS2] = A_TW_US2; tf[A_TW_LS] = A_TW_DS;

  tr[A_TW_U1] = A_TW_F1; tr[A_TW_U2] =  A_TW_F2;  tr[A_TW_U3] = A_TW_F3;
  tr[A_TW_F1] = A_TW_D1; tr[A_TW_F2] =  A_TW_D2;  tr[A_TW_F3] = A_TW_D3;
  tr[A_TW_D1] = A_TW_B1; tr[A_TW_D2] =  A_TW_B2;  tr[A_TW_D3] = A_TW_B3;
  tr[A_TW_B1] = A_TW_U1; tr[A_TW_B2] =  A_TW_U2;  tr[A_TW_B3] = A_TW_U3;
  tr[A_TW_US] = A_TW_FS; tr[A_TW_US2] = A_TW_FS2; tr[A_TW_DS] = A_TW_BS;
  tr[A_TW_FS] = A_TW_DS; tr[A_TW_FS2] = A_TW_US2; tr[A_TW_BS] = A_TW_US;

  for (j = 0; j < A_N_TW; j++) {
    sttr[SYM_ID][j] = j;
    sttr[SYM_US][j] = tu[j];
    sttr[SYM_FS][j] = tf[j];
    sttr[SYM_RS][j] = tr[j];
    sttr[SYM_US2][j] = tu[tu[j]];
    sttr[SYM_FS2][j] = tf[tf[j]];
    sttr[SYM_RS2][j] = tr[tr[j]];
    sttr[SYM_DS][j] = tu[tu[tu[j]]];
    sttr[SYM_BS][j] = tf[tf[tf[j]]];
    sttr[SYM_LS][j] = tr[tr[tr[j]]];
    sttr[SYM_US_FS][j] = tf[tu[j]];
    sttr[SYM_US_RS][j] = tr[tu[j]];
    sttr[SYM_FS_RS][j] = tr[tf[j]];
    sttr[SYM_RS_US][j] = tu[tr[j]];
    sttr[SYM_US_FS2][j] = tf[tf[tu[j]]];
    sttr[SYM_US_RS2][j] = tr[tr[tu[j]]];
    sttr[SYM_FS_US2][j] = tu[tu[tf[j]]];
    sttr[SYM_FS_RS2][j] = tr[tr[tf[j]]];
    sttr[SYM_RS_US2][j] = tu[tu[tr[j]]];
    sttr[SYM_RS_FS2][j] = tf[tf[tr[j]]];
    sttr[SYM_US_LS][j] = tr[tr[tr[tu[j]]]];
    sttr[SYM_FS_DS][j] = tu[tu[tu[tf[j]]]];
    sttr[SYM_RS_BS][j] = tf[tf[tf[tr[j]]]];
    sttr[SYM_DS_BS][j] = tf[tf[tf[tu[tu[tu[j]]]]]];
  }
  init_done = 1;
}

// definition of the static variables (they are initialized only once)
int  SliceTurnTransform_table::init_done = 0;
Byte SliceTurnTransform_table::sttr[N_SYM][A_N_TW];
Byte SliceTurnTransform_table::sttd[N_SYM][A_N_TW];
Byte SliceTurnTransform_table::a[A_N_TW];
Byte SliceTurnTransform_table::b[B_N_TW];

