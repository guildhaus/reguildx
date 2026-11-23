/* shot_types.h -- the cannon ball records of shot.c (ai_InitShot / ai_StepShot) and the wind EFFECTREC, for the units
   that send or start a ball (gv_types.h's GVSHOTMSG) without the rest of menu.h: types only. menu.h includes it. */
#ifndef SHOT_TYPES_H
#define SHOT_TYPES_H
#include "d3_types.h" /* D3VECTOR */

typedef struct
    EFFECTREC { /* 0x10 bytes at 0x62de60: the default effect (the wind): a vector and its scale */
  D3VECTOR
  pos; /* +0x00, 0, 0, 1.0 at the start; ai_InitWind sets (sin, 0, cos) of the wind direction 6 */
  union {
    float scale; /* +0x0c, 25.0 at the start */
    int scaleBits; /* the same bits as an int: 0x5dbc20 passes them through an int K&R view */
  };
} EFFECTREC;
typedef struct
    SHOTVEL { /* 0x10 bytes: a velocity as direction * speed and the speed */
  D3VECTOR v;
  float speed;
} SHOTVEL;
typedef struct
    SHOTREC { /* 0x68 bytes: a cannon ball in flight (am.c 0x4a6ae0 builds one per ball with ai_InitShot
                 from the barrel direction, the charge, the ball size and 7874 = the density of iron;
                 gv.c 0x4edf80 moves it with ai_StepShot); the units are meters and seconds, the
                 positions are in the world's units (inches: 39.37 per meter) */
  SHOTVEL
  velStart; /* +0x00, the start velocity: barrel direction * speed, speed = charge / mass * 0.1 */
  SHOTVEL
  vel; /* +0x10, the current velocity (m/s), the start velocity at first */
  D3VECTOR posStart; /* +0x20, the start position */
  float pad2c;
  D3VECTOR pos; /* +0x30, the current position, the start position at first */
  float pad3c;
  EFFECTREC
  wind; /* +0x40, the wind (ai_DefaultEffect) with its scale clamped to 0 .. 60 and the vector scaled by it */
  float
      area; /* +0x50, the ball's SPHEREVOLUME surface (2 pi size^2), the drag area */
  float mass; /* +0x54, volume * density */
  float
      energy; /* +0x58, set by ai_StepShot when the ball lands: 0.5 * mass * v^2 (0 when it left the map) */
  int state;  /* +0x5c, 1 in flight, 2 landed, 3 left the height map */
  int time; /* +0x60, d3_Time (ms) of the last flight step (one step per ms) */
  unsigned
      steps; /* +0x64, the flight steps made; ai_ScatterShot works only before the first */
} SHOTREC;

#endif
