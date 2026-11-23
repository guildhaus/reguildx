struct VFSFILE;
struct AIBLD;
struct AICHAR;
/* Declarations of ahm.c (0x4eaa50.., the alchemist's building / recipes; tag "ahm_AllocRecipePrototypes" 0x60f1c8..). Names are ours. */
#ifndef AHM_H
#define AHM_H

#include "ai_types.h" /* AITIME */

#include "ahm_types.h" /* AHMSLOT */
#pragma pack(push, 1)
#define AHM_CMD_SET_SHARE                                                      \
  0x61437353 /* 'SsCa', sets the share at +8 of the record (0x4eca00) */
#define AHM_CMD_ADD_PLACE                                                      \
  0x61616452 /* 'Rdaa', adds a place from the recipe table (0x4ecb30) */
#define AHM_CMD_SET_PLACE                                                      \
  0x61535263 /* 'cRSa', sets the value of a place (0x4ecd10) */
#define AHM_CMD_ADD_VALUE                                                      \
  0x61536d53 /* 'SmSa', adds to the value at +4 of the record (0x4ecdb0) */
#define AHM_CMD_DELETE 0x46697245 /* 'ErFi', deletes the alchemist (0x4ece60) */
#define AHM_CMD_REMOVE_PLACE 0x61736452 /* 'Rdsa', removes a place (0x4ecbc0) */
typedef union AHMSEED { /* 0x6f0ddc, the seed of the CRT generator (its low word is saved) */
  int seed;              /* the seed as the shuffler reads it */
  unsigned short seed16; /* the low word written on a restart */
} AHMSEED;
#pragma pack(pop)
typedef struct
    AHMSTEP { /* 0x18 bytes, 0x6f0de0 (3 of them): a step of the grid walk */
  int on;     /* +0x0, 1 while the step is in use */
  AHMGRID
  grid; /* +0x4, the table entry the step took (ahm_FillSteps copies its three words) */
  int x,
      y; /* +0x10 / +0x14, its position on the 25 x 25 grid (also the name indexes 0x144a7a8 / 0x144a80c) */
} AHMSTEP;

extern struct AIBTYPE *ai_BTypes;    /* 0x7e3f30, the building types */
extern int ai_PlayerPrototypeCount;  /* 0x6f0e28 */
extern AHMGRID *ai_PlayerPrototypes; /* 0x6f0e2c */
extern int ai_RecipePrototypeCount;  /* 0x6f0e30 */
extern AHMGRID *ai_RecipePrototypes; /* 0x6f0e34 */
extern int ai_WalkX, ai_WalkDX, ai_WalkY, ai_WalkDY,
    ai_WalkIndex; /* 0x6f0dc8, 0x6f0dcc, 0x6f0dd0, 0x6f0dd4, 0x6f0dd8 */
extern AHMSEED ai_WalkSeed;                 /* 0x6f0ddc */
extern AHMSTEP ai_WalkSteps[3];             /* 0x6f0de0 */
extern int ahm_Tab[8];                      /* 0x60f1b0 */
#include "ai_types.h"                       /* AITIME */
extern AITIME ai_Time;                      /* 0x770ae0, the game clock */
struct AIJOB *he_FindEvent(int n, ...);     /* 0x53e400 */
struct AIJOB *he_NextEvent(void);           /* 0x53e300 */
int cm_SendExSetHE(int k, struct AIJOB *p); /* 0x4c4c60, cm.c */

struct AICHAR *ahm_OwnerChar(
    struct AIBLD
        *p); /* 0x4eaa50, the character the alchemist object p belongs to */
int ahm_UsedSlots(
    struct AICHAR *
        c); /* 0x4eaa90, the number of the places in use in the record of c's object */
int ahm_HasRecord(
    struct AICHAR *
        c); /* 0x4eaad0, 1 when the character c has an alchemist object with a record */
float ahm_Share(
    struct AICHAR *c,
    int i); /* 0x4eab20, the share i (0 .. 3) of the record of c's object, -1 when none */
AHMSLOT *ahm_SlotOf(
    struct AICHAR *c,
    int id); /* 0x4eabd0, the place of c's record with the id (forwards to ahm_FindSlot) */
AHMSLOT *ahm_FindSlot(
    struct AICHAR *c,
    int id); /* 0x4eabe0, the place of c's record with the id, 0 when there is none */
int ahm_HasFreeSlot(
    struct AICHAR *
        c); /* 0x4eac20, 1 when a place of c's record is still free (the share 2 sets the limit of six) */
void ahm_FillSteps(
    void); /* 0x4eac60, fills the three walk steps from the shuffled table */
void ahm_ShufflePlayers(
    int init); /* 0x4ead20, shuffles the player prototype table (init: reseed and restart the walk at random grid positions) */
void ahm_ShuffleTable(
    void); /* 0x4eadc0, shuffles the player prototype table with random swaps */
AHMGRID *ahm_FindRecipe(
    int id); /* 0x4eae60, the entry of the recipe prototype table with the id, 0 when there is none */
AHMGRID *ahm_RandomRecipe(
    struct AICHAR *
        c); /* 0x4eaea0, a random recipe the character c has no place for yet, 0 when it may not take more */
int ahm_ResearchTime(
    struct AICHAR *c,
    AHMGRID
        *g); /* 0x4eaf50, the research time of a recipe in tenths of minutes */
