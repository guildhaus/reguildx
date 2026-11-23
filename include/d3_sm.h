/* d3_sm.c -- terrain height/shadow map ("d3_sm:", "d3sm_"), original file name unknown.
   Names are ours. */
#ifndef UNK_45DB40_H
#define UNK_45DB40_H
#include "d3.h"                       /* the D3 records and typedefs this header names */
#include "d3_sm_types.h"             /* D3SM, D3SMENTRY */

char d3sm_FindGround(D3SM *h, int x, int z, int *ox, int *oz);           /* 0x45efc0, the cell nearest to
                                                                            (x, z) with a real ground type */
char d3_GetHeightAt(D3SM *h, D3VECTOR *pos, int *px, int *pz, float *py);        /* 0x45f170, the cell of pos and
                                                                            (h != 0) the interpolated height there */

/* declared in other units' headers before (moved to the owner) */
void d3sm_Destroy(D3SM *h);  /* 0x45ef60 */
extern D3SM *d3sm_Shadow;  /* 0x633df8 */
char d3sm_Pick(D3SM *h, int sx, int sy, int *px, int *pz);              /* 0x45f2b0, the cell (px, pz) under the screen point (sx, sy); 0 = none */

#endif
