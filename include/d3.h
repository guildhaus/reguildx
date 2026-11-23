/* d3 engine types and functions as far as reconstructed.
   Field names unkXXX are byte offsets whose meaning is not known yet; pads keep the offsets exact.
   Function names are ours unless noted; the address is the function's location in GildeGold.exe. */
#ifndef D3_H
#define D3_H

typedef struct D3SURF D3SURF;      /* below: a surface of a mesh (D3MESH.surf), what D3OBJECT.info points to */
struct D3ANIMSLOT;

#include "d3_types.h"                /* D3VECTOR, D3VECTOR4, D3SCENE, D3TEXFLAGS */

typedef struct D3MATRIX {
    float _11, _12, _13, _14;
    float _21, _22, _23, _24;
    float _31, _32, _33, _34;
    float _41, _42, _43, _44;
} D3MATRIX;

typedef struct D3RECT {
    int left, top, right, bottom;
} D3RECT;

struct D3OBJECT;
struct D3OBJECT;

typedef struct D3OBJECT D3OBJECT;
typedef struct D3OBJBITS {          /* D3OBJECT::state as bitfields (D3OBJECT.bits) */
    unsigned char top : 1;          /* starts a group in a top-level list */
    unsigned char linked : 1;
    unsigned char dirty : 1;
    unsigned char drawDirty : 1;    /* the dirty bit as d3_DrawObjectCB took it (it clears dirty) */
    unsigned char b4 : 1;           /* cleared by d3_DrawObjectCB */
    unsigned char b5 : 1;
    unsigned char reclip : 1;       /* 0x40, d3_DrawObjectCB clips the object anew and sets its info */
    unsigned char b7 : 1;
} D3OBJBITS;
typedef struct D3LIGHTKEY {         /* 0x38 bytes, one of the 7 day-time keys of a light (d3_SetLightKey blends two) */
    D3VECTOR pos;                   /* 0x00, relative to the light's parent */
    D3VECTOR rot;                   /* 0x0c */
    D3VECTOR color;                 /* 0x18, -> the object's lightColor (sv_SetSkyLightColors copies the sky tables in) */
    union {
        float intensity;            /* 0x24, -> the object's power; 0 = off */
        int intensityBits;          /* the same bits as an int (the scene file's bio_wr_i, d3_WriteObject) */
    };
    union {
        float range;                /* 0x28, -> the object's range */
        int rangeBits;
    };
    union {
        float atten;                /* 0x2c, -> the object's atten */
        int attenBits;
    };
    union {
        float flicker;              /* 0x30, the key's flicker factor; 0.3 from d3_InitObject, else the scene file's */
        int flickerBits;
    };
    int interval;                   /* 0x34, its flicker interval; 15 from d3_InitObject, else the scene file's */
} D3LIGHTKEY;

typedef struct D3LIGHTINFO {        /* 0x1ac bytes, "d3:SpawnObject(lightinfo)": D3OBJECT.light of the object types >= 5 */
    D3LIGHTKEY keys[7];             /* 0x000 */
    D3VECTOR dir;                   /* 0x188, direction in camera space (type 7) */
    unsigned long time;             /* 0x194, last flicker step (d3_Time) */
    struct D3LREC *list;            /* 0x198, the lit vertex records (d3_light.h); cleared in d3_InitObject */
    union {
        float flicker;              /* 0x19c, 0.3 from d3_InitObject, else the scene file's */
        int flickerBits;            /* the same bits as an int (the scene file's bio_wr_i, d3_WriteObject) */
    };
    unsigned int interval;          /* 0x1a0, 15 from d3_InitObject, else the scene file's */
    float phase;                    /* 0x1a4, added to the day time by d3_SetLightKey: the random -0.9 .. 0.9 a lamp
                                       gets from sv_SetLampRamp */
    unsigned char on;               /* 0x1a8, the light reaches the object being lit (d3_light.c) */
    char pad1a9[0x3];
} D3LIGHTINFO;

