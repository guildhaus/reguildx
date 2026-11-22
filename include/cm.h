struct GVRAISE;
struct D3PARTSYS;
struct D3COLOR;
struct D3TERRAIN;
struct D3SM;
struct AMTAPP;
struct AMTMSG;
struct CHACTION;
struct CHARACTER;
struct GMSTOCK;
struct D3BGF;
struct D3TRAIN;
struct G15PLANT;
struct SBBANK;
struct SBSAMPLE;
struct AITIME;
struct D2FADE;
struct AMTREC;
struct D2SURF;
struct AMTKIND;
struct D3SKY;
struct D3SKYLAYER;
struct D3VECTOR;
struct D3OBJECT;
struct D3QNODE;
struct D3SURF;
/* Declarations of cm.c (0x4c3180..): the game messages sent to / received from the server (net.c): message
   sizes by type, the send ring, the receive list, split long messages (type 7), field blocks. Its .data block starts at
   0x60bd80 (0x302, 2, -1 globals, the handler table 0x60bd98). Names are ours. */
#ifndef CM_H
#define CM_H
#include "portable.h"                /* intptr_t: a text id or a string in one parameter */
struct AICHAR;
struct D3FLMAP;
typedef struct G18POP { float t; int v; int h; struct AICHAR *c; int kind; } G18POP;      /* 0x14 bytes, a floating number: its rise left (t), the value, the screen text, the character, the kind */
typedef struct CMPORTRAIT {             /* 0x20 bytes, a portrait box of a selected fighter (cm_Portraits, built by 0x4cfc10) */
    int portrait;                       /* 0x00, the portrait picture object (a click toggles D2OBJ.checked: the selection) */
    int frame;                          /* 0x04, the frame picture object (0x5da) */
    int win;                            /* 0x08, the box window, -1: the box is unused */
    int unused0c;                       /* 0x0c, set to -1 only */
    int text;                           /* 0x10, the name and health text */
    int weaponPic;                      /* 0x14, the weapon picture (goods picture id + 0xdf) */
    int countText;                      /* 0x18, the count left of the weapon item (kind 1 / 2) */
    struct AICHAR *c;                   /* 0x1c, the character */
} CMPORTRAIT;
typedef struct G18LOG { char text[0x40]; char name[0x24]; int to; int id; } G18LOG;      /* 0x6c bytes, a lobby chat line: the text, the sender's name, the receiver (0: everybody), the sender */

#include "d2_types.h"                /* D2OBJ (d2_Objs); outside the packed region below */
#pragma pack(push, 1)
#include "cm_types.h"                /* G17MSG, G17STAT, CRIME */
#include "rt_types.h"                /* RTPOINT */
#pragma pack(pop)

typedef char ai_AssertG17MSG[sizeof(G17MSG) == 0x99 ? 1 : -1];

typedef struct CMSPLITBUF {             /* the long message cm_SplitMsg (cm_SetLongMsg fills it, cm_QueueSplit sends
                                           it as parts of type 7): the whole length, then its bytes */
    unsigned short len;                 /* 0x00, cm_SplitMsgLen - 2 */
    unsigned char data[0x3fe];          /* 0x02 */
} CMSPLITBUF;

extern G17MSG cm_RecvPool[0x2000];     /* 0x9367e0, the free receive records */
extern int cm_NextNetStep;                /* 0xa687e4, d3_Time of the start */
extern CMSPLITBUF cm_SplitMsg;         /* 0xa68800, a long message to split (cm_SplitMsgLen bytes) */
extern G17MSG *cm_RecvFree;            /* 0xa68c00, the free list */
extern unsigned int cm_GroupEndSeq;       /* 0xa68c04 */
extern int cm_FieldBlockLen;                /* 0xa68c08, bytes used in cm_FieldBlock.buf */
extern G17FIELDS cm_FieldBlock;          /* 0xa68c20 */
extern G17FIELDS ai_NeedBlock;          /* 0xa68ca0 */
extern int ai_NeedBlockLen;                /* 0xa68d20, bytes used in ai_NeedBlock.buf */
extern G17MSG *cm_RecvQueue;            /* 0xa68d24, the received messages */
extern char *cm_FieldObject;              /* 0xa68d2c, the object of the field block (fields are offsets into it) */
extern int cm_SplitMsgLen;                /* 0xa68d30, length of cm_SplitMsg */
extern struct AICHAR *ai_NeedBlockChar;       /* 0xa68d34 */
extern unsigned char cm_LongMsg[];    /* 0xa68d40, a joined long message */
extern G17MSG cm_SendRing[0x8000];     /* 0xa69140, the send ring */
extern G17STAT cm_SendStates[0x8000];    /* 0xf31160 */
extern G17MSG *cm_SendQueue;            /* 0xf81160, the messages to send */
extern unsigned int cm_LongMsgLen;       /* 0xf81164, length of cm_LongMsg */
extern int cm_LastSeq;       /* 0xf81168, the last sequence number */
extern G17MSG cm_RecvMsg;             /* 0xf81180, the message being received */
extern unsigned int cm_GroupFirstSeq;       /* 0xf8121c */
extern unsigned int cm_SpeedLevel;               /* 0x60bd84, = 2 (0..4) */
extern int cm_LastCharId;                /* 0x60bd88, = -1 */
extern int cm_LastBuildingId;                /* 0x60bd8c, = -1 */
extern int cm_LastObjectId;                /* 0x60bd90, = -1 */
extern int cm_LeftPlayerId;                /* 0x60bd94, = -1 */
extern int (*cm_Handlers[0x6a])(G17MSG *m, G17STAT *s);  /* 0x60bd98, the handler of each message type */
extern int (*cm_Checks[0x6a])(G17MSG *m);             /* 0x60bf40, the check of each type (groups 5..6) */
extern unsigned int cm_LastRequCount;       /* 0xa68d1c, "cm_LastRequCount" */
extern int cm_LastSyncCount;               /* 0xa687e0, "cm_LastSyncCount" (net.h) */
extern int ai_GameOver;                /* 0x6f259c */
extern float ai_DifficultyValue;              /* 0x5fef04 */
extern float ai_DifficultyScale;              /* 0x5fef08 */
extern int cm_RecvCount;                /* 0x6f0cd0, received messages */
extern unsigned short ai_PlayerId;     /* 0x6f25b8, the player */
extern volatile unsigned long d3_Time;  /* 0x6333cc */
extern int ai_NextCrimeId;                /* 0x6f1b88 */
extern char cm_EventNames[][0x20];       /* 0x625820, names ("HE_NULL", ..) */
#include "ai_types.h"                /* AITIME */
#include "ai_bld.h"                  /* AIBLD */
extern AITIME ai_Time;                   /* 0x770ae0, the game clock */

#pragma pack(push, 1)
typedef struct G17B9 { char b[9]; } G17B9;
typedef struct G17B10 { char b[10]; } G17B10;
typedef struct G17B12 { char b[12]; } G17B12;
typedef struct G17B15 { char b[15]; } G17B15;
#pragma pack(pop)

int gm_FindById(struct AIBLD **bld, struct AIOBJ **obj, struct AICHAR **chr, int id);                             /* 0x4fea50, out: three object views */
void main_GameLoop(int ctl);                                                              /* 0x53bb20 */
struct AICHAR *gm_FindChar(int id);                                                      /* 0x505df0, ai.h: AICHAR * */
int gm_CompareTime(AITIME *a, AITIME *b);                                          /* 0x4fe210 */
struct AIBLD *gm_FindBuildingById(int id);                                                      /* 0x502020, ai.h: AIBLD * */
int gm_IsHomeType(struct AIBLD *bld);                                                     /* 0x502520 */
struct AIOBJ *gm_GetGebaeudeHauptraum(struct AIBLD *bld);                                                   /* 0x501ce0, ai.h: AIOBJ * */
struct AIOBJ *gm_Query(void *list, int n, ...);                                        /* 0x4ffe90, ai.h: AIOBJ * */
struct AICHAR; struct AIBLD; struct AICHAR *gm_FindApplicant(struct AIBLD *o, unsigned title, unsigned job);                             /* 0x4fda70 */
struct AIBLD; struct AIBLD *gm_FindHome(int unused, struct AIBLD *o);                                   /* 0x4fd820 */
struct GMSTOCK *gm_FindGoods(int p, unsigned id);                                   /* 0x4ffc40 */
extern G28REC *cm_CurrentFight;            /* 0x6f0d90, the scene party running (cm_ExecCutscene) */
int gm_SumSlotAmounts(void *list, unsigned char i);                                     /* 0x508660 */
int gm_FreeCapacity(struct AIOBJ *l, int item, int max);                                    /* 0x50ab80 */
struct AICHAR *gm_ObjectBuildingOwner(struct AIOBJ *o);                                                     /* 0x50a050 */
int gm_TakeableCount(struct AICHAR *p, int item, int max);                                    /* 0x50ad70 */
struct AIBLD *gm_BuildQuery(int n, ...);                                                  /* 0x501190, ai.h: AIBLD * */
int amt_CheckApplication(struct AMTAPP *m);                                                       /* 0x4e6360 */
int amt_CheckOfficeMessage(struct AMTMSG *m);                                                       /* 0x4e6710 */
extern signed char ai_Relations[0x300][0x300];  /* 0x7e5360, relations between the characters */
extern signed char ai_RelationMemory[0x300][0x300];  /* 0x889f80 */
extern int ai_NextEventId;                /* 0x6f2618 */
int he_IsMessageKindFiltered(int id);                                                        /* 0x575640 */
struct AIJOB *he_CreateEvent(struct AIMSG *msg);                                                   /* 0x53e040, AIMSG * */
struct AIJOB *he_FindEvent(int n, ...);                                                  /* 0x53e400, ai.h: AIJOB * */
extern int ai_NextObjectId;                /* 0x61a654 */
unsigned char * gm_CreateBuilding(unsigned char kind, unsigned short owner);                    /* 0x501580 */
struct AIBLD; unsigned short gm_CreateCharacter(int type, int a2, int a3, unsigned short a4, struct AIBLD *a5, unsigned a6, int a7, int a8); /* 0x507690 */
struct AIFIN; struct AIFIN *gm_PlayerRecord(struct AICHAR *ch);                                       /* 0x506430 */
unsigned gm_TakeOverCharacter(int a, int b);                                                  /* 0x5064d0 */
int gv_FindHeldEntry(void *a, struct AIBLD **o, struct GVENTRY **e);                                    /* 0x4f2540 */
struct GVYARD; struct GVENTRY; int gv_EntryIndex(struct GVYARD *g, struct GVENTRY *e);                                       /* 0x4ef6b0 */
int gv_OrderBury(int *g, struct AIBLD *o, int v, int b);                     /* 0x4f01d0 */
int gm_FreeBuilding(struct AIBLD *b);                                                       /* 0x5012e0 */
void gm_KillSpieler(int c, int mode);                                     /* 0x503c60 */
int gm_TakeObjekt(int id, int good, int n);                                       /* 0x500a40 */
int gm_AddObjekt(int id, int proto, int n);                                       /* 0x500970, hmt.h: void * n */
int gm_AddNegative(int id, int good, int n);                                       /* 0x500ae0 */
extern struct AIGOOD *ai_Goods;         /* 0x91aaf0, the goods (0x41 bytes each, the kind at 0) */
extern unsigned char ai_OwnPlayer;      /* 0x6f1bc5 */
int gm_ListAmount(struct AIOBJ *l, struct AIOBJ *o);                                              /* 0x50aaf0 */
int gm_ListStock(struct AIOBJ *l, int item);                                             /* 0x50ab50 */
int gm_RemoveObject(struct AIOBJ **list, unsigned item);                                          /* 0x4ffff0 */
int gm_RemoveObjectFromBuilding(struct AIBLD *b, int id);                                            /* 0x503480 */
unsigned short * gm_AllocRaum(struct AIBLD *b, unsigned n);                                           /* 0x5031b0 */
/* 0x500190 */
void txt_Format(char *buf, intptr_t id, ...);                                       /* 0x5176d0 */
struct SBSAMPLE *sb_PlaySample(struct SBBANK *bank, char *name, int loops, int pan, int volume, int fade, int delay); /* 0x426fa0, sblib.c */
float gm_ItemPrice(int item, unsigned char n);                                   /* 0x5087f0 */
struct AIBLD *gm_ObjectBuilding(struct AIOBJ *o);                                                     /* 0x50a0f0 */
void util_Seed(unsigned int seed);                                               /* 0x42ec90, tr.c */
extern int cm_NetFlags;                /* 0x6f2594, flags */
extern unsigned cm_LoadSize;           /* 0xa68d28, size of the load buffer */
extern char *cm_LoadBuf;              /* 0xf31140, the load buffer ("cm_LoadBuf") */
extern unsigned cm_LoadReceived;           /* 0xf81220, bytes in it */
extern struct AICHAR *ai_PlayerChar;    /* 0x6f1bf8, the player's character */

