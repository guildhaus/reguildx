/* Declarations of rmsg.c (0x4b6480..0x4bb720): 69 message callbacks (text 0x12e7 + type), table 0x602570,
   dispatcher 0x4bb6c0. Names are ours. */
#ifndef RMSG_H
#define RMSG_H

#include "am.h"

/* G14MSG, the argument of the callbacks: ai_types.h (the random-message event 0x42 holds one, AIJOB.msg) */



void gm_ClockToDate(struct AITIME *c, unsigned char *out);                                            /* 0x4fe2c0 */


extern unsigned int ai_RandomSeed;       /* 0x6f0730, random seed of the messages */

typedef int (*G14CB)(G14MSG *m);
extern G14CB ai_MsgCallbacks[0x45];        /* 0x602570 */
int ai_PostRandomMessages(int n, int id);   /* 0x4bb720, posts 0..n random messages (AIMSG 0x42) for the character id */
int ai_RunMessage(G14MSG *m);   /* 0x4bb6c0, runs the message m through ai_MsgCallbacks (from the 8th day on) */

#endif
