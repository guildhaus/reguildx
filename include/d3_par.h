/* d3_par ("d3_par:" allocation tags, 0x455630..0x457c30): particle system list, drawing and emitters.
   Original file name unknown. Names are ours. */
#ifndef D3_PAR_H
#define D3_PAR_H
#include "d3.h"                       /* the D3 records and typedefs this header names */

/* The list of particle systems is bracketed by two fake nodes whose link fields are plain globals:
   the end marker d3_ParEnd (0xfb9280), whose prev field (+0x318) is the tail pointer at 0xfb9598, and the head
   node (0xfb95e0), whose next field (+0x314) is the head pointer at 0xfb98f4. */
extern D3PARTSYS d3if_ParList;      /* 0xfb95e0, d3_interface.c */
extern D3PARTSYS d3_ParEnd;         /* 0xfb9280 */
#define d3_ParHead (d3if_ParList.next)     /* 0xfb98f4, head of the default scene's list (as d3_engine.h) */
#define d3_ParTail (d3_ParEnd.prev)        /* 0xfb9598, tail of the default scene's list */

void par_Init(void);                                    /* 0x455630 */
void par_DeleteAll(void);                               /* 0x4556b0 */
void par_Unlink(D3PARTSYS *ps);                         /* 0x4556e0 */
void par_Delete(D3PARTSYS *ps);                         /* 0x455760, also in d3_engine.h */

extern float d3_ParUV0[6];          /* 0xfb95a0, (0,0) (1,1) (0,1) */
extern float d3_ParUV1[6];          /* 0xfb95c0, (0,0) (1,0) (1,1) */

/* The particle quads' clip and visible bits, written through views of the D3VERTEX.flags / D3TRI.flags bytes
   (par_Draw's chained bit stores). @original: par_Draw stores through a plain bitfield struct; any union member
   for the bits (D3VERTEX.clip, a bit struct added to D3VERTEX's or D3TRI's flags union, D3TRI's hm bits) moves
   its register allocation (draft, 74 ins), so the views stay. */
typedef struct PARVFLAGS {
    unsigned char l : 1, r : 1, t : 1, b : 1, b4 : 1, b5 : 1, b6 : 1, vis : 1;
} PARVFLAGS;
#define PAR_VF(v) ((PARVFLAGS *)&(v)->flags)
typedef struct PARTFLAGS {
    unsigned char low : 7, vis : 1;
} PARTFLAGS;
#define PAR_TF(t) ((PARTFLAGS *)&(t)->flags)

/* a D3COLOR that can also be set as a whole; the original stores the four bytes as a long */
typedef union PARCOL {
    unsigned long color;
    D3COLOR c;
} PARCOL;

/* each particle is a quad of 4 projected vertices (ps->points) and 2 triangles (ps->polys) */
#define PAR_RND() ((float)((float)rand() / RAND_MAX))

struct TSTEXTURE * tex_GetFrame(int index, unsigned char frame);                                         /* 0x460b00 */
void par_SetDir(D3PARTSYS *ps, D3VECTOR *dir, float roll);                              /* 0x455a40 */
void par_Draw(D3PARTSYS *ps);                                                       /* 0x455a90, draw */
char par_EmitterCB0(D3PARTSYS *ps, unsigned long time);                                 /* 0x456350 */
char par_EmitterCB1(D3PARTSYS *ps, unsigned long time);                                 /* 0x456b60 */
char par_EmitterCB2(D3PARTSYS *ps, unsigned long time);                                 /* 0x457460 */

#endif