int cm_MessageSize(G17MSG *m);                                                     /* 0x4c3180 */
void ai_InitStates(void);                                                         /* 0x4c3480 */
void ai_ResetMessages(void);                                                         /* 0x4c3560 */
void cm_SendHello(void);                                                         /* 0x4c3600 */
int cm_WaitHello(void);                                                          /* 0x4c3630 */
int cm_FlushSendQueue(void);                                                          /* 0x4c3680 */
int cm_QueueSplit(void);                                                          /* 0x4c3720 */
int cm_SplitComplete(G17MSG *m);                                                     /* 0x4c3850 */
unsigned int cm_JoinSplit(G17MSG *m);                                            /* 0x4c38e0 */
int cm_QueueSend(G17MSG *src);                                                   /* 0x4c39c0 */
int cm_GetSlotState(int h);                                                         /* 0x4c3ae0 */
void *cm_GetSlotValue(int h);                                                       /* 0x4c3b10 */
void cm_BeginSendGroup(void);                                                         /* 0x4c3b30 */
void cm_EndSendGroup(void);                                                         /* 0x4c3b40 */
int cm_SendGroupState(void);                                                          /* 0x4c3b50 */
void cm_BeginFieldBlock(void *o, int id);                                              /* 0x4c3ba0 */
int cm_AddFieldDelta(unsigned char size, unsigned char n, unsigned short field, void *v); /* 0x4c3c00 */
int cm_AddFieldValues(unsigned char size, unsigned char n, unsigned short field, void *v); /* 0x4c3d00 */
int cm_AddFieldValue(unsigned char size, unsigned char n, unsigned short field, void *v); /* 0x4c3d90 */
void ai_BeginNeedBlock(struct AICHAR *p);                                             /* 0x4c3e70 */
int ai_AddNeedDelta(int k, float v);                                        /* 0x4c3eb0 */
void cm_SetSpeedLevel(unsigned int v);                                               /* 0x4c3ef0 */
void cm_RaiseSpeedLevel(void);                                                         /* 0x4c3f20 */
void cm_LowerSpeedLevel(void);                                                         /* 0x4c3f50 */
unsigned int cm_GetSpeedLevel(void);                                                      /* 0x4c3f80 */
int cm_SendPlayerId(void);                                                         /* 0x4c3f90 */
int cm_ReceiveMessages(void);                                                          /* 0x4c3fd0 */
G17MSG *cm_WaitMessage(unsigned char type, int timeout);                                    /* 0x4c4030 */
int cm_EnqueueReceived(G17MSG *src);                                                   /* 0x4c4080 */
void cm_FreeReceived(G17MSG *m);                                                    /* 0x4c4130 */
int cm_ExecCommands(void);                                                          /* 0x4c4190, "cm_ExecCommand" */
int cm_CheckGroup(G17MSG *grp);                                                   /* 0x4c43c0 */
int cm_ResolveId(int a, int id);                                                 /* 0x4c4450 */
int cm_SetLongMsg(unsigned short len, void *p);                                   /* 0x4c4480 */
void cm_SendLoadSize(int v);                                                        /* 0x4c44d0 */
int cm_SendLoadBlock(void *p);                                                      /* 0x4c4500 */
void cm_BeginGroup(const char *s);                                                /* 0x4c4540 */
int cm_EndGroup(const char *s);                                                /* 0x4c4580 */
int cm_SendMessage10(unsigned char n, int b, void *p, short d);                      /* 0x4c45c0 */
int cm_SendCreateCharacter(unsigned char a, int b, int c, unsigned short d, int e, unsigned char f, unsigned char g, unsigned char h); /* 0x4c4650 */
int cm_SendMessage0c(int a, int b, short c, unsigned char d, int e, unsigned char f, unsigned char g, const char *s1, const char *s2); /* 0x4c46d0 */
void cm_SendTakeOverCharacter(int a, int b);                                                 /* 0x4c4770 */
void cm_SendDeleteObject(int id);                                                      /* 0x4c47b0 */
int cm_SendMoveGoods(int a, int b, unsigned char c, int d);                         /* 0x4c47e0 */
int cm_SendMoveGoodsUnchecked(int a, int b, unsigned char c, int d);                         /* 0x4c4830 */
int cm_SendExSellObject(int a, int b, int c, int d, unsigned char e, int f);         /* 0x4c4880 */
int cm_SendMakeGoods(int a, int b, int c);                                          /* 0x4c48e0 */
int cm_SendCartRoute(int a, int b, int c);                                           /* 0x4c4920 */
void cm_SendRemoveGoods(int a, int b);                                                 /* 0x4c4960 */
int cm_SendFieldDeltas(void);                                                         /* 0x4c49a0 */
int cm_SendFieldValues(void);                                                          /* 0x4c49e0, returns the cm slot of the send */
void ai_SendNeedBlock(void);                                                         /* 0x4c4a20 */
int cm_SendSetField(int a, int b, int c, int d, int e);                            /* 0x4c4a60 */
int cm_SendFloatDelta(int id, int field, float delta);                                          /* 0x4c4ac0 */
int cm_SendRelations(int a, int b, int c, int d);                                   /* 0x4c4b00 */
struct AIMSG; int cm_SendLongMessage(struct AIMSG *msg);                                                    /* 0x4c4b70, AIMSG (am.h, 0xf8 bytes) */
int cm_SendLongMessageText(struct AIMSG *msg, unsigned int len, void *extra);                      /* 0x4c4bc0 */
int cm_SendExSetHE(int k, struct AIJOB *p);                                     /* 0x4c4c60 */
int cm_SendTime(AITIME *t);                                                       /* 0x4c4d40 */
int cm_SendExSysMessage(unsigned char id, void *msg);                               /* 0x4c4db0 */
void cm_SendKillCharacter(int a, int b);                                                 /* 0x4c4e00 */
int cm_SendCrime(void *p);                                                       /* 0x4c4e40 */
int cm_SendRetireCrime(int a, int b);                                                  /* 0x4c4e90 */
void cm_SendProofExecuted(int a, int b);                                                 /* 0x4c4ed0 */
void cm_SendDropEvidence(int id, int netId, int value);                                 /* 0x4c4f10 */
int cm_RequestSendCutInfo(int playerId, int fightId);                                     /* 0x4c4f50, its send slot (cm_GetSlotState) */
int cm_SendNewParty(void *p);                                                      /* 0x4c4fa0 */
int cm_SendLeaveParty(int partyId, int member);                                        /* 0x4c4fd0, its send slot (cm_GetSlotState) */
int cm_SendMoveObject(int holder, int objId, int entry);                               /* 0x4c5010 */
int cm_SetPlant(int bldId, unsigned char x, unsigned char z, int type, unsigned char fall, int fallId); /* 0x4c5050, the send slot */
int cm_SendObject1b5(int owner, G17B7 value);                                        /* 0x4c50b0 */
void cm_SendChrWalkTo(int a, int b, int c, int d);                                   /* 0x4c5100 */
void cm_RequestChrMove(int a, int b, int c, const char *s);                           /* 0x4c5150 */
void cm_RequestChrMoveToUniverse(int a, int b, int c, const char *s);                           /* 0x4c51b0, "cm_RequestChrMoveToUniverse" */
void cm_SendChrStop(int a);                                                        /* 0x4c5230 */
void cm_SendCartState(int a, int b);                                                 /* 0x4c5260 */
int cm_SendPlaceOnStage(int a, int b, int c);                                           /* 0x4c52a0 */
int cm_SendChrGotoBuilding(int id, int bld, int c, const char *s, int f, const char *s2);  /* 0x4c52e0 */
void cm_SendChrAnim(int a, const char *s, int c);                        /* 0x4c5410 */
void cm_SendChrUseGates(int a, int b, int c);                                          /* 0x4c5460 */
int cm_SendOwnership(int a, int b, int c);                                          /* 0x4c54a0 */
void cm_SendUpgradeDone(int a);                                                        /* 0x4c54e0 */
void cm_SendBuildingDestroyed(int a);                                                        /* 0x4c5510 */
void cm_SendBoss(int a, int b);                                                 /* 0x4c5540 */
int cm_SendHandOverCrimes(int a, int b, int c, int d);                                   /* 0x4c5580 */
int cm_SendMessage3d(struct AIBLD *p, unsigned char b, int c, int d);                        /* 0x4c55d0 */
void cm_SendCharModel(int a, const char *s);                                         /* 0x4c5690 */
void cm_SendGoodsRecord(void *p, unsigned char k);                                     /* 0x4c56d0 */
void cm_SendGoodsDelta(struct GMSTOCK *p, unsigned char k);                                     /* 0x4c5710 */
void cm_SendMessage41(void *p);                                                      /* 0x4c5800 */
void cm_SendUpdateSmoke(int a);                                                        /* 0x4c5840 */
void cm_SendSkillsChanged(int a);                                                        /* 0x4c5870 */
int cm_SendApplication(AMTAPP *p);                                                     /* 0x4c58a0 */
int cm_SendOfficeRecord(AMTMSG *p);                                                    /* 0x4c58e0 */
int cm_SendDecisionValue(GVDECMSG *p);                                                   /* 0x4c5930 */
void cm_SendCharClear(int a, int b, int c);                                          /* 0x4c5970 */
void cm_SendSetJob(int id, int job);                                       /* 0x4c59b0 */
int cm_SendSpawnCharacter(unsigned char a, int b, int c, unsigned char d, unsigned char e, int f, const char *s); /* 0x4c59f0 */
void cm_SendFreeObject(int a);                                                        /* 0x4c5a70 */
void cm_SendChat(void *p);                                                      /* 0x4c5aa0 */
int cm_RequestCreateGeb(int owner, int kind, D3VECTOR4 *pos, int *rot);                /* 0x4c5ae0, "cm_RequestCreateGeb" */
void cm_SendCharHalt(int a);                                                        /* 0x4c5b90 */
int cm_SendObjCell(const char *s, int a, int b, const char *s2);                  /* 0x4c5bc0 */
int cm_SendCutEntry(int a, struct CMCUTENTRY *p);                                               /* 0x4c5c40 */
int cm_SendCutEntryUpdate(int a, struct CMCUTENTRY *p);                                               /* 0x4c5ca0 */
void cm_SendDamage(int a, int b, int c);                                          /* 0x4c5d00 */
void cm_SendScriptMessage(void *p);                                                      /* 0x4c5d40 */
int cm_SendTableRequest(G17TABLEMSG *p);                                               /* 0x4c5d80 */
int cm_SendFightCommand(struct AICHAR *c, int cmd, CMFIGHTSLOT *f);                             /* 0x4c5dc0 */
void cm_SendMessage56(void *p);                                                      /* 0x4c5e80 */
void cm_SendChrDelete(int a);                                                        /* 0x4c5ec0 */
void cm_SendCancelParty(int a);                                                        /* 0x4c5ef0 */
int cm_SendCutsceneReady(void *p);                                                       /* 0x4c5f20, its send slot (cm_GetSlotState) */
void cm_SendMoneyDelta(int a, int b);                                                 /* 0x4c5f60 */
void cm_SendMessage5b(int a, int b, int c);                                          /* 0x4c5fa0 */
int cm_SendTradeMessage(AMTTRADE *p);                                                   /* 0x4c5fe0 */
void cm_SendAddSkill(int a, int b, int c);                                          /* 0x4c6020 */
void cm_SendSpyReport(AIBLD *o, HESPYREPORT *p);                                     /* 0x4c6060 */
int cm_SendGraveOrder(void *p);                                                      /* 0x4c60b0 */
int cm_SendGraveMove(void *p);                                                       /* 0x4c60f0 */
int cm_SendRaiseDead(void *p);                                                      /* 0x4c6130 */
int cm_SendCreateAlchemist(void *p);                                                      /* 0x4c6170 */
int cm_SendCommand(void *p);                                                      /* 0x4c61b0 */
int cm_SendMasterChange(G28REC *p, struct AICHAR *q);                                    /* 0x4c61f0, returns the message's send slot */
int cm_SendEffectLoad(int *p);                                                       /* 0x4c6230 */
int cm_SendShots(void *p);                                                      /* 0x4c6260 */
void cm_SendSetRoute(AIOBJ *o, RTPOINT *pts);                                        /* 0x4c62a0, rt.c's route points */
void cm_SendClearRoute(AIOBJ *o);                                                    /* 0x4c6320 */
int cm_CheckMoveGoods(G17MSG *m);                                                     /* 0x4c6350, check of 0xf */
int cm_CheckSellObject(G17MSG *m);                                                     /* 0x4c63e0, check of 0x11 */
int cm_CheckFieldDeltas(G17MSG *m);                                                     /* 0x4c65b0, check of 0x16 */
int cm_CheckSetField(G17MSG *m);                                                     /* 0x4c66c0, check of 0x19 */
int cm_CheckOwnership(G17MSG *m);                                                     /* 0x4c6750, check of 0x38 */
int cm_CheckApplication(G17MSG *m);                                                     /* 0x4c6780, check of 0x44 */
int cm_CheckOfficeMessage(G17MSG *m);                                                     /* 0x4c67a0, check of 0x45 */
int cm_CheckDarkCorner(G17MSG *m);                                                     /* 0x4c67c0, check of 0x53 */
int cm_CheckTableRequest(G17MSG *m);                                                     /* 0x4c6870, check of 0x54 */
int cm_CheckCutsceneReady(G17MSG *m);                                                     /* 0x4c69c0, check of 0x59 */
int cm_ExNothing(G17MSG *m, G17STAT *s);                                         /* 0x4c6a20, handler of 0, 3, 5..7 */
int cm_ExGroupPassed(G17MSG *m, G17STAT *s);                                         /* 0x4c6a50, handler of 1 */
int cm_ExNetFlags(G17MSG *m, G17STAT *s);                                         /* 0x4c6a60, handler of 4 */
int cm_ExLoadSize(G17MSG *m, G17STAT *s);                                         /* 0x4c6a90, handler of 8: starts a load buffer */
int cm_ExLoadBlock(G17MSG *m, G17STAT *s);                                         /* 0x4c6ad0, handler of 9: appends to it */
int cm_ExCreateBuilding(G17MSG *m, G17STAT *s);                                         /* 0x4c6b20, handler of 10 */
int cm_ExCreateCharacter(G17MSG *m, G17STAT *s);                                         /* 0x4c6bf0, handler of 0xb */
int cm_ExCreateNamedCharacter(G17MSG *m, G17STAT *s);                                         /* 0x4c6cd0, handler of 0xc */
int cm_ExTakeOverCharacter(G17MSG *m, G17STAT *s);                                         /* 0x4c6e10, handler of 0xd */
int cm_ExDeleteObject(G17MSG *m, G17STAT *s);                                         /* 0x4c6ec0, handler of 0xe */
int cm_ExMoveGoods(G17MSG *m, G17STAT *s);                                         /* 0x4c6f60, handler of 0xf */
int cm_ExMoveGoodsUnchecked(G17MSG *m, G17STAT *s);                                         /* 0x4c7010, handler of 0x10 */
int cm_ExSellObjekt(G17MSG *m, G17STAT *s);                                         /* 0x4c70b0, handler of 0x11, "cm_ExSellObjekt" */
int cm_ExMakeGoods(G17MSG *m, G17STAT *s);                                         /* 0x4c78c0, handler of 0x12 */
int cm_ExMoveObject(G17MSG *m, G17STAT *s);                                         /* 0x4c7c30, handler of 0x13 */
int cm_ExRemoveGoods(G17MSG *m, G17STAT *s);                                         /* 0x4c7d80, handler of 0x14 */
int cm_ExCreateObject(G17MSG *m, G17STAT *s);                                         /* 0x4c7e20, handler of 0x15 */
int cm_ExFieldDeltas(G17MSG *m, G17STAT *s);                                         /* 0x4c7e90, handler of 0x16 */
int cm_ExFieldValues(G17MSG *m, G17STAT *s);                                         /* 0x4c7f70, handler of 0x17: writes the field block's values to the object */
int cm_ExMoodDeltas(G17MSG *m, G17STAT *s);                                         /* 0x4c8050, handler of 0x18: adds deltas to a character's mood values */
int cm_ExSetField(G17MSG *m, G17STAT *s);                                         /* 0x4c8110, handler of 0x19: clears and sets bits of one field of an object */
int cm_ExFloatDelta(G17MSG *m, G17STAT *s);                                         /* 0x4c81d0, handler of 0x1a: adds a delta to a float field of an object */
int cm_ExRelations(G17MSG *m, G17STAT *s);                                         /* 0x4c8240, handler of 0x1b: changes the relations between two characters */
int cm_ExLongMessage(G17MSG *m, G17STAT *s);                                         /* 0x4c85c0, handler of 0x1c: creates the event of a long message and its texts */
int cm_ExSetHE(G17MSG *m, G17STAT *s);                                         /* 0x4c87a0, handler of 0x1d: sets an event's times, stage and argument block */
struct RTPOINT;
int rt_PointCount(struct RTPOINT *p);                                             /* 0x4bdaa0, rt.h */


