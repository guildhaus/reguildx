struct D3PARTSYS;
struct D3COLOR;
struct D3SM;
struct D3VECTOR;
struct SBSAMPLE;
struct SHOTREC;
struct AIBLD;
struct AICHAR;
struct GVSHOTMSG;
struct VFSFILE;
struct D3OBJECT;
struct CHARACTER;
struct G15PLANT;
/* Declarations of gv.c (0x4ed170.., the avatar table 0x60f310 and the effect slots 0x6f1008). Names are ours. */
#ifndef GV_H
#define GV_H
#include "ai_types.h"
#include "cm_types.h"                /* CRIME */
#include "gv_types.h"                /* GVENTRY, AIDEC, ORDSTATS, ORDSTATROUND, ORDMSGREC */

extern AITIME gv_LastTime;              /* 0x6f0e38, ai_Time at the last effect step (struct copies of it) */
typedef struct GVGRAVE {                /* 0x44 bytes, a dead person in a grave (GVYARD.graves; filled by gv_BuryNewDead) */
    int id;                             /* 0x00, the object id (ai_NextObjectId), -1 when free */
    char first[0x10];                   /* 0x04, the first name (TXT_MALE_FIRST_NAMES / TXT_FEMALE_FIRST_NAMES by sex) */
    char family[0x10];                  /* 0x14, the family name (TXT_FAMILY_NAMES) */
    unsigned char traits[5];            /* 0x24, five values 42 .. 189 (random 0 .. 7 * 21 + 42) */
    char pad29[3];
    int v2c;                            /* 0x2c, 1 .. 9 */
    int v30;                            /* 0x30, 1 .. 2 */
    int nameId;                         /* 0x34, 1 .. 0x5e, the id of its gm_NameRecord */
    int sex;                            /* 0x38, 0 male, 1 female (picks the first-name list and the gm_NameRecord table) */
    int icon;                           /* 0x3c, 0x639 + one of the name record's four words +0x34 (0xff: none) */
    int year;                           /* 0x40, a year 1 .. 4 before the burial (ai_Time.year), a guess: the year of death */
} GVGRAVE;
typedef struct GVYARD {                 /* 0x24 bytes, the graveyard record of a kind 0x1d building (AIBLD.yard; gv_AllocGraveyard) */
    int id;                             /* 0x00, the building's id */
    int kind;                           /* 0x04, 1 .. 3, the building type's level when allocated */
    GVENTRY *lists[4];                  /* 0x08, the entries (0x14 bytes) of the four grave sizes (0x44 << i bytes each) */
    unsigned char open[4];              /* 0x18, the size i is in use (open[0] is set at allocation; 0x19 .. 0x1b by expansion) */
    GVENTRY *entries;                   /* 0x1c, all entries ("gv_Alloc:_all_graves") */
    GVGRAVE *graves;                    /* 0x20, the grave records, first word -1 when free ("gv_Alloc:_all_zombies") */
} GVYARD;
#pragma pack(push, 1)
typedef struct GVORDER {                /* 0x1f bytes, a graveyard order: the data of message 0x60 (cm_SendGraveOrder), executed by type in cm.c's handler 0x4cce10 */
    int type;                           /* 0x00, 0 .. 6 (0 gv_BuryCharacter, 1 a grave reserved for a living character 0x4f0490, ..) */
    int chr;                            /* 0x04, the character's netId (AICHAR.netId), -1 for none */
    int bld;                            /* 0x08, the graveyard building's id (AIBLD.id) */
    int size;                           /* 0x0c, the grave size (GVYARD.lists index) */
    unsigned char entry;                /* 0x10, the entry of that list, 0xff for none */
    short years;                        /* 0x11, type 1: years added to ai_Time.year for the entry's GVENTRY.until */
    int price;                          /* 0x13, type 1: the price (> 0: the owner's money changes) */
    int objId;                          /* 0x17, ai_NextObjectId, filled by the handler when the game is networked */
    int seed;                           /* 0x1b, a rand() the handler fills otherwise */
} GVORDER;
typedef struct GVRAISE {                /* 0x19 bytes, a raising of a dead person: the data of message 0x62 (cm_SendRaiseDead), run by gv_RaiseDead */
    int seed;                           /* 0x00, a rand() the handler 0x4ccf10 fills (util_Seed) */
    int objId;                          /* 0x04, ai_NextObjectId when the game is networked */
    int bld;                            /* 0x08, the graveyard building's id (AIBLD.id) */
    int size;                           /* 0x0c, the grave size (GVYARD.lists index) */
    unsigned char entry;                /* 0x10, the entry of that list */
    int grave;                          /* 0x11, the dead person's GVGRAVE.id */
    int kind;                           /* 0x15, 0x1b or 0x1c (the handler refuses others) */
} GVRAISE;
#pragma pack(pop)
typedef struct GVCANNON {               /* 0x20 bytes, the state of the cannon scene (sv_t 0x57e270 ..), saved with the effects */
    int bld;                            /* 0x00, the record id (rec + 1) the scene was last set up for, -1 after the reset */
    int spare;                          /* 0x04, no reader besides the save game */
    float camTarget[3];                 /* 0x08, the aim angles (pitch, yaw, roll) the scene keeps between visits: the camera's rotation (+0x84 .. +0x8c) at the first, the scene's rot after */
    int sliderA;                        /* 0x14, the first panel slider (0 .. 4) */
    int sliderB;                        /* 0x18, the second panel slider (0 .. 100) */
    int selected;                       /* 0x1c, the selected object (the scene's +0xa0) */
} GVCANNON;
extern GVCANNON gv_Cannon;              /* 0x925100 */
extern AITIME ai_Time;                   /* 0x770ae0, the game clock */