struct D3OBJECT {
    union {
        char name[0x4c];            /* compared with _strcmpi by name lookups; real length unknown */
        struct {
            char padtime[0x40];
            unsigned long animTime; /* 0x40, d3_Time of the object's last vertex animation step (d3anim_StepObject; set
                                       by d3anim_CreatePath and by d3_ToggleRLightCB when it switches an "r" light) */
            unsigned long lightTime;    /* 0x44, d3_Time of the last lighting (d3_light.c); d3_anim.c compares it
                                       with a timeout */
        };
        struct {
            char padname[0x48];
            union {
                unsigned int pickId;    /* 0x48, the game record the object stands for: 0x1000000 | an object
                                           prototype (ai_Goods), 0x2000000 | a building type (ai_BTypes; f3init's
                                           init_SceneNameToPrototype), a character's body its AICHAR id | 0x3000000
                                           (ls_ReadSceneRecords) */
                signed char pickBytes[4]; /* the same word by byte: [3] its kind (1 object, 2 building, 3 character) */
            };
        };
    };
    D3VECTOR pos;                   /* 0x4c */
    float flickerEnd;               /* 0x58, a light's flicker factor the current interval runs to (d3_light.c) */
    union {
        D3VECTOR savedPos;          /* 0x5c, a camera's saved position (objectFlags & 1: applied on load, d3_int_io.c), its
                                       default view (sv_BorderCameraView) */
        D3VECTOR lightColor;        /* a light's colour */
    };
    union {
        float radius;               /* 0x68, a type-0 object's radius (read from the scene file; d3if's screen size) */
        int radiusBits;             /* the same bits as an int: the scene file writes it with bio_wr_i (d3_WriteObject) */
        float soundRange;           /* an "sfx_" object's sound radius (init_SoundObjectHook: + 50 = the range) */
        float flickerStart;         /* a light's flicker factor the current interval started from (d3_light.c) */
    };
    D3VECTOR pivot;                 /* 0x6c, the point the object's rotation turns about (d3_pose.c) */
    D3VECTOR posOffset;               /* 0x78 */
    D3VECTOR rotation;                /* 0x84, rotation angles in degrees; d3_SetObjectRot writes them */
    union {
        D3VECTOR savedRot;          /* 0x90, a camera's saved angles, with savedPos */
        D3VECTOR lightParams;       /* a light's range / power / attenuation, as the scene reader copies them */
        struct {
            union {
                float range;        /* 0x90, a light's range */
                int rangeBits;      /* the same bits as an int (the scene file's bio_wr_i, d3_WriteObject) */
            };
            union {
                float power;        /* 0x94, a light's power, 0: off */
                int powerBits;
            };
            union {
                float atten;        /* 0x98, a light's attenuation */
                int attenBits;
            };
        };
    };
    struct D3CAMVIEW {              /* 0x9c, 10 position + direction pairs: the camera's preset views;
                                       sv_BorderCameraMove moves the camera to 1 / 2 (above / below the window) and
                                       3 / 4 (left / right), an all-zero position meaning the view is not set */
        D3VECTOR pos;
        D3VECTOR dir;
    } views[10];
    D3MATRIX matrix;                /* 0x18c */
    struct D3SURF *info;         /* 0x1cc, the current surface of the mesh (material->surf[k]) */
    struct D3PATH *path;            /* 0x1d0, the path animation it follows, 0: none */
    D3EVENT *events;                /* 0x1d4, the object's D3E_NEVENTS event handlers (d3e_RegisterEvent), 0 = none */
    D3VECTOR cam;                   /* 0x1d8, a light's position in camera space (d3_light.c) */
    float radius2;                  /* 0x1e4, a light's squared radius */
    D3LIGHTINFO *light;             /* 0x1e8, the light record of the object types >= 5 */
    struct D3MESH *material;        /* 0x1ec, the mesh: its surfaces (levels of detail) and their animations */
    D3OBJECT *next;                 /* 0x1f0, sibling list */
    D3OBJECT *prev;                 /* 0x1f4 */
    D3OBJECT *parent;               /* 0x1f8, set with d3_SetParent */
    D3OBJECT *child;                /* 0x1fc */
    void *owner;                    /* 0x200, the game record the object stands for (a character's body: its AICHAR) */
    D3OBJECT *flagObj;              /* 0x204, the flag put up at the object (cm.c: the escape flag at a fight's dummy) */
    D3SCENE *scene;                 /* 0x208 */
    struct D3SOUND *sound;          /* 0x20c, set by d3snd_Attach */
    union {
        unsigned char state;        /* 0x210, object state bits: 1 = starts an object group, 2 = linked, 4 = dirty,
                                       8 = mirrored, 0x20 = vertex normals, 0x80 = no camera transform */
        struct D3OBJBITS bits;      /* the same bits by name (d3_DrawObjectCB) */
    };
    union {
    unsigned char objectFlags;      /* 0x211, object flags, read and written bit by bit: 1 = has a saved position
                                       and angle (applied on load; d3t_RecordKeys keys it), 2 = saved with the
                                       scene, 4 = shadow caster (d3s_LightCB), 8 = simple shadow, 0x10 = light
                                       keeps its stored direction (type 7), 0x20 = shadow fake object (no box,
                                       tracks the z range), 0x40 = mirrored (d3_mir.c), 0x80 = alpha alias applied
                                       (d3_SetObjectAlpha) */
        struct D3OBJFLAGBITS {      /* the same bits by name (the scene reader rd_object, ch.c) */
            unsigned char savedPose : 1;    /* 1 */
            unsigned char sceneSaved : 1;   /* 2 */
            unsigned char shadowCaster : 1; /* 4 */
            unsigned char simpleShadow : 1; /* 8 */
            unsigned char keepDir : 1;      /* 0x10 */
            unsigned char shadowFake : 1;   /* 0x20 */
            unsigned char mirrored : 1;     /* 0x40 */
            unsigned char alphaAlias : 1;   /* 0x80 */
        } flagBits;
        struct D3MIRBITS {          /* the mirror bit as d3_MirDrawObject stores it: through flagBits' single-bit
                                       fields its store compiles otherwise (shape) */
            unsigned char b0 : 6;
            unsigned char mirrored : 1;     /* 0x40, its mirror image is visible */
            unsigned char b7 : 1;
        } mirBits;
    };
    union {
    unsigned char stateFlags;       /* 0x212, object flags, read and written bit by bit: 2 = vertex colors set
                                       (d3t_SetColor), 0xc = shadow mask tested against D3SM.mask, 0x10 = cast
                                       shadows despite the mask, 0x80 = world matrix current (d3_UpdateWorldMatrix) */
        struct D3OBJSTATEBITS {     /* the same bits by name (the scene reader rd_object) */
            unsigned char s0 : 1;
            unsigned char vertexColors : 1; /* 2 */
            unsigned char transient : 2;    /* 0xc, the shadow mask bits (the script's SetTransient) */
            unsigned char blocked : 1;      /* 0x10, casts shadows despite the mask (the script's SetBlocked) */
            unsigned char s5 : 1;
            unsigned char s6 : 1;
            unsigned char worldCurrent : 1; /* 0x80 */
        } stateBits;
    };
    unsigned char flags;            /* 0x213 */
    int meshMode;                   /* 0x214, reasoned guess at the meaning: 0 from d3_InitObject, 3 for the
                                       shadow_fake object (d3_Init), 4 once d3io_AttachStock adds a level-of-detail
                                       surface, else the scene file's value for the mesh types 1 / 4 (rd_object /
                                       d3_WriteObject); no reader in the original's code besides the writer */
    int type;                       /* 0x218, 4 = mesh */
    int type0;                      /* 0x21c, the object's real type: d3if_Show saves it there while it hides
                                       the object as type 1, and the spawn sets it */
    int kind;                       /* 0x220, object kind from the file: 1 = per-vertex lit (d3_LightApply), 2 = character, 5 = hand object / sun rays; d3_ReloadMeshes selects one kind */
    int mask;                       /* 0x224, the object's mask bits, tested against the pick mask
                                       (d3if_PickCB: p->mask && !(obj->mask & p->mask)); 1 for the sun rays,
                                       -1 / 0 from the loader */
};