extern int ai_NetPlayer;  /* 0x1460af4 */
void ai_UpdateNeeds(void);  /* 0x47da80 */
void ai_UpdateCharacters(void);  /* 0x47e560 */
void ai_RunMasterEvaluation(struct AICHAR *c);  /* 0x47e990 */
void ai_SetFirstMission(int owner, int type);  /* 0x4b3bd0 */
struct G28REC *cm_PartyById(int id);  /* 0x4e50a0, the used party with the id: its record, 0 without */
extern G28REC cm_Parties[96];  /* 0x925520, the scene party records (cm.c) */
struct G28REC *cm_AllocParty(void *src);  /* 0x4e5150 */
int cm_AddPartyMember(int id, int who);  /* 0x4e51b0 */
int cm_RemovePartyMember(int id, int who);  /* 0x4e5210 */
void ord_AddGridAmount(int who, unsigned char kind, int *px, int *py);  /* 0x4f8460, gv.h (ord.c) */
void ord_AdvanceRatingBase(void);  /* 0x4f9c00, ord.c */
void gm_CountCharacters(void);  /* 0x4fdfd0 */
struct AIJOB *he_NextEvent(void);  /* 0x53e300 */
void ai_NotifyPlayerOfChar(struct AICHAR *cRec, struct AICHAR *pRec);  /* 0x5a9170 */
void lc_UpdateGoodsReserves(void);  /* 0x5ba750 */
void ai_ApplyOptions(void);  /* 0x5d5e90 */
extern const int cm_SpeedTicks[];  /* 0x5edc10 */
extern int cm_SpeedTick;  /* 0x60bd80 */
extern int ai_NextPartyId;  /* 0x61a658 */
extern int cm_RunCharacters;  /* 0x624570, 1: a later server time also updates the characters (cm_ExTime) */
extern int cm_RunRating;  /* 0x624574, 1: a later server time also advances the rating base */
extern int cm_RunEvents;  /* 0x624578, 1: a later server time also runs the event handlers */
extern signed char ai_MissionMode;  /* 0x624580 */
extern unsigned char ai_NumPlayers;  /* 0x62489c */
extern int ai_MissionPartner;  /* 0x6248a0, the netId of the other player in a network mission (-1 none; set by message 8, cleared by 10) */
extern struct D3SCENE *ch_Saved0;  /* 0x631084 */
extern void *d3_Terrain;  /* 0x633738, d3_fl.c: the current terrain map */
extern int ai_TradeMsgCount;  /* 0x6f046c */
extern int cm_NoticeCount;  /* 0x6f0cd4 */
extern int ai_GameFlags;  /* 0x6f23f8 */
extern int cm_RequestedSaveSlot;  /* 0x6f25c8 */
extern char cm_RequestedSaveName[];  /* 0x6f25d0 */
extern unsigned int ai_MissionSeed;  /* 0x75e120, the random seed of the missions (as mission.h) */
extern AITIME ai_TimeCopy;  /* 0x75e130, the clock copy */
extern int cm_SaveAcks[][2];  /* 0x76fa20 */
extern int ai_Evidence[0x800][2];  /* 0x91b6e0, pairs (character netId, crime id): the character holds evidence of the crime (0x4f3640) */
extern CRIME ai_Crimes[0x200];  /* 0x91f700, the crime records */
extern CMCUTINFO cm_CutInfos[16];  /* 0x92cae0, the cutscene (fight) records */
extern int cm_DayEndRequest;  /* 0xf31144 */
extern int hst_SeedPending;  /* 0xf83650 */
struct D3SM; struct D3TERRAIN; void d3sm_Build(struct D3SM *h, struct D3TERRAIN *t);  /* 0x45e620, d3_sm.c: void d3sm_Build(D3SM *, D3TERRAIN *) */
void hmt_SetPendingElection(int v);  /* 0x4ad1b0 */

