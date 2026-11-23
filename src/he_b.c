/* he_b.c -- the second object of the event system (0x568aa0..0x575860): the alloc / run handlers of the running
   income 3, the production, the searches 8 / 9, trade 0xb, research 0xc and construction 0xd events, the alchemist
   events 0x95 .. 0x98, the secret room 0x99 .. 0x9b, the graveyard and meeting events 0x88 .. 0x94, the gypsy /
   curse / trial / circus events 0x9d .. 0xa4 and the message filter. The records and views are he.c's (he.h).
   Its .data block starts with he_BuildingModels 0x627e98, right after he's last strings (0x568310's "Trainieren",
   "Heilen"): a plain datum after literals, a new object; its strings follow from 0x628a28 ("_NACHRICHTEN_HS_07",
   0x568be0's). The first function lies in 0x568310 (exclusive) .. 0x568be0; 0x568aa0 is a guess (the first after
   he's registration function). The name is ours.
   Open: the first function (bprobe: he_RunProduktion 122 -> 28 for any split from 0x568220 to 0x569210, no other change).
   Open: head: the prototypes of this unit's functions still sit in he.h (scattered among he's).
   split from he (rea 8cef7d5b, src/game/he.c); boundaries in decl/text.dcl */
struct AHMSLOT;
struct D3SM;
struct SBBANK;
struct SBSAMPLE;
union AHMGRID;
struct D3SM;
#include "d2_types.h"
#include "txt_views.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <d3d.h>
#include "he.h"
void he_NoHandlerB(
    struct AIJOB *
        ev); /* unlinked, defined at the end of the unit: the empty handler of the event types without one */
#include "he_b.h"
#include "hmt_types.h"
#include "d3.h"
#include "d3_quad.h"
#include "d3.h"
#include "d3_light.h"
#include "txt.h"
#include "di_input.h"
#include "evt.h"
#include "data_views.h"
#define GAPDATA __declspec(align(1)) unsigned char

/* full rebuild: the symbols whose original addresses the code above spells literally */
extern const unsigned __int64 gypsyFilter; /* 0x5eed68, lcmap.c */
#include "menu_types.h"
extern GAPDATA full_data_602568[];
extern GAPDATA full_data_5ff710[];

extern GAPDATA full_data_5f320c[];
extern int d2_ClickedForm;
extern unsigned char ai_GameState;
extern GAPDATA full_data_5fe7d0[];
extern const int sv_PhaseMinutes[24];
extern GAPDATA full_data_60d0d4[];
extern struct G16TRACKHANDLES snd_TrackHandles;
extern struct D3TRAIN *d3t_Rain;
extern GAPDATA full_data_5f1890[];
extern int ai_PermsDirty;

extern unsigned char ai_GameState;
extern struct SBBANK *snd_SystemBank;
extern const int sv_PhaseMinutes[24];
#include "sv_types.h"
extern float gm_DayStartHours[];
extern char main_GamePath[]; /* 0x624690, main.c: the game directory */
extern float gm_DayEndHours[];

extern unsigned char ai_GameState;
#include "cm_types.h"
extern int d2_ClickedForm;
#include "mission_types.h"
#include "ahm_types.h" /* AHMSLOT */
extern float gm_DayStartHours[];
extern float gm_DayEndHours[];
extern int d2_ClickedForm;
extern GAPDATA full_data_602568[];
extern const int sv_PhaseMinutes[24];
extern float gm_DayStartHours[];
extern float gm_DayEndHours[];
extern const float gm_MoodRanges[476];
extern const float gv_SaleShares[];

struct AICHAR;
struct AMTREC;
struct CHARACTER;
struct CHACTION;
struct EVTSCRIPT;
struct G15PLANT;
struct G11REC;
struct AITIME;

/* one of the ten 16-byte slots of the walk event 0x7a at AIJOB +0xac (he_StartWalk clears them) */
typedef struct
    HEDETECT { /* he_DetectAttack's question and answer (he_RunRobbery builds it on its stack) */
  struct AIBLD *bld; /* 0x0, the building attacked */
  float
      range; /* 0x4, how near a watch character has to stand to see it (5000.0f) */
  AIJOB *ev;    /* 0x8, the attack event */
  AIJOB *found; /* 0xc, the watch event that saw it, 0 at the start */
} HEDETECT;
typedef union HESOLDMSG { /* the data of the sys message 4 he_RunSale sends: an hour from now as AITIME, of
                             which the building and the object overwrite the first 8 bytes (the
                             original's order) */
  AITIME due;
  struct {
    int bld;   /* 0x0, the building's id */
    int objId; /* 0x4, the sold object's id (AIOBJ.objId) */
  } sold;
  char data
      [0x7c]; /* the 0x7c bytes cm_SendExSysMessage copies into its message */
} HESOLDMSG;
#define HE_WALK_PARTNERS1                                                      \
  0x20a0 /* the two partner masks of he_FillWalkSlot's ai_FindPartnersRandomWalk (bits not read yet) */
#define HE_WALK_PARTNERS2 0x402c20
#define HE_WALK_BUILDINGS                                                      \
  0x1a7f4c3a0i64 /* the building kinds of a walk (bit k: ai_BTypes kind k; he_StepWalk tests the same mask) */

int he_RegisterEventTypes22(void);
int he_RegisterEventTypes02();
int he_RegisterEventTypes03();
int he_RegisterEventTypes88();
int he_RegisterEventTypes95();
int he_RegisterEventTypes99();
int he_RegisterEventTypes9d();
int he_RegisterEventTypeA2();

#include "ls.h"
#include "f3init.h"
#include "d2.h"
#include "d3_anim.h"
#include "d3_engine.h"
#include "d3_int_io.h"
#include "d3_interface.h"
#include "d3_io_a.h"
#include "d3_par.h"
#include "d3_sm.h"
#include "d3_vec.h"
#include "err.h"
#include "gfx.h"
#include "io_text.h"
#include "main.h"
#include "mem.h"
#include "rd.h"
#include "tb.h"
#include "tr.h"
#include "udp.h"
#include "d3_pose.h"
#include "sv_t.h"
#include "lc.h"
#include "ai_bld.h"
#include "f3gm_carry.h"
#include "ai_char.h"
#include "f3gm_types.h" /* AIGOOD / GM_GOOD (the goods prototypes) */
#include "gv_types.h"
#include "ch.h"
#include "am_types.h"
#include "net.h"
#include "amt_types.h"
#include "rt_types.h"
#include "rt.h"
#include "d3_tools.h"
#include "d3_snd.h"
#include "sblib.h"
#include "vfs.h"
#include "sv.h"
#include "f3gm.h"
#include "cm.h"
#include "gv.h"
#include "ahm.h"
#include "am.h"
#include "amt.h"
#include "mission.h"
#include "rmsg.h"
#define HE_BARD_MARK                                                           \
  0x68427244 /* 'DrBh': he_RunBard's mark of the bard's script (EVTSCRIPT.tag[0]) */
#define HE_LOVER_FLAG                                                          \
  0x800000 /* AICHAR.flags1c8: has a keeper (he_StartLover sets it, he_RunLover clears it) */
typedef struct
    HECHILDLIST { /* the children of a scene object, collected by he_CollectChild */
  D3OBJECT *root;        /* 0x000, the object walked */
  D3OBJECT *items[0x40]; /* 0x004 */
  int count;             /* 0x104 */
} HECHILDLIST;
#define MEETING_KINDS_LO                                                                      \
  0x807c4116 /* the building kinds 1, 2, 4, 8, 0xa, 0xe, 0x12 .. 0x16 and 0x1f whose people a \
                 meeting's disease reaches (he_Unk572310's 1 << kind mask, kinds below 0x20) */
#define MEETING_KINDS_HI 1 /* the same for the kinds from 0x20 on: 0x20 */
#define PLUNDER_PARTNER_FLAGS                                                  \
  0x700408 /* the partner-chain flags the plunder event's victim search passes \
              ai_PickPartnerRandomWalk (an immediate, no address; the bits are not read) */
#define HE_MEET_MARK                                                           \
  0x66675073 /* the meeting scene's mark (event 0x91: EVTSCRIPT.tag[0], the building id in tag[1]) */

/* dcp unit split: the declarations of he before the moved functions */
void err_Message(char *text);
#include <stdarg.h>
#include <math.h>
/* clang-format off */
unsigned short util_Random(unsigned short n);  /* 0x42ec00, @original: tr.c defines it returning int; this unit's callers read the 16-bit result (mov si,ax / movzx): the original's units saw a 16-bit declaration */
/* clang-format on */
void he_AllocDueIsStart(AIJOB *ev);
void he_SetLifeByAge(AICHAR *c, unsigned short num);
void d3t_SetColor(D3OBJECT *obj, unsigned char r, unsigned char g,
                  unsigned char b);
struct D3OBJECT;
char d3if_Delete(struct D3OBJECT *obj); /* 0x447190, d3_interface.h */
void sv_PumpNet();
int sprintf(char *buf, const char *fmt, ...);
void mem_Free(void *p);
void err_Message(char *text);
void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c, struct AIJOB *g);
void ai_ShowTributeDelayedNews(struct AICHAR *param_1);
void ai_ShowTributeCollectNews(struct AICHAR *param_1);
void ai_ShowTributeClaimNews(struct AICHAR *param_1, struct AICHAR *param_2);
void ai_ShowTavernHelperNews(struct AICHAR *param_1, struct AICHAR *param_2,
                             int param_3);
unsigned int ai_MarriageTest(int param_1, int param_2);
int gv_HeldCrimeIdsOf(int culprit, int *out, unsigned short t);
void gm_ChangeRelationToJobs(unsigned short a, int b);
void ai_PlagueNews(void);
int ai_PickActionBuilding(struct AICHAR *p, int a, __int64 mask, float lo,
                          float hi, int *out);
void ai_PlagueMessage(struct AICHAR *c, void *bld);
float util_RandomF2();
int ls_GetLanguage();
typedef struct
    HEINN { /* he_RunInnSim's list of the inns (he_FindGuestInn walks it, 12 bytes each) */
  AIBLD
  *inn; /* 0x0, the inn (a building of kind 0x16), 0: the end of the list */
  AIOBJ *drink1; /* 0x4, its bar's good 0x179, 0: none */
  AIOBJ *drink2; /* 0x8, its bar's good 0x17a, 0: none */
} HEINN;
unsigned short hmt_RecordCount(void);
unsigned short hmt_RandomRecord(short k);
unsigned short hmt_RandomTextOffset(unsigned short k);
const struct G11REC *hmt_GetRecord(unsigned short k);
struct ORDSTATS;
float ord_GetStatistics(struct ORDSTATS *o);
int d3t_PlaceObjectV(struct D3OBJECT *camera, struct D3VECTOR *pos,
                     struct D3VECTOR *dir, int unk, char flags);
void ai_PlagueMessageAll(void);
void udp_Send(char *buf, int len);
#pragma pack(push, 1)
typedef struct
    HERANKHEAD { /* 0xcf bytes, the head packet of the ranking he_RunRanking sends (udp_Send) */
  unsigned short one;  /* 0x00, 1 */
  unsigned short kind; /* 0x02, 3: the head */
  unsigned short size; /* 0x04, 0xcf, the bytes sent */
  char titles[5]
             [0x18]; /* 0x06, the five column titles (texts 0x16b7 .. 0x16bb) */
  char player[0x20]; /* 0x7e, the own player's name */
  char worthTitle[0x18];  /* 0x9e, "Vermögen" */
  char pointsTitle[0x18]; /* 0xb6, "Gewinnpunkte" */
  unsigned char count;    /* 0xce, the players that follow */
} HERANKHEAD;
typedef struct
    HERANKLINE { /* 0xb9 bytes, one ranked player's packet (after HERANKHEAD) */
  unsigned short one;  /* 0x00, 1 */
  unsigned short kind; /* 0x02, 2: a line */
  unsigned short size; /* 0x04, 0xb9, the bytes sent */
  unsigned int netId;  /* 0x06, the character's netId */
  int worth; /* 0x0a, GMRANK.worth in the own player's money (gm_ConvertMoney) */
  int points;          /* 0x0e, GMRANK.points */
  unsigned char count; /* 0x12, the players ranked */
  unsigned char
      player; /* 0x13, 1 for a player's character (kind 6 / 7), else 2 */
  unsigned char skills[5]; /* 0x14, AICHAR.skills */
  char name[0x18];         /* 0x19, the name */
  char job
      [0x20]; /* 0x31, the profession (text 0x130, + 0x5f for a woman, + jobId) */
  char rank[0x20]; /* 0x51, the rank (text 0x114, + 0xa for a woman, + b00d) */
  char office
      [0x24]; /* 0x71, the office (text 0x253, + 0x28 for a woman, + officeKind) */
  char office2
      [0x24]; /* 0x95, the second office (the same texts, + secondOffice) */
} HERANKLINE;
#pragma pack(pop)
int he_PickNearBuilding(AICHAR *c, int n, AIBLD **blds, int *bldId, int *objId);
int amt_InitApplicant(struct AICHAR *c, int k);
int amt_GetOpenOffice(int k);
int amt_CreateApplicant(int k);
int ai_TutorialOpenIntro();
int ai_TutorialTick();
int ai_TutorialCloseIntro();
void ai_TutorialClearHost(void);
void sv_PopTo(void (*v)());
void he_FreeEventNow(AIJOB *r);
void he_MessageBoxQuickjump(int a1, int a2, char *text, int fl, int a5, int a6,
                            int a7, char *jump, char *text2);
int gm_LevelPayout(int v, int kind);
int d3_VecEqual(const struct D3VECTOR *a, const struct D3VECTOR *b, float eps);
void sv_SelectPanelObject(struct AIBLD *o, int b, char *c);
void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c, struct AIJOB *g);
int ord_DispatchOrder(int id, struct AICHAR *c, ORDMSG *m);
struct G15PLANT *veg_FindPlantId(struct G15PLANT *p, int id);
float gm_StockPrice(int p,
                    int n); /* 0x4ffa10 (f3gm.c; f3gm.h does not declare it) */
struct AIBLD *gm_NearestBuilding(struct AIBLD *b, unsigned kind);
int d3_VecEqual(const struct D3VECTOR *a, const struct D3VECTOR *b, float eps);
float gm_TitlePeriodServed(int n, struct AITIME *out);

/* dcp unit split: the definitions of he the functions of he_b use */
void he_AllocDueIsStart(AIJOB *ev);
int he_PickNearBuilding(AICHAR *c, int n, AIBLD **blds, int *bldId, int *objId);

/* 0x568aa0, ends every started loan event 0x23 (he_EndEventNow) whose partner (AIJOB.loanPartner, the other party's
   netId) is the character c: gm_ReleaseCharacter calls it before the character is released */

void he_EndKind23Events(AICHAR *rec) {
  AICHAR *c = rec;
  AIJOB *e;

  for (e = he_FindEvent(1, 0, 0x23); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) != 0 && e->loanPartner == c->netId)
      he_EndEventNow(e);
  }
}

float gm_MeanLiking(int c, int n, int *ids);

/* 0x568ae0, the allocation handler of the event type 3 (the running income, its run handler 0x568be0): the stock amount +0xb0
   and its float at +0xb4 are the work time of the goods +0xac (ai_Goods), both clocks +0x52 / +0x60 are the start clock +0x44,
   the rate +0xc4 is (gm_MeanLiking (+8, 8, +0x8c) - 0.5) * 0.25 and the counter +0xc8 is 0; every character whose job +0x17c is
   this event joins the group of the building +0xb8; the next run is one minute ahead */

void he_AllocIncomeEvent(AIJOB *e) {
  AIBLD *b;
  AICHAR *rec;
  double d;
  int v;

  v = (int)(&ai_Goods[e->incomeGood])->workTime;
  e->incomeAmount = v;
  e->end = e->start;
  e->incomeAmountF = (float)v;
  e->clock60 = e->start;
  d = gm_MeanLiking(e->chr, 8, e->ids) - 0.5;
  e->incomeCounter = 0;
  e->incomeRate = (float)(d * 0.25);
  b = gm_FindBuildingById(e->incomeBld);
  for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
    if (rec->job == e)
      sv_MoveToGroup(b, 0, rec->id, e);
  }
  gm_AddTime(&e->end, 0, 0, 1);
}
/* 0x568be0, the run handler of the running income event 3 (its alloc handler he_AllocIncomeEvent): without its
   building (incomeBld) every character on the event leaves the group and the event is freed. The building's owner
   counts unless it is the player's character. Stage 0 goes to 1. Stage 1 goes to 2 when no workers are left (the
   words +0x14 / +0x18); else the factor is 1 + 0.01 * the building's skill (gm_BuildingSkill); every 60 minutes
   (incomeCounter) the owner sends his relations to the eight characters ids[] (2 - workRate, unless it is 2) and
   the rate becomes (gm_MeanLiking - 0.5) * 0.25; the minutes since clock60 add to the counter. While the due clock
   is past, the stock incomeAmount loses the work minutes since clock60 times (2 * +0x14 + +0x18) times
   (factor + rate); a used-up stock takes the next batch of the goods (at most the goods' batch) from incomeFrom
   to incomeTo and adds the goods' work time, until it is positive; without the goods left the owner gets the
   news 0x1bb7 ("_NACHRICHTEN_HS_07"), the characters leave the group and the event is freed; clock60 takes the
   due clock, which moves 5 seconds on. Stage 2 goes back to 1 while workers are left, else the characters leave
   the building's group and the event is freed (stage -1 when the building is gone); -1 / -2 free it too */
void he_RunIncomeEvent(AIJOB *ev) {
  AIBLD *bld;
  float factor;
  float amount;
  AIOBJ *from;
  AIOBJ *to;
  char text[0x100];
  AICHAR *owner;
  AIGOOD *good;
  AIOBJ *stock;
  int i;
  int n;

  owner = 0;
  gm_FindById(&bld, 0, 0, ev->incomeBld);
  if (bld == 0) {
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].job == ev)
        sv_MoveToGroup(0, 0, ai_Chars[i].id, 0);
    }
    he_FreeEvent(ev);
    return;
  }
  if (bld->owner != 0xffff && &ai_Chars[bld->owner] != ai_PlayerChar)
    owner = &ai_Chars[bld->owner];
  switch (ev->stage) {
  case 0:
    ev->stage++;
    return;
  case 1:
    if (ev->words14[0] == 0 && ev->words14[1] == 0) {
      ev->stage = 2;
      return;
    }
    gm_FindById(&bld, 0, 0, ev->incomeBld);
    factor = gm_BuildingSkill(bld, 1, 1) * 0.01 + 1.0;
    if (ev->incomeCounter >= 60) {
      for (i = 0; i < 8 && owner != 0; i++) {
        if (ev->ids[i] != -1 && bld->workRate != 2)
          cm_SendRelations(owner->netId, ev->ids[i], 2 - bld->workRate, 0);
      }
      if (owner != 0)
        ev->incomeRate =
            (float)((gm_MeanLiking(owner->id, 8, ev->ids) - 0.5) * 0.25);
      ev->incomeCounter = 0;
    }
    n = gm_WorkMinutesBetween(&ev->clock60, &ai_Time, 0);
    if (n > 0)
      ev->incomeCounter += n;
    factor += ev->incomeRate;
    while (gm_CompareTime(&ev->end, &ai_Time) < 0) {
      good = (&ai_Goods[ev->incomeGood]);
      amount = (float)ev->incomeAmount;
      n = gm_WorkMinutesBetween(&ev->clock60, &ev->end, 0) *
          (ev->words14[0] * 2 + ev->words14[1]);
      ev->incomeAmount = (int)(amount - n * factor);
      while (ev->incomeAmount <= 0) {
        gm_FindById(0, &from, 0, ev->incomeFrom);
        stock = gm_Query(from->list, 1, 0, ev->incomeGood);
        gm_FindById(0, &to, 0, ev->incomeTo);
        if (stock == 0) {
          txt_Format(text, 0x1bb7, ev->incomeGood * 2 + 0x9a8, bld);
          he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, -1, text, 0, 0x5f1,
                                 bld->id, -1, 0, "_NACHRICHTEN_HS_07");
          for (i = 0; i < 768; i++) {
            if (ai_Chars[i].job == ev)
              sv_MoveToGroup(bld, 0, ai_Chars[i].id, 0);
          }
          he_FreeEvent(ev);
          return;
        }
        n = good->batch;
        if (n >= stock->count)
          n = stock->count;
        cm_SendExSellObject(ev->incomeTo, ev->incomeFrom, ev->incomeGood, n,
                            ai_OwnPlayer, 0);
        ev->incomeAmount += good->workTime;
        ev->incomeAmountF = (float)ev->incomeAmount;
      }
      ev->clock60 = ev->end;
      gm_AddTime(&ev->end, 0, 0, 5);
    }
    return;
  case 2:
    if (ev->words14[0] > 0 || ev->words14[1] > 0) {
      ev->stage = 1;
      return;
    }
    gm_FindById(&bld, 0, 0, ev->incomeBld);
    if (bld == 0) {
      ev->stage = -1;
      return;
    }
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].job == ev)
        sv_MoveToGroup(bld, 0, ai_Chars[i].id, 0);
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].job == ev)
        sv_MoveToGroup(0, 0, ai_Chars[i].id, 0);
    }
    he_FreeEvent(ev);
    return;
  default:
    return;
  }
}
/* 0x5690c0, the allocation handler of the production event ("he_AllocProduktion()"): the building (0xbc) and the good (0xac) are taken; both clocks (0x52 / 0x60) are the start clock (0x44), the amount (0xb4 / 0xb8) is the good's work time (its record's 0x22), due 1 unit later; the state 0xc4 = -1 and 0xc8 = 0; every character whose job (0x17c) is this event moves to the building's group; the rate 0xcc = (the owner's mean liking - 0.5) * 0.25 and 0xd4 = 1.0; an unset owner (chr 0xffff) with a found building prints the debug text */

void he_AllocProduktion(AIJOB *ev) {
  AIJOB *p = ev;
  char buf[0x200];
  AIBLD *b;
  AIGOOD *g;
  int o, id;
  AICHAR *rec;
  float v;

  if (ev->chr == 0xffff) {
    o = (int)gm_FindBuildingById(p->productionBld);
    if (o != 0)
      txt_Format(buf, (intptr_t)"he_AllocProduktion(): geb:%G", o);
  }
  b = gm_FindBuildingById(p->productionBld);
  g = ai_Goods;
  id = p->productionGood;
  v = (float)g[id].workTime;
  ev->end = ev->start;
  ev->clock60 = ev->start;
  p->productionAmount = v;
  p->productionAmount2 = v;
  gm_AddTime(&ev->end, 0, 0, 1);
  p->productionSlot = -1;
  p->productionLacking = 0;
  for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
    if (rec->job == ev)
      sv_MoveToGroup(b, 0, rec->id, ev);
  }
  p->productionRate = (gm_MeanLiking(ev->chr, 8, ev->ids) - 0.5) * 0.25;
  p->productionStaff = 1.0f;
}

void sv_CountGroupMembers(struct AIJOB *g);
int he_HasEvent9f(AICHAR *a);

/* 0x569210, the run handler of the production event (he_AllocProduktion; "he_RunProduktion()"): without a character
   it frees itself (the debug text names the building). Stage 1 goes to 2 when no workers are left (the words +0x14 /
   +0x18). A make message sent (slot) is waited for; once it failed (state 2) and a worker is on the event, the master
   is not away (flags1b4 bit 1) and no shortage was reported yet, the owner of kind 6 / 7 gets the news why: the
   store holds the good and has no room for it (0x1bb3, "_NACHRICHTEN_HS_04"), no room at all (0x1bb4, "_HS_05") or
   the inputs were missing (0x1bb2, the shortage news of the building type, cm_SendStates kind 8); the smoke stops.
   Without a pending message the work runs: the factor is 1 + 0.01 * the building's skill, plus the master's skill
   sk81 / 1008 for an owner of kind 6 / 7, halved with flag 0x20 and the item 0x178; every 60 minutes the owner sends
   his relations to the workers ids[], their mean factor (health, skill for the titles 0x1b / 0x1c, the place factor,
   x 1.25 with the item 0x2ba; x 0.9 with an event 0x9f) and the liking rate are taken anew. While the due clock is
   past and the store (kind 0x2a / 0x116) has the inputs (AIGOOD.in / need) and room, the work minutes times
   (1.3 * +0x14 + +0x18) times the rate wear the amount down; every work time used up makes one unit
   (cm_SendMakeGoods); without units and the good no longer in the store, the good is ordered (cm_SendExSellObject).
   A shortage reports as above (once), stops the smoke and waits 5 minutes. Stage 2 goes back to 1 while workers are
   left, else the workers leave the building's group, the smoke stops and the event is freed; -1 / -2 free it
   @deep deep s44: 40 -> 4 ins, size right (3793). Two levers: case 1's no-worker path written out in case
   1 (if (w0 <= 0 && w1 <= 0) { ev->stage++; return; }, no goto work) with case 0 placed before case 2: VC6
   cross-jumps case 0 into case 1's copy (the switch entry +0x87, the stage in eax from the switch); and
   the debug line's buffer is its own char buf[0x200] (the original's only reference to esp+0x534), text is
   char text[0x400]. Left (4 ins): line 'fv = (gm_GetSkill(worker, 1) + 0.5) * fv;' - the original
   schedules mov al,[esi+0x1b4] (the flags1b4 test) and add esp,8 before fadd 0.5 / fmul fv; ours fadd /
   fmul first (c2dag: fadd prio 131072 h=8 above the flag load 106496 h=5; the op=263 node of the
   parenthesised sum). Tried: fv *= .., fv * (..), 0.5f (fpu hunk), (float) cast, 0.5 + .., (double)fv, the
   flag test as != 0 / == 1 / ternary / if-else: none moves it. prior: rebuilt from the whole original
   (frame 0x724: name[MAX_PATH] at 0x20, text[0x600] at 0x124; the case order 1/0/2/-1; txt_Format(text,
   id, bld, good*2+0x9a8); the shortage news chains; the make / order slots; while amount <= 0.0f; the
   minutes product with the call converted in place). 1147 vs 1151 instructions. Left is allocation: VC6
   keeps &ev->clock60 (the CSE, or the clock variable) in ebx where the original keeps it in the stack slot
   0x8 (mov [esp+0x24], eax at +0x79e) and caches the constant 0 in ebx instead (xor ebx, ebx at +0x8cc /
   +0x96b; cmp ax, bx / push ebx / cmp [ebp+0xc8], ebx / mov [esp+0x28], ebx for the qword high half):
   every code hunk from +0x792 to +0xd95 is that (push ebx vs push 0, mov ecx, ebx vs mov edx, [esp+0x18]),
   and the slots hunks follow from it (factor f at 0x8 vs 0xc). The tail hunk: case 1's no-worker path
   shares case 0's stage++ inline in the original (+0x87) and as a tail block in ours (+0xda0), the cause
   of the one switch entry that differs; goto / fall-through spellings gave the same layout (size: 8 of the
   instruction difference are shared / inline tails) */
void he_RunProduktion(AIJOB *ev) {
  AIJOB *p = ev;
  AIBLD *bld;
  AIOBJ *store;
  float f;
  float fv;
  float sum;
  AIBTYPE *bt;
  char name[MAX_PATH];
  char text[0x400];
  char buf[0x200];
  AICHAR *rec;
  AICHAR *worker;
  AICHAR *master;
  AIOBJ *mainObj;
  AIOBJ *o;
  AIJOB *box;
  AIGOOD *g;
  int news;
  int n;
  int i;
  int units;

  name[0] = 0;
  if (ev->chr == 0xffff) {
    bld = gm_FindBuildingById(p->productionBld);
    if (bld != 0)
      txt_Format(buf, (intptr_t)"he_RunProduktion(): geb:%G", bld);
    he_FreeEvent(ev);
    return;
  }
  switch (ev->stage) {
  case 1:
    if (ev->words14[0] <= 0 && ev->words14[1] <= 0) {
      ev->stage++; /* no workers left: on to stage 2 */
      return;
    }
    if (p->productionSlot != -1) {
      if (cm_GetSlotState(p->productionSlot) == 0)
        return;
      gm_FindById(&bld, 0, 0, p->productionBld);
      if (bld == 0) {
        ev->stage = -1;
        return;
      }
      bt = &ai_BTypes[bld->type];
      if (cm_GetSlotState(p->productionSlot) == 2) {
        worker = 0;
        name[0] = 0;
        master = gm_FindCharacterByMaster(bld);
        for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
          if (rec->job == ev)
            worker = rec;
        }
        if (worker != 0 && (master == 0 || (master->flags1b4 & 1) == 0) &&
            p->productionLacking == 0) {
          gm_FindById(0, &store, 0, p->productionStore);
          mainObj = gm_BuildingMainObject(bld);
          if (gm_Query(store->list, 1, 0, p->productionGood) != 0 &&
              gm_FreeCapacity(store, p->productionGood, 1) == 0) {
            txt_Format(text, 0x1bb3, bld, p->productionGood * 2 + 0x9a8);
            strcpy(name, "_NACHRICHTEN_HS_04");
          } else if (gm_FreeCapacity(store, p->productionGood, 1) == 0) {
            txt_Format(text, 0x1bb4, bld, p->productionGood * 2 + 0x9a8);
            strcpy(name, "_NACHRICHTEN_HS_05");
          } else {
            if (cm_SendStates[p->productionSlot].kind != 8)
              goto wait;
            txt_Format(text, 0x1bb2, bld, p->productionGood * 2 + 0x9a8);
            if (bt->kind == 7)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_01");
            else if (bt->kind == 8)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_03");
            else if (bt->kind == 0xb)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_05");
            else if (bt->kind == 0xc)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_07");
            else if (bt->kind == 0xd)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_09");
            else if (bt->kind == 0xe)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_11");
            else if (bt->kind == 0x12)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_13");
            else if (bt->kind == 0x14)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_15");
            else if (bt->kind == 0x15)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_17");
            else if (bt->kind == 0x16)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_19");
            else if (bt->kind == 0x1e)
              strcpy(name, "_NACHRICHTEN_DOMIZIL_02");
            else if (bt->kind == 0x20 || bt->kind == 0x1f || bt->kind == 0x1d)
              strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_20");
          }
          if (ai_Chars[bld->owner].kind == 6 ||
              ai_Chars[bld->owner].kind == 7) {
            news = 0x5f1;
            master = gm_FindCharacterByMaster(bld);
            if (master != 0 && (master->flags1b4 & 1))
              news = 0x60d;
            if (name[0] != 0)
              he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, ev->id, text,
                                     0, news, bld->id, mainObj->objId, 0, name);
            else
              he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, ev->id, text,
                                     0, news, bld->id, mainObj->objId, 0, 0);
          }
          if (bld != 0 && bld->smokeEffect != -1)
            cm_SendUpdateSmoke(bld->id);
          p->productionLacking = 1;
        }
      wait:
        p->productionSlot = -1;
        gm_AddTime(&ev->end, 0, 5, 0);
        return;
      }
    }
    gm_FindById(&bld, 0, 0, p->productionBld);
    if (bld == 0) {
      ev->stage = -1;
      return;
    }
    if (bld->smokeEffect == -1)
      cm_SendUpdateSmoke(bld->id);
    bt = &ai_BTypes[bld->type];
    f = gm_BuildingSkill(bld, 1, 1) * 0.01 + 1.0;
    master = gm_FindCharacterByMaster(bld);
    if (master == 0)
      master = &ai_Chars[bld->owner];
    f += master->kind == 6 || master->kind == 7
             ? (float)(master->sk81 * 0.000992063492063492)
             : 0.0f;
    if ((bld->flags5a & 0x20) && ai_BuildingHasItem(bld, 0x178))
      f = f * 0.5;
    if (p->productionCounter >= 60) {
      n = 0;
      sum = 0;
      for (i = 0; i < 8; i++) {
        if (ev->ids[i] == -1)
          continue;
        if (bld->workRate != 2)
          cm_SendRelations(ai_Chars[bld->owner].netId, ev->ids[i],
                           2 - bld->workRate, 0);
        worker = gm_FindChar(ev->ids[i]);
        if (worker != 0) {
          fv = gm_HealthRatio(worker);
          if (worker->title == 0x1b || worker->title == 0x1c) {
            fv = (gm_GetSkill(worker, 1) + 0.5) * fv;
            if (worker->flags1b4 & 1)
              fv = 0.01f;
          }
          if (worker->flags1cc & 4)
            fv = ahm_PlaceFactor(worker, p->productionGood) * fv;
          sum +=
              ai_InventoryHas(&ai_Chars[bld->owner], 0x2ba) ? fv * 1.25f : fv;
        }
        n++;
      }
      if (n != 0) {
        p->productionStaff = sum / n;
        if (he_HasEvent9f(&ai_Chars[bld->owner]))
          p->productionStaff = p->productionStaff * 0.9f;
      }
      sv_CountGroupMembers(ev);
      p->productionRate = (gm_MeanLiking(bld->owner, 8, ev->ids) - 0.5) * 0.25;
      p->productionCounter = 0;
    }
    n = gm_WorkMinutesBetween(&ev->clock60, &ai_Time, 0);
    if (n > 0)
      p->productionCounter += n;
    f = ((bld->flags5aw & 0x1000 ? f + 0.1f : f) + p->productionRate +
         (bld->workRate - 2) * 0.1) *
        p->productionStaff;
    if (gm_FindById(0, &store, 0, p->productionStore) == 0 ||
        (store->type != 0x2a && store->type != 0x116)) {
      he_FreeEvent(ev);
      return;
    }
    if (gm_Query(store->list, 1, 0, p->productionGood) != 0 &&
        gm_FreeCapacity(store, p->productionGood, 1) == 0) {
      txt_Format(text, 0x1bb3, bld, p->productionGood * 2 + 0x9a8);
      strcpy(name, "_NACHRICHTEN_HS_04");
    } else if (gm_FreeCapacity(store, p->productionGood, 1) == 0) {
      txt_Format(text, 0x1bb4, bld, p->productionGood * 2 + 0x9a8);
      strcpy(name, "_NACHRICHTEN_HS_05");
    } else {
      g = (&ai_Goods[p->productionGood]);
      for (i = 0; i < 4; i++) {
        if (g->in[i] != 0) {
          o = gm_Query(store->list, 1, 0, g->in[i]);
          if (o == 0 || gm_ListAmount(store, o) < g->need[i])
            goto lacking;
        }
      }
      if (p->productionLacking != 0) {
        box = he_FindEvent(2, 0, 0x11, 3, ev->id);
        if (box != 0)
          he_FreeEvent(box);
        p->productionLacking = 0;
        if (ev->gfx != 0) {
          he_FreeGfxInfo(ev->gfx);
          ev->gfx = 0;
        }
        ev->clock60 = ev->end;
      }
      while (gm_CompareTime(&ev->end, &ai_Time) < 0) {
        g = (&ai_Goods[p->productionGood]);
        p->productionAmount = p->productionAmount -
                              gm_WorkMinutesBetween(&ev->clock60, &ev->end, 0) *
                                  (ev->words14[0] * 1.3f + ev->words14[1]) * f;
        units = 0;
        while (p->productionAmount <= 0.0f) {
          p->productionAmount = g->workTime + p->productionAmount;
          p->productionAmount2 = p->productionAmount;
          units++;
        }
        if (units != 0)
          p->productionSlot =
              cm_SendMakeGoods(p->productionStore, p->productionGood, units);
        else if (p->productionSlot == -1 &&
                 gm_Query(store->list, 1, 0, p->productionGood) == 0)
          p->productionSlot = cm_SendExSellObject(
              store->objId, -1, p->productionGood, 0, ai_OwnPlayer, 0);
        ev->clock60 = ev->end;
        gm_AddTime(&ev->end, 0, 1, 0);
      }
      return;
    lacking:
      txt_Format(text, 0x1bb2, bld, p->productionGood * 2 + 0x9a8);
      if (bt->kind == 7)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_01");
      else if (bt->kind == 8)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_03");
      else if (bt->kind == 0xb)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_05");
      else if (bt->kind == 0xc)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_07");
      else if (bt->kind == 0xd)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_09");
      else if (bt->kind == 0xe)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_11");
      else if (bt->kind == 0x12)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_13");
      else if (bt->kind == 0x14)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_15");
      else if (bt->kind == 0x15)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_17");
      else if (bt->kind == 0x16)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_19");
      else if (bt->kind == 0x20 || bt->kind == 0x1f || bt->kind == 0x1d)
        strcpy(name, "_NACHRICHTEN_ROHSTOFFMANGEL_HS_20");
    }
    mainObj = gm_BuildingMainObject(bld);
    if (p->productionLacking == 0 &&
        (ai_Chars[bld->owner].kind == 6 || ai_Chars[bld->owner].kind == 7)) {
      news = 0x5f1;
      master = gm_FindCharacterByMaster(bld);
      if (master != 0 && (master->flags1b4 & 1))
        news = 0x60d;
      if (mainObj != 0)
        he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, ev->id, text, 0,
                               news, bld->id, mainObj->objId, 0, name);
      else
        he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, ev->id, text, 0,
                               news, bld->id, -1, 0, name);
    }
    if (bld != 0 && p->productionLacking == 0 && bld->smokeEffect != -1)
      cm_SendUpdateSmoke(bld->id);
    p->productionLacking = 1;
    p->productionSlot = -1;
    gm_AddTime(&ev->end, 0, 5, 0);
    ev->clock60 = ev->end;
    return;
  case 0:
    ev->stage++;
    return;
  case 2:
    if (ev->words14[0] > 0 || ev->words14[1] > 0) {
      ev->stage = 1;
      return;
    }
    gm_FindById(&bld, 0, 0, p->productionBld);
    if (bld == 0) {
      ev->stage = -1;
      return;
    }
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(bld, 0, rec->id, 0);
    }
    if (bld != 0)
      cm_SendUpdateSmoke(bld->id);
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    gm_FindById(&bld, 0, 0, p->productionBld);
    if (bld != 0)
      cm_SendUpdateSmoke(bld->id);
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(0, 0, rec->id, 0);
    }
    he_FreeEvent(ev);
    return;
  default:
    return;
  }
}
/* 0x56a100, the allocation handler of a search event 8 / 9: both clocks (end and clock60) start at the event's
   start clock, and the end is a random 0 .. 59 minutes later (kind 4) */