typedef struct GVAVATAR {               /* 0xf4 bytes, a record of the avatar table gv_Avatars (32) */
    unsigned id;                        /* 0x00, four characters ("neVm"), the key of the save game's (id, used) pairs */
    char name[0x10];                    /* 0x04, "Maven" (the read report prints it): the first name of the character made from it */
    char title[0x10];                   /* 0x14, "of Reading": its family name */
    unsigned char skills[5];            /* 0x24, the five skill bytes (AICHAR.skills) */
    char pad29[3];
    float mood[14][3];                  /* 0x2c, the mood triples (AICHAR.mood; gv_AllocAvatar sets the second of each to the first * 0.001) */
    unsigned char jobId;                /* 0xd4, AICHAR.jobId */
    unsigned char sex;                  /* 0xd5, AICHAR.sex */
    unsigned char b00c;                 /* 0xd6, AICHAR.faith */
    char ownName[0x1b];                 /* 0xd7, AICHAR.ownName, the head name */
    unsigned char used;                 /* 0xf2, 1 while the record is in use (gv_AllocAvatar), 0 free */
    char padf3;
} GVAVATAR;
typedef char gv_AssertGVAVATAR[sizeof(GVAVATAR) == 0xf4 ? 1 : -1];
extern GVAVATAR gv_Avatars[0x20];     /* 0x60f310, the avatars: the characters the graveyard raises (gv_AllocAvatar) */


#pragma pack(push, 1)

#pragma pack(pop)

/* a record of the event list (he_FindEvent / he_NextEvent) as the order handlers read it */
typedef struct ORDEVENT {
    char pad000[0xac];
    int ownerId;                    /* 0x0ac, the character the event belongs to */
    int targetId;                   /* 0x0b0, the event's other character */
} ORDEVENT;
extern volatile unsigned long d3_Time;  /* 0x6333cc, milliseconds (tb.c) */
extern int d3_CurrentScene;                /* 0x633444 */

struct AIBLD *gm_BuildQuery(int n, ...);                     /* 0x501190 */
char d3if_Delete(struct D3OBJECT *obj);  /* 0x447190, d3_interface.h */
struct D3PARTSYS *d3t_CreateExplosion(void *parent, struct D3VECTOR *pos, int count, float radius, float height, float z, float size, unsigned int duration); /* 0x416040, d3_tools.c */
struct SBSAMPLE; struct SBBANK;
struct SBSAMPLE * sb_GetSample(struct SBBANK *bank, char *name);   /* 0x426030 */
struct AIMSG; int cm_SendLongMessage(struct AIMSG *msg);                     /* 0x4c4b70 */
void cm_BeginFieldBlock(void *o, int id);                     /* 0x4c3ba0 */
int cm_AddFieldValues(unsigned char size, unsigned char n, unsigned short field, void *v);                     /* 0x4c3d00 */
int cm_SendFieldDeltas(void);                     /* 0x4c49a0 */
extern struct AIBLD *ai_Blds;           /* 0x889f74, 256 records of 0xa9 bytes */
extern struct AICHAR *ai_PlayerChar;    /* 0x6f1bf8, the player's character */
extern const struct D3VECTOR4 d3_Origin;     /* 0x5ebba4, (0, 0, 0), d3_vec.c */
extern const struct D3VECTOR d3_ZeroRot;      /* 0x5ebbb4, (0, 0, 0), d3_vec.c */