struct CHACTION * ch_AddAction(struct CHARACTER *ch, unsigned int type, ...);  /* 0x40b2f0, ch.h ch_AddAction */
struct G15TREE * veg_FindType(int type);  /* 0x4bc5a0 */
int veg_Fits(struct G15PLANT *p, int x, int z, int size);  /* 0x4bc710 */
void gm_SelectModelVariant(struct AICHAR *o);  /* 0x4fb5a0, f3gm.c: the model variant of the object o */
struct CHARACTER *gm_PlaceOnStage(int id, int a, int b, int *p4, int *p5);  /* 0x4fbd10 */
struct AIOBJ *gm_FindObjectInst(int id);  /* 0x4fe980 */
int gm_RemoveOwned(struct AIOBJ **list, int id);  /* 0x5000c0, f3gm.h */
extern int veg_NextId;  /* 0x6f0748 */
extern AIBTYPE *ai_BTypes;  /* 0x7e3f30 */
#ifndef DATA_VIEWS_H
extern char init_SceneDirty[];  /* 0xfd7f75 */
#endif


char d3_SetLightKeyCB(struct D3OBJECT *obj, float *time);  /* 0x449da0 */
struct GVYARD *gv_GrowGraveyard(struct AIBLD *o);  /* 0x4eff50 */
void gm_RefreshGoodsLists(unsigned p);  /* 0x4ff190 */
void gm_AssignBuilding(struct AIBLD *b, unsigned master, unsigned own);  /* 0x502b60 */
void ai_DropObjectAt(struct D3OBJECT *obj, struct D3VECTOR *target);  /* 0x58feb0 */
extern const struct D3VECTOR4 d3_ZAxis;  /* 0x5ebb74, (0, 0, 1), d3_vec.c */
extern struct VFSDIR *vfs_Root;  /* 0x6333fc */
extern char ai_DataPath[];  /* 0x75dca0 */

void ai_ResetJob(struct AICHAR *c);  /* 0x47e940 */
void gm_MoveIntoHome(struct AICHAR *c, struct AIBLD *b);  /* 0x4fda10 */
struct AIOBJ *gm_HomeObject(struct AIBLD *b);  /* 0x4fdc10 */
short *gm_SpawnCharacter(unsigned char flags, int p2, int p3, unsigned char p4, unsigned char p5, struct AIBLD *p6);  /* 0x4fddb0 */
struct AIOBJ *gm_QueryNext(void);  /* 0x4ffcc0 */
struct AIOBJ *gm_BuildingMainObject(struct AIBLD *b);  /* 0x501b50 */
void gm_FreeObject(struct AIOBJ *obj);  /* 0x5034b0 */
extern struct AIBLD *sv_SelectedObject;  /* 0x75ec60 */
typedef struct G17B16 { char b[16]; } G17B16;

void ord_LoadStatistics(void *p);  /* 0x4f9020 */
void gm_ChooseHeadIcon(struct AICHAR *c);  /* 0x4fb890 */
void gm_SetJob(int i, unsigned n);  /* 0x504790 */
extern char ch_EmptyName[];  /* 0x631090, "" (ch.h) */

extern char cm_ChatLog[];  /* 0x75fba0 */

void cm_PlaceFighter(struct AICHAR *c, struct D3VECTOR *pos, struct D3VECTOR *rot, int v);                              /* 0x4cc720 */
void ai_ShowPurchaseNews(struct AICHAR *buyer, struct AICHAR *ownerRec, struct AIBLD *bld, int value);  /* 0x5a8c50 */

void cm_FighterAct(CMFIGHTSLOT *f);  /* 0x4d6ba0, the action of one fighter (message 0x55) */
void cm_FightSlotStop(CMFIGHTSLOT *f);  /* 0x4d6f60 */
void cm_FightSlotCheer(CMFIGHTSLOT *f);  /* 0x4d6f90 */
void cm_FightSlotPickUp(CMFIGHTSLOT *f);  /* 0x4d7000 */
void cm_FightSlotPutDown(CMFIGHTSLOT *f);  /* 0x4d70a0 */
void cm_FightSlotWinner(CMFIGHTSLOT *f);  /* 0x4d7150 */
int cm_Attack(CMCUTINFO *rec, struct AICHAR *c, struct AICHAR *g);  /* 0x4d7360 */
int ai_InventoryHas(void *ch, int id);  /* 0x5ba6b0 */
void cm_PlantEscapeFlag(CMFIGHTSLOT *f);  /* 0x4d7190 */
void cm_ClearParty(int id);  /* 0x4e5180 */
void ai_GameFrame(void);  /* 0x591520 */

unsigned gv_RaiseDead(struct GVRAISE *m);  /* 0x4f1200 */

void rt_FreePoints(RTPOINT *p);  /* 0x4bd9e0, rt.h */
RTPOINT *rt_CopyPoints(RTPOINT *p);  /* 0x4bda00, rt.h */

