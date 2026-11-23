/* d3_mir.c -- mirrors ("d3_mir:" allocation tags), original file name unknown: 0x454780..0x455630.
   The outline of the mirror polygon becomes a set of clipping planes; the objects whose mirrored bounding box
   is inside them are drawn a second time, mirrored at the mirror plane. Names are ours.
   Open: d3_engine.h declares d3_MirBeginFrame / d3_MirDrawObject with other parameter types than d3_mir.h.
   unit of rea 8cef7d5b (src/game/d3_mir.c); boundaries in decl/text.dcl */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#include <d3d.h>
#include "d3.h"
/* d3_engine.h declares these two with other parameter types */
#define d3_MirBeginFrame d3_Unk4554b0_decl
#define d3_MirDrawObject d3_Unk4550e0_decl
#include "d3_engine.h"
#undef d3_MirBeginFrame
#undef d3_MirDrawObject
#include "d3_mir.h"
#include "data_views.h"
#include "ts_texture.h"
#include "d3_pose.h"

#define D3M_PTS(mesh) ((mesh)->mirrorPoints) /* "d3_mir:MirroredPoints" */
#define D3M_TRIS(mesh) ((mesh)->mirrorPolys) /* "d3_mir:MirroredPolys" */

/* 0x454780, the boundary edges of the point set pts: for every pair (i, j) not taken yet the triangle
   (origin, i, j) is a hull edge when all other points lie on its positive side; the pairs go to out (2 per
   edge, *count of them), used is the n x n matrix that marks the taken pairs */
char d3_MirBoundaryEdges(unsigned int n, unsigned char *used, D3VERTEX **pts,
                         unsigned int *count, D3VERTEX **out) {
  D3VECTOR4 nrm;
  D3VERTEX *p;
  unsigned char *row;
  unsigned i, j, k;

  *count = 0;
  for (i = 0; i < n; i++) {
    row = used + i;
    for (j = 0; j < n; j++, row += n) {
      if (i != j && used[i * n + j] == 0) {
        d3_TriNormal(&d3_Origin.v, &pts[i]->pos, &pts[j]->pos, &nrm.v);
        for (k = 0; k < n; k++) {
          if (k != i && k != j) {
            p = pts[k];
            if (nrm.x * p->x + nrm.y * p->y + nrm.z * p->z < -0.01)
              break;
          }
        }
        if (k == n) {
          out[(*count)++] = pts[i];
          out[(*count)++] = pts[j];
          *row = 1;
          used[i * n + j] = 1;
        }
      }
    }
  }
  return 1;
}
/* 0x454890, d3_mir:CreateOutline: turns the boundary edges of the mirror polygon (d3_MirBoundaryEdges: pairs of
   vertices in edges[], nedge of them) into the outline segments: connected edges that are collinear are
   merged, *out gets the (start, end) vertex pairs, *nout their count (2 per segment). Returns 0 only for n < 3.
   used[0..nedge) = edge taken by the current chain, used[nedge..2*nedge) (mark) = edge taken by any chain
   @deep deep s49: the IL creates the loads in evaluation order and hands out the scratch registers then
   (c2dag): mark[head] creates head's load first (edx), mark (eax), address [edx+eax] (head base); the
   used[nedge + head] form creates the CSE mark load first (edx), head (eax), address [edx+eax] (mark
   base). The original creates mark first (edx) and head (eax) but has head as the base ([eax+edx]), like
   the tail arm's mark[tail] (tail first, base). Every spelling of the store gives one of the two codes (40
   tried: casts to int / unsigned, &used[nedge], &mark[0], (head + mark)[0], mark + nedge - nedge, the RHS
   as used[i], chains with used[i] either way, a comma); types of head / nedge (int / unsigned, 72), local
   declaration order (16), head / tail / mark = 0 at the declaration / the top / before or after mark =
   used + i (96), head = tail = 0 at every place of the init block x mark[0] as mark[tail] / mark[head]
   (52), init and restart assignment spellings and positions (116), restart test / store forms x tail arm
   form x initializers (128); climb 4 rounds --unsafe (seed 11): nothing. flip.py: only deleting head's
   restart definition (tail = head = i -> tail = i) or the init gives mark-first in this block, with the
   slots of head / tail swapped (a meaning change). Next: why head's restart definition decides the
   creation order (c2dag of the two texts per block; whether head's web or its slot number orders the
   commutative operands), then an ordinary form with that effect. prior: deep s48: the address operand
   order follows the evaluation order of the two loads at every site: mark[x] loads x first and addresses
   [x+mark], used[nedge + x] loads the mark temp first and addresses [mark+x]; the original's head block
   loads mark first (edx) and addresses [head+mark] ([eax+edx]), which no spelling gives. Rounds (dcp try):
   head + nedge, (used + head)[nedge], *(used + nedge + head), *(head + used + nedge), (nedge +
   head)[used], (int) casts: = control; *(head + mark) / mark[(int)head] = mark[head] (6, order 10); 63
   masks of {arm 1 mark[tail] / used[nedge + tail], arm 2 mark[head], restart test and store as used[nedge
   + i], head = 0 initializer, mark = 0 initializer dropped}: best = control (2), every other 4..12; nres =
   0 inside the if / before res / at the top (4..15), head = tail = 0 right before the do (10 / 14): no
   lever. Left: the regs-2 hunk at 0x454acf ([edx+eax] for [eax+edx]). */