typedef union D3CLIP {              /* clip code of a point or a box */
    unsigned char raw;              /* the code as a whole: cleared, and | / & of two codes */
    struct {
        unsigned char left : 1;
        unsigned char right : 1;
        unsigned char top : 1;
        unsigned char bottom : 1;
        unsigned char znear : 1;
        unsigned char zfar : 1;
        unsigned char out : 1;      /* all points outside one plane */
        unsigned char b7 : 1;
    };
} D3CLIP;

typedef struct D3TRIBITS {          /* D3TRI.drawFlags as bitfields */
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;           /* 4 = no culling */
    unsigned char b3 : 1;           /* 8 = the texture wraps */
    unsigned char b47 : 4;
} D3TRIBITS;

typedef struct D3UV { float u, v; } D3UV;

typedef struct D3VERTEX {           /* 0x50 bytes, a point of a mesh (D3SURF.keys, then the 8 corners of the bounding
                                       box), of a particle's quad or of a mirror copy: position, screen position, normal,
                                       colours */
    union {
        struct {
            float x, y, z;          /* 0x00, camera space */
        };
        D3VECTOR pos;               /* 0x00, the same three floats (the 3-float callees: d3_TriNormal) */
    };
    float u;                        /* 0x0c, a texture coordinate while clipping (d3_ClipPoly) */
    union {
        struct {
            float sx, sy;           /* 0x10, screen position */
        };
        struct {
            float gx, gz;           /* 0x10, a height map point (d3_sm.c): the position in map cells */
        };
        struct {
            float shadowU, shadowV; /* 0x10, the point's position in its shadow texture (d3s.c, texels):
                                       d3s_ProjectShadow writes it, d3s_ShadowPoly rasterises the triangles */
        };
    };
    float sz;                       /* 0x18 */
    float rhw;                      /* 0x1c */
    union {
        struct {
            float nx, ny, nz;       /* 0x20, normal (d3_vtx.c, d3_light.c) */
        };
        struct {
            float tu, tv;           /* 0x20, environment map coordinates (d3_EnvMapCoords), the texture
                                       coordinates of the clipper's and the draw loops' points */
        };
        D3UV uv;                    /* the same two floats as a texture coordinate */
    };
    float v;                        /* 0x2c, the other texture coordinate while clipping */
    union {
        D3VECTOR light;             /* 0x30, sum of the lights that reach the vertex (d3_light.c) */
        struct {
            float r, g, b;
        };
    };
    float pad3c;
    union {
        unsigned long color;        /* 0x40, the current colour: the static lights plus the dynamic ones */
        unsigned char col[4];       /* the same by byte (the clipper interpolates them) */
        D3COLOR c;
        D3COLOR lit;
        struct {
            unsigned char pad40;
            unsigned char hmFlags;  /* 0x41, a height map point's flags (d3_sm.c) */
            unsigned char hmHeight; /* 0x42, a height map point's height in map units */
            unsigned char pad43;
        };
    };
    union {
        unsigned long specular;     /* 0x44 */
        D3COLOR s;
        D3COLOR base;               /* the colour from the static lights (d3_light.c) */
    };
    union {
        struct D3BGFVERT *src;      /* 0x48, the stock object's point (D3BGF.vtx) */
        float *srcPos;              /* the same as its six floats (d3s.c: a shadow mesh point's position in
                                       d3s_Verts, as D3BGF.verts) */
    };
    union {
        signed char flags;          /* 0x4c, bit 7 = visible (d3_light.c: reached by the light being processed;
                                       the stock attach: used by a triangle) */
        D3CLIP clip;                /* the same byte as the clip code d3_ClipMesh computes */
        unsigned char rawFlags;
    };
    union {
        unsigned char wrap;         /* 0x4d, the triangle's texture wraps (its flags bit 0, d3_InflateObject) */
        signed char used;           /* 0x4d, d3_EnvMapCoords: the point gets environment map coordinates */
    };
    char pad4e[0x1];
    unsigned char fog;              /* 0x4f */
} D3VERTEX;

D3VERTEX *d3_GetBoxVerts(D3OBJECT *obj, struct D3SURF *info, D3MATRIX *m);           /* 0x459ab0 */

typedef struct D3TRI {              /* 0x28 bytes, a triangle of a mesh (D3SURF.tris), a particle or a mirror copy */
    D3VERTEX *v[3];
    void *clip;                     /* 0x0c, &d3_ClipInfo[clip code] */
    union {
        struct D3BGFPOLY *src;      /* 0x10, the stock object's polygon */
        float *uv;                  /* 0x10, the (u, v) per corner: a particle's static UV table, or the
                                       polygon's own (D3BGFPOLY starts with them) as the draw loops read it */
    };
    struct TSTEXTURE *tex;          /* 0x14 */
    float zofs;                     /* 0x18, depth offset: d3_DrawSortedD3D adds it (less the frame's
                                       nearest z) to every vertex's z */
    float uofs, vofs;               /* 0x1c, texture offsets added to u and v (with the texture's scroll) */
    union {
        unsigned char flags;        /* 0x24, bit 7 = visible, 0x40 = double sided drawn, 0x10 = double sided */
        signed char sflags;         /* 0x24, the same byte where bit 7 is tested as the sign */
        struct {
            unsigned char hm0 : 6;
            unsigned char hmSolid : 1;  /* a height map triangle (d3_sm.c): no shadow test (steep or flagged) */
            unsigned char hmCast : 1;   /* a height map triangle: casts a shadow */
        };
    };
    unsigned char unk25;
    union {
        unsigned char drawFlags;    /* 0x26, bit 2 (4) = no culling, bit 3 (8) = wrap; a height map triangle:
                                       2 = skip, 4 = always casts; a terrain shadow triangle (d3s.c): 2 = steep */
        D3TRIBITS bits;
    };
    char pad27[0x1];
} D3TRI;