char *cm_LobbyRecord(int id);  /* 0x4cd380 */
void cm_LobbyAddChat(int id, int to, char *text);  /* 0x4cd3c0 */
G18LOG *cm_LobbyChatFirst(void);  /* 0x4cd480 */
G18LOG *cm_LobbyChatNextLine(void);  /* 0x4cd4c0 */
void cm_LobbyClearChat(void);  /* 0x4cd500 */
int cm_LobbyAllReady(void);  /* 0x4cd510 */
void cm_LobbyStart(int lobbyId, int value);  /* 0x4cd580, opens the lobby from the hello answer */
unsigned int *cm_LobbyPlayerList(void);  /* 0x4cd5d0 */
CMLOBBYPLAYER *cm_LobbyFindPlayer(int id);  /* 0x4cd5e0, the lobby record of the player id, else a free one; 0 for id 0 */
CMLOBBYPLAYER *cm_LobbyMyPlayer(void);  /* 0x4cd5f0 */
int *cm_LobbyState(void);  /* 0x4cd600 */
int cm_LobbyRequestList(void);  /* 0x4cd610 */
int cm_LobbySetReady(int v);  /* 0x4cd650 */
int cm_LobbyLeave(void);  /* 0x4cd6a0 */
int cm_LobbySendChat(int to, char *text);  /* 0x4cd6e0 */
int cm_LobbyJoin(CMLOBBYPLAYER *p);  /* 0x4cd760 */
int cm_LobbyUpdatePlayer(CMLOBBYPLAYER *p);  /* 0x4cd7c0 */
int cm_LobbyRequestPlayer(int id);  /* 0x4cd820 */
int cm_ExLobby(G17MSG *m, G17STAT *s);  /* 0x4cd870 */
AIWEAPON *ai_FindWeaponRecord(int id);  /* 0x4cd9d0 */
AIWEAPON *cm_CharWeaponAny(struct AICHAR *c);  /* 0x4cda00 */
AIWEAPON *cm_CharWeapon(struct AICHAR *c);  /* 0x4cda50 */
struct AIOBJ *cm_CharWeaponItem(struct AICHAR *c);  /* 0x4cdac0 */
void cm_DiscardWeapons(struct AICHAR *c);  /* 0x4cdb20 */
char cm_FightWeaponLoss(struct AICHAR *c);  /* 0x4cdb80 */
float cm_FightStrength(struct AICHAR *c);  /* 0x4cdcf0 */
void cm_UpdateHandObject(struct AICHAR *c);  /* 0x4cde20 */
struct CMCUTINFO; struct CMCUTENTRY; struct CMCUTENTRY *cm_CutEntrySlot(struct CMCUTINFO *rec, struct AICHAR *c);  /* 0x4cdf00 */
struct CMCUTENTRY *cm_FightCutEntry(struct AICHAR *c);  /* 0x4cdf80 */
int cm_CellUsable(int x, int y);  /* 0x4cdfe0 */
int cm_FindNearCell(int a, int b, int *ox, int *oy);  /* 0x4ce040 */
struct AICHAR *cm_FindFighter(int id);  /* 0x4ce130 */
int ai_LedSelectBits(int idx, struct AICHAR *c);  /* 0x4ce170 */
float cm_CharObjDistXZ(struct AICHAR *c, char *o);  /* 0x4ce1b0 */
float cm_CharCellDistXZ(struct AICHAR *c, int x, int y);  /* 0x4ce200 */
int cm_OtherBuilding(struct AICHAR *a, struct AICHAR *b);  /* 0x4ce270 */
struct CMBOMB *cm_LayBomb(struct D3VECTOR *p);  /* 0x4ce290 */
char d3sm_GetVertex(struct D3SM *h, int x, int z, struct D3VECTOR *out);                              /* 0x45f100, d3_sm.c */
float gm_HealthRatio(struct AICHAR *c);  /* 0x4fc8e0, f3gm.h */
float gm_GetSkill(struct AICHAR *c, int skill);  /* 0x504ec0 */
int he_ShowNews(int pid, int fl, char *text, int unused, int ev, char *text2);  /* 0x53dda0 */
extern AIWEAPON ai_WeaponRecords[10];  /* 0x60c7c0 */
extern int cm_LobbyChatCount;  /* 0x6f0cd8 */
extern int cm_LobbyChatPos;  /* 0x6f0cdc */
extern G28REC *cm_FightRecord;  /* 0x6f0d04, the fight being run */
extern int gm_AllowAll;  /* 0x6f2448 */
extern G18LOG cm_LobbyChat[15];  /* 0x935da0 */
extern int cm_LobbyChatNext;  /* 0x9363f4 */
typedef struct CMLOBBYSTATE {
    int open;       /* 0x00, the lobby is open (cm_LobbyStart) */
    int changed;    /* 0x04, a lobby message came in (cm_ExLobby) */
    int closed;     /* 0x08, the lobby was closed (message 0x5f kind 3) */
    int unread[2];  /* 0x0c, no surviving code reads them */
} CMLOBBYSTATE;
extern CMLOBBYSTATE cm_LobbyStateFlags;  /* 0x936400 */
extern unsigned int cm_LobbyList[];  /* 0x936420, the count then the eight player states (0x24 bytes) */
extern CMNETGAME cm_NetGame;  /* 0x936460, the network game */
extern CMLOBBYPLAYER cm_LobbyPlayers[8];  /* 0x9364e0, the eight lobby player records */
extern CMJOIN cm_JoinChar;  /* 0x9367a0, the joined character of a saved game (main_JoinNetworkGame) */
extern int cm_LobbyPlayerId;  /* 0x9367d0, this player's lobby id (G17HELLOMSG.lobbyId) */
extern int cm_LobbyHelloValue;  /* 0x9367d4, the hello answer's second value (G17HELLOMSG.value) */

struct CMGRENADE *cm_ThrowGrenade(struct D3VECTOR *p, int x, int y);  /* 0x4ce5d0 */
unsigned int cm_Random(unsigned int n);  /* 0x4e52f0, a random number below n */
extern struct AICHAR *cm_FightAttacker;  /* 0x6f0cec, the attacking side's leader */
extern struct SBBANK *cm_BombSounds;  /* 0x6f0d14 */

int cm_ObjectOwner(char *c);  /* 0x4ceb70 */
void cm_WaitEventStop(int id);  /* 0x4ceb80 */
void cm_OpenCharInfoWin(struct CMCUTINFO *a, struct AICHAR *c);  /* 0x4cec30 */
void cm_UpdateCharInfoWins(struct CMCUTINFO *a);  /* 0x4ced80 */
struct D3OBJECT; struct D3RECT; char d3if_ScreenBox(struct D3OBJECT *obj, struct D3RECT *r);  /* 0x4486e0 */
int d2_WinOpenPic(short x, short y, int pic, int win);  /* 0x4731d0 */
void d2_SetObjValue(int obj, ...);  /* 0x475cb0 */
extern int d2_LastWindow;  /* 0x6ed938 */
extern int cm_SkipEvents;  /* 0x6f0d8c */
extern int cm_CharInfoWins[];  /* 0x935d20 */

void cm_ShowDamage(struct AICHAR *c, int v, int kind);  /* 0x4cedc0 */
void cm_UpdateDamagePops(void);  /* 0x4cee20 */
void cm_InitDamagePops(void);  /* 0x4cef80 */
void cm_ClearDamagePops(void);  /* 0x4cefa0 */
void d2_MoveObj(short x, short y, int obj);  /* 0x46cda0 */
int d2_CreateScreenText(short x, short y, char *text);  /* 0x473860 */
void d2_CloseView(int view);  /* 0x4758f0 */
extern int cm_FightView;  /* 0x60cb60 */
extern G18POP cm_DamagePops[16];  /* 0x9304c0 */

char d3if_ShowTree(struct D3OBJECT *obj, char show);  /* 0x447300 */
extern int cm_FightOwner;  /* 0x60cb5c */
extern struct AICHAR *cm_CutChar;  /* 0x6f0d74, the character the player commands in the running cut scene */

void cm_DrawScrollArrows(void);  /* 0x4cf370 */
int d2_DrawShape(int x, int y, void *surf, void *pic, unsigned char i);  /* 0x47c6f0 */
void d2_SetClipRect(int x0, int y0, int x1, int y1);  /* 0x47cb40 */
extern const struct D3VECTOR4 d3_Origin;  /* 0x5ebba4, (0, 0, 0), d3_vec.c */
extern float d2_ScreenScale;  /* 0x5fe708 */
extern void *d2_ScreenSurf;  /* 0x6ed924, the screen surface (d2.c defines it) */
extern short d2_ScreenH;  /* 0xfb9070 */
extern short d2_ScreenW;  /* 0xfb9072 */

struct D3OBJECT * d3if_Pick(float x, float y, int mask, int one);  /* 0x448630 */
struct D3SM; char d3sm_Pick(struct D3SM *h, int sx, int sy, int *px, int *pz);  /* 0x45f2b0 */
char d3if_Show(struct D3OBJECT *obj, char show);  /* 0x4471b0 */
extern int cm_SelectedCount;  /* 0x6f0d08 */
extern struct D3OBJECT *cm_HoverObject;  /* 0x6f0ce0 */
extern char *cm_PickMarker;  /* 0x6f0cf0 */
extern struct D3OBJECT *ai_PickedObject;  /* 0x6f22e8 */
extern struct AICHAR *ai_PickedChar;  /* 0x6f22f8 */

void d2_SetObjText(int obj, char *text);  /* 0x4734d0 */
void d2_ScaleObject(int obj, int a);  /* 0x475e80 */
void d2_AddPointerItem(int id, int amount);  /* 0x476b90 */
void d2_ClearPointerItems(void);  /* 0x476c70 */
extern int d2_ClickedId;  /* 0xf8a668 */
extern CMPORTRAIT cm_Portraits[6];  /* 0x930400 */
extern D2OBJ *d2_Objs;          /* 0xf8f080, 0x2ec bytes each (d2.c) */

int d2_CreateWinText(short x, short y, char *text, int win);  /* 0x473650 */

struct SBSAMPLE *snd_QueueVoice(int id, struct SBBANK *bank, char *text, int var, unsigned int delay);  /* 0x4c27d0 */
extern struct D3OBJECT *ai_ClickedObject;  /* 0x6f22e4 */
extern struct SBBANK *cm_AttackerClickVoices;  /* 0x6f0d24 */
extern struct SBBANK *cm_DefenderClickVoices;  /* 0x6f0d28 */

int cm_OrderAttack(struct CMCUTINFO *rec, struct AICHAR *c, struct AICHAR *tgt, int x, int z);  /* 0x4cffd0 */
char d3_GetHeightAt(struct D3SM *h, struct D3VECTOR *pos, int *px, int *pz, float *py);  /* 0x45f170 */




int cm_OrderEscape(struct CMCUTINFO *rec, struct AICHAR *c, struct D3OBJECT *tgt);  /* 0x4d0200 */

int cm_OrderConquer(struct CMCUTINFO *rec, struct AICHAR *c, struct D3OBJECT *tgt);  /* 0x4d02d0 */
int cm_OrderWare(struct CMCUTINFO *rec, struct AICHAR *c, struct D3OBJECT *tgt);  /* 0x4d0380 */

int cm_OrderToBestCell(struct CMCUTINFO *rec, struct AICHAR *c);  /* 0x4d0460 */
void cm_OrderWait(struct CMCUTINFO *rec, struct AICHAR *c);  /* 0x4d0520 */
int cm_BestCellNear(struct AICHAR *c, int cx, int cy, int r, int *ox, int *oy);  /* 0x4d2170 */

char cm_OrderClick(struct CMCUTINFO *rec, struct AICHAR *c);  /* 0x4d0570 */