char d3_MirCreateOutline(D3VERTEX **pts, unsigned int n, unsigned int *nout,
                         D3VERTEX ***out) {
  D3VERTEX **edges;
  unsigned char *used;
  unsigned char *mark = 0;
  D3VERTEX **res;
  D3VERTEX *start, *end, *p, *q;
  D3VECTOR4 dir, d, nd;
  unsigned int i, j, nres, tail, head, nedge;

  if (n < 3)
    return 0;
  edges = mem_Alloc(n << 5, "d3_mir:CreateOutlineMaxOut");
  used = mem_Alloc((n + 8) * n, "d3_mir:track_connections");
  d3_MirBoundaryEdges(n, used, pts, &nedge, edges);
  i = nedge;
  res = mem_Alloc(i * 4, "d3_mir:CreateOutlineOutput");
  nres = 0;
  if (i > 0) {
    mark = used + i;
    D3_ZERO_AT(used, i * 2);
    mark[0] = 1;
    used[0] = 1;
    end = edges[1];
    head = tail = 0;
    start = edges[0];
    dir.x = end->x - start->x;
    dir.y = end->y - start->y;
    dir.z = end->z - start->z;
    d3_Normalize(&dir.v);
    do {
      for (i = 0; i < nedge; i += 2) {
        if (!used[i] && (p = edges[i]) == end) {
          q = edges[i + 1];
          d.x = p->x - q->x;
          d.y = p->y - q->y;
          d.z = p->z - q->z;
          d3_Normalize(&d.v);
          nd.x = -d.x;
          nd.y = -d.y;
          nd.z = -d.z;
          if (d3_VecEqual(&dir.v, &d.v, 0.001f) ||
              d3_VecEqual(&dir.v, &nd.v, 0.001f)) {
            used[i] = 1;
            mark[tail] = 1;
            tail = i;
            end = edges[i + 1];
            break;
          }
        }
        if (!used[i] && (p = edges[i + 1]) == start) {
          q = edges[i];
          d.x = p->x - q->x;
          d.y = p->y - q->y;
          d.z = p->z - q->z;
          d3_Normalize(&d.v);
          nd.x = -d.x;
          nd.y = -d.y;
          nd.z = -d.z;
          if (d3_VecEqual(&dir.v, &d.v, 0.001f) ||
              d3_VecEqual(&dir.v, &nd.v, 0.001f)) {
            used[i] = 1;
            /* used[nedge + head], not mark[head]: the form that gives VC6's operand order */
            used[nedge + head] = 1;
            head = i;
            start = edges[i];
            break;
          }
        }
      }
      if (i >= nedge) {
        for (j = 0; j < nres; j += 2) {
          q = res[j + 1];
          if ((res[j] == start && res[j + 1] == end) ||
              (res[j + 1] == start && res[j] == end))
            break;
        }
        if (j >= nres) {
          res[nres++] = start;
          res[nres++] = end;
        }
        /* next unmarked edge starts a new outline; none left ends the do loop (start stays NULL;
           this form, not a test after the scan, gives VC6's threaded exit) */
        start = NULL;
        for (i = 0; i < nedge; i += 2) {
          if (!mark[i]) {
            D3M_ZERO_VAR(used, nedge);
            tail = head = i;
            mark[i] = 1;
            used[i] = 1;
            end = edges[i + 1];
            start = edges[i];
            dir.x = end->x - start->x;
            dir.y = end->y - start->y;
            dir.z = end->z - start->z;
            d3_Normalize(&dir.v);
            break;
          }
        }
      }
    } while (start);
  }
  mem_Free(used);
  mem_Free(edges);
  *nout = nres;
  *out = res;
  return 1;
}
/* 0x454be0: the clipping planes of the mirror: one per outline edge of the visible polygons with tex (through
   the eye point), followed by the view clip planes those polygons touch */

