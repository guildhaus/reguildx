/* Types of d3s.c (0x459d80..0x45ce60): the object shadow TU ("d3s:" tags, "Schatten" texture). Names are ours. */
#ifndef D3S_H
#define D3S_H
#include "d3.h"                       /* the D3 records and typedefs this header names */

typedef struct D3SCENT {            /* 0x14 bytes, one cached shadow texture (d3s_Cache); D3MESHSUB.cache */
    struct TSTEXTURE *tex;               /* 0x00 */
    void **owner;                   /* 0x04, the slot that uses it (its tex pointer is cleared when taken over) */
    unsigned int time;              /* 0x08, frame of last use */
    unsigned int size;              /* 0x0c, 0 = free */
    signed char flag;               /* 0x10 */
    char pad11[3];
} D3SCENT;

/* declared in other units' headers before (moved to the owner) */
void d3_ExitShadows(void);  /* 0x45aee0 */
void d3_InitShadows(unsigned int size, unsigned int maxsize, int ncache, int age, char mips, int polys, int mapsize);  /* 0x45ad80 */
void d3s_CollectLights(void);  /* 0x45c9f0 */
void d3s_ShadowTriangle(float *p, unsigned char *c, unsigned char *dst, int pitch, unsigned char flags, struct D3SMENTRY *base, int radius);  /* 0x45a2e0, a shadow triangle: edges from the three points p (x, y pairs), colours c, radius pixels / rows around */
extern unsigned int d3s_Count;  /* 0x633dc0 */
char d3s_FreeLightCB(D3OBJECT *obj, D3OBJECT *light);  /* 0x45cd60 */
void d3s_FreeShadows(D3OBJECT *obj);  /* 0x45ccd0 */
extern unsigned int d3s_MaxPolys;  /* 0x633dc4 */
extern int d3s_NumUVs;  /* 0xfb925c */
extern int d3s_NumVerts;  /* 0xfb9220 */
extern D3OBJECT * d3s_Object;  /* 0x633448 */
void d3s_ResetShadows(D3OBJECT *obj);  /* 0x45ce00 */
void d3s_UpdateObject(D3OBJECT *obj);  /* 0x45ca20 */
void d3s_UpdateObjectAt(D3OBJECT *obj);  /* 0x45ca60 */

#endif