void cm_FightMouse(struct CMCUTINFO *rec);  /* 0x4d0740 */
struct SBSAMPLE *snd_PlayVoice(int id, struct SBBANK *bank, char *text, int var);  /* 0x4c2760 */
char d3if_SelectTextureSet(struct D3OBJECT *obj, struct D3SURF *surf, unsigned char set, char reload);  /* 0x446f30 */
extern struct SBBANK *cm_AttackerOrderVoices;  /* 0x6f0d34 */
extern struct SBBANK *cm_DefenderOrderVoices;  /* 0x6f0d38 */

void cm_ClearMarks(void);  /* 0x4d08c0 */
struct AICHAR *cm_AddFighter(int id, char *dummy);  /* 0x4d0920 */

void cm_CollectSceneChars(void);  /* 0x4d0a30 */
char cm_CreateDummyFlag(struct D3OBJECT *obj, void *ctx);  /* 0x4d0a80 */
extern int cm_FlagObjectCount;  /* 0x6f0d58 */
extern struct D3OBJECT *cm_FlagObjects[32];  /* 0x935980, the conquest flag objects of the fight scene */

int cm_FreeNetIdSlot(int *a);  /* 0x4d0cd0 */
void ai_ArmGateGuards(G28REC *rec, unsigned char kind);  /* 0x4d0cf0, arms the guards of the town gate event (the kind 0xb characters ai_KindBChars) */
char cm_ClearKind3MaskCB(struct D3OBJECT *o);  /* 0x4d0f80 */
float gm_AddHealth(unsigned short id, int d);  /* 0x4fca40 */

void cm_SetupFightScene(G28REC *rec);  /* 0x4d0fa0, sets up the fight scene of a fight record */
struct SBBANK *snd_LoadVoiceBank(char *name, int a);  /* 0x4c2830 */
void cm_LoadEventScene(char *name);  /* 0x4e2e60, loads the scene file name into a free scene and fades it in */
void cm_ApplySeason(void);  /* 0x4e3650 */
void d3sky_Init(struct D3SKY *s, char build);  /* 0x45d690 */
struct D3SM * d3sm_Create(struct D3TERRAIN *t, int size, int mask);  /* 0x45eeb0, d3_sm.h */
void gm_ShuffledBytes(unsigned char n, unsigned char *out);  /* 0x505be0 */
int gm_BuildingSkill(struct AIBLD *b, unsigned k, int flag);  /* 0x5092e0, f3gm.h (not includable here, cm.c lead comment) */
extern struct AICHAR *cm_FightDefender;  /* 0x6f0ce8, the defending side's leader */
extern int cm_FightWinner;  /* 0x6f0cf4 */
extern struct SBBANK *cm_FightSounds;  /* 0x6f0d0c */
extern struct SBBANK *cm_CrossbowSounds;  /* 0x6f0d10 */
extern struct SBBANK *cm_DaggerSounds;  /* 0x6f0d18 */
extern struct SBBANK *cm_PistolSounds;  /* 0x6f0d1c */
extern struct SBBANK *cm_SwordSounds;  /* 0x6f0d20 */
extern struct SBBANK *cm_AttackerAttackVoices;  /* 0x6f0d2c */
extern struct SBBANK *cm_DefenderAttackVoices;  /* 0x6f0d30 */
extern struct SBBANK *cm_AttackerTauntVoices;  /* 0x6f0d3c */
extern struct SBBANK *cm_DefenderTauntVoices;  /* 0x6f0d40 */
extern struct SBBANK *cm_AttackerPainVoices;  /* 0x6f0d44 */
extern struct SBBANK *cm_DefenderPainVoices;  /* 0x6f0d48 */
extern int cm_AttackerRole;  /* 0x6f0d50 */
extern int cm_DefenderRole;  /* 0x6f0d54 */
extern struct D3BGF *cm_BootsObject;  /* 0x6f0d5c */
extern float cm_FightCellScale;  /* 0x935d00 */
extern float cm_DefenseFactor;  /* 0x60cb58 */

void cm_EndFightScene(G28REC *rec);  /* 0x4d1a10, ends the fight scene of a fight record (cm_SetupFightScene its counterpart) */
void cm_PlaceFighters(int *ids, char *side);  /* 0x4d1c20, places the fighters of one side of the fight at their dummies */
int cm_FadeToBlack(void);  /* 0x4e3060 */
void cm_LeaveEventScene(void);  /* 0x4e30c0 */
void d2_CopyCaption(char *caption);  /* 0x478870 */
char ch_FindFreeCell(struct D3SM *h, struct D3VECTOR *from, struct D3VECTOR *to, int x, int z, int *px, int *pz, int max, int flags); /* 0x4072a0, ch.h */

void cm_FightIntro(char *a);  /* 0x4d1e00, the fight's intro: a random fight track and the cutscene "Kampf_Intro_Fluege" (a unread) */
void cm_FightOutro(char *a);  /* 0x4d1eb0, the outro: stops cm_FightAmbient and runs "Kampf_outro_flug" (a unread) */
struct AICHAR *cm_NearestEnemy(struct AICHAR *c);  /* 0x4d1f10, the enemy the fighter c goes for */
void snd_PlaySpecialTrack(char *name);  /* 0x4c23f0 */
extern int snd_MusicEnabled;  /* 0x6f2578 */
extern int sv_FrameMask;  /* 0x760638 */
extern struct MSXTRACK *cm_FightAmbient;  /* 0x6f0d4c */

float cm_ThreatAt(struct AICHAR *c, int a, int b, float limit);  /* 0x4d2010, the threat at a height map vertex for the fighter c */

int cm_MostThreatenedCellNear(struct AICHAR *c, int cx, int cy, int r, int *ox, int *oy);  /* 0x4d22d0 */
char cm_CollectEscapeObject(struct D3OBJECT *o, void *ctx);  /* 0x4d2450 */
struct D3OBJECT *cm_NearestEscapeObject(struct AICHAR *c);  /* 0x4d2490 */
char cm_CollectWareObject(struct D3OBJECT *o, void *ctx);  /* 0x4d2550 */
struct D3OBJECT *cm_NearestWareObject(struct AICHAR *c);  /* 0x4d25a0 */
char cm_CollectConquerPoint(struct D3OBJECT *o, void *ctx);  /* 0x4d2650 */
struct D3OBJECT *cm_NearestConquerPoint(struct AICHAR *c);  /* 0x4d2680 */
extern int cm_PointCount;  /* 0x6f0d60 */
extern struct D3OBJECT *cm_PointList[];  /* 0x930380 */

void cm_InitOrderChances(void);  /* 0x4d27a0 */
extern float cm_OrderChances[0xb4];  /* 0x9300a0 */

float *cm_OrderChancesFor(struct AICHAR *side);  /* 0x4d2c00 */

float cm_OrderRating(struct AICHAR *c, int order);  /* 0x4d2e30 */
void cm_GiveFightOrders(struct AICHAR *side);  /* 0x4d2f80 */

void cm_CarryOutOrder(struct CMCUTINFO *rec, struct AICHAR *c);  /* 0x4d3120 */
void cm_FallDownAction(struct CHACTION *a);  /* 0x4d3300 */

int cm_CheckDeath(struct AICHAR *c);  /* 0x4d3390 */
struct CHACTION * ch_AddActionCB(struct CHARACTER *ch, void (*func2)(struct CHACTION *), unsigned char frame, unsigned int type, ...); /* 0x40b400, ch.h (CHACTFUNC func2; cm.c calls it through ch_AddActionCBK) */

void cm_HitAction(struct CHACTION *a);  /* 0x4d3550 */
void cm_LayBombAction(char *ev);  /* 0x4d3980 */
void cm_ThrowBombAction(char *ev);  /* 0x4d3a30 */
void cm_CheerAction(char *ev);  /* 0x4d3ac0 */
void cm_PickUpAction(char *ev);  /* 0x4d3ae0 */
struct AICHAR *cm_CheckFightWinner(G28REC *rec);  /* 0x4d3b30 */
int cm_LootStock(AIBLD *a, AIBLD *b, struct AICHAR *d, struct AICHAR *t);  /* 0x4d3d10 */
int cm_FightRole(struct AIBLD *b);  /* 0x4d4050 */
int cm_LootList(int x, int y, int mode);  /* 0x4d4090 */
void cm_FightPortraits(int *ids, int x, int y);  /* 0x4d4340 */
int cm_FightStartDialog(G28REC *a);  /* 0x4d4540 */
void cm_FightEndDialog(G28REC *a);  /* 0x4d4d70 */
int cm_CheckFight(G28REC *a);  /* 0x4d60b0 */
void cm_FightResult(struct CMCUTINFO *r);  /* 0x4d6930 */
void cm_FightFrame(struct CMCUTINFO *r);  /* 0x4d6970 */
void cm_BuildFightUI(struct CMCUTINFO *a);  /* 0x4d6a50, a: the member record, unused */
void cm_CloseFightUI(void);  /* 0x4d6b70 */
extern int cm_PickCellX;  /* 0xfa5f00 */
extern int cm_PickCellZ;  /* 0xfa5f04 */
extern int cm_SceneDeadline;  /* 0x6f0d84 */
extern int cm_SceneTicks;  /* 0x6f0d80 */
extern int cm_SceneTimedOut;  /* 0x6f0d88 */
extern int cm_FightTimeBar;  /* 0x60cb64 */
extern int cm_FightButton;  /* 0x60cb68 */
extern int cm_FightForm;  /* 0x6f0d64 */

extern int cm_TextBox;  /* 0x60d368 */
void cm_RunFight(G28REC *a);  /* 0x4d63e0, runs a fight record */
unsigned int cut_GetRandSeed(void);  /* 0x4e52c0 */
void cut_RandSeed(unsigned int seed);  /* 0x4e52a0 */
void cm_RunSceneParty(G28REC *party, void *ctx);  /* 0x4e3830 */
char d3_SetLightSet(unsigned int set, float t, float scale, char calc);  /* 0x449de0 */
extern int cm_SceneDuration;  /* 0x60d364 */
extern int cm_FightFixedLight;  /* 0x6f244c */
void cm_SendPartyNote(struct AICHAR *a, G28REC *b, char *text, char *extra);  /* 0x4e48b0 */



