#ifndef H_CONST_H_
#define H_CONST_H_

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned long Long;

// various metrics:
//   QT: |X| = |X'| = 1, |X2| = 2
//   FT: |X| = |X'| = |X2| = 1
//   ST: |RL'| = |R2L2| = |R'L| = ... = |X| = |X'| = |X2| = 1
enum {INVALID_METRIC, QUARTER_TURN_METRIC, FACE_TURN_METRIC, SLICE_TURN_METRIC};

// sizes of transform-tables
enum {A_N_CT =  2187, A_N_EF =   2048, A_N_EL = 495,
      A_N_CP = 40320, A_N_SE =  11880,
      A_M_CT = 20412, A_M_EF = 126720};
enum {B_N_CP = 40320, B_N_EP =  40320, B_N_MP =  24};
enum {N_SE   = 11880, N_HE   =   1680, N_ME   =  24};

// which configurations are the solved ones
//enum {A_CT_START = 0,   // no twisted corner
//      A_EF_START = 0,   // no flipped edge
//      A_EL_START = 0,   // 000000001111 for index 0123456789AB
//      B_CP_START = 0,   // 01234567     for index 01234567
//      B_EP_START = 0,   // 01234567     for index 01234567
//      B_MP_START = 0};  // 0123         for index 0123 (89AB)

// limits
enum {BIG = 30};

// corner-cubies enumeration
enum {CR_UFR, CR_URB, CR_UBL, CR_ULF, CR_DRF, CR_DFL, CR_DLB, CR_DBR};

enum {A_CR_UFR, A_CR_URB, A_CR_UBL, A_CR_ULF,
      A_CR_DRF, A_CR_DFL, A_CR_DLB, A_CR_DBR};

enum {B_CR_UFR, B_CR_URB, B_CR_UBL, B_CR_ULF,
      B_CR_DRF, B_CR_DFL, B_CR_DLB, B_CR_DBR};

// edge-cubies enumeration
enum {A_ED_UF, A_ED_UR, A_ED_UB, A_ED_UL, A_ED_DF, A_ED_DR,
      A_ED_DB, A_ED_DL, A_ED_FR, A_ED_FL, A_ED_BR, A_ED_BL};

// up & down layer edge-cubies enumeration
enum {B_ED_UF, B_ED_UR, B_ED_UB, B_ED_UL, B_ED_DF, B_ED_DR, B_ED_DB, B_ED_DL};

// middle layer edge-cubies enumeration
enum {B_MD_FR, B_MD_FL, B_MD_BR, B_MD_BL};


// moves enumeration
enum {A_TW_F1, A_TW_F2,  A_TW_F3, A_TW_L1, A_TW_L2, A_TW_L3,
      A_TW_U1, A_TW_U2,  A_TW_U3, A_TW_B1, A_TW_B2, A_TW_B3,
      A_TW_R1, A_TW_R2,  A_TW_R3, A_TW_D1, A_TW_D2, A_TW_D3,
      // "slice" moves follows
      A_TW_FS, A_TW_FS2, A_TW_BS,
      A_TW_RS, A_TW_RS2, A_TW_LS,
      A_TW_US, A_TW_US2, A_TW_DS,
      A_N_TW};

enum {B_TW_F2,  B_TW_L2,  B_TW_U1, B_TW_U2,  B_TW_U3,
      B_TW_B2,  B_TW_R2,  B_TW_D1, B_TW_D2,  B_TW_D3,
      // "slice" moves follows
      B_TW_FS2, B_TW_RS2, B_TW_US, B_TW_US2, B_TW_DS,
      B_N_TW};

enum {S_TW_US, S_TW_US2, S_TW_DS, S_TW_FS, S_TW_FS2, S_TW_BS,
      S_TW_RS, S_TW_RS2, S_TW_LS, S_N_TW};

// move combinations possibility enumerations
enum {TWL_INVALID,  TWL_BEGIN,
      TWL_F1, TWL_F2, TWL_F3, TWL_L1, TWL_L2, TWL_L3,
      TWL_U1, TWL_U2, TWL_U3, TWL_B1, TWL_B2, TWL_B3,
      TWL_R1, TWL_R2, TWL_R3, TWL_D1, TWL_D2, TWL_D3,
      // "slice" moves follows
      TWL_FB, TWL_RL, TWL_UD,
      N_TWL};

// (non-mirror) symetries of the cube (rotational) enumeration
enum {SYM_ID, SYM_US, SYM_FS, SYM_RS, SYM_US2, SYM_FS2, SYM_RS2,
      SYM_DS, SYM_BS, SYM_LS, SYM_US_FS, SYM_US_RS, SYM_FS_RS, SYM_RS_US,
      SYM_US_FS2, SYM_US_RS2, SYM_FS_US2, SYM_FS_RS2, SYM_RS_US2, SYM_RS_FS2,
      SYM_US_LS, SYM_FS_DS, SYM_RS_BS, SYM_DS_BS,
      N_SYM};

#endif
