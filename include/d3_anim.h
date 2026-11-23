struct D3VECTOR4;
/* d3_anim.c types: vertex animations ("d3_anim_CalculateAnimNormals" allocation tags).
   Field names unkXXX are byte offsets whose meaning is not known yet. */
#ifndef D3_ANIM_H
#define D3_ANIM_H
#include "d3.h" /* the D3 records and typedefs this header names */

typedef struct
    D3ANIMFRAME { /* 0xc0 bytes, one key frame of a vertex animation */
  int time; /* 0x00, start time of the frame (ch_CheckAniMorph blends over half the gap) */
  int count;      /* 0x04, the time to the next frame (* 3 after loading) */
  D3VECTOR base;  /* 0x08, packed positions: base + byte * scale */
  D3VECTOR scale; /* 0x14 */
  D3VECTOR move;  /* 0x20, root motion of the whole segment (position) */
  D3VECTOR turn;  /* 0x2c, (angles) */
  float radius;   /* 0x38, mesh radius minus the frame's extent */
  D3VECTOR min;   /* 0x3c, bounding box */
  D3VECTOR max;   /* 0x48 */
  struct {
    D3VECTOR pos, rot;
  } bone[4];              /* 0x54, skeleton animations: bone transforms */
  unsigned char *packed;  /* 0xb4, 3 bytes per vertex */
  unsigned char *normals; /* 0xb8, 3 bytes per vertex */
  D3VECTOR *
      pos; /* 0xbc, 12 bytes per vertex (the loader's points, freed after packing) */
} D3ANIMFRAME;

typedef struct D3ANIMDATA D3ANIMDATA;
struct
    D3ANIMDATA { /* 0x16c bytes, cached animation (LRU list); d3_LoadBinaryAnimStream reads a
                    stream file ("tp_veranimstream") into it */
  union {
    char name
        [0x140]; /* the name in the first 0x40 bytes, the bone names after it (D3ANIM_BONENAME) */
    struct {
      char namePad[0x40];
      char boneNames
          [4]
          [0x40]; /* 0x040, the skeleton's bone names (the stream's link names, tag 0x38) */
    };
  };
  int nverts;  /* 0x140 */
  int nbones;  /* 0x144, skeleton animations: bone names follow the name */
  int nframes; /* 0x148 */
  int refs;    /* 0x14c */
  int first; /* 0x150, first frame of the animation range (the stream's chunks 0x29 / 0x2a, d3_LoadBinaryAnimStream) */
  int last;  /* 0x154, last frame, -1: nframes */
  unsigned int lastuse; /* 0x158, d3_FrameCount at the last use */
  D3ANIMFRAME *frames;  /* 0x15c */
  D3ANIMDATA *next;     /* 0x160 */
  D3ANIMDATA *prev;     /* 0x164 */
  signed char normals;  /* 0x168, normals calculated */
  signed char
      relative; /* 0x169, points relative to the frame position (d3_LoadBinaryAnimStream's relative) */
  char pad16a[0x2];
};

int d3anim_GetSize(D3ANIMDATA *a);                            /* 0x434a80 */
char d3anim_Purge(int limit, int size);                       /* 0x434af0 */
void d3anim_Release(D3ANIMDATA *a, char now);                 /* 0x434b70 */
float d3anim_MaxRadius(D3VECTOR4 *v, int n);                  /* 0x434d00 */
void d3anim_CalculateAnimNormals(D3ANIMDATA *a, D3BGF *mesh); /* 0x434d60 */

int d3anim_NextFrame(D3ANIMFLAGS f, int frame, int a, int b,
                     int c);          /* 0x4324e0 */
char d3anim_MapBones(D3OBJECT *obj);  /* 0x4319e0 */
void d3anim_PoseBones(D3OBJECT *obj); /* 0x431ae0 */

/* Object path animations: D3PATH / D3PATHKEY in d3.h (D3ANIMKEY there is the same key as d3anim_CreatePath takes it). */
/* Inline-asm copy as D3_COPY (d3.h), with the destination temp declared (and stored) first. */
/* clang-format off */
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
/* clang-format on */
#define D3PATH_COPY_LABEL(n) D3_ZERO_CAT(d3path_copy_tail, n)

void d3path_Tangents(D3PATHKEY *k0, D3PATHKEY *k1,
                     D3PATHKEY *k2); /* 0x432530 */
void d3path_Init(D3PATH *p);         /* 0x433b50 */

/* ---- round 3 (worker d3_left) ---- */
/* Inline-asm copy with size, src and dst through temps, declared in this order (D3_COPY3 in d3_d3d.h). */
/* clang-format off */
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
/* clang-format on */
#define D3ANIM_COPY3_LABEL(n) D3_ZERO_CAT(d3anim_copy3_tail, n)
#define D3ANIM_BONENAME(a, i)                                                  \
  ((a)->name + 0x40 * ((i) + 1)) /* bone names follow the name */
D3ANIMDATA *d3anim_CreateMorphAnim(D3BGF *mesh, D3ANIMDATA *src,
                                   D3ANIMFRAME *frame, D3ANIMDATA *dst,
                                   D3ANIMFRAME *dframe, D3BGF *dmesh,
                                   char *name, int n); /* 0x433f80 */

/* declared in other units' headers before (moved to the owner) */
void d3anim_ApplyRootMotion(D3OBJECT *obj, D3ANIMSLOT *s, int from, int to,
                            int flags);                        /* 0x4315c0 */
void d3anim_PauseAnim(D3SURF *ctl, char *name);                /* 0x435810 */
void d3anim_PlayAnim(D3SURF *ctl, char *name, char on);        /* 0x435870 */
void d3anim_SetFrame(D3OBJECT *obj, D3ANIMSLOT *s, int frame); /* 0x435950 */
char d3anim_StepObject(D3OBJECT *obj, void *ctx);              /* 0x432750 */

#endif