char *gv_AllocAvatar(void);              /* 0x4ed170 */
int gv_WriteAvatars(void *f);             /* 0x4ed1e0 */
int gv_ReadAvatars(void *f);             /* 0x4ed270 */
typedef struct GVEFFPART {              /* 0x68 bytes, one of an effect slot's three parts (saved field by field) */
    float v0[4];                        /* 0x00 */
    float v1[4];                        /* 0x10 */
    float v2[4];                        /* 0x20 */
    float v3[4];                        /* 0x30, not saved */
    float v4[4];                        /* 0x40 */
    int a, b, c;                        /* 0x50 */
    int state;                          /* 0x5c, the part is a SHOTREC (menu.h): this is its state, 0 idle, 1 in flight, 2 landed, 3 left the map (gv_UpdateEffects) */
    int time;                           /* 0x60, not saved: the reader sets it to d3_Time */
    int steps;                          /* 0x64, the flight steps made (SHOTREC.steps) */
} GVEFFPART;
typedef struct GVEFFREC {               /* 16 bytes, a record of an effect slot's argument */
    int bldId;                          /* 0x00, a building id (gm_BuildQuery(1, 1, id)), -1: none */
    float dist;                         /* 0x04, the building's distance from the explosion (gv_ExplodeShot) */
    int mode;                           /* 0x08, 1: the explosion lay inside the building's box, 2: near it (gv_ExplodeShot); 1: the message depends on value */
    float value;                        /* 0x0c, the explosion's strength at the building (0 .. 100), compared with 25 */
} GVEFFREC;
typedef struct GVEFFARG {               /* 0x38 bytes, the argument of an effect slot's default callback (gv_EffectArgs, one per slot) */
    int cur;                            /* 0x00, the record at hand (0 .. 2) */
    int effectId;                       /* 0x04, the effect slot's id (gv_ExplodeShot) */
    GVEFFREC recs[3];                   /* 0x08 */
} GVEFFARG;
typedef struct GVEFFECT {               /* 0x170 bytes, an effect slot of gv_Effects (8) */
    int id;                             /* 0x000, -1: free */
    int flags;                          /* 0x004, 4: to be released (gv_ReleaseEffect) */
    union {
        struct {
            float f08, f0c, f10;        /* 0x008, 1.0 after the reset; the per-frame step adds dt up to 1.0 */
        };
        float charge[3];                /* 0x008, by the salvo's mode (0 .. 2): a received salvo takes its value off (0x4eee00, not below 0) */
    };
    int f14;                            /* 0x014 */
    GVEFFPART parts[3];                 /* 0x018 */
    int tail[3];                        /* 0x150, 0: the part is free (gv_UpdateEffects clears it when the part ends) */
    struct D3OBJECT *objs[3];           /* 0x15c, the parts' "kugel" objects (gv_UpdateEffects creates them, gv_FreeEffectObjects frees them) */
    int (*cb)(GVEFFARG *arg);           /* 0x168, the slot's callback (gv_EffectNotifyOwner by default), called when a part ends */
    GVEFFARG *arg;                      /* 0x16c, its argument: cur = the part that ended */
} GVEFFECT;
extern GVEFFECT gv_Effects[8];          /* 0x6f1008, the effect slots */
typedef char gv_AssertGVEFFECT[sizeof(GVEFFECT) == 0x170 ? 1 : -1];
extern GVEFFARG gv_EffectArgs[8];      /* 0x6f0e48, one per effect slot */
int gv_EffectNotifyOwner(GVEFFARG *a);  /* 0x4ed3f0, the default effect slot callback: tells the owner of the current record's building */
int gv_WriteEffects(void *f);             /* 0x4ed480 */
int gv_ReadEffects(void *f, int v);      /* 0x4ed910 */
void unk_ResetEffectSlots(void);               /* 0x4eddf0 */
void gv_FreeEffectObjects(void);               /* 0x4ede70 */
GVEFFECT *gv_FindEffect(int id);        /* 0x4eded0 */
void gv_ReleaseEffect(int id);             /* 0x4edf10 */
void gv_ExplodeShot(int damage, int effectId, struct SHOTREC *shot, GVEFFARG *out);  /* 0x4ee360 */
void gv_UpdateEffects(void);               /* 0x4edf80 */
int gv_RequestEffectLoad(struct AIBLD *bld);            /* 0x4eea70 */
int gv_ReserveEffect(int id);              /* 0x4eeaa0 */
int gv_StopEffect(int id);              /* 0x4eeb00 */
int gv_FireShots(struct AIBLD *bld, struct AICHAR *ch, struct SHOTREC *a, struct SHOTREC *b, struct SHOTREC *d, float v, int cost, int x);  /* 0x4eeb70 */
char *gv_GetEffect(int id);            /* 0x4eedd0 */
int gv_StartShot(struct GVSHOTMSG *m, int w);       /* 0x4eee00 */
void gv_SetEffectCallback(int id, void *cb, void *arg);  /* 0x4eeee0 */
float gv_SalvoCharge(int a, int b, int c);  /* 0x4eef50 */
struct G9KIND; void gv_CannonKind(int n, struct G9KIND *out);  /* 0x4ef000, am.h's record */
void cm_SendMoneyDelta(int a, int b);                     /* 0x4c5f60 */
extern unsigned char ai_OwnPlayer;      /* 0x6f1bc5 */
void gv_BuildingCannon(struct AIBLD *o, unsigned *balls, unsigned *kind);  /* 0x4ef170 */
void gv_CannonScatter(struct AIBLD *o, float *spread, float *speedSpread);  /* 0x4ef260 */
float gv_CannonItemFactor(struct AIBLD *o);           /* 0x4ef330 */
int gv_GraveCount(struct AIBLD *o);    /* 0x4ef3c0 */
int gv_GravesInUse(struct AIBLD *o);    /* 0x4ef440 */
int gv_EntryCount(struct AIBLD *o);    /* 0x4ef470 */
int gv_SizeOpen(struct GVYARD *r, int i);      /* 0x4ef4f0 */
extern struct AIBTYPE *ai_BTypes;    /* 0x7e3f30, the building types */
int gv_ListEntry(struct GVYARD *r, int i, unsigned char n);  /* 0x4ef570 */
int gv_EntryIndex(struct GVYARD *g, struct GVENTRY *e);     /* 0x4ef6b0 */
int gv_EntryHeldBy(struct AICHAR *a, char *b);    /* 0x4ef710 */
int gv_EntrySameId(int *a, int *b);      /* 0x4ef740 */
int gv_EntryIsFree(int *a, int *b);      /* 0x4ef760 */
int gv_EntryIsUsed(int *a, int *b);      /* 0x4ef770 */
int gv_EntryHasId(int *a, int *b);      /* 0x4ef780 */
struct GVENTRY *gv_FindEntry(void *a, struct AIBLD *bld, struct GVENTRY *after, int (*cb)(), int l);  /* 0x4ef7c0 */
struct GVENTRY *gv_LoadGraveyard(struct AIBLD *o, int *e);  /* 0x4ef900 */
GVGRAVE *gv_RandomGrave(struct AIBLD *o);/* 0x4ef930 */
extern const int gv_EntryCounts[];             /* 0x5ee054, entries per kind */
extern const int gv_ListEntries0[4];         /* 0x5ee084, the entries of list 0 by the building level */
extern const int gv_ListEntries1[4];         /* 0x5ee094, of list 1 */
extern const int gv_ListEntries2[4];         /* 0x5ee0a4, of list 2 */
extern const int gv_ListEntries3[4];         /* 0x5ee0b4, of list 3 */
int gv_BuryNewDead(struct AIBLD *o, int n);  /* 0x4ef9c0 */
GVYARD *gv_AllocGraveyard(struct AIBLD *o);  /* 0x4efc10, allocates the graveyard record of the building o ("gv_AllocGraveyardField", at +0x65 of o) */
extern const int gv_EntryTotals[];             /* 0x5ee064 */
extern const int gv_GraveTotals[];             /* 0x5ee074 */
extern int ai_NextObjectId;                /* 0x61a654 */