D3MIRPLANES *d3_MirCreatePlanes(D3OBJECT *obj, TSTEXTURE *tex) {
  D3SURF *info;
  D3TRI *t;
  D3TRI **polys;
  D3VERTEX **pts;
  D3VERTEX **uniq;
  D3VERTEX *p;
  D3CLIPINFO *ci;
  D3MIRPLANES *planes;
  unsigned int n, cnt, np, nu, ne, k, j;
  unsigned char clip;

  if (obj && (info = obj->info) && tex) {
    n = info->ntris;
    cnt = 0;
    for (k = 0, t = info->tris; k < n; k++, t++)
      if (t->tex == tex)
        cnt++;
    if (cnt) {
      polys = mem_Alloc(cnt * 4, "d3_mir:CrClippingPolys");
      cnt = 0;
      for (k = 0, t = info->tris; k < n; k++, t++)
        if (t->tex == tex && (t->flags & 0x80))
          polys[cnt++] = t;
      pts = mem_Alloc(cnt * 3 * 8, "d3_mir:CrClippingPoints");
      uniq = pts + cnt * 3;
      np = 0;
      clip = 0;
      for (k = 0; k < cnt; k++) {
        if (!(polys[k]->v[0]->flags & polys[k]->v[1]->flags &
              polys[k]->v[2]->flags & 0x3f)) {
          clip |= (polys[k]->v[0]->flags | polys[k]->v[1]->flags |
                   polys[k]->v[2]->flags) &
                  0x3f;
          for (j = 0; j < 3; j++)
            pts[np++] = polys[k]->v[j];
        }
      }
      mem_Free(polys);
      nu = 0;
      for (k = 0; k < np; k++) {
        p = pts[k];
        for (j = 0; j < np; j++)
          if (!uniq[j] || uniq[j] == p ||
              d3_VecEqual(&uniq[j]->pos, &p->pos, 0.001f))
            break;
        if (j < np && !uniq[j]) {
          uniq[j] = p;
          nu++;
        }
      }
      if (nu < 3)
        mem_Free(pts);
      else {
        if (!d3_MirCreateOutline(uniq, nu, &ne, &uniq)) {
          mem_Free(pts);
          return 0;
        }
        if (ne < 6) {
          mem_Free(uniq);
          mem_Free(pts);
          return 0;
        }
        mem_Free(pts);
        ne /= 2;
        ci = &d3_ClipInfo[clip & 0x3f];
        planes =
            mem_Alloc((ci->n + ne) * 16 + 8, "d3_mir:CrClippingPlanesFinal");
        planes->n = ci->n + ne;
        planes->mirror = 1;
        for (j = 0; j < ne; j++) {
          d3_TriNormal(&d3_Origin.v, &uniq[j * 2]->pos, &uniq[j * 2 + 1]->pos,
                       &planes->p[j].v);
          p = uniq[j * 2];
          planes->p[j].w = -(p->x * (planes->p[j].x) + p->y * planes->p[j].y +
                             (p->z) * planes->p[j].z);
        }
        mem_Free(uniq);
        D3M_COPY(&planes->p[ne], ci->plane, ci->n * 16);
        return planes;
      }
    }
  }
  return 0;
}
/* 0x454ec0, d3_Mirror.Transform: mirrors camera-space points at the mirror plane and projects them again */

