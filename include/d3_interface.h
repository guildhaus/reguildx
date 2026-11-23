struct D3SM;
struct D3FLMAP;
struct D3OBJECT;
struct VFSFILE;
/* d3_interface.c types and globals: object creation / deletion API of the d3 engine and the scene switch.
   __FILE__ string "D:\develop\Units\d3\d3_interface.c" at 0x5fbd94. Names are ours. */
#ifndef D3_INTERFACE_H
#define D3_INTERFACE_H
#include <stddef.h>                    /* offsetof, for the layout checks */
#include "d3.h"                       /* the D3 records and typedefs this header names */

extern float d3if_Gray;             /* 0x5fcc74, 0.3 r + 0.59 g + 0.11 b of the ambient colour */
extern D3VECTOR d3_AmbientColor;    /* 0x5fcc78, the ambient colour (r, g, b) */
extern D3FOGSET d3if_Fog[6];        /* 0xfba960, the fog sets of the current light set */
extern D3LIGHTSET d3if_Levels[7];   /* 0xfba9c0, the day-time light sets */
extern D3OBJECT *d3if_CamOben;              /* 0x6338b8 */
extern D3OBJECT *d3if_CamVorne;              /* 0x6338bc */
extern D3OBJECT *d3if_CamSeite;              /* 0x6338c0 */
#ifndef DATA_VIEWS_H
extern int d3if_SceneState0;              /* 0x5fb5c0 */
#endif

extern int d3s_ShadowMapSize;          /* 0x633dcc */
#ifndef DATA_VIEWS_H
extern unsigned int d3if_SceneSwitches;     /* 0x6339dc, counts the scene switches */
#endif
extern D3OBJECT *d3if_LastMegaCam;          /* 0xfba944 */

void d3_AddChild(D3OBJECT *parent, D3OBJECT *obj);                                      /* 0x43cb80, d3_engine.c */
struct D3BGF *d3io_FindStock(char *name);                                                           /* 0x44c5d0 */
void d3if_CreateCameras(void);                                                                /* 0x448910 */
void d3_SetFog(float start, float end, D3COLOR color);                    /* 0x43a6f0, d3_engine.c */
struct D3SM * d3sm_Create(struct D3FLMAP *t, int size, int mask);                                /* 0x45eeb0 */
void d3sm_Destroy(struct D3SM *h);                                                          /* 0x45ef60 */
struct TSTEXTURE; void tex_GetParams(struct TSTEXTURE *tex, unsigned char *opts, unsigned char *fmt);                                   /* 0x460aa0, ts_texture.c */

char d3if_Delete(D3OBJECT *obj);                                                        /* 0x447190 */
char d3if_Show(struct D3OBJECT *obj, char show);                                               /* 0x4471b0 */
char d3if_ScreenBox(D3OBJECT *obj, D3RECT *r);                                                   /* 0x4486e0, the screen rectangle an object covers */
char d3if_ShowTree(D3OBJECT *obj, char show);                                           /* 0x447300 */
D3OBJECT *d3if_Pick(float x, float y, int flags, int mask);                       /* 0x448630, the object under a screen position, 0 if none */


extern D3PARTSYS d3if_ParList;      /* 0xfb95e0, the particle list head node */
typedef char d3if_chk_size[sizeof(D3SCENE) == 0x3e0 ? 1 : -1];
typedef char d3if_chk_levels[offsetof(D3SCENE, levels) == 0x128 ? 1 : -1];
typedef char d3if_chk_sceneFlags[offsetof(D3SCENE, sceneFlags) == 0x3d8 ? 1 : -1];

/* --- 0x447e60..0x448910 (worker d3if2) --- */
#define D3IF_RGB_MASK 0xffffff      /* the r/g/b bits of an ARGB colour (sprite vertex colour) */

typedef struct D3IFMOVE {           /* context of d3if_MoveCB */
    D3SCENE *from, *to;
} D3IFMOVE;


typedef union D3IFTEXFLAGS {        /* D3TEXFLAGS with the bits named */
    D3TEXFLAGS raw;                 /* what tex_Load takes by value */
    struct {
        unsigned char alpha;
        unsigned char b1;
        unsigned char f0 : 1;
        unsigned char glow : 1;
        unsigned char f2 : 6;
        unsigned char b3;
    } bits;
} D3IFTEXFLAGS;

typedef struct D3IFHIT {
    D3OBJECT *obj;
    float dist;
} D3IFHIT;

