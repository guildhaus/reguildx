/* The building-site record of rd's ai_Bauplaetze (0xf812e4, defined by f3init) and the vegetation record G15PLANT
   (AIBLD.plants), for the units that read them without rd.h: types only. rd.h includes it. */
#ifndef RD_TYPES_H
#define RD_TYPES_H

typedef struct
    G15BK { /* 0x60 bytes, a building site (ai_Bauplaetze[ai_NBauplaetze]) */
  char name[0x40];  /* 0x00 */
  float x0, y0, z0; /* 0x40, the minimum corner */
  char pad4c[4];
  float x1, y1, z1; /* 0x50, the maximum corner */
  char pad5c[4];
} G15BK;

struct D3OBJECT;
typedef struct G15PLANT { /* 0x18 bytes, 64 per vegetation map */
  int id;                 /* 0x00, from veg_NextId */
  int bldId; /* 0x04, the building whose map holds it (cm's handler of message 0x2c sets it) */
  unsigned char x;     /* 0x08, cell */
  unsigned char z;     /* 0x09 */
  unsigned short type; /* 0x0a, G15TREE.id; 0 removes it */
  signed char size;    /* 0x0c, size in cells */
  signed char state;   /* 0x0d, growth state; -1: free */
  char pad0e[2];
  int fallId; /* 0x10, the id message 0x2c set the fall model with (veg_SetPlant: -1 for a plain
                 plant); a later 0x2c without fall and that id puts the plant back */
  struct D3OBJECT *obj; /* 0x14, its 3D object */
} G15PLANT;

#endif
