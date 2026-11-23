/* d3_pose.h -- object pose helpers (0x458810..0x4591a0), see d3_pose.c. Names are ours. */
#ifndef D3_POSE_H
#define D3_POSE_H
#include "d3.h" /* the D3 records and typedefs this header names */
struct D3SURF;

struct D3ANIMSLOT *d3anim_GetMainSlot(struct D3SURF *ctl); /* 0x435900 */
void d3_MatMul43(D3MATRIX *a, D3MATRIX *b, D3MATRIX *out); /* 0x453ee0 */
void d3_MatToAngles(const D3MATRIX *m, D3VECTOR *angles);  /* 0x454690 */

void d3_DirToWorld(struct D3OBJECT *obj, const struct D3VECTOR *in,
                   struct D3VECTOR *out);                    /* 0x458810 */
void d3_WorldAngles(struct D3OBJECT *obj, D3VECTOR *angles); /* 0x458910 */
void d3_DirToRef(struct D3OBJECT *obj, struct D3OBJECT *ref,
                 const struct D3VECTOR *in,
                 struct D3VECTOR *out); /* 0x458950 */
/* d3_PointToWorld is declared in d3.h: (D3OBJECT *obj, D3VECTOR *v, D3VECTOR *out) */
void d3_PointToRef(struct D3OBJECT *obj, struct D3OBJECT *ref,
                   struct D3VECTOR *in, struct D3VECTOR *out); /* 0x458b20 */
void d3_LocalToWorld(struct D3OBJECT *obj, const struct D3VECTOR *in,
                     struct D3VECTOR *out); /* 0x458c10 */
void d3_MatToWorld(struct D3OBJECT *obj, char orientOnly, D3MATRIX *m,
                   D3MATRIX *out); /* 0x458ce0 */
void d3_WorldMatrix(struct D3OBJECT *obj, struct D3OBJECT *ref, char orientOnly,
                    D3MATRIX *out); /* 0x458da0 */
#endif