void he_AllocSearchEvent(AIJOB *e) {
  e->end = e->start;
  e->clock60 = e->start;
  gm_AddTime(&e->end, 4, util_Random(0x3c), 0);
}
/* 0x56a170, the run handler of the search event 8 ("Suchen", he_AllocSearchEvent): stage 0 goes to 1; stage 1 frees
   the event when no workers are left (the words +0x14 / +0x18), else waits for the due clock; then, with its building
   (else stage -1), the workers find (random(batch * 40) + batch * 40) times their number of the good (AIGOOD.batch),
   handed to the event's store (cm_SendExSellObject from nobody), the building's owner gets the news 0x1bb8
   ("_NACHRICHTEN_HS_08"), the workers join the building's group and the event is freed; -1 / -2 send the workers off
   and free it */
void he_RunSearchEvent(AIJOB *ev) {
  AIJOB *s = ev;
  AIBLD *bld;
  char text[0x200];
  AIGOOD *g;
  AICHAR *rec;
  int amount;

  switch (ev->stage) {
  case 0:
    ev->stage++;
    return;
  case 1:
    if (ev->words14[0] == 0 && ev->words14[1] == 0)
      break;
    if (gm_CompareTime(&ev->end, &ai_Time) >= 0)
      return;
    gm_FindById(&bld, 0, 0, s->searchBld);
    if (bld == 0) {
      ev->stage = -1;
      return;
    }
    g = (&ai_Goods[s->searchGood]);
    amount = (util_Random(g->batch * 40) + g->batch * 40) *
             (ev->words14[0] + ev->words14[1]);
    cm_SendExSellObject(s->searchStore, -1, s->searchGood, amount, ai_OwnPlayer,
                        0);
    txt_Format(text, 0x1bb8, s->searchGood * 2 + 0x9a8, bld, amount);
    he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5f1,
                           bld->id, -1, 0, "_NACHRICHTEN_HS_08");
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(bld, 0, rec->id, 0);
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(0, 0, rec->id, 0);
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x56a360, the allocation handler of the search event 9: both clocks (end and clock60) start at the event's start
   clock, and the end is 7 hours and a random 30 .. 59 minutes later */

void he_AllocSearch9(AIJOB *e) {
  e->end = e->start;
  e->clock60 = e->start;
  gm_AddTime(&e->end, 7, util_Random(0x1e) + 0x1e, 0);
}

/* 0x56a3d0, the run handler of the search event 9 (the second "Suchen" activity, he_AllocSearch9): stage 0 goes to 1;
   stage 1 frees the event when no workers are left (the words +0x14 / +0x18), else waits for the due clock; then,
   with its building (else stage -1), the first good of the kind 0x17 with a count of 1 in the source object's list
   (gm_Query key 4) is found: one more of it goes to the source, three of every good the building can make
   (gm_BuildKindObjects, not of the kind 0x17) whose other inputs the source holds at least twice, and
   (random(batch * 30) + batch * 30) times the workers of it to the event's store; the owner gets the news 0x1bb8
   ("_NACHRICHTEN_HS_08"). The workers join the building's group and the event is freed; -1 / -2 send the
   workers off and free it */
void he_RunSearch9(AIJOB *ev) {
  AIJOB *s = ev;
  AIBLD *bld;
  AIOBJ *src;
  int i;
  char text[0x200];
  AIOBJ *found;
  AIOBJ *o;
  AIGOOD *g;
  AICHAR *rec;
  int j;
  int ok;
  int amount;

  switch (ev->stage) {
  case 0:
    ev->stage++;
    return;
  case 1:
    if (ev->words14[0] == 0 && ev->words14[1] == 0)
      break;
    if (gm_CompareTime(&ev->end, &ai_Time) >= 0)
      return;
    gm_FindById(&bld, 0, 0, s->search9Bld);
    if (bld == 0) {
      ev->stage = -1;
      return;
    }
    gm_FindById(0, &src, 0, s->search9Source);
    for (found = gm_Query(src->list, 1, 4, 0x17); found != 0;
         found = gm_QueryNext()) {
      if (found->count == 1)
        break;
    }
    if (found != 0) {
      cm_SendExSellObject(src->objId, -1, found->id, 1, ai_OwnPlayer, 0);
      gm_BuildKindObjects(bld);
      for (i = 0; i < gm_KindObjCount; i++) {
        g = (&ai_Goods[gm_KindObjs[i]]);
        if (g->type == 0x17)
          continue;
        ok = 1;
        for (j = 0; ok && j < 4; j++) {
          if (g->in[j] != 0 && g->in[j] != found->id) {
            o = gm_Query(src->list, 1, 0, g->in[j]);
            if (o == 0 || o->count < 2)
              ok = 0;
          }
        }
        if (ok)
          cm_SendExSellObject(src->objId, -1, gm_KindObjs[i], 3, ai_OwnPlayer,
                              0);
      }
      g = (&ai_Goods[found->id]);
      amount = (util_Random(g->batch * 30) + g->batch * 30) *
               (ev->words14[0] + ev->words14[1]);
      cm_SendExSellObject(s->search9Store, -1, found->id, amount, ai_OwnPlayer,
                          0);
      txt_Format(text, 0x1bb8, found->id * 2 + 0x9a8, bld, amount);
      he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5f1,
                             bld->id, -1, 0, "_NACHRICHTEN_HS_08");
    }
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(bld, 0, rec->id, 0);
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    for (rec = ai_Chars; (intptr_t)rec < (intptr_t)&ai_Chars[768]; rec++) {
      if (rec->job == ev)
        sv_MoveToGroup(0, 0, rec->id, 0);
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x56a710, the run handler of the new-occurrence debug event 0xa ("HE_NEUE_VORKOMMEN_SUCHEN_MSG"): stage 0 opens
   the message panel "Misc\EventMessagebox" (he_OpenEventSlot, its slot at +0x74), shows the bug text with the name of
   the good and goes to stage 1; stage 1 frees the event once that panel's window was clicked on (d2_ClickedForm, the
   id 0); -1 / -2 release the slot and free it */

void he_RunNewOccurrenceMsg(AIJOB *ev) {
  AIJOB *v = ev;
  int good;

  switch (ev->stage) {
  case -2:
  case -1:
    he_ReleaseSlot(ev);
    he_FreeEvent(ev);
    return;
  case 0:
    good = v->occurrenceGood;
    he_OpenEventSlot(ev, 0, 0, "Misc\\EventMessagebox", 0x5f2);
    d2_SetForm(ev->slot->win, 0);
    io_PrintText((intptr_t)"HE_NEUE_VORKOMMEN_SUCHEN_MSG: Ich bin ein Bug !!! "
                           "%s gefunden!!",
                 good * 2 + 0x9a8);
    ev->stage++;
    return;
  case 1:
    if (d2_ClickedForm == ev->slot->win && d2_ClickedId != -1 &&
        d2_ClickedId == 0) {
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
    }
    return;
  }
}

/* 0x56a7b0, the allocation handler of the trade event 0xb: when another event of the same kind already works for the same good (0xac) of another sender (0x10) this record is freed; else both clocks (0x52 / 0x60) are the start clock (0x44), due 1 unit later, the handles 0xe8 / 0xec = -1, and a move-goods message 0xf (AIMSG: type 0xf, to the character chr, fromId -1, the clock, the good (arg[0]), the buyer (from, arg[1]), the building (0xb0, arg[2]), the event id (0xa0)) is posted unless the flag 0xf1 is set (then due 1 + 0x1e later); modes 0xf0 = 4 when the character (0xb4) exists */
void he_AllocTrade(AIJOB *ev) {
  AIJOB *p = ev;
  AIMSG msg;
  AIJOB *e2;

  for (e2 = he_FindEvent(2, 0, 0xb, 3, ev->from); e2 != 0;
       e2 = he_NextEvent()) {
    if (e2->cart == p->cart && e2->id != ev->id) {
      he_FreeEvent(ev);
      return;
    }
  }
  ev->end = ev->start;
  ev->clock60 = ev->start;
  p->tradeMoveSlot = -1;
  p->tradeMsgSlot = -1;
  gm_AddTime(&ev->end, 0, 1, 0);
  memset(&msg, 0, sizeof(msg));
  msg.type = 0xf;
  msg.fromId = -1;
  msg.to = ai_Chars[ev->chr].netId;
  msg.flags = 2;
  msg.time = ev->start;
  msg.arg[0] = p->cart;
  msg.arg[1] = ev->from;
  msg.arg[2] = p->tradeBld;
  msg.jobId = ev->id;
  if (gm_FindObjectInst(p->cart) != 0) {
    if (ev->flags != 0)
      gm_AddTime(&ev->end, 1, 0x1e, 0);
    else
      p->tradeMsgSlot = cm_SendLongMessage(&msg);
  } else
    he_FreeEvent(ev);
  ev->modes = 0;
  if (gm_FindChar(p->tradeChr) != 0)
    ev->modes = 4;
}

/* 0x56a960, the run handler of the trade event 0xb (he_AllocTrade): a cart (t->cart) of the character t->tradeChr trades
   at the building t->tradeBld. Stage -2 restarts it for the player's character. While its move or message send is still
   open it waits a minute. Without the cart or the building it is freed; a transport event 0xf of the character
   for the same cart makes it wait 5 minutes (going to this building) or frees it. A cart not at the building
   (ai_CartAtBuilding, unless deferred) frees it. With nothing to sell or buy in its slots (at most the cart
   object's slot count, 3) the cargo of the cart object (0x1dd) goes into the building's store (kind 0x2a, else
   0x116). Else the sell slots for this building sell their goods: what the store has room for at 0.9 of the
   price (booked to the character's money +0x1b8), the rest at 0.8 to nobody; or the buy slots buy up to their
   amount of what the store (the market object of a market building) holds beyond its reserve, at 1.1 of the
   price (a market) or the building's price factor, as far as the money of the character and its master reach
   ("Meister %s (%s) kauft ..."); a buy that found nothing is tried again every half hour up to t->tradeTries times
   (before 20:00). Then the cart moves on to the building of the first slot left, else home (ev->from): the
   message 0xf, unless that is this building (5 minutes) or the trade is deferred (1 1/2 hours)
   @original the exits share one free (done) and one 5-minute wait (wait) by goto, the transport loop tests e == 0
   inside its body and the cart / building tests are two ifs: that flow graph lays the transport-match block out
   last, in front of the wait, as the original does */
void he_RunTrade(AIJOB *ev) {
  AIJOB *t = ev;
  AIBLD *bld;
  int left;
  int n;
  AIOBJ *store;
  AIOBJ *cart;
  AICHAR *chr;
  int price;
  AIOBJ *cargo;
  int slots;
  int flags;
  AIMSG m;
  char buf[0x80];
  AIJOB *e;
  AIOBJ *g;
  int i;
  int found;

  n = 0;
  flags = left = 0;
  cart = 0;
  bld = 0;
  chr = 0;
  if (ev->stage == -2) {
    ev->stage = 0;
    he_SetEventChar(ev, ai_PlayerChar->id);
  }
  if (t->tradeMoveSlot != -1) {
    if (cm_GetSlotState(t->tradeMoveSlot) == 0) {
      gm_AddTime(&ev->end, 0, 1, 0);
      return;
    }
    t->tradeMoveSlot = -1;
  }
  if (t->tradeMsgSlot != -1) {
    if (cm_GetSlotState(t->tradeMsgSlot) == 0) {
      gm_AddTime(&ev->end, 0, 1, 0);
      return;
    }
    t->tradeMsgSlot = -1;
  }
  gm_FindById(0, &cart, 0, t->cart);
  gm_FindById(&bld, 0, 0, t->tradeBld);
  gm_FindById(0, 0, &chr, t->tradeChr);
  if (cart == 0)
    goto done;
  if (bld == 0)
    goto done;
  for (e = he_FindEvent(2, 0, 0xf, 2, ev->chr);; e = he_NextEvent()) {
    if (e == 0)
      break;
    if (e->transportCart == t->cart)
      goto moving;
  }
  if (t->tradeDeferred == 0 && ai_CartAtBuilding(bld, cart) == 0) {
    ai_CartAtBuilding(bld, cart);
    he_FreeEvent(ev);
    return;
  }
  cargo = gm_Query(cart->list, 1, 0, 0x1dd);
  slots = cargo->lvl1c < 3 ? cargo->lvl1c : 3;
  found = 0;
  for (i = 0; found == 0 && i < slots; i++) {
    if (t->tradeSell[i] != 0 || t->tradeBuy[i] != 0)
      found = 1;
  }
  if (found == 0) {
    if ((store = gm_Query(bld->objList, 2, 6, 0, 0x2a)) != 0) {
      for (g = gm_Query(cargo->list, 1, 5); g != 0; g = gm_QueryNext())
        t->tradeMoveSlot = cm_SendExSellObject(
            store->objId, cargo->objId, g->id, g->count, ai_OwnPlayer, 0);
    } else if ((store = gm_Query(bld->objList, 2, 6, 0, 0x116)) != 0) {
      for (g = gm_Query(cargo->list, 1, 5); g != 0; g = gm_QueryNext())
        t->tradeMoveSlot = cm_SendExSellObject(
            store->objId, cargo->objId, g->id, g->count, ai_OwnPlayer, 0);
    }
    if (t->tradeMoveSlot == -1)
      goto done;
    goto wait;
  }
  found = 0;
  for (i = 0; found == 0 && i < slots; i++) {
    if (t->tradeSell[i] != 0)
      found = 1;
  }
  if (found != 0) {
    for (i = 0; i < slots; i++) {
      if (t->tradeSell[i] != 0 && t->tradeSellBld[i] == bld->id) {
        g = gm_Query(cargo->list, 1, 0, t->tradeSell[i]);
        if (g != 0) {
          if (ai_BTypes[bld->type].kind == 0xa)
            store = gm_FindMarketObject(t->tradeSell[i]);
          else if ((store = gm_Query(bld->objList, 2, 6, 0, 0x2a)) == 0)
            store = gm_Query(bld->objList, 2, 6, 0, 0x116);
          if (store != 0) {
            int have, put, price;

            have = gm_ListAmount(cargo, g);
            put = gm_FreeCapacity(store, g->id, have);
            price = (int)(gm_GoodsPrice(g->id, ai_OwnPlayer) * 0.9);
            if (have < put)
              put = have;
            cm_SendExSellObject(store->objId, cargo->objId, g->id, put,
                                ai_OwnPlayer, price);
            if (chr != 0)
              chr->budget += price * put;
            if ((have -= put) != 0)
              t->tradeMoveSlot = cm_SendExSellObject(
                  -1, cargo->objId, g->id, have, ai_OwnPlayer,
                  (int)(gm_GoodsPrice(g->id, ai_OwnPlayer) * 0.8));
          }
        }
        t->tradeSell[i] = 0;
        t->tradeSellBld[i] = -1;
      }
    }
  } else {
    if (chr != 0 && chr->bld != 0) {
      left = gm_CharCurrency(&ai_Chars[chr->bld->owner], ai_OwnPlayer);
      if (left >= chr->budget)
        left = chr->budget;
    }
    for (i = 0; i < slots; i++) {
      if (t->tradeBuy[i] != 0 && t->tradeBuyBld[i] == bld->id) {
        if (ai_BTypes[bld->type].kind == 0xa)
          store = gm_FindMarketObject(t->tradeBuy[i]);
        else if ((store = gm_Query(bld->objList, 2, 6, 0, 0x2a)) == 0)
          store = gm_Query(bld->objList, 2, 6, 0, 0x116);
        if (store != 0) {
          g = gm_Query(store->list, 1, 0, t->tradeBuy[i]);
          if (g == 0)
            continue;
          if (ai_BTypes[bld->type].kind == 0xa)
            price = (int)(gm_GoodsPrice(g->id, ai_OwnPlayer) * 1.1);
          else
            price =
                (int)(gm_GoodsPrice(g->id, ai_OwnPlayer) * bld->priceFactor);
          n = min(t->tradeBuyAmount[i],
                  gm_ListAmount(store, g) -
                      ((unsigned)gm_ListStock(store, g->id) * g->reserve >> 2));
          n = min(n, left / price);
          n = n < 0 ? 0 : n;
          if (n != 0)
            t->tradeMoveSlot = cm_SendExSellObject(
                cargo->objId, store->objId, g->id, n, ai_OwnPlayer, price);
          if (chr != 0 && chr->bld != 0)
            sprintf(buf,
                    "Meister %s (%s) kauft f\xfcr %li Credits (hat %li) %li "
                    "Einheiten %s",
                    chr->name, chr->bld->name, price * n, left, n,
                    (&ai_Goods[g->id])->name);
          left -= price * n;
          if (chr != 0)
            chr->budget -= price * n;
        }
        if (n == 0 && t->tradeTries != 0) {
          flags |= 1;
        } else {
          t->tradeBuy[i] = 0;
          t->tradeBuyBld[i] = -1;
        }
      }
    }
  }
  if (t->tradeTries != 0 && flags != 0) {
    if (ai_Time.hour < 20) {
      gm_AddTime(&ev->end, 0, 30, 0);
      t->tradeTries--;
    } else {
      gm_AddTime(&ev->end, 0, 5, 0);
      t->tradeTries = 0;
    }
    return;
  }
  t->tradeBld = -1;
  for (i = 0; t->tradeBld == -1 && i < slots; i++) {
    if (t->tradeSell[i] != 0)
      t->tradeBld = t->tradeSellBld[i];
  }
  for (i = 0; t->tradeBld == -1 && i < slots; i++) {
    if (t->tradeBuy[i] != 0)
      t->tradeBld = t->tradeBuyBld[i];
  }
  if (t->tradeBld == -1) {
    AIBLD *home;

    gm_FindById(&home, 0, 0, ev->from);
    t->tradeBld = home->id;
  }
  if (t->tradeDeferred != 0) {
    gm_AddTime(&ev->end, 1, 30, 0);
    return;
  }
  memset(&m, 0, sizeof(m));
  m.type = 0xf;
  m.fromId = -1;
  m.flags = 2;
  m.to = ai_Chars[ev->chr].netId;
  m.time = ai_Time;
  m.car = cart->objId;
  m.n = bld->id;
  m.ch = t->tradeBld;
  m.jobId = ev->id;
  if (m.n == m.ch) {
    gm_AddTime(&ev->end, 0, 5, 0);
    return;
  }
  t->tradeMsgSlot = cm_SendLongMessage(&m);
  gm_AddTime(&ev->end, 0, 10, 0);
  return;
moving:
  if (e->transportGoal == t->tradeBld)
    goto wait;
  goto done;
wait:
  gm_AddTime(&ev->end, 0, 5, 0);
  return;
done:
  he_FreeEvent(ev);
}
/* 0x56b380, the allocation handler of the research event 0xc (he_RunResearch): both clocks (end and clock60) start
   at the event's start clock, the end is one minute later, and the order's countdown words (wbc, limit, rounds)
   are cleared */

void he_AllocResearch(AIJOB *ev) {
  AIJOB *r = ev;

  ev->end = ev->start;
  ev->clock60 = ev->start;
  gm_AddTime(&ev->end, 0, 1, 0);
  r->researchWbc = 0;
  r->researchLimit = 0;
  r->researchRounds = 0;
}

void init_HookObject(struct D3OBJECT *o, void *p, int kind);

/* 0x56b3f0, the run handler of the research event 0xc (AIJOB.research*): stage 0, once due, orders the good it
   researches (cm_SendExSellObject: the building +0xac as buyer, the good +0xb4, one piece) and keeps the send
   slot (+0xc8); stage 1 waits for that slot (cm_GetSlotState): an error (2) frees the event, else the objId of
   the object the order made (+0xb8, the reply's AIOBJ.objId) is kept and 0x20 rounds (+0xc0 / +0xc4) are
   counted from now; stage 2 looks the object up each minute (gm_FindById) and at the end of the countdown hooks
   its scene object into the building (init_HookObject) and frees the event */
void he_RunResearch(AIJOB *e) {
  AIJOB *r = e;
  AIOBJ *o;

  switch (e->stage) {
  case 0:
    if (gm_CompareTime(&e->end, &ai_Time) > 0)
      return;
    r->researchSlot = cm_SendExSellObject(r->researchBuyer, -1, r->researchGood,
                                          1, ai_OwnPlayer, 0);
    e->stage++;
    return;
  case 1:
    if (cm_GetSlotState(r->researchSlot) == 0)
      return;
    if (cm_GetSlotState(r->researchSlot) == 2)
      goto done;
    o = (AIOBJ *)cm_GetSlotValue(r->researchSlot);
    r->researchObjId = o->objId;
    r->researchLimit = 0x20;
    r->researchRounds = 0;
    gm_AddTime(&e->end, 0, 1, 0);
    e->stage++;
    return;
  case 2:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    do {
      gm_FindById(0, &o, 0, r->researchObjId);
      gm_AddTime(&e->end, 0, 1, 0);
      if (r->researchRounds > r->researchLimit) {
        init_HookObject(o->obj, o, 1);
        he_FreeEvent(e);
        return;
      }
    } while (gm_CompareTime(&e->end, &ai_Time) < 0);
    return;
  case -2:
  case -1:
    goto done;
  }
  return;
done:
  he_FreeEvent(e);
}

struct D3OBJECT *
ai_FindNearestObject(float *ref, struct D3OBJECT **list); /* 0x58fe10 (lc.c) */

/* 0x56b570, "he_AllocGebaeudeBauen", the alloc of an event of the type 0xd (when another one of the type is still
   below the stage 5 the record is freed): both clocks (end / clock60) = the start clock, due now + 1, workTotal /
   argc8 = 0; the name of the building type (bldType) is looked up (ai_BuildingName into buf) and its plots are
   searched in the scene 0 (ai_FindBauplaetze into tab), each checked against the position pos (ai_FindNearestObject);
   without plots or with a miss the record is freed, else the error text is formatted into buf and exSlot = -1 */
void he_AllocGebaeudeBauen(AIJOB *e) {
  AIJOB *b = e;
  char buf[0x80];
  D3OBJECT *tab[0x100];
  AIJOB *e2;
  int n, i, scene;

  for (e2 = he_FindEvent(1, 0, 0xd); e2 != 0; e2 = he_NextEvent()) {
    if (e2 != e && e2->stage < 5)
      goto done;
  }
  e->end = e->start;
  e->clock60 = e->start;
  gm_AddTime(&e->end, 0, 1, 0);
  e->workTotal = 0;
  e->argc8 = 0;
  if (ai_BuildingName(b->buildBldType, buf) == 0)
    goto done;
  scene = d3_CurrentScene;
  memset(tab, 0, sizeof(tab));
  d3if_SelectScene(0, 1);
  n = ai_FindBauplaetze(buf, tab);
  if (n == 0) {
    d3if_SelectScene(scene, 1);
    he_FreeEvent(e);
    return;
  }
  for (i = 0; i < n; i++) {
    if (ai_FindNearestObject(b->buildPos, tab) == 0) {
      he_FreeEvent(e);
      d3if_SelectScene(scene, 1);
      return;
    }
  }
  txt_Format(buf, (intptr_t)"he_AllocGebaeudeBauen: %1N1", e->chr);
  d3if_SelectScene(scene, 1);
  e->exSlot = -1;
  return;
done:
  he_FreeEvent(e);
}
/* 0x56b700, the object callback of the building event 0xd (o: its pos +0x4c and rotation +0x84): places the object
   at its position with its rotation lifted by 1.47 (d3t_PlaceObjectV, the kind 0x46) and counts the event's
   placements (+0xd0) down */
void he_PlaceGebaeudeObject(struct D3OBJECT *o, AIJOB *ev) {
  D3VECTOR t;

  t.x = o->rotation.x + 1.47;
  t.y = o->rotation.y;
  t.z = o->rotation.z;
  d3t_PlaceObjectV(o, &o->pos, &t, 0x46, 0x20);
  ev->buildCount -= 1;
}
/* 0x56b750, scene callback: appends the object o to the list (0x40 entries, the count at +0x104); true while there is room */

char he_CollectChild(int o, int *list) {
  list[list[0x41] + 1] = o;
  list[0x41]++;
  return list[0x41] < 0x40;
}

/* 0x56b780, shows the construction stage of the building event ev on its scene object "he_<id>" (in the default
   scene, the current one restored at the end): not started (stage -1) every child (he_CollectChild) becomes a kind 5
   object out of the quad tree and the tree is hidden; below the last stage each child is shown or hidden by the
   numbers its name ends in ("..._n": from stage n on, "..._n1_n2": for the stages n2 .. n1); past the last stage
   the building's own object shows and the construction object is deleted */
void he_ShowConstruction(AIJOB *ev) {
  AIJOB *c = ev;
  int i;
  int scene;
  char digits[0x10];
  int nums[8];
  HECHILDLIST list;
  char part[0x80];
  char name[0x100];
  D3OBJECT *obj;
  D3OBJECT *o;
  AIBLD *bld;
  char *p;
  int n;

  scene = d3_CurrentScene;
  d3if_SelectScene(0, 1);
  sprintf(name, "he_%i", ev->id);
  obj = d3_FindObject(0, 0x1c0, 0, name);
  if (c->constructStage == -1 && obj != 0) {
    list.count = 0;
    list.root = obj;
    d3_ForEachObject(d3_DefaultScene, obj, 0x2c0, (D3OBJECTCB)he_CollectChild,
                     &list);
    for (i = 0; i < list.count; i++) {
      o = list.items[i];
      if (o->kind != 5 || (o->flags & 4)) {
        o->kind = 5;
        if ((list.items[i]->flags & 4) && d3_QuadTree != 0)
          d3q_RemoveObject(list.items[i], d3_QuadTree);
        list.items[i]->flags &= ~4;
      }
    }
    d3if_ShowTree(obj, 0);
  } else if (c->constructStage < c->constructStages && obj != 0) {
    list.count = 0;
    list.root = obj;
    d3_ForEachObject(d3_DefaultScene, obj, 0x2c0, (D3OBJECTCB)he_CollectChild,
                     &list);
    for (i = 0; i < list.count; i++) {
      o = list.items[i];
      if (o->kind != 5 || (o->flags & 4)) {
        if ((o->flags & 4) && d3_QuadTree != 0)
          d3q_RemoveObject(o, d3_QuadTree);
        list.items[i]->kind = 5;
        list.items[i]->flags &= ~4;
      }
      n = 0;
      list.items[i]->mask = 0;
      strcpy(part, list.items[i]->name);
      for (p = strrchr(part, '_'); p != 0 && n < 2; p = strrchr(part, '_')) {
        strncpy(digits, p + 1, 2);
        digits[2] = 0;
        if (isdigit(digits[0]))
          nums[n++] = atoi(digits);
        *p = 0;
      }
      if (n == 1) {
        if (c->constructStage >= nums[0])
          d3if_ShowTree(list.items[i], 1);
        else
          d3if_ShowTree(list.items[i], 0);
      } else if (n == 2) {
        if (c->constructStage <= nums[0] && c->constructStage >= nums[1])
          d3if_ShowTree(list.items[i], 1);
        else
          d3if_ShowTree(list.items[i], 0);
      }
    }
  } else if (c->constructStage > c->constructStages) {
    bld = gm_FindBuildingById(c->constructBld);
    if (bld != 0 && bld->object != 0)
      d3if_ShowTree(bld->object, 1);
    if (obj != 0) {
      if (d3_QuadTree != 0)
        d3q_RemoveObject(obj, d3_QuadTree);
      d3if_Delete(obj);
    }
  }
  d3if_SelectScene(scene, 1);
}
/* 0x56bac0, the construction stage the scene object "he_<id>" of the building event ev shows: the highest number
   among the "_nn" suffixes of its children's names (he_CollectChild, in the default scene, the current one restored
   at the end); after cutting a suffix the next search starts at the cut, so only the last suffix of each name is read */
int he_ConstructionStage(AIJOB *ev) {
  int best;
  int scene;
  char digits[0x10];
  int nums[8];
  HECHILDLIST list;
  char part[0x80];
  char name[0x80];
  char *p;
  int i, n;

  best = 0;
  scene = d3_CurrentScene;
  d3if_SelectScene(0, 1);
  sprintf(name, "he_%i", ev->id);
  list.root = d3_FindObject(0, 0x1c0, 0, name);
  list.count = 0;
  d3_ForEachObject(d3_DefaultScene, list.root, 0x2c0,
                   (D3OBJECTCB)he_CollectChild, &list);
  for (i = 1; i < list.count; i++) {
    n = 0;
    list.items[i]->mask = 0;
    strcpy(part, list.items[i]->name);
    for (p = strrchr(part, '_'); p != 0 && n < 2; p = strrchr(p, '_')) {
      strncpy(digits, p + 1, 2);
      digits[2] = 0;
      if (isdigit(digits[0]))
        nums[n++] = atoi(digits);
      *p = 0;
    }
    if (n != 0 && nums[0] > best)
      best = nums[0];
  }
  d3if_SelectScene(scene, 1);
  return best;
}

/* 0x627e98, the construction models of the building types (he_b.c's he_CreateConstruction): the types of each record, then
   its scaffolding model; the record with type 0 ends the table and names the model for the types not listed */
HEBLDMODEL he_BuildingModels[37] = {
    {{8, 9, 10, 0}, "*bau_BRUNNEN_a.ogr"},
    {{5, 0, 0, 0}, "*bau_BUERGERHAUS_a.ogr"},
    {{17, 0, 0, 0}, "*bau_GEFAENGNIS_a.ogr"},
    {{18, 19, 0, 0}, "*bau_GEFAENGNIS_b.ogr"},
    {{50, 51, 52, 0}, "*bau_HANDWERK_b.ogr"},
    {{33, 34, 35, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{14, 15, 16, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{41, 42, 43, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{26, 27, 28, 0}, "*bau_HANDWERK_d.ogr"},
    {{4, 2, 0, 0}, "*bau_HAUS_a.ogr"},
    {{3, 1, 0, 0}, "*bau_HAUS_a.ogr"},
    {{22, 0, 0, 0}, "*bau_KIRCHE_GROSS_a.ogr"},
    {{20, 0, 0, 0}, "*bau_KIRCHE_KLEIN_a.ogr"},
    {{21, 0, 0, 0}, "*bau_KIRCHE_MITTEL_a.ogr"},
    {{44, 0, 0, 0}, "*bau_STADTWACHE_a.ogr"},
    {{45, 0, 0, 0}, "*bau_STADTWACHE_b.ogr"},
    {{46, 0, 0, 0}, "*bau_STADTWACHE_b.ogr"},
    {{11, 12, 13, 0}, "*bau_STADTWACHE_b.ogr"},
    {{23, 24, 25, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{47, 48, 49, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{53, 54, 55, 0}, "*bau_WIRTSHAUS_a.ogr"},
    {{6, 7, 0, 0}, "*bau_WOHNSITZ_GROSS_a.ogr"},
    {{57, 58, 56, 0}, "*bau_ZUNFTHAUS_a.ogr"},
    {{60, 61, 59, 0}, "*bau_ZUNFTHAUS_a.ogr"},
    {{63, 64, 62, 0}, "*bau_ZUNFTHAUS_a.ogr"},
    {{66, 67, 65, 0}, "*bau_ZUNFTHAUS_a.ogr"},
    {{75, 0, 0, 0}, "*bau_DOMIZIL_LANDSITZ.ogr"},
    {{76, 0, 0, 0}, "*bau_DOMIZIL_BURG.ogr"},
    {{77, 0, 0, 0}, "*bau_DOMIZIL_SCHLOSS.ogr"},
    {{84, 85, 86, 0}, "*bau_BRUNNEN_a.ogr"},
    {{81, 0, 0, 0}, "*bau_HANDWERK_SCHNEIDER_a.ogr"},
    {{82, 83, 0, 0}, "*bau_HANDWERK_SCHNEIDER_b.ogr"},
    {{79, 78, 80, 0}, "*bau_ZIGEUNER_ZIGEUNER_a.ogr"},
    {{72, 0, 0, 0}, "*bau_FRIEDHOF_TOTENFELD.ogr"},
    {{73, 0, 0, 0}, "*bau_FRIEDHOF_GOTTESACKER.ogr"},
    {{74, 0, 0, 0}, "*bau_FRIEDHOF_FRIEDHOF.ogr"},
    {{0, 0, 0, 0}, "*bau_HAUS_a.ogr"}};

/* 0x56bc50, creates the two scene objects of the building event ev in the default scene (the current one restored
   at the end): the construction model of the building type *type (he_BuildingModels; a type not listed gets the
   model of the closing record), named "he_<id>", and the building's own group model, hidden, dropped on the ground
   (not below pos) and hooked to the building (init_HookObject); both are placed at pos and rot, the construction
   shows its first stage (he_ShowConstruction, not started); returns the building's object, 0 when a load failed */
D3OBJECT *he_CreateConstruction(D3VECTOR *rot, D3VECTOR *pos,
                                unsigned char *type, char *model, AIJOB *ev) {
  int scene;
  char name[0x100];
  D3OBJECT *obj;
  int n, k, found;

  n = 0;
  found = 0;
  if (he_BuildingModels[0].types[0] != 0) {
    for (; he_BuildingModels[n].types[0] != 0; n++) {
      if (found)
        break;
      for (k = 0; k < 4; k++) {
        if (*type == he_BuildingModels[n].types[k]) {
          strcpy(name, he_BuildingModels[n].model);
          found = 1;
          break;
        }
      }
    }
  }
  if (!found)
    strcpy(name, he_BuildingModels[n].model);
  scene = d3_CurrentScene;
  d3if_SelectScene(0, 1);
  obj = d3_LoadGroup(name, 0, 0);
  if (obj == 0) {
    d3if_SelectScene(scene, 1);
    return 0;
  }
  d3_SetObjectPos(obj, pos);
  d3_SetObjectRot(obj, rot);
  obj->objectFlags = obj->objectFlags & ~4 | 2;
  sprintf(obj->name, "he_%i", ev->id);
  obj = d3_LoadGroup(model, 0, 0);
  if (obj == 0) {
    d3if_SelectScene(scene, 1);
    return 0;
  }
  d3_SetObjectPos(obj, pos);
  d3_SetObjectRot(obj, rot);
  init_StripTorches(obj);
  d3t_DropObject(obj, 1, 0);
  if (obj->pos.y < pos->y) {
    obj->pos.x = pos->x;
    obj->pos.y = pos->y;
    obj->pos.z = pos->z;
  }
  d3if_ShowTree(obj, 0);
  d3_RelightObjects(obj);
  ev->constructStage = -1;
  ev->constructScript = -1;
  he_ShowConstruction(ev);
  init_HookObject(obj, type, 2);
  d3if_SelectScene(scene, 1);
  return obj;
}

/* the construction event's run handler stores gm_AddToTreasury's result (the send slot of its goods message) as
   the payment's slot (0x56bf1a .. 0x56bf22) */
void sv_CreateBanners(struct AIBLD *b);

/* 0x56be30, the run handler of the building construction event 0xd, by its stage: 0 pays the price when due (the
   player's own money to the treasury, else moved from the payer), 1 waits for the payment, 2 sends the building
   message 10, 3 takes the new building from its answer, 4 creates the construction objects (he_CreateConstruction)
   and sets the work minutes per stage, 5 sends the "vg_" objects of the site to the building nearest to it
   (SpecialEvents\\Hausbau.esc), 6 deletes them once placed, 7 counts the work minutes into stages (the workers'
   script SpecialEvents\\Hausbau_2.esc from stage 2 on) and at the last one shows the building, builds its road,
   sends the news and moves the owner in; -1 / -2 tear the construction down; every stage but the waiting ones goes
   on through the cm slot cm_SendExSetHE gives
   @deep s47: 70 -> 32 ins, frame 0x38c = the original's. Read from the original's leas (pending pushes
   subtracted): 0x10 bld, 0x14 best/i/radius, 0x18 dist/nearest, 0x1c scene, 0x20 v/center (16 bytes), 0x30
   at/now, 0x40 minutes, 0x44 site, 0x98 list, 0x11c u, 0x19c text. Kept: v a block local of each search
   (case 5 block, the stage-7 search block with at), now in its type block, the completion as if (c->constructStage
   > c->constructStages) { D3VECTOR4 center; float radius; ..} break; (center is 16 bytes: the slot 0x20..0x30; it
   must conflict with now, so its block encloses now's), door = 0 before the sprintf (order), nearest =
   &ai_Blds[i] before best = dist in stage 5 (regs). Left: only the slot order of scene (ours 0x18) and
   dist/nearest (ours 0x1c): equal densities 2250, VC6's unstable qsort. c2frame counts: scene 9, dist 6 +
   nearest 3. A model of VC6's qsort (cutoff 8, ascending, table reversed) fitted to 4 compiles says the
   original has scene 8 OR dist+nearest 10 (one counted reference: counts are taken after allocation and
   before tail merging / the store-load peephole, so the final code can be identical). Probes that flip it
   (all change meaning): deleting one SelectScene(scene) (2917 / 2952 / 2967 / -1 case), the -1 case's
   memset (its rep stosd forces the scene reload into edi), moving if (scene != 0). = control: nearest /
   best init order, if (!nearest), nested dist test, (float)sqrt, best in the for init, door / best order
   in stage 7, stage-5 failure via one shared exit (worse). prior: size queue s16: 202 -> 70 ins, raw 4000
   = the original's padded size. Kept: stage 0's two exits (payer gone, the success send) end with break
   (retgen sites 0+1: the original's stage 0 jumps into stage 3's copies), stage 3's bld test written
   positive (if (bld != 0) { ..; send(stage + 1); return; } send(-1); return;: its failure send cross-jumps
   into stage 1's copy as in the original), the bounding sphere into its own center / radius locals (the
   original's lea [esp+0x20] / [esp+0x14]; &v / &best kept best address-taken and moved every slot). Left:
   only frame slots (frame 0x3a4 vs 0x38c): the original shares [0x14] best / i / radius, [0x18] dist /
   nearest, [0x30] v / now, center at [0x20]. Block-scoping center+radius, now, at, v (31 subsets) gives
   frame 0x388 at best (sphere+now+at 67 ins, but raw 4004, padded too big); a sphere with &at / &v (any
   radius) brings back 2400 bytes of slot hunks. Next: c2frame on sphere+now+at for the 4 missing bytes. */
void he_RunConstruction(AIJOB *e) {
  AIJOB *c = e;
  AIBLD *bld;
  float best;
  float dist;
  int scene;
  int minutes;
  AIBUILDSITE site;
  AIVGLIST list;
  union {
    char name[0x80]; /* the construction object's name "he_<id>" */
    int msg
        [0x1f]; /* the data of the system message 0xc (cm_SendExSysMessage copies 0x7c bytes) */
  } u;
  char text[0x200];
  AIBLD *nearest;
  D3OBJECT *door;
  D3OBJECT *o;
  D3OBJECT *house;
  EVTSCRIPT *sc;
  AICHAR *ch;
  AIBLD *home;
  AIFIN *fin;
  AIBTYPE *bt;
  int i, size, season;

  scene = d3_CurrentScene;
  bld = 0;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if (gm_CompareTime(&e->end, &ai_Time) > 0)
      break;
    if (!(e->opts & 2))
      break;
    if (c->constructPayer != ai_PlayerChar->netId) {
      ch = gm_FindChar(c->constructPayer);
      if (ch == 0) {
        e->exSlot = cm_SendExSetHE(-1, e);
        break;
      }
      c->constructSlot = cm_SendMoveGoods(-1, c->constructPayer, ai_OwnPlayer,
                                          c->constructCarry);
      fin = gm_PlayerRecord(ch);
      if (fin != 0)
        fin->buildPaid += c->constructCarry;
    } else {
      c->constructSlot = gm_AddToTreasury(c->constructCarry);
    }
    e->exSlot = cm_SendExSetHE(e->stage + 1, e);
    break;
  case 1:
    e->exSlot = -1;
    if (e->opts & 4)
      break;
    if (cm_GetSlotState(c->constructSlot) == 0)
      break;
    if (cm_GetSlotState(c->constructSlot) == 2) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(e->stage + 1, e);
    return;
  case 2:
    if (!(e->opts & 2))
      break;
    c->constructSlot = cm_SendMessage10((unsigned char)c->constructBldType,
                                        c->constructPayer, 0, 1);
    e->exSlot = cm_SendExSetHE(e->stage + 1, e);
    return;
  case 3:
    e->exSlot = -1;
    if (e->opts & 4)
      break;
    if (cm_GetSlotState(c->constructSlot) == 0)
      break;
    if (cm_GetSlotState(c->constructSlot) == 2) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    bld = (AIBLD *)cm_GetSlotValue(c->constructSlot);
    if (bld != 0) {
      c->constructBld = bld->id;
      e->from = bld->id;
      e->exSlot = cm_SendExSetHE(e->stage + 1, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 4:
    e->exSlot = -1;
    gm_FindById(&bld, 0, 0, c->constructBld);
    if (bld == 0) {
      e->stage = -1;
      return;
    }
    if (he_CreateConstruction(&c->constructRot, &c->constructPos, &bld->type,
                              c->constructModel, e) == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      d3if_SelectScene(scene, 1);
      return;
    }
    init_HookObject(bld->object, bld, 2);
    bt = &ai_BTypes[bld->type];
    if (gm_AllowAll != 0) {
      c->constructStages = he_ConstructionStage(e);
      c->constructMinutes = 10;
    } else {
      c->constructStages = he_ConstructionStage(e);
      c->constructMinutes = (unsigned)(bt->v243 * 0x3fc) / c->constructStages;
    }
    c->constructStage = 0;
    gm_AddTime(&e->end, 0, 1, 0);
    e->stage++;
    return;
  case 5: {
    D3VECTOR v;

    e->exSlot = -1;
    d3if_SelectScene(0, 1);
    gm_FindById(&bld, 0, 0, c->constructBld);
    if (bld == 0 || lc_GetGebaeudeBauplatz(&site, bld) == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      d3if_SelectScene(scene, 1);
      return;
    }
    nearest = 0;
    best = 1e35f;
    for (i = 0; i < 0x100; i++) {
      if (&ai_Blds[i] != bld && ai_Blds[i].type != 0 &&
          ai_Blds[i].object != 0) {
        house = ai_Blds[i].object;
        d3_PointToWorld(house, &house->pos, &v);
        v.x -= site.pos.x;
        v.y -= site.pos.y;
        v.z -= site.pos.z;
        dist = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (dist < best &&
            d3_FindObject(ai_Blds[i].object, 0x100, 0, "dummy_TUER") != 0) {
          nearest = &ai_Blds[i];
          best = dist;
        }
      }
    }
    if (nearest == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      d3if_SelectScene(scene, 1);
      return;
    }
    memset(&list, 0, sizeof(list));
    d3_ForEachObject(d3_DefaultScene, site.object, 0x2c0, ai_VgFilter, &list);
    c->constructPlacing = 0;
    for (i = 0; i < list.count; i++) {
      o = list.objs[i];
      door = d3_FindObject(nearest->object, 0x100, 0, "dummy_TUER");
      if (o != 0 && o->type != 1 && door != 0) {
        sc = evt_Load("SpecialEvents\\Hausbau.esc");
        if (sc != 0) {
          evt_RunScriptArgs(sc, 4, door, o, he_PlaceGebaeudeObject, e);
          sc->group = 0;
          sc->ownScene = 1;
          evt_Step(sc);
        }
        c->constructPlacing++;
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->stage++;
    d3if_SelectScene(scene, 1);
    return;
  }
  case 6:
    e->exSlot = -1;
    gm_AddTime(&e->end, 0, 0x14, 0);
    if (c->constructPlacing != 0)
      break;
    d3if_SelectScene(0, 1);
    gm_FindById(&bld, 0, 0, c->constructBld);
    if (lc_GetGebaeudeBauplatz(&site, bld) == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      d3if_SelectScene(scene, 1);
      return;
    }
    memset(&list, 0, sizeof(list));
    d3_ForEachObject(d3_DefaultScene, site.object, 0x2c0, ai_VgFilter, &list);
    for (i = 0; i < list.count; i++) {
      if (d3_QuadTree != 0)
        d3q_RemoveObject(list.objs[i], d3_QuadTree);
      d3if_Delete(list.objs[i]);
    }
    e->clock60 = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->stage++;
    c->constructCarry = 0;
    d3if_SelectScene(scene, 1);
    return;
  case 7:
    minutes =
        gm_FixedWorkMinutesBetween(&e->clock60, &ai_Time) + c->constructCarry;
    if (minutes < c->constructMinutes) {
      gm_AddTime(&e->end, 0, 0x1e, 0);
      return;
    }
    e->clock60 = e->end;
    if (bld == 0)
      gm_FindById(&bld, 0, 0, c->constructBld);
    if (c->constructScript == -1 && c->constructStage >= 2) {
      D3VECTOR at;
      D3VECTOR v;

      d3if_SelectScene(0, 1);
      door = 0;
      sprintf(u.name, "he_%i", e->id);
      o = d3_FindObject(0, 0x1c0, 0, u.name);
      d3_PointToWorld(o, &o->pos, &at);
      best = 1e35f;
      for (i = 0; i < 0x100; i++) {
        if (&ai_Blds[i] != bld && ai_Blds[i].type != 0 &&
            ai_Blds[i].object != 0) {
          house = ai_Blds[i].object;
          d3_PointToWorld(house, &house->pos, &v);
          v.x -= at.x;
          v.y -= at.y;
          v.z -= at.z;
          dist = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
          if (dist < best && (house = d3_FindObject(ai_Blds[i].object, 0x100, 0,
                                                    "dummy_TUER")) != 0) {
            best = dist;
            door = house;
          }
        }
      }
      if (door != 0 && o != 0) {
        sc = evt_Load("SpecialEvents\\Hausbau_2.esc");
        if (sc != 0) {
          evt_RunScriptArgs(sc, 3, o, door, 2);
          sc->ownScene = 1;
          sc->group = 0;
          c->constructScript = sc->id;
          evt_Step(sc);
        }
      }
      d3if_SelectScene(scene, 1);
    }
    c->constructStage += minutes / c->constructMinutes;
    c->constructCarry = minutes % c->constructMinutes;
    gm_AddTime(&e->end, 0, c->constructMinutes, 0);
    if (d3_CurrentScene == 0) {
      if (c->constructStage <= c->constructStages)
        he_ShowConstruction(e);
      if (c->constructStage == 2 && (e->opts & 2)) {
        memset(u.msg, 0, sizeof(u.msg));
        cm_SendExSysMessage(0xc, u.msg);
      }
    }
    if (c->constructStage > c->constructStages) {
      D3VECTOR4 center;
      float radius;

      d3if_SelectScene(0, 1);
      if (c->constructScript != -1) {
        sc = evt_FindById(c->constructScript);
        if (sc != 0)
          evt_Stop(sc);
        c->constructScript = -1;
      }
      if (scene != 0) {
        d3t_InflateObjectTree(bld->object);
        bld->object->flags |= 4;
      }
      he_ShowConstruction(e);
      if (bld->object != 0) {
        season = gm_ClockSeason(&ai_Time);
        if (season == 1)
          init_TextureSet = 1;
        else if (season == 0)
          init_TextureSet = 0;
        else if (season == 2)
          init_TextureSet = 2;
        else if (season == 3)
          init_TextureSet = 3;
        init_TextureSetHook(bld->object);
      }
      if (d3_QuadTree != 0)
        d3q_Rebuild(bld->object, d3_QuadTree);
      if (bld->object != 0 && bld->object->type == 1)
        d3if_ShowTree(bld->object, 1);
      if (ai_Chars[bld->owner].kind == 6 || ai_Chars[bld->owner].kind == 5 ||
          ai_Chars[bld->owner].kind == 7)
        sv_CreateBanners(bld);
      ai_CheckBuildSites();
      if (bld->object->info == 0)
        d3_InflateObject(bld->object);
      if (bld->object->material != 0 &&
          d3t_GetBoundingSphere(bld->object, d3_Camera, &center.v, &radius) !=
              0) {
        size = (int)(radius * 1.8);
        sc = evt_Load("Effekte/geb_bauen.esc");
        if (sc != 0) {
          evt_RunScriptArgs(sc, 6, (int)center.x, (int)center.y, (int)center.z,
                            (int)radius, size, bld->object);
          sc->group = 0;
        }
      }
      rd_BuildRoad(bld->object, bld->type);
      if (e->opts & 2) {
        cm_SendSetField(bld->id, 0x5a, 2, 0, 1);
        if (bld->type >= 4 && bld->type <= 7) {
          AITIME now;

          now = ai_Time;
          cm_BeginFieldBlock(bld, bld->id);
          cm_AddFieldDelta(1, 0xe, 0x69, &now);
          cm_SendFieldDeltas();
        }
        if (ai_Chars[bld->owner].kind == 6) {
          if (bld->type >= 4 && bld->type <= 7) {
            txt_Format(text, 0x1c2f, bld);
            he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, e->from, text, 1,
                                   0x5f6, bld->id, -1, 0, "_NACHRICHTEN_HS_49");
          } else {
            txt_Format(text, 0x1c27, bld);
            he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, e->from, text, 0,
                                   0x5f6, bld->id, -1, 0, "_NACHRICHTEN_HS_49");
          }
          sb_PlaySample(snd_SystemBank, "NeuesGebaeude_s", 1, 0x3f, 0x7f, 0, 0);
        }
        if (ai_Chars[bld->owner].kind == 6 || ai_Chars[bld->owner].kind == 5) {
          for (ch = ai_Chars;
               (intptr_t)&ch->netId < (intptr_t)&ai_Chars[0x300].netId; ch++) {
            if ((ch->kind == 6 || ch->kind == 7) &&
                ch->netId != ai_Chars[bld->owner].netId) {
              txt_Format(text, 0x1c30, bld->owner, bld->type * 14 + 0x48e);
              he_MessageBoxQuickjump(ch->netId, -1, text, 0, 0x607, bld->id, -1,
                                     0, "_NACHRICHTEN_HS_50");
            }
          }
        }
        memset(u.msg, 0, sizeof(u.msg));
        cm_SendExSysMessage(0xc, u.msg);
      }
      if (bld->type >= 4 && bld->type <= 7) {
        home = ai_Chars[bld->owner].bld2;
        if (home == 0 || home->type <= bld->type)
          ai_Chars[bld->owner].bld2 = bld;
      }
      gm_MoveIntoHome(&ai_Chars[bld->owner], bld);
      d3if_SelectScene(scene, 1);
      e->text = 0;
      he_FreeEvent(e);
      return;
    }
    break;
  case -2:
  case -1:
    gm_FindById(&bld, 0, 0, c->constructBld);
    d3if_SelectScene(0, 1);
    if (c->constructScript != -1) {
      sc = evt_FindById(c->constructScript);
      if (sc != 0)
        evt_Stop(sc);
      c->constructScript = -1;
    }
    c->constructStage = c->constructStages + 1;
    he_ShowConstruction(e);
    if ((e->opts & 2) && bld != 0) {
      cm_SendBuildingDestroyed(bld->id);
      memset(u.msg, 0, sizeof(u.msg));
      cm_SendExSysMessage(0xc, u.msg);
    }
    d3if_SelectScene(scene, 1);
    he_FreeEvent(e);
    break;
  }
}
/* 0x56cdd0, the allocation handler of the mission check event 0x4c (he_RunMissionCheck): both clocks (end and
   clock60) start at the event's start clock, the end is 10 minutes later, the stage is 0 and the slot is -1 */

void he_AllocMissionCheck(AIJOB *ev) {
  AIJOB *m = ev;

  ev->end = ev->start;
  ev->clock60 = ev->start;
  ev->stage = 0;
  m->missionCheckSlot = -1;
  gm_AddTime(&ev->end, 0, 0xa, 0);
}

/* 0x56ce40, the run handler of the mission check event 0x4c (alloc he_AllocMissionCheck): without a mission mode
   (ai_MissionMode negative) it frees the event; it finds the running mission (ai_Missions) of its character, none:
   due in 30 minutes; by its stage (-2 / -1 free) 0 checks the mission before 22 h (ai_IsMissionFulfilled: fulfilled,
   stage 1), 1 tells its owner with the system message 8 (before 22 h, outside a network mission: stage 2), 2 waits
   for that message's slot (1: stage 0, due in a day; else back to stage 1) */
void he_RunMissionCheck(AIJOB *e) {
  AIJOB *m = e;
  int msg[0x1f];
  int i, h;

  if (ai_MissionMode <= -1) {
    he_FreeEvent(e);
    return;
  }
  for (i = 0; i < 0x80; i++) {
    if (ai_Missions[i].type != 0 &&
        ai_Missions[i].owner == ai_Chars[e->chr].netId)
      break;
  }
  if (i >= 0x80) {
    gm_AddTime(&e->end, 0, 0x1e, 0);
    return;
  }
  switch (e->stage) {
  case 0:
    if (ai_Missions[i].fulfilled == 0 && ai_Time.hour < 0x16) {
      if (ai_IsMissionFulfilled(&ai_Missions[i]) != 0) {
        ai_Missions[i].fulfilled = 1;
        gm_AddTime(&e->end, 0, 1, 0);
        e->stage = 1;
        return;
      }
    }
    gm_AddTime(&e->end, 0, 0xa, 0);
    break;
  case 1:
    gm_AddTime(&e->end, 0, 1, 0);
    if (ai_Missions[i].fulfilled == 1 && ai_Time.hour < 0x16 &&
        ai_MissionPartner == -1) {
      msg[0] = ai_Missions[i].owner;
      m->missionCheckSlot = cm_SendExSysMessage(8, msg);
      e->stage = 2;
      return;
    }
    gm_AddTime(&e->end, 1, 0, 0);
    e->stage = 1;
    break;
  case 2:
    h = cm_GetSlotState(m->missionCheckSlot);
    gm_AddTime(&e->end, 0, 1, 0);
    if (h == 0)
      return;
    if (h == 1) {
      e->stage = 0;
      gm_AddTime(&e->end, 0x18, 0, 0);
      return;
    }
    e->stage = 1;
    gm_AddTime(&e->end, 0, 0x1e, 0);
    break;
  case -2:
  case -1:
    he_FreeEvent(e);
    break;
  }
}
/* 0x56d050, registers the event types of the construction / production group (called by 0x53d4b0): the alloc / run pairs of 3, 4, 5, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0x4c, 0x4d and the type texts of 3, 4, 8, 9; 0 = ok, 1 = a registration failed */

int he_RegisterEventTypes03(void) {
  if (he_SetEventHandlers(3, he_AllocIncomeEvent, he_RunIncomeEvent) != 0)
    return 1;
  sv_RegisterActivity(3, "Abbau", 1, 0x501, 0xac);
  if (he_SetEventHandlers(4, he_AllocProduktion, he_RunProduktion) != 0)
    return 1;
  sv_RegisterActivity(4, "Produktion", 1, 0x4ff, 0xac);
  if (he_SetEventHandlers(5, he_FreeEventNow, he_NoHandlerB) != 0)
    return 1;
  if (he_SetEventHandlers(8, he_AllocSearchEvent, he_RunSearchEvent) != 0)
    return 1;
  sv_RegisterActivity(8, "Suchen", 1, 0x500, 0xac);
  if (he_SetEventHandlers(9, he_AllocSearch9, he_RunSearch9) != 0)
    return 1;
  sv_RegisterActivity(9, "Suchen", 1, 0x500, -1);
  if (he_SetEventHandlers(10, he_NoHandlerB, he_RunNewOccurrenceMsg) != 0)
    return 1;
  if (he_SetEventHandlers(0xb, he_AllocTrade, he_RunTrade) != 0)
    return 1;
  if (he_SetEventHandlers(0xc, he_AllocResearch, he_RunResearch) != 0)
    return 1;
  if (he_SetEventHandlers(0xd, he_AllocGebaeudeBauen, he_RunConstruction) != 0)
    return 1;
  if (he_SetEventHandlers(0xe, he_NoHandlerB, he_NoHandlerB) != 0)
    return 1;
  if (he_SetEventHandlers(0x4c, he_AllocMissionCheck, he_RunMissionCheck) != 0)
    return 1;
  if (he_SetEventHandlers(0x4d, he_FreeEventNow, he_NoHandlerB) != 0)
    return 1;
  return 0;
}

void he_AllocRecipeResearch(AIJOB *ev);
void he_RunRecipeResearch(AIJOB *ev);
void he_AllocResearchRecipe(AIJOB *ev);
void he_RunResearchRecipe(AIJOB *ev);
void he_AllocTrainShare(AIJOB *ev);
void he_RunTrainShare(AIJOB *ev);
void he_AllocAlchemistDay(AIJOB *ev);
void he_RunAlchemistDay(AIJOB *ev);

/* 0x56d220, registers the research event types 0x95 .. 0x98 (called by 0x53d4b0) and the texts of 0x95 / 0x96; 0 = ok, 1 = a registration failed */
int he_RegisterEventTypes95(void) {
  if (he_SetEventHandlers(0x95, he_AllocRecipeResearch, he_RunRecipeResearch) ==
      0) {
    if (he_SetEventHandlers(0x96, he_AllocResearchRecipe,
                            he_RunResearchRecipe) == 0) {
      if (he_SetEventHandlers(0x97, he_AllocTrainShare, he_RunTrainShare) ==
          0) {
        if (he_SetEventHandlers(0x98, he_AllocAlchemistDay,
                                he_RunAlchemistDay) == 0) {
          sv_RegisterActivity(0x95, "erforschen", 1, 0x500, -1);
          sv_RegisterActivity(0x96, "erforschen", 1, 0x500, -1);
          return 0;
        }
      }
    }
  }
  return 1;
}

void snd_PlayFavourComment(void);

/* 0x56d2d0, the allocation handler of the research event 0x95 (he_RunRecipeResearch): the character (alchemist) and
   a random recipe it has no place for yet (ahm_RandomRecipe) set the recipe id and the research minutes (left /
   total), both clocks (worked and end) start at the game clock, the end is 5 minutes later, the stage is 0, and the
   character is registered in its building's group (gm_Query / sv_MoveToGroup); without a character or recipe the
   event frees itself */

void he_AllocRecipeResearch(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;
  AHMGRID *p;
  int v;

  c = gm_FindChar(r->recipeAlchemist);
  if (c != 0) {
    p = ahm_RandomRecipe(c);
    if (p != 0) {
      r->recipeRecipe = p->rcp.id;
      v = ahm_ResearchMinutes(c, p);
      r->recipeLeft = v;
      r->recipeTotal = v;
      r->recipeWorked = ai_Time;
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      e->stage = 0;
      sv_MoveToGroup(c->bld, gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b),
                     c->id, e);
      snd_PlayFavourComment();
      return;
    }
  }
  he_FreeEvent(e);
}

void ai_DomizilMessage(struct AICHAR *to, struct AICHAR *c, struct AIOBJ *obj,
                       int level);

/* 0x56d3d0, the run handler of the research event 0x95 (alloc he_AllocRecipeResearch): without its character or the
   character's alchemist record the event ends (stage -2); stages -2 / -1 free it; outside the day hours of the season
   (gm_DayStartHours .. gm_DayEndHours) it waits an hour, the work clock restarted; stage 1 finishes: the Domizil
   message about the recipe to the event's character, the recipe added (ahm_SendAddPlace), the alchemist out of the
   laboratory group, the event freed; while the laboratory (room 0x24b of the character's building) is busy it waits
   15 minutes; stage 0 takes the minutes worked off the minutes left and goes on in 5 minutes, at none left stage 1 */
void he_RunRecipeResearch(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;
  AICHAR *to;
  AIOBJ *o;
  int season;

  season = gm_ClockSeason(&ai_Time);
  c = gm_FindChar(r->recipeAlchemist);
  if (c == 0 || ahm_HasRecord(c) == 0)
    e->stage = -2;
  if (e->stage == -2 || e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if (!((float)ai_Time.hour >= gm_DayEndHours[season] ||
        (float)ai_Time.hour < gm_DayStartHours[season])) {
    if (e->stage == 1) {
      o = gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b);
      to = gm_FindChar(e->netId);
      if (to != 0)
        ai_DomizilMessage(to, c, o, r->recipeRecipe);
      ahm_SendAddPlace(c, r->recipeRecipe);
      sv_MoveToGroup(0, 0, c->id, 0);
      he_FreeEvent(e);
      return;
    }
    if (he_RoomBusy(c->bld, 0x24b) != 0) {
      r->recipeWorked = ai_Time;
      gm_AddTime(&e->end, 0, 0xf, 0);
      return;
    }
    if (e->stage == 0) {
      r->recipeLeft -= gm_MinutesBetween(&r->recipeWorked, &ai_Time);
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      r->recipeWorked = ai_Time;
      if (r->recipeLeft <= 0)
        e->stage = 1;
    }
    return;
  }
  r->recipeWorked = ai_Time;
  gm_AddTime(&e->end, 1, 0, 0);
}

/* 0x56d610, the alloc of the alchemist research event 0x96: the character (chr), the recipe (id) and the minutes the
   research takes (start) are looked up (gm_FindChar, ahm_FindRecipe, ahm_ResearchProgress into progress); when that
   progress is above ai_FloatZero the amount = the minutes it started with, both clocks (clock / end) = now, due 5,
   stage 0, and the character is registered in its building's group (gm_Query / sv_MoveToGroup); else the event
   frees itself */
void he_AllocResearchRecipe(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;
  AHMGRID *p;

  c = gm_FindChar(r->ahmResearchChr);
  if (c != 0) {
    p = ahm_FindRecipe(r->ahmResearchId);
    if (p != 0) {
      r->ahmResearchProgress = ahm_ResearchProgress(c, p, &r->ahmResearchStart);
      if (!(r->ahmResearchProgress <= 0.0f)) {
        r->ahmResearchAmount = r->ahmResearchStart;
        r->ahmResearchClock = ai_Time;
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 5, 0);
        e->stage = 0;
        sv_MoveToGroup(c->bld,
                       gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b), c->id,
                       e);
        snd_PlayFavourComment();
        return;
      }
    }
  }
  he_FreeEvent(e);
}

void ai_DomizilMessageResearchKind(struct AICHAR *param_1,
                                   struct AICHAR *param_2,
                                   struct AIOBJ *param_3, int param_4);

/* 0x56d730, the run handler of the alchemist research event 0x96 (alloc he_AllocResearchRecipe): without its character,
   the character's alchemist record or the record's place of the recipe (ahm_SlotOf) the event ends (stage -2, freed);
   outside the day hours of the season it waits an hour, the clock restarted; while the laboratory (room 0x24b of the
   character's building) is busy it waits 15 minutes; stage 1 finishes: the Domizil message about the research to the
   event's character, the place's value raised by the progress (ahm_SendSetPlaceValue), the alchemist out of the
   laboratory group, the event freed; stage 0 takes the minutes worked off the amount and goes on in 5 minutes, at
   none left stage 1 */
void he_RunResearchRecipe(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;
  AICHAR *to;
  AHMSLOT *p;
  struct AIOBJ *o;
  int season;

  season = gm_ClockSeason(&ai_Time);
  p = 0;
  c = gm_FindChar(r->ahmResearchChr);
  if (c == 0 || ahm_HasRecord(c) == 0 ||
      (p = ahm_SlotOf(c, r->ahmResearchId)) == 0)
    e->stage = -2;
  if (e->stage != -2) {
    if (!((float)ai_Time.hour >= gm_DayEndHours[season] ||
          (float)ai_Time.hour < gm_DayStartHours[season])) {
      if (he_RoomBusy(c->bld, 0x24b) != 0) {
        r->ahmResearchClock = ai_Time;
        gm_AddTime(&e->end, 0, 0xf, 0);
        return;
      }
      if (e->stage == 1) {
        o = gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b);
        to = gm_FindChar(e->netId);
        if (to != 0)
          ai_DomizilMessageResearchKind(to, c, o, r->ahmResearchId);
        ahm_SendSetPlaceValue(c, r->ahmResearchId,
                              r->ahmResearchProgress + p->v);
        sv_MoveToGroup(0, 0, c->id, 0);
        he_FreeEvent(e);
        return;
      }
      if (e->stage == 0) {
        r->ahmResearchAmount -=
            gm_MinutesBetween(&r->ahmResearchClock, &ai_Time);
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 5, 0);
        r->ahmResearchClock = ai_Time;
        if (r->ahmResearchAmount <= 0)
          e->stage = 1;
      }
      return;
    }
    r->ahmResearchClock = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    return;
  }
  he_FreeEvent(e);
}

void ai_DomizilMessageResearch(struct AICHAR *param_1, struct AICHAR *param_2,
                               struct AIOBJ *param_3, int param_4);

/* 0x56d990, the alloc of the alchemist training event 0x97: the character (chr) and the share (id) are looked up
   (gm_FindChar, ahm_ShareProgress into progress, its minutes into start); when that progress is above ai_FloatZero
   the amount = the minutes it started with, both clocks (clock / end) = now, due 5, stage 0, and the character is
   registered in its building's group (gm_Query / sv_MoveToGroup); else the event frees itself */
void he_AllocTrainShare(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;

  c = gm_FindChar(r->ahmResearchChr);
  if (c != 0) {
    r->ahmResearchProgress =
        ahm_ShareProgress(c, r->ahmResearchId, &r->ahmResearchStart);
    if (!(r->ahmResearchProgress <= 0.0f)) {
      r->ahmResearchAmount = r->ahmResearchStart;
      r->ahmResearchClock = ai_Time;
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      e->stage = 0;
      sv_MoveToGroup(c->bld, gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b),
                     c->id, e);
      snd_PlayFavourComment();
      return;
    }
  }
  he_FreeEvent(e);
}
/* 0x56daa0, the run handler of the alchemist training event 0x97 (alloc he_AllocTrainShare): without its character,
   the character's alchemist record or a share above ai_FloatZero (ahm_Share) the event ends (stage -2); stages -2 /
   -1 free it; outside the day hours of the season it waits an hour, the clock restarted; stage 1 finishes: the Domizil
   message about the training to the event's character, the share raised by the progress (ahm_SendSetShare), the
   alchemist out of the laboratory group, the event freed; while the laboratory (room 0x24b of the character's
   building) is busy it waits 15 minutes; stage 0 takes the minutes worked off the amount and goes on in 5 minutes, at
   none left stage 1 */
void he_RunTrainShare(AIJOB *e) {
  AIJOB *r = e;
  AICHAR *c;
  AICHAR *to;
  struct AIOBJ *o;
  float share;
  int season;

  season = gm_ClockSeason(&ai_Time);
  share = 0;
  c = gm_FindChar(r->ahmResearchChr);
  if (c == 0 || ahm_HasRecord(c) == 0 ||
      (share = ahm_Share(c, r->ahmResearchId)) <= 0.0f)
    e->stage = -2;
  if (e->stage == -2 || e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if (!((float)ai_Time.hour >= gm_DayEndHours[season] ||
        (float)ai_Time.hour < gm_DayStartHours[season])) {
    if (e->stage == 1) {
      o = gm_Query((void *)c->bld->objList, 2, 6, 0, 0x24b);
      to = gm_FindChar(e->netId);
      if (to != 0)
        ai_DomizilMessageResearch(to, c, o, r->ahmResearchId);
      ahm_SendSetShare(c, r->ahmResearchId, share + r->ahmResearchProgress);
      sv_MoveToGroup(0, 0, c->id, 0);
      he_FreeEvent(e);
      return;
    }
    if (he_RoomBusy(c->bld, 0x24b) != 0) {
      r->ahmResearchClock = ai_Time;
      gm_AddTime(&e->end, 0, 0xf, 0);
      return;
    }
    if (e->stage == 0) {
      r->ahmResearchAmount -= gm_MinutesBetween(&r->ahmResearchClock, &ai_Time);
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      r->ahmResearchClock = ai_Time;
      if (r->ahmResearchAmount <= 0)
        e->stage = 1;
    }
    return;
  }
  r->ahmResearchClock = ai_Time;
  gm_AddTime(&e->end, 1, 0, 0);
}
/* 0x56dd20, the alloc of the research event 0x98 (not while paused, flags +0x78 & 4): the clock +0x52 = now, the hour set to a random 9 .. 16 (or 13 on the next day from 20 on), +0xac = 0, +0xb0 / +0xb4 = -1, and the handler scheduled (0x4c4c60) into +0x84 */

void he_AllocAlchemistDay(AIJOB *e) {
  AIJOB *d = e;
  int h;

  if (e->opts & 4)
    return;
  e->end = ai_Time;
  if (e->end.hour > 0x13) {
    e->end.hour = 0xd;
    e->end.year += 1;
  } else if (e->end.hour < 9) {
    h = util_Random(8);
    e->end.hour = h + 9;
  }
  d->ahmDayBonus = 0;
  d->ahmDayPayloadB0 = -1;
  d->ahmDayPayloadB4 = -1;
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x56ddc0, true when the room `kind` of the building b (0x24b the alchemist's laboratory, 0x256 the cannon
   room, 0x266 the cabinet) is locked (a task runs in it): its object (0x4ffe90 (b->objList, 2, 6, 0, kind))
   has a nonzero locked; the calls outside those three kinds answer 0 */

int he_RoomBusy(AIBLD *b, unsigned short kind) {
  AIOBJ *o;

  if (kind == 0x24b || kind == 0x256 || kind == 0x266) {
    o = gm_Query(b->objList, 2, 6, 0, kind);
    if (o != 0 && o->locked > 0)
      return 1;
  }
  return 0;
}

/* 0x56de10, the run handler of the alchemist's daily laboratory event 0x98 (alloc he_AllocAlchemistDay; the character
   AIJOB.netId): stages -1 / -2 free it, a paused event (opts & 4) waits; without the character or its alchemist record
   the event is ended through cm_SendExSetHE (-1); it is due again next year at a random hour of the next season's
   day hours and a random quarter hour; a pending bonus adds 0.25 .. 0.5 to the record's value; else a roll of
   0.25 .. 0.5 above the record's value runs the laboratory scene he_LabIncident with the research state
   (ahm_ResearchState), otherwise the value changes by the state: 1 -0.1 .. -0.2, 2 -0.1 .. -0.25, 3 / 4 -0.1 .. -0.3,
   none +0.05 .. +0.2 (ahm_SendAddValue); then the event goes on (cm_SendExSetHE 0) */
void he_RunAlchemistDay(AIJOB *e) {
  AIJOB *d = e;
  AICHAR *c;
  AHMREC *rec;
  float done;
  int id;
  float delta;
  int season, state;

  season = (gm_ClockSeason(&ai_Time) + 1) % 4;
  c = gm_FindChar(e->netId);
  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  if (c == 0 || ahm_HasRecord(c) == 0 || e->stage == -2 || e->stage == -1) {
    cm_SendExSetHE(-1, e);
    return;
  }
  rec = c->bld->ahm;
  e->end = ai_Time;
  e->end.year++;
  e->end.hour =
      util_Random((int)(gm_DayEndHours[season] - gm_DayStartHours[season])) +
      (int)gm_DayStartHours[season];
  e->end.min = util_Random(4) * 15;
  if (d->ahmDayBonus != 0) {
    ahm_SendAddValue(c, (util_RandomF() + 1.0f) * 0.25f);
    d->ahmDayBonus = 0;
    cm_SendExSetHE(0, e);
    return;
  }
  state = ahm_ResearchState(c->bld, &id, &done, 1);
  if ((util_RandomF() + 1.0f) * 0.25f > rec->value) {
    he_LabIncident(c, e, c->bld, state);
    cm_SendExSetHE(0, e);
    return;
  }
  switch (state) {
  case 1:
    delta = -((util_RandomF() + 1.0f) * 0.1f);
    break;
  case 2:
    delta = -(util_RandomF() * 0.15f + 0.1f);
    break;
  case 3:
  case 4:
    delta = -(util_RandomF() * 0.2f + 0.1f);
    break;
  default:
    delta = util_RandomF() * 0.15f + 0.05f;
    break;
  }
  ahm_SendAddValue(c, delta);
  cm_SendExSetHE(0, e);
}

void ai_DomizilMessageTask(struct AICHAR *to, struct AICHAR *c,
                           struct AIBLD *bld, struct AIOBJ *obj);
void ai_DomizilMessage04(struct AICHAR *to, struct AICHAR *c,
                         struct AIBLD *bld);
void ai_DomizilMessageAge(struct AICHAR *param_1, struct AICHAR *param_2,
                          struct AIBLD *param_3);
void ai_DomizilMessagePlace(struct AICHAR *to, struct AICHAR *c,
                            struct AIBLD *bld, int placeId);

/* 0x56e070, the laboratory incident of the alchemist's daily event 0x98 (he_RunAlchemistDay, only for a building
   type of kind 0x1e): of four mishaps it picks the first possible one from a random start (1 .. 4, in turn):
   1 a running task object of the building (0x24b / 0x256 / 0x266 with its state 0) is advanced (state +1,
   +0x20 by 3 .. 6), 2 the building's level drops by 4 .. 6 / 6 .. 8 / 8 .. 10 by the type's level 3 / 2 / other
   (only above level 10), 3 the alchemist ages by 1 .. 3 years (he_SetLifeByAge; always possible), 4 a place of
   the alchemist record above 0.2 loses 0.05 .. 0.15 (not in research state 2); the owner gets the message of the
   mishap; the mishap (0 none) goes to the event's +0xac (AIJOB.ahmDayBonus) */
void he_LabIncident(AICHAR *c, AIJOB *ev, AIBLD *b, int state) {
  AIJOB *d = ev;
  AIBTYPE *bt;
  AHMREC *rec;
  AIOBJ *task[3];
  int mishap = 0;
  int i, n, k, pick;
  char drop;
  float v;

  bt = &ai_BTypes[b->type];
  if (bt->kind == 0x1e) {
    int possible[5];

    for (i = 0; i < 5; i++)
      possible[i] = 0;
    possible[3] = 1;
    if (b->level > 10)
      possible[2] = 1;
    rec = b->ahm;
    if (state != 2) {
      for (i = 0; i < 6; i++) {
        if (rec->slots[i].id != 0 && rec->slots[i].v > 0.2f) {
          possible[4] = 1;
          break;
        }
      }
    }
    task[0] = gm_Query(b->objList, 2, 6, 0, 0x24b);
    if (task[0] != 0 && task[0]->lab.broken == 0)
      possible[1] = 1;
    task[1] = gm_Query(b->objList, 2, 6, 0, 0x256);
    if (task[1] != 0 && task[1]->lab.broken == 0)
      possible[1] = 1;
    task[2] = gm_Query(b->objList, 2, 6, 0, 0x266);
    if (task[2] != 0 && task[2]->lab.broken == 0)
      possible[1] = 1;
    pick = util_Random(4) + 1;
    for (n = 5; n != 0; n--) {
      if (pick != 0 && possible[pick] != 0) {
        mishap = pick;
        break;
      }
      pick = (pick + 1) % 5;
    }
    switch (mishap) {
    case 1:
      k = util_Random(3);
      for (n = 3; n != 0; n--) {
        if (task[k] != 0 && task[k]->lab.broken == 0) {
          int one = 1;
          int step = util_Random(4) + 3;

          cm_BeginFieldBlock(task[k], task[k]->objId);
          cm_AddFieldDelta(4, 1, 0x1c, &one);
          cm_AddFieldDelta(4, 1, 0x20, &step);
          cm_SendFieldDeltas();
          ai_DomizilMessageTask(&ai_Chars[b->owner], c, b, task[k]);
          break;
        }
        k = (k + 1) % 3;
      }
      break;
    case 2:
      if (bt->level == 3)
        drop = -4 - util_Random(3);
      else if (bt->level == 2)
        drop = -6 - util_Random(3);
      else
        drop = -8 - util_Random(3);
      cm_BeginFieldBlock(b, b->id);
      cm_AddFieldValues(1, 1, 0x5c, &drop);
      cm_SendFieldDeltas();
      ai_DomizilMessage04(&ai_Chars[b->owner], c, b);
      break;
    case 3:
      he_SetLifeByAge(c, util_Random(3) + 1);
      ai_DomizilMessageAge(&ai_Chars[b->owner], c, b);
      break;
    case 4:
      k = util_Random(6);
      for (n = 6; n != 0; n--) {
        if (rec->slots[k].id != 0 && rec->slots[k].v > 0.2f) {
          v = rec->slots[k].v - (util_RandomF() * 0.1f + 0.05f);
          ahm_SendSetPlaceValue(c, rec->slots[k].id, v);
          ai_DomizilMessagePlace(&ai_Chars[b->owner], c, b, rec->slots[k].id);
          break;
        }
        k = (k + 1) % 6;
      }
      break;
    default:
      return;
    }
    d->ahmDayBonus = mishap;
  }
}

void he_AllocSecretRoom(AIJOB *ev);
void he_RunSecretRoom(AIJOB *ev);
void he_AllocEvent9a(AIJOB *ev);
void he_RunDomizilEvent(AIJOB *ev);
void he_AllocDomizilEvent(AIJOB *ev);

/* 0x56e400, registers the event types 0x99 .. 0x9b (called by 0x53d4b0): the pairs (0x56e460, 0x56e5b0), (0x56efc0, 0x56f040) and (0x56f050, 0x56f0b0); 0 = ok, 1 = a registration failed */
int he_RegisterEventTypes99(void) {
  if (he_SetEventHandlers(0x99, he_AllocSecretRoom, he_RunSecretRoom) == 0) {
    if (he_SetEventHandlers(0x9a, he_AllocEvent9a, he_FreeEventNow) == 0) {
      if (he_SetEventHandlers(0x9b, he_AllocDomizilEvent, he_RunDomizilEvent) ==
          0)
        return 0;
    }
  }
  return 1;
}

/* 0x56e460, the alloc of the event 0x99 (not while paused, flags +0x78 & 4): when another event of the type 0x99 of the same player (+8) already runs, this one only announces the text 0x3ff7 (0x5176d0 / 0x53dda0), schedules with the handle -1 (0x4c4c60 ( -1, ev) into +0x84) and frees; else the start clock +0x44 and the due clock +0x52 = now, due 1, +0xcc = the notification 0x4c59f0 (0xd, ev's +0xb0, -1, 0x2d, 0, 0, the text 0x628dc8) and the handler scheduled (0x4c4c60 (0, ev)) into +0x84 */
void he_AllocSecretRoom(AIJOB *e) {
  char text[0x400];
  AIJOB *r;

  if (e->opts & 4)
    return;
  for (r = he_FindEvent(1, 0, 0x99); r != 0; r = he_NextEvent()) {
    if (r != e && r->chr == e->chr)
      goto taken;
  }
  e->start = ai_Time;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  e->secretRoomWalkSlot =
      cm_SendSpawnCharacter(0xd, e->secretRoomHome, -1, 0x2d, 0, 0, "ASSASSIN");
  e->exSlot = cm_SendExSetHE(0, e);
  return;
taken:
  txt_Format(text, 0x3ff7, e->chr);
  he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5fa, 0);
  e->exSlot = cm_SendExSetHE(-1, e);
  he_FreeEvent(e);
}

int ai_PickActionBuilding(struct AICHAR *p, int a, __int64 mask, float lo,
                          float hi, int *out); /* 0x4a63f0 (amt_ai.h) */
void he_FreeEventNow(AIJOB *r);                /* 0x56f040 */

/* 0x56e5b0, the run handler of the secret room event 0x99 (alloc he_AllocSecretRoom): the stages -1 / -2 remove the
   agent (opts & 2) and, at -1, tell the event's character (text 0x3ff9, the news "_NACHRICHTEN_DOMIZIL_08") and free
   the event; a paused event or one whose cm slot is still busy waits. Stage 0 takes the spawned agent from its cm
   slot: the spy hunt (way 3) goes on with stage 6, else the agent walks to the target building (stage 1). Stage 1
   waits 4 minutes while the agent walks, then an hour at the target (stage 3); stage 3 does the deed by the way
   (1 he_SecretRoomAttack, 2 he_SecretRoomAccuse, 3 the spy hunt again, 4 he_SecretRoomDomizil) with its news, and
   stage 4 sends the agent home (stage 5); stage 5 waits until it is there, removes it and ends the event after the
   rest of the way's time (way 2 0x21c minutes, way 4 0xb40, else 0x5a0; at least 5). The spy hunt: stage 6 follows
   the nearest spy (he_FindNearestSpying: stage 7) or walks to a picked building (stage 6 again in 15 minutes),
   stage 7 tries to catch it (he_SecretRoomCatchSpy); after 0x5a0 minutes it goes home (stage 4). A lost agent ends
   the event. */
void he_RunSecretRoom(AIJOB *e) {
  char text[0x100];
  AIJOB *s = e;
  AICHAR *per, *agent, *victim;
  AIBLD *bld;
  AIJOB *spy;
  int minutes, rest, caught;
  union {
    struct {
      unsigned int lo, hi;
    } s;
    __int64 q;
  } kinds;

  if (e->stage == -1 || e->stage == -2) {
    if (e->opts & 2) {
      if (gm_FindChar(s->secretRoomAgent) != 0)
        cm_SendKillCharacter(s->secretRoomAgent, 1);
      if (e->stage == -1)
        he_ShowNews(ai_Chars[e->chr].netId, -1, txt_Ptrs[0x3ff9], 1, 0x5fa,
                    "_NACHRICHTEN_DOMIZIL_08");
    }
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  per = &ai_Chars[e->chr];
  switch (e->stage) {
  case 0:
    if (cm_GetSlotState(s->secretRoomWalkSlot) == 1 &&
        (agent = (AICHAR *)cm_GetSlotValue(s->secretRoomWalkSlot)) != 0) {
      s->secretRoomAgent = agent->netId;
      if (s->secretRoomWay == 3) {
        e->end = ai_Time;
        e->exSlot = cm_SendExSetHE(6, e);
        return;
      }
      if ((bld = gm_BuildQuery(1, 1, s->secretRoomTarget)) == 0) {
        e->end = ai_Time;
        e->exSlot = cm_SendExSetHE(-1, e);
        return;
      }
      s->secretRoomWalkSlot =
          cm_SendChrGotoBuilding(agent->netId, bld->id, -1, 0, 1, "ASSASSIN");
      cm_SendExSetHE(1, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 1:
    s->secretRoomWalkSlot = -1;
    agent = gm_FindChar(s->secretRoomAgent);
    if (agent == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (agent->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    if (gm_BuildQuery(1, 1, s->secretRoomTarget) == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    e->exSlot = cm_SendExSetHE(3, e);
    return;
  case 3:
    agent = gm_FindChar(s->secretRoomAgent);
    if (agent == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    victim = gm_FindChar(s->secretRoomVictim);
    bld = gm_BuildQuery(1, 1, s->secretRoomHome);
    if (per != 0 && victim != 0 && bld != 0) {
      switch (s->secretRoomWay) {
      case 1:
        if (he_SecretRoomAttack(per, victim, s->secretRoomStrength) != 0) {
          txt_Format(text, 0x4004, victim->id);
          he_ShowNews(per->netId, -1, text, 1, 0x5fa,
                      "_NACHRICHTEN_DOMIZIL_06");
          txt_Format(text, 0x4006, s->secretRoomStrength + 0x4007);
          he_ShowNews(victim->netId, -1, text, 1, 0x5fb,
                      "_NACHRICHTEN_DOMIZIL_09");
        } else {
          txt_Format(text, 0x4005, victim->id);
          he_ShowNews(per->netId, -1, text, 1, 0x5fa,
                      "_NACHRICHTEN_DOMIZIL_07");
          txt_Format(text, 0x400a);
          he_ShowNews(victim->netId, -1, text, 1, 0x5fb,
                      "_NACHRICHTEN_DOMIZIL_09");
        }
        break;
      case 2:
        if (he_SecretRoomAccuse(per, victim, s->secretRoomStrength) != 0) {
          txt_Format(text, 0x4019, 0x400c, victim->id, victim->id);
          he_ShowNews(per->netId, -1, text, 1, 0x5fa, 0);
        } else {
          txt_Format(text, 0x401a, 0x400c, victim->id, victim->id);
          he_ShowNews(per->netId, -1, text, 1, 0x5fa, 0);
        }
        break;
      case 3:
        e->end = ai_Time;
        s->secretRoomSpyEvent = -1;
        s->secretRoomHunting = 0;
        e->exSlot = cm_SendExSetHE(6, e);
        break;
      case 4:
        he_SecretRoomDomizil(bld->id, victim);
        break;
      }
    }
    e->exSlot = cm_SendExSetHE(4, e);
    break;
  case 4:
    agent = gm_FindChar(s->secretRoomAgent);
    e->end = ai_Time;
    if (agent == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    s->secretRoomWalkSlot = cm_SendChrGotoBuilding(
        s->secretRoomAgent, s->secretRoomHome, -1, 0, 0, "ASSASSIN");
    e->exSlot = cm_SendExSetHE(5, e);
    return;
  case 5:
    agent = gm_FindChar(s->secretRoomAgent);
    if (agent == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (agent->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    minutes = gm_MinutesBetween(&e->start, &ai_Time);
    switch (s->secretRoomWay) {
    case 1:
      rest = 0x5a0;
      break;
    case 2:
      rest = 0x21c;
      break;
    case 3:
      rest = 0x5a0;
      break;
    case 4:
      rest = 0xb40;
      break;
    default:
      rest = 0x5a0;
      break;
    }
    rest -= minutes;
    minutes = rest > 5 ? rest : 5;
    e->end = ai_Time;
    gm_AddTime(&e->end, minutes / 60, minutes % 60, 0);
    cm_SendKillCharacter(s->secretRoomAgent, 1);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 6:
    if (gm_MinutesBetween(&e->start, &ai_Time) > 0x5a0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(4, e);
      return;
    }
    agent = gm_FindChar(s->secretRoomAgent);
    if (agent == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if ((spy = he_FindNearestSpying(per, agent, s->secretRoomSpyEvent)) != 0) {
      s->secretRoomTarget = spy->spyingAt;
      s->secretRoomSpyEvent = spy->id;
      s->secretRoomHunting = 1;
      cm_SendChrStop(agent->netId);
      cm_SendChrGotoBuilding(agent->netId, s->secretRoomTarget, -1, 0, 1,
                             "Spy Killer");
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(7, e);
    } else {
      kinds.s.lo = 0xa7f4c7a0;
      kinds.s.hi = 1;
      ai_PickActionBuilding(per, 0, kinds.q, 0.0f, 100.0f,
                            &s->secretRoomTarget);
      s->secretRoomSpyEvent = -1;
      s->secretRoomHunting = 0;
      cm_SendChrStop(agent->netId);
      cm_SendChrGotoBuilding(agent->netId, s->secretRoomTarget, -1, 0, 1,
                             "Spy Killer");
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 0xf, 0);
      e->exSlot = cm_SendExSetHE(6, e);
    }
    return;
  case 7:
    minutes = gm_MinutesBetween(&e->start, &ai_Time);
    agent = gm_FindChar(s->secretRoomAgent);
    if (agent == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (minutes > 0x5a0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(4, e);
      return;
    }
    caught = he_SecretRoomCatchSpy(
        agent, e, he_FindEvent(2, 0, 0x18, 1, s->secretRoomSpyEvent));
    if (caught == 0) {
      gm_AddTime(&e->end, 0, 6, 0);
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(7, e);
      return;
    }
    if (caught == 1) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(6, e);
      return;
    }
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(6, e);
    return;
  }
}
/* 0x56efc0, the alloc of the event 0x9a (the run 0x56f040 only frees it): the due clock +0x52 = now; when
   0x56f360 (no event 0x9a holds the building +0xac and the character of +0xb0 yet) answers 1, due in 0x18
   hours and the stage 0 posted; the stage -1 is posted in every case and its send slot kept at +0x84 */

void he_AllocEvent9a(AIJOB *e) {

  e->end = ai_Time;
  if (he_NoEvent9aFor(e->bldId, gm_FindChar(e->id2)) != 0) {
    gm_AddTime(&e->end, 0x18, 0, 0);
    cm_SendExSetHE(0, e);
  }
  e->exSlot = cm_SendExSetHE(-1, e);
}
/* 0x56f040, frees the event record it is handed (he_FreeEvent): the alloc / run handler of the event types the
   game drops at once (5, 0x2d, 0x30, 0x4d, 0x7b) and the run handler of 0x29 / 0x9a */

void he_FreeEventNow(AIJOB *r) { he_FreeEvent(r); }
/* 0x56f050, the alloc of the event 0x9b (not while paused, flags +0x78 & 4): due = now +0x30 hours (0x4fe140), state 0 scheduled (0x4c4c60) */

void he_AllocDomizilEvent(AIJOB *e) {
  if (e->opts & 4)
    return;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x30, 0, 0);
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x56f0b0, the run of the domicile event 0x9b: any stage but 0 frees; stage 0 sends the text 0x4035 with the news
   0x5fb (its second text "_NACHRICHTEN_DOMIZIL_11") to the character partner1 when it exists, and the text 0x4036 with the
   news 0x5fa to the character partner2 when it exists (the first character's id as its argument), then frees */
void he_RunDomizilEvent(AIJOB *e) {
  char text[0x100];
  AICHAR *c, *c2;

  if (e->stage == 0) {
    c = gm_FindChar(e->partner1);
    c2 = gm_FindChar(e->partner2);
    if (c != 0) {
      txt_Format(text, 0x4035);
      he_ShowNews(e->partner1, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_11");
    }
    if (c2 != 0) {
      txt_Format(text, 0x4036, c->id);
      he_ShowNews(e->partner2, -1, text, 1, 0x5fa, 0);
    }
  }
  he_FreeEvent(e);
}
/* 0x56f170, 1 when a running event of the type 0x99 has the owner +0xb0 == `owner` (the search 0x53e400 / 0x53e300) */

int he_EventOnBuilding(int owner) {
  AIJOB *r;

  for (r = he_FindEvent(1, 0, 0x99); r != 0; r = he_NextEvent()) {
    if (r->secretRoomHome == owner)
      return 1;
  }
  return 0;
}
/* 0x56f1b0, a meeting message when the slot he_FindMeetingSlot (c + 3) is free and (0x504ec0 (a, 4) - 0x504ec0 (b, 4) * 0.5f) + 0x42ec20 () >= 1.0: 0x4f2e30 (slot, 1, b + 4, a + 4, the id +1 of the record at b + 0x170 / +0x16c, else -1); 0 when not sent */

int he_SecretRoomAccuse(AICHAR *a, AICHAR *b, int c) {
  float fa, fb;
  int slot = he_FindMeetingSlot(c);
  int id;

  if (slot >= 0) {
    fa = gm_GetSkill(a, 4);
    fb = gm_GetSkill(b, 4);
    if (fa - fb * 0.5f + util_RandomF() >= 1.0f) {
      if (b->bld2 != 0)
        id = b->bld2->id;
      else if (b->bld != 0)
        id = b->bld->id;
      else
        id = -1;
      gv_Accuse(slot, 1, b->netId, a->netId, id);
      return 1;
    }
  }
  return 0;
}
/* 0x56f260, the first free meeting slot of 0x1d (two rounds from a random start): the record 0x4f2720 (slot) has +0x18 == 1, +1 == 2 and +0xc == the wanted id `c` + 3 (one more each round); -1 when none */

int he_FindMeetingSlot(int c) {
  AIDEC dec;
  int want = c + 3;
  int round;
  int i;
  int slot;

  round = 2;
  do {
    round--;
    slot = util_Random(0x1d);
    i = 0x1d;
    do {
      gv_GetTableRecord(slot, &dec);
      if (dec.cur == 1 && dec.valueText == 2 && dec.guilt == want)
        return slot;
      i--;
      slot = (slot + 1) % 0x1d;
    } while (i != 0);
    want++;
  } while (round != 0);
  return -1;
}
/* 0x56f2e0, a message when the person a and the record b (its word at 0 is the target) can meet: b not 0 and (0x504ec0 (a, 2) - 0x504ec0 (b, 2) * 0.5f) + 0x42ec20 () >= 1.0; then 0x4fca40 (*b, (-1 - c) * 5) */

int he_SecretRoomAttack(AICHAR *a, AICHAR *b, int c) {
  float fa, fb;

  if (b != 0) {
    fa = gm_GetSkill(a, 2);
    fb = gm_GetSkill(b, 2);
    if (fa - fb * 0.5f + util_RandomF() >= 1.0f) {
      gm_AddHealth(b->id, (-1 - c) * 5);
      return 1;
    }
  }
  return 0;
}
/* 0x56f360, 1 when no running event of the type 0x9a has both the building bldId and the netId of the character c; 0 when one does */

int he_NoEvent9aFor(int bldId, AICHAR *c) {
  AIJOB *r;

  for (r = he_FindEvent(1, 0, 0x9a); r != 0; r = he_NextEvent()) {
    if (r->bldId == bldId && r->id2 == c->netId)
      return 0;
  }
  return 1;
}
/* 0x56f3b0, 1 when no running domicile event 0x9b runs against the character a (its partner1 is a's netId); 0 when
   one does */

int he_NoEvent9bFor(AICHAR *a) {
  AIJOB *r;

  for (r = he_FindEvent(1, 0, 0x9b); r != 0; r = he_NextEvent()) {
    if (r->partner1 == (int)a->netId)
      return 0;
  }
  return 1;
}
/* 0x56f3f0, the domicile deed of the secret room event (way 4, he_RunSecretRoom): when no domicile event 0x9b runs
   against the victim yet (he_NoEvent9bFor) and the secret room's building bldId exists, its owner tries against the
   victim: skill 2 (owner - victim * 0.5 + random * 0.5 at least 0.8) and then skill 3 (at least 0.7); success tells
   both (texts 0x4031 / 0x4033) and posts the domicile event 0x9b (from the building, the victim and the owner) and
   returns 1; a failure tells both (texts 0x4032 / 0x4034); 0 when nothing was posted */
int he_SecretRoomDomizil(int bldId, AICHAR *victim) {
  char text[0x400];
  AIMSG msg;
  AIBLD *bld;
  AICHAR *owner;
  float mine, theirs;
  int ok;

  if (he_NoEvent9bFor(victim) != 0) {
    bld = gm_BuildQuery(1, 1, bldId);
    if (bld != 0) {
      owner = &ai_Chars[bld->owner];
      ok = 1;
      mine = gm_GetSkill(owner, 2);
      theirs = gm_GetSkill(victim, 2);
      if (mine - theirs * 0.5f + util_RandomF() * 0.5 < 0.8)
        ok = 0;
      else {
        mine = gm_GetSkill(owner, 3);
        theirs = gm_GetSkill(victim, 3);
        if (mine - theirs * 0.5f + util_RandomF() * 0.5 < 0.7)
          ok = 0;
      }
      if (ok == 0) {
        txt_Format(text, 0x4032, victim->id, victim->id);
        he_ShowNews(owner->netId, -1, text, 1, 0x5fa,
                    "_NACHRICHTEN_DOMIZIL_07");
        txt_Format(text, 0x4034);
        he_ShowNews(victim->netId, -1, text, 1, 0x5fb,
                    "_NACHRICHTEN_DOMIZIL_09");
      } else {
        txt_Format(text, 0x4031, victim->id);
        he_ShowNews(owner->netId, -1, text, 1, 0x5fa,
                    "_NACHRICHTEN_DOMIZIL_06");
        txt_Format(text, 0x4033);
        he_ShowNews(victim->netId, -1, text, 1, 0x5fb,
                    "_NACHRICHTEN_DOMIZIL_09");
        memset(&msg, 0, sizeof(msg));
        msg.type = 0x9b;
        msg.to = owner->netId;
        msg.fromId = bldId;
        msg.arg[0] = victim->netId; /* the event's partner1 */
        msg.arg[1] = owner->netId;  /* its partner2 */
        msg.flags = 2;
        cm_SendLongMessage(&msg);
        return 1;
      }
    }
  }
  return 0;
}
/* 0x56f600, the spy hunt's search (he_RunSecretRoom stage 6): of the running spying events 24 that spy on the
   character per (AIJOB.spyingVictim) and are not the event skip (an event id), the one whose spied building
   (AIJOB.spyingAt, gm_FindById) stands nearest to the agent's body; 0 when none (or the agent has no scene character) */
AIJOB *he_FindNearestSpying(AICHAR *per, AICHAR *agent, int skip) {
  float best = 1.0e7f;
  D3VECTOR4 here, diff;
  float d;
  AIJOB *found, *ev;
  AIBLD *bld;
  D3OBJECT *body;

  found = 0;
  if (agent->scene == 0)
    return 0;
  body = agent->scene->obj;
  /* @original: the position copies go through the FPU (fld / fstp), here and into diff before the
     subtracts; VC6 copies a parenthesised float member that way, a plain one through an integer register */
  here.x = (body->pos.x);
  here.y = (body->pos.y);
  here.z = (body->pos.z);
  he_FindEvent(1, 0, 0x18);
  for (ev = he_FindEvent(1, 0, 0x18); ev != 0; ev = he_NextEvent()) {
    if (ev->stage == -1 || ev->stage == -2 || skip == ev->id)
      continue;
    if (ev->spyingVictim != per->netId)
      continue;
    gm_FindById(&bld, 0, 0, ev->spyingAt);
    if (bld == 0)
      continue;
    body = bld->object;
    diff.x = (body->pos.x);
    diff.y = (body->pos.y);
    diff.z = (body->pos.z);
    diff.x -= here.x;
    diff.y -= here.y;
    diff.z -= here.z;
    d = sqrt(diff.z * diff.z + diff.y * diff.y + diff.x * diff.x);
    if (found == 0) {
      best = d;
      found = ev;
    } else if (best > d) {
      best = d;
      found = ev;
    }
  }
  return found;
}
/* 0x56f740, the spy hunt's catch (he_RunSecretRoom stage 7; agent = the secret room's agent, ev = its event, spy =
   the spying event 24 it follows): -1 without a spying event, after 0x14 tries (the event's spyEvent word, counted
   up here) or without the spy's scene character; while the spy is at least 1850 from the agent, the agent walks
   on to the spied building (when it changed, "Spy Killer") and 0; near, the spy is caught when the spy's
   employer's skill 2 + (days + 1) * 0.5 is below the victim's skill 2 + (strength + 1) * 0.5: the spying event
   ends, both are told (texts 0x4028 / 0x4029, the news "_NACHRICHTEN_DOMIZIL_10") and 1; else -1. match-deep 2026-11-10: parenthesized member copies (the FPU-copy lever) ins 16 -> 8. */
int he_SecretRoomCatchSpy(AICHAR *agent, AIJOB *ev, AIJOB *spy) {
  char text[0x400];
  AIJOB *s = ev;
  AIJOB *sp = spy;
  AICHAR *spyChr, *employer, *victim;
  D3VECTOR4 d, there;
  float dist, spyBonus, guard, skill;

  if (spy == 0 || spy->kind != 0x18)
    return -1;
  if ((unsigned int)s->secretRoomSpyEvent >= 0x14)
    return -1;
  s->secretRoomSpyEvent++;
  spyChr = gm_FindChar(sp->spyingSpy);
  if (spyChr == 0 || spyChr->scene == 0)
    return -1;
  d.x = (agent->scene->obj->pos.x);
  d.y = (agent->scene->obj->pos.y);
  d.z = (agent->scene->obj->pos.z);
  there.x = (spyChr->scene->obj->pos.x);
  there.y = (spyChr->scene->obj->pos.y);
  there.z = (spyChr->scene->obj->pos.z);
  d.x -= there.x;
  d.y -= there.y;
  d.z -= there.z;
  dist = sqrt(d.z * d.z + d.y * d.y + d.x * d.x);
  if (dist < 1850.0f) {
    employer = &ai_Chars[spy->chr];
    victim = gm_FindChar(sp->spyingVictim);
    spyBonus = (sp->spyingDays + 1) * 0.5f;
    guard = (s->secretRoomStrength + 1) * 0.5f;
    skill = gm_GetSkill(employer, 2);
    if (gm_GetSkill(victim, 2) + guard > skill + spyBonus) {
      spy->exSlot = cm_SendExSetHE(-1, spy);
      txt_Format(text, 0x4028, victim->id);
      he_ShowNews(employer->netId, -1, text, 1, 0x5fb,
                  "_NACHRICHTEN_DOMIZIL_10");
      txt_Format(text, 0x4029, employer->id);
      he_ShowNews(victim->netId, -1, text, 1, 0x5fb, "_NACHRICHTEN_DOMIZIL_10");
      return 1;
    }
    return -1;
  }
  if (sp->spyingAt != s->secretRoomTarget) {
    s->secretRoomTarget = sp->spyingAt;
    cm_SendChrStop(agent->netId);
    cm_SendChrGotoBuilding(agent->netId, sp->spyingAt, -1, 0, 1, "Spy Killer");
  }
  return 0;
}

void he_AllocHaunting(struct AIJOB *ev);          /* 0x56fc50 */
void he_RunHaunting(struct AIJOB *ev);            /* 0x56fda0 */
void he_AllocDecay(struct AIJOB *ev);             /* 0x570130 */
void he_RunDecay(struct AIJOB *ev);               /* 0x5702e0 */
void he_AllocMasterWork(struct AIJOB *ev);        /* 0x570ef0 */
void he_RunMasterWork(struct AIJOB *ev);          /* 0x571000 */
void he_AllocGraveCare(struct AIJOB *ev);         /* 0x571550 */
void he_RunGraveCare(struct AIJOB *ev);           /* 0x571640 */
void he_AllocPlunder(struct AIJOB *ev);           /* 0x5706e0 */
void he_RunPlunder(struct AIJOB *ev);             /* 0x5707a0 */
void he_AllocPlunderOfferLease(struct AIJOB *ev); /* 0x572860 */
void he_RunPlunderOffer(struct AIJOB *ev);        /* 0x570cc0 */
void he_AllocDeathDue(struct AIJOB *ev);          /* 0x571990 */
void he_RunDeathDue(struct AIJOB *ev);            /* 0x5719e0 */
void he_AllocGraveTraining(struct AIJOB *ev);     /* 0x571ac0 */
void he_RunGraveTraining(struct AIJOB *ev);       /* 0x571c30 */
void he_AllocMeeting(struct AIJOB *ev);           /* 0x571f60 */
void he_RunMeeting(struct AIJOB *ev);             /* 0x5725b0 */
void he_AllocMeetingScene(struct AIJOB *ev);      /* 0x5726a0 */
void he_RunMeetingScene(struct AIJOB *ev);        /* 0x5726b0 */
void he_AllocGraveyardWorkers(struct AIJOB *ev);  /* 0x572b90 */
void he_RunGraveyardWorkers(struct AIJOB *ev);    /* 0x572bf0 */
void he_RunGraveyardTheft(struct AIJOB *ev);      /* 0x572fd0 */
void he_RunGraveLease(struct AIJOB *ev);          /* 0x572a50 */

/* 0x56f980, registers the event types 0x88 .. 0x94 (called by 0x53d4b0): (0x88, 0x56fc50, 0x56fda0), (0x89, 0x570130, 0x5702e0), (0x8c, 0x570ef0, 0x571000), (0x8d, 0x571550, 0x571640), (0x8a, 0x5706e0, 0x5707a0), (0x8b, 0x572860, 0x570cc0), (0x8d again), (0x8e, 0x571990, 0x5719e0), (0x8f, 0x571ac0, 0x571c30), (0x90, 0x571f60, 0x5725b0), (0x91, 0x5726a0, 0x5726b0), (0x93, 0x572b90, 0x572bf0), (0x94, 0x55e3a0, 0x572fd0), (0x92, 0x572860, 0x572a50), then the texts of 0x52b350; 0 = ok, 1 = a registration failed */
int he_RegisterEventTypes88(void) {
  if (he_SetEventHandlers(0x88, he_AllocHaunting, he_RunHaunting) == 0) {
    if (he_SetEventHandlers(0x89, he_AllocDecay, he_RunDecay) == 0) {
      if (he_SetEventHandlers(0x8c, he_AllocMasterWork, he_RunMasterWork) ==
          0) {
        if (he_SetEventHandlers(0x8d, he_AllocGraveCare, he_RunGraveCare) ==
            0) {
          if (he_SetEventHandlers(0x8a, he_AllocPlunder, he_RunPlunder) == 0) {
            if (he_SetEventHandlers(0x8b, he_AllocPlunderOfferLease,
                                    he_RunPlunderOffer) == 0) {
              if (he_SetEventHandlers(0x8d, he_AllocGraveCare,
                                      he_RunGraveCare) == 0) {
                if (he_SetEventHandlers(0x8e, he_AllocDeathDue,
                                        he_RunDeathDue) == 0) {
                  if (he_SetEventHandlers(0x8f, he_AllocGraveTraining,
                                          he_RunGraveTraining) == 0) {
                    if (he_SetEventHandlers(0x90, he_AllocMeeting,
                                            he_RunMeeting) == 0) {
                      if (he_SetEventHandlers(0x91, he_AllocMeetingScene,
                                              he_RunMeetingScene) == 0) {
                        if (he_SetEventHandlers(0x93, he_AllocGraveyardWorkers,
                                                he_RunGraveyardWorkers) == 0) {
                          if (he_SetEventHandlers(0x94, he_AllocDueIsStart,
                                                  he_RunGraveyardTheft) == 0) {
                            if (he_SetEventHandlers(0x92,
                                                    he_AllocPlunderOfferLease,
                                                    he_RunGraveLease) == 0) {
                              sv_RegisterActivity(0x8d, "grabpflege", 1, 0x513,
                                                  -1);
                              sv_RegisterActivity(0x8c, "Rohstoffsuchen", 1,
                                                  0x500, 0xac);
                              sv_RegisterActivity(0x8f, "Upgraden", 0, 0x512,
                                                  -1);
                              sv_RegisterActivity(0x8a, 0, 0, 0x514, -1);
                              sv_RegisterActivity(0x88, 0, 0, 0x511, -1);
                              return 0;
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 1;
}
/* 0x56fbc0, ages the character c's life value f01c by num years: fnum not above f020 -> sends the delta
   f018 - f01c; else (int)(fnum - f020) steps of v = v - f014 + f014 / v from v = f018, then the delta
   v - f01c (cm_SendFloatDelta, field 0x1c) */

void he_SetLifeByAge(AICHAR *c, unsigned short num) {
  float f, v, fnum;
  int n;

  if (c == 0)
    return;
  fnum = (float)num;
  if (fnum <= c->f020) {
    cm_SendFloatDelta(c->netId, 0x1c, c->f018 - c->f01c);
    return;
  }
  v = c->f018;
  f = c->f014;
  for (n = (int)(fnum - c->f020); n > 0; n--)
    v = v - f + (f / v);
  cm_SendFloatDelta(c->netId, 0x1c, v - c->f01c);
}
/* 0x56fc50, the alloc of the event 0x88 (a work at the building +0xb0 of the player +8): paused -> nothing; with a running event 0x88 of the same player and building the text 0x4096 and state -1; else the due clock now + 1 hour and state 0 (0x4c4c60), or -1 when +0xb4 is -1, and the message 0x50cc50 (pid, -(+0xb8)) */

void he_AllocHaunting(AIJOB *e) {
  AIJOB *h = e;
  AIJOB *r;
  char text[0x400];

  if (e->opts & 4)
    return;
  for (r = he_FindEvent(1, 0, 0x88); r != 0; r = he_NextEvent()) {
    if (r != e && r->chr == e->chr && r->hauntVictim == h->hauntVictim)
      break;
  }
  if (r != 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    txt_Format(text, 0x4096, h->hauntVictim);
    he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5fa, 0);
    return;
  }
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  if (h->hauntHaunter == -1)
    e->exSlot = cm_SendExSetHE(-1, e);
  else {
    e->exSlot = cm_SendExSetHE(0, e);
    gm_SendMoneyDelta(ai_Chars[e->chr].netId, -h->hauntPaid);
  }
}

void ai_HauntingText(struct AICHAR *param_1, struct AICHAR *param_2,
                     struct AITIME *param_3); /* 0x5a9910 */

/* 0x56fda0, the run handler of the graveyard owner's haunting event 0x88 (alloc he_AllocHaunting; am.c's
   ai_ExecGraveyardOwner0 / sv_t.c post it): without the haunter the event is freed; the stages -1 / -2 take the
   haunter out of the event's group (sv_MoveToGroup) and free it; a paused event or one whose cm slot is still busy
   waits. Stage 0 puts the haunter in the group and sends it to the victim's building ("HEIMSUCHUNG", stage 2), or
   ends the event; stage 2 waits 4 minutes while it walks, then a day at the building, telling the event's
   character and the victim (ai_HauntingText), stage 3; stage 3 sends it back to its own building (stage 4), stage
   4 waits until it is there, takes it out of the group and keeps the event (stage 5) for max (paid / 2, 1) + 1
   more years; stage 5 ends it. A haunter without a building ends the event. */
void he_RunHaunting(AIJOB *e) {
  AIJOB *h = e;
  AICHAR *haunter, *victim;
  AIBLD *bld;
  int years;

  haunter = gm_FindChar(h->hauntHaunter);
  if (haunter == 0) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage == -1 || e->stage == -2) {
    sv_MoveToGroup(0, 0, haunter->id, e);
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if (cm_GetSlotState(e->exSlot) == 0)
      return;
    sv_MoveToGroup(0, 0, haunter->id, e);
    bld = gm_BuildQuery(1, 1, h->hauntHome);
    if (bld == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    h->hauntWalkSlot = cm_SendChrGotoBuilding(haunter->netId, bld->id, -1, 0, 1,
                                              "HEIMSUCHUNG");
    cm_SendExSetHE(2, e);
    return;
  case 2:
    h->hauntWalkSlot = -1;
    if (haunter->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    if (gm_BuildQuery(1, 1, h->hauntHome) != 0) {
      e->end = ai_Time;
      victim = gm_FindChar(h->hauntVictim);
      if (victim != 0) {
        gm_AddTime(&e->end, 0x18, 0, 0);
        ai_HauntingText(&ai_Chars[e->chr], victim, &e->end);
      }
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 3:
    if (haunter->bld == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    h->hauntWalkSlot = cm_SendChrGotoBuilding(haunter->netId, haunter->bld->id,
                                              -1, 0, 0, "HEIMSUCHUNG");
    e->exSlot = cm_SendExSetHE(4, e);
    return;
  case 4:
    if (haunter->bld == 0) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (haunter->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    e->end = ai_Time;
    sv_MoveToGroup(0, 0, haunter->id, 0);
    e->exSlot = cm_SendExSetHE(5, e);
    years = h->hauntPaid >> 1;
    if (years < 1)
      years = 1;
    e->end.year += years + 1;
    return;
  case 5:
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x570130, the alloc of the event 0x89 (a work at +0xb0 by the character +0xb4): paused -> nothing; with a running event 0x89 of the same player and building the text 0x40a2, state -1 and free; else the character +0xb4 missing -> free; the due clock now + 1 hour, 0x50cc50 (pid, -(+0xb8)), state 0 and 0x4f2e30 (0x1b, 1, pid, +4 of the character, the id +1 of +0x170 or -1) */

void he_AllocDecay(AIJOB *e) {
  AIJOB *d = e;
  AICHAR *per;
  AIJOB *r;
  char text[0x400];
  int id, netId;

  if (e->opts & 4)
    return;
  per = gm_FindChar(d->decayVictim);
  for (r = he_FindEvent(1, 0, 0x89); r != 0; r = he_NextEvent()) {
    if (r != e && r->chr == e->chr && r->decayVictim == d->decayVictim)
      break;
  }
  if (r != 0) {
    if (per != 0) {
      txt_Format(text, 0x40a2, per->id);
      he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5fa, 0);
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    he_FreeEvent(e);
    return;
  }
  if (gm_FindChar(d->decayAgent) == 0) {
    he_FreeEvent(e);
    return;
  }
  d->decayAged = 0;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  gm_SendMoneyDelta(ai_Chars[e->chr].netId, -d->decayPaid);
  e->stage = 0;
  if (per != 0 && per->bld2 != 0)
    id = per->bld2->id;
  else
    id = -1;
  if (per != 0)
    netId = (int)per->netId;
  else
    netId = -1;
  gv_Accuse(0x1b, 1, ai_Chars[e->chr].netId, netId, id);
}

void ai_TellGraveWorkSuccess(struct AICHAR *param_1); /* 0x5a9990 */
void ai_TellGraveWorkFailure(struct AICHAR *param_1); /* 0x5a99e0 */
void ai_GraveyardMessage(struct AICHAR *to, struct AICHAR *worker,
                         struct AICHAR *other, int detail); /* 0x5a9a30 */
void ai_GraveyardMessagePlain(struct AICHAR *param_1, struct AICHAR *param_2,
                              struct AICHAR *param_3); /* 0x5a9af0 */

/* 0x5702e0, the run handler of the graveyard owner's "breath of decay" event 0x89 (alloc he_AllocDecay; am.c's
   ai_ExecGraveyardOwner2 / sv_t.c post it): the stages -1 / -2 take the agent out of the event's group and free
   the event, a lost agent frees it too. Stage 0 puts the agent in the group, stage 1 sends it to the victim's
   building ("HAUCH DES VERFALLS"), stage 2 waits 4 minutes while it walks, then (due in an hour) rolls
   gm_Mix (agent, victim, 2) + random above 1: the victim ages by the building's level / 50 + 0 .. 2 + its type's
   level * 2 years (he_SetLifeByAge, ai_TellGraveWorkSuccess; aged = 1), else ai_TellGraveWorkFailure (aged = 0);
   stage 3 sends the agent back to its building, stage 4 waits until it is there and reports to the event's
   character (aged: ai_GraveyardMessage, its last argument 0 when random + 1 - the agent's skill 1 is above 1;
   else ai_GraveyardMessagePlain); then the event ends (stage -1)
   @original case 1 ends with break where the other cases return: VC6 then merges case 1's walk call into case
   3's copy (push text; push 1; jmp), as in he_RunPlunder; the age sum is a named local (one temporary more,
   which puts stage 3's registers on stage 1's) */
void he_RunDecay(AIJOB *e) {
  AIJOB *d = e;
  AICHAR *agent, *victim, *per;
  AIBLD *bld;
  AIBTYPE *bt;
  float chance;
  int told;
  int age;

  agent = gm_FindChar(d->decayAgent);
  if (e->stage == -1 || e->stage == -2) {
    if (agent != 0)
      sv_MoveToGroup(0, 0, agent->id, 0);
    he_FreeEvent(e);
    return;
  }
  if (agent == 0) {
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    sv_MoveToGroup(0, 0, agent->id, e);
    e->exSlot = -1;
    e->stage++;
    return;
  case 1:
    bld = gm_BuildQuery(1, 1, d->decayHome);
    if (bld == 0) {
      e->stage = -1;
      return;
    }
    cm_SendChrGotoBuilding(d->decayAgent, bld->id, -1, 0, 1,
                           "HAUCH DES VERFALLS");
    e->stage++;
    break;
  case 2:
    gm_BuildQuery(1, 1, d->decayHome);
    agent = gm_FindChar(d->decayAgent);
    if (agent == 0) {
      e->stage = -1;
      return;
    }
    if (agent->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    victim = gm_FindChar(d->decayVictim);
    agent = gm_FindChar(d->decayAgent);
    chance = gm_Mix(agent, victim, 2);
    if (victim != 0) {
      if (util_RandomF() + chance > 1.0) {
        bld = agent->bld;
        bt = &ai_BTypes[bld->type];
        d->decayAged = 1;
        age = util_Random(3) + bt->cap247 * 2 + bld->level / 50;
        he_SetLifeByAge(victim, age);
        ai_TellGraveWorkSuccess(victim);
        e->stage++;
        return;
      }
      ai_TellGraveWorkFailure(victim);
      d->decayAged = 0;
    }
    e->stage++;
    return;
  case 3:
    agent = gm_FindChar(d->decayAgent);
    if (agent == 0 || (bld = agent->bld) == 0) {
      e->stage = -1;
      return;
    }
    cm_SendChrGotoBuilding(d->decayAgent, bld->id, -1, 0, 0,
                           "HAUCH DES VERFALLS");
    e->stage++;
    return;
  case 4:
    agent = gm_FindChar(d->decayAgent);
    if (agent == 0 || agent->bld == 0) {
      e->stage = -1;
      return;
    }
    if (agent->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    gm_BuildQuery(1, 1, d->decayHome);
    victim = gm_FindChar(d->decayVictim);
    per = &ai_Chars[e->chr];
    agent = gm_FindChar(d->decayAgent);
    if (victim != 0 && per != 0 && agent != 0) {
      if (d->decayAged != 0) {
        chance = 1.0f - gm_GetSkill(agent, 1);
        if (!(util_RandomF() + chance > 1.0))
          told = 1;
        else
          told = 0;
        ai_GraveyardMessage(per, agent, victim, told);
      } else
        ai_GraveyardMessagePlain(per, agent, victim);
    }
    e->stage = -1;
    return;
  }
}

int ai_PickActionBuildings(struct AICHAR *p, int a, __int64 mask, float lo,
                           float hi, unsigned char n, int *out); /* 0x4a6570 */

/* 0x5706e0, the alloc of the plunder event 0x8a: paused -> nothing; the buildings the character (chr) can plunder are
   picked (ai_PickActionBuildings, mask 4, at most 5, into bld) -> none -> free; the picked slot of the found index
   (when below 5) is cleared, at = 0, the due clock is now + 1 hour and the event is scheduled (cm_SendExSetHE) */
void he_AllocPlunder(AIJOB *e) {
  AIJOB *p = e;
  int r;
  LARGE_INTEGER mask;

  if (e->opts & 4)
    return;
  mask.LowPart = 4;
  mask.HighPart = 0;
  r = ai_PickActionBuildings(&ai_Chars[e->chr], 5, mask.QuadPart, 0, 0, 5,
                             p->plunderBld);
  if (r == 0) {
    he_FreeEvent(e);
    return;
  }
  if (r < 5)
    p->plunderBld[r] = 0;
  p->plunderAt = 0;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  e->exSlot = cm_SendExSetHE(0, e);
}

int ai_PickPartnerRandomWalk(struct AICHAR *p, unsigned int fl, int n,
                             unsigned short *ids, float lo, float hi,
                             unsigned short *id); /* 0x4a5d30 */
void he_PlunderTakePrice(int *a, AICHAR *c);      /* 0x570bf0 */
void he_PlunderFailNews(int *a, AICHAR *c);       /* 0x570c70 */

/* 0x5707a0, the run handler of the plunder event 0x8a ("PAKT MIT DEM TOD"; alloc he_AllocPlunder): stage -1 / -2,
   a missing agent (the netId +0xac) or one without health take the agent out of the event's group
   (sv_MoveToGroup) and free the event. Stage 0 puts the agent in the group; stage 1 sends it to the building
   bld[at] (stage 2), none ends the event; stage 2 waits 10 minutes while the agent is busy, else picks a
   victim near the event's character (ai_PickPartnerRandomWalk, liking up to 100, not one of victims[]), notes
   it in victims[at] and, when the victim's worth (gm_GetWorth / gm_ConvertMoney) is above its protection price
   (gv_ProtectionPrice) and its flags1cc bit 0 is clear, asks a player victim (kind 6 / 7) with the message 0x8b,
   else takes the price (he_PlunderTakePrice) or tells of the failure (he_PlunderFailNews) by a coin throw; then the next
   building (stage 1 again) up to 5, else stage 3; stage 3 sends the agent home (stage 4), stage 4 waits 4
   minutes while it is busy there; a missing agent or home ends the event.
   @original case 1 ends with break where the other cases return: VC6 then merges case 2's closing stage++ into
   case 3's copy as the original does (with return it takes case 1's, and case 2's jumps become near jumps) */
void he_RunPlunder(AIJOB *e) {
  unsigned short idx;
  int deal[4];
  AIMSG msg;
  AIJOB *p = e;
  AICHAR *agent;
  AIBLD *bld;
  int price, worth;

  agent = gm_FindChar(p->plunderAgent);
  if (e->stage == -1 || e->stage == -2 || agent == 0 || agent->health == 0) {
    if (agent != 0)
      sv_MoveToGroup(0, 0, agent->id, 0);
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    sv_MoveToGroup(0, 0, agent->id, e);
    e->stage++;
    e->exSlot = -1;
    return;
  case 1:
    bld = gm_BuildQuery(1, 1, p->plunderBld[p->plunderAt]);
    if (bld == 0) {
      e->stage = -1;
      return;
    }
    cm_SendChrGotoBuilding(p->plunderAgent, bld->id, -1, 0, 1,
                           "PAKT MIT DEM TOD");
    e->stage++;
    break;
  case 2:
    agent = gm_FindChar(p->plunderAgent);
    if (agent == 0) {
      e->stage = -1;
      return;
    }
    if (agent->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 10, 0);
      return;
    }
    if (ai_PickPartnerRandomWalk(&ai_Chars[e->chr], PLUNDER_PARTNER_FLAGS, 4,
                                 p->plunderVictims, 0, 100.0f, &idx) != 0) {
      price = gv_ProtectionPrice(&ai_Chars[idx]);
      worth = gm_ConvertMoney(gm_GetWorth(idx), ai_OwnPlayer);
      p->plunderVictims[p->plunderAt] = idx;
      if (worth > price && !(ai_Chars[idx].flags1cc & 1)) {
        if (ai_Chars[idx].kind == 6 || ai_Chars[idx].kind == 7) {
          msg.type = 0x8b;
          msg.to = ai_Chars[idx].netId;
          msg.fromId = ai_Chars[idx].netId;
          msg.nIds = 0;
          msg.reserved14 = 0;
          msg.time = ai_Time;
          msg.flags = 9;
          msg.arg[0] = e->netId;
          msg.arg[1] = p->plunderAgent;
          msg.arg[2] = ai_Chars[idx].netId;
          msg.arg[3] = price;
          cm_SendLongMessage(&msg);
        } else {
          deal[0] = e->netId;
          deal[1] = p->plunderAgent;
          deal[2] = ai_Chars[idx].netId;
          deal[3] = price;
          if (util_Random(2) != 0)
            he_PlunderTakePrice(deal, &ai_Chars[idx]);
          else
            he_PlunderFailNews(deal, &ai_Chars[idx]);
        }
      }
      p->plunderAt++;
      if (p->plunderAt < 5 && p->plunderBld[p->plunderAt] != 0) {
        e->stage--;
        return;
      }
      e->stage++;
      return;
    }
    e->stage = -1;
    return;
  case 3:
    agent = gm_FindChar(p->plunderAgent);
    if (agent == 0 || agent->bld == 0) {
      e->stage = -1;
      return;
    }
    cm_SendChrGotoBuilding(p->plunderAgent, agent->bld->id, -1, 0, 0,
                           "PAKT MIT DEM TOD");
    e->stage++;
    return;
  case 4:
    agent = gm_FindChar(p->plunderAgent);
    if (agent == 0 || agent->bld == 0 || agent->scene->actions == 0) {
      e->stage = -1;
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 4, 0);
    return;
  }
}
/* 0x570bf0, a plunder message: 0x4c4830 (a[0], b + 4, the byte 0x6f1bc5, a[3]), 0x4c4a60 (b + 4, 0x1cc, 4, 1, 0), the text 0x40fe to a[0] (flag 1, 0x5f4) */

void he_PlunderTakePrice(int *a, AICHAR *c) {
  char text[0x400];

  cm_SendMoveGoodsUnchecked(a[0], c->netId, ai_OwnPlayer, a[3]);
  cm_SendSetField(c->netId, 0x1cc, 4, 1, 0);
  txt_Format(text, 0x40fe, c->id, a[3]);
  he_ShowNews(a[0], -1, text, 1, 0x5f4, 0);
}
/* 0x570c70, the text 0x40ff (the character's id) to a[0] (flag 1, 0x5f4) */

void he_PlunderFailNews(int *a, AICHAR *c) {
  char text[0x400];

  txt_Format(text, 0x40ff, c->id);
  he_ShowNews(a[0], -1, text, 1, 0x5f4, 0);
}

/* 0x570cc0, the run handler of the plunder offer 0x8b (he_RunPlunder sends it to a player victim; its words over
   AIJOB's union are the plunder deal AIJOB.plunderDeal*): a missing client (the deal's netId) or a player whose
   flags1cc bit 0 is set (he_RunPlunder skips such a victim) end it (stage -2: the event bar slot is released, the event freed). Stage 0 opens the
   offer window ("Berufe\Messagebox_Meisterpruefung") with the text 0x40fd (the client, the price) and the voice
   "_NACHRICHTEN_FRIEDHOF_09", stage 1; a window that could not be opened frees the event. Stage 1: past the
   due time the offer counts as refused (he_PlunderFailNews); without the window back to stage 0; a click on its
   button 0 pays the price (he_PlunderTakePrice), on button 1 refuses; either ends the event. */
void he_RunPlunderOffer(AIJOB *e) {
  AIJOB *d = e;
  AICHAR *client;
  int id;

  client = gm_FindChar(d->plunderDealDeal[0]);
  if (client == 0 || (ai_Chars[e->chr].flags1cc & 1))
    e->stage = -2;
  if (e->stage == -2) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    if (e->slot == 0)
      he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_CentreViewWindows(e->slot->win);
    d2_SetForm(e->slot->win, 0);
    io_PrintText((intptr_t)"$C");
    io_PrintText(0x40fd, client->id, d->plunderDealDeal[3]);
    snd_QueueVoice(-7, 0, "_NACHRICHTEN_FRIEDHOF_09", -1, 0);
    e->stage = 1;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_PlunderFailNews(d->plunderDealDeal, &ai_Chars[ai_PlayerId]);
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      break;
    }
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win)
      return;
    id = d2_ClickedId;
    if (id == -1)
      return;
    if (id == 0) {
      he_PlunderTakePrice(d->plunderDealDeal, &ai_Chars[ai_PlayerId]);
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (id == 1) {
      he_PlunderFailNews(d->plunderDealDeal, &ai_Chars[ai_PlayerId]);
      he_ReleaseSlot(e);
      he_FreeEvent(e);
    }
    return;
  }
}

int ai_PickPartnerRandomWalk(struct AICHAR *p, unsigned int fl, int n,
                             unsigned short *ids, float lo, float hi,
                             unsigned short *id); /* 0x4a5d30 */
void he_PlunderTakePrice(int *a, AICHAR *c);      /* 0x570bf0 */
void he_PlunderFailNews(int *a, AICHAR *c);       /* 0x570c70 */
int sv_UsedGroupSlots(struct AIJOB *g);           /* 0x5241b0 */
struct GVENTRY *gv_ListEntry(struct GVYARD *r, int i,
                             unsigned char n); /* 0x4ef570 */
void ai_HauntingText(struct AICHAR *param_1, struct AICHAR *param_2,
                     struct AITIME *param_3); /* 0x5a9910 */

/* 0x570ea0, 1 when no running haunting event 0x88 has b's netId as its character (+8) and a's netId as its victim
   (+0xb0); 0 when one does */
int he_NoEvent88Pair(AICHAR *a, AICHAR *b) {
  AIJOB *r;

  for (r = he_FindEvent(1, 0, 0x88); r != 0; r = he_NextEvent()) {
    if ((unsigned int)b->netId == r->chr && r->hauntVictim == a->netId)
      return 0;
  }
  return 1;
}
/* 0x570ef0, the alloc of the master's production job 0x8c: the building (gm_BuildQuery 0x501190 on AIJOB.from), its
   object list (gm_Query 0x4ffe90, key 0xfd), and each of the four workers (AIJOB.ids[0..3], gm_FindChar) registered
   in the group (sv_MoveToGroup 0x524260); none -> the event is freed. Else the job starts: made 0, the counted-up
   clock since = now, 0x168 working minutes left, the due clock (AIJOB.end) = now + 5 minutes, stage 0 */
void he_AllocMasterWork(AIJOB *e) {
  int i, n = 0;
  AIJOB *p = e;
  AIBLD *bld = gm_BuildQuery(1, 1, e->from);
  struct AIOBJ *grp = gm_Query(bld->objList, 2, 0, 0xfd, 6);
  AICHAR *w;

  for (i = 0; i < 4; i++) {
    w = gm_FindChar(e->ids[i]);
    if (w != 0) {
      n++;
      sv_MoveToGroup(bld, grp, w->id, e);
    }
  }
  if (n == 0) {
    he_FreeEvent(e);
    return;
  }
  p->masterworkMade = 0.0f;
  p->masterworkSince = ai_Time;
  p->masterworkLeft = 0x168;
  e->end = ai_Time;
  e->stage = 0;
  gm_AddTime(&e->end, 0, 5, 0);
}
/* 0x571000, the run handler of a master's production job 0x8c (alloc he_Unk570ef0; ai.c's master step posts it
   for a graveyard 0x1d or a gypsy camp 0x1f): outside the working hours of the season (gm_DayStartHours ..
   gm_DayEndHours) a running job only waits 5 minutes. A job without its character ends at once. The four
   workers (ids[]) are counted, the ones with the worker titles 0x1b / 0x1c at work (flags1b4 bit 0) count as
   idle; none, no building (from) or no store in it (gm_Query kind 0x2a) end the job (stage -1). Stage 0 adds
   per busy worker (skill + 1) * the minutes since `since` / 60 to `made` (the skill: gm_BuildingSkill 0x12 at
   a graveyard, else 0x1e, less 0.5 in winter without the heating bit 0x2000), takes the minutes off `left` (at
   0 the job ends) and waits 5 minutes. An ended job stores the whole units made (at least 1; none when it
   was cancelled with its group empty) in the store (gm_FreeCapacity, cm_SendExSellObject) and tells a player
   master who is not at work of it (he_MessageBoxQuickjump: the texts 0x4222 / 0x4223 / 0x4224 at a gypsy camp,
   0x412c / 0x412d / 0x412e else; a full store 0x4225 / 0x412f; the voices "_NACHRICHTEN_ZIGEUNER_03" /
   "_NACHRICHTEN_FRIEDHOF_01"); then the workers leave the group and the event is freed. The 1.0f is a literal
   (VC6's pooled 1.0f, 0x5eb780): spelled as an object VC6 loads it first and keeps the rate on
   the FPU stack (fld / fadd st, st(1)), which the original's fadd [0x5eb780] does not.
   @deep 58 ins, stack slots only (plus 6 regs / 4 order that follow them). The original's slot groups
   (read from its pushes): {loop count of the ids loop, busy, master} 0x10, {bt} 0x14, {hour, bld} 0x18,
   {the two gm_BuildingSkill int temps} 0x1c, {minutes, step} 0x20, {store} 0x24, {season} 0x28; ours {tmp,
   busy}, {minutes, step, master}, {hour, both temps}, {bt}, {store}, {season}, {bld}. c2frame replay: the
   original's groups come out exactly when master and bld each have one more counted reference (count 3:
   they are then packed before the count-2 locals: master joins busy's slot, bld opens one that hour then
   joins, the temps conflict with bld and open their own). Their counts are spill / reload IL ops (bld: the
   store after gm_BuildQuery and the reload for bld->id at the end; master: the store after
   gm_FindCharacterByMaster and one reload). s41 no lever: all 720 declaration orders (one code), removing
   hour / bt = 0 / store = 0 (draft), climb 2 rounds (958 mutants, nothing), the kind / master tests as one
   && or master outer, master read after gm_FreeCapacity. Next: a source where bld and master are reloaded
   once more before the late passes (a second use in another block, e.g. bld in the store-full arms) */
void he_RunMasterWork(AIJOB *e) {
  AIJOB *p = e;
  char voice[0x98];
  char what[0x200];
  char text[0x400];
  int season, hour, i, n, cnt, busy, minutes;
  float rate, step;
  AICHAR *w, *master;
  AIBTYPE *bt;
  AIBLD *bld;
  AIOBJ *store;

  season = gm_ClockSeason(&ai_Time);
  hour = ai_Time.hour;
  store = 0;
  cnt = 0;
  busy = 0;
  bt = 0;
  if ((float)hour >= gm_DayEndHours[season] ||
      (float)hour < gm_DayStartHours[season]) {
    if (e->stage != -1 && e->stage != -2) {
      gm_AddTime(&e->end, 0, 5, 0);
      return;
    }
  }
  if (e->chr == 0xffff || e->netId == -1) {
    he_FreeEvent(e);
    return;
  }
  for (i = 0; i < 4; i++) {
    w = gm_FindChar(e->ids[i]);
    if (w != 0) {
      cnt++;
      busy++;
      if ((w->title == 0x1b || w->title == 0x1c) && (w->flags1b4 & 1))
        busy--;
    }
  }
  if (cnt == 0)
    e->stage = -1;
  bld = gm_BuildQuery(1, 1, e->from);
  if (bld != 0) {
    bt = &ai_BTypes[bld->type];
    store = gm_Query(bld->objList, 2, 6, 0, 0x2a);
    if (store == 0)
      e->stage = -1;
  } else
    e->stage = -1;
  if (e->stage == 0) {
    minutes = gm_MinutesBetween(&p->masterworkSince, &ai_Time);
    if (bt->kind == 0x1d) {
      rate = gm_BuildingSkill(bld, 0x12, 1) * 0.01f;
    } else {
      rate = gm_BuildingSkill(bld, 0x1e, 1) * 0.01f;
      if (season == 3 && !(bld->flags5aw & 0x2000))
        rate -= 0.5f;
    }
    step = (rate + 1.0f) * minutes * 0.01667f;
    for (i = busy; i > 0; i--)
      p->masterworkMade += step;
    p->masterworkLeft -= minutes;
    p->masterworkSince = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    if (p->masterworkLeft < 0)
      e->stage = -1;
  }
  if (e->stage != -2 && e->stage != -1)
    return;
  n = (int)p->masterworkMade;
  if (n <= 1)
    n = 1;
  if (e->stage == -1 && sv_UsedGroupSlots(e) <= 0)
    n = -1;
  if (bld != 0 && store != 0 && n > 0) {
    master = gm_FindCharacterByMaster(bld);
    n = gm_FreeCapacity(store, p->masterworkGood, n);
    if (n != 0) {
      cm_SendExSellObject(store->objId, -1, p->masterworkGood, n, ai_OwnPlayer,
                          0);
      if (bt->kind == 0x1f) {
        txt_Format(text, 0x4222, 0x421e, 0x22c, bld);
        strcpy(voice, "_NACHRICHTEN_ZIGEUNER_03");
        if (n == 1)
          txt_Format(what, 0x4223, p->masterworkGood * 2 + 0x9a8);
        else
          txt_Format(what, 0x4224, n, p->masterworkGood * 2 + 0x9a8);
      } else {
        txt_Format(text, 0x412c, 0x4128, 0x228, bld);
        strcpy(voice, "_NACHRICHTEN_FRIEDHOF_01");
        if (n == 1)
          txt_Format(what, 0x412d, p->masterworkGood * 2 + 0x9a8);
        else
          txt_Format(what, 0x412e, n, p->masterworkGood * 2 + 0x9a8);
      }
      strcat(text, what);
    } else if (bt->kind == 0x1f) {
      txt_Format(text, 0x4225, 0x421e, 0x22c, bld);
      strcpy(voice, "_NACHRICHTEN_ZIGEUNER_03");
    } else {
      txt_Format(text, 0x412f, 0x4128, 0x228, bld);
      strcpy(voice, "_NACHRICHTEN_FRIEDHOF_01");
    }
    if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
      if (master == 0 || !(master->flags1b4 & 1))
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                               bld->id, -1, 0, voice);
    }
  }
  for (i = 0; i < 4; i++) {
    w = gm_FindChar(e->ids[i]);
    if (w != 0)
      sv_MoveToGroup(0, 0, w->id, 0);
  }
  he_FreeEvent(e);
}
/* 0x571550, the alloc of the grave care job 0x8d: a missing worker (AIJOB.ids[0], gm_FindChar) or building (AIJOB.from,
   gm_FindBuildingById 0x502020) frees the event; else the worker is registered (sv_MoveToGroup 0x524260) in the group
   gm_Query 0x4ffe90 on the building's object list (key 0xfd), the care done is 0, 0x1fe working minutes are left, the
   counted-up clock since and the due clock (AIJOB.end) = now, the due clock + 5 minutes, stage 0 */
void he_AllocGraveCare(AIJOB *e) {
  AIJOB *p = e;
  AICHAR *per = gm_FindChar(e->ids[0]);
  AIBLD *bld;
  AIOBJ *grp;

  if (per != 0) {
    bld = gm_FindBuildingById(e->from);
    if (bld != 0) {
      grp = gm_Query(bld->objList, 1, 0, 0xfd);
      sv_MoveToGroup(bld, grp, per->id, e);
      p->graveCareCare = 0.0f;
      p->graveCareLeft = 0x1fe;
      p->graveCareSince = ai_Time;
      e->end = ai_Time;
      e->stage = 0;
      gm_AddTime(&e->end, 0, 5, 0);
      return;
    }
  }
  he_FreeEvent(e);
}
/* 0x571640, the run handler of the grave care job 0x8d (alloc he_AllocGraveCare; ai.c's ai_GraveCare posts it with the
   grave's list size and entry): outside the working hours of the season (gm_DayStartHours .. gm_DayEndHours) a
   running job only restarts its clock and waits 5 minutes. A job without its character is freed at once. A
   missing worker (ids[0]; else it joins the event's group), building (from) or grave entry (gv_ListEntry of
   the building's graveyard) ends the job (stage -1). Stage 0 adds (4 - the entry's size) * the minutes since
   `since` * 0.1 to `care` (a quarter of it for a worker with the title 0x1b / 0x1c at work), waits 5 minutes,
   takes the minutes off `left` (at 0 the job ends) and ends it too when the entry's b0c + the care reaches
   0xff. An ended job hands the whole care to the grave (gv_OrderAdjustEntry) and tells a player master who is
   not at work of it (the text 0x4126 / 0x411e, the voice "_NACHRICHTEN_FRIEDHOF_02"); the worker leaves the
   group and the event is freed. */
void he_RunGraveCare(AIJOB *e) {
  AIJOB *g = e;
  char text[0x400];
  int season, hour, minutes, n;
  float x;
  AICHAR *w, *master;
  AIBLD *bld;
  GVENTRY *entry;

  season = gm_ClockSeason(&ai_Time);
  hour = ai_Time.hour;
  if ((float)hour >= gm_DayEndHours[season] ||
      (float)hour < gm_DayStartHours[season]) {
    if (e->stage != -1 && e->stage != -2) {
      g->graveCareSince = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      return;
    }
  }
  if (e->chr == 0xffff || e->netId == -1) {
    he_FreeEvent(e);
    return;
  }
  w = gm_FindChar(e->ids[0]);
  if (w != 0)
    sv_MoveToGroup(0, 0, w->id, e);
  else
    e->stage = -1;
  bld = gm_BuildQuery(1, 1, e->from);
  if (bld == 0)
    e->stage = -1;
  entry = gv_ListEntry(bld->yard, g->graveCareSize, g->graveCareEntry);
  if (entry == 0)
    e->stage = -1;
  if (e->stage == 0) {
    minutes = gm_MinutesBetween(&g->graveCareSince, &ai_Time);
    x = (float)(4 - entry->size) * minutes * 0.1f;
    if ((w->title == 0x1b || w->title == 0x1c) && (w->flags1b4 & 1))
      x *= 0.25f;
    g->graveCareCare += x;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    g->graveCareLeft -= minutes;
    g->graveCareSince = ai_Time;
    if (g->graveCareLeft <= 0)
      e->stage = -1;
    if (entry->b0c + (int)g->graveCareCare >= 0xff)
      e->stage = -1;
  }
  if (e->stage < -2 || e->stage >= 0)
    return;
  n = (int)g->graveCareCare;
  if (entry != 0 && n > 0) {
    gv_OrderAdjustEntry(bld, g->graveCareSize, g->graveCareEntry, n);
    if (w != 0) {
      master = gm_FindCharacterByMaster(bld);
      txt_Format(text, 0x4126, 0x411e, w->id, bld);
      if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
          (master == 0 || !(master->flags1b4 & 1)))
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                               bld->id, -1, 0, "_NACHRICHTEN_FRIEDHOF_02");
    }
  }
  if (w != 0)
    sv_MoveToGroup(0, 0, w->id, 0);
  he_FreeEvent(e);
}
/* 0x571990, the alloc of the death-due event 0x8e: the due clock (AIJOB.end) = now + 0x48 hours, stage 0 */
void he_AllocDeathDue(AIJOB *e) {

  e->end = ai_Time;
  e->stage = 0;
  gm_AddTime(&e->end, 0x48, 0, 0);
}
/* 0x5719e0, the run handler of the event 0x8e (alloc he_AllocDeathDue: due 72 hours after its start; a reasoned
   guess from what it does: the due day of a pact with death): only at the stages -2 .. 0. The event's character
   (netId) pays the price (`price`, cm_SendMoveGoods to nobody) when its money (gm_CharCurrency) is above it;
   else every living relative of relatives[3..7] (the descendants ai_DecideUseDynastyObject walks) loses 1001
   health (gm_AddHealth), or the character itself when there is none. The event is then freed (twice on the
   unpaid path, as the original does: once in the branch, once at the end). */
void he_RunDeathDue(AIJOB *e) {
  AIJOB *d = e;
  AICHAR *ch, *r;
  int i, found, money;

  if (e->stage < -2 || e->stage > 0)
    return;
  ch = gm_FindChar(e->netId);
  if (ch != 0) {
    money = gm_CharCurrency(ch, ai_OwnPlayer);
    if (money > d->deathDuePrice)
      cm_SendMoveGoods(-1, ch->netId, ai_OwnPlayer, d->deathDuePrice);
    else {
      found = 0;
      for (i = 0; i < 5; i++) {
        if (ch->relatives[3 + i] != -1) {
          r = gm_FindChar(ch->relatives[3 + i]);
          if (r != 0) {
            gm_AddHealth(r->id, -1001);
            found = 1;
          }
        }
      }
      if (!found)
        gm_AddHealth(ch->id, -1001);
      he_FreeEvent(e);
    }
  }
  he_FreeEvent(e);
}
/* 0x571ac0, the alloc of the grave training job 0x8f: a missing trainee (AIJOB.graveTrainingTrainee, gm_FindChar), a
   trainee already on a running job 0x8f (AICHAR.job's kind) or a missing building (AIJOB.from, gm_BuildQuery 0x501190)
   frees the event; with an object id (AIJOB.graveTrainingObjId != -1) the group is gm_Query 0x4ffe90 on the building's
   object list (key 0xfd, the object 6, the id); the due clock (AIJOB.end) and the start clock (AIJOB.start) = now, the
   trainee is registered (sv_MoveToGroup 0x524260) in the group (or alone without one), the second clock (AIJOB.clock60)
   = now, the due clock + 0x1e minutes (gm_AddTime 0x4fe140), and until = the due clock, 3 hours later */
void he_AllocGraveTraining(AIJOB *e) {
  AIJOB *p = e;
  struct AIOBJ *grp = 0;
  AICHAR *per = gm_FindChar(p->graveTrainingTrainee);
  AIBLD *bld;

  if (per != 0 && (per->job == 0 || (unsigned char)per->job->kind != 0x8f) &&
      (bld = gm_BuildQuery(1, 1, e->from)) != 0) {
    if (p->graveTrainingObjId != -1)
      grp = gm_Query(bld->objList, 2, 6, 1, p->graveTrainingObjId);
    e->end = ai_Time;
    e->start = ai_Time;
    if (grp != 0)
      sv_MoveToGroup(bld, grp, per->id, e);
    else
      sv_MoveToGroup(bld, 0, per->id, e);
    e->clock60 = ai_Time;
    gm_AddTime(&e->end, 0, 0x1e, 0);
    p->graveTrainingUntil = e->end;
    gm_AddTime(&p->graveTrainingUntil, 3, 0, 0);
  } else
    he_FreeEvent(e);
}
/* 0x571c30, the run handler of the training job 0x8f (ai_SendFreeSpies posts its message for the free characters
   of a graveyard building: the trainee's netId, the skill index 1 / 2 / 4, the object 0x211's id; alloc
   he_AllocGraveTraining): only at the stages -2 .. 0, -1 / -2 free the event. Stage 0, while the trainee's skill is
   below 252 and the end time `until` is not reached: every 30 minutes the skill gains the working minutes
   (gm_WorkMinutesBetween since clock60) / 30 * 8 * (1 + the building's skill 0xc / 100), divided by
   (1 + skill / 252) and capped at 252 (sent as a field value of the character, cm_AddFieldValues); a missing
   building frees the event. At the end (no trainee, the skill full or the time up) a player whose master is not
   at work is told (the text 0x1bc8 at the object, else at the building's main room; the voice
   "_NACHRICHTEN_HS_81"), the trainee leaves the group and the event is freed. The gain's spelling
   S * ((minutes / 30.0) * 8.0) gives the original's fmul order (the parentheses keep 1/30 and 8.0 apart and
   unfolded, the building factor first; he_RunStudy byte with it). */
void he_RunGraveTraining(AIJOB *e) {
  AIJOB *t = e;
  char text[0x200];
  int minutes;
  float bskill;
  unsigned char *skill;
  AICHAR *ch, *master;
  AIBLD *bld;
  AIOBJ *obj;

  if (e->stage < -2)
    return;
  if (e->stage < 0) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0)
    return;
  ch = gm_FindChar(t->graveTrainingTrainee);
  if (ch != 0 && (float)ch->skills[t->graveTrainingSkill] < 252.0f &&
      gm_CompareTime(&ai_Time, &t->graveTrainingUntil) < 0) {
    unsigned char gain;

    bld = gm_BuildQuery(1, 1, e->from);
    if (bld == 0) {
      he_FreeEvent(e);
      return;
    }
    bskill = (float)gm_BuildingSkill(bld, 0xc, 1);
    minutes = gm_WorkMinutesBetween(&e->clock60, &ai_Time, bld);
    gain = (unsigned char)((bskill * 0.01 + 1.0) * ((minutes / 30.0) * 8.0));
    skill = &ch->skills[t->graveTrainingSkill];
    gain = (unsigned char)(gain / (*skill * (1.0f / 252) + 1.0));
    if ((float)(gain + *skill) > 252.0f)
      gain = (unsigned char)(252.0f - *skill);
    cm_BeginFieldBlock(ch, ch->netId);
    cm_AddFieldValues(
        1, 1, (char *)&ch->skills[t->graveTrainingSkill] - cm_FieldObject,
        &gain);
    cm_SendFieldDeltas();
    e->end = ai_Time;
    e->clock60 = ai_Time;
    gm_AddTime(&e->end, 0, 0x1e, 0);
    return;
  }
  ch = gm_FindChar(t->graveTrainingTrainee);
  bld = gm_BuildQuery(1, 1, e->from);
  if (bld == 0 || ch == 0) {
    he_FreeEvent(e);
    return;
  }
  master = gm_FindCharacterByMaster(bld);
  if (master == 0 || !(master->flags1b4 & 1)) {
    obj = gm_Query(bld->objList, 1, 1, t->graveTrainingObjId);
    if (obj == 0)
      obj = gm_GetGebaeudeHauptraum(bld);
    if (obj != 0) {
      txt_Format(text, 0x1bc8, ch->id, bld);
      he_MessageBoxQuickjump(ai_Chars[e->chr].netId, e->from, text, 0, 0x5f2,
                             bld->id, obj->objId, ch_EmptyName,
                             "_NACHRICHTEN_HS_81");
    }
  }
  sv_MoveToGroup(bld, 0, ch->id, 0);
  he_FreeEvent(e);
}
/* 0x571f60, the alloc of the meeting event 0x90: stage 0, then paused -> nothing; the due clock = now; another
   running event 0x90 of the building (from) -> exSlot = cm_SendExSetHE(-1, ev) and return; else the message 0x91
   (to the netId, from the building bldId, the clock, flags 0xa, arg 0 = the id, arg 1 = -1, arg 2 = unkb0) is
   sent, unkb4 / unkb0 are capped at 2, unkb8 = 0, the money -((unkb4 + 2) * (unkb0 + 2)) is taken from the
   character, due now + 5 hours, then the event is scheduled (cm_SendExSetHE) */
void he_AllocMeeting(AIJOB *e) {
  AIJOB *m = e;
  AIMSG msg;
  AIJOB *r;

  e->stage = 0;
  if (e->opts & 4)
    return;
  e->end = ai_Time;
  for (r = he_FindEvent(2, 0, 0x90, 3, e->from); r != 0; r = he_NextEvent()) {
    if (r != e) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
  }
  memset(&msg, 0, sizeof(msg));
  msg.type = 0x91;
  msg.to = e->netId;
  msg.fromId = m->meetingBld;
  msg.time = ai_Time;
  msg.flags = 0xa;
  msg.arg[0] = e->id;
  msg.arg[1] = -1;
  msg.arg[2] = m->meetingRadius;
  cm_SendLongMessage(&msg);
  m->meetingRounds = 0;
  if (m->meetingKind > 2)
    m->meetingKind = 2;
  if (m->meetingRadius > 2)
    m->meetingRadius = 2;
  gm_SendMoneyDelta(ai_Chars[e->chr].netId,
                    -((m->meetingKind + 2) * (m->meetingRadius + 2)));
  gm_AddTime(&e->end, 0, 5, 0);
  cm_SendExSetHE(0, e);
}

/* 0x5720f0, the meeting's disease lottery (he_SpreadMeetingDisease calls it per character): with the chance `chance`
   (util_RandomF) the character ch catches one of the diseases of the group `kind` that it does not have yet (its
   word v02c holds the diseases 2 .. 9 as bit fields): kind 2 the diseases 2 / 3, kind 1 the diseases 4 / 5, any
   other 6 and a coin throw of 7 / 8 (one of two free ones by a coin throw). The disease's record (gm_GetDisease)
   gives its severity util_Random(range); a severity above 0 is written into the disease's bit field (a field
   delta of v02c) and costs severity * the record's cost health (gm_AddHealth), the health left stored in *health
   when given. Returns the disease kind, 0 when none was caught.
   @deep deep s48: a = 0; b = 0; at the top with delta (the field-delta int) as a block local of the
   lottery block gives the original's frame 0x10 (function-scope delta: 0x14), but a still in memory
   (c2trace: a#1 prio -8 split alone where ch#1 prio 0 took ebp; the original never keeps ch in a register:
   [esp+0x24] reloaded in every arm). 127 variants (a / b init orders and the < form x delta / d / res /
   bits as block locals x cost after the sev test): best with the original frame 76 ins; climb round 1 from
   that base: nothing. Left: the 2-ins xor ebx,ebx place (the tree's text). prior: deep s24: the severity
   as its own local sev (not the reused b) = the same code, kept (one register either way, esi). a = 0
   before the call again with the pick written as (a == 0 || (b != 0 && rnd == 0)) { if (b == 0) return 0;
   a = b; } (or: 3 ins with a = 0 inside, 79 with a = 0 at the top), if / else-if + one if (a == 0) return
   0 (7 / 79), the zero test first (23 / 97): a = 0 at the top always lets ch#1 (prio -1) take ebp before
   a#1 (-12, c2trace), frame 0x14. Left: the original's xor ebx,ebx before the util_RandomF call (ours
   after the chance test). */
int he_CatchMeetingDisease(AICHAR *ch, float chance, int kind, float *health) {
  unsigned int bits, delta;
  GMDISEASE d;
  int a, b, sev, cost;
  float res;

  b = 0;
  if (!(util_RandomF() >= chance)) {
    a = 0;
    if (kind == 2) {
      if ((ch->ailments & 0xf0) == 0)
        a = 2;
      if ((ch->ailments & 0xf00) == 0)
        b = 3;
    } else if (kind == 1) {
      if ((ch->ailments & 0x3000) == 0)
        a = 4;
      if ((ch->ailments & 0x1c000) == 0)
        b = 5;
    } else {
      if ((ch->ailments & 0xe0000) == 0)
        a = 6;
      b = util_Random(2) ? 7 : 8;
      if ((ch->ailments & 0x1800000) != 0 && b == 8)
        b = 0;
      if ((ch->ailments & (7 << 0x14)) != 0 && b == 7)
        b = 0;
    }
    if (a != 0) {
      if (b != 0 && util_Random(2) == 0)
        a = b;
    } else {
      if (b == 0)
        return 0;
      a = b;
    }
    bits = ch->ailments;
    if (gm_GetDisease(a, &d) == 0)
      return a;
    sev = util_Random(d.range);
    cost = (int)(sev * d.cost);
    if (sev == 0)
      return a;
    if (a == 2)
      bits ^= ((sev << 4) ^ bits) & 0xf0;
    else if (a == 3)
      bits ^= ((sev << 8) ^ bits) & 0xf00;
    else if (a == 4)
      bits ^= ((sev << 0xc) ^ bits) & 0x3000;
    else if (a == 5)
      bits ^= ((sev << 0xe) ^ bits) & 0x1c000;
    else if (a == 6)
      bits ^= ((sev << 0x11) ^ bits) & 0xe0000;
    else if (a == 7)
      bits ^= ((sev << 0x14) ^ bits) & (7 << 0x14);
    else if (a == 8)
      bits ^= ((sev << 0x17) ^ bits) & 0x1800000;
    else if (a == 9)
      bits ^= ((sev << 0x19) ^ bits) & 0x1e000000;
    delta = bits;
    cm_BeginFieldBlock(ch, ch->netId);
    cm_AddFieldDelta(4, 1, 0x2c, &delta);
    cm_SendFieldDeltas();
    res = gm_AddHealth(ch->id, -cost);
    if (health != 0)
      *health = res;
    return a;
  }
  return 0;
}
/* 0x572310, the disease spread of a meeting (the meeting event 0x90's run handler calls it): around the building
   b (it needs its 3D object) every other building of a kind in the meeting mask (the kinds 1, 2, 4, 8, 0xa, 0xe,
   0x12 .. 0x16, 0x1f and 0x20) with an owner who is not the player and an object within the radius (radius kind 2:
   1500, 1: 800, else 400) is visited; each character of the round's quarter (netId & 3 == group: the meeting
   passes its round AIJOB.meetingRounds) who works there (bld:
   mode 3), lives there (bld2: mode 2) or owns it (mode 1) gets the disease lottery he_CatchMeetingDisease of the
   kind group `kind` with the chance (1 - dist / radius) * 0.5 + 0.25. A disease caught by a worker is reported as
   the owner's character illness (he_CharIllness); one caught by a player owner (kind 6 / 7) is told to it (the
   text 0x163c with the disease's name 0x1632 + kind). The positions are three 16-byte vectors as the original's
   frame shows (0x844: the text, five words, three D3VECTOR4). */
void he_SpreadMeetingDisease(AIBLD *b, int radiusKind, int kind, int group) {
  char text[0x800];
  float lim, dist, f, len;
  D3VECTOR4 pos, at, d;
  unsigned int lo, hi;
  int i, n, v, mode;
  AIBTYPE *bt;
  AIBLD *rec;
  AICHAR *owner, *ch;
  D3OBJECT *o;

  if (b->object == 0)
    return;
  if (radiusKind == 2)
    lim = 1500.0f;
  else if (radiusKind == 1)
    lim = 800.0f;
  else
    lim = 400.0f;
  o = b->object;
  pos.x = (o->pos.x);
  pos.y = (o->pos.y);
  pos.z = (o->pos.z);
  for (n = 0; n < 0x100; n++) {
    rec = &ai_Blds[n];
    lo = 0;
    bt = &ai_BTypes[rec->type];
    hi = 0;
    if ((unsigned char)bt->kind > 0x1f)
      hi = 1 << ((unsigned char)bt->kind - 0x20);
    else
      lo = 1 << (unsigned char)bt->kind;
    if (rec->owner == 0xffff || rec->owner == ai_PlayerChar->id)
      continue;
    if (rec->object == 0)
      continue;
    if ((lo & MEETING_KINDS_LO) == 0 && (hi & MEETING_KINDS_HI) == 0)
      continue;
    o = rec->object;
    at.x = (o->pos.x);
    at.y = (o->pos.y);
    at.z = (o->pos.z);
    d.x = pos.x - at.x;
    d.y = pos.y - at.y;
    d.z = pos.z - at.z;
    owner = &ai_Chars[rec->owner];
    len = (float)sqrt(d.z * d.z + d.y * d.y + d.x * d.x);
    if ((dist = len) > lim)
      continue;
    for (i = 0; i < 0x300; i++) {
      ch = &ai_Chars[i];
      if (ch->id == 0xffff || ch->kind >= 0xa || (int)(ch->netId & 3) != group)
        continue;
      if (ch->bld != 0 && ch->bld == rec)
        mode = 3;
      else if (ch->bld2 != 0 && ch->bld2 == rec)
        mode = 2;
      else if (owner == ch)
        mode = 1;
      else
        continue;
      v = he_CatchMeetingDisease(ch, (1.0f - dist / lim) * 0.5f + 0.25f, kind,
                                 &f);
      if (v != 0) {
        if (mode == 3)
          he_CharIllness(0, ch, owner, rec, v, f);
        else if (mode == 1 && (ch->kind == 6 || ch->kind == 7)) {
          txt_Format(text, 0x163c, v + 0x1632);
          he_ShowNews(ch->netId, -1, text, 0, 0x5f7, ch_EmptyName);
        }
      }
    }
  }
}
/* 0x5725b0, the run handler of the meeting event 0x90: a stage -2 / -1 frees the event (and continues, as in the
   original); paused (AIJOB.opts bit 4) -> nothing; the due clock (AIJOB.end) = now; a missing building (AIJOB.meetingBld,
   gm_BuildQuery 0x501190) tells the client -1 (cm_SendExSetHE 0x4c4c60); a stage other than 0 does nothing; stage 0 with
   fewer than 4 rounds holds one (he_SpreadMeetingDisease 0x572310 on the radius / kind / rounds, the due clock + 0x1e
   minutes, rounds + 1, tells the client 0); else stage -1, the due clock + 0x16 hours and the client -1 */
void he_RunMeeting(AIJOB *e) {
  AIJOB *p = e;
  AIBLD *bld;

  if (e->stage == -2 || e->stage == -1)
    he_FreeEvent(e);
  if (e->opts & 4)
    return;
  e->end = ai_Time;
  bld = gm_BuildQuery(1, 1, p->meetingBld);
  if (bld == 0) {
    cm_SendExSetHE(-1, e);
    return;
  }
  if (e->stage != 0)
    return;
  if (p->meetingRounds < 4) {
    he_SpreadMeetingDisease(bld, p->meetingRadius, p->meetingKind,
                            p->meetingRounds);
    gm_AddTime(&e->end, 0, 0x1e, 0);
    p->meetingRounds = p->meetingRounds + 1;
    cm_SendExSetHE(0, e);
    return;
  }
  e->stage = -1;
  gm_AddTime(&e->end, 0x16, 0, 0);
  cm_SendExSetHE(-1, e);
}
/* 0x5726a0, the alloc of the meeting scene event 0x91: stage 0 */
void he_AllocMeetingScene(AIJOB *e) { e->stage = 0; }
/* 0x5726b0, the run of the event 0x91 (the meeting scene object): while the partner event 0x90 (he_FindEvent) is
   active and the building (gm_BuildQuery, the event's from) has a scene object, it keeps the scene object the event
   holds (evt_FindById, its tag 0x66675073 and the building id) or loads the big / middle / small NEBEL_DES_GRAUENS
   script by the kind (evt_Load), marks it, selects the scene (d3if_SelectScene), raises the building's position 500
   (d3_PointToWorld) and runs the script with it (evt_RunScriptArgs), then keeps the script's id; without them it
   stops the old object (evt_Stop) and frees the event (he_FreeEvent) */
void he_RunMeetingScene(AIJOB *e) {
  AIJOB *m = e;
  AIJOB *other;
  AIBLD *bld;
  D3OBJECT *o;
  EVTSCRIPT *obj;
  D3VECTOR4 p; /* the engine's padded vector (the original's frame is 0x10) */
  int scene;

  other = he_FindEvent(1, 1, m->meetScenePartner);
  bld = gm_BuildQuery(1, 1, e->from);
  if (bld != 0 && bld->object != 0 && other != 0 && other->stage != -2 &&
      other->stage != -1) {
    if (m->meetSceneObj != -1) {
      obj = evt_FindById(m->meetSceneObj);
      if (obj != 0) {
        if (obj->tag[0] == HE_MEET_MARK && obj->tag[1] == e->from)
          return;
        m->meetSceneObj = -1;
      }
    }
    if (m->meetSceneKind == 2)
      obj = evt_Load("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_GROSS.esc");
    else if (m->meetSceneKind == 1)
      obj =
          evt_Load("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_MITTEL.esc");
    else
      obj = evt_Load("LOCATIONS\\NEKROMANTENTURM\\NEBEL_DES_GRAUENS_KLEIN.esc");
    if (obj == 0)
      return;
    obj->tag[0] = HE_MEET_MARK;
    obj->tag[1] = e->from;
    scene = d3_CurrentScene;
    d3if_SelectScene(0, 1);
    o = bld->object;
    d3_PointToWorld(o, &o->pos, &p.v);
    p.y += 500.0f;
    evt_RunScriptArgs(obj, 3, (int)p.x, (int)p.y, (int)p.z);
    obj->group = 0;
    d3if_SelectScene(scene, 1);
    m->meetSceneObj = obj->id;
    return;
  }
  obj = evt_FindById(m->meetSceneObj);
  if (obj != 0 && obj->tag[0] == HE_MEET_MARK && obj->tag[1] == e->from) {
    scene = d3_CurrentScene;
    d3if_SelectScene(0, 1);
    evt_Stop(obj);
    d3if_SelectScene(scene, 1);
  }
  he_FreeEvent(e);
}
/* 0x572860, the alloc of the plunder offer / grave lease events 0x8b and 0x92: the due clock (AIJOB.end) = now; an
   hour (AIJOB.end.hour) at 0x17 (23:00) or later -> the due clock + 0x18 hours with the hour set to 0xc (noon), else
   the due clock + 6 hours; stage 0 */
void he_AllocPlunderOfferLease(AIJOB *e) {

  e->end = ai_Time;
  if (e->end.hour >= 0x17) {
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 0xc;
  } else
    gm_AddTime(&e->end, 6, 0, 0);
  e->stage = 0;
}

void ai_ShowGraveOrderExtended(struct AICHAR *param_1, struct AICHAR *param_2,
                               int param_3, int param_4, int param_5,
                               int param_6); /* 0x5a97e0 */
void ai_ShowGraveOrderCancelled(struct AICHAR *param_1, struct AICHAR *param_2,
                                int param_3, int param_4); /* 0x5a9880 */
int gv_OrderExtendGrave(struct AICHAR *c, struct AIBLD *o, int v, int b,
                        short s, int x);    /* 0x4f0700 */
void he_AnswerGraveLease(struct AIJOB *ev); /* 0x5728d0 */
void he_ExamCancelled(struct AIJOB *ev);    /* 0x5729c0 */

/* 0x5728d0, the answer of the grave lease offer event 0x92 (the run handler 0x572a50 calls it with the event): when
   the building (+0xac) is a graveyard (ai_BTypes kind 0x1d), it extends the lease of the character (+0xc) on it
   (gv_OrderExtendGrave: size +0xb0, entry +0xb4, years +0xbc, price +0xb8); when that character is not the building's
   owner and its kind is 6 / 7, the owner is told (ai_ShowGraveOrderExtended with the size's sale share of the price) */
void he_AnswerGraveLease(AIJOB *e) {
  AIJOB *l = e;
  AIBLD *bld;
  AICHAR *per;
  int n;

  bld = gm_BuildQuery(1, 1, l->graveLeaseBld);
  if (bld == 0 || ai_BTypes[bld->type].kind != 0x1d)
    return;
  per = gm_FindChar(e->netId);
  if (per == 0)
    return;
  gv_OrderExtendGrave(per, bld, l->graveSize, l->graveEntry, l->graveLeaseYears,
                      l->graveLeasePrice);
  if (per == &ai_Chars[bld->owner])
    return;
  if (ai_Chars[bld->owner].kind != 6 && ai_Chars[bld->owner].kind != 7)
    return;
  n = (int)((float)l->graveLeasePrice * gv_SaleShares[l->graveSize]);
  ai_ShowGraveOrderExtended(&ai_Chars[bld->owner], per, (int)bld, l->graveSize,
                            l->graveLeasePrice, n);
}
/* 0x5729c0, the master exam cancelled (the answer "no" of the exam window, its due time over): when the
   answer's building (0x501190 (1, 1, bldId)) is of the kind 0x1d (a graveyard), the grave order is freed
   (0x4f0900 (0, building, graveSize, graveEntry)) and the owner of the building is told of the character
   (0x5a9880 (the owner record, the character, the building, graveSize)) */

void he_ExamCancelled(AIJOB *e) {
  AIBLD *bld = gm_BuildQuery(1, 1, e->bldId);
  AICHAR *per;

  if (bld == 0 || ai_BTypes[bld->type].kind != 0x1d)
    return;
  gv_OrderSetGraveHolder(0, bld, e->graveSize, e->graveEntry);
  per = gm_FindChar(e->netId);
  if (per != 0)
    ai_ShowGraveOrderCancelled(&ai_Chars[bld->owner], per, (int)bld,
                               e->graveSize);
}
/* 0x572a50, the run handler of the grave lease offer 0x92 (gv_GraveyardTurn posts it to the player whose grave lease
   runs out; its words over AIJOB's union are AIJOB.graveLease*): stage -2 releases the event bar slot and frees the
   event. Stage 0 opens the offer window ("Berufe\Messagebox_Meisterpruefung") with the text 0x411c (the price) and
   the voice "_NACHRICHTEN_FRIEDHOF_07", stage 1; a window that could not be opened frees the event. Stage 1: past
   the due time the lease ends (he_ExamCancelled frees the grave); without the window back to stage 0; a click on
   its button 0 extends the lease (he_AnswerGraveLease), on button 1 refuses it; either ends the event. */
void he_RunGraveLease(AIJOB *ev) {
  AIJOB *l = ev;
  int id;

  if (ev->stage == -2) {
    if (ev->slot != 0)
      he_ReleaseSlot(ev);
    he_FreeEvent(ev);
    return;
  }
  switch (ev->stage) {
  case 0:
    if (ev->slot == 0)
      he_OpenEventSlot(ev, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    if (ev->slot == 0) {
      he_FreeEvent(ev);
      return;
    }
    d2_CentreViewWindows(ev->slot->win);
    d2_SetForm(ev->slot->win, 0);
    io_PrintText((intptr_t)"$C");
    io_PrintText(0x411c, l->graveLeasePrice);
    snd_QueueVoice(-7, 0, "_NACHRICHTEN_FRIEDHOF_07", -1, 0);
    ev->stage = 1;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &ev->end) > 0) {
      he_ExamCancelled(ev);
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
      break;
    }
    if (ev->slot == 0) {
      ev->stage = 0;
      return;
    }
    if (d2_ClickedForm != ev->slot->win)
      return;
    id = d2_ClickedId;
    if (id == -1)
      return;
    if (id == 0) {
      he_AnswerGraveLease(ev);
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
      return;
    }
    if (id == 1) {
      he_ExamCancelled(ev);
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
    }
    return;
  }
}

/* 0x572b90, the alloc of the graveyard workers event 0x93: the due clock (AIJOB.end) = now, set to 6:00 (gm_SetTime
   0x4fe1e0); the second clock (AIJOB.clock60) = the due clock */
void he_AllocGraveyardWorkers(AIJOB *e) {

  e->end = ai_Time;
  gm_SetTime(&e->end, 6, 0, 0);
  e->clock60 = e->end;
}

void ai_EndCharExtra(struct AICHAR *o, int f); /* 0x587c40 */
int ls_GetLanguage();                          /* 0x5190a0 */

/* 0x572bf0, the run handler of the graveyard workers' event 0x93 (alloc 0x572b90, first due at 6:00), a four-stage
   cycle over every graveyard building (gm_BuildQuery (1, 5, 0x1d)): -2 / -1 free the event. Stage 0, for each owned
   graveyard: its workers (the characters whose bld is it) are tested against 0.75 + 0.0025 * the building's skill
   0x15; one above it whose job is 4 / 0x8c / 0x8d and who is not player-led (flags1b4 bit 0) ends that job
   (ai_EndCharExtra (.., 1)); one below it and above 0.5, without a job, whose owner's opinion of him beats
   -random(0x4a), gets the message 0x94 (to the event's character, from the building, arg[0] his netId). Stage 1,
   for each graveyard: its player-led workers of the job 0 / 4 / 0x8c / 0x8d other than the master (gm_FindCharacterByMaster)
   end their job (ai_EndCharExtra (.., 0)) above 0.75, or below it when the master is player-led and the worker has a
   model. Both stages are due again in 20 + random(20) minutes, the stages 2 and 3 in 30 minutes (3 back to 0).
   While a graveyard has no owner (0xffff) stage 0 never takes the next one: the original's loop is written so. */
void he_RunGraveyardWorkers(AIJOB *e) {
  AICHAR *chars[0x20];
  AIBLD *bld;
  AICHAR *ch, *master;
  float r, chance;
  int i, n, v;

  switch (e->stage) {
  case 0:
    bld = gm_BuildQuery(1, 5, 0x1d);
    while (bld != 0) {
      if (bld->owner != 0xffff) {
        chance = (float)gm_BuildingSkill(bld, 0x15, 1) * 0.0025f;
        n = 0;
        for (ch = ai_Chars; (intptr_t)ch < (intptr_t)&ai_Chars[768]; ch++) {
          if (ch->id != 0xffff && ch->bld == bld)
            chars[n++] = ch;
        }
        i = 0;
        if (n > 0) {
          AIMSG msg;

          chance += 0.75f;
          while (i < n) {
            r = util_RandomF();
            if (r > chance) {
              ch = chars[i];
              if (!(ch->flags1b4 & 1) &&
                  (ch->jobKind == 4 || ch->jobKind == 0x8c ||
                   ch->jobKind == 0x8d))
                ai_EndCharExtra(ch, 1);
            } else if (r > 0.5) {
              ch = chars[i];
              if (ch->job == 0) {
                v = gm_Opinion(bld->owner, ch->id);
                if (-util_Random(0x4a) < v) {
                  memset(&msg, 0, sizeof(msg));
                  msg.type = 0x94;
                  msg.to = e->chr;
                  msg.fromId = bld->id;
                  msg.time = ai_Time;
                  msg.flags = 1;
                  msg.arg[0] = ch->netId;
                  cm_SendLongMessage(&msg);
                }
              }
            }
            i++;
          }
        }
        bld = gm_BuildNext();
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0x14 + util_Random(0x14), 0);
    e->stage++;
    break;
  case 1:
    for (bld = gm_BuildQuery(1, 5, 0x1d); bld != 0; bld = gm_BuildNext()) {
      n = 0;
      master = gm_FindCharacterByMaster(bld);
      for (ch = ai_Chars; (intptr_t)ch < (intptr_t)&ai_Chars[768]; ch++) {
        if (ch->id != 0xffff && ch->bld == bld)
          chars[n++] = ch;
      }
      gm_BuildingSkill(bld, 0x15, 1);
      for (i = 0; i < n; i++) {
        ch = chars[i];
        if (!(ch->flags1b4 & 1))
          continue;
        if (ch->jobKind != 4 && ch->jobKind != 0x8c && ch->jobKind != 0x8d &&
            ch->jobKind != 0)
          continue;
        if (master != 0 && master == ch)
          continue;
        if (util_RandomF() > 0.75f ||
            (master != 0 && (master->flags1b4 & 1) && ch->scene != 0))
          ai_EndCharExtra(ch, 0);
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0x14 + util_Random(0x14), 0);
    e->stage++;
    break;
  case 2:
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0x1e, 0);
    e->stage++;
    break;
  case 3:
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0x1e, 0);
    e->stage = 0;
    break;
  case -2:
  case -1:
    he_FreeEvent(e);
    break;
  }
}
/* 0x572fd0, the run handler of the graveyard worker's theft 0x94 (he_RunGraveyardWorkers posts its message for a
   worker without a job whose owner's opinion beat a random draw; arg[0], here AIJOB.graveTheftWorker, is his netId):
   -2 / -1 free the event. Stage 0: a missing worker or one without a building ends it, and so does an owner's
   opinion of him above -26. Else one object of the building's store (the object 0x2a, else 0x116 in its object
   list) is picked at random and sold away (cm_SendExSellObject (-1, the store, its good, 1, ai_OwnPlayer, 0)), the
   player of the event is told (the text 0x414b with 0x229, the building and the good's name 0x9a8 + 2 * good, their
   order by the language; the voice "_NACHRICHTEN_FRIEDHOF_06", the quick jump to the building's main object), and
   the event is freed. "Theft" is a reasoned guess from the sale to nobody and the news. */
void he_RunGraveyardTheft(AIJOB *ev) {
  AIJOB *t = ev;
  AICHAR *per;
  AIBLD *bld;
  AIOBJ *store, *main, *obj;
  int n;
  AIOBJ *objs[0x20];
  char text[0x400];

  switch (ev->stage) {
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  case 0:
    break;
  default:
    return;
  }
  per = gm_FindChar(t->graveTheftWorker);
  if (per == 0) {
    he_FreeEvent(ev);
    return;
  }
  bld = per->bld;
  if (bld == 0) {
    he_FreeEvent(ev);
    return;
  }
  if (gm_Opinion(bld->owner, per->id) > -0x1a) {
    he_FreeEvent(ev);
    return;
  }
  store = gm_Query(bld->objList, 2, 6, 0, 0x2a);
  if (store == 0)
    store = gm_Query(bld->objList, 2, 6, 0, 0x116);
  main = gm_BuildingMainObject(bld);
  if (store == 0)
    goto done;
  n = 0;
  memset(objs, 0, sizeof objs);
  obj = gm_Query(store->list, 1, 5);
  while (obj != 0) {
    objs[n++] = obj;
    obj = gm_QueryNext();
  }
  if (n == 0)
    goto done;
  obj = objs[util_Random(n)];
  if (obj == 0)
    goto done;
  gm_GoodsPrice(obj->id, ai_OwnPlayer);
  cm_SendExSellObject(-1, store->objId, obj->id, 1, ai_OwnPlayer, 0);
  switch (ls_GetLanguage()) {
  case 0:
  case 2:
    txt_Format(text, 0x414b, 0x229, per->bld, obj->id * 2 + 0x9a8);
    break;
  case 1:
    txt_Format(text, 0x414b, 0x229, obj->id * 2 + 0x9a8, per->bld);
    break;
  }
  he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, -1, text, 0, 0x5f2, bld->id,
                         main->objId, 0, "_NACHRICHTEN_FRIEDHOF_06");
done:
  he_FreeEvent(ev);
}
/* 0x573200, 1 when a graveyard work is pending on a grave: an event of the type 0x8d (the work ai_StartBuildingWork
   posts) of the building bld (its id, the event's search key) whose grave care words (AIJOB.graveCareSize / entry)
   are the grave's size (list) and its index in that list */
int he_HasGraveWork(AIBLD *bld, int size, int index) {
  AIJOB *g;
  AIJOB *ev;

  ev = he_FindEvent(2, 3, bld->id, 0, 0x8d);
  while (ev != 0) {
    g = ev;
    if (g->graveCareSize == size && g->graveCareEntry == index)
      return 1;
    ev = he_NextEvent();
  }
  return 0;
}

void he_AllocCouncil(struct AIJOB *ev); /* 0x573280 */
void he_RunCouncil(struct AIJOB *ev);   /* 0x5732d0 */

/* 0x573260, registers the event type 0xa2 (called by 0x53d4b0): the pair (0x573280, 0x5732d0); 0 = ok, 1 = a registration failed */
int he_RegisterEventTypeA2(void) {
  return he_SetEventHandlers(0xa2, he_AllocCouncil, he_RunCouncil) != 0;
}
/* 0x573280, the alloc of the event 0xa2 (the daily Hanseatic League politics): nothing while paused (AIJOB.opts & 4) or
   while the hour (ai_Time.hour) is 0xa or less; else the due clock AIJOB.end = now + 24 hours (0x4fe140), its hour 0xa,
   minute and second 0, stage 0 */

void he_AllocCouncil(AIJOB *e) {

  if (e->opts & 4)
    return;
  if (ai_Time.hour <= 0xa)
    return;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->end.hour = 0xa;
  e->end.min = 0;
  e->end.sec = 0;
  e->stage = 0;
}

void hmt_Update();           /* 0x4ace40, hmt_Update */
void hmt_Begin();            /* 0x4ad0a0, hmt_Begin */
void hmt_Election();         /* 0x4ad1c0, hmt_Election */
void hmt_ClearOffices(void); /* 0x4ad510 */
void hmt_DecideElection();   /* 0x4ad580 */

/* 0x5732d0, the run of the event 0xa2 (the daily Hanseatic League politics): nothing while paused (AIJOB.opts & 4); the
   stage 0 .. 4 picks the step, each schedules the next state with 0x4c4c60: 0 hmt_Update and +2 hours, 1 hmt_Begin and
   +2 hours, 2 hmt_Election and the time of day 0x16 (0x4fe1e0), 3 hmt_ClearOffices and the time of day 6:05 with the day +1,
   4 hmt_DecideElection and the time of day 0xa */
void he_RunCouncil(AIJOB *e) {

  if (e->opts & 4)
    return;
  switch (e->stage) {
  case 0:
    hmt_Update();
    gm_AddTime(&e->end, 2, 0, 0);
    cm_SendExSetHE(1, e);
    return;
  case 1:
    hmt_Begin();
    gm_AddTime(&e->end, 2, 0, 0);
    cm_SendExSetHE(2, e);
    return;
  case 2:
    hmt_Election();
    gm_SetTime(&e->end, 0x16, 0, 0);
    cm_SendExSetHE(3, e);
    return;
  case 3:
    hmt_ClearOffices();
    gm_SetTime(&e->end, 6, 5, 0);
    e->end.year = e->end.year + 1;
    cm_SendExSetHE(4, e);
    return;
  case 4:
    hmt_DecideElection();
    gm_SetTime(&e->end, 0xa, 0, 0);
    cm_SendExSetHE(0, e);
    return;
  }
}

void he_AllocGypsyApproach(struct AIJOB *ev); /* 0x5734b0 */
void he_RunGypsyApproach(struct AIJOB *ev);   /* 0x573580 */
void he_AllocGypsyCurse(struct AIJOB *ev);    /* 0x573f20 */
void he_RunGypsyCurse(struct AIJOB *ev);      /* 0x573fb0 */
void he_AllocGypsySlowdown(struct AIJOB *ev); /* 0x574060 */
void he_RunGypsySlowdown(struct AIJOB *ev);   /* 0x5740d0 */
void he_AllocTrialScene(struct AIJOB *ev);    /* 0x574120 */
void he_RunTrialScene(struct AIJOB *ev);      /* 0x5743c0 */
void he_AllocMeeting4(struct AIJOB *ev);      /* 0x574550 */
void he_RunCircusShow(struct AIJOB *ev);      /* 0x5748d0 */
void he_AllocPettyLoss(struct AIJOB *ev);     /* 0x575150 */
void he_RunPettyLoss(struct AIJOB *ev);       /* 0x5751e0 */
void he_AllocEventGood(struct AIJOB *ev);     /* 0x575320 */
void he_RunEventGood(struct AIJOB *ev);       /* 0x5753a0 */

/* 0x5733c0, registers the event types 0x9d .. 0xa1, 0xa3 and 0xa4 (called by 0x53d4b0): the pairs
   (he_AllocGypsyApproach, he_RunGypsyApproach), (he_AllocGypsyCurse, he_RunGypsyCurse),
   (he_AllocGypsySlowdown, he_RunGypsySlowdown), (he_AllocTrialScene, he_RunTrialScene),
   (he_AllocMeeting4, he_RunCircusShow), (he_AllocPettyLoss, he_RunPettyLoss) and (he_AllocEventGood, he_RunEventGood),
   then the type text 0x50f of 0xa1 (0x52b350); 0 = ok, 1 = a registration failed */
int he_RegisterEventTypes9d(void) {
  if (he_SetEventHandlers(0x9d, he_AllocGypsyApproach, he_RunGypsyApproach) ==
      0) {
    if (he_SetEventHandlers(0x9e, he_AllocGypsyCurse, he_RunGypsyCurse) == 0) {
      if (he_SetEventHandlers(0x9f, he_AllocGypsySlowdown,
                              he_RunGypsySlowdown) == 0) {
        if (he_SetEventHandlers(0xa0, he_AllocTrialScene, he_RunTrialScene) ==
            0) {
          if (he_SetEventHandlers(0xa1, he_AllocMeeting4, he_RunCircusShow) ==
              0) {
            if (he_SetEventHandlers(0xa3, he_AllocPettyLoss, he_RunPettyLoss) ==
                0) {
              if (he_SetEventHandlers(0xa4, he_AllocEventGood,
                                      he_RunEventGood) == 0) {
                sv_RegisterActivity(0xa1, 0, 0, 0x50f, -1);
                return 0;
              }
            }
          }
        }
      }
    }
  }
  return 1;
}
/* 0x5734b0, the alloc of the gypsy event 0x9d: stage 0; nothing while paused (AIJOB.opts & 4); both clocks AIJOB.start /
   AIJOB.end = now; the gypsy figure AIJOB.gypsyFigure (gm_FindChar): without one the event is scheduled with -1; else gv_Accuse
   (0x1c, 1, the player's netId AIJOB.netId, the figure's netId, the id of the figure's building AIBLD.bld2 ? its id : -1) and
   the handler scheduled with 0 */

void he_AllocGypsyApproach(AIJOB *e) {
  AIJOB *g = e;
  AICHAR *per;
  AIBLD *b;
  int x;

  e->stage = 0;
  if (e->opts & 4)
    return;
  e->start = ai_Time;
  e->end = ai_Time;
  per = gm_FindChar(g->gypsyFigure);
  if (per == 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  b = per->bld2;
  x = b != 0 ? b->id : -1;
  gv_Accuse(0x1c, 1, e->netId, per->netId, x);
  e->exSlot = cm_SendExSetHE(0, e);
}

void he_GypsyApproach(struct AICHAR *pl, struct AICHAR *per,
                      int a);        /* 0x5736d0 */
void he_GypsyFee(AICHAR *pl, int a); /* 0x573e30 */

/* 0x573580, the run of the event 0x9d: -2 / -1 free; nothing while paused or while the pending handle AIJOB.exSlot is not done
   (0x4c3ae0); then exSlot = -1, the due clock AIJOB.end = now, the figure AIJOB.gypsyFigure (0x505df0) and the player record
   ai_Chars[e->chr] (0x770b80) must exist (else scheduled with -1): stage 0 calls he_GypsyApproach (player, figure, the
   approach) and retries in 24 hours with the hour 6 and the minute 15 * random (4) + 5; stage 1 calls he_GypsyFee (player,
   the approach) and schedules -1 */
void he_RunGypsyApproach(AIJOB *e) {
  AIJOB *g = e;
  AICHAR *per, *pl;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  e->end = ai_Time;
  per = gm_FindChar(g->gypsyFigure);
  if (per == 0 || ai_Chars[e->chr].id == 0xffff) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  pl = &ai_Chars[e->chr];
  switch (e->stage) {
  case 0:
    he_GypsyApproach(pl, per, g->gypsyApproach);
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 6;
    e->end.min = util_Random(4) * 0xf + 5;
    e->exSlot = cm_SendExSetHE(1, e);
    return;
  case 1:
    he_GypsyFee(pl, g->gypsyApproach);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}

void he_GypsyDisease(AICHAR *pl, AICHAR *per);     /* 0x573760 */
void he_GypsyRumour(AICHAR *pl, AICHAR *per);      /* 0x573820 */
void he_GypsyWorkerQuits(AICHAR *pl, AICHAR *per); /* 0x573970 */
void he_GypsySwapSkills(AICHAR *pl, AICHAR *per);  /* 0x573ae0 */
void he_GypsyCurse(AICHAR *pl, AICHAR *per);       /* 0x573c20 */
void he_GypsySlowdown(AICHAR *pl, AICHAR *per);    /* 0x573d30 */

/* 0x5736d0, dispatches the approach +0xac `a` of the event 0x9d: 0 0x573760, 1 0x573820, 2 0x573970, 3 0x573ae0, 4 0x573c20, else 0x573d30 */
void he_GypsyApproach(AICHAR *pl, AICHAR *per, int a) {
  if (a == 0)
    he_GypsyDisease(pl, per);
  else if (a == 1)
    he_GypsyRumour(pl, per);
  else if (a == 2)
    he_GypsyWorkerQuits(pl, per);
  else if (a == 3)
    he_GypsySwapSkills(pl, per);
  else if (a == 4)
    he_GypsyCurse(pl, per);
  else
    he_GypsySlowdown(pl, per);
}
/* 0x573760, the approach 0 of the event 0x9d (he_GypsyApproach): the character per catches a disease (gm_CatchDisease
   draws its kind and health; none caught: nothing), and per's player is told (the news 0x5fb, the text 0x41dd when
   per is the event's own character pl, else 0x41dc, around 0x41de with the disease's name 0x1632 + kind) with the
   voice "_NACHRICHTEN_ZIGEUNER_02" (pl) or "_NACHRICHTEN_ZIGEUNER_01" (another) */
void he_GypsyDisease(AICHAR *pl, AICHAR *per) {
  int kind;
  float health;
  char voice[100];
  char what[0x400];
  char text[0x400];
  int fmt;

  if (gm_CatchDisease(per, &kind, &health) == 0)
    return;
  if (per == pl) {
    fmt = 0x41dd;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_02");
  } else {
    fmt = 0x41dc;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_01");
  }
  txt_Format(what, 0x41de, kind + 0x1632);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, voice);
}
/* 0x573820, the approach 1 of the event 0x9d (he_GypsyApproach): the standing of the character per changes: when he
   holds an office (amt_GetKind of officeKind, its column col other than 0: the district), its opinion of him falls by
   20 + random(16) (amt_ChangeDistrictOpinion); else, when he is not of the kinds 5 / 6 / 7, the opinion of a random
   district 1 + random(3) rises by 20 + random(16); else every other figure of the kinds 5 .. 7 thinks worse of him
   by 20 + random(16) (cm_SendRelations). Then per's player is told (the news 0x5fb, the text 0x41dd when per is the
   event's own character pl, else 0x41dc, around 0x41df). "Rumour" is a reasoned guess from that effect. */
void he_GypsyRumour(AICHAR *pl, AICHAR *per) {
  AMTKIND kind;
  char what[0x400];
  char text[0x400];
  AICHAR *ch;
  int i, delta, district, fmt;

  if (amt_GetKind(per->officeKind, &kind) != 0 && (district = kind.col) != 0) {
    amt_ChangeDistrictOpinion(per, district, -0x14 - util_Random(0x10));
  } else if (per->kind != 6 && per->kind != 7 && per->kind != 5) {
    amt_ChangeDistrictOpinion(per, 1 + util_Random(3),
                              0x14 + util_Random(0x10));
  } else {
    delta = -0x14 - util_Random(0x10);
    for (i = 0, ch = ai_Chars;
         (intptr_t)&ch->kind < (intptr_t)&ai_Chars[768].kind; ch++, i++) {
      if (i == per->id)
        continue;
      if (ch->kind == 6 || ch->kind == 7 || ch->kind == 5)
        cm_SendRelations(per->netId, ch->netId, delta, 1);
    }
  }
  if (per == pl)
    fmt = 0x41dd;
  else
    fmt = 0x41dc;
  txt_Format(what, 0x41df);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, 0);
}
/* 0x573970, the approach 2 of the event 0x9d (he_GypsyApproach): the first worker (kind 0, a building, no jobId) of a
   building per owns is made to quit: the message 0x33 (the worker who quits, its run handler 0x55e1d0) to per from
   that building, arg[0] the worker's netId. Then per's player is told (the news 0x5fb, the text 0x41dd when per is
   the event's own character pl, else 0x41dc, around 0x41e0 with the worker and the building) with the voice
   "_NACHRICHTEN_ZIGEUNER_02" (pl) or "_NACHRICHTEN_ZIGEUNER_01" (another). No such worker: nothing. */
void he_GypsyWorkerQuits(AICHAR *pl, AICHAR *per) {
  AIMSG msg;
  char voice[100];
  char what[0x400];
  char text[0x400];
  AICHAR *ch;
  int i, fmt;

  ch = 0;
  for (i = 0; i < 0x300; i++) {
    if (ai_Chars[i].kind == 0 && ai_Chars[i].bld != 0 &&
        ai_Chars[i].jobId == 0 && ai_Chars[i].bld->owner == per->id) {
      ch = &ai_Chars[i];
      break;
    }
  }
  if (ch == 0)
    return;
  memset(&msg, 0, sizeof(msg));
  msg.type = 0x33;
  msg.to = per->netId;
  msg.fromId = ch->bld->id;
  msg.time = ai_Time;
  msg.flags = 1;
  msg.arg[0] = ch->netId;
  cm_SendLongMessage(&msg);
  if (per == pl) {
    fmt = 0x41dd;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_02");
  } else {
    fmt = 0x41dc;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_01");
  }
  txt_Format(what, 0x41e0, ch->id, ch->bld);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, voice);
}
/* 0x573ae0, the approach 3 of the event 0x9d (he_GypsyApproach): of per's five skills the highest and the lowest (the
   first of each) trade places: the lowest gains their difference, the highest loses it (cm_SendAddSkill); five
   equal skills: nothing. Then per's player is told (the news 0x5fb, the text 0x41dd when per is the event's own
   character pl, else 0x41dc, around 0x41e1 with both skills' names 0x16b7 + index) with the voice
   "_NACHRICHTEN_ZIGEUNER_02" (pl) or "_NACHRICHTEN_ZIGEUNER_01" (another). */
void he_GypsySwapSkills(AICHAR *pl, AICHAR *per) {
  char voice[100];
  char what[0x400];
  char text[0x400];
  int hi, lo, hiIdx, loIdx, i, fmt;

  lo = 0xff;
  hi = -1;
  hiIdx = -1;
  loIdx = -1;
  for (i = 0; i < 5; i++) {
    if (per->skills[i] > hi) {
      hi = per->skills[i];
      hiIdx = i;
    }
    if (per->skills[i] < lo) {
      lo = per->skills[i];
      loIdx = i;
    }
  }
  if (loIdx == hiIdx || loIdx <= -1 || hiIdx <= -1)
    return;
  cm_SendAddSkill(per->netId, loIdx, hi - lo);
  cm_SendAddSkill(per->netId, hiIdx, lo - hi);
  if (per == pl) {
    fmt = 0x41dd;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_02");
  } else {
    fmt = 0x41dc;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_01");
  }
  txt_Format(what, 0x41e1, loIdx + 0x16b7, hiIdx + 0x16b7);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, voice);
}
/* 0x573c20, the approach 4 of the event 0x9d (he_GypsyApproach): posts the message 0x9e to per (from -1; arg[0] the
   netId of the event's own character pl, -1 when that is per; arg[1] per's netId), whose event (alloc 0x573f20, run
   0x573fb0) charges per once a day for two days. Then per's player is told (the news 0x5fb, the text 0x41dd when per
   is pl, else 0x41dc, around 0x41e2) with the voice "_NACHRICHTEN_ZIGEUNER_02" (pl) or "_NACHRICHTEN_ZIGEUNER_01"
   (another). "Curse" is a reasoned guess from that effect. */
void he_GypsyCurse(AICHAR *pl, AICHAR *per) {
  AIMSG msg;
  char voice[100];
  char what[0x400];
  char text[0x400];
  int fmt;

  memset(&msg, 0, sizeof(msg));
  msg.type = 0x9e;
  msg.to = per->netId;
  msg.fromId = -1;
  msg.time = ai_Time;
  msg.flags = 1;
  msg.arg[0] = pl == per ? -1 : pl->netId;
  msg.arg[1] = per->netId;
  cm_SendLongMessage(&msg);
  if (per == pl) {
    fmt = 0x41dd;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_02");
  } else {
    fmt = 0x41dc;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_01");
  }
  txt_Format(what, 0x41e2);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, voice);
}
/* 0x573d30, the default approach (5 and up) of the event 0x9d (he_GypsyApproach): posts the message 0x9f to per (from
   -1), whose event (alloc 0x574060, run 0x5740d0) lasts 24 hours; while it exists per's workshops work at 0.9 of
   their rate (he_HasEvent9f). Then per's player is told (the news 0x5fb, the text 0x41dd when per is the event's own
   character pl, else 0x41dc, around 0x41e3) with the voice "_NACHRICHTEN_ZIGEUNER_02" (pl) or
   "_NACHRICHTEN_ZIGEUNER_01" (another). "Slowdown" is a reasoned guess from that effect. */
void he_GypsySlowdown(AICHAR *pl, AICHAR *per) {
  AIMSG msg;
  char voice[100];
  char what[0x400];
  char text[0x400];
  int fmt;

  memset(&msg, 0, sizeof(msg));
  msg.type = 0x9f;
  msg.to = per->netId;
  msg.fromId = -1;
  msg.time = ai_Time;
  msg.flags = 1;
  cm_SendLongMessage(&msg);
  if (per == pl) {
    fmt = 0x41dd;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_02");
  } else {
    fmt = 0x41dc;
    strcpy(voice, "_NACHRICHTEN_ZIGEUNER_01");
  }
  txt_Format(what, 0x41e3);
  txt_Format(text, fmt, what);
  he_ShowNews(per->netId, -1, text, 1, 0x5fb, voice);
}

/* 0x573e30, the second step of the event 0x9d (state 1 of he_RunGypsyApproach): the event's own character pl pays the fee n
   for the approach a (a < 2: 2 + random(2); a == 2: 3 + random(2); a == 3: 3 + random(3); a == 4: 3 + random(4); else
   4 + random(4)): with the money he is charged n (gm_SendMoneyDelta) and told (the news 0x5fa, the text 0x41db with n)
   with the voice "_NACHRICHTEN_ZIGEUNER_00"; without it the approach a strikes himself (he_GypsyApproach (pl, pl, a)).
   "Fee" is a reasoned guess from that effect. */
void he_GypsyFee(AICHAR *pl, int a) {
  char text[0x200];
  int n;

  if (a < 2)
    n = util_Random(2) + 2;
  else if (a == 2)
    n = util_Random(2) + 3;
  else if (a == 3)
    n = util_Random(3) + 3;
  else if (a == 4)
    n = util_Random(4) + 3;
  else
    n = util_Random(4) + 4;
  if (pl->money >= n) {
    gm_SendMoneyDelta(pl->netId, -n);
    txt_Format(text, 0x41db, n);
    he_ShowNews(pl->netId, -1, text, 1, 0x5fa, "_NACHRICHTEN_ZIGEUNER_00");
  } else {
    he_GypsyApproach(pl, pl, a);
  }
}
/* 0x573f20, the alloc of the gypsy curse event 0x9e: stage 0, the start and the due clock AIJOB.start / AIJOB.end = now, the
   due clock + 24 hours (0x4fe140), the hour 6 and the minute 5 + random (0x10) */

void he_AllocGypsyCurse(AIJOB *e) {

  e->stage = 0;
  e->start = ai_Time;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->end.hour = 6;
  e->end.min = util_Random(0x10) + 5;
}
/* 0x573fb0, the run of the event 0x9e: -2 / -1 free; the stage + 1; the cursed character +0xb0 and the gypsy +0xac
   (gm_FindChar); the cursed one's money +0x194 (n) is taken -n and the gypsy gets n / 2 (at least 2) (gm_SendMoneyDelta);
   while the stage stays below 2 the due clock +0x52 moves 24 hours ahead (gm_AddTime), else the event is freed */

void he_RunGypsyCurse(AIJOB *e) {
  AIJOB *g = e;
  AICHAR *a, *b;
  int n, x;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  e->stage = e->stage + 1;
  a = gm_FindChar(g->curseCursed);
  b = gm_FindChar(g->curseGypsy);
  if (a != 0) {
    n = a->money;
    if (n != 0) {
      gm_SendMoneyDelta(a->netId, -n);
      x = n / 2;
      if (x <= 2)
        x = 2;
      if (b != 0)
        gm_SendMoneyDelta(b->netId, x);
    }
    if (e->stage < 2) {
      gm_AddTime(&e->end, 0x18, 0, 0);
      return;
    }
  }
  he_FreeEvent(e);
}
/* 0x574060, the alloc of the event 0x9f: stage -1, start and end = now, the end clock + 24 hours (gm_AddTime) */

void he_AllocGypsySlowdown(AIJOB *e) {

  e->stage = -1;
  e->start = ai_Time;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
}
/* 0x5740d0, the run of the event 0x9f: the stage -2 / -1 (a free record) frees the event */

void he_RunGypsySlowdown(AIJOB *e) {

  if (e->stage == -1 || e->stage == -2)
    he_FreeEvent(e);
}
/* 0x5740f0, 1 when the character `a` has an event of the type 0x9f (he_FindEvent (2, 0, 0x9f, 2, a->id)) */

int he_HasEvent9f(AICHAR *a) { return he_FindEvent(2, 0, 0x9f, 2, a->id) != 0; }
/* 0x574120, the alloc of the event 0xa0: nothing while paused (opts & 4); start and end = now; when gm_AllowAll is set
   the end moves 1 hour ahead, else 24 hours with the hour 0x13 + random (2); the minute 0 and the handler scheduled with 0 */

void he_AllocTrialScene(AIJOB *e) {

  if (e->opts & 4)
    return;
  e->start = ai_Time;
  e->end = ai_Time;
  if (gm_AllowAll != 0) {
    gm_AddTime(&e->end, 1, 0, 0);
  } else {
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = util_Random(2) + 0x13;
  }
  e->end.min = 0;
  e->exSlot = cm_SendExSetHE(0, e);
}

/* 0x5741d0, the curse event 0xa0 the building `a` sent (he_FindEvent (2, 0, 0xa0, 3, a->id): its from id), 0 when none */

AIJOB *ai_FindCurseEvent(AIBLD *a) {
  return he_FindEvent(2, 0, 0xa0, 3, a->id);
}
/* 0x5741f0, the trial payment of the event 0xa0 (state 1 of he_RunTrialScene): the building from (gm_FindById) and the
   character netId (gm_FindChar) must exist. By the building's trial kind (gm_TrialBuildingKind) and the trial's level
   the bar (the liking a figure needs) and a bonus count are: kind 3: 40 + 20 / 10 / 0 and 10 / 20 / 25 for a level
   below 4 / below 7 / else; kind 2: 50 + 10 / 0 and 10 / 15 for a level below 4 / else; else 70 and 10. The fee per
   head is 32 * (15 + random(24)) / 32 * (12 + random(16)) / 32 * (10 + random(8)). Every other figure (kind below
   10) whose liking from the character (gm_Liking) is above the bar adds a head to the bonus; the character is told
   (the news 0x5fa, the text 0x41fa with the building, the heads and the sum) and gets heads * fee from the own player
   (cm_SendMoveGoodsUnchecked). */
void he_TrialPayment(AIJOB *e) {
  AIJOB *t = e;
  char text[0x200];
  AIBLD *bld;
  AICHAR *per, *ch;
  int kind, bonus, cnt, fee, sum, i;
  float bar;

  gm_FindById(&bld, 0, 0, e->from);
  if (bld == 0)
    return;
  per = gm_FindChar(e->netId);
  if (per == 0)
    return;
  kind = gm_TrialBuildingKind(bld);
  if (kind == 3) {
    int add, adj;

    add = 0;
    adj = 0;
    if (t->trialCaseLevel < 4) {
      add = 0x14;
      adj = -0xf;
    } else if (t->trialCaseLevel < 7) {
      add = 0xa;
      adj = -5;
    }
    bar = add + 40.0f;
    bonus = adj + 0x19;
    fee = (util_Random(0x18) + 0xf) * 32;
  } else if (kind == 2) {
    int add, adj;

    add = 0;
    adj = 0;
    if (t->trialCaseLevel < 4) {
      add = 0xa;
      adj = -5;
    }
    bar = add + 50.0f;
    bonus = adj + 0xf;
    fee = (util_Random(0x10) + 0xc) * 32;
  } else {
    bar = 70.0f;
    bonus = 0xa;
    fee = (util_Random(8) + 0xa) * 32;
  }
  cnt = 0;
  for (i = 0; i < 0x300; i++) {
    ch = &ai_Chars[i];
    if (ch->id == 0xffff || ch == per || ch->kind >= 0xa)
      continue;
    if (gm_Liking(per->id, ch->id, 1) > bar)
      cnt++;
  }
  cnt += bonus;
  sum = cnt * fee;
  txt_Format(text, 0x41fa, bld, cnt, sum);
  he_ShowNews(per->netId, -1, text, 1, 0x5fa, 0);
  cm_SendMoveGoodsUnchecked(per->netId, -1, ai_OwnPlayer, sum);
}
/* 0x5743c0, the run of the trial event 0xa0: it waits on the pending handle (cm_GetSlotState) and frees on the states
   -1 / -2; state 0 finds the building (gm_FindBuildingById, its from) and its group object (gm_Query, the prototype
   0x27f), puts the due clock 2 hours ahead (gm_AddTime), and with a group shows the text 0x4205 (txt_Format,
   he_MessageBoxQuickjump with the owner's character and the group's id), selects the group's scene
   (init_ObjectSceneUniverse, d3if_SelectScene), loads the theatre script (evt_Load) as the owner's own scene and runs it
   with the trial's level, then restores the scene; it clears the due minute and goes to state 1; state 1 runs the trial
   payment (he_TrialPayment) unless paused (opts 4) and schedules the next run with cm_SendExSetHE */
void he_RunTrialScene(AIJOB *e) {
  AIJOB *t = e;
  char text[0x400];
  AIBLD *bld;
  AIOBJ *grp;
  AICHAR *ch;
  EVTSCRIPT *o;
  int sc, sc2;

  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage == 0) {
    grp = 0;
    bld = gm_FindBuildingById(e->from);
    if (bld != 0)
      grp = gm_Query(bld->objList, 1, 0, 0x27f);
    gm_AddTime(&e->end, 2, 0, 0);
    if (grp != 0) {
      ch = &ai_Chars[bld->owner];
      txt_Format(text, 0x4205, bld);
      he_MessageBoxQuickjump(ch->netId, ch->netId, text, 0, 0x5fc, bld->id,
                             grp->objId, ch_EmptyName, ch_EmptyName);
      sc = d3_CurrentScene;
      sc2 = init_ObjectSceneUniverse(grp);
      d3if_SelectScene(sc2, 1);
      o = evt_Load("locations/zirkuszelt/theaterauffuehrung.esc");
      if (o != 0) {
        o->group = grp->objId;
        o->ownScene = 1;
        evt_RunScriptArgs(o, 1, t->trialCaseLevel);
      }
      d3if_SelectScene(sc, 1);
    }
    e->end.min = 0;
    e->stage = 1;
    return;
  }
  if (e->stage == 1 && !(e->opts & 4)) {
    he_TrialPayment(e);
    e->exSlot = cm_SendExSetHE(-1, e);
  }
}
/* 0x574550, the alloc of the event 0xa1 (a meeting of up to four figures +0x8c ..): when one of them is in the building +0x10
   (0x505df0, +0x16c, +1) the start and the due clock +0x44 / +0x52 = now, two indices of the table 7 / 0x16 / 0xf / 0xa
   (0x505ca0 (4, out)) go to +0xc0 / +0xc2 and +0xc4 / +0xc6, the words +0xc8 .. +0xce = 0, +0xac = 0, +0xb0 / +0xb4 = 0xf0,
   +0xbc = 0, +0xd0 = -1 and state 0; else the event is freed */

void he_AllocMeeting4(AIJOB *e) {
  AIJOB *m = e;
  unsigned short w[4];
  int out[4];
  AICHAR *per;
  AIBLD *bld;
  int i;

  w[0] = 7;
  w[1] = 0x16;
  w[2] = 0xf;
  w[3] = 0xa;
  for (i = 0; i < 4; i++) {
    per = gm_FindChar(e->ids[i]);
    if (per == 0)
      continue;
    bld = per->bld;
    if (bld == 0)
      continue;
    if (bld->id == e->from)
      goto done;
  }
  he_FreeEvent(e);
  return;
done: /* no contact object: -1 */
  e->start = ai_Time;
  e->end = ai_Time;
  gm_Shuffled(4, out);
  m->circusObjs[3] = 0;
  m->circusClasses[0] = w[out[0]];
  m->circusClasses[1] = w[out[1]];
  m->circusObjs[2] = 0;
  m->circusClasses[2] = w[out[2]];
  m->circusClasses[3] = w[out[3]];
  m->circusObjs[1] = 0;
  m->circusObjs[0] = 0;
  m->circusIncome = 0;
  m->circusRoom = 0xf0;
  m->circusStop = 0xf0;
  m->circusStart = 0;
  m->circusBld = -1;
  e->stage = 0;
}
/* 0x5746b0, the payout at the end of the meeting event 0xa1 (its run 0x5748d0): the character netId (gm_FindChar) and
   the building from (gm_FindById) must exist. The meeting's objects objs[] (the non-zero ones) are looked up in his
   inventory (ai_FindWantedItems: per object the entry, st[0] the inventory's entries); an object he already holds 3 of,
   or one he lacks while his inventory has 6 entries, adds its price (gm_GoodsPrice) to the income; any other he gets
   (cm_SendExSellObject, one of it). He is paid the income (cm_SendMoveGoodsUnchecked) and told (the news 0x5ff, the
   text 0x41f0 with the building around 0x41f2 (objects given) or 0x41f1 (none), both with the income). The objects
   are read by the record's index from objs[] again (equal to the found ones while no zero lies between them). */
void he_CircusShowPayout(AIJOB *e) {
  AIJOB *m = e;
  AIBLD *bld;
  int st[3]; /* ai_FindWantedItems: st[0] the inventory's entries */
  int given[4];
  G9REC want[4]; /* ai_FindWantedItems' records */
  char text[0x100];
  char text2[0x200];
  AICHAR *per;
  AIOBJ *entry;
  unsigned short *obj;
  G9REC *row;
  int n, i, ngiven;

  per = gm_FindChar(e->netId);
  if (per == 0)
    return;
  gm_FindById(&bld, 0, 0, e->from);
  if (bld == 0)
    return;
  memset(want, 0, sizeof(want));
  n = 0;
  for (i = 0; i < 4; i++) {
    if (m->circusObjs[i] != 0)
      want[n++].item = m->circusObjs[i];
  }
  if (n != 0) {
    ai_FindWantedItems(per, n, want, st);
    ngiven = 0;
    obj = m->circusObjs;
    row = want;
    for (i = 0; i < n; i++, obj++, row++) {
      if (*obj == 0)
        continue;
      entry = row->entry;
      if (entry != 0) {
        if (entry->count >= 3) {
          m->circusIncome += (int)gm_GoodsPrice(*obj, ai_OwnPlayer);
        } else {
          given[ngiven++] = *obj;
          cm_SendExSellObject(per->netId, -1, *obj, 1, ai_OwnPlayer, 0);
        }
      } else if (st[0] >= 6) {
        m->circusIncome += (int)gm_GoodsPrice(*obj, ai_OwnPlayer);
      } else {
        st[0]++;
        given[ngiven++] = *obj;
        cm_SendExSellObject(per->netId, -1, *obj, 1, ai_OwnPlayer, 0);
      }
    }
  }
  if (n != 0 && ngiven != 0)
    txt_Format(text, 0x41f2, m->circusIncome);
  else
    txt_Format(text, 0x41f1, m->circusIncome);
  cm_SendMoveGoodsUnchecked(per->netId, -1, ai_OwnPlayer, m->circusIncome);
  txt_Format(text2, 0x41f0, bld, text);
  he_ShowNews(per->netId, -1, text2, 0, 0x5ff, 0);
}

void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c,
                    struct AIJOB *g); /* 0x524260, the group register */
void he_CircusShowIncome(struct AIJOB *ev, int n); /* 0x575030 */

/* 0x5748d0, the run of the event 0xa1, a circus show of up to four figures (AIJOB.ids, the ones gm_FindChar finds):
   -1 / -2 or no figure: they leave the group (sv_MoveToGroup) and the event is freed. Stage 0 picks the building:
   with time left (room > 0) one of the show's building classes (he_FindMeetingRoom, walked to as a room), else the
   building from, at its main room (gm_GetGebaeudeHauptraum); without a building the event ends (stage -1, due now).
   Else bld keeps the building's id and every figure joins the group, stops and walks there ("Bettler"); stage 1 is
   due in 10 minutes. Stage 1 (the building found again by bld, else the end as above) waits
   5 minutes until every figure is at its door (sv_IsAtDoor); then with time left the show runs for 2 hours (stage 2):
   each figure with a model plays 8 of the ten circus animations at random (cm_SendChrAnim, 1 or 2 times each); with
   none left the figures leave the group, the payout runs (he_CircusShowPayout) and the event ends. Stage 2 stops the
   figures, takes the show's income (he_CircusShowIncome), takes 120 off the time and goes back to stage 0, due now. */
void he_RunCircusShow(AIJOB *e) {
  AIJOB *m = e;
  AIBLD *bld;
  AICHAR *pers[4];
  int viaRoom, place;
  AIOBJ *hall;
  AICHAR *p;
  int n, i, k;

  n = 0;
  memset(pers, 0, sizeof(pers));
  bld = 0;
  for (i = 0; i < 4; i++) {
    if (e->ids[i] != -1 && (p = gm_FindChar(e->ids[i])) != 0)
      pers[n++] = p;
  }
  if (e->stage == -1 || e->stage == -2 || n == 0) {
    for (i = 0; i < n; i++)
      sv_MoveToGroup(0, 0, pers[i]->id, 0);
    he_FreeEvent(e);
    return;
  }
  if (e->stage == 0) {
    place = -1;
    if (m->circusRoom > 0) {
      bld = he_FindMeetingRoom(e);
      viaRoom = 1;
      m->circusStart++;
    } else {
      gm_FindById(&bld, 0, 0, e->from);
      viaRoom = 0;
      if (bld != 0 && (hall = gm_GetGebaeudeHauptraum(bld)) != 0)
        place = hall->objId;
    }
    if (bld == 0) {
      e->stage = -1;
      e->end = ai_Time;
      return;
    }
    m->circusBld = bld->id;
    for (i = 0; i < n; i++) {
      p = pers[i];
      sv_MoveToGroup(0, 0, p->id, e);
      cm_SendChrStop(p->netId);
      cm_SendChrGotoBuilding(p->netId, bld->id, place, 0, viaRoom, "Bettler");
    }
    e->stage = 1;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0xa, 0);
    return;
  }
  gm_FindById(&bld, 0, 0, m->circusBld);
  if (bld == 0) {
    e->stage = -1;
    e->end = ai_Time;
    return;
  }
  if (e->stage == 1) {
    char anims[10][0x40] = {"zirkus/anfeuern",
                            "zirkus/handstand",
                            "zirkus/handstand2",
                            "zirkus/lachen",
                            "zirkus/lang_winken",
                            "zirkus/posieren",
                            "zirkus/ruecksalto",
                            "zirkus/ruecksalto2",
                            "zirkus/stehend_beschwoeren",
                            "zirkus/tief_verbeugen"};
    for (i = 0; i < n; i++) {
      if (sv_IsAtDoor(pers[i], bld) == 0) {
        e->stage = 1;
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 5, 0);
        return;
      }
    }
    if (m->circusRoom <= 0) {
      for (i = 0; i < n; i++)
        sv_MoveToGroup(0, 0, pers[i]->id, 0);
      he_CircusShowPayout(e);
      e->stage = -1;
      e->end = ai_Time;
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 2, 0, 0);
    e->stage = 2;
    for (i = 0; i < n; i++) {
      p = pers[i];
      if (p->scene != 0) {
        for (k = 8; k != 0; k--)
          cm_SendChrAnim(p->netId, anims[util_Random(0xa)], util_Random(2) + 1);
      }
    }
    return;
  }
  if (e->stage == 2) {
    for (i = 0; i < n; i++)
      cm_SendChrStop(pers[i]->netId);
    he_CircusShowIncome(e, n);
    m->circusRoom -= 0x78;
    e->end = ai_Time;
    e->stage = 0;
  }
}
/* 0x574fe0, the meeting room of the event 0xa1: up to three of the event's words circusRoomKeys[circusStart],
   [n % 4 + 1], ... are looked up as buildings by their class (0x501190 (1, 5, word)); returns the
   first hit, 0 when none */

AIBLD *he_FindMeetingRoom(AIJOB *e) {
  int i, n;
  AIBLD *r;

  n = e->circusStart;
  r = 0;
  i = 3;
  while (1) {
    if (i == 0)
      break;
    r = gm_BuildQuery(1, 5, e->circusRoomKeys[n]);
    i--;
    n = n % 4 + 1;
    if (r != 0)
      break;
  }
  return r;
}

unsigned short
ai_RandomDomizilGoodNotIn(int param_1, unsigned short *param_2); /* 0x5a9e90 */

/* 0x575030, a round's takings of the circus show event 0xa1 (stage 2 of he_RunCircusShow) for its n figures: the
   character netId (gm_FindChar) and the building from (gm_FindById) must exist. The rate is 1 + the building's skill
   0x1d / 60 (gm_BuildingSkill), the character's skill 2 (gm_GetSkill) squared the base; n times the income grows by
   32 * (int)(((random + base) * 75 + 25) * rate). Then, when random + 1 is below the rate, the first free one of the
   show's four objects may (random above 0.4) become a Domizil good not among the ones before it (ai_RandomDomizilGoodNotIn). */
void he_CircusShowIncome(AIJOB *e, int n) {
  AIJOB *m = e;
  AICHAR *per;
  AIBLD *bld;
  float rate, base, skill;
  int i;

  per = gm_FindChar(e->netId);
  if (per == 0)
    return;
  gm_FindById(&bld, 0, 0, e->from);
  if (bld == 0)
    return;
  rate = gm_BuildingSkill(bld, 0x1d, 1) * 0.0166666675f + 1.0f;
  skill = gm_GetSkill(per, 2);
  base = skill * skill;
  for (i = n; i > 0; i--)
    m->circusIncome +=
        (int)(((util_RandomF() + base) * 75.0 + 25.0) * rate) * 0x20;
  if (util_RandomF() + 1.0f < rate) {
    for (i = 0; i < 4; i++) {
      if (m->circusObjs[i] == 0) {
        if (util_RandomF() > 0.4)
          m->circusObjs[i] = ai_RandomDomizilGoodNotIn(i, m->circusObjs);
        return;
      }
    }
  }
}
/* 0x575150, the alloc of the event 0xa3: stage 0, start and end = now, the end plus random (2) hours and random (0x1e)
   minutes (gm_AddTime) */

void he_AllocPettyLoss(AIJOB *e) {

  e->start = ai_Time;
  e->end = ai_Time;
  e->stage = 0;
  gm_AddTime(&e->end, util_Random(2), util_Random(0x1e), 0);
}
/* 0x5751e0, the run of the event 0xa3 (alloc he_AllocPettyLoss): -1 / -2, a stage above 3 or no character netId
   (gm_FindChar): freed. Else the stage advances and the next run is due in 3 + random(3) hours; a character with money
   loses 1 + random(2) of it when a first such draw is below his money, else all of it (gm_SendMoneyDelta); one of the
   kinds 6 / 7 is told (the news 0x5fb, the text 0x1008 with the amount); past the stage 3 the event is due now (and freed then).
   "Petty loss" is a reasoned guess from that effect. */
void he_RunPettyLoss(AIJOB *e) {
  char text[0x400];
  AICHAR *per;
  int x;

  per = gm_FindChar(e->netId);
  if (e->stage == -1 || e->stage == -2 || e->stage > 3 || per == 0) {
    he_FreeEvent(e);
    return;
  }
  e->stage++;
  gm_AddTime(&e->end, util_Random(3) + 3, 0, 0);
  if (per->money < 1)
    return;
  if (util_Random(2) + 1 < per->money)
    x = util_Random(2) + 1;
  else
    x = per->money;
  gm_SendMoneyDelta(per->netId, -x);
  if (per->kind == 6 || per->kind == 7) {
    txt_Format(text, 0x1008, x);
    he_ShowNews(per->netId, -1, text, 0, 0x5fb, 0);
  }
  if (e->stage > 3)
    e->end = ai_Time;
}
/* 0x575320, the alloc of the event 0xa4: stage 0, start and end = now, the end plus random (0x20) hours (gm_AddTime) */

void he_AllocEventGood(AIJOB *e) {

  e->start = ai_Time;
  e->end = ai_Time;
  e->stage = 0;
  gm_AddTime(&e->end, util_Random(0x20), 0, 0);
}

void he_GiveDomizilGood(AICHAR *per); /* 0x575430 */
void he_EventGoodMoney(AICHAR *per);  /* 0x575540 */
void he_EventGoodRefund(AICHAR *per); /* 0x575570 */

/* 0x5753a0, the run of the event 0xa4: -2 / -1 free, also without the character +0xc (gm_FindChar); a random draw picks
   the good outcome above 0.8 (he_GiveDomizilGood), the money one above 0.4 (he_EventGoodMoney), else the refund
   (he_EventGoodRefund); then free */
void he_RunEventGood(AIJOB *e) {
  AICHAR *per;
  float r;
  int state;

  per = gm_FindChar(e->netId);
  state = e->stage;
  if (state == -1 || state == -2 || per == 0) {
    he_FreeEvent(e);
    return;
  }
  r = util_RandomF();
  if (r > (0.800000012f))
    he_GiveDomizilGood(per);
  else if (r > (0.400000006f))
    he_EventGoodMoney(per);
  else
    he_EventGoodRefund(per);
  he_FreeEvent(e);
}
/* 0x575430, the good outcome of the event 0xa4 (he_RunEventGood): a Domizil good of the ranks 3 .. 6
   (ai_DomizilGoodInRange) is looked up in the character's inventory (ai_FindWantedItems; st[0] its entries); he gets
   one of it (cm_SendExSellObject) unless he already holds 3 of it or lacks it with 6 entries in his inventory: then
   he is paid its price instead (gm_GoodsPrice, cm_SendMoveGoodsUnchecked). */
void he_GiveDomizilGood(AICHAR *per) {
  int st[3];  /* ai_FindWantedItems: st[0] the inventory's entries */
  G9REC want; /* ai_FindWantedItems' record */
  AIOBJ *entry;

  memset(&want, 0, sizeof(want));
  want.item = ai_DomizilGoodInRange(3, 6) & 0xffff;
  ai_FindWantedItems(per, 1, &want, st);
  entry = want.entry;
  if (entry != 0) {
    if (entry->count >= 3)
      cm_SendMoveGoodsUnchecked(
          per->netId, -1, ai_OwnPlayer,
          (int)gm_GoodsPrice((unsigned short)want.item, ai_OwnPlayer));
    else
      cm_SendExSellObject(per->netId, -1, want.item, 1, ai_OwnPlayer, 0);
  } else if (st[0] >= 6) {
    cm_SendMoveGoodsUnchecked(per->netId, -1, ai_OwnPlayer,
                              (int)gm_GoodsPrice(want.item, ai_OwnPlayer));
  } else {
    cm_SendExSellObject(per->netId, -1, want.item, 1, ai_OwnPlayer, 0);
  }
}
/* 0x575540, the middle outcome of the event 0xa4: the character +4 is credited 3 + random (4) money (gm_SendMoneyDelta) */

void he_EventGoodMoney(AICHAR *per) {
  gm_SendMoneyDelta(per->netId, util_Random(4) + 3);
}
/* 0x575570, the low outcome of the event 0xa4: the character +4 is credited the price of good 0x2b7 (gm_GoodsPrice)
   times (2 * random + 1) (cm_SendMoveGoodsUnchecked) */

void he_EventGoodRefund(AICHAR *per) {
  float f;

  f = gm_GoodsPrice(0x2b7, ai_OwnPlayer);
  cm_SendMoveGoodsUnchecked(per->netId, -1, ai_OwnPlayer,
                            (int)((util_RandomF() * 2.0f + 1.0f) * f));
}
/* 0x5755c0, copies the INI path `s` to 0x6fa0e0 and loads "Game" / "message_filter_mask" from it (GetPrivateProfileIntA) into 0x6f263c */

void he_LoadMessageFilter(char *s) {
  strcpy(he_OptionsPath, s);
  he_MessageFilterMask =
      GetPrivateProfileIntA("Game", "message_filter_mask", 0, he_OptionsPath);
}
/* 0x575600, writes 0x6f263c as "Game" / "message_filter_mask" into the INI file 0x6fa0e0 (WritePrivateProfileStringA) */

void he_SaveMessageFilter(void) {
  char buf[0xc];

  sprintf(buf, "%d", he_MessageFilterMask);
  WritePrivateProfileStringA("Game", "message_filter_mask", buf,
                             he_OptionsPath);
}
/* 0x575640, 1 when the message filter mask 0x6f263c has the bit of the message kind id (0x605 the bit 1, 0x606 2, 0x607 4, 0x608 8,
   0x609 0x10, 0x60a 0x20, 0x60b 0x40, 0x60c 0x80, 0x60d 0x100); else 0 */

int he_IsMessageKindFiltered(int id) {
  switch (id) {
  case 0x605:
    if (he_MessageFilterMask & 1)
      return 1;
    break;
  case 0x606:
    if (he_MessageFilterMask & 2)
      return 1;
    break;
  case 0x607:
    if (he_MessageFilterMask & 4)
      return 1;
    break;
  case 0x608:
    if (he_MessageFilterMask & 8)
      return 1;
    break;
  case 0x609:
    if (he_MessageFilterMask & 0x10)
      return 1;
    break;
  case 0x60a:
    if (he_MessageFilterMask & 0x20)
      return 1;
    break;
  case 0x60b:
    if (he_MessageFilterMask & 0x40)
      return 1;
    return 0;
  case 0x60c:
    if (he_MessageFilterMask & 0x80)
      return 1;
    break;
  case 0x60d:
    if (he_MessageFilterMask & 0x100)
      return 1;
    break;
  }
  return 0;
}
/* 0x575710, sets / clears the bit of the message kind id in the filter mask 0x6f263c (0x605 the bit 1, 0x606 2,
   0x607 4, 0x608 8, 0x609 0x10, 0x60a 0x20, 0x60b 0x40, 0x60c 0x80, 0x60d 0x100): `on` 0 clears it, else sets it.
   The setter side of he_IsMessageKindFiltered; the jump table 0x575830. Ends 0x57582f, the table runs to 0x575854, fill to 0x575860 */

void he_SetMessageKindFiltered(int id, int on) {
  switch (id) {
  case 0x605:
    if (on)
      he_MessageFilterMask |= 1;
    else
      he_MessageFilterMask &= ~1;
    break;
  case 0x606:
    if (on)
      he_MessageFilterMask |= 2;
    else
      he_MessageFilterMask &= ~2;
    break;
  case 0x607:
    if (on)
      he_MessageFilterMask |= 4;
    else
      he_MessageFilterMask &= ~4;
    break;
  case 0x608:
    if (on)
      he_MessageFilterMask |= 8;
    else
      he_MessageFilterMask &= ~8;
    break;
  case 0x609:
    if (on)
      he_MessageFilterMask |= 0x10;
    else
      he_MessageFilterMask &= ~0x10;
    break;
  case 0x60a:
    if (on)
      he_MessageFilterMask |= 0x20;
    else
      he_MessageFilterMask &= ~0x20;
    break;
  case 0x60b:
    if (on)
      he_MessageFilterMask |= 0x40;
    else
      he_MessageFilterMask &= ~0x40;
    break;
  case 0x60c:
    if (on)
      he_MessageFilterMask |= 0x80;
    else
      he_MessageFilterMask &= ~0x80;
    break;
  case 0x60d:
    if (on)
      he_MessageFilterMask |= 0x100;
    else
      he_MessageFilterMask &= ~0x100;
    break;
  }
}
/* unlinked: the empty alloc / run handler of the event types without one; LINK folds it (/OPT:ICF) into
   d3io_NoopCallback, 0x44ee40, where the original's registrations (he_SetEventHandlers) point */
void he_NoHandlerB(AIJOB *ev) {}