void * mem_Alloc(int size, char *tag);        /* 0x4223c0, allocates zeroed memory */
void mem_Free(void *p);                 /* 0x422620 */
GVYARD *gv_GrowGraveyard(struct AIBLD *o);  /* 0x4eff50 */
void gv_FreeGraveyard(int *g);             /* 0x4f0180 */
int gv_OrderBury(int *g, struct AIBLD *o, int v, int b);  /* 0x4f01d0 */
int gv_BuryCharacter(int *p);              /* 0x4f0240 */
int gv_OrderReserveGrave(struct AICHAR *c, struct AIBLD *o, int size, short years, int price);  /* 0x4f0430 */
int gv_ReserveGrave(GVORDER *m);          /* 0x4f0490 */
int gv_OrderExtendGrave(int *g, struct AIBLD *o, int v, int b, short s, int x);  /* 0x4f0700 */
int gv_ExtendGrave(GVORDER *m);           /* 0x4f0770 */
int gv_OrderSetGraveHolder(struct AICHAR *c, struct AIBLD *o, int size, int entry);  /* 0x4f0900 */
int gv_SetGraveHolder(GVORDER *m);         /* 0x4f0970 */
int gv_OrderOpenSize(struct AICHAR *c, struct AIBLD *o, int size);  /* 0x4f0a90 */
int gm_AddObjekt(int id, int proto, int n);                     /* 0x500970 */
int gv_OpenSize(GVORDER *m);           /* 0x4f0af0 */
int gv_OrderAdjustEntry(struct AIBLD *o, int v, int b, int x);  /* 0x4f0c20 */
int gv_AdjustEntry(GVORDER *m);          /* 0x4f0c80 */
int gv_OrderNewDead(struct AIBLD *o, int x);      /* 0x4f0d70 */
int gv_AddNewDead(unsigned char *p);    /* 0x4f0dd0 */
int gv_OrderMoveGrave(struct AICHAR *c, int to, struct AIBLD *o, int from, int entry, int price);  /* 0x4f0e80 */
int gv_MoveGrave(GVMOVE *m);           /* 0x4f0ed0 */
int gv_OrderRaiseDead(struct AIBLD *o, int size, int entry, int grave, int kind);  /* 0x4f1170 */
int gv_SendGrave(struct AIBLD *o);    /* 0x4f15e0 */
int gv_DecayRaisedDead(struct AICHAR *c);  /* 0x4f1660 */
int gv_RoomForRaised(struct AIBLD *o, int *n);  /* 0x4f1d50 */
float gv_PreserveRate(struct AIBLD *o);           /* 0x4f16f0 */
int cm_SendFloatDelta(int id, int field, float delta);  /* 0x4c4ac0 */
int gv_WriteGraveyard(void *f, struct AIBLD *o);  /* 0x4f17f0 */
struct AIOBJ *gm_Query(void *list, int n, ...);                   /* 0x4ffe90 */
unsigned gv_RaiseDead(GVRAISE *m);     /* 0x4f1200 */
int gv_ReadGraveyard(void *f, struct AIBLD *o);  /* 0x4f1aa0, reads the graveyard record of o from the file f (allocated by 0x4efc10) */
float util_RandomF(void);               /* 0x42ec20 */
extern int ai_CharCount;                /* 0x6f1bc0, the number of characters in use (of ai_Chars[0x300]) */
struct CHARACTER *gm_PlaceOnStage(int id, int a, int b, struct D3VECTOR *p, struct D3VECTOR *ori);                     /* 0x4fbd10 */
void gm_ChooseHeadIcon(struct AICHAR *c);                     /* 0x4fb890 */
GVENTRY *gv_FindWornEntry(struct AIBLD *bld, unsigned char m);  /* 0x4f22a0 */