typedef struct D3IFPICK {           /* context of d3if_PickCB */
    D3IFHIT hits[9];                /* the nearest hit per object type */
    D3OBJECT *cam;                  /* 0x48 */
    int mask;                       /* 0x4c, tested against obj->mask */
    float dx, dy;                   /* 0x50, screen centre minus the point */
} D3IFPICK;

void d3_Frame(unsigned int mask, char flag, char tick);                               /* 0x43e680, d3_engine.c */
void d3if_ClearView(void);                                                         /* 0x448a50 */

/* 0x448ac0..0x44aa10 (d3_obj.h until layout 2026-10-22) */
typedef struct D3FINDCTX {          /* context of the name lookups */
    char *name;                     /* compared with the object's name (a leading '!' ignored), may be 0 */
    struct D3OBJECT *obj;           /* when set, only this object matches (compared by address) */
    struct D3OBJECT *found;
} D3FINDCTX;

extern const D3VECTOR4 d3_ZAxis;             /* 0x5ebb74, (0, 0, 1) */
typedef struct D3CORNERPT { int x, y; } D3CORNERPT;
typedef struct D3CORNERCTX {        /* 0x88 bytes: context of d3_CornerCB */
    void *tex;                      /* 0x00, the texture whose polygons are examined */
    D3VECTOR4 v[4];                 /* 0x04, the 3D vertex nearest to each screen corner of the texture's area */
    float uv[4][2];                 /* 0x44, its texture coordinates */
    D3CORNERPT pt[4];               /* 0x64, its screen position: top left, top right, bottom left, bottom right */
    signed char found;              /* 0x84 */
    char pad85[3];
} D3CORNERCTX;

float d3_YawTo(D3OBJECT *obj, const D3VECTOR *p);                          /* 0x448ac0 */
char d3_ScreenToUV(float sx, float sy, D3OBJECT *obj, void *tex, float *outu, float *outv);   /* 0x448e60 */
D3OBJECT *d3_FindObjectNoCase(D3OBJECT *a, int flags, D3OBJECT *c, char *name);  /* 0x449770, case-insensitive */
void d3_WorldToParent(D3OBJECT *obj, const D3VECTOR *pos, D3MATRIX *rot, D3VECTOR *outpos, D3VECTOR *outrot);  /* 0x4497f0 */
void d3_SetWorldPosRot(D3OBJECT *obj, const D3VECTOR *pos, D3MATRIX *rot);        /* 0x449920 */


extern int d3o_LightSet;            /* 0x5fbcfc, the current light set */
extern int d3o_FogSet;              /* 0x5fbd00, the current fog set */
extern float d3o_FogScale;          /* 0x5fbd04, the factor of the fog distances (1 - the fog option %) */

char d3_SetParent(D3OBJECT *obj, D3OBJECT *parent);                                    /* 0x449960 */
char d3_SetLightKey(D3OBJECT *obj, unsigned int key, float t);                          /* 0x449b20 */
char d3_ScaleLightCB(D3OBJECT *obj, float *scale);                                      /* 0x449d80 */
char d3_SetLightKeyCB(struct D3OBJECT *obj, float *time);                                      /* 0x449da0 */
char d3_SetLightSet(unsigned int set, float t, float scale, char calc);                 /* 0x449de0 */
char d3_SetFogSet(unsigned int a, unsigned int b, float t);                             /* 0x44a170 */
struct VFSFILE; struct D3FLMAP;        /* vfs.h / d3_fl.h: the tags, so the prototypes below do not declare new ones */
void d3_WriteObject(struct VFSFILE *f, struct D3OBJECT *obj);                                         /* 0x44a2c0 */
void d3_WriteMap(struct VFSFILE *f, struct D3FLMAP *map);                                                /* 0x44a770 */
int d3_SceneVersion(unsigned int version);                                              /* 0x44a9e0 */
void d3_SaveScene(char *name, struct VFSFILE *f);                                              /* 0x44aa10 */

void d3if_Reset(void);                                         /* 0x4473f0 */

/* declared in other units' headers before (moved to the owner) */
void d3if_FreeSprite(struct TSTEXTURE *t);  /* 0x4481e0 */
struct TSTEXTURE *d3if_LoadSprite(char *name, char glow);  /* 0x448200 */
char d3if_Reload(D3OBJECT *obj, char *name);  /* 0x447340 */

#endif