void d3_TransformSurf(D3OBJECT *obj);                                                       /* 0x43d7c0 */
char d3_RelightObject(struct D3OBJECT *obj);                                                       /* 0x453280 */
void d3_LocalToWorld(struct D3OBJECT *obj, const struct D3VECTOR *in, struct D3VECTOR *out);                             /* 0x458c10 */
void d3_PointToWorld(struct D3OBJECT *obj, struct D3VECTOR *in, struct D3VECTOR *out);                          /* 0x458a20, writes out and the angles after it */

#define D3_MAX_SCENES 64


struct TSTEXTURE;                   /* a texture slot (ts_texture.h), what tex_Load returns */

/* Inline-asm clear used all over the engine (284 copies): byte stores up to dword alignment,
   then dwords, then the remaining bytes. */
#define D3_ZERO_CAT(a, b) a##b
#define D3_ZERO_LABEL(n) D3_ZERO_CAT(d3_zero_tail, n)   /* unique per line, so D3_ZERO can be used twice in one function */
#define D3_ZERO(dst, size) {                                        \
    int _zn = (size); void *_zp = (dst);                            \
    __asm mov edi, _zp                                              \
    __asm mov ebx, _zn                                              \
    __asm xor eax, eax                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3_ZERO_LABEL(__LINE__)                                        \
    __asm rep stosb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep stosd                                                 \
    __asm D3_ZERO_LABEL(__LINE__): add ecx, ebx                            \
    __asm rep stosb                                                 \
}

/* Same with the destination named directly in the asm (a plain variable, e.g. a global): no pointer temp. */
#define D3_ZERO_AT(var, size) {                                     \
    int _zn = (size);                                               \
    __asm mov edi, var                                              \
    __asm mov ebx, _zn                                              \
    __asm xor eax, eax                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3_ZERO_LABEL(__LINE__)                                        \
    __asm rep stosb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep stosd                                                 \
    __asm D3_ZERO_LABEL(__LINE__): add ecx, ebx                            \
    __asm rep stosb                                                 \
}

extern D3SCENE d3_Scenes[D3_MAX_SCENES];   /* 0xfd7ba0 */
extern D3SCENE *d3_DefaultScene;            /* 0x5fb5b0 */
extern int d3_CurrentScene;                 /* 0x633444 */
extern D3OBJECT *d3_Camera;                 /* 0xfc2dec */
extern D3RECT d3_Viewport;                  /* 0xfc2930 */
extern volatile unsigned long d3_Time;      /* 0x6333cc, milliseconds; re-read at every use */
extern struct IDirect3DDevice3 *d3d_Device; /* 0x633418 */
extern long d3d_hr;                         /* 0x14661a4, result of the last checked D3D call */

/* Checked D3D call; the original passes __FILE__, __LINE__ and the call text. Callers pin __LINE__
   with #line so the pushed line number matches the original. */
#define D3DCHECK(call) if ((d3d_hr = (call)) != 0) d3d_Error(__FILE__, __LINE__, #call)

typedef char (*D3OBJECTCB)(D3OBJECT *obj, void *ctx);

char d3_ForEachObject(struct D3SCENE *scene, struct D3OBJECT *obj, unsigned int mask, D3OBJECTCB cb, void *ctx); /* 0x438d40 */
void d3_ReleaseTexture(struct D3SURF *ctl, char *name);                                 /* 0x435740 */
void d3_UpdateObject(D3OBJECT *obj, unsigned char full);                                           /* 0x43b6b0 */
void d3_InflateObject(D3OBJECT *obj);                                                       /* 0x43dbc0 */
void d3_MatFromAngles(const D3VECTOR *v, D3MATRIX *m);                                           /* 0x4545c0 */
char d3if_SelectScene(int index, char keep);                                                /* 0x4478e0 */
typedef struct D3ANIMFLAGS {        /* 12 bytes passed by value to d3anim_CreatePath / d3anim_NextFrame / d3anim_StartAnim */
    union {
        unsigned char b[12];
        struct {                    /* the bits the path loader names (d3_LoadObjectAnim) */
            unsigned char b0;
            unsigned char c0 : 1;   /* b[1], D3PATH +0x2d: 0x20 = finished, 0x10 = loop, 0x08, 0x04 */
            unsigned char rev : 1;  /* b[1] bit 1: play backwards, starts at the last key */
            unsigned char c2 : 3;
            unsigned char c5 : 1;   /* b[1] bit 5, cleared after loading */
            unsigned char c6 : 2;
            unsigned char b2, b3, b4, b5, b6, b7;
            unsigned char d0 : 1;   /* b[8], D3PATH +0x34 */
            unsigned char d1 : 1;   /* set from d3_LoadObjectAnim's reload argument */
            unsigned char d2 : 6;
            unsigned char b9, b10, b11;
        };
    };
} D3ANIMFLAGS;

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

