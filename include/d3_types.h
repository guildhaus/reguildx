/* d3 records other units need without the rest of d3.h: the scene record of the table d3_Scenes and
   the texture flags tex_Load takes by value (ts_texture.c's TSFLAGS), the sort entry of d3_engine's
   d3_SortBuf (d3_sm fills it), the particle colour D3COLOR (d3_tools' d3t_CreateSmoke / CreateEarth take it
   by value), the vectors D3VECTOR / D3VECTOR4. Types only; d3.h and d3_engine.h include it. */
#ifndef D3_TYPES_H
#define D3_TYPES_H

typedef struct D3VECTOR {
  union {
    struct {
      float x, y, z;
    };
    float e[3]; /* the components by index (x, y, z) */
  };
} D3VECTOR;

typedef struct
    D3VECTOR4 { /* the engine pads most vectors to 16 bytes: a D3VECTOR and a fourth float */
  union {
    struct {
      float x, y, z;
    };
    D3VECTOR v; /* the vector itself, for the D3VECTOR parameters */
  };
  float w;
} D3VECTOR4;

typedef struct
    D3TEXFLAGS { /* passed by value to tex_Load (TSFLAGS in ts_texture.h) */
  union {
    unsigned char b[4];
    unsigned int all; /* the four flag bytes as one value (cleared at once) */
  };
} D3TEXFLAGS;

/* event tables ("d3e:"): an object's (D3OBJECT.events) and a scene's (D3SCENE.events) */
#define D3E_NEVENTS 7
typedef int (*D3EVHANDLER)(void *obj, int id, char *name,
                           int arg); /* obj: the object or scene, id: the event
      (sv fires 2 at an object's camera focus, 3 at its release, 6 at a scene),
      name: the handler's D3EVENT.name, arg: 0 at every known call */
typedef struct
    D3EVENT { /* 0x84 bytes, D3E_NEVENTS of them in D3OBJECT.events / D3_SCENE3C8 */
  D3EVHANDLER fn;
  char name[0x80]; /* 0x04, name of the handler */
} D3EVENT;

typedef struct
    D3SORTENT { /* 8 bytes, sorted by key with a radix sort (d3_RadixSort) */
  unsigned long key;
  void *item; /* a D3TRI (d3_engine; d3_sm: a height map triangle) */
} D3SORTENT;

typedef struct D3COLOR { /* a B, G, R, A colour (passed by value) */
  unsigned char b, g, r, a;
} D3COLOR;

typedef union D3COLORU { /* a D3COLOR stored or passed as its dword (the fog colour of a fog set, a sky colour) */
  D3COLOR c;
  unsigned long col;
} D3COLORU;

typedef struct
    D3FOGSET { /* 12 bytes: a fog colour and its range (the 6 fog sets, the current fog of a scene) */
  D3COLORU
  col; /* 0x00, d3_SetFogSet blends the bytes, the scene file holds the dword */
  float start, end; /* 0x04, 0x08 */
} D3FOGSET;

typedef struct D3LIGHTSET { /* 0x60 bytes: one of the 7 day-time light sets */
  D3VECTOR amb;             /* 0x00, the ambient colour (d3_AmbientColor) */
  D3VECTOR sun;             /* 0x0c, the sun colour (d3_SunColor) */
  D3FOGSET fog[6];          /* 0x18, the fog sets (d3if_Fog) */
} D3LIGHTSET;

typedef struct
    D3SCENE { /* 0x3e0 bytes, 64 of them in d3_Scenes: a scene and its copy of the engine's global
                 state (d3if_SelectScene stores the globals of the scene it leaves and loads those
                 of the one it selects) */
  char name
      [0x80]; /* 0x000, the scene (file) name; f3init.c names a reserved universe after its building type or goods */
  struct D3OBJECT *first; /* 0x080, first top-level object (d3_TopFirst) */
  struct D3OBJECT *last;  /* 0x084, last top-level object (d3_TopLast) */
  struct D3OBJECT *cam;   /* 0x088, d3if_MegaCam */
  D3VECTOR campos;        /* 0x08c, cam->pos */
  D3VECTOR camrot;        /* 0x098, cam->rotation */
  struct D3PARTSYS
      *parHead; /* 0x0a4, first of the particle list (d3_ParHead) */
  struct D3PARTSYS *parTail; /* 0x0a8, last of the particle list (d3_ParTail) */
  struct D3FLMAP *
      map; /* 0x0ac, the scene's terrain map (d3_Terrain; d3fl_ReloadTextures) */
  struct D3SM *hmap; /* 0x0b0, terrain height map */
  int mapSize; /* 0x0b4, height map size: 0x80 with terrain, 0x40 without, from the file */
  struct D3SKY *sky;    /* 0x0b8, d3_Sky */
  D3VECTOR amb;         /* 0x0bc, d3_AmbientColor */
  D3VECTOR sun;         /* 0x0c8, d3_SunColor */
  D3FOGSET fog;         /* 0x0d4, d3_fog_color, d3_FogStart1, d3_FogEnd2 */
  D3FOGSET fogs[6];     /* 0x0e0, d3if_Fog */
  D3LIGHTSET levels[7]; /* 0x128, d3if_Levels */
  D3EVENT *
      events; /* 0x3c8, the scene's D3EVENT table (D3E_NEVENTS entries, allocated by
                 d3e_RegisterSceneEvent, "d3e:RegisterSceneEvent(eventtable)", freed in d3_Shutdown) */
  int state0,
      state1; /* 0x3cc, d3if_SceneState0 and the word after it (0x5fb5c0, 0x5fb5c4) */
  signed char
      loaded; /* 0x3d4, set after a scene file was loaded into the slot; a scene slot
                 with loaded or dirty set is not free (d3t_FindFreeScene) */
  signed char
      dirty; /* 0x3d5, a reserved scene whose file is not loaded yet: the next use
                reloads it and clears the flag (f3init.c "flagged dirty") */
  char pad3d6[0x2];
  unsigned int
      sceneFlags; /* 0x3d8, the scene's d3_SceneFlags (d3if_SelectScene saves and restores it) */
  unsigned char hardware; /* 0x3dc, its d3_Hardware */
  char pad3dd[0x3];
} D3SCENE;

#endif
