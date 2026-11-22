struct D3VECTOR4;
/* d3_anim.c types: vertex animations ("d3_anim_CalculateAnimNormals" allocation tags).
   Field names unkXXX are byte offsets whose meaning is not known yet. */
#ifndef D3_ANIM_H
#define D3_ANIM_H
#include "d3.h"                       /* the D3 records and typedefs this header names */

typedef struct D3ANIMFRAME {        /* 0xc0 bytes, one key frame of a vertex animation */
    int time;                       /* 0x00, start time of the frame (ch_CheckAniMorph blends over half the gap) */
    int count;                      /* 0x04 */
    D3VECTOR base;                  /* 0x08, packed positions: base + byte * scale */
    D3VECTOR scale;                 /* 0x14 */
    D3VECTOR move;                  /* 0x20, root motion of the whole segment (position) */
    D3VECTOR turn;                  /* 0x2c, (angles) */
    float radius;                   /* 0x38, mesh radius minus the frame's extent */
    D3VECTOR min;                   /* 0x3c, bounding box */
    D3VECTOR max;                   /* 0x48 */
    struct { D3VECTOR pos, rot; } bone[4];  /* 0x54, skeleton animations: bone transforms */
    unsigned char *packed;          /* 0xb4, 3 bytes per vertex */
    unsigned char *normals;         /* 0xb8, 3 bytes per vertex */
    D3VECTOR *pos;                  /* 0xbc, 12 bytes per vertex */
} D3ANIMFRAME;

typedef struct D3ANIMDATA D3ANIMDATA;
struct D3ANIMDATA {                 /* 0x16c bytes, cached animation (LRU list) */
    char name[0x140];
    int nverts;                     /* 0x140 */
    int nbones;                     /* 0x144, skeleton animations: bone names follow the name */
    int nframes;                    /* 0x148 */
    int refs;                       /* 0x14c */
    int first;                      /* 0x150, first frame of the animation range (D3BASTREAM.first) */
    int last;                       /* 0x154, last frame, -1: nframes (D3BASTREAM.last) */
    unsigned int lastuse;           /* 0x158, d3_FrameCount at the last use */
    D3ANIMFRAME *frames;            /* 0x15c */
    D3ANIMDATA *next;               /* 0x160 */
    D3ANIMDATA *prev;               /* 0x164 */
    signed char normals;            /* 0x168, normals calculated */
    signed char relative;           /* 0x169, points relative to the frame position (D3BASTREAM.relative) */
    char pad16a[0x2];
};

int d3anim_GetSize(D3ANIMDATA *a);                                                     /* 0x434a80 */
char d3anim_Purge(int limit, int size);                                                 /* 0x434af0 */
void d3anim_Release(D3ANIMDATA *a, char now);                                           /* 0x434b70 */
float d3anim_MaxRadius(D3VECTOR4 *v, int n);                                            /* 0x434d00 */
void d3anim_CalculateAnimNormals(D3ANIMDATA *a, D3BGF *mesh);                     /* 0x434d60 */

int d3anim_NextFrame(D3ANIMFLAGS f, int frame, int a, int b, int c);                        /* 0x4324e0 */
char d3anim_MapBones(D3OBJECT *obj);                                                       /* 0x4319e0 */
void d3anim_PoseBones(D3OBJECT *obj);                                                       /* 0x431ae0 */

/* Object path animations (d3anim_CreatePath; D3ANIM in d3.h is the same struct, D3ANIMKEY the same key). */
typedef struct D3PATHKEY {          /* 0x58 bytes */
    int time;                       /* frames; multiplied by 3 when the path is created */
    D3VECTOR pos;                   /* 0x04 */
    float unk10;
    D3VECTOR rot;                   /* 0x14 */
    D3VECTOR posin;                 /* 0x20, spline tangents (d3path_Tangents) */
    float unk2c;
    D3VECTOR posout;                /* 0x30 */
    float timeout;
    D3VECTOR rotin;                 /* 0x40 */
    D3VECTOR rotout;                /* 0x4c */
} D3PATHKEY;