void gm_ChangeBuildingState(struct AIBLD *b, int d);  /* 0x50cad0 */

int d2_OpenForm(short x, short y, char *name);  /* 0x4741f0 */
int d2_SetForm(int view, int n);  /* 0x475f70 */
int d2_GetWinObj(int view, int idx, int k);  /* 0x475b80 */
int io_PrintText(intptr_t fmt, ...);  /* 0x515960 */
int cm_MessageBox(intptr_t id, int flags);  /* 0x4e5470, a message box for the text id with the flags (see cm.c) */
int gm_StallGoodsList(struct AIOBJ *c, struct AIRECIPE *out);  /* 0x50aa00 */
extern int cm_FightSettled;  /* 0x6f0cf8 */
extern int cm_FightLootValue;  /* 0x6f0cfc */
extern struct D2WIN *d2_LastWindowPtr;  /* 0x6ed980, window created last (d2.c) */

int cm_LootCarts(G28REC *a, AIBLD *b, struct AICHAR *d, struct AICHAR *t, float f);  /* 0x4d3ea0 */
float gm_GoodsPrice(unsigned id, unsigned char p);  /* 0x5089c0, a price */
int gm_GetGoodsValue(struct AICHAR *ch);  /* 0x509e60 */

extern int cm_OrderTicks;  /* 0x92bec0 */
void cm_RunCutOrders(CMCUTINFO *rec);  /* 0x4d76a0 */

extern int cm_FightPaused;  /* 0x6f0ce4, fight paused */

extern int cm_ScenePartyRuns;  /* 0x6f0d7c */
struct MSXTRACK * msx_PlayAmbient(char *name, int vol);  /* 0x4243f0 */
void cm_FightLoop(struct CMCUTINFO *a, int ctx);  /* 0x4d88c0 */
void cm_FightMember(struct CMCUTINFO *a, int ctx);  /* 0x4d8b10, the cm_Kinds[].askPlayer callback */

extern struct CHARACTER *cm_SceneChars[16];  /* 0x92ca80 */
extern unsigned int cm_FightStart;  /* 0x6f0da4, fight start (d3_Time) */
void * d2_SetFont(int font);  /* 0x476030 */
void d2_DrawTextBox(int x, int y, int w, int h, void *surf, char *text, unsigned int flags);  /* 0x46f1a0 */
void d2_AddDirty(int x, int y, int w, int h);  /* 0x468eb0 */
extern int d2_TextDrawnW;  /* 0x6ed968 */
extern int d2_TextDrawnH;  /* 0x6ed96c */
void cm_ClearSceneChars(void);  /* 0x4d8b30 */
void cm_DrawFightTime(void);  /* 0x4d8b50 */

int cm_DeleteChar(struct CHARACTER *a);  /* 0x4e3250 */

void d2_SetObjFont(int obj, int font);  /* 0x4760b0 */


/* ---- declarations of cut.c (joined) ---- */
/* Declarations of cut.c (the cutscene code 0x4d8c70..: council sessions, duels, executions; tag "cut_MainDuell()"). Names are ours. */

extern int cm_TallyYes;  /* 0x6f0d6c, the "yes" pictures of the deposition tally */
extern int cm_TallyNo;  /* 0x6f0d68, the "no" pictures of the deposition tally */
extern int cm_TallyAbstain;  /* 0x6f0d70, the abstentions of the deposition tally */
struct LCAMOUNTROW; void cm_StackPicture(int unused, struct LCAMOUNTROW *o);  /* 0x4d8c70 */
void cm_TallyStack(int a, int b, int c);  /* 0x4d8cb0 */

typedef struct G22ENT {                 /* 0x18 bytes, one participant of a session (amt_GetColumnOffices) */
    int unk00;
    int id;                             /* 0x04, character id */
    int unk08;
    int flag;                           /* 0x0c */
    signed char kind;                   /* 0x10, 2 = candidate, 3 = voter */
    char pad[7];
} G22ENT;
extern struct D2PIC *d2_Pics;  /* 0x6ed918 */
struct SBBANK *cm_LoadVoiceBank(char *name, int a);  /* 0x4e3270 */
void cm_PlaySpecialTrack(char *a);  /* 0x4e3620 */
int amt_GetColumnOffices(int col, int max, struct AMTREC *out);  /* 0x4e6fc0 */
void d2_SetViewEnabled(int view, int on);  /* 0x475590 */
void d2_CloseView(int view);  /* 0x4758f0 */
struct SBSAMPLE *cm_QueueVoice(int id, struct SBBANK *bank, char *text, int var, unsigned int delay);  /* 0x4e32d0 */
int cm_RunSceneTicks(int a);  /* 0x4e3570 */
int amt_SendOfficeMessage(unsigned char a, struct AICHAR *b, struct AICHAR *c, int d, unsigned char e);  /* 0x4e6680 */
int cm_StartEventArg(char *name, char *cmd);  /* 0x4e2c30 */
int cm_WaitEvent(int a);  /* 0x4e2c70 */
int cm_UnloadVoiceBank(struct SBBANK *a);  /* 0x4e3290, drops the reference of the voice bank a (0 in the replay mode) */
int cm_WaitEventFull(int a);  /* 0x4e2d40 */
void cm_EndSpecialTrack(void);  /* 0x4e3640 */
void ai_CampaignStep(int a, void *b, int c, int d);  /* 0x576040 */
void cm_RunCouncilSession(G28REC *a);  /* 0x4d8e20 */
extern int cm_DialogFrameFlags;  /* 0x60d360, the frame wait of the dialogs (0x5309a0) */
extern int d2_ClickedId;  /* 0xf8a668 */
int cm_DialogTimer(int dlg, int a, int c);  /* 0x4e53e0 */
struct AICHAR; int ai_TrustedOfFour(unsigned char k, struct AICHAR *p, int *ids, int *out);  /* 0x4aad30, poker.c */
int amt_GetOffice(unsigned char i, struct AMTREC *out);  /* 0x4e6f30, amt.c (this unit calls it through amt_GetOfficeI) */
int amt_GetKind(int k, struct AMTKIND *out);  /* 0x4e6f80 */

int cm_AskDeposeVote(struct AICHAR *a, struct AICHAR *b, struct AICHAR *c, int *out);  /* 0x4da9e0 */
int cm_AskElectVote(unsigned char office, struct AICHAR *b, int *ids, int *click);  /* 0x4dab50 */
void cm_SessionAskPlayer(CMCUTINFO *r, CMSESSIONREQ *m);  /* 0x4dada0 */

extern int cm_DuelOver;  /* 0x6f0d94 */
extern int cm_DuelLeft;  /* 0x92bca4 */
extern unsigned char cm_DuelScore[2];  /* 0x6f0da8, the damage taken by the left / right duellist */
extern unsigned char cm_DuelLeftInsultWon;  /* 0x6f0daa, the left duellist won the insult round */
extern unsigned char cm_DuelRightInsultWon;  /* 0x6f0dab, the right duellist won the insult round */
extern unsigned char cm_DuelLeftRollWon;  /* 0x6f0dac, the left duellist won the roll round */
extern unsigned char cm_DuelRightRollWon;  /* 0x6f0dad, the right duellist won the roll round */
struct CMCUTINFO *cm_CutInfoById(int id);  /* 0x4e50e0, the cutscene record cm_CutInfos whose playerId is id; 0 without */
int cm_WaitTicks(int a);  /* 0x4e3420 */
void cm_SinkDownAction(struct CHACTION *a);  /* 0x4de4b0 */
int cm_DuelSinkDown(struct AICHAR *c, int dmg);  /* 0x4de530 */
void cm_DuelRound(struct AICHAR *a, struct AICHAR *b, char *side);  /* 0x4de900 */
extern int cm_DuelVariantCount;  /* 0x60d370 */
extern int cm_DuelVariantPos;  /* 0x6f0db0 */
extern int cm_DuelVariants[];  /* 0x92bcc0 */
void gm_Shuffled(unsigned char n, int *out);  /* 0x505ca0 */
void cm_DuelInitVariants(int n);  /* 0x4de5e0 */
int cm_DuelVariant(int n);  /* 0x4de610 */
void cm_DuelShotAction(struct CHACTION *a);  /* 0x4de640 */
extern int cm_DuelRight;  /* 0x92bca0 */
void cm_DuelOutcome(G28REC *m);  /* 0x4debe0 */
int cm_ResetCutInfos(G28REC *party);  /* 0x4e36a0 */
char d3_SetFogSet(unsigned int a, unsigned int b, float t);  /* 0x44a170 */
int cm_StartScript(char *name);  /* 0x4e2bf0, loads the script name (evt_Load), runs it and returns its id */
struct SBSAMPLE *cm_PlayVoice(int id, struct SBBANK *bank, char *text, int var);  /* 0x4e32b0, plays the voice sample of speaker id in bank (text, var pick the sample); 0 in the replay mode */
int cm_StopScript(int a);  /* 0x4e2d90 */
void cm_RunDuel(G28REC *m);  /* 0x4ded10 */



int cm_DuelAftermath(G28REC *m);  /* 0x4dfa20 */
void cm_DuelRoundDialog(CMCUTINFO *r, G28REC *m);  /* 0x4dfcb0 */
void cm_DuelChooseRound(CMCUTINFO *, G28REC *);  /* 0x4dfdd0, the duel round dialog of the party scene (r, the duel record m) */
void cm_DuelAskAI(CMCUTINFO *r);  /* 0x4dff80 */
void cm_DuelAskPlayer(CMCUTINFO *r, G28REC *m);  /* 0x4dfff0 */
void cm_RunPictureShow(G28REC *m);  /* 0x4e0010 */

int cm_ExecutionAftermath(G28REC *m);  /* 0x4e0040 */

