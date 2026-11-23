struct TSTEXTURE;
/* d3_int_io.c -- scene file reader of the d3 interface ("d3_int_io:" allocation tag, "rd_object()" in an error
   message): objects (0x44abb0) and the floor (0x44b920). Its own TU (see d3_obj.c). Names are ours
   except rd_object. */
#ifndef UNK_44ABB0_H
#define UNK_44ABB0_H
#include "d3_engine.h"                /* D3CLIP / D3BGFPOLY / D3TRI */
#include "d3.h"                       /* the D3 records and typedefs this header names */
struct VFSFILE;

typedef union D3IOFLAGS {           /* tex_Load flags as the floor reader builds them */
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
} D3IOFLAGS;




#ifndef UNK_401000_H                /* bio.h's, for the includers without it (the bio.h / d3_fl.h clash is gone) */
void bio_rd_c(struct VFSFILE *f, char *c);                                                        /* 0x401180 */
void bio_rd_v3(struct VFSFILE *f, void *v);                                                       /* 0x401260 */
struct VFSFILE; void bio_rd_v4(struct VFSFILE *f, void *v);                                                       /* 0x401290 */
int bio_rd_array_quick(struct VFSFILE *f, int size, void **out);                                  /* 0x401380 */
#endif

extern char d3_LodMissing;                  /* 0x6339e4, set when an object LOD is missing */

void d3e_LoadEvents(void *f, D3OBJECT *obj);                                            /* 0x43e970, d3_engine.c */
D3OBJECT *rd_object(void *f, D3OBJECT *parent, unsigned int version, char reload);  /* 0x44abb0 */
struct D3FLMAP *d3io_ReadFloor(void *f, unsigned int version);                           /* 0x44b920 */

/* --- 0x44be60..0x44cd40 (worker d3io): scene / group loading, stock objects --- */
extern char d3io_StockPath[];               /* 0x633a00 */
struct VFSDIR * vfs_FindDir(char *path, struct VFSDIR *d);                                                 /* 0x42f7e0, vfs.c */
char * vfs_GetPath(char *name, struct VFSDIR *d, struct VFSDIR *stop, char *out);                          /* 0x42fca0, vfs.c */

void d3io_SetStockDir(char *path);                                                      /* 0x44c510 */
char *d3io_StockFile(char *name, char *ext);                                            /* 0x44c530 */

typedef union D3IOLOD {             /* 0x5fbf78 (initialized to 2): which stock object LODs are loaded */
    unsigned int all;               /* the whole dword: main_OpenScreen stores 2 (0x531fcb mov dword [d3io_Lod], 2) */
    struct {
        unsigned int mode : 7;      /* 1: all three, 2: the best one found */
        unsigned int shadow : 1;    /* load the "_s" variant for lod < 0 */
    };
} D3IOLOD;
extern D3IOLOD d3io_Lod;                    /* 0x5fbf78, which stock object LODs are loaded (d3_io_t.c and main.c include this header) */
char d3io_LodName(char *name, char *name2, int lod, char *out, char *out2);            /* 0x44c9d0 */

void d3io_AttachStock(D3OBJECT *obj, D3SURF *surf, char *name);                        /* 0x44c610 */
typedef void (*D3IOPROGRESS)(int a, int i, int n);

D3OBJECT *d3_CloneObject(D3OBJECT *src);                                                /* 0x43d180, d3_engine.c */
char d3_LoadScene(char *name, void *f, D3IOPROGRESS progress);                    /* 0x44be60 */
struct VFSDIR;
struct VFSFILE * vfs_Tfopen(char *name, char *mode, struct VFSDIR *dir);                                    /* 0x430470, vfs.c */
int vfs_fclose(struct VFSFILE *f);                                                                /* 0x430aa0, vfs.c */
D3OBJECT *d3_LoadGroup(char *name, void *f, D3OBJECT *parent);                    /* 0x44c3f0 */

/* declared in other units' headers before (moved to the owner) */
void d3_AttachMesh(D3OBJECT *obj, struct D3SURF *surf, char *name);  /* 0x44cbb0 */
struct D3BGF *d3io_FindStock(char *name);  /* 0x44c5d0 */

#endif