void d3_MirTransform(D3VERTEX *v, int n, int unk) {
  int i;
  float d, z;

  for (i = 0; i < n; i++, v++) {
    d = (d3_Mirror.plane.x * v->x + d3_Mirror.plane.y * v->y +
         d3_Mirror.plane.z * v->z - d3_Mirror.plane.w) *
        -2.0f;
    v->x += d * d3_Mirror.plane.x;
    v->y += d * d3_Mirror.plane.y;
    v->z += d * d3_Mirror.plane.z;
    v->rhw = d;
    z = 1.0f / v->z;
    v->sx = d3_ScaleX * v->x * z + d3_CenterX;
    v->sy = d3_ScaleY * v->y * z + d3_CenterY;
  }
}
/* 0x454f70: is the mirrored bounding box of obj inside the mirror's clipping planes? Widens d3_MinZ / d3_MaxZ. */

char d3_MirBoxInPlanes(D3OBJECT *obj, D3MIRROR *m) {
  D3SURF *info;
  D3MIRPLANES *pl;
  D3VERTEX *box;
  D3VECTOR4 pts[8];
  D3VECTOR4 *p;
  float d;
  int i;
  unsigned int j, k;

  if (obj && (info = obj->info) && info->mesh && m && (pl = m->planes)) {
    if (obj->state & 0x10)
      box = info->mesh->GetBox(obj, info, &obj->material->cameraMatrix);
    else
      box = &info->keys[info->nkeys];
    for (i = 0; i < 8; i++, box++) {
      d = (box->x * m->plane.x + box->y * (m->plane.y) +
           (box->z) * (m->plane.z) - m->plane.w) *
          -2.0f;
      pts[i].x = d * m->plane.x + box->x;
      pts[i].y = d * m->plane.y + box->y;
      pts[i].z = d * m->plane.z + box->z;
    }
    for (j = 0; j < pl->n; j++) {
      for (k = 0; k < 8; k++)
        if (pts[k].x * pl->p[j].x + pts[k].y * pl->p[j].y +
                (pts[k].z * pl->p[j].z) >=
            pl->p[j].w)
          break;
      if (k >= 8)
        return 0;
    }
    for (i = 0; i < 8; i++) {
      d3_MinZ = min(d3_MinZ, pts[i].z);
      d3_MaxZ = max(d3_MaxZ, pts[i].z);
    }
    return 1;
  }
  return 0;
}
/* 0x4550e0, d3_ForEachObject callback (ctx = &d3_Mirror): draws the mirror image of obj */

