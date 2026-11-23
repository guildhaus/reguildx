struct VFSFILE;
/* d3_io_b.h -- the binary BGF reader of the d3 engine ("d3_io_b:BGIMaterialBuffer" etc.): a chunk parser driven
   by tables of {id, handler or sub table, entry count}. Continues the AGI text reader (d3_io_a.c, "d3_io_a:");
   the TU extent is not known (0x44e570.. up to at least 0x44f870). Names are ours. */
#ifndef UNK_44EE50_H
#define UNK_44EE50_H
#include "d3_io_t.h" /* D3BGF / D3BGFMAT */
#include "d3.h"      /* the D3 records and typedefs this header names */

typedef struct VFSFILE VFSFILE; /* vfs.h */

typedef struct BGIENT { /* one table entry, 12 bytes */
  int id;               /* chunk id, 0x28 ends the table */
  void *fn;             /* handler (f, ctx), or the sub table when n != 0 */
  int n;                /* entries of the sub table */
} BGIENT;

typedef struct
    BGIRD { /* reader context; the first 0x38 bytes are the AGICTX layout */
  unsigned char flag0; /* 0x00 */
  unsigned char flag1; /* 0x01 */
  char pad02[2];
  int geomInt;    /* 0x04, int of chunk 0x18; the description never reads it */
  int cur;        /* 0x08, current material */
  int nmats;      /* 0x0c */
  D3BGFMAT *mats; /* 0x10 */
  int npoly;      /* 0x14 */
  int polyidx;    /* 0x18 */
  int polybase;   /* 0x1c */
  D3BGFPOLY *polys;      /* 0x20 */
  int npts;              /* 0x24 */
  int ptidx;             /* 0x28 */
  int ptbase;            /* 0x2c */
  float (*pts)[6];       /* 0x30 */
  int nattach;           /* 0x34 */
  D3BGFATTACH attach[4]; /* 0x38 */
} BGIRD;

extern int bgi_Depth; /* 0x633b00 */

int bgi_ReadId(void *f);                             /* 0x44eea0 */
int bgi_Find(int id, BGIENT *t, int n);              /* 0x44eee0 */
void bgi_Parse(void *f, BGIENT *t, int n, BGIRD *c); /* 0x44ef10 */
void bgi_NextMat(
    void *f,
    BGIRD *c); /* 0x44f000, next material (also the AGI tables' handler) */

/* 0x44f8c0..0x450858: binary vertex animation stream reader and two chunk-file probes (was unk_44f8c0.h,
   worker anim). d3_io_t.h declares 0x44f8c0 and 0x4506f0 too (by the struct tag). */

struct D3ANIMDATA;
struct D3ANIMDATA *d3_LoadBinaryAnimStream(char *path, char *name,
                                           char relative); /* 0x44f8c0 */
char d3_BGFCanWeld(char *path);                            /* 0x4506f0 */
VFSFILE *d3_OpenFastChunk(char *path);                     /* 0x4507a0 */

/* declared in other units' headers before (moved to the owner) */
void d3_ReadBGF(void *f, D3BGFDESC *desc); /* 0x44f870 */

#endif