int gv_FindHeldEntry(void *a, struct AIBLD **o, struct GVENTRY **e);  /* 0x4f2540 */
int gv_FindReservedEntry(void *a, struct AIBLD **o, struct GVENTRY **e);  /* 0x4f25d0 */
float gv_SeanceChance(struct AIBLD *o);           /* 0x4f2660 */
int gv_GetTableRecord(int i, AIDEC *out);     /* 0x4f2720 */
int gv_FindTableRecord(struct AICHAR *c, unsigned b, int *out);  /* 0x4f2870 */
extern AIDEC gv_Decisions[];           /* 0x611258, 0x1d AIDEC records of 0x24 bytes (the AI decision table) */

int gv_WriteCrimes(void *f);             /* 0x4f28d0 */
float gv_SchoolLevelFactor(unsigned short *c);          /* 0x4f2da0 */

int gv_ReadCrimes(struct VFSFILE *f);             /* 0x4f2b30 */
int gv_TableRecordText(char *out, int i);    /* 0x4f2fe0 */

int gv_FindCrimesByState(int state, int *out);    /* 0x4f3610 */
int gv_AddEvidence(int crime, int owner);        /* 0x4f3640 */
int gv_FreeCrimeSlot(void);                /* 0x4f36b0 */
int gv_FindCrime(int id);              /* 0x4f36e0 */
int gv_EvidenceSlot(int a, int b);        /* 0x4f3780 */

int gv_HandOverCrimes(int owner, int culprit, int state, int hand);  /* 0x4f3910 */
int gv_CountOwnedGraves(int c);               /* 0x4f39b0 */
int gv_CulpritGuilt(int c);               /* 0x4f39e0 */

int gv_HeldCrimesOf(int culprit, int *out, unsigned short t);  /* 0x4f3fe0 */
int gv_HeldCrimeIdsOf(int culprit, int *out, unsigned short t);  /* 0x4f4080 */
int gv_HeldCrimeCount(int culprit, unsigned short t);   /* 0x4f4130 */
void gv_ClearCrimes(void);               /* 0x4f4350 */
int gv_CheckSentence(struct AICHAR *c, unsigned k); /* 0x4f4420 */
struct AICHAR *gm_FindChar(int id);                   /* 0x505df0 */

