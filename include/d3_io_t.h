/* d3_io_t.c -- the "d3_io_t:" / "d3_io:" part of the d3 scene I/O: the BGF mesh loader and its helpers
   (0x44cd40..0x44e570; 0x44df40.. from worker d3io3). Names are ours. */
#ifndef UNK_44CD40_H
#define UNK_44CD40_H
#include "d3.h" /* the D3 records and typedefs this header names */

typedef union D3BGFFLAGS { /* tex_Load flags as the loader builds them */
  unsigned int all;
  D3TEXFLAGS f;
  struct {
    unsigned char b0;
    unsigned char b1;
    unsigned char c0 : 1;
    unsigned char c1 : 1;
    unsigned char c2 : 6;
    unsigned char b3;
  } s;
} D3BGFFLAGS;

typedef struct D3BGFMAT { /* 0xe0 bytes, a material as stored in the file */
  char name[3][0x40];     /* 0x00, 0x40, 0x80: texture names */
  unsigned char kind;     /* 0xc0 */
  unsigned char c1;       /* 0xc1 */
  signed char c2;         /* 0xc2 */
  signed char c3;         /* 0xc3 */
  char pad4;
  signed char c5;
  signed char c6;
  signed char c7;
  signed char c8;
  signed char c9;
  char padca[2];
  float su, sv; /* 0xcc: scale */
  float ou, ov; /* 0xd4: offset */
  float rot;    /* 0xdc */
} D3BGFMAT;

typedef struct
    D3BGFDESC { /* 0x198 bytes, what the file reader (0x44f870) fills in */
  char pad00;
  signed char flag01; /* 0x01 */
  char pad02[0xa];
  int nmat;       /* 0x0c */
  D3BGFMAT *mats; /* 0x10 */
  char pad14[0x8];
  int npoly;        /* 0x1c */
  D3BGFPOLY *polys; /* 0x20 */
  char pad24[0x8];
  int npts;              /* 0x2c */
  float *pts;            /* 0x30, 6 floats each */
  int nattach;           /* 0x34 */
  D3BGFATTACH attach[4]; /* 0x38 */
} D3BGFDESC;

/* The eight bounding-box corners are appended to the vertex array as D3BGFVERT records (d3_io_fl.h):
   D3BGF_CORNER(m, k) is corner k (x, y, z; its normals stay unset) */
#define D3BGF_CORNER(m, k) ((m)->vtx + (m)->nverts + (k))

extern struct VFSDIR *vfs_Root; /* 0x6333fc */
struct VFSDIR;
struct VFSFILE *vfs_Tfopen(char *name, char *mode,
                           struct VFSDIR *dir); /* 0x430470 */

void d3iot_DeleteStockObject(D3BGF *m);                        /* 0x44cd40 */
void d3iot_CalcBounds(D3BGF *m);                               /* 0x44ce40 */
void d3iot_Finish(D3BGF *m, char bounds);                      /* 0x44d1c0 */
void d3iot_LoadTexSet(char *name, char **out, int *w, int *h); /* 0x44d1f0 */
D3BGF *d3iot_LoadBGF(char *path, char *name, char *texnames, int ntexsets,
                     int ntex);                     /* 0x44d330 */
float d3iot_GetRadius(D3OBJECT *obj, D3SURF *info); /* 0x44df20 */

/* 0x44df40..0x44e570 (worker d3io3, joined at the round-10 close) */

struct D3OBJECT;
struct D3SURF;
void d3_TransformNormals(
    struct D3OBJECT *obj,
    struct D3SURF *info);              /* 0x4598d0, stock object callback */
extern char d3_AnimDir[];              /* 0x5fbf80, "animations/" */
extern volatile unsigned long d3_Time; /* 0x6333cc, milliseconds (tb.c) */

struct D3ANIMDATA *
d3_LoadBinaryAnimStream(char *path, char *name,
                        char relative); /* 0x44f8c0, d3_io_b.c */

D3BGF *d3io_LoadObjectFile(char *name, char *file); /* 0x44df40 */
D3BGF *d3io_LoadObject(char *a, char *b);           /* 0x44e080 */
D3BGF *d3io_LoadObjectRef(char *a, char *b);        /* 0x44e190 */
void d3io_ReleaseObject(D3BGF *obj);                /* 0x44e2c0 */
D3PATH *d3_LoadObjectAnim(char *file, D3OBJECT *obj,
                          char reload); /* 0x44e2e0 */
struct D3ANIMDATA *d3_LoadAnimStream(char *name, char *file,
                                     char unk); /* 0x44e4a0 */

#endif