int ahm_ResearchMinutes(struct AICHAR *c,
                        AHMGRID *g); /* 0x4eafa0, the same in minutes */
float ahm_ResearchProgress(
    struct AICHAR *c, AHMGRID *g,
    int *
        cap); /* 0x4eafd0, the progress made in *cap minutes (which get the minutes used) */
float ahm_ShareProgress(struct AICHAR *c, int i,
                        int *cap); /* 0x4eb0b0, the same for the share i */

float ahm_PlaceFactor(struct AICHAR *c, int id); /* 0x4eb130 */
int ahm_ResearchState(struct AIBLD *o, int *a, float *f,
                      int flag);              /* 0x4eb180 */
void ahm_RescheduleResearch(struct AIBLD *o); /* 0x4eb410 */
int ahm_LoadPrototypes(int mode);             /* 0x4eb480 */

int ahm_LoadIni(void);          /* 0x4eb4c0 */
int ahm_LoadDfn(void);          /* 0x4eba80 */
int ahm_SaveDfn(void);          /* 0x4ebd60 */
int ahm_ObjectId(char *name);   /* 0x4ebf50 */
void ahm_FreePrototypes(void);  /* 0x4ebf60 */
AHMSTEP *ahm_WalkStep(int i);   /* 0x4ec2d0 */
void ahm_ClearStep(AHMSTEP *p); /* 0x4ec2f0 */
extern void *main_Instance;     /* 0x75e140, the module handle */
extern struct VFSDIR *vfs_Root; /* 0x6333fc, the VFS directory tree (vfs.h) */
struct AIOBJ *gm_Query(void *list, int n, ...);          /* 0x4ffe90 */
int gm_RemoveObject(struct AIOBJ **list, unsigned item); /* 0x4ffff0 */
struct CHARACTER *gm_PlaceOnStage(int id, int a, int b, struct D3VECTOR *p,
                                  struct D3VECTOR *ori); /* 0x4fbd10 */
struct AICHAR;
void gm_ChooseHeadIcon(struct AICHAR *c);       /* 0x4fb890 */
void gm_RefreshGoodsLists(unsigned p);          /* 0x4ff190 */
int gm_AddObjekt(int id, int proto, int n);     /* 0x500970 */
void gm_KillSpieler(int c, int mode);           /* 0x503c60 */
int cm_SendCommand(void *p);                    /* 0x4c61b0 */
extern signed char ai_Relations[768][768];      /* 0x7e5360 */
extern signed char ai_RelationMemory[768][768]; /* 0x889f80 */
extern int ai_CharCount;           /* 0x6f1bc0, the number of characters */
extern unsigned char ai_OwnPlayer; /* 0x6f1bc5 */
extern int ai_NextObjectId;        /* 0x61a654 */

int ahm_SaveWalk(void *f); /* 0x4ebfb0 */
int ahm_LoadWalk(void *f); /* 0x4ec140 */
int ahm_SendCreateAlchemist(
    struct AIBLD *o,
    AHMSTEP *
        s); /* 0x4ec490, posts the type 99 message that creates the alchemist's owner character from the step */
int cm_SendCreateAlchemist(void *p); /* 0x4c6170 */

int ahm_StepValue(AHMSTEP *s);        /* 0x4ec320 */
int ahm_ObjectValue(struct AIBLD *p); /* 0x4ec3d0 */
int ahm_CreateAlchemist(
    AHMCREATEMSG *
        m); /* 0x4ec500, the alchemist character of the creation message m; its id or 0xffff */
int ahm_SendSetShare(struct AICHAR *c, int id, float v); /* 0x4ec940 */
int ahm_SetShare(AHMORDER *m, struct AHMREC *rec);       /* 0x4eca00 */
int ahm_SendAddPlace(struct AICHAR *c, int id);          /* 0x4ecaa0 */
int ahm_AddPlace(AHMORDER *m, struct AHMREC *rec,
                 struct AIBLD *o); /* 0x4ecb30 */
int ahm_RemovePlace(AHMORDER *m, struct AHMREC *rec,
                    struct AIBLD *o);                         /* 0x4ecbc0 */
int ahm_SendSetPlaceValue(struct AICHAR *c, int id, float v); /* 0x4ecc30 */
int ahm_SetPlaceValue(AHMORDER *m, struct AHMREC *rec);       /* 0x4ecd10 */
int ahm_SendAddValue(struct AICHAR *c, float v);              /* 0x4ecd50 */
int ahm_AddValue(AHMORDER *m, struct AHMREC *rec);            /* 0x4ecdb0 */
int ahm_SendDelete(struct AICHAR *c);                         /* 0x4ece10 */
int ahm_WriteRecord(void *f, struct AIBLD *o);                /* 0x4ecf10 */
int ahm_ReadRecord(
    void *f,
    struct AIBLD *
        o); /* 0x4ed040, reads the alchemist record of o (+0x65) from the file f */
int ahm_DeleteAlchemist(AHMORDER *m, struct AHMREC *rec,
                        struct AIBLD *o); /* 0x4ece60 */

/* declared in other units' headers before (moved to the owner) */
extern unsigned short ai_PlayerId;    /* 0x6f25b8 */
extern unsigned short d2_HighBitMask; /* 0xf8a11c */

#endif
