struct PATHOUT;
struct PMAP;
struct D3SCENE;
struct D3FLMAP;
struct D3SM;
/* Declarations of rd.c (0x4bc2e0..): places for animals (door dummies, free cells, dummy lookup), the
   vegetation map, roads. Names are ours. */
#ifndef RD_H
#define RD_H
#include "path.h" /* PATHOUT, for G15ROAD */
struct D3VECTOR;

typedef struct G15FIND {       /* 0xa4 bytes, context of rd_CollectNamed */
  char name[0x20];             /* 0x00 */
  struct D3OBJECT *objs[0x20]; /* 0x20, the objects named so */
  int n;                       /* 0xa0 */
} G15FIND;

typedef struct
    G15TREE { /* 0x46 bytes, the vegetation types veg_Types ("TANNE", "BUCHE", "EICHE", ..; id 0 ends) */
  unsigned short id;    /* 0x00 */
  char name[0x40];      /* 0x02 */
  unsigned char size;   /* 0x42, copied to G15PLANT.size (its size in cells) */
  unsigned char states; /* 0x43, growth states per model */
  unsigned char lastState; /* 0x44, the last growth state */
  char pad45;
} G15TREE;

#include "rd_types.h" /* G15BK, G15PLANT */

typedef struct G15ROAD { /* 0x1020 bytes, rd_Road */
  struct D3FLMAP *map;   /* 0x00, the town's terrain map (d3_Scenes[0].map) */
  struct D3SM
      *grid; /* 0x04, d3sm_Create's grid: its entries' type 6 / 0xb is a road */
  int simple; /* 0x08, the ground type "EINFACHER_WEG" (2 if none) */
  int prunk;  /* 0x0c, the ground type "PRUNK_WEG" (1 if none) */
  unsigned char path[0x400][2];  /* 0x10, path_Find's cells */
  int n2;                        /* 0x810 */
  unsigned char path2[0x400][2]; /* 0x814, the road so far */
  PATHOUT out; /* 0x1014, path_Find's out: count, max, cells (path) */
} G15ROAD;

#include "d3_types.h" /* D3VECTOR4 */

typedef struct G15BKFIND { /* context of rd_FindSiteCB */
  char name[0x40];         /* 0x00 */
  D3VECTOR4 pos;           /* 0x40, the site's place (world) */
  struct D3OBJECT *found;  /* 0x50, the site object found, 0: none */
} G15BKFIND;

#ifndef DATA_VIEWS_H
#endif
extern G15ROAD rd_Road; /* 0xf81300 */

extern G15TREE veg_Types[]; /* 0x602860 */
extern int veg_NextId;      /* 0x6f0748, the next plant id */
extern char ai_DataPath[];  /* 0x75dca0, the data path */
extern struct D3FLMAP
    *d3_Terrain; /* 0x633738, d3_fl.c: the current terrain map */

/* views of other units */
struct D3SM *d3sm_Create(struct D3FLMAP *t, int size, int mask); /* 0x45eeb0 */
struct D3FLMAP;
void d3fl_MakeDivide(struct D3FLMAP *map); /* 0x441300, d3_fl.c */
struct D3OBJECT;
char d3if_Delete(struct D3OBJECT *obj); /* 0x447190, d3_interface.h */
char d3if_ShowTree(struct D3OBJECT *obj,
                   char show); /* 0x447300, d3_interface.h */
struct D3OBJECT *
d3_LoadGroup(char *name, void *f,
             struct D3OBJECT *parent); /* 0x44c3f0, d3_int_io.h: D3OBJECT * */
void err_Message(char *msg);           /* 0x4222b0 */
void d3_SetObjectPos(
    struct D3OBJECT *obj,
    const struct D3VECTOR *pos); /* 0x43b790, d3.h: D3OBJECT *, D3VECTOR * */
struct D3OBJECT *d3_FindObject(struct D3OBJECT *a, int flags,
                               struct D3OBJECT *c,
                               char *name); /* 0x449690, d3.h */
char d3sm_GetVertex(
    struct D3SM *h, int x, int z,
    struct D3VECTOR *out); /* 0x45f100, ch.h: D3SM *, D3VECTOR * */
char ch_FindFreeCell(struct D3SM *h, struct D3VECTOR *from, struct D3VECTOR *to,
                     int x, int z, int *px, int *pz, int max,
                     int flags); /* 0x4072a0, ch.h */
char d3_ForEachObject(struct D3SCENE *scene, struct D3OBJECT *obj,
                      unsigned int mask, char (*cb)(struct D3OBJECT *, void *),
                      void *ctx); /* 0x438d40, d3.h: D3OBJECTCB */

int rd_DoorPos(struct D3VECTOR *pos);
struct D3VECTOR4;
int rd_PointsNear(struct D3VECTOR *pos, int n, struct D3VECTOR4 *pts);
char rd_CollectNamed(struct D3OBJECT *obj, void *ctx);
struct D3OBJECT *rd_RandomNamedObject(char *name);
G15TREE *veg_FindType(int type);
G15PLANT *veg_FindPlantAt(G15PLANT *p, int x, int z);
G15PLANT *veg_FindPlantObject(G15PLANT *p, struct D3OBJECT *obj);
G15PLANT *veg_FindPlantId(G15PLANT *p, int id);
G15PLANT *veg_FindPlantArea(G15PLANT *p, int x, int z);
int veg_Fits(G15PLANT *p, int x, int z, int size);
G15PLANT *veg_SetPlant(G15PLANT *p, int x, int z, int type, int fall);
void veg_GrowPlants(G15PLANT *p);
void veg_LoadModel(G15PLANT *q, int fall);
void veg_ShowPlants(G15PLANT *p);
void veg_HidePlants(G15PLANT *p);
int rd_BuildRoad(struct D3OBJECT *obj, int name);
int rd_PathToRoad(G15ROAD *r, int x, int z, int tx, int tz);
void rd_AddBauplaetze(G15ROAD *r);
void rd_AllBauplatzToSupermap(G15ROAD *r, struct D3OBJECT *site);
char rd_FindSiteCB(struct D3OBJECT *obj, void *ctx);
G15BK *rd_GetBKSize(char *name);
void rd_WorldToCell(float *x, float *z, const struct D3VECTOR *v,
                    struct D3OBJECT *obj, G15ROAD *r);
void rd_FillQuad(G15ROAD *r, float *c, unsigned char v, int t);

#endif