char d3_MirDrawObject(D3OBJECT *obj, D3MIRROR *m) {
  D3SURF *s;
  D3MESH *mesh;
  D3TRI *t;
  TSTEXTURE *tex, *tt;
  D3VERTEX *a, *b, *c;
  struct D3MIRBITS *bits;
  char redo;
  int i, k, n;

  s = obj->info;
  if (!s)
    return 1;
  if (obj == d3s_Object)
    return 1;
  bits = &obj->mirBits;
  bits->mirrored = d3_MirBoxInPlanes(obj, m);
  if (bits->mirrored) {
    if (m->flags.on || (obj->state & 8))
      redo = 1;
    else
      redo = 0;
    if (s != obj->material->mirrorSource) {
      if (obj->material->mirrorSource) {
        mem_Free(D3M_PTS(obj->material));
        D3M_PTS(obj->material) = 0;
        mem_Free(D3M_TRIS(obj->material));
        D3M_TRIS(obj->material) = 0;
      }
      obj->material->mirrorSource = s;
      D3M_PTS(obj->material) =
          mem_Alloc(s->nkeys * 0x50, "d3_mir:MirroredPoints");
      D3M_TRIS(obj->material) =
          mem_Alloc(s->ntris * 0x28, "d3_mir:MirroredPolys");
      D3M_COPY(D3M_TRIS(obj->material), s->tris, s->ntris * 0x28);
      for (i = 0, t = D3M_TRIS(obj->material); i < s->ntris; i++, t++) {
        k = 0;
        /* do-while: the original's loop is the bottom-tested pointer walk (`dec edi / jne`) */
        do {
          t->v[k] = &D3M_PTS(obj->material)[t->src->v[k]];
        } while (++k < 3);
      }
      redo = 1;
    }
    if ((obj->state & 0x10) || (obj->material->flags & 0x40)) {
      s->mesh->Transform(obj, s, &obj->material->cameraMatrix);
      obj->state &= 0xef;
      redo = 1;
    }
    if (redo) {
      D3M_COPY(D3M_PTS(obj->material), s->keys, s->nkeys * 0x50);
      m->Transform(D3M_PTS(obj->material), s->nkeys, 0);
    } else {
      n = s->nkeys;
      b = s->keys;
      a = D3M_PTS(obj->material);
      for (i = 0; i < n; i++, b++, a++) {
        a->color = b->color;
        d3_MaxZ = max(d3_MaxZ, a->z);
      }
    }
    n = min(s->ntris, d3_Cfg.maxpolys - (int)d3_SortCount);
    tex = m->tex;
    for (t = D3M_TRIS(obj->material); n > 0; n--, t++) {
      tt = t->tex;
      a = t->v[0];
      b = t->v[1];
      c = t->v[2];
      if (tt != tex && (a->rhw < 1e-7f || b->rhw < 1e-7f || c->rhw < 1e-7f) &&
          ((t->drawFlags & 4) || ((a->sx - b->sx)) * (a->sy - c->sy) <
                                     ((a->sy - b->sy)) * (a->sx - c->sx))) {
        d3_SortPtr->item = t;
        if (tt) {
          d3_SortPtr->key = (tt - d3_Textures) + 1;
          tt->stamp = d3_FrameCount;
        } else
          d3_SortPtr->key = 0;
        t->clip = m->planes;
        d3_SortPtr++;
        d3_SortCount++;
      }
    }
  }
  return 1;
}
/* 0x4554b0 (from d3_DrawObjectCB, m = &d3_Mirror): if obj has a polygon with a mirror texture, makes it the
   frame's mirror and builds the clipping planes */

void d3_MirBeginFrame(D3OBJECT *obj, D3MIRROR *m) {
  D3SURF *s;
  TSTEXTURE **tp;
  TSTEXTURE *tex;
  D3TRI *t;
  unsigned int i, n;
  int k, ntris;

  s = obj->info;
  if (s && s->mesh && !d3_MirrorObject) {
    n = s->mesh->ntex;
    tp = s->texHandles;
    for (i = 0; i < n; i++) {
      tex = *tp++;
      if (tex && (tex->bits & 0x20))
        goto found;
    }
    return;
  found:
    ntris = s->ntris;
    if (m->flags.on)
      m->flags.on = 0;
    m->tex = tex;
    if (m->info != s) {
      for (k = 0, t = s->tris; k < ntris; k++, t++) {
        if (t->tex == tex) {
          m->info = s;
          m->obj = obj;
          m->tri = t;
          m->Transform = d3_MirTransform;
          break;
        }
      }
    }
    m->flags.on = obj->state >> 3;
    if (m->flags.on) {
      for (k = 0, t = s->tris; k < ntris; k++, t++)
        if ((t->flags & 0x80) && t->tex == tex)
          break;
      m->flags.visible = k < s->ntris;
      if (m->planes) {
        mem_Free(m->planes);
        m->planes = 0;
      }
      if (m->flags.visible) {
        d3_DirToRef(obj, d3_Camera, &m->tri->src->n, &m->plane.v);
        m->plane.w = m->plane.x * m->tri->v[0]->x +
                     m->plane.y * m->tri->v[0]->y +
                     m->plane.z * m->tri->v[0]->z;
        m->planes = d3_MirCreatePlanes(m->obj, m->tex);
      }
    }
    if (m->planes)
      d3_MirrorObject = (int)obj;
  }
}

extern D3MIRROR d3_Mirror;
