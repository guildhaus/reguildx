/* ts_texture.c -- texture manager (D:\develop\Units\d3\ts_texture.c, allocation tags "d3_ts:...").
   Types and globals of the TU. Names are ours. */
#ifndef TS_TEXTURE_H
#define TS_TEXTURE_H
#include <windows.h>                  /* Win32 types */
#include <d3d.h>                      /* Direct3D / DirectDraw types */

#include "d3_types.h"
typedef D3TEXFLAGS TSFLAGS;         /* tex_Load flags, passed by value: b[0] 0xff: slot from the front; b[2] 1: from
                                       the back, 4: animation frame */

/* Hardware surface cache entry: surfaces of released textures are kept for reuse. */
typedef struct TSCACHE {            /* 0x14 bytes, ts_CacheSize of them at ts_Cache */
    IDirectDrawSurface4 *surf;
    IDirect3DTexture2 *d3dtex;      /* 0x04 */
    unsigned int size;              /* 0x08, texture size; 0 = free entry */
    unsigned int time;              /* 0x0c, d3_FrameCount when stored */
    unsigned char hicolor;          /* 0x10, TSTEXTURE.hicolor */
    unsigned char nomip;            /* 0x11, TSTEXTURE.nomip */
    char pad12[0x2];
} TSCACHE;

/* One texture slot. */
typedef struct TSTEXTURE {          /* 0x80 bytes, d3_TexCount of them at d3_Textures */
    char name[0x40];
    int refs;                       /* 0x40, 0 = free slot */
    unsigned char *data;            /* 0x44, 8-bit pixels (software renderer) */
    unsigned short *hicol;          /* 0x48, colour table from ts_GetHiColTab */
    union {                         /* 0x4c */
        int mask;                   /* size*size-1 | size-1; for an alias: index of the original */
        struct D3FLCACHE *cache;    /* a "*fltx" ground cache texture: its cache record (d3fl_GetTexture) */
    };
    int group;                      /* 0x50, animation group, -1 = none */
    int stamp;                      /* 0x54, d3_FrameCount of the last use */
    int reserved;                   /* 0x58, no reader in the game: cleared whenever the slot is created, evicted or unloaded (reasoned: unused) */
    struct TSTEXTURE *src;          /* 0x5c */
    IDirectDrawSurface4 *surf;      /* 0x60 */
    union {                         /* 0x64, the original calls it surftext (D3DCHECK texts) */
        IDirect3DTexture2 *d3dtex;
        IDirect3DTexture2 *surftext;
    };
    union {                         /* 0x68 */
        struct {
            unsigned char wrap : 1;     /* tex_Load opts bit 0: the triangles wrap their uv (D3VERTEX.wrap) */
            unsigned char alias : 1;    /* shares the surfaces of d3_Textures[mask] */
            unsigned char hicolor : 1;  /* 16-bit surface (d3_TexFormat16) */
            unsigned char nomip : 1;    /* name contains "_NM": no mipmaps */
            unsigned char nocull : 1;   /* tex_Load opts bit 1: no culling for the triangles using it (d3_SetVertexColors) */
            unsigned char mirror : 1;   /* tex_Load opts bit 6 (not for alpha textures): d3_MirDrawObject draws the mirror
                                           pass of an object with such a texture */
            unsigned char noscale : 1;  /* name contains "_NS": not shrunk by d3_MipSkip */
            unsigned char precached : 1; /* d3d_PrecacheTexture done (d3if_PrecacheCB, d3fl_Prerender) */
        };
        unsigned char bits;         /* the byte, copied whole into the triangles' draw flags */
    };
    unsigned char f69 : 5;          /* 0x69, the u scroll: index into ts_ScrollV (d3_DrawSortedD3D) */
    unsigned char f6a : 5;          /* 0x6a, the v scroll: index into ts_ScrollU */
    unsigned char pad6b;
    TSFLAGS flags;                  /* 0x6c, the flags tex_Load was called with */
    union {                         /* 0x70 */
        int anim;
        struct {
            unsigned char frames;   /* 0x70 */
            unsigned char frame;    /* 0x71 */
            unsigned char speed : 4; /* 0x72, index into d3_AnimDiv */
        };
    };
    unsigned int size;              /* 0x74 */
    unsigned int origsize;          /* 0x78 */
    unsigned char bpp;              /* 0x7c */
    unsigned char filebpp;          /* 0x7d */
    char pad7e[0x2];
} TSTEXTURE;

/* Inline-asm copy in the style of D3_ZERO (d3.h), both pointers named directly in the asm. */
#define D3_COPY_AT(dst, src, size) {                                \
    int _cn = (size);                                               \
    __asm mov edi, dst                                              \
    __asm mov esi, src                                              \
    __asm mov ebx, _cn                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3_ZERO_LABEL(__LINE__)                               \
    __asm rep movsb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep movsd                                                 \
    __asm D3_ZERO_LABEL(__LINE__): add ecx, ebx                     \
    __asm rep movsb                                                 \
}

typedef struct TSHICOL {            /* 0x308 bytes, ts_HiColCount of them at ts_HiCol */
    unsigned short *tab;            /* 0x8200 bytes: 64 shades of 256 colours, then the 256 colours */
    unsigned char rgb[0x100][3];    /* 0x004 */
    unsigned int free;              /* 0x304, unused palette entries */
} TSHICOL;

void tex_SetPalette(void *pal);                                    /* 0x45fb30 */

/* declared in other units' headers before (moved to the owner) */
void tex_Exit(void);  /* 0x45fd00 */
void tex_Init(int count, int maxhicol, int mips, unsigned int cache);  /* 0x45fa80 */
void tex_ReloadAll(char keep, void (*cb)(int, int, int));  /* 0x461090 */
void ts_UpdateScroll(unsigned long time);  /* 0x460cb0 */
char *tex_FindFile(char *name);  /* 0x45f9f0 */

#endif
