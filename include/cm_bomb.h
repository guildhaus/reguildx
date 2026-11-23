/* The bomb records of the fights (cmfight.c's cm_Bombs) for the units that clear them without the rest of cm.h
   (sv.c's sv_InitTick): types and the one datum. cm_types.h includes it. */
#ifndef CM_BOMB_H
#define CM_BOMB_H
struct D3OBJECT;
typedef struct CMBOMB { /* 8 bytes, one of the 32 bombs of cm_Bombs */
  struct D3OBJECT *obj; /* the bomb object "ob_BOMBE", 0 = a free slot */
  unsigned long time;   /* d3_Time when it was laid */
} CMBOMB;
extern CMBOMB cm_Bombs
    [32]; /* 0x935c00, cmfight.c: the 32 bomb records (cm_LayBomb, cm_UpdateBombs) */
#endif