typedef struct D3PATH {             /* 0x44 bytes, D3OBJECT.path: a path animation (d3anim_CreatePath, d3_LoadObjectAnim) */
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


struct D3ANIMDATA;                  /* d3_anim.h: a cached vertex animation */
typedef struct D3ANIMSLOT {         /* 0x7c bytes */
    int frame;                      /* 0x00, current key frame */
    int nextFrame;                  /* 0x04, the frame the blend interpolates to (d3anim_NextFrame) */
    int subFrame;                   /* 0x08, position inside the frame, in 1/count units */
    int lastFrame;                  /* 0x0c, last frame the root motion was applied at */
    int lastSub;                    /* 0x10, sub-frame within lastFrame */
    int attachFirst;                /* 0x14, frame the bone attach starts at, -1: none */
    int attachLast;                 /* 0x18, frame it ends at, -1: none */
    int attachBone;                 /* 0x1c, bone index of the attached object */
    D3VECTOR attachPos;             /* 0x20, the attached object's position when the attachment started
                                       (d3anim_StepObject adds it to the attachment point) */
    char pad2c[0x4];
    struct D3OBJECT *attached;      /* 0x30, the object attached to the bone, 0: none */
    int fadeStart;                  /* 0x34, fade-in start time (ms) */
    int fadeEnd;                    /* 0x38, fade-in end time */
    int timeout;                    /* 0x3c, how long the animation may run (ms), -1: no limit */
    float weight;                   /* 0x40, blend weight */
    float fadeFrom;                 /* 0x44, weight at fadeStart */
    float fadeTo;                   /* 0x48, weight at fadeEnd */
    D3VECTOR4 stopPos;              /* 0x4c, the root position the motion stops at (d3anim_StepObject
                                       compares x/z with stopRadius) */
    float stopRadius;               /* 0x5c, the walk code's 15 / 30 / 60 (a person, a horse, a cart) scaled by the cell size */
    float speed;                    /* 0x60, animation speed, frames per ms */
    float frameTime;                /* 0x64, sub-frame time accumulator (d3_AnimBlendWeights) */
    struct D3ANIMDATA *data;        /* 0x68, the animation (d3_anim.h); its name and bone names come first */
    union {
        D3ANIMFLAGS flags;          /* 0x6c, as passed to d3anim_StartAnim */
        unsigned int flagWord;      /* flags.b[0..3] as one dword (d3_InitSurf clears it whole) */
        struct {
            unsigned char pad6c[8];
            unsigned char unk74_0 : 1;
            unsigned char play : 1; /* 0x74 bit 1 */
            unsigned char stopAtPos : 1;    /* 0x74 bit 2: d3anim_StepObject stops the root motion within
                                               stopRadius of stopPos (the walk code sets it) */
            unsigned char stopped : 1;      /* 0x74 bit 3: set when it did */
        };
        struct {                    /* D3ANIMFLAGS.b[1] by bit, as the walk code (ch.c) writes them */
            unsigned char pad6c1;
            unsigned char unk6d_0 : 4;
            unsigned char unk6d_4 : 1;      /* 0x6d bit 4 (0x10) */
            unsigned char finished : 1;     /* 0x6d bit 5 (0x20): the animation ran out (d3anim_StepObject) */
            unsigned char unk6d_6 : 2;
        };
        struct {                    /* D3ANIMFLAGS.b[4..7] as the dword the flag bitfields live in */
            unsigned char pad6c4[4];
            union {
                unsigned int rootFlags; /* 0x70, bits 0/1 (CHANIMFLAGS.a / .b): the root motion
                                           ch_ReleaseSlot applies; a sit animation clears them */
                struct {
                    int turn : 2;   /* 0x70 bits 0..1, signed -2..1: the turn the root motion
                                       follows (d3anim_StepObject passes it to d3anim_ApplyRootMotion /
                                       d3anim_ApplyMotionTo) */
                    unsigned int turnPad : 30;
                };
                struct {            /* the same two bits one by one (the walk code: turnLo = 1, turnHi = 0) */
                    unsigned int turnLo : 1;
                    unsigned int turnHi : 1;
                    unsigned int turnPad2 : 30;
                };
            };
        };
    };
    union {
        unsigned char map[4];       /* 0x78, bone index per child object (d3anim_MapBones), 0xff = none */
        unsigned int mapAll;        /* the four map bytes at once; -1 = no bone mapped */
    };
} D3ANIMSLOT;

typedef struct D3BGFPOLY {          /* 0x38 bytes, D3BGF::polys */
    float uv[3][2];                 /* 0x00 */
    int v[3];                       /* 0x18, vertex indices */
    int tex;                        /* 0x24, index into d3_Textures or -1 */
    int mat;                        /* 0x28, material index: the slot in the stock object's texture set (D3SURF.texHandles) */
    D3VECTOR n;                     /* 0x2c, the face normal (d3_MirBeginFrame turns it into the mirror plane) (d3_TriNormal of its three vertices, summed into the vertex normals, d3_io_fl.c) */
} D3BGFPOLY;

typedef struct D3BGFVERT {          /* 0x18 bytes, a point of a stock object and its normal */
    union {
        struct {
            float x, y, z;
        };
        D3VECTOR pos;
    };
    union {
        struct {
            float nx, ny, nz;
        };
        D3VECTOR n;
    };
} D3BGFVERT;

typedef struct D3BGFATTACH {        /* 0x58 bytes, an attachment point; an animated mesh's bones in their rest pose */
    char name[0x40];
    union {
        float f[6];                 /* 0x40, as the loader reads and copies them */
        struct {
            D3VECTOR pos;           /* 0x40 */
            D3VECTOR rot;           /* 0x4c */
        };
    };
} D3BGFATTACH;

typedef struct D3BGF D3BGF;
struct D3BGF {                      /* 0x20c bytes, a loaded mesh ("d3_io:LoadAGI_obj"): a stock object, the mesh driver
                                       of the surfaces that show it (D3SURF.mesh);
                                       the loaded ones are linked between the sentinels d3_StockListStart and d3_StockListEnd */
    char name[0x40];
    union {
        float *verts;               /* 0x40, 6 floats each (as the loaders write them), followed by the 8 corners of
                                       the bounding box */
        D3BGFVERT *vtx;             /* the same points as records */
    };
    int nverts;                     /* 0x44 */
    D3BGFPOLY *polys;               /* 0x48 */
    int npolys;                     /* 0x4c */
    D3VECTOR pos;                   /* 0x50, the root position and angles (d3anim_CreateMorphAnim: the move and
                                       turn between two meshes) */
    D3VECTOR rot;                   /* 0x5c */
    float cx, cy, cz;               /* 0x68, centre of the box (d3_LightApply subtracts cy from the points
                                       before the directional-light normals) */
    D3BGFATTACH attach[4];          /* 0x74 */
    union {
        float radius;               /* 0x1d4 */
        int radiusBits;             /* 0x1d4, the same as the fast chunk writes it (bio_wr_i, d3_AddFLChunk) */
    };
    float diagonal;                 /* 0x1d8 */
    int refs;                       /* 0x1dc */
    int ntex;                       /* 0x1e0 */
    int nsets;                      /* 0x1e4, texture sets of the name table */
    void (*Release)(D3BGF *m);      /* 0x1e8, the stock object's callbacks (d3io_LoadObjectFile): d3iot_DeleteStockObject */
    void (*TransformNormals)(struct D3OBJECT *obj, struct D3SURF *info);                        /* 0x1ec, the normals of a mesh without key frames */
    void (*Transform)(struct D3OBJECT *obj, struct D3SURF *info, struct D3MATRIX *m);           /* 0x1f0 */
    struct D3VERTEX *(*GetBox)(struct D3OBJECT *obj, struct D3SURF *info, struct D3MATRIX *m);       /* 0x1f4 */
    float (*GetRadius)(struct D3OBJECT *obj, struct D3SURF *info);                                     /* 0x1f8 */
    D3BGF *next;                    /* 0x1fc, the stock object list: towards d3_StockListEnd */
    D3BGF *prev;                    /* 0x200, towards the head sentinel d3_StockListStart */
    char *texnames;                 /* 0x204, ntex names of 0x40 bytes */
    unsigned char nattach;          /* 0x208, the attachment points in use (d3_FindBGF stores the low byte of their count) */
    char pad209[3];
};

struct D3SURF {                     /* 0x198 bytes, a surface of a mesh (one level of detail) with its own geometry */
    D3VERTEX *keys;                 /* 0x00, the points, followed by the 8 bounding box corners */
    D3TRI *tris;                    /* 0x04 */
    int nkeys;                      /* 0x08 */
    int ntris;                      /* 0x0c */
    struct D3BGF *mesh;             /* 0x10, the mesh driver: the loaded stock object the surface shows */
    struct TSTEXTURE **texHandles;  /* 0x14, the surf's textures (mesh->ntex of them) */
    D3OBJECT *owner;                /* 0x18, the object whose mesh this surf belongs to (set by d3_InitSurf) */
    D3ANIMSLOT slots[3];            /* 0x1c, the three vertex animation slots (d3anim_StartAnim) */
    union {
        int i;
        D3TEXFLAGS f;               /* f.b[0] = alpha */
    } flags;                        /* 0x190 */
    signed char active;             /* 0x194, a vertex animation runs (d3anim_StartAnim sets it, d3_ReleaseTexture clears it
                                       with the last slot): the surf is transformed and drawn even when nothing else changed */
    unsigned char texSet;           /* 0x195, current texture set: index into the ops' name table */
    char pad196[0x2];
};

typedef struct D3MESHSUB {          /* 0x80 bytes, the shadow of one light (d3s.c), 4 per mesh */
    struct TSTEXTURE *tex;          /* 0x00 */
    D3OBJECT *light;                /* 0x04 */
    struct D3SCENT *cache;          /* 0x08, the cached shadow texture (d3s.h) */
    unsigned char *map;             /* 0x0c, height map data */
    int size;                       /* 0x10 */
    unsigned int maxh;              /* 0x14 */
    D3VECTOR dir;                   /* 0x18, light direction the shadow was made for */
    int pad24;
    D3VECTOR cell;                  /* 0x28 */
    int pad34;
    D3VECTOR origin;                /* 0x38 */
    int pad44;
    float x0, x1, z0, z1;           /* 0x48, shadow rectangle */
    float y;                        /* 0x58, ground height */
    int ix0, ix1, iz0, iz1;         /* 0x5c, in map cells */
    int bz0, bx0, bz1, bx1;         /* 0x6c, in 8x8 blocks; bz0 -1 = none */
    unsigned char simple;           /* 0x7c */
    char pad7d[0x3];
} D3MESHSUB;

typedef struct D3MESH {             /* 0x970 bytes, what D3OBJECT::material points to ("d3:AddObjectDrawData") */
    void (*freeCallback)(D3OBJECT *obj);    /* 0x000, optional object callback, called before the mesh is freed
                                       (d3_DisposeObject); only cleared in the drafted code */
    D3OBJECT *camera;               /* 0x004, the camera cameraMatrix was transformed for */
    D3MATRIX worldMatrix;           /* 0x008, the object's world matrix (d3_WorldMatrix writes it) */
    D3MATRIX cameraMatrix;          /* 0x048, worldMatrix with the camera transform applied;
                                       GetBox / Transform take it to put the box / the verts in camera space */
    float zMin;                     /* 0x088, nearest z of the box in camera space (d3_ClipBox writes it) */
    float zMax;                     /* 0x08c, farthest z of the box in camera space */
    D3VECTOR4 boundsMin;            /* 0x090, the object's world box, as the quad tree keeps it (d3q_GetBounds) */
    D3VECTOR4 boundsMax;            /* 0x0a0 */
    int frameStamp;                 /* 0x0b0, the frame the mesh was last transformed/clipped in (d3_FrameCount; d3q_Mark
                                       stamps the objects the camera box touches, d3q_Create resets them to -1);
                                       equal to the current frame: already current, only flag 0x40 is set;
                                       -1 = never (d3_AddObjectDrawData) */
    char boneName[0x40];            /* 0x0b4, the parent's bone the object is attached to (d3_AttachToBone writes it,
                                       d3anim_MapBones / d3anim_PoseBones match the children by it); the length is the
                                       room to surf */
    D3SURF surf[4];                 /* 0x0f4, surf[3] at 0x5bc */
    D3MESHSUB sub[4];               /* 0x754 */
    float groundOffset;             /* 0x954, offset added to the mesh's ground height (d3s_GetGround) */
    float lightScale;               /* 0x958, light brightness scale (ch.c: 1.8 for characters) */
    unsigned int lightGeneration;   /* 0x95c */
    struct D3VERTEX *mirrorPoints;          /* 0x960, mirrored point array ("d3_mir:MirroredPoints") */
    struct D3TRI *mirrorPolys;             /* 0x964, mirrored polygon array ("d3_mir:MirroredPolys") */
    D3SURF *mirrorSource;           /* 0x968, the surf the mirror copy was made from */
    unsigned char nsurf;            /* 0x96c */
    unsigned char flags;            /* 0x96d, 0x40 = no vertex animation (d3anim_StepObject) */
    char pad96e[0x2];
} D3MESH;

typedef struct D3ANIMKEY {          /* 0x58 bytes */
    int time;
    D3VECTOR4 pos;                  /* 0x04, relative to the object's position */
    D3VECTOR4 rot;                  /* 0x14, relative to the object's angles */
    char pad24[0x34];
} D3ANIMKEY;

D3PATH *d3anim_CreatePath(D3OBJECT *obj, D3ANIMFLAGS f, int nkeys, D3ANIMKEY *keys);          /* 0x433d70 */
void d3_UnwrapAngles(const struct D3VECTOR *a, const struct D3VECTOR *b, struct D3VECTOR *ra, struct D3VECTOR *rb);                            /* 0x453d60, angles mod 2pi */
struct D3ANIMDATA *d3_FindAnim(char *name);                                            /* 0x433f40, anim loaded? */
struct D3ANIMSLOT *d3anim_StartAnim(struct D3SURF *ctl, char *name, D3ANIMFLAGS f);                          /* 0x435550 */
struct D3PATH *d3_LoadObjectAnim(char *file, struct D3OBJECT *obj, char reload);                                 /* 0x44e2e0 */
extern struct VFSDIR *d3io_StockDir;          /* 0xfba940, the stock object directory (d3io_SetStockDir, d3_int_io.c) */
char *util_BaseName(char *path);            /* 0x401040, strips the extension in place, returns the file name */
extern D3VECTOR d3t_PlaceTarget;             /* 0x1466620, camera target position */
extern D3VECTOR d3t_PlaceAngles;              /* 0x1466630, camera target angles */
void d3anim_FreePath(D3OBJECT *obj);                                                       /* 0x433b10 */
char d3if_Delete(D3OBJECT *obj);                                                       /* 0x447190, d3_interface.h */
struct D3OBJECT * d3_FindObject(struct D3OBJECT *a, int flags, struct D3OBJECT *c, char *name);                     /* 0x449690 */
D3OBJECT *d3_CreateObject(D3OBJECT *a, const D3VECTOR *pos, const D3VECTOR *rot, char *name);       /* 0x446e10 */
int d3_VecEqual(const struct D3VECTOR *a, const struct D3VECTOR *b, float eps);                                   /* 0x453e80 */
void d3_SetObjectPos(struct D3OBJECT *obj, const struct D3VECTOR *pos);                                     /* 0x43b790 */
void d3_SetObjectRot(D3OBJECT *obj, const D3VECTOR *rot);                                   /* 0x43b860 */
void d3_SetObjectPosXYZ(D3OBJECT *obj, float x, float y, float z);                      /* 0x43b7f0 */
void d3_SetObjectRotXYZ(D3OBJECT *obj, float x, float y, float z);                      /* 0x43b920 */

void d3d_Error(char *file, int line, char *call);                                      /* 0x418e90 */
void d3_BeginScene(unsigned char fog, unsigned long fogcol, unsigned char zbuffer);                                                 /* 0x4385a0 */
void d3_SetBlendState(unsigned char balpha, unsigned char glow, unsigned char colorkey);   /* 0x4387b0, d3_d3d.c */
void d3_EndScene(void);                                                                /* 0x438780 */

struct TSTEXTURE; extern struct TSTEXTURE *d3_Textures;  /* 0xfb9074, the texture slots (ts_texture.h's TSTEXTURE) */
extern unsigned int d3_TexCount;            /* 0xfb9084 */
extern struct D3FLMAP *d3_Terrain;        /* 0x633738, d3_fl.c: the current terrain map */

struct TSTEXTURE; struct TSTEXTURE *tex_Load(char *name, D3TEXFLAGS flags, unsigned char opts, unsigned char fmt);  /* 0x4605c0, ts_texture.c (TSFLAGS is D3TEXFLAGS) */
void d3_SetObjectAlpha(D3OBJECT *obj, struct D3SURF *info, D3TEXFLAGS f);           /* 0x43d430, f.b[0] = alpha */
struct TSTEXTURE; void tex_Reload(struct TSTEXTURE *tex, char keep);                                               /* 0x460e50 */
struct TSTEXTURE; void tex_Release(struct TSTEXTURE *tex);                                                          /* 0x45fbc0 */
struct TSTEXTURE; char tex_SetHiColor(struct TSTEXTURE *tex, unsigned char hicolor);                                            /* 0x4611b0 */
struct TSTEXTURE; char tex_Unload(struct TSTEXTURE *tex);                                                     /* 0x461140 */
void d3fl_Flush(void);                                                                /* 0x43f990 */
struct D3FLMAP;


/* Particle systems (d3_par, "d3_par:ParticleSystem"). The engine allocates the particles and calls
   the system's callback each frame; the callbacks in d3_tools.c animate them. */
/* the template par_CreateEmitter reads (global at 0x1468620, 0xa4 bytes) */
typedef struct D3EMITTERCFG {
    int type;                       /* 0x00, emitter type: 0/1/2 -> par_EmitterCB0/1/2 */
    char pad04[0x30];
    float f34, f38, f3c;
    D3VECTOR dir;                   /* 0x40, d3_YAxis */
    char pad4c[0x34];
    float f80;
    char pad84[0x8];
    float f8c;
    int i90, i94, i98;
    unsigned char c9c, c9d, c9e, c9f;
    unsigned char flags;            /* 0xa0 */
    char pada1[3];
} D3EMITTERCFG;

typedef struct D3PARTICLE {         /* 0x54 bytes */
    D3VECTOR4 vel;                  /* meaning depends on the effect; an emitter's: w the phase of the alpha wave */
    union {
        D3VECTOR4 start;            /* 0x10, start position of the effect; .x is the brightness in the emitter */
        float phase[4];             /* an emitter's particle: the phases of the x / y / z / size waves */
    };
    union {
        char pad20[0x10];
        struct {
            float base[3];          /* 0x20, an emitter's particle: the position without the waves */
            float pad2c;
        };
    };
    unsigned long time;             /* 0x30, d3_Time of the last update */
    union {
        int pad34;
        unsigned long birth;        /* 0x34, an emitter's particle: d3_Time of its birth */
    };
    D3VECTOR4 pos;                  /* 0x38 */
    float size;                     /* 0x48 */
    union {
        unsigned long color;        /* 0x4c, initialized to 0xffffffff */
        struct { unsigned char b, g, r, a; };
    };
    unsigned char frame;            /* 0x50, texture animation frame (tex_GetFrame index) */
    unsigned char flags;            /* 0x51, bit 0 = alive */
    char pad52[0x2];
} D3PARTICLE;

typedef struct D3PARTSYS D3PARTSYS;
typedef char (*D3PARTCB)(D3PARTSYS *ps, unsigned long time);

struct D3PARTSYS {                  /* 0x31c bytes */
    D3VECTOR4 v00;                  /* 0x00..0x1c: effect parameters, meaning depends on the effect */
    D3VECTOR4 v10;
    unsigned int flags;             /* 0x20 */
    union {
        unsigned int spawnCount;    /* particles spawned per frame (d3t_CreateEmitter sets 2) */
        D3COLOR color24;            /* base color + random mask in a (Erdbrocken) */
        unsigned long lasttime;     /* an emitter's d3_Time of its last callback; a repeated time is skipped */
    };
    D3PARTICLE *particles;          /* 0x28 */
    union {                         /* 0x2c..0xd0 */
        D3EMITTERCFG cfg;           /* an emitter's parameters: the template par_CreateEmitter copies in */
        struct {                    /* the same bytes by name: the emitter callbacks and the script commands (ecmd.c) */
            char pade2c[0x4];
            float inv_alpha0;       /* 0x30, 1 / alpha[0], cached by the emitter callbacks */
            float inv_alpha_gap;    /* 0x34, 1 / (alpha[2] - alpha[1]) */
            float inv_size;         /* 0x38, 1 / |psize[1] - psize[0]| (type 0), 1 / psize[2] (type 1) */
            float size_ratio;       /* 0x3c, psize[1] / psize[0] */
            float amp[3];           /* 0x40 */
            float amp3;             /* 0x4c */
            float phase[3];         /* 0x50 */
            float phase3;           /* 0x5c */
            float psize[3];         /* 0x60, the particle sizes (ocmd_SetEmitterSize) */
            D3VECTOR dir;           /* 0x6c */
            float vel[3];           /* 0x78 */
            float rnd[3];           /* 0x84 */
            float acc[3];           /* 0x90 */
            float plane[3];         /* 0x9c */
            float plane3;           /* 0xa8 */
            float maxtrigger;       /* 0xac, also set by SetEmitterFlags */
            float amp4;             /* 0xb0 */
            float phase4;           /* 0xb4 */
            float time;             /* 0xb8 */
            int alpha[3];           /* 0xbc */
            unsigned char b, g, r, a;   /* 0xc8 */
            unsigned char texmode : 5, initfill : 1, rebirthfill : 1, istrigger : 1;   /* 0xcc */
            unsigned char triggeronce : 1, trigger : 1, bcd : 6;                        /* 0xcd */
            char padce[0x2];
        };
        struct {
            char padc2c[0x9c];
            unsigned long color;    /* 0xc8 */
        };
    };
    int count;                      /* 0xd0 */
    struct TSTEXTURE *tex;               /* 0xd4 */
    int texindex;                   /* 0xd8, index into d3_Textures */
    D3VERTEX *points;               /* 0xdc, 4 D3VERTEX per particle ("d3_par:ParticlePoints") */
    D3TRI *polys;                   /* 0xe0, 2 D3TRI per particle ("d3_par:ParticlePolys") */
    float size;                     /* 0xe4, initial particle size */
    D3OBJECT obj;                   /* 0xe8, the embedded object (0x228 bytes, up to 0x310): par_Create sets its
                                       flags, parent and scene; par_Draw takes its world matrix */
    D3PARTCB callback;              /* 0x310 */
    D3PARTSYS *next;                /* 0x314 */
    D3PARTSYS *prev;                /* 0x318 */
};

D3PARTSYS *par_Create(int count, char *tex, D3TEXFLAGS flags, float size, void *parent, D3PARTCB cb); /* 0x455830 */
void par_SetPos(D3PARTSYS *ps, const D3VECTOR *pos);                                          /* 0x455a20 */
extern const D3VECTOR4 d3_Origin;           /* 0x5ebba4, (0, 0, 0), d3_vec.c */
void d3_Normalize(D3VECTOR *v);                                                         /* 0x454560 */

void *mem_Alloc(int size, char *tag);                                                  /* 0x4223c0 */
void mem_Free(void *p);                                                                 /* 0x422620 */

/* Inline-asm copy, the counterpart of D3_ZERO (dd_vesa.c): size and destination go through temps (which
   VC6 puts into dead parameter slots), the source is named directly in the asm. */
#ifndef D3_COPY
#define D3_COPY_LABEL(n) D3_ZERO_CAT(d3_copy_tail, n)
#define D3_COPY(dst, src, size) {                                   \
    int _cn = (size); void *_cd = (dst);                            \
    __asm mov edi, _cd                                              \
    __asm mov esi, src                                              \
    __asm mov ebx, _cn                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle D3_COPY_LABEL(__LINE__)                               \
    __asm rep movsb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep movsd                                                 \
    __asm D3_COPY_LABEL(__LINE__): add ecx, ebx                     \
    __asm rep movsb                                                 \
}
#endif

extern unsigned char d3_D3DActive;   /* 0x63345c, d3_engine.c: a Direct3D device was created (d3d_Init / d3d_CreateDevice) */

#endif