void gv_CheckRankUps(void);               /* 0x4f4d10 */
int gv_EvidencePrice(int id, struct AICHAR *seller, int *price, short *culprit, unsigned *law);  /* 0x4f4d30 */
void gv_CheckRankUp(unsigned i);              /* 0x4f4970 */
int gm_CharLevel(unsigned short id, int again);                     /* 0x505e60 */

void gv_SendCrimes(void);               /* 0x4f3700 */
int gv_RetireCrime(int id, int m);       /* 0x4f37e0 */
void gv_SortCrimesByLaw(int n, CRIME *r);     /* 0x4f4390 */
struct AIJOB *he_FindEvent(int n, ...);         /* 0x53e400, as he.h */
extern unsigned short ai_PlayerId;     /* 0x6f25b8 */

int gv_RetireCrimesOf(int p, int n);        /* 0x4f3a30 */
int gv_RetireCrimeIds(int p, int n, int *ids);  /* 0x4f3b40 */

int gv_RankCulprits(int *ids, int *cnt, unsigned short t);/* 0x4f3c50 */

int gv_RankCulpritsAll(int *ids, int *open, int *total, unsigned short t);  /* 0x4f3dd0 */

extern const int gv_RankWorth[10];           /* 0x5ee0f8, the worth each rank needs */
extern unsigned char ai_NumPlayers;     /* 0x62489c, the number of players (as ai.h / cm.h / mission.c) */
int gm_GetWorth(unsigned short id);    /* 0x50a640 */
int cm_SendSetField(int a, int b, int c, int d, int e);                     /* 0x4c4a60 */
struct AIMSG; int cm_SendLongMessage(struct AIMSG *msg);                     /* 0x4c4b70 */
void cm_BeginFieldBlock(void *o, int id);                     /* 0x4c3ba0 */
int cm_AddFieldDelta(unsigned char size, unsigned char n, unsigned short field, void *v);                     /* 0x4c3c00 */
int cm_SendFieldDeltas(void);                     /* 0x4c49a0 */
struct AITIME;  /* f3gm.h typedef (gm_AddTime); file-scope so the gm_AddTime prototype below is stable */
void gm_AddTime(struct AITIME *c, int hours, int mins, int secs);                     /* 0x4fe140 */

int gv_CannonCost(struct AICHAR *o, int a, int b, int d, int *n, int *price);  /* 0x4ef090 */
int gv_MovePrice(struct AICHAR *c, int k1, int k2, int *out);  /* 0x4f2440 */
int gv_ProtectionPrice(struct AICHAR *c);  /* 0x4f24a0, returns gm_PlayerFactor's value (0x4f2532 ret after the 0x5085f0 call) */
int gv_CrimeTextLaw2to8(char *out, CRIME r, int mode);  /* 0x4f30a0 */
int gv_CrimeTextLaw9to16(char *out, CRIME r, int mode);  /* 0x4f31d0 */
int gv_CrimeTextLaw17to28(char *out, CRIME r, int mode);  /* 0x4f3270 */
int gv_CrimeText(char *out, CRIME r, int mode);  /* 0x4f3580 */
struct AICHAR *gv_FindAccused(struct AICHAR *c, int max, int *ids, int *cnt);  /* 0x4f41b0 */
void gv_PassSentence(struct AICHAR *c, int a, struct AICHAR *judge, struct AICHAR *assessor1, struct AICHAR *assessor2);  /* 0x4f4460 */
void gv_SentenceText(struct AICHAR *c, int a, char *out);  /* 0x4f48f0 */

unsigned ord_ApplyForOffice(struct AICHAR *c, ORDMSG *m);  /* 0x4f4e20 */
struct AIJOB *he_NextEvent(void);                   /* 0x53e300 */

int ord_LevelOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f4f20 */
int ord_ChangeProfessionOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f4ff0 */
int ord_PrivilegeDialog(char *text, int mode, int arg);  /* 0x4f8200, the privilege dialog */

int gv_SetTableRecord(struct AICHAR *c, int i, int v);  /* 0x4f2750 */
int gv_OnDecisionValue(GVDECMSG *p);              /* 0x4f27d0 */

int gv_Accuse(int i, int v, int a, int b, int obj);  /* 0x4f2e30 */
float util_RandomF(void);               /* 0x42ec20 */