typedef struct D3PATH {             /* 0x44 bytes, at D3OBJECT + 0x1d0 */
    int nkeys;
    int key;                        /* 0x04 */
    int next;                       /* 0x08 */
    int time;                       /* 0x0c */
    int maxStep;                    /* 0x10, the largest update step (ms) the path interpolates: a longer one
                                       relights the object instead of moving it (d3_anim.c:759), 100 at creation */
    D3VECTOR pos;                   /* 0x14, the object's position and angles at the start */
    D3VECTOR rot;                   /* 0x20 */
    D3ANIMFLAGS flags;              /* 0x2c */
    float fadeEnd;
    float frameTime;                /* 0x3c, sub-frame time accumulator (d3anim_StepObject's
                                       `acc - (int)acc`; d3path_Init clears it) */
    D3PATHKEY *keys;                /* 0x40 */
} D3PATH;

#define D3_OBJPATH(obj) (*(D3PATH **)((char *)(obj) + 0x1d0))

/* Inline-asm copy as D3_COPY (d3.h), with the destination temp declared (and stored) first. */
#define D3PATH_COPY(dst, src, size) {                               \
    void *_cd = (dst); int _cn = (size);                            \
    __asm mov edi, _cd                                              \
    __asm mov esi, src                                              \
    __asm mov ebx, _cn                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3PATH_COPY_LABEL(__LINE__)                           \
    __asm rep movsb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep movsd                                                 \
    __asm D3PATH_COPY_LABEL(__LINE__): add ecx, ebx                 \
    __asm rep movsb                                                 \
}
#define D3PATH_COPY_LABEL(n) D3_ZERO_CAT(d3path_copy_tail, n)

void d3path_Tangents(D3PATHKEY *k0, D3PATHKEY *k1, D3PATHKEY *k2);                      /* 0x432530 */
void d3path_Init(D3PATH *p);                                                            /* 0x433b50 */


/* ---- round 3 (worker d3_left) ---- */
/* Inline-asm copy with size, src and dst through temps, declared in this order (D3_COPY3 in d3_d3d.h). */
#define D3ANIM_COPY3(dst, src, size) {                              \
    int _cn = (size); void *_cs = (src); void *_cd = (dst);         \
    __asm mov edi, _cd                                              \
    __asm mov esi, _cs                                              \
    __asm mov ebx, _cn                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3ANIM_COPY3_LABEL(__LINE__)                          \
    __asm rep movsb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep movsd                                                 \
    __asm D3ANIM_COPY3_LABEL(__LINE__): add ecx, ebx                \
    __asm rep movsb                                                 \
}
#define D3ANIM_COPY3_LABEL(n) D3_ZERO_CAT(d3anim_copy3_tail, n)
#define D3ANIM_BONENAME(a, i) ((a)->name + 0x40 * ((i) + 1))     /* bone names follow the name */
D3ANIMDATA *d3anim_CreateMorphAnim(D3BGF *mesh, D3ANIMDATA *src, D3ANIMFRAME *frame, D3ANIMDATA *dst,
                                   D3ANIMFRAME *dframe, D3BGF *dmesh, char *name, int n);  /* 0x433f80 */

/* declared in other units' headers before (moved to the owner) */
void d3anim_ApplyRootMotion(D3OBJECT *obj, D3ANIMSLOT *s, int from, int to, int flags);  /* 0x4315c0 */
void d3anim_PauseAnim(D3SURF *ctl, char *name);  /* 0x435810 */
void d3anim_PlayAnim(D3SURF *ctl, char *name, char on);  /* 0x435870 */
void d3anim_SetFrame(D3OBJECT *obj, D3ANIMSLOT *s, int frame);  /* 0x435950 */
char d3anim_StepObject(D3OBJECT *obj, void *ctx);  /* 0x432750 */

#endif
