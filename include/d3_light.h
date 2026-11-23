struct D3ANIMFRAME;
struct D3VECTOR4;
struct D3SURF;
/* d3_light.c -- dynamic lighting of mesh objects ("d3_light:cache", "d3_light:rlight_object"), original file
   name unknown: 0x451e80..0x4538a0. The objects are D3OBJECT with its light fields (lightTime, flickerStart /
   flickerEnd, lightColor, range / power / atten, cam, radius2) and D3LIGHTINFO (d3.h). Names are ours. */
#ifndef UNK_451E80_H
#define UNK_451E80_H
#include "d3.h"                       /* the D3 records and typedefs this header names */

typedef struct D3LHIT {             /* 8 bytes: a lit vertex and the light's contribution (only c.r in grey mode) */
    D3VERTEX *v;
    D3COLOR c;
} D3LHIT;

typedef struct D3LREC D3LREC;
struct D3LREC {                     /* "d3_light:rlight_object": the vertices one light reaches in one object */
    int n;                          /* 0x00 */
    D3OBJECT *obj;                  /* 0x04, the lit object */
    D3LREC *next;                   /* 0x08 */
    D3LHIT v[1];                    /* 0x0c, n of them */
};


typedef struct D3LCTX {             /* the lights that reach an object (d3_LightCollectCB collects, d3_LightApply adds) */
    D3OBJECT *obj;                  /* 0x00, the lit object */
    unsigned int count;             /* 0x04 */
    D3OBJECT **list;                /* 0x08 */
    unsigned char normals;          /* 0x0c, use the vertex normals (D3OBJECT::state bit 5) */
} D3LCTX;

typedef struct D3LCTX2 {            /* context of d3_LightAddObject: the light and whether it needs the vertex normals */
    D3OBJECT *light;
    unsigned char normals;
} D3LCTX2;


extern volatile unsigned long d3_Time;      /* 0x6333cc */
extern D3OBJECT *d3_Camera;                 /* 0xfc2dec */
extern float d3_LightRadiusMargin;          /* 0x633b18, added to the mesh radius for the light reach:
                                               the matrix z offset (m->_43) or 0 */
extern D3VECTOR d3_AmbientColor;               /* 0x5fcc78, ambient light colour */
extern const D3VECTOR4 d3_ZAxis;             /* 0x5ebb74, (0, 0, 1) */

/* float to int with fistp (current rounding mode), as d3_FtoI in d3_engine.h but float first */
__inline void d3l_FtoI2(float f, int *dst)
{
    __asm fld f
    __asm mov edx, dst
    __asm fistp dword ptr [edx]
}

void d3_LightResetVertexColors(D3OBJECT *obj);           /* 0x451e80, callback */
void d3_LightFlicker(D3OBJECT *obj);           /* 0x451f10, callback: light flicker */
char d3_LightApply(D3OBJECT *obj, D3LCTX *set);  /* 0x4522b0, adds the lights in set to the vertex colours of obj */
char d3_LightAddObject(D3OBJECT *obj, D3LCTX2 *ctx); /* 0x452940 */
char d3_LightAttach(D3OBJECT *light, D3OBJECT *obj);  /* 0x452d90 */
void d3_LightUpdate(void);                      /* 0x452e10 */
char d3_LightRemoveRecords(D3OBJECT *obj, void *src); /* 0x452e40, drops the light records of obj (all, or src's) */
void d3_SetVertexColors(D3OBJECT *obj, struct D3SURF *s, char on, D3TEXFLAGS fl); /* 0x452fa0 */
char d3_RelightObject(D3OBJECT *obj);           /* 0x453280 */
void d3_RelightObjects(D3OBJECT *obj);          /* 0x453580, recomputes the vertex colours of the selected objects */
void d3_RelightObjectFrame(D3OBJECT *obj, struct D3ANIMFRAME *f); /* 0x4535b0 */
void d3_FrameNormals(D3OBJECT *obj, D3SURF *info, struct D3ANIMFRAME *f);              /* 0x459980, f: key frame (d3_anim.h) */
char d3_ForEachObject2(D3SCENE *scene, D3OBJECT *obj, unsigned int mask, void (*cb)(D3OBJECT *obj)); /* 0x438e60 */
struct D3FLMAP;
void d3fl_MakeLight(struct D3FLMAP *map);   /* 0x441860 (d3_fl.c) */
void d3_LightInvalidate(unsigned char on);  /* 0x4538a0 (d3_engine.h: d3_LightInvalidate(int)) */

#endif
