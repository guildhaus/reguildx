/* d3_sm_types.h -- the terrain height / shadow map D3SM (d3_sm.c) and its cells, which path.c's A* search
   works on (the cells carry the search's node words). Types only; d3_sm.h and path.h include it. */
#ifndef D3_SM_TYPES_H
#define D3_SM_TYPES_H
#include "d3_types.h" /* D3VECTOR4 */

typedef struct D3SMENTRY { /* 0x1c bytes, one per height map cell */
  int type; /* 0x00, ground type, index into d3sm_GroundNames (0xd = border) and path.c's
               terrain cost table */
  short stamp; /* 0x04, path_Stamp of the search that touched the cell */
  short pad06;
  float f;             /* 0x08, the search's g + h */
  float g;             /* 0x0c */
  float h;             /* 0x10 */
  unsigned char flags; /* 0x14, 1 open, 2 closed, 4/8 reached from start/goal */
  unsigned char pad15;
  unsigned short next;   /* 0x16, the open list, sorted by f */
  unsigned short prev;   /* 0x18 */
  unsigned short parent; /* 0x1a */
} D3SMENTRY;

typedef struct
    D3SM { /* 0x34 bytes, a scene's terrain height / shadow map (D3SCENE.hmap) */
  D3VECTOR4 origin;    /* 0x00 */
  D3VECTOR4 cell;      /* 0x10, cell size; cell.y = height per unit */
  int size;            /* 0x20, cells per side (path.c: a power of two) */
  D3SMENTRY *entries;  /* 0x24 */
  unsigned char *data; /* 0x28, heights */
  int pad2c;
  int mask; /* 0x30, object shadow mask (D3OBJECT.stateFlags >> 2 & 3), tested as a byte */
} D3SM;

#endif