void gv_GraveyardTurn(struct AIBLD *o);            /* 0x4f1de0 */
int gv_LeasePrice(struct AICHAR *c, unsigned char care, int kind, int flag, int *out);  /* 0x4f2330 */
int cm_SendRelations(int a, int b, int c, int d);                     /* 0x4c4b00 */
int gm_CharCurrency(struct AICHAR *c, signed char p);                   /* 0x509ee0 */

int ord_MedicusOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5070 */

int ord_AccusationOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f50f0 */

int ord_BlackmailBuildingOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5190 */
int ord_IntimidateOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f52e0 */
int ord_BlackmailContactOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5350 */
int ord_DismissOfficeOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5c30 */
int ord_LawOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5d50 */
int ord_LawOrder2(struct AICHAR *c, ORDMSG *m);     /* 0x4f5f00 */
int ord_Level3Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f5200 */
int ord_Level4Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f53c0 */
int ord_Level4Order2(struct AICHAR *c, ORDMSG *m);     /* 0x4f54a0 */
int ord_Level4To5Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f5580 */
int ord_Level5UpOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5660 */
int ord_Level5UpOrder2(struct AICHAR *c, ORDMSG *m);     /* 0x4f5730 */
int ord_Level6UpOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f58e0 */
int ord_Level6UpOrder2(struct AICHAR *c, ORDMSG *m);     /* 0x4f59b0 */

int ord_Job11Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f60b0 */
int ord_JobMultiOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f6180 */
int ord_Job28Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f6270 */
int ord_Job29Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f6340 */
int ord_Job34Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f6410 */
int ord_JobRangeOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f64e0 */
int ord_JobMultiOrder2(struct AICHAR *c, ORDMSG *m);     /* 0x4f65c0 */

int ord_BewitchOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f66b0 */

int ord_Job17Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f68d0 */
int ord_Job17Order2(struct AICHAR *c, ORDMSG *m);     /* 0x4f69a0 */
int ord_JobMultiOrder4(struct AICHAR *c, ORDMSG *m);     /* 0x4f6a70 */
int ord_Job10Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f6c60 */
int ord_Job15Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f6d30 */
int ord_CounterEspionageOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f67c0 */
int ord_MisappropriationOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f6b40 */

int ord_SeatSwapOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f6e00 */
int ord_HatredOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f6f10 */
int ord_HearingOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f70f0 */
int ord_ExpelWorkerOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7200 */
int ord_ConvertOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7300 */
int ord_PeaceOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7400 */
int ord_PenanceOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f74f0 */
int ord_SpyTargetFlagOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f75e0 */
int ord_JobMultiOrder3(struct AICHAR *c, ORDMSG *m);     /* 0x4f7000 */

int ord_MiracleOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f76e0 */
int ord_Level7Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f77d0 */
int ord_Level8Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f78b0 */
int ord_Level9UpOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7990 */
int ord_Flag800Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f7ca0 */
int ord_Flag800Order2(struct AICHAR *c, ORDMSG *m);     /* 0x4f7d70 */
int ord_Flag200Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f7ef0 */
int ord_Flag400Order(struct AICHAR *c, ORDMSG *m);     /* 0x4f8070 */
int ord_InterrogationOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7a60 */
int ord_DismissalOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f7b80 */
int ord_InterrogationOrder2(struct AICHAR *c, ORDMSG *m);     /* 0x4f7e40 */
int ord_InterrogationOrder3(struct AICHAR *c, ORDMSG *m);     /* 0x4f7fc0 */
int ord_DismissWorkerOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f8140 */

extern int (*ord_OrderHandlers[0x3a])(struct AICHAR *c, ORDMSG *m);    /* 0x611768, the order handler of each order number */
int d2_OpenForm(short x, short y, char *name);  /* 0x4741f0, d2.h: loads the view, returns its number */
void d2_CentreViewWindows(int view);                     /* 0x475600 */
int d2_SetForm(int view, int n);                       /* 0x475f70 */
void d2_CloseView(int view);                     /* 0x4758f0 */
void d2_SetPointerSprite(int a, int pic);            /* 0x476f80, d2.h / gfx.h */
int sv_RunFrame(void (*cb)(), unsigned mask);                     /* 0x5309a0 */
extern int sv_PopRequest;                /* 0x6f22a0 */
extern int d2_ClickedId;                /* 0xf8a668 */
int ord_DispatchOrder(int id, struct AICHAR *c, ORDMSG *m);  /* 0x4f81c0 */

int ord_DivorceOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5800 */
int ord_WageReportOrder(struct AICHAR *c, ORDMSG *m);     /* 0x4f5a80 */
int gm_CharacterWages(unsigned short id, int flag, unsigned char *out);  /* 0x4fa700, the wage record (ORDWAGES) of the character id for the report */