void cm_CreateSceneSky(char *tex);  /* 0x4e32f0 */
int cm_StartSceneRain(int a);  /* 0x4e33d0, remembers the result of 0x413b30(a) in 0x6f0dbc */
int cm_StopSceneRain(void);  /* 0x4e33f0 */
int cm_DestroySceneSky(void);  /* 0x4e3390 */
void cm_RunExecution(G28REC *m);  /* 0x4e01e0 */
int cm_CheckWedding(G28REC *m);  /* 0x4e0580 */
int cm_EndWedding(void *arg);  /* 0x4e06d0 */
int cm_RunSceneTicksOrClick(int ticks, int (*cb)(void *), void *arg);  /* 0x4e3490 */
int cm_WaitEventOrClick(int a, int (*cb)(void *), void *arg);  /* 0x4e2cc0 */
int cm_RunWedding(G28REC *m);  /* 0x4e0770 */

int cm_CheckBirth(G28REC *m);  /* 0x4e0e90 */
extern struct D2INPUT *d2_FocusedInput;  /* 0x6ed9dc, the focused input (as d2.h / rt.h) */
extern int cm_TutorialActive;  /* 0x6f2438 */
void snd_ClearQueue(void);  /* 0x4c01b0 */
void d2_CentreViewWindows(int view);  /* 0x475600 */
void cm_RunBirth(G28REC *m);  /* 0x4e0f70 */
int cm_DeathSceneCheck(G28REC *m);  /* 0x4e1220 */
struct AICHAR; void gm_ForfeitEstate(struct AICHAR *c, char *out, int flag);  /* 0x506e70, the character c forfeits its estate after a lost fight; the announcement into out */
void ai_FamilyTreeWindow(int param_1, unsigned char param_2, intptr_t param_3, int param_4);  /* 0x5c4150 */
void cm_RunDeath(G28REC *m);  /* 0x4e1250 */



int gm_GetWorth(unsigned short id);  /* 0x50a640 */
void d2_SetObjEnabled(int obj, int on);  /* 0x475e40 */
void cm_SetViewEnabled(int view, int on);  /* 0x4e2bd0 */
void cm_WaitGroupScripts(void);  /* 0x4e2e00 */
void snd_EndSpecialTrack(void);  /* 0x4c2480 */
extern struct D3TRAIN *cm_SceneRain;  /* 0x6f0dbc */
extern struct D3SKYLAYER *cm_SkyLayer;  /* 0x6f0db4, the layer of cm_CreateSceneSky's sky */
extern struct D3SKY *cm_SceneSky;  /* 0x6f0db8, the scene's sky (cm_CreateSceneSky) */
struct D3SKY; struct D3SKYLAYER; void d3sky_DeleteLayer(struct D3SKY *s, struct D3SKYLAYER *l);  /* 0x45d800 */
int cm_ShowPartyTexts(G28REC *party);  /* 0x4e37a0 */
int cm_WaitTicks(int a);  /* 0x4e3420 */
int cm_PartyAnswered(G28REC *party);  /* 0x4e3750 */
int cm_PrevPartyMember(G28REC *party, int n);  /* 0x4e3800 */
struct D3SKY; struct D3SKY *d3sky_Create(float horizon, float fogstart, float fogscale);  /* 0x45da30 */
/* d3sky_CreateLayer (0x45d880): declared in cm's head after d3.h (its D3TEXFLAGS parameter is passed by value) */
void d3sky_SetLayerSpeed(struct D3SKY *s, struct D3SKYLAYER *l, float speed);  /* 0x45d960 */
void d3sky_FadeLayer(struct D3SKY *s, struct D3SKYLAYER *l, unsigned char alpha, float time);  /* 0x45d9a0 */
void cm_CreateSceneSky(char *tex);  /* 0x4e32f0 */
extern struct D2FADE *cm_SceneFade;  /* 0x6f0da0, the fade 0x4e3060 started */
extern int cm_SceneDepth;  /* 0x6f0d9c, the scene nesting depth */
extern int cm_SceneEnterScript;  /* 0x60d36c, -1 or the object waited for (0x4284a0) */
extern int evt_LastId;  /* 0x5f8438 */
extern int d3t_CamMoving;  /* 0x6310e4 */
struct CHARACTER *cm_CreateChar(char *name, struct D3VECTOR *pos);  /* 0x4e3230 */
void cm_RunBankruptcy(G28REC *m);  /* 0x4e1700 */
int cm_CheckAuction(G28REC *m);  /* 0x4e19a0 */


struct AIDEC; int gv_GetTableRecord(int i, struct AIDEC *out);  /* 0x4f2720 */
int sb_IsPlaying(struct SBSAMPLE *s);  /* 0x426f20 */
void msx_StopAmbient(struct MSXTRACK *t);  /* 0x4244b0 */

int gm_ConvertMoney(int a, unsigned char k);  /* 0x5085b0 */
int gm_PlayerFactor(int a, unsigned char k);  /* 0x5085f0 */
void d2_SetObjValue(int obj, ...);  /* 0x475cb0 */
void cm_ShowObjectScene(struct AIBLD *o, int id);  /* 0x4e2910 */

int d2_ClearSurface(struct D2SURF *surf);  /* 0x4796c0 */
void d2_BlitPart(int sx, int sy, int w, int h, struct D2SURF *src, int x, int y, struct D2SURF *dst);  /* 0x479480 */
void d2_ReleaseFade(struct D2FADE *f);  /* 0x476860 */
struct D2FADE * d2_StartFade(int x, int y, int w, int h, char *name, int dur, unsigned int flags);  /* 0x4767d0 */
char d3_InflateScene(unsigned int flags);  /* 0x43deb0 */
extern void *d2_BackSurf;  /* 0x6ed92c */
extern unsigned int d3_SceneFlags;  /* 0x63349c */
extern unsigned int cm_SceneInflateFlags;  /* 0x6f0d98 */

char d3_LoadScene(char *name, void *f, void (*progress)(int a, int i, int n));  /* 0x44be60 */
void d3fl_SetShift(struct D3FLMAP *map, unsigned char shift, char light);  /* 0x446dc0, d3_fl.c */
void d3if_Prerender(char map);  /* 0x447860 */

extern int cm_PartyTurn;  /* 0x6f0d78 */


void cm_ExecCutscene(G28REC *party);  /* 0x4e4060, runs the scene party m */
int cm_UpdateParties(void);  /* 0x4e4060's caller: runs every done party within its hour (cm_ExecCutscene) */
int cm_IsPartyMember(int id, G28REC *party);  /* 0x4e4870, 1 when the character id is one of the scene party m's members and still exists */
void gm_AddTime(struct AITIME *c, int hours, int mins, int secs);  /* 0x4fe140 */



char ai_RunPendingParties(int pl);  /* 0x4e4f80, runs the pending parties of the player pl */
void ai_DebugDumpPerson(struct AICHAR *c);  /* 0x4e5bf0, the debug dump of a person */
struct G28REC *cm_FindPartyOfKind(int a, int b);  /* 0x4e5050, the used party of the kind a with the thing b: its record, 0 without */
void cm_InitScenes(void);  /* 0x4e5770, clears the party records and registers the 12 scene kinds */


extern unsigned int cut_RandState;  /* 0x92c4e0, the random seed of the scenes */
extern int cm_DialogStart;  /* 0x6f0dc0 */

extern int cm_DialogLength;  /* 0x60d374 */

int d2_CreateRadioGroup(int n, ...);  /* 0x46c490 */
void d2_RadioAdd(int g, int obj);  /* 0x46c560 */
void d2_RadioSelect(int g, int sel);  /* 0x46c630 */
void d2_MenuNavigate(int g);  /* 0x46c6c0 */
void d2_RaiseViewWindows(int view);  /* 0x4741a0 */
void d2_CentreViewWindows(int view);  /* 0x475600 */
void d2_RadioClear(int g);  /* 0x46c600 */
extern char cm_MessageBoxOpen;  /* 0x6f0dc4 */

extern CMKIND cm_Kinds[];  /* 0x92c500, the scene kind table (12 of 0x14 bytes): run, callbacks, flag, check */
void d3io_NoopCallback(void *t);  /* 0x44ee40 */

extern char ai_CharKindNames[][24];  /* 0x60eae0, the names of the NPC kinds */









extern float cm_SpeedFactor;  /* 0x5f1290 */
extern int ch_LowPoly;  /* 0x631064 */
extern int cm_SavedScene;  /* 0x925510 */
extern int cm_SavedNoGroup;  /* 0x92cac0 */
extern char cm_SceneState[];  /* 0x92c600, 0x480 bytes of scene state */
extern unsigned char d3_FogByDistance;  /* 0x6334a5 */
extern char d2_CaptionCopy[0x80];  /* 0xf8aae0, the d2 caption / status text buffer */
extern unsigned short cm_DisabledObjs[];  /* 0x92bee0 */
void d2_SetPointerSprite(int a, int pic);  /* 0x476f80 */

/* copy of am.h's AI_ZERO (the headers do not compile together) */
/* The engine's inline-asm clear (d3.h D3_ZERO), byte stores up to dword alignment, dwords, the rest. */
#define AI_ZERO_CAT(a, b) a##b
#define AI_ZERO_LABEL(n) AI_ZERO_CAT(ai_zero_tail, n)
#define AI_ZERO(dst, size) {                                        \
    int _zn = (size); void *_zp = (dst);                            \
    __asm mov edi, _zp                                              \
    __asm mov ebx, _zn                                              \
    __asm xor eax, eax                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle AI_ZERO_LABEL(__LINE__)                               \
    __asm rep stosb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep stosd                                                 \
    __asm AI_ZERO_LABEL(__LINE__): add ecx, ebx                     \
    __asm rep stosb                                                 \
}



/* the same with the destination named in the asm (a global: use `offset name`) */
#define AI_ZERO_AT(var, size) {                                     \
    int _zn = (size);                                               \
    __asm mov edi, var                                              \
    __asm mov ebx, _zn                                              \
    __asm xor eax, eax                                              \
    __asm lea ecx, [edi+edi*2]                                      \
    __asm and ecx, 3                                                \
    __asm sub ebx, ecx                                              \
    __asm jle AI_ZERO_LABEL(__LINE__)                               \
    __asm rep stosb                                                 \
    __asm mov ecx, ebx                                              \
    __asm and ebx, 3                                                \
    __asm shr ecx, 2                                                \
    __asm rep stosd                                                 \
    __asm AI_ZERO_LABEL(__LINE__): add ecx, ebx                     \
    __asm rep stosb                                                 \
}

#endif