/* the tables 0x4f82a0 clears */
extern ORDMSGREC ord_MessageRecord;     /* 0x91b480, the record the messages carry */
extern int gm_IncomeHistory[5][17];       /* 0x91b580, the 17-round history of the five income sums (rows of
                                            0x44 bytes, the running sums behind them) */
extern ORDSTATROUND ord_StatisticsHistory[16]; /* 0x91ab00, the statistics of the last 16 rounds */
extern ORDSTATS ord_Statistics;         /* 0x91b4c0, the last statistics (ord_UpdateStatistics) */
extern float ai_RatingBase;              /* 0x6f1b9c, the running rating: it moves towards ai_Rating (ai.h, 0x6f1ba0) by ord_RatingRate */
extern float ord_RatingRate;             /* 0x91aaf4, the change rate of the rating (ord.c 0x4f8ed0; ls.c saves it) */
char d3_GetHeightAt(struct D3SM *h, struct D3VECTOR *pos, int *px, int *pz, float *py);                    /* 0x45f170 */
void ord_ResetStatistics(void);               /* 0x4f82a0 */
int ord_GetGridCell(struct D3VECTOR *p, int *x, int *y);  /* 0x4f8300, the grid cell (x, y) of the position p */

struct AIBLD *gm_BuildNext(void);                     /* 0x501030 */
int gm_FindById(struct AIBLD **bld, struct AIOBJ **obj, struct AICHAR **chr, int id);  /* 0x4fea50, fills *bld with the object of the id (ai.h's prototype) */
int gm_EquipmentValue(struct AIBLD *b, int level);                     /* 0x509b10 */
void ord_CountGridObjects(void);               /* 0x4f8360 */

char d3sm_GetVertex(struct D3SM *h, int x, int z, struct D3VECTOR *out);                              /* 0x45f100, d3_sm.c */
extern char ord_KindTable[];            /* 0x617468, 0x58 pairs of ints */
char ord_RandomCellPoint(int x, int y, struct D3VECTOR *out);  /* 0x4f86a0, ord.c */
int ord_GetKindRecord(int i, int *out);     /* 0x4f8890 */

void ord_AddGridAmount(int who, unsigned char kind, int *px, int *py);  /* 0x4f8460, kind: a law record (CRIME.law; the caller cm_ExAddCrime pushes the byte unwidened) */
void ord_SubGridAmount(int who, unsigned char kind);  /* 0x4f8590 */

int ord_RandomObjectId(struct AICHAR *c);             /* 0x4f8700 */

void ord_AppendStatisticsRound(void);               /* 0x4f88c0 */

extern CRIME ai_Crimes[0x200];  /* 0x91f700, 0x200 records of 0x2d bytes (to 0x925100) */
void ord_RebuildGridSums(void);               /* 0x4f8920 */

void ord_GetMessageRecord(int *out);           /* 0x4f9170 */
void ord_InitMessageRecord(int a, float b, float c, float d);  /* 0x4f9190 */

extern char ord_RatingBytes[];            /* 0x91b460, 5 + 1 bytes */
extern struct AIBLD *ai_Blds;     /* 0x889f74 */
void ord_ComputeStatistics(float *out);         /* 0x4f8ae0 */
void ord_UpdateStatistics(void);               /* 0x4f8ed0 */
void ord_LoadStatistics(void *p);       /* 0x4f9020 */
void ord_UpdateMessageEvent(void);               /* 0x4f9220 */
void ord_ReportStatistics(void);        /* 0x4f9850 */
int ord_HandleMessageRecord(int *m);              /* 0x4f9710 */
unsigned char ord_GetRatingByte(int i);              /* 0x4f97a0 */
float ord_BuildingCapacityRatio(void);              /* 0x4f97c0 */

float ord_StatisticsRating(int *rec);              /* 0x4f9ce0 */
float ord_WeightedRecordSum(int *out);          /* 0x4f9d40 */
struct ORDSTATS; float ord_GetStatistics(struct ORDSTATS *o);            /* 0x4f9e00 */

extern AITIME ord_StatisticsClock;      /* 0x91b470, the clock of the last rating step (ord_AdvanceRatingBase) */
void ord_AdvanceRatingBase(void);               /* 0x4f9c00 */

/* declared in other units' headers before (moved to the owner) */
extern struct AICHAR *ai_JudgeCatholic;  /* 0x6f1bfc */
extern struct AICHAR *ai_JudgeProtestant;  /* 0x6f1c00 */

#endif
