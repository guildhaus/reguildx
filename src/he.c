/* he.c -- the event ("Handlung" / HE) system, tag "he_" (0x626680 ..), panel "Panel\Event_Leiste": the 16 slot
   event bar (0x6faa80), the event records (0x400 of 0x14c bytes at 0x6fab40), the alloc / run handler tables
   (0x74df40 / 0x758600, registered by he_RegisterEventTypes22 / he_RegisterEventTypes02) and the handlers of the
   single event types.
   0x53d430 .. 0x568aa0: starts right after main.c's program entry; its .data block 0x625708 .. 0x626680 (the
   he_Find* filter, he_LastSlot, he_BarShown, ai_AmbushSpots, cm_EventNames) follows main.c's strings, then its
   strings up to 0x627e92 (the last ones he_RegisterEventTypes02's). he_b (0x568aa0 ..) follows; the handlers of
   the running income 3, the production, searches, trade, construction and the 0x88 .. 0xa4 events below are its.
   (no @bytes: the block after he_TransportStadtStadt's ret at 0x556055 is its int 3 error path, reached by the je at 0x555dd7)
   The event record is AIJOB (0x14c bytes, he_Events over he_Events), the message record AIMSG (both in ai_types.h,
   readable without ai.h); the buildings and characters are AIBLD / AICHAR (ai_bld.h / ai_char.h, ai_PlayerChar), the
   carts AIOBJ (ai_types.h), the carried-goods records GMCARRYREC (f3gm_carry.h), the goods prototypes AIGOOD
   (f3gm_types.h), the AP events HEAPEVENT (he.h, he_ApEvents). The event bar, the event create / free / search, the
   gfx info, AP event and the event posting functions up to 0x53f370 read them typed.
   The handlers up to 0x547ba0 (the feast 0x37 / feast exam 0x36, tribute 0x35, courtship 0x41, patrol 0x43,
   raid 0x44, fight 0x45, duel challenge 0x46 and insult 0x47 events) read AIJOB typed, their kind words named in
   AIJOB's union (fest*, exam*, tribute*, pair*, patrol*, raid*; partner1 / partner2) and the fight parties they
   post as G28REC (cm_types.h, its raid lists).
   The handlers 0x547f90 .. 0x54a7b0 (events 0x4a, 0x53 .. 0x61) read AIJOB / AICHAR / AIBLD / G28REC typed too,
   and so do the send-home event 0x77 (AIJOB.homeUntil), the reaper event 0x54ff20 .. 0x550e9a (AIJOB's reaper*
   words, the D3OBJECT reaper) and the ranking event 0x550ee0 (its packets HERANKHEAD / HERANKLINE); so do the
   walk event 0x551340 .. 0x552920 (its ten slots HEWALKSLOT; the delay 0x80, skill-bonus 0x82 and applicants 0x86
   handlers in AIJOB.delay* / AIJOB.skillBonus* / AIJOB.applicants*), the six-group event 0x7d (AIJOB.groups / grpMode,
   AMTREC / AMTKIND from amt_types.h), the master exam question / offer 0x7e / 0x7f (AIJOB.examBox*, AIJOB.examOffer*, the
   message AIMSG.exam), the conversion event 0x81 (AIJOB.convert*), the applicants event 0x86 (AIJOB.applicants*),
   the office award 0xa5 (AIJOB.award*), the watch event 0x43 with the attack's question (AIJOB.patrolGuards / patrolWait / HEDETECT), the
   sale 2 (AIJOB.sale*, its sys message 4 HESOLDMSG), the customers / hire events 6 / 7 (AIJOB.customers* / AIJOB.hire*), the
   transport event 15 with its four legs (AIJOB.transport*; the cart's CHARACTER, the ordering event's AIJOB.orderBld / orderStops*),
   the cart repair 16 (AIJOB.cartRepair*), the message box 17 (AIJOB.msgBox*, the party G28REC) and the slot order 18
   (AIJOB.slotOrder*), and the events 19 .. 25 that follow: the store extension (AIJOB.storeExt*), herb gathering (AIJOB.herbs*),
   animal hunt (AIJOB.hunt*), study (AIJOB.study*), the event 0x17 (AIJOB.ev17*), spying (AIJOB.spying*) and sabotage (AIJOB.sabotage*), and the brawl 26
   (AIJOB.brawl*), theft 27 (AIJOB.theft*), repair 28 (AIJOB.repair*) and upgrade 0x1e events, and the events 0x1f .. 0x26 up to
   0x55e730: 0x1f (AIJOB.upgradeGood), the demolition 0x20, the building purchase 0x21 (AIJOB.buy*), the loan 0x23 (AIJOB.loan*), 0x24
   (AIJOB.ev24*), the master exam notice / pass 0x25 / 0x26 (AIJOB.examPass*), the payment 0x27 (AIJOB.ev27*), the harvest 0x28 (AIJOB's
   harvest* words), the dismissal 0x31 (AIJOB.dismiss*), the promotion 0x32, the worker's quitting / theft 0x33 / 0x34 and
   the event 0x38 (AIJOB.ev38*). The protection money
   0x62, its ask 0x63 and the audit 0x64 handlers (0x54ae20 .. 0x54b9b0) read AIJOB and their words typed too
   (AIJOB.protection*, AIJOB.audit*). The head includes
   rt.h and d3_tools.h / d3_snd.h / sblib.h.
   The event and message words are read typed, except the kind-specific words over AIJOB's union the
   local views name: AIJOB.inn* (the meeting event 0x2a at +0xac .. +0xc0), AIJOB.offer* (the offer event 0x2c and the
   master exam 0x2f: offerWho[] at +0xac, offerAt at +0xc4 / +0xc5, offerHandle at +0xd4), AIJOB.duel* (the duel challenge's +0xac and the duel's
   +0xb4 / +0xb6), AIJOB.geselle* / AIJOB.examPay* / AIJOB.payment* / AIJOB.punish* / AIJOB.offspring* / AIJOB.trial* / AIJOB.trialStep* / AIJOB.train* /
   AIJOB.plague* / AIJOB.gang* (the events 0x4a / 0x55 / 0x56 / 0x5b / 0x5c / 0x5d / 0x5e / 0x5f / 0x60 / 0x59 / 0x61; the fine
   0x5b and the pillory 0x5c are the trial's sentences of gv_PassSentence), AIMSG.fee / skillLevel /
   plague (the AI messages 0x56 / 0x6a / 0x78), AIJOB.protection* / AIJOB.audit* / AIJOB.gathering* /
   AIJOB.sim* / AIJOB.auction* / AIJOB.title* (the events 0x62 / 0x64 / 0x65 / 0x66, 0x68, 0x70 / 0x67 / 0x69), AIJOB.skillUp* /
   AIJOB.bard* / AIJOB.population* / AIJOB.lover* / AIJOB.darkCorner* (the events 0x6a / 0x6b / 0x6d / 0x6f / 0x74; the bard's script
   mark EVTSCRIPT.tag[0]; the dark corner's proofs / year are AIOBJ.recs / cornerYear), HEINN (the inn
   simulation's list), the tutorial / tip / routine / storm / new-worker / production / trade words in AIJOB.hint*,
   AIJOB.tip*, AIJOB.routine*, AIJOB.storm*, AIJOB.newWorker*, AIJOB.production*, AIJOB.trade*, the search 8 / 9 and
   new-occurrence 0xa words in AIJOB.search* / AIJOB.search9* / AIJOB.occurrence*, the research /
   building / training / plunder / meeting words in AIJOB.research* (event 0xc), AIJOB.build* (0xd), AIJOB.ahmResearch* (0x96 / 0x97),
   AIJOB.plunder* (0x8a), AIJOB.plunderDeal* (0x8b), AIJOB.masterwork* (0x8c), AIJOB.graveCare* (0x8d), AIJOB.deathDue* (0x8e),
   AIJOB.graveTraining* (0x8f) and AIJOB.meeting* (0x90), AIJOB.meetScene* / EVTSCRIPT.tag (the meeting scene object 0x91), AIJOB.graveLease* (the grave
    lease answer 0x92), AIJOB.gypsy* (the gypsy approach 0x9d), AIJOB.curse* (the curse 0x9e), AIJOB.trialCase* (the trial 0xa0) and AIJOB.circus* (the circus show 0xa1), and over AIOBJ
   the tavern's object 0x1b5 (AIOBJ.sermon: text1 / text2 / priest / enabled hold its hired helper); the hint table he_Hints (0x6fa260, HEHINT), the tip
   order he_TipOrder (0x6fa1e0) and the tip texts TXT_TIP_TEXTS (0x1442430) are typed (the scene, voice and activity
   names are string literals of he / he_b, not objects). AIJOB's fields between
   0x14 and 0xac are named only as the message's words; a member added to AIJOB / AIMSG / G28REC can flip other
   units' matches by declaration set (ai_CalcMeisterFernhaendler, ord_CountGridObjects are debt for it; ai_TutorialInitChapter3
   is a tie-break for it).
   The ransom 0x3d / 0x3e (AIJOB.ransom* / AIJOB.ransomDemand*), burglary 0x3f (AIJOB.burglary*), building spying 0x40 (AIJOB.bldSpy*, its report
   HESPYREPORT), ambush 0x48 (AIJOB.ambush*), attack 0x49 (AIJOB's raid* words) and fire 0x4e (AIJOB.fire*; the burning event's
   AIJOB.burn*) handlers read their records typed, and so do the handlers up to 0x567990: the burning 0x4f (AIJOB.burn*), the
   new worker 0x6e (AIJOB.newWorker*), the kill-player run handler 0x72 (AIJOB.kill*, its funeral party G28REC), the night
   watchman 0x73 (AIJOB.nightWatch*), the robbery 0x75 (AIJOB.robbery*, the burglary's twin), the title period 0x7c (AIMSG)
   and he_OpenHelpEvents (HEHINT); so do the tutorial building tour 0x85, the guard patrol step (AIOBJ's patrol*
   bytes), the running income 3, the production (AIJOB.production*), the searches 8 / 9 (AIJOB.search* / AIJOB.search9*), the trade
   0xb (AIJOB.trade*), the construction event 0xd (AIJOB.construct*, its child list HECHILDLIST, the models
   he_BuildingModels), the mission check 0x4c (AIJOB.missionCheck*) and the alchemist events 0x95 .. 0x98 (AIJOB.recipe*,
   AIJOB.ahmResearch*, AIJOB.ahmDay*; the alchemist records through ahm_types.h), the secret room run 0x99 and its deeds
   (AIJOB.secretRoom*, with AIJOB.spying*), the haunting 0x88 (AIJOB.haunt*) and the breath of decay 0x89 (AIJOB.decay*).
   Open: types: the handlers past 0x570300 other than the plunder / master work / grave care / death due / grave
   training / meeting disease / meeting 0x90 / meeting scene 0x91 / plunder offer lease 0x8b and grave lease 0x92
   alloc / graveyard workers 0x93 alloc ones up to 0x572b90, the grave lease 0x92 run, the graveyard workers 0x93
   run / theft 0x94 (AIJOB.graveTheft*), the gypsy approaches 0x573760 .. 0x573c20 and the curse 0x9e / slowdown 0x9f /
   trial scene 0xa0 / petty loss 0xa3 / event good 0xa4 handlers (0x573f20 .. 0x5755c0) still read the event and
   message records through raw offsets
   Open: head: ai.h is not included (ai_FINVIEW stands in), nor are anm.h f3snd.h hmt.h hst.h menu.h; the @original
   cast macros next to the includes keep the spellings the definitions disagree with: util_RandomInt
   (he_RunInnSim).
   Open: data: 0x6faa80 he_EventSlots, 0x6faa60 he_BarView, 0x6f262c he_ActiveSlot, 0x6f2630 he_SlotConfirmed,
   0x6f2634 he_ReaperMusic, 0x6f2638 he_PatrolBuilding, 0x6f263c he_MessageFilterMask, 0x6f2624 he_FindFirst, 0x6f2628 he_FindUnused, 0x6fa0e0 he_OptionsPath,
   owner he or main (typed in place in main.c's gap block; he.c and sv.c use them, they lie among main.c's data / bss).
   Open: data: 0x5ebb40 ai_FloatHundred (VC6's pooled 100.0f: lc.c's view, defined in main.c's rdata gap block, owner
   lc or main).
   Open: types: SVFRAME / the frame stack view is declared in sv.c, lc.c and here (it belongs in sv_types.h).
   unit of rea 8cef7d5b (src/game/he.c); boundaries in decl/text.dcl */
struct AHMSLOT;
struct D3SM;
struct SBBANK;
struct SBSAMPLE;
union AHMGRID;
struct D3SM;
#include "d2_types.h"
#include "f3snd_types.h" /* G16TRACKHANDLES (snd_TrackHandles) */
#include "txt_views.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <d3d.h>
#include "he.h"
void he_NoHandler(
    struct AIJOB *
        ev); /* unlinked, defined at the end of the unit: the empty handler of the event types without one */
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
extern G16TRACKHANDLES snd_TrackHandles;
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
extern AIJOB he_Events
    [0x400]; /* 0x6fab40, the 0x400 event records (ls.h cannot see AIJOB) */
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
/* clang-format off */
unsigned short util_Random(unsigned short n);  /* 0x42ec00, @original: tr.c defines it returning int; this unit's callers read the 16-bit result (mov si,ax / movzx): the original's units saw a 16-bit declaration */
#define util_RandomInt ((int (*)(unsigned short))util_Random)  /* 0x42ec00 as tr.c defines it (the headers declare it unsigned short): @original he_RunInnSim reads the full int result (util_Random(4) + 3, no 16-bit mask); every other caller of this unit reads 16 bits */
/* clang-format on */
int gm_SumListMoney(
    void *
        list); /* f3gmt.c, folded into gm_SumListAmounts 0x509e30: he_AllocTheft pushes only the list */
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
/* 0x53d430, the allocation handler of an event of an unknown type (debug text only) */

void he_AllocNone(AIJOB *e) {
  char buf[256];

  sprintf(buf, "he_AllocNone(): Invalid HE-Type : %i, von Spieler %s", e->kind,
          ai_Chars[e->chr].name);
}
/* 0x53d470, the run handler of an event of an unknown type (debug text only) */

void he_RunNone(AIJOB *e) {
  char buf[256];

  sprintf(buf, "he_RunNone(): Invalid HE-Type : %i, von Spieler %s", e->kind,
          ai_Chars[e->chr].name);
}
/* 0x53d4b0, the init of the event module: registers the alloc / run handlers of the types 0 and 1, runs the init of the other event modules (0x553060 .. 0x573260; non 0 = failed) and clears the tables */

int he_InitEvents(void) {
  if (he_SetEventHandlers(0, he_AllocNone, he_RunNone) != 0)
    return 1;
  if (he_SetEventHandlers(1, he_NoHandler, he_NoHandler) != 0)
    return 1;
  if (he_RegisterEventTypes22() != 0)
    return 1;
  if (he_RegisterEventTypes02() != 0)
    return 1;
  if (he_RegisterEventTypes03() != 0)
    return 1;
  if (he_RegisterEventTypes88() != 0)
    return 1;
  if (he_RegisterEventTypes95() != 0)
    return 1;
  if (he_RegisterEventTypes99() != 0)
    return 1;
  if (he_RegisterEventTypes9d() != 0)
    return 1;
  if (he_RegisterEventTypeA2() != 0)
    return 1;
  memset(gm_CarryRecs, 0, sizeof(gm_CarryRecs));
  memset(he_ApEvents, 0, sizeof(he_ApEvents));
  memset(he_GfxInfos, 0, sizeof(he_GfxInfos));
  return 0;
}
/* 0x53d590, frees every used record (0x14c bytes each from 0x6fab40) up to 0x6f261c */

void he_FreeEvents(void) {
  AIJOB *p;
  int i = 0;

  if (he_EventTop >= 0) {
    p = he_Events;
    do {
      if ((intptr_t)p >= (intptr_t)&he_Events[0x400])
        return;
      if (p->kind != 0)
        he_FreeEvent(p);
      i++;
      p++;
    } while (i <= he_EventTop);
  }
}
/* 0x53d5d0, frees the records, then asks 0x52a040 three times */

int he_ReleaseEvents(void) {
  he_FreeEvents();
  if (sv_ReturnZero() != 0)
    return 1;
  if (sv_ReturnZero() != 0)
    return 1;
  return sv_ReturnZero() != 0;
}
/* 0x53d600, sets the alloc / run handlers of the event type `type` (0 .. 0xa6; 1 = type out of range) */

int he_SetEventHandlers(int type, HEHANDLER alloc, HEHANDLER run) {
  if (type >= 0 && type < 0xa7) {
    he_AllocHandlers[type] = alloc;
    he_RunHandlers[type] = run;
    return 0;
  }
  return 1;
}
/* 0x53d630, makes room in the 16 slots: finds the slot whose event started earliest, releases the slot and frees the event (he_ReleaseSlot / he_FreeEvent) and returns 0xf; -1 when no slot holds an event */

int he_FreeOldestSlot(void) {
  AITIME oldest;
  AIJOB *best = 0;
  int bi = -1;
  int i;

  oldest = ai_Time;
  for (i = 0; i < 16; i++) {
    if (he_EventSlots[i].ev != 0 && he_EventSlots[i].obj != -1 &&
        gm_CompareTime(&he_EventSlots[i].ev->start, &oldest) < 0) {
      oldest = he_EventSlots[i].ev->start;
      best = he_EventSlots[i].ev;
      bi = i;
    }
  }
  if (best != 0) {
    he_ReleaseSlot(best);
    he_FreeEvent(best);
    return 0xf;
  }
  if (bi != -1) {
    /* clang-format off */
    __asm int 3
    /* clang-format on */
  }
  return bi;
}
/* 0x53d6f0, gives the event `ev` a slot of the event bar (only with its option 8; 1: not shown in the bar, 2: no slot free
   nor freed by he_FreeOldestSlot): the slot's picture object (pic, at 32 * the slot index) and its event window, the view
   form opened at (x, y); the slot is kept in the event's slot field; 0 */

int he_OpenEventSlot(AIJOB *job, int x, int y, char *form, int pic) {
  int i;

  if ((job->opts & 8) == 0) {
    job->slot = 0;
    return 1;
  }
  for (i = 0; i < 16; i++)
    if (he_EventSlots[i].obj == -1)
      break;
  if (i >= 16)
    i = he_FreeOldestSlot();
  if (i == -1) {
    job->slot = 0;
    return 2;
  }
  if (i > he_LastSlot)
    he_LastSlot = i;
  d2_SetForm(he_BarView, 0);
  job->slot = &he_EventSlots[i];
  job->slot->ev = job;
  job->slot->obj = d2_WinOpenPic(i << 5, 0, pic, d2_LastWindow);
  d2_Objs[job->slot->obj].checkable = 1;
  job->slot->win = d2_OpenForm(x, y, form);
  d2_PlaceMainWindow(job->slot->win, 3);
  d2_SetViewEnabled(job->slot->win, 0);
  if (job->slot->obj == -1) {
    /* clang-format off */
    __asm int 3
    /* clang-format on */
  }
  if (job->slot->win == -1) {
    /* clang-format off */
    __asm int 3
    /* clang-format on */
  }
  return 0;
}
/* 0x53d800, releases the slot of the event `ev`: removes its picture object and closes its window, moves the events of
   the slots after the first free one down by one (their objects 32 to the left, d2_MoveObj) and sets he_LastSlot to the
   highest slot still used */

void he_ReleaseSlot(AIJOB *job) {
  int i, k;

  if (job->slot == 0)
    return;
  if (job->slot->obj != -1) {
    d2_SetForm(he_BarView, 0);
    d2_RemoveObj(job->slot->obj);
    job->slot->obj = -1;
  } else {
    /* clang-format off */
    __asm int 3
    /* clang-format on */
  }
  if (job->slot->win != -1) {
    d2_CloseView(job->slot->win);
    job->slot->win = -1;
  }
  if (he_ActiveSlot == job->slot)
    he_ActiveSlot = 0;
  job->slot = 0;
  for (i = 0; i < 16; i++)
    if (he_EventSlots[i].obj == -1)
      break;
  if (i < 16) {
    do {
      if (i < 15 && he_EventSlots[i + 1].obj != -1) {
        he_EventSlots[i].obj = he_EventSlots[i + 1].obj;
        he_EventSlots[i].ev = he_EventSlots[i + 1].ev;
        he_EventSlots[i].win = he_EventSlots[i + 1].win;
        he_EventSlots[i].ev->slot = &he_EventSlots[i];
        he_EventSlots[i + 1].obj = -1;
        he_EventSlots[i + 1].ev = 0;
        he_EventSlots[i + 1].win = -1;
        if (he_EventSlots[i].obj == -1 && he_EventSlots[i].ev != 0) {
          /* clang-format off */
          __asm int 3
          /* clang-format on */
        }
      }
      k = he_EventSlots[i].obj;
      if (k != -1)
        d2_MoveObj(d2_Objs[k].x - 0x20, d2_Objs[k].y, k);
    } while (++i < 16);
  }
  for (i = 0; i < 16; i++)
    if (he_EventSlots[i].obj != -1)
      he_LastSlot = i;
}
/* 0x53d930, creates the panel "Panel\Event_Leiste" (bottom right: screen size - 0x7d / - 0x21) and frees all slots */

void he_CreateEventBar(void) {
  int i;

  he_BarView = d2_OpenForm(0, 0, "Panel\\Event_Leiste");
  d2_SetForm(he_BarView, 0);
  d2_MoveObj(d2_ScreenW - 0x7d, d2_ScreenH - 0x21,
             d2_Wins[d2_LastWindow].parent);
  for (i = 0; i < 16; i++)
    he_EventSlots[i].obj = -1;
  d2_SetViewEnabled(he_BarView, 0);
}
/* 0x53d9b0, closes every used slot and the event bar panel */

void he_CloseEventSlots(void) {
  HEEVSLOT *s;

  for (s = he_EventSlots; (int)s < (int)(he_EventSlots + 16); s++)
    if (s->obj != -1)
      he_ReleaseSlot(s->ev);
  d2_CloseView(he_BarView);
}
/* 0x53d9f0, shows / hides the event bar for the player slot `pl` (0xffff = hide): a bar already shown first hides its
   event windows and moves to the bottom right of the screen hidden; shown, he_LastSlot is the first free slot and
   he_BarShown the bar's view, hidden both are -1 */

void he_ShowEventBar(int pl) {
  int i;

  if (he_BarShown != -1) {
    for (i = 0; i < 16; i++)
      if (he_EventSlots[i].obj != -1 && he_EventSlots[i].win != -1)
        d2_SetViewEnabled(he_EventSlots[i].win, 0);
    d2_SetForm(he_BarView, 0);
    d2_MoveObj(d2_ScreenW - 0x7d, d2_ScreenH - 0x21,
               d2_Wins[d2_LastWindow].parent);
    d2_SetViewEnabled(he_BarView, 0);
  }
  if (pl != 0xffff) {
    d2_SetViewEnabled(he_BarView, 1);
    for (i = 0; i < 16; i++)
      if (he_EventSlots[i].obj == -1)
        break;
    he_LastSlot = i;
    he_BarShown = he_BarView;
    return;
  }
  he_LastSlot = -1;
  he_BarShown = -1;
}
/* 0x53dad0, sets the state of the event bar panel */

void he_SetBarEnabled(int state) {
  if (he_BarShown != -1)
    d2_SetViewEnabled(he_BarView, state);
}

/* the quick jump marker (0x6333e0): set when the active event is a type 0x11 record with bit 0x40 at +0xf0 or a type 0x87 record, outside the network games */
#define HE_PAUSES(e)                                                           \
  ((e) != 0 &&                                                                 \
   ((e)->kind == 0x11 && ((e)->modes & 0x40) != 0 || (e)->kind == 0x87) &&     \
   (ai_GameFlags & 4) ==                                                       \
       0) /* the event pauses the game while its window is active (kinds 0x11 with mode 0x40, 0x87; not with game flag 4) */

/* 0x53daf0, picks the active event window (he_ActiveSlot): drops the active slot whose object is no longer checked (hides
   its window, unpauses), then activates each used slot whose object is checked: the previous one's window hidden and
   its object unchecked, the new one's window shown and raised; an event of HE_PAUSES pauses the game (tb_Paused) */
void he_PickActiveEvent(void) {
  int i;

  if (he_BarShown != -1) {
    if (he_ActiveSlot != 0 && he_ActiveSlot->obj != -1 &&
        d2_Objs[he_ActiveSlot->obj].checked == 0) {
      if (he_ActiveSlot->win != 0)
        d2_SetViewEnabled(he_ActiveSlot->win, 0);
      if (HE_PAUSES(he_ActiveSlot->ev))
        tb_Paused = 0;
      he_ActiveSlot = 0;
    }
    for (i = 0; i < 16; i++) {
      if (he_EventSlots[i].obj != -1 && he_ActiveSlot != &he_EventSlots[i] &&
          d2_Objs[he_EventSlots[i].obj].checked != 0) {
        if (he_ActiveSlot != 0 && he_ActiveSlot->win != -1) {
          if (he_ActiveSlot->win != 0)
            d2_SetViewEnabled(he_ActiveSlot->win, 0);
          if (he_ActiveSlot->obj != -1) {
            d2_Objs[he_ActiveSlot->obj].checked = 0;
            d2_Objs[he_ActiveSlot->obj].highlighted = 0;
          }
          if (HE_PAUSES(he_ActiveSlot->ev))
            tb_Paused = 0;
          he_ActiveSlot = &he_EventSlots[i];
        } else
          he_ActiveSlot = &he_EventSlots[i];
        d2_SetViewEnabled(he_ActiveSlot->win, 1);
        d2_RaiseViewWindows(he_ActiveSlot->win);
        if (HE_PAUSES(he_ActiveSlot->ev))
          tb_Paused = 1;
      }
    }
  }
}
/* 0x53dcb0, makes the slot `sl` the active event window (0x6f262c), closing the previous one */

void he_ActivateSlot(HEEVSLOT *sl) {
  HEEVSLOT *s = sl;

  if (he_BarShown != -1) {
    if (he_ActiveSlot != 0) {
      if (he_ActiveSlot->obj != -1)
        d2_SetObjValue(he_ActiveSlot->obj, 0);
      d2_SetViewEnabled(he_ActiveSlot->win, 0);
      if (HE_PAUSES(he_ActiveSlot->ev))
        tb_Paused = 0;
      he_ActiveSlot = 0;
    }
    if (s != 0 && s->win != -1) {
      if (s->obj != -1)
        d2_SetObjValue(s->obj, 1);
      d2_SetViewEnabled(s->win, 1);
      d2_RaiseViewWindows(s->win);
      if (HE_PAUSES(s->ev))
        tb_Paused = 1;
    }
    he_ActiveSlot = s;
  }
}

void err_Message(char *text);

/* 0x53dda0, sends the news message 0x11 (message flags 9) to the character `pid`, which must be of kind 6 / 7 (else -1):
   from `from`, the news id `news` (arg[0]), the text flags `tflags` (| 0x10 when `text2` follows the text behind its NUL);
   cm_SendLongMessageText's result */
int he_ShowNews(int pid, int from, char *text, int tflags, int news,
                char *text2) {
  AIMSG msg;
  char buf[0x1fa0];
  unsigned char *ch;
  unsigned char fl;
  int n, ret;

  ch = (unsigned char *)gm_FindChar(pid);
  if (ch == 0 || (ch[2] != 6 && ch[2] != 7)) /* AICHAR.kind */
    return -1;
  fl = (unsigned char)tflags;
  memset(&msg, 0, sizeof(msg));
  msg.to = pid;
  msg.fromId = from;
  msg.type = 0x11;
  msg.flags = 9;
  msg.arg[0] = news;
  msg.textFlags = fl;
  strcpy(buf, text);
  n = strlen(text) + 1;
  if (text2 == 0 || *text2 == 0) {
    ret = cm_SendLongMessageText(&msg, n, text);
  } else {
    memcpy(buf + n, text2, strlen(text2) + 1);
    fl |= 0x10;
    msg.textFlags = fl;
    ret = cm_SendLongMessageText(&msg, strlen(text2) + n + 1, buf);
  }
  return ret;
}
/* 0x53dee0, sends the news message 0x11 (message flags 9) with a quick jump to the player `pid`: from `from`, the news
   id `news` (arg[0], as he_ShowNews), the object `obj` and the second id `obj2` (arg[1] / arg[2]; callers pass a
   building id and an item object or -1), the contact name `jump` at +0x68 (at most 0x30 bytes with its NUL, else
   an error), the text flags `tflags` | 2 (| 0x10 when `text2` follows the text behind its NUL) */
void he_MessageBoxQuickjump(int pid, int from, char *text, int tflags, int news,
                            int obj, int obj2, char *jump, char *text2) {
  AIMSG msg;
  char buf[0x1fa0];
  int n;
  unsigned char fl;

  memset(&msg, 0, sizeof(msg));
  msg.type = 0x11;
  msg.to = pid;
  msg.fromId = from;
  msg.flags = 9;
  if (jump != 0) {
    if (strlen(jump) + 1 > 0x30)
      err_Message("he_MessageBoxQuickjump(): contactname is too long!");
    else
      strcpy((char *)&msg.arg[4],
             jump); /* 0x68: the contact name, over arg[4..] (up to 0x98) */
  }
  msg.arg[0] = news;
  fl = (unsigned char)tflags | 2;
  msg.arg[1] = obj;
  msg.textFlags = fl;
  msg.arg[2] = obj2;
  strcpy(buf, text);
  n = strlen(text) + 1;
  if (text2 == 0 || *text2 == 0) {
    cm_SendLongMessageText(&msg, n, text);
    return;
  }
  memcpy(buf + n, text2, strlen(text2) + 1);
  fl |= 0x10;
  msg.textFlags = fl;
  cm_SendLongMessageText(&msg, strlen(text2) + n + 1, buf);
}

#include <stdarg.h>
#include <math.h>
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

/* HE_SET_CLOCK: the game clock (0x770ae0 ..) into a message at +0x28 .. +0x34, flag byte 2 at +0x36 */

/* 0x53e040, creates the event record of the message `m`: its type needs both an alloc and a run handler (< 0xa7) and its
   receiver `to` (unless -1) must be a character; takes the first free of the 0x400 records he_Events (raising
   he_EventTop), copies the message into it (the character's index and netId, the new event id ai_NextEventId, the
   words, the time, the flags, the ids and the arguments 0x58.. to 0xac..), lists it in he_QuickList when it is
   shown in the event bar (flags 8, he_QuickTop), calls the alloc handler and counts it (he_EventCount); 0 when it
   cannot */
AIJOB *he_CreateEvent(AIMSG *msg) {
  AICHAR *ch = 0;
  AIJOB *ev;
  int i, j, k;

  if (msg->type >= 0xa7 || he_AllocHandlers[msg->type] == 0 ||
      he_RunHandlers[msg->type] == 0)
    return 0;
  if (msg->to != -1 && (ch = gm_FindChar(msg->to)) == 0)
    return 0;
  for (i = 0; i < 0x400; i++)
    if (he_Events[i].kind == 0)
      break;
  if (i == 0x400)
    return 0;
  ev = &he_Events[i];
  if (i > he_EventTop)
    he_EventTop = i;
  if (msg->to == -1) {
    ev->netId = -1;
    ev->chr = 0xffff;
  } else {
    ev->netId = ch->netId;
    ev->chr = ch->id;
  }
  if (msg->flags & 8) {
    for (j = 0; j < 0x100; j++)
      if (he_QuickList[j] == 0)
        break;
    if (j == 0x100)
      return 0;
    he_QuickList[j] = ev;
    if (j > he_QuickTop)
      he_QuickTop = j;
  }
  ev->kind = msg->type;
  ev->id = ai_NextEventId;
  ai_NextEventId++;
  ev->from = msg->fromId;
  for (k = 0; k < 0xc; k++)
    ev->words14[k] = (&msg->nIds)[k]; /* the message words +0x10..+0x3f */
  ev->start = msg->time;
  ev->opts = msg->flags;
  ev->stage = 0;
  ev->slot = 0;
  ev->text = 0;
  ev->exSlot = -1;
  for (k = 0; k < 8; k++)
    ev->ids[k] = msg->ids[k];
  memcpy(ev->tail, msg->arg, 0xa0); /* the arguments 0x58..0xf8 */
  he_AllocHandlers[msg->type](ev);
  he_EventCount++;
  return ev;
}
/* 0x53e1f0, frees the event record `ev`: its message box text (+0x7c), its entry in he_QuickList when it is shown in the
   event bar (flags 8: releases its slot first, shrinks he_QuickTop), counts it off (he_EventCount), clears it and,
   when it was the last used record, shrinks he_EventTop */
void he_FreeEvent(AIJOB *ev) {
  AIJOB *q;
  int i, t;

  if (ev == 0)
    return;
  if (ev->text != 0) {
    mem_Free(ev->text);
    ev->text = 0;
  }
  if (ev->opts & 8) {
    for (i = 0; i < 0x100; i++)
      if (he_QuickList[i] == ev)
        break;
    q = he_QuickList[i];
    if (q != ev)
      return;
    if (q->slot != 0 && q->slot->win != -1)
      he_ReleaseSlot(q);
    t = he_QuickTop;
    he_QuickList[i] = 0;
    if (i == t) {
      for (; t >= 0 && he_QuickList[t] == 0; t--)
        ;
      he_QuickTop = t < 0 ? 0 : t;
    }
  }
  he_EventCount--;
  memset(ev, 0, sizeof(AIJOB));
  if (ev == &he_Events[he_EventTop]) {
    t = he_EventTop;
    for (; t >= 0 && he_Events[t].kind == 0; t--)
      ;
    he_EventTop = t < 0 ? 0 : t;
  }
}

/* 0x53e300, the next event record after he_Cursor that passes he_FindEvent's filter (he_FindKind, he_FindId, he_FindChr,
   he_FindFrom; a record whose first filters matched stays matched through the free records after it), up to the last
   used record he_EventTop (an error when that is out of range); 0 at the end
   @deep s52: the mechanism, by probe: the cursor must be restricted to callee-saved registers while ranked
   below temp#aa (28): only a range across a call does that (k#24 prefers eax from the return copy; with
   the pref gone, ret local, it takes ecx, so VC6 takes scratch first). Probe P (p = he_Cursor before the
   he_EventTop check, so p spans err_Message) matches everything but the load's place and temp#aa /
   he_FindKind (al / cl swapped, because p, prio 42, is served before temp#aa): 12 ins. = control or worse:
   a cursor local p (folds; 128 p / he_Cursor read mixes, best 37), p = 0 initialised / returned on the
   guard path, volatile stores, an extern / block-static / file-static global instead of the he_QuickList
   view, the filters (or he_FindKind) as locals, the error test spellings (>= 0 && <, nested, he_Events +
   top), guard splits, he_FindFirst spellings, returns in the loop, a ret local, a goto loop; flip --want
   on mov eax,esi / mov esi,[he_Cursor] after the call: no mutant. climb 3 rounds (tree and from P):
   nothing. Next: what else puts a call into the cursor's range (a decided test with a call, a macro around
   err_Message), or a candidate between 28 and 23 holding eax over the cursor's range. prior: s45: the
   three gotos replaced by a match flag (match = 1; each filter sets ok or clears match; if (!match) ok =
   0;): the same code (VC6 decides the flag per path). c2trace: the cursor is the global candidate
   he_Cursor (k#24, prio 23, 14 refs), served before the hoisted filters (prio -42 each) and takes eax; the
   original has the cursor in esi and he_FindKind in al (mov al,[he_FindFirst] also in eax), so in the
   original the cursor is not served first or eax is closed to it. No change: the cursor as a local p
   (he_Cursor = ++p), the filters copied into locals before the loop (182 bytes), both. Next: what makes
   the cursor rank below the filters or keeps eax from it (a call / return use in its range? the
   err_Message branch?). */
AIJOB *he_NextEvent(void) {
  char ok = 0;
  AIJOB *last = 0;
  char match;

  if (he_EventTop < 0 || he_EventTop >= 0x400)
    err_Message("he_fn_Handlung(): invalid Handlungen_LAST");
  else
    last = &he_Events[he_EventTop];
  if (he_Cursor == 0 || he_Cursor == last || he_Cursor > last)
    return 0;
  if (he_FindFirst != 0)
    he_FindFirst = 0;
  else
    he_Cursor++;
  for (;;) {
    if (he_Cursor->kind != 0) {
      match = 1;
      if (he_FindKind != 0xff) {
        if ((unsigned char)he_Cursor->kind == he_FindKind)
          ok = 1;
        else
          match = 0;
      }
      if (match && he_FindId != -1) {
        if (he_Cursor->id == he_FindId)
          ok = 1;
        else
          match = 0;
      }
      if (match && he_FindChr != 0xffff) {
        if (he_Cursor->chr == he_FindChr)
          ok = 1;
        else
          match = 0;
      }
      if (match && he_FindFrom != -1) {
        if (he_Cursor->from == he_FindFrom)
          break;
        match = 0;
      }
      if (!match)
        ok = 0;
    }
    if (ok)
      break;
    if (he_Cursor >= last) {
      he_Cursor = 0;
      break;
    }
    he_Cursor++;
  }
  return he_Cursor;
}
/* 0x53e400, starts a search of the event records: n pairs (key, value) set the filter, key 0 the kind (he_FindKind),
   1 the event id (he_FindId), 2 the character index (he_FindChr), 3 the sending building (he_FindFrom), the others
   unset; puts he_Cursor on the first used record (0 when there is none) and returns he_NextEvent's first match */
AIJOB *he_FindEvent(int n, ...) {
  va_list ap;
  int i;

  he_FindKind = 0xff;
  he_FindId = -1;
  he_FindChr = 0xffff;
  he_FindFrom = -1;
  he_FindFirst = 1;
  he_FindUnused = 0;
  va_start(ap, n);
  for (i = n; i > 0; i--) {
    switch ((unsigned char)va_arg(ap, int)) {
    case 0:
      he_FindKind = (unsigned char)va_arg(ap, int);
      break;
    case 1:
      he_FindId = va_arg(ap, int);
      break;
    case 2:
      he_FindChr = (unsigned short)va_arg(ap, int);
      break;
    case 3:
      he_FindFrom = va_arg(ap, int);
      break;
    }
  }
  va_end(ap);
  he_Cursor = he_Events;
  for (i = 0; he_Cursor->kind == 0; i++) {
    if (i >= 0x400)
      break;
    he_Cursor++;
  }
  if (i >= 0x400)
    he_Cursor = 0;
  return he_NextEvent();
}

/* 0x53e4e0, spreads the gfx infos over the object `obj` (at most 0x20) on a circle around its position: radius 100 (0 for
   a single one), each at half its own height above obj's top */
void he_SpreadGfxInfos(D3OBJECT *obj) {
  int cnt = 0;
  HEGFXINFO *list[32];
  D3VECTOR4 pos;
  float lo, hi, rad, ang;
  int i;
  D3VECTOR4 at;

  for (i = 0; i < 0x40; i++) {
    if (cnt >= 0x20)
      break;
    if (he_GfxInfos[i].parent == obj)
      list[cnt++] = &he_GfxInfos[i];
  }
  rad = 0.0f;
  if (cnt != 1)
    rad = 100.0f;
  d3_PointToWorld(obj, &obj->pos, &pos.v);
  d3t_GetHeightRange(obj, &lo, &hi);
  pos.y = hi;
  for (i = 0; i < cnt; i++) {
    d3t_GetHeightRange(list[i]->obj, &lo, &hi);
    ang = i * 6.2831855f / (float)cnt;
    at.x = (float)(sin(ang) * rad + pos.x);
    at.y = (float)((hi - lo) * 0.5 + pos.y);
    at.z = (float)(cos(ang) * rad + pos.z);
    d3_SetObjectPos(list[i]->obj, &at.v);
  }
}
/* 0x53e5f0, creates the model object `name` of the gfx info `e` at the top of `obj` (its world position, at its
   height's top), parent obj: shadow mask bits 0xc on, saved-with-scene and flag 4 off, kind 5, alpha 0x80, vertex
   colour (0xc0, 0xa0, 0x80), and a two-key path that turns it about y by 64 pi in 0x8c0; then re-spreads obj's
   gfx infos (he_SpreadGfxInfos). The object, 0 when it could not be created */
D3OBJECT *he_CreateGfxObject(HEGFXINFO *e, char *name, D3OBJECT *obj) {
  D3TEXFLAGS alpha;
  D3ANIMFLAGS f;
  D3VECTOR4 pos; /* the engine's padded vector */
  float lo, hi;
  D3OBJECT *o;
  D3ANIMKEY keys[2];

  d3_PointToWorld(obj, &obj->pos, &pos.v);
  d3t_GetHeightRange(obj, &lo, &hi);
  pos.y = hi;
  o = d3_CreateObject(0, &pos.v, &d3_Origin.v, name);
  e->obj = o;
  e->parent = obj;
  if (o != 0) {
    o->objectFlags &= ~2;
    o->stateFlags |= 0xc;
    o->flags &= ~4;
    o->kind = 5;
    alpha.all = 0;
    alpha.b[2] = 1;
    alpha.b[0] = 0x80;
    d3_SetObjectAlpha(o, o->info, alpha);
    d3t_SetColor(o, 0xc0, 0xa0, 0x80);
    memset(&f, 0, sizeof(f));
    keys[0].time = 0x8c0;
    keys[1].rot.y = 201.06193f; /* 64 pi */
    f.b[1] &= ~0x14;
    f.b[8] |= 2;
    f.b[1] &= ~8;
    f.b[0] = 0;
    f.b[1] &= ~1;
    keys[0].rot.x = 0.0f;
    keys[0].rot.y = 0.0f;
    keys[0].rot.z = 0.0f;
    keys[0].pos.x = 0.0f;
    keys[0].pos.y = 0.0f;
    keys[0].pos.z = 0.0f;
    keys[1].rot.x = 0.0f;
    keys[1].rot.z = 0.0f;
    keys[1].pos.x = 0.0f;
    keys[1].pos.y = 0.0f;
    keys[1].pos.z = 0.0f;
    d3anim_CreatePath(o, f, 2, keys);
    he_SpreadGfxInfos(obj);
  }
  return o;
}
/* 0x53e780, adds a gfx info for the event `ev`: the model `name` over the object `parent` in the first free of the 0x40
   he_GfxInfos (he_CreateGfxObject), with the 3D option (ai_GameSwitches byte 3) only; an unknown parent gives the
   message "he_CreateGfxInfo(): invalid parent :%s" (formatted, never shown; %s prints the parent's name at its
   offset 0). Selects scene 0 meanwhile */
void he_CreateGfxInfo(AIJOB *ev, char *name, D3OBJECT *parent) {
  int scene = d3_CurrentScene;
  int i;
  HEGFXINFO *e;
  char buf[0x200];

  if (ai_GameSwitches.byte[3] != 0) {
    for (i = 0; i < 0x40; i++) {
      if (he_GfxInfos[i].ev == 0)
        break;
    }
    if (i != 0x40) {
      e = &he_GfxInfos[i];
      d3if_SelectScene(0, 1);
      if (d3_FindObject(0, 0x40, parent, 0) == 0) {
        sprintf(buf, "he_CreateGfxInfo(): invalid parent :%s", parent->name);
        d3if_SelectScene(scene, 1);
      } else {
        e->ev = ev;
        e->eventId = ev->id;
        e->parent = 0;
        ev->gfx = e;
        he_CreateGfxObject(e, name, parent);
        d3if_SelectScene(scene, 1);
      }
    }
  }
}
/* 0x53e840, removes the gfx info `e` (frees its object, re-spreads the others on the same parent) */

void he_FreeGfxInfo(HEGFXINFO *g) {
  int sv;
  D3OBJECT *par = g->parent;

  if (g->obj != 0) {
    sv = d3_CurrentScene;
    g->parent = 0;
    d3if_SelectScene(0, 1);
    if (par != 0) {
      if (d3_FindObject(0, 0x1c0, par, 0) != 0)
        he_SpreadGfxInfos(par);
    }
    d3if_Delete(g->obj);
    g->obj = 0;
    d3if_SelectScene(sv, 1);
  }
  g->ev = 0;
  g->eventId = -1;
}
/* 0x53e8b0, adds the gfx info of the event `ev` by its kind when it has none (3D option only): 0x1b a coin, 0x1c / 0x1e
   a gold (saw) hammer, 0x1f / 2 a plus hammer, 0x40 binoculars (the player's), 0x1a blows over the event's building;
   an exclamation mark over the notice board (0x35, the player's tribute collector, scene 0), the tribune (0x6b at stage
   2, scene 0, unless the player's flags1c8 has 0x20000) or the building of a kind 4 event of the player with argc8 */
void he_AddEventGfxInfo(AIJOB *ev) {
  AIBLD *b;
  unsigned short *ch;
  D3OBJECT *o;

  if (ai_GameSwitches.byte[3] == 0)
    return;
  if (ev->gfx != 0)
    return;
  switch ((unsigned char)ev->kind) {
  case 0x1b:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0)
      he_CreateGfxInfo(ev, "he_muenze", b->object);
    break;
  case 0x1c:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0 && b->object != 0)
      he_CreateGfxInfo(ev, "he_hammer_gold", b->object);
    break;
  case 0x1e:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0 && b->object != 0)
      he_CreateGfxInfo(ev, "he_saege_hammer_gold", b->object);
    break;
  case 0x1f:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0 && b->object != 0)
      he_CreateGfxInfo(ev, "he_plus_hammer", b->object);
    break;
  case 2:
    b = gm_FindBuildingById(ev->from);
    if (b != 0 && b->object != 0)
      he_CreateGfxInfo(ev, "he_plus_hammer", b->object);
    break;
  case 0x40:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0 && b->object != 0 && ev->chr == ai_PlayerId)
      he_CreateGfxInfo(ev, "he_fernglas", b->object);
    break;
  case 0x35:
    ch = (unsigned short *)gm_FindChar(ev->idbc);
    if (ch != 0 && *ch == ai_PlayerId && d3_CurrentScene == 0) {
      o = d3_FindObject(0, 0x40, 0, "ob_SCHWARZES_BRETT");
      if (o != 0)
        he_CreateGfxInfo(ev, "he_ausrufezeichen", o);
    }
    break;
  case 0x6b:
    if (ev->stage == 2 && d3_CurrentScene == 0 &&
        (ai_Chars[ai_PlayerId].flags1c8 & 0x20000) == 0) {
      o = d3_FindObject(0, 0x40, 0, "ob_TRIBUENE");
      if (o != 0)
        he_CreateGfxInfo(ev, "he_ausrufezeichen", o);
    }
    break;
  case 0x1a:
    b = gm_FindBuildingById(ev->bldd0);
    if (b != 0 && b->object != 0)
      he_CreateGfxInfo(ev, "he_schlaege", b->object);
    break;
  case 4:
    if (ev->chr == ai_PlayerId && ev->argc8 != 0) {
      b = gm_FindBuildingById(ev->idbc);
      if (b != 0 && b->object != 0)
        he_CreateGfxInfo(ev, "he_ausrufezeichen", b->object);
    }
    break;
  }
}
/* 0x53eba0, removes the gfx infos whose parent changed or when the 3D option is off */

void he_RemoveStaleGfxInfos(void) {
  HEGFXINFO *p;

  for (p = he_GfxInfos; (int)p < (int)(he_GfxInfos + 0x40); p++)
    if (p->ev != 0 && (p->ev->id != p->eventId || ai_GameSwitches.byte[3] == 0))
      he_FreeGfxInfo(p);
}
/* 0x53ebe0, removes the gfx infos of the object `obj` */

void he_RemoveGfxInfos(D3OBJECT *obj) {
  HEGFXINFO *p = he_GfxInfos;

  do {
    if (p->parent == obj)
      he_FreeGfxInfo(p);
    p++;
  } while ((intptr_t)p < (intptr_t)&he_GfxInfos[0x40]);
}
/* 0x53ec10, calls 0x4471b0 for the gfx infos of the object `obj` */

void he_ShowObjectInfos(D3OBJECT *obj, int a) {
  HEGFXINFO *p = he_GfxInfos;

  do {
    if (p->parent == obj)
      d3if_Show(p->obj, a);
    p++;
  } while ((intptr_t)&p->obj < (intptr_t)&he_GfxInfos[0x40].obj);
}
/* 0x53ec40, makes the event `r` due now (stage -2, end = the game clock) when its character is gone (another netId
   or kind 0xf) or dead (health 0) for the kinds of the list */

void he_RecheckEventPerson(AIJOB *ev) {
  unsigned short us = ev->chr;

  if (us == 0xffff)
    return;
  if (ai_Chars[us].netId != ev->netId || ai_Chars[us].kind == 0xf)
    goto reset;
  if (ai_Chars[us].health > 0)
    return;
  switch ((unsigned char)ev->kind) {
  case 0x16:
  case 0x18:
  case 0x19:
  case 0x1a:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x35:
  case 0x36:
  case 0x37:
  case 0x38:
  case 0x41:
  case 0x45:
  case 0x46:
  case 0x47:
  case 0x4a:
  case 0x4b:
  case 0x5e:
  case 0x5f:
  case 0x60:
  case 0x69:
  case 0x6a:
  case 0x6f:
  case 0x7e:
    break;
  default:
    return;
  }
reset:
  ev->stage = -2;
  ev->end = ai_Time;
}
/* 0x53ed40, runs 0x53ec40 on every record of the player *pl (type 2 filter) */

void he_RecheckPersonEvents(unsigned short *pl) {
  AIJOB *iv = he_FindEvent(1, 2, *pl);

  while (iv != 0) {
    he_RecheckEventPerson(iv);
    iv = he_NextEvent();
  }
}
/* 0x53ed70, the per-frame run of the event records: updates the gfx infos, then calls the run handler (0x758600) of every record (not 0x18 flagged) that is due */

void he_RunEvents(void) {
  int iv, i;
  AIJOB *pb;

  he_RemoveStaleGfxInfos();
  i = 0;
  if (he_EventTop >= 0) {
    pb = he_Events;
    do {
      if ((int)pb >= (int)(he_Events + 0x400))
        return;
      if (pb->kind != 0 && (pb->opts & 0x18) == 0) {
        he_AddEventGfxInfo(pb);
        iv = gm_CompareTime(&ai_Time, &pb->end);
        if (iv > 0 && (unsigned char)pb->kind < 0xa7) {
          he_RecheckEventPerson(pb);
          he_RunHandlers[(unsigned char)pb->kind](pb);
        }
      }
      i++;
      pb++;
    } while (i <= he_EventTop);
  }
}
/* 0x53edf0, runs the run handler of the quick list records (0x74db40) */

void he_RunQuickList(void) {
  AIJOB *pb;
  int i = 0;

  if (he_QuickTop >= 0) {
    do {
      if (i >= 0x100)
        return;
      pb = he_QuickList[i];
      if (pb != 0 && pb->kind < 0xa7) {
        he_RecheckEventPerson(pb);
        he_RunHandlers[pb->kind](pb);
      }
      i++;
    } while (i <= he_QuickTop);
  }
}
/* 0x53ee40, runs the run handler of the records with the option 0x10 (runs every frame) */

void he_RunEveryFrameEvents(void) {
  AIJOB *pb;
  int i = 0;

  if (he_EventTop >= 0) {
    pb = he_Events;
    do {
      if ((int)pb >= (int)(he_Events + 0x400))
        return;
      if (pb->kind != 0 && (pb->opts & 0x10) != 0 &&
          (unsigned char)pb->kind < 0xa7) {
        he_RecheckEventPerson(pb);
        he_RunHandlers[(unsigned char)pb->kind](pb);
      }
      i++;
      pb++;
    } while (i <= he_EventTop);
  }
}
/* 0x53eea0, counts the time to live of the 0x100 carried-goods records (gm_CarryRecs) down, freeing (ref 0) each one
   that reaches 0 */
void he_AgeCarryRecs(void) {
  int i;

  for (i = 0; i < 0x100; i++) {
    if (--gm_CarryRecs[i].ttl == 0)
      gm_CarryRecs[i].ref = 0;
  }
}
/* 0x53eec0, registers the AP event `name` of the character `key` with `income` and `cost` in the first free (no
   income, cost or name) of the 0x100 he_ApEvents, for 2 rounds; 0 when all are used */
HEAPEVENT *he_AddApEvent(int key, char *name, int income, int cost) {
  int i;
  HEAPEVENT *e;

  for (i = 0; i < 0x100; i++) {
    if (he_ApEvents[i].income == 0 && he_ApEvents[i].cost == 0 &&
        he_ApEvents[i].name[0] == 0)
      break;
  }
  if (i >= 0x100) {
    err_Message("he_RegisterApEvent(): Too many ApEvents...");
    return 0;
  }
  e = &he_ApEvents[i];
  e->key = key;
  e->income = income;
  e->cost = cost;
  e->counter = 2;
  strncpy(e->name, name, 0x3f);
  return e;
}
/* 0x53ef50, counts the rounds of the he_ApEvents down; an expired one loses its income, cost and name (is free) */
void he_CountDownApEvents(void) {
  int i;

  for (i = 0; i < 0x100; i++) {
    if (--he_ApEvents[i].counter <= 0) {
      he_ApEvents[i].income = 0;
      he_ApEvents[i].cost = 0;
      he_ApEvents[i].name[0] = 0;
    }
  }
}
/* 0x53ef80, the sum of the values (+8) of the AP events with key (+4) `key` */

int he_SumApEvents(int key) {
  int sum = 0;
  HEAPEVENT *p = he_ApEvents;

  do {
    if (p->income != 0 && p->key == key)
      sum += p->income;
    p++;
  } while ((intptr_t)&p->income < (intptr_t)&he_ApEvents[0x100].income);
  return sum;
}
/* 0x53efb0, the sum of the values (+0xc) of the AP events with key (+4) `key` */

int he_SumApEventCosts(int key) {
  int sum = 0;
  HEAPEVENT *p = he_ApEvents;

  do {
    if (p->cost != 0 && p->key == key)
      sum += p->cost;
    p++;
  } while ((intptr_t)&p->cost < (intptr_t)&he_ApEvents[0x100].cost);
  return sum;
}

/* the 0x6d / 0x6b / 0x7a events of the current player when none exists yet (one message of 0xf8 bytes) */
#define HE_ONCE(typ)                                                           \
  AIMSG m;                                                                     \
  if (he_FindEvent(1, 0, typ) == 0) {                                          \
    memset(&m, 0, sizeof(m));                                                  \
    m.type = typ;                                                              \
    m.fromId = -1;                                                             \
    m.flags = 2;                                                               \
    m.to = ai_Chars[ai_PlayerId].netId;                                        \
    m.time = ai_Time;                                                          \
    cm_SendLongMessage(&m);                                                    \
  }

/* 0x53efe0, posts the event 0x6d (once) */
void he_PostEvent6d(void) { HE_ONCE(0x6d) }
/* 0x53f070, posts the event 0x6b (once) */

void he_PostEvent6b(void) { HE_ONCE(0x6b) }
/* 0x53f100, posts the event 0x7a (once) */

void he_PostEvent7a(void) { HE_ONCE(0x7a) }
/* 0x53f190, posts the tavern event 0x2b for every building of kind 5 / 7 that has none yet (the message's fromId is the
   building); once one building has its event, the rest of the walk posts nothing */
void he_PostEvent2b(void) {
  AIMSG m;
  int found = 0;
  AIJOB *ev;
  AIBLD *b;

  memset(&m, 0, sizeof(m));
  for (b = gm_BuildQuery(1, 5, 7); b != 0; b = gm_BuildNext()) {
    for (ev = he_FindEvent(1, 0, 0x2b); ev != 0; ev = he_NextEvent()) {
      if (ev->from == b->id) {
        found = 1;
        break;
      }
    }
    if (!found) {
      m.type = 0x2b;
      m.time = ai_Time;
      m.flags = 2;
      m.to = ai_PlayerChar->netId;
      m.fromId = b->id;
      m.tavern.mode = 0;
      cm_SendLongMessage(&m);
    }
  }
}
/* 0x53f270, posts the events 0x86 and 0xa2 to the player's character, each when none exists yet */
void he_PostPlayerEvents86a2(void) {
  AIMSG m;

  if (he_FindEvent(1, 0, 0x86) == 0) {
    memset(&m, 0, sizeof(m));
    m.type = 0x86;
    m.to = ai_PlayerChar->netId;
    m.fromId = -1;
    m.flags = 2;
    m.time = ai_Time;
    cm_SendLongMessage(&m);
  }
  if (he_FindEvent(1, 0, 0xa2) == 0) {
    memset(&m, 0, sizeof(m));
    m.type = 0xa2;
    m.to = ai_PlayerChar->netId;
    m.fromId = -1;
    m.flags = 2;
    m.time = ai_Time;
    cm_SendLongMessage(&m);
  }
}
/* 0x53f370, posts the event 0x98 for every building of kind 0x1e (workshop) that has none (he_FindEvent key 3, the
   message's fromId: the building) and an owner (ahm_OwnerChar), to that owner */
void he_PostWorkshopEvents98(void) {
  AIBLD *b;
  AICHAR *o;

  for (b = gm_BuildQuery(1, 5, 0x1e); b != 0; b = gm_BuildNext()) {
    AIMSG m;

    if (he_FindEvent(2, 0, 0x98, 3, b->id) == 0 &&
        (o = ahm_OwnerChar(b)) != 0) {
      memset(&m, 0, sizeof(m));
      m.type = 0x98;
      m.to = o->netId;
      m.fromId = b->id;
      m.flags = 2;
      m.time = ai_Time;
      cm_SendLongMessage(&m);
    }
  }
}
/* 0x53f430, for every inn building (type 0x16) sends the table request "leav" to the four seats of its table (the
   object 0x12d) whose figure is gone, dead (health 0) or a corpse (kind 0xf) ("stammtisch supervisor") */

void he_InnStaffLeave(void) {
  AIBLD *f;
  AIOBJ *r;
  AICHAR *o;
  int k;
  int *p;

  f = gm_BuildQuery(1, 5, 0x16);
  while (f != 0) {
    r = gm_Query(f->objList, 1, 0, 0x120);
    if (r != 0 && (r = gm_Query(r->list, 1, 0, 0x12d)) != 0) {
      p = r->seats;
      for (k = 4; k != 0; k--) {
        if (*p != -1 &&
            ((o = gm_FindChar(*p)) == 0 || o->health == 0 || o->kind == 0xf)) {
          G17TABLEMSG arg;

          arg.op = 0x6c656176;
          arg.bldId = f->id;
          arg.charId = *p;
          cm_BeginGroup("stammtisch supervisor");
          cm_SendTableRequest(&arg);
          cm_EndGroup("stammtisch supervisor");
        }
        p++;
      }
    }
    f = gm_BuildNext();
  }
}
/* 0x53f500, for every inn building (type 0x16) whose job table (object 0x12c) was started more than one year ago sends
   the script message "cler" to clear its dark corner ("clear dunkle ecke") */

void he_ClearInnDarkCorner(void) {
  AIBLD *f;
  AIOBJ *r;

  f = gm_BuildQuery(1, 5, 0x16);
  while (f != 0) {
    r = gm_Query(f->objList, 1, 0, 0x120);
    if (r != 0 && (r = gm_Query(r->list, 1, 0, 300)) != 0 &&
        ai_Time.year - r->cornerYear > 1) {
      int arg
          [5]; /* the 0x14-byte record cm_SendScriptMessage copies; arg[4] left unset */

      arg[0] = 0x636c6572;
      arg[2] = f->id;
      arg[1] = -1;
      arg[3] = -1;
      cm_BeginGroup("clear dunkle ecke");
      cm_SendScriptMessage(arg);
      cm_EndGroup("clear dunkle ecke");
    }
    f = gm_BuildNext();
  }
}
/* 0x53f5b0, tops up the money of the characters of kind 5 and 4 (kind 2 when the year % 4 is its net id & 3) to the
   level 0x640 * (difficulty * 5 + 0x14), from the own player (no source); after 0x20 transfers it waits for the last
   one's send slot */
void he_TopUpCharMoney(void) {
  int i, level, have, n, slot = -1;

  if (ai_Time.year % (ai_Time.year / 10 + 1) == 0) {
    level = (ai_Difficulty * 5 + 0x14) * 0x640;
    n = 0;
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].kind == 5) {
        have = gm_GetGoodsValue(&ai_Chars[i]);
        if (have < level) {
          slot = cm_SendMoveGoods(ai_Chars[i].netId, -1, ai_OwnPlayer,
                                  level - have);
          n++;
        }
      } else if (ai_Chars[i].kind == 4 ||
                 (ai_Chars[i].kind == 2 &&
                  ai_Time.year % 4 == (int)(ai_Chars[i].netId & 3))) {
        have = gm_GetGoodsValue(&ai_Chars[i]);
        if (have < level) {
          slot = cm_SendMoveGoods(ai_Chars[i].netId, -1, ai_OwnPlayer,
                                  level - have);
          n++;
        }
      }
      if (n >= 0x20 && slot != -1) {
        do {
          if (cm_GetSlotState(slot) != 0)
            break;
          sv_PumpNet();
        } while (1);
        slot = -1;
        n = 0;
      }
    }
  }
}

/* the ai_Blds walk of he_SpawnFounders: i is the first building of the kind k that is the player's or nobody's
   (owner 0xffff), 0x100 when there is none (the original reuses the option loop's i for it) */
#define HE_FIND_OWN(k)                                                         \
  for (i = 0, b = ai_Blds; i < 0x100; i++, b++) {                              \
    if (b->type != 0) {                                                        \
      bt = &ai_BTypes[b->type];                                                \
      if (bt->kind == (k) &&                                                   \
          (b->owner == 0xffff || b->owner == ai_PlayerChar->id))               \
        break;                                                                 \
    }                                                                          \
  }

/* that building b (of the type bt)'s offer: twice its equipment value, the title of the group at its type's level */
#define HE_OFFER_FOUND(group)                                                  \
  do {                                                                         \
    amt = gm_EquipmentValue(b, 100) * 2;                                       \
    title = gm_TitleNumber(group, bt->cap247 * 2 - 1);                         \
  } while (0)

/* the offer without a building: twice the value of the building kind bk, the title (group, rank) */
#define HE_OFFER_KIND(bk, group, rank)                                         \
  do {                                                                         \
    amt = gm_BuildingKindValue(bk) * 2;                                        \
    title = gm_TitleNumber(group, rank);                                       \
  } while (0)

/* creates the founder (a kind 4 character with the title), waits for its send slot and, when it was created, gives it
   amt from the own player and sets its field 0xd to 2 (and what `extra` adds). A plain block (used without a `;`):
   as a do { } while (0) statement its end is one more block in front of the option loops' step, and VC6 splits the
   live ranges there another way */
#define HE_SEND_FOUNDER(rnd, extra)                                            \
  {                                                                            \
    slot = cm_SendCreateCharacter(4, -1, -1, util_Random(4) + 0xf, -1, title,  \
                                  0, rnd);                                     \
    while (slot != -1 && cm_GetSlotState(slot) == 0)                           \
      sv_PumpNet();                                                            \
    if (cm_GetSlotState(slot) == 1) {                                          \
      int two;                                                                 \
      two = 2;                                                                 \
      c = (AICHAR *)cm_GetSlotValue(slot);                                     \
      cm_SendMoveGoods(c->netId, -1, ai_OwnPlayer, amt);                       \
      cm_BeginFieldBlock(c, c->netId);                                         \
      cm_AddFieldDelta(1, 1, 0xd, &two);                                       \
      extra;                                                                   \
      cm_SendFieldDeltas();                                                    \
    }                                                                          \
  }

const float he_FounderOdds[5] = {
    4.0f, 3.0f, 2.5f, 1.5f,
    1.0f}; /* 0x5eebc4, the odds of a founder by the difficulty: x / (x + odds) (he_SpawnFounders, its only reader; first in he.c's .rdata literals) */

/* he's .data block (0x625708..0x626680, then its strings): the event search filter and bar state, the ambush
   spots ai.c reads, the event names cm.c reads (the block's object owns them) */
unsigned char he_FindKind = 0xff;   /* 0x625708, he.h */
int he_FindId = -1;                 /* 0x62570c, he.h */
unsigned short he_FindChr = 0xffff; /* 0x625710, he.h */
int he_FindFrom = -1;               /* 0x625714, he.h */
int he_LastSlot = -1;               /* 0x625718, he.h */
int he_BarShown = -1;               /* 0x62571c, he.h */
char ai_AmbushSpots[8][32] = {
    "sp_AUFLAUERLEGEN_NORDEN",
    "sp_AUFLAUERLEGEN_OSTEN",
    "sp_AUFLAUERLEGEN_SUEDEN",
    "sp_AUFLAUERLEGEN_WESTEN",
    "sp_AUFLAUERLEGEN_STADT_1",
    "sp_AUFLAUERLEGEN_STADT_2",
    "sp_AUFLAUERLEGEN_STADT_3",
    "sp_AUFLAUERLEGEN_STADT_4"}; /* 0x625720, "sp_AUFLAUERLEGEN_NORDEN" ... */
char cm_EventNames[115][0x20] = {
    "HE_NULL",
    "HE_HISTORIE",
    "HE_UPGRADE_DUMMY",
    "HE_ABBAU",
    "HE_PRODUKTION",
    "HE_PRODUKTION_FERTIG_MSG",
    "HE_ARBEITER_EINSTELLEN",
    "HE_MEISTER_EINSTELLEN",
    "HE_VORKOMMEN_SUCHEN",
    "HE_NEUE_VORKOMMEN_SUCHEN",
    "HE_NEUE_VORKOMMEN_SUCHEN_MSG",
    "HE_AI_WATCH_TRANSPORT",
    "HE_OBJEKT_BAUEN",
    "HE_GEBAEUDE_BAUEN",
    "HE_MAUER_BAUEN",
    "HE_TRANSPORT",
    "HE_REPARATUR",
    "HE_MESSAGEBOX",
    "HE_LAGERSLOTS_BAUEN",
    "HE_LAGER_ERWEITERN",
    "HE_KRAEUTER_SAMMELN",
    "HE_GETIER_FANGEN",
    "HE_SPIELER_TRAINIEREN",
    "HE_GEHEIM_TREFFEN",
    "HE_SPIONAGE",
    "HE_SABOTAGE",
    "HE_PRUEGEL",
    "HE_GEB_VERKAUFEN",
    "HE_GEB_RENOVIEREN",
    "HE_GEB_VERMIETEN_DUMMY",
    "HE_GEB_UPGRADEN",
    "HE_GEB_RAUM_UPGRADEN",
    "HE_GEB_ABREISSEN",
    "HE_GEB_KAUFANGEBOT",
    "HE_SITZUNG",
    "HE_KREDIT",
    "HE_MEISTER_PRUEFUNG",
    "HE_MEISTER_PRUEFUNG_MSG",
    "HE_MEISTER_BESTANDEN",
    "HE_GELDBOTE",
    "HE_ERNTEN",
    "HE_STAMMTISCH_MSG",
    "HE_STAMMTISCH",
    "HE_GOTTESDIENST",
    "HE_PROZESS",
    "HE_DROHEN_MSG",
    "HE_DROHEN",
    "HE_ANSCHWAERZEN_MSG",
    "HE_BUCH_SCHREIBEN",
    "HE_ENTLASSEN",
    "HE_BEFOERDERN",
    "HE_PERSONAL_KUENDIGEN",
    "HE_PERSONAL_STEHLEN",
    "HE_PAMPHLET",
    "HE_FEST_MSG",
    "HE_FEST",
    "HE_GELAGE",
    "HE_KERKER_MEISTER_BESTECHEN",
    "HE_SIM_PERSONAL",
    "HE_MARKT_SUPERVISOR",
    "HE_ENTFUEHREN",
    "HE_SPIELER_ENTFUEHRT",
    "HE_LOESEGELD",
    "HE_EINBRUCH",
    "HE_GEB_SPIONAGE",
    "HE_WERBUNG",
    "HE_RANDOM_EVENT",
    "HE_STREIFE",
    "HE_RAZZIA",
    "HE_ERPRESSUNG",
    "HE_BELEIDIGUNG_MSG",
    "HE_BELEIDIGUNG",
    "HE_UEBERFALL",
    "HE_ANGRIFF",
    "HE_RANDOM_GESELLE",
    "HE_FURCHT_EINFLOESSEN",
    "HE_MISSION_SUPERVISOR",
    "HE_MISSION_DONE_MSG",
    "HE_EVT_GROSS_BRAND",
    "HE_EVT_BRAND",
    "HE_EVT_WIRBELSTURM",
    "HE_EVT_RAUBRITTER",
    "HE_EVT_KOMMENTARE",
    "HE_EVT_STADTFEST",
    "HE_EVT_SPENDE",
    "HE_EVT_BETEILIGUNG_MSG",
    "HE_EVT_BETEILIGUNG",
    "HE_EVT_SOELDNER_PLUENDERN",
    "HE_EVT_SOELDNER_MARODIEREN",
    "HE_EVT_PEST",
    "HE_ESKORTE_VERHINDERN",
    "HE_GELDSTRAFE",
    "HE_PRANGER",
    "HE_NACHWUCHS",
    "HE_BERUFSAUSBILDUNG",
    "HE_UNI",
    "HE_TALENT_SPIELER",
    "HE_TASCHENDIEB",
    "HE_SCHUTZGELD",
    "HE_SCHUTZGELD_MSG",
    "HE_BETRIEBS_PRUEFUNG",
    "HE_UMLAND_PATROL",
    "HE_SIM_UNFALL",
    "HE_PACHT",
    "HE_SIM_WIRTSHAUS",
    "HE_TITEL_VERGABE",
    "HE_AMT_VERGABE",
    "HE_BARDE",
    "HE_HEILEN",
    "HE_SIM_EINWANDERUNG",
    "HE_INIT_BETRIEB",
    "HE_GELIEBTE",
    "HE_SIM_KRANKHEITEN",
    "HE_DIE_PLAYER",
    "HE_KILL_PLAYER"}; /* 0x625820, names ("HE_NULL", ..) */

/* 0x53f6b0, the founders of the round (main_BeginPlayerRound): tops up the money of the characters (he_TopUpCharMoney),
   counts the buildings per kind (all, and the player's or nobody's; of kind 7 the others' by their owner's b00c) and
   by the year % 5 looks at a group of building kinds (1: 4 / 0x13 / 0x10, 2: 0x12 / 0x15 / 0x14 / 0xe, 3: 8 / 0x16,
   0: 9 / 7 / 5, 4: 0x20 / 0x1f / 0x1d); the kinds the town has few of (fewer than 3, or the player's share at least
   a half) are eligible, the missing ones always, else one at random when util_RandomF() <= x / (x + odds[level]),
   x = year / 4 + 1; for each chosen kind it creates a founder character paid twice the value of the player's first
   building of the kind (or of the building kind) (reasoned: the character of kind 4 that he_TopUpCharMoney keeps in
   money, its title from the kind's group) */
void he_SpawnFounders(void) {
  int cnt[0x21]; /* the buildings per kind */
  int own[0x21]; /* the player's or nobody's per kind */
  int lvl, x, i, t;
  int n7a = 0,
      n7b; /* the others' buildings of kind 7: owner's b00c 0 / not 0 */
  float gate;
  int amt, title, slot;
  AIBLD *b;
  AIBTYPE *bt;
  AICHAR *c;

  n7b = 0;
  lvl = max(min(4, ai_Difficulty), 0);
  x = ai_Time.year / 4 + 1;
  gate = (float)x / ((float)x + he_FounderOdds[lvl]);
  he_TopUpCharMoney();
  memset(cnt, 0, sizeof(cnt));
  memset(own, 0, sizeof(own));
  for (i = 0, b = ai_Blds; i < 0x100; i++, b++) {
    if (b->type != 0) {
      bt = &ai_BTypes[b->type];
      if (bt->kind < 0x21) {
        cnt[bt->kind]++;
        if (b->owner == 0xffff || b->owner == ai_PlayerChar->id)
          own[bt->kind]++;
        else if (bt->kind == 7) {
          if (ai_Chars[b->owner].faith == 0)
            n7a++;
          else
            n7b++;
        }
      }
    }
  }
  t = ai_Time.year % 5;
  if (t == 1) {
    int d4, d13, d10, mask, zero, pick;
    int r, n;
    /* the others' buildings of the kinds 4 / 0x13 / 0x10 */
    d4 = cnt[4] - own[4];
    d10 = cnt[0x10] - own[0x10];
    d13 = cnt[0x13] - own[0x13];
    mask = 0;
    pick = 0;
    zero = 0;
    if (d4 < 3)
      mask |= 1;
    if (d4 == 0)
      zero |= 1;
    if (d13 < 3)
      mask |= 2;
    if (d13 == 0)
      zero |= 2;
    if (d10 < 3)
      mask |= 4;
    if (d10 == 0)
      zero |= 4;
    if (zero != 0) {
      r = util_Random(3);
      for (n = 3; n != 0; n--, r = (r + 1) % 3) {
        if (mask & (1 << r)) {
          pick = mask = 1 << r;
          break;
        }
      }
    } else {
      if (util_RandomF() > gate)
        return;
      if (d4 + d10 > d13 * 2 && (mask & 2))
        pick = 2;
      else if (d4 + d10 < d13 * 2) {
        if (d4 < d10) {
          if (mask & 1)
            pick = 1;
        } else if (mask & 4)
          pick = 4;
      } else
        pick = 1 << util_Random(3);
    }
    if (!(mask & pick))
      return;
    if (pick == 1) {
      if (cnt[4] < 3) {
        amt = gm_BuildingKindValue(0xb) * 2;
        title = 6;
      } else {
        HE_FIND_OWN(4);
        if (i >= 0x100)
          return;
        HE_OFFER_FOUND(0xb);
      }
    } else if (pick == 2) {
      if (cnt[0x13] < 3) {
        amt = gm_BuildingKindValue(0x2c) * 2;
        title = 0x39;
      } else {
        HE_FIND_OWN(0x13);
        if (i >= 0x100)
          return;
        HE_OFFER_FOUND(10);
      }
    } else {
      title = 0x2d;
      amt = gm_BuildingKindValue(0x27) * 2;
    }
    HE_SEND_FOUNDER(0, (void)0)
  } else if (t == 2) {
    float r0, r1, r2, r3;
    int elig, zero, bit;
    int r, n;
    /* the kinds 0x12 / 0x15 / 0x14 / 0xe */
    r0 = cnt[0x12] > 0 ? (float)own[0x12] / cnt[0x12] : 0.0f;
    r1 = cnt[0x15] > 0 ? (float)own[0x15] / cnt[0x15] : 0.0f;
    r2 = cnt[0x14] > 0 ? (float)own[0x14] / cnt[0x14] : 0.0f;
    r3 = cnt[0xe] > 0 ? (float)own[0xe] / cnt[0xe] : 0.0f;
    elig = 0;
    zero = 0;
    if (cnt[0x12] < 3 || r0 >= 0.5f) {
      elig |= 1;
      if (cnt[0x12] == 0)
        zero |= 1;
    }
    if (cnt[0x15] < 3 || r1 >= 0.5f) {
      elig |= 2;
      if (cnt[0x15] == 0)
        zero |= 2;
    }
    if (cnt[0x14] < 3 || r2 >= 0.5f) {
      elig |= 4;
      if (cnt[0x14] == 0)
        zero |= 4;
    }
    if (cnt[0xe] < 3 || r3 >= 0.5f) {
      elig |= 8;
      if (cnt[0xe] == 0)
        zero |= 8;
    }
    if (zero != 0)
      elig = zero;
    else {
      if (util_RandomF() > gate)
        return;
      r = util_Random(4);
      for (n = 4; n != 0; n--, r = (r + 1) % 4) {
        if (elig & (1 << r)) {
          elig = 1 << r;
          break;
        }
      }
    }
    for (i = 0; i < 4; i++) {
      if (elig == 0)
        return;
      bit = elig & (1 << i);
      if (bit == 1) {
        if (cnt[0x12] < 3)
          HE_OFFER_KIND(0x29, 1, 1);
        else {
          HE_FIND_OWN(0x12);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(1);
        }
      } else if (bit == 2) {
        if (cnt[0x15] < 3)
          HE_OFFER_KIND(0x32, 3, 1);
        else {
          HE_FIND_OWN(0x15);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(3);
        }
      } else if (bit == 4) {
        if (cnt[0x14] < 3)
          HE_OFFER_KIND(0x2f, 2, 1);
        else {
          HE_FIND_OWN(0x14);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(2);
        }
      } else if (bit == 8) {
        if (cnt[0xe] < 3)
          HE_OFFER_KIND(0x21, 5, 1);
        else {
          HE_FIND_OWN(0xe);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(5);
        }
      } else
        continue;
      HE_SEND_FOUNDER(util_Random(2), (void)0)
    }
  } else if (t == 3) {
    float r0, r1;
    int elig, zero, bit;
    int r, n;
    /* the kinds 8 / 0x16 */
    r0 = cnt[8] > 0 ? (float)own[8] / cnt[8] : 0.0f;
    r1 = cnt[0x16] > 0 ? (float)own[0x16] / cnt[0x16] : 0.0f;
    elig = 0;
    zero = 0;
    if (cnt[8] < 3 || r0 >= 0.5f) {
      elig |= 1;
      if (cnt[8] == 0)
        zero |= 1;
    }
    if (cnt[0x16] < 3 || r1 >= 0.5f) {
      elig |= 2;
      if (cnt[0x16] == 0)
        zero |= 2;
    }
    if (zero != 0)
      elig = zero;
    else {
      if (util_RandomF() > gate)
        return;
      r = util_Random(2);
      for (n = 2; n != 0; n--, r = (r + 1) % 2) {
        if (elig & (1 << r)) {
          elig = 1 << r;
          break;
        }
      }
    }
    for (i = 0; i < 2; i++) {
      if (elig == 0)
        return;
      bit = elig & (1 << i);
      if (bit == 1) {
        if (cnt[8] < 3)
          HE_OFFER_KIND(0x17, 6, 1);
        else {
          HE_FIND_OWN(8);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(6);
        }
      } else if (bit == 2) {
        if (cnt[0x16] < 3)
          HE_OFFER_KIND(0x35, 4, 1);
        else {
          HE_FIND_OWN(0x16);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(4);
        }
      } else
        continue;
      HE_SEND_FOUNDER(util_Random(2), (void)0)
    }
  } else if (t == 0) {
    float r0, r2;
    int elig, zero, bit;
    int r, n;
    int fl;
    /* the kinds 9 / 7 / 5; kind 7 also when the others' kind 7 buildings are all of one b00c class */
    r0 = cnt[9] > 0 ? (float)own[9] / cnt[9] : 0.0f;
    r2 = cnt[5] > 0 ? (float)own[5] / cnt[5] : 0.0f;
    elig = 0;
    zero = 0;
    fl = util_Random(2);
    if (cnt[9] < 2 || r0 >= 0.5f) {
      elig |= 1;
      if (cnt[9] == 0)
        zero |= 1;
    }
    if (cnt[7] < 2 || (cnt[7] < 3 && (n7a == 0 || n7b == 0))) {
      elig |= 2;
      if (cnt[7] == 0)
        zero |= 2;
    }
    if (cnt[5] < 2 || r2 >= 0.5f) {
      elig |= 4;
      if (cnt[5] == 0)
        zero |= 4;
    }
    if (zero != 0)
      elig = zero;
    else {
      if (util_RandomF() > gate)
        return;
      r = util_Random(3);
      for (n = 3; n != 0; n--, r = (r + 1) % 3) {
        if (elig & (1 << r))
          break;
      }
    }
    for (i = 0; i < 3; i++) {
      if (elig == 0)
        return;
      bit = elig & (1 << i);
      if (bit == 1) {
        if (cnt[9] < 2)
          HE_OFFER_KIND(0x1a, 8, 1);
        else {
          HE_FIND_OWN(9);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(8);
        }
      } else if (bit == 2) {
        /* the field 0xc: the b00c class of the fewer others' kind 7 buildings (random when even) */
        if (n7a < n7b)
          fl = 0;
        else if (n7a > n7b)
          fl = 1;
        for (i = 0, b = ai_Blds; i < 0x100; i++, b++) {
          if (b->type != 0) {
            bt = &ai_BTypes[b->type];
            if (bt->kind == 7 &&
                (b->owner == 0xffff || b->owner == ai_PlayerChar->id)) {
              HE_OFFER_FOUND(7);
              break;
            }
          }
        }
        if (i >= 0x100) {
          if (cnt[7] < 2)
            HE_OFFER_KIND(0x14, 7, 1);
          else
            HE_OFFER_KIND(0x15, 7, 3);
        }
      } else if (bit == 4) {
        if (cnt[5] < 1)
          HE_OFFER_KIND(0xe, 9, 1);
        else {
          HE_FIND_OWN(5);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(9);
        }
      } else
        continue;
      HE_SEND_FOUNDER(util_Random(2), cm_AddFieldDelta(1, 1, 0xc, &fl))
    }
  } else if (t == 4) {
    float r0, r1, r2;
    int elig, zero, bit;
    int r, n;
    int rnd;
    /* the kinds 0x20 / 0x1f / 0x1d */
    r0 = cnt[0x20] > 0 ? (float)own[0x20] / cnt[0x20] : 0.0f;
    r1 = cnt[0x1f] > 0 ? (float)own[0x1f] / cnt[0x1f] : 0.0f;
    r2 = cnt[0x1d] > 0 ? (float)own[0x1d] / cnt[0x1d] : 0.0f;
    elig = 0;
    zero = 0;
    if (cnt[0x20] < 3 || r0 >= 0.5f) {
      elig |= 1;
      if (cnt[0x20] == 0)
        zero |= 1;
    }
    if (cnt[0x1f] < 3 || r1 >= 0.5f) {
      elig |= 2;
      if (cnt[0x1f] == 0)
        zero |= 2;
    }
    if (cnt[0x1d] < 3 || r2 >= 0.5f) {
      elig |= 4;
      if (cnt[0x1d] == 0)
        zero |= 4;
    }
    if (zero != 0)
      elig = zero;
    else {
      if (util_RandomF() > gate)
        return;
      r = util_Random(3);
      for (n = 3; n != 0; n--, r = (r + 1) % 3) {
        if (elig & (1 << r)) {
          elig = 1 << r;
          break;
        }
      }
    }
    for (i = 0; i < 3; i++) {
      if (elig == 0)
        return;
      rnd = 0;
      bit = elig & (1 << i);
      if (bit == 1) {
        rnd = util_Random(2);
        if (cnt[0x20] < 3)
          HE_OFFER_KIND(0x51, 0xf, 1);
        else {
          HE_FIND_OWN(0x20);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(0xf);
        }
      } else if (bit == 2) {
        if (cnt[0x1f] < 3)
          HE_OFFER_KIND(0x4e, 0xe, 1);
        else {
          HE_FIND_OWN(0x1f);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(0xe);
        }
      } else if (bit == 4) {
        if (cnt[0x1d] < 3)
          HE_OFFER_KIND(0x48, 0xd, 1);
        else {
          HE_FIND_OWN(0x1d);
          if (i >= 0x100)
            return;
          HE_OFFER_FOUND(0xd);
        }
      } else
        continue;
      HE_SEND_FOUNDER(rnd, (void)0)
    }
  }
}

/* 0x540c90, from the year 8 on, in 1 of 4 calls, when no event 0x67 runs: posts the auction message 0x67 about one of
   the player's buildings of the kinds 0x20 / 0x1e / 0x1f (the first of each kind, gm_BuildQuery; one of them at
   random): arg[0] its id, arg[1] its daySum plus ((5 - the AI decision 7's cur) * 0.1 + 0.7) * 0.5 * (earnings +
   daySum), or, when that is not positive, 1 .. 2 times its equipment value */
void he_PostEvent67(void) {
  AIMSG m;
  AIDEC dec;
  AIBLD *cand[3];
  AIBLD *a, *b, *c, *f;
  int n, amt, pick;

  if (ai_Time.year >= 8 && util_Random(4) == 0 &&
      he_FindEvent(1, 0, 0x67) == 0) {
    a = gm_BuildQuery(1, 0, 0x20);
    b = gm_BuildQuery(1, 0, 0x1e);
    c = gm_BuildQuery(1, 0, 0x1f);
    n = 0;
    if (a != 0 && a->owner == ai_PlayerChar->id)
      cand[n++] = a;
    if (b != 0 && b->owner == ai_PlayerChar->id)
      cand[n++] = b;
    if (c != 0 && c->owner == ai_PlayerChar->id)
      cand[n++] = c;
    if (n != 0) {
      pick = util_Random(n);
      gv_GetTableRecord(7, &dec);
      f = cand[pick];
      amt = (int)((f->earnings + f->daySum) *
                  (((5 - dec.cur) * 0.1f + 0.7f) * 0.5f));
      m.type = 0x67;
      m.time = ai_Time;
      m.to = ai_PlayerChar->netId;
      m.fromId = f->id;
      m.arg[0] = f->id;
      m.arg[1] = f->daySum + amt;
      if (m.arg[1] <= 0) {
        amt = gm_EquipmentValue(f, 100);
        m.arg[1] = (int)((util_RandomF() + 1.0f) * amt);
      }
      m.flags = 2;
      cm_SendLongMessage(&m);
    }
  }
}
/* 0x540e40, the inn report of the round: for every inn (kind 5 / 0x16) with an owner and flag 1 of flags5a clear, when
   the owner is a character of kind 6 / 7 and the inn had guests, sends the owner the report 0x18a1 (fewer than half of
   the guests bought, with the jump "_NACHRICHTEN_HS_82") or 0x18a2 (the guests, the takings); then moves the takings to
   lastTakings and clears the round's counters (field deltas) */
void he_InnReport(void) {
  AIBLD *b;
  unsigned short owner;
  int none, noneW, guests, served;
  char buf1[512], buf2[512];

  for (b = gm_BuildQuery(1, 5, 0x16); b != 0; b = gm_BuildNext()) {
    owner = b->owner;
    if (owner != 0xffff && (b->flags5a & 1) == 0) {
      none = 0;
      noneW = 0;
      if ((ai_Chars[owner].kind == 6 || ai_Chars[owner].kind == 7) &&
          b->inn.guests > 0) {
        served = b->inn.served;
        guests = b->inn.guests;
        if ((double)served / guests < 0.5) {
          txt_Format(buf1, 0x18a1, b, guests, b->inn.takings);
          he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, buf1, 0, 0x5fc,
                                 b->id, -1, 0, "_NACHRICHTEN_HS_82");
        } else {
          txt_Format(buf2, 0x18a2, b, guests, b->inn.takings);
          he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, buf2, 0, 0x5fc,
                                 b->id, -1, 0, ch_EmptyName);
        }
      }
      cm_BeginFieldBlock(b, b->id);
      cm_AddFieldDelta(4, 1, (char *)&b->inn.lastTakings - cm_FieldObject,
                       &b->inn.takings);
      cm_AddFieldDelta(4, 1, (char *)&b->inn.takings - cm_FieldObject, &none);
      cm_AddFieldDelta(2, 1, (char *)&b->inn.served - cm_FieldObject, &noneW);
      cm_AddFieldDelta(2, 1, (char *)&b->inn.guests - cm_FieldObject, &noneW);
      cm_SendFieldDeltas();
    }
  }
}
/* 0x540fe0, the daily event checks */

void he_DailyEventChecks(void) {
  he_PostEvent2b();
  he_PostPlayerEvents86a2();
  he_PostEvent67();
  he_ClearInnDarkCorner();
  he_InnStaffLeave();
  he_InnReport();
  he_PostWorkshopEvents98();
}
/* 0x541010, posts the message 0x3a (from -1, flag 1) to the player's character */

void he_PostEvent3a(void) {
  AIMSG m;

  m.type = 0x3a;
  m.fromId = -1;
  m.flags = 1;
  m.to = ai_Chars[ai_PlayerId].netId;
  cm_SendLongMessage(&m);
}
/* 0x541060, posts the message 0x3b (now, from -1, flag 1) to the player's character, after freeing a running event 0x3b */

void he_PostEvent3b(void) {
  AIMSG m;
  AIJOB *ev;

  ev = he_FindEvent(1, 0, 0x3b);
  if (ev != 0)
    he_FreeEvent(ev);
  m.type = 0x3b;
  m.fromId = -1;
  m.flags = 1;
  m.to = ai_Chars[ai_PlayerId].netId;
  m.time = ai_Time;
  cm_SendLongMessage(&m);
}
/* 0x5410f0, posts the event 0x73 to the player character (its netId), from -1, flag 1, at the current ai_Time;
   replaces a running event 0x73 first */

void he_PostEvent73(void) {
  AIMSG m;
  AIJOB *r;

  r = he_FindEvent(1, 0, 0x73);
  if (r != 0)
    he_FreeEvent(r);
  m.type = 0x73;
  m.to = ai_PlayerChar->netId;
  m.fromId = -1;
  m.flags = 1;
  m.time = ai_Time;
  cm_SendLongMessage(&m);
}
/* 0x541170, posts the message 0xa6 (now, from -1, flag 1) to the player's character, after freeing a running event 0xa6 */

void he_PostEventA6(void) {
  AIMSG m;
  AIJOB *ev;

  ev = he_FindEvent(1, 0, 0xa6);
  if (ev != 0)
    he_FreeEvent(ev);
  m.type = 0xa6;
  m.fromId = -1;
  m.flags = 1;
  m.to = ai_Chars[ai_PlayerId].netId;
  m.time = ai_Time;
  cm_SendLongMessage(&m);
}
/* 0x541200, sets the end clock (AIJOB.end) of the event record to ai_Time and posts it again when its opts bit 2
   (post when due) is set */

void he_EndEventNow(AIJOB *r) {
  r->end = ai_Time;
  if ((r->opts & 2) != 0)
    cm_SendExSetHE(-1, r);
}
/* 0x541250, sets the character slot (AIJOB.chr, +0x8) of the event record and its netId (+0xc), -1 for 0xffff */

void he_SetEventChar(AIJOB *e, int pl) {

  e->chr = (unsigned short)pl;
  if (pl != 0xffff) {
    e->netId = ai_Chars[pl].netId;
    return;
  }
  e->netId = -1;
}

void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c, struct AIJOB *g);

/* 0x541280, the idle behaviour of the event's characters (ids[], 8 of them) in the default scene: each one whose scene
   character has no queued action either walks to 1 .. 3 points near pos (rd_PointsNear, actions 0x2d tagged
   "he_CharacterBehavior"; 41 of 100) or plays one of three gestures twice, each 1 .. 3 times */
void he_CharacterBehavior(AIJOB *ev, D3VECTOR *pos) {
  int *id;
  int k, n;
  AICHAR *c;
  struct D3SM *h;
  int px, pz;
  float py;
  D3VECTOR4 *p;
  CHACTION *act;

  if (d3_CurrentScene == 0) {
    for (id = ev->ids, k = 8; k != 0; k--, id++) {
      if (*id != -1 && (c = gm_FindChar(*id)) != 0 && c->scene->actions == 0) {
        if (util_Random(100) > 40) {
          char gest[3][0x20] = {"gestik/durch_haar_fahr", "gestik/kopf_kratzen",
                                "gestik/mit_faust_droh"};

          ch_QueueAnim(c->scene, gest[util_Random(3)], util_Random(3) + 1);
          ch_QueueAnim(c->scene, gest[util_Random(3)], util_Random(3) + 1);
        } else {
          D3VECTOR4 pts[8];

          h = d3_DefaultScene->hmap;
          n = util_Random(3) + 1;
          n = rd_PointsNear(pos, n, pts);
          if (n > 0) {
            for (p = pts; n != 0; n--, p++) {
              if (d3_GetHeightAt(h, &p->v, &px, &pz, &py)) {
                act = ch_AddAction(c->scene, 0x2d, px, pz, 0);
                strcpy(act->why, "he_CharacterBehavior");
              }
            }
          }
        }
      }
    }
  }
}
/* 0x5414a0, the accident of the character c at its workplace bld (the accident simulation he_RunAccidentSim rolls it):
   for value <= 0 it dies (its script stopped, the death message 0x71 posted, from the event ev's character or
   else the boss), and a playing boss (kind 6 / 7) gets the news 0x1bb0, or 0x414a for a kind 0x14 character,
   unless quiet; for a value below half its base health with a place to carry it to (he_FindFigurePlace) it is
   carried there ("Unfall") and the boss gets the news 0x1baf; else the boss gets 0x1bae, or 0x4149 for kind 0x14.
   value: the float the simulation rolls (reasoned guess: what is left of the character after the accident) */

void he_CharAccident(AIJOB *ev, AICHAR *c, AICHAR *boss, AIBLD *bld,
                     float value, int quiet) {
  AIMSG m;
  char buf[0x800];
  int place, obj;
  float half;

  if (value <= 0.0f) {
    sv_MoveToGroup(0, 0, c->id, 0);
    if (c->scene != 0 && c->scene->scriptId != -1)
      evt_Stop(evt_FindById(c->scene->scriptId));
    memset(&m, 0, sizeof(m));
    m.type = 0x71;
    if (ev != 0)
      m.to = ai_Chars[ev->chr].netId;
    else
      m.to = boss->netId;
    m.fromId = -1;
    m.time = ai_Time;
    m.flags = 2;
    m.arg[0] = c->netId;
    cm_SendLongMessage(&m);
    if (boss->kind != 6 && boss->kind != 7)
      return;
    if (quiet != 0)
      return;
    if (c->kind == 0x14) {
      txt_Format(buf, 0x414a, c->id, bld);
      he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x60a, bld->id, -1,
                             0, "_NACHRICHTEN_FRIEDHOF_05");
      return;
    }
    txt_Format(buf, 0x1bb0, c->id, bld);
    he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x60a, bld->id, -1, 0,
                           "_NACHRICHTEN_HS_62");
    return;
  }
  half = gm_CharacterBaseHealth(c) * 0.5f;
  if (value < half && he_FindFigurePlace(c, &place, &obj, 0) != 0 &&
      c->scene != 0) {
    sv_MoveToGroup(0, 0, c->id, 0);
    if (c->scene->scriptId != -1)
      evt_Stop(evt_FindById(c->scene->scriptId));
    cm_SendSetField(c->netId, 0x1c8, 4, 0x800, 0);
    if (obj == -1)
      cm_SendChrGotoBuilding(c->netId, place, obj, 0, 1, "Unfall");
    else
      cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0, "Unfall");
    if (boss->kind != 6 && boss->kind != 7)
      return;
    txt_Format(buf, 0x1baf, c->id, bld);
    he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x60a, bld->id, -1, 0,
                           "_NACHRICHTEN_HS_61");
    return;
  }
  if (boss->kind != 6 && boss->kind != 7)
    return;
  if (c->kind == 0x14) {
    txt_Format(buf, 0x4149, c->id, bld);
    he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x60a, bld->id, -1, 0,
                           "_NACHRICHTEN_FRIEDHOF_04");
    return;
  }
  txt_Format(buf, 0x1bae, c->id, bld);
  he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x60a, bld->id, -1, 0,
                         "_NACHRICHTEN_HS_61");
}
/* 0x5417d0, the illness of the character c at the workplace bld (the callers roll it: gm_CatchDisease's disease
   and value, the plague): for value <= 0 a playing boss (kind 6 / 7) gets the news 0x1632 and the death message
   0x71 is posted (to the event ev's character, else the boss); for a value below half its base health with a place
   to carry it to (he_FindFigurePlace) it is carried there ("Unfall") and the boss gets the news 0x1631, else
   0x1630; both name the disease (text 0x1626 + disease) */

void he_CharIllness(AIJOB *ev, AICHAR *c, AICHAR *boss, AIBLD *bld, int disease,
                    float value) {
  AIMSG m;
  char buf[0x800];
  int place, obj;
  float half;

  if (value <= 0.0f) {
    if (boss->kind == 6 || boss->kind == 7) {
      txt_Format(buf, 0x1632, c->id, bld);
      he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x5ed, bld->id, -1,
                             0, 0);
    }
    memset(&m, 0, sizeof(m));
    m.type = 0x71;
    if (ev != 0)
      m.to = ai_Chars[ev->chr].netId;
    else
      m.to = boss->netId;
    m.fromId = -1;
    m.time = ai_Time;
    m.flags = 2;
    m.arg[0] = c->netId;
    cm_SendLongMessage(&m);
    return;
  }
  half = gm_CharacterBaseHealth(c) * 0.5f;
  if (value < half && he_FindFigurePlace(c, &place, &obj, 0) != 0 &&
      c->scene != 0) {
    sv_MoveToGroup(0, 0, c->id, 0);
    if (c->scene->scriptId != -1)
      evt_Stop(evt_FindById(c->scene->scriptId));
    if (obj == -1)
      cm_SendChrGotoBuilding(c->netId, place, obj, 0, 1, "Unfall");
    else
      cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0, "Unfall");
    if (boss->kind != 6 && boss->kind != 7)
      return;
    txt_Format(buf, 0x1631, c->id, bld, disease + 0x1626);
    he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x5ed, bld->id, -1, 0,
                           0);
    return;
  }
  if (boss->kind != 6 && boss->kind != 7)
    return;
  txt_Format(buf, 0x1630, c->id, bld, disease + 0x1626);
  he_MessageBoxQuickjump(boss->netId, bld->id, buf, 0, 0x5ed, bld->id, -1, 0,
                         0);
}
/* 0x541a50, the run handler of the event types 0x29 / 0x2f / 0x25: sets the event's end clock (AIJOB.end) to
   ai_Time, so it is due at once */

void he_RunDueNow(AIJOB *ev) { ev->end = ai_Time; }
/* 0x541a80, the alloc handler of the inn meeting event 0x2a (when opts bit 4 is clear): due now + 1, the meeting
   clock (+0xb0) now + 0x18 units with its minutes cleared and a random hour 0x13 .. 0x16, state 1, posts it and
   keeps the cm slot (+0x84) */

void he_AllocStammtisch(AIJOB *e) {
  AIJOB *m = e;
  short s;

  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    m->innMeeting = ai_Time;
    gm_AddTime(&m->innMeeting, 0x18, 0, 0);
    m->innMeeting.min = 0;
    s = util_Random(4);
    m->innMeeting.hour = s + 0x13;
    m->innState = 1;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}

void ai_ShowTributeDelayedNews(struct AICHAR *param_1);
void ai_ShowTributeCollectNews(struct AICHAR *param_1);
void ai_ShowTributeClaimNews(struct AICHAR *param_1, struct AICHAR *param_2);

/* 0x541b40, the inn meeting ("Stammtisch", see 0x53f430) hears of a table request (cm_ExTableRequest) or of its
   own run (he_RunStammtisch): `cmd` is a four letter code, inn the inn building, table its table object (kind 0x12d,
   the four seats), figId the character who joins / leaves. It tells the seated players and the inn's owner (boss)
   the news 0x1893 .. 0x189d: 'join' (with a full table now), 'leav' (the last one gone; a table that was full tells
   every other player too), 'cler' (cleared), 'new ' (a new meeting, to every player but the owner), and 'exec'
   (the meeting is held: every member pays the owner the price of the goods 0x179 + 0x17a, and all the members and
   the owner rise in each other's relations) */
void he_StammtischCommand(unsigned cmd, AIBLD *inn, AIOBJ *table, int figId) {
  AICHAR *boss;
  int n;
  int total;
  AICHAR *mem[4];
  char big[0x400];
  AICHAR *fig, *pm, *c;
  int *seat;
  int i, j, k, amt;

  n = 0;
  boss = &ai_Chars[inn->owner];
  seat = table->seats;
  for (i = 4; i != 0; i--, seat++) {
    pm = gm_FindChar(*seat);
    if (pm != 0)
      mem[n++] = pm;
  }
  switch (cmd) {
  case 'exec':
    amt = (int)(gm_GoodsPrice(0x17a, ai_OwnPlayer) +
                gm_GoodsPrice(0x179, ai_OwnPlayer));
    total = 0;
    txt_Format(big, 0x189a, inn, amt);
    for (j = 0; j < n; j++) {
      pm = mem[j];
      cm_SendMoveGoodsUnchecked(boss->netId, pm->netId, ai_OwnPlayer, amt);
      total += amt;
      if (pm->kind == 6 || pm->kind == 7)
        he_MessageBoxQuickjump(pm->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                               ch_EmptyName);
      cm_SendRelations(boss->netId, pm->netId, 3, 1);
      cm_SendRelations(pm->netId, boss->netId, 3, 1);
    }
    if (boss->kind == 6 || boss->kind == 7) {
      txt_Format(big, 0x1893, inn, total);
      he_MessageBoxQuickjump(boss->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                             ch_EmptyName);
    }
    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        if (i != j) {
          cm_SendRelations(mem[i]->netId, mem[j]->netId, 3, 1);
          cm_SendRelations(mem[j]->netId, mem[i]->netId, 3, 1);
        }
      }
    }
    break;
  case 'cler':
    txt_Format(big, 0x189d, inn);
    for (j = 0; j < n; j++) {
      if (mem[j]->kind == 6 || mem[j]->kind == 7)
        he_MessageBoxQuickjump(mem[j]->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                               ch_EmptyName);
    }
    break;
  case 'join':
    fig = gm_FindChar(figId);
    if (fig == 0)
      break;
    txt_Format(big, 0x189b, inn, fig->id);
    for (j = 0; j < n; j++) {
      if (mem[j]->kind == 6 || mem[j]->kind == 7)
        he_MessageBoxQuickjump(mem[j]->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                               ch_EmptyName);
    }
    if (boss->kind == 6 || boss->kind == 7) {
      if (++n == 4) {
        char s1[0x100];
        char s2[0x100];

        txt_Format(s1, 0x1894, inn, fig->id);
        txt_Format(s2, 0x1896);
        txt_Format(big, (intptr_t)"%s%s", s1, s2);
      } else {
        txt_Format(big, 0x1894, inn, fig->id);
      }
      he_MessageBoxQuickjump(boss->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                             ch_EmptyName);
    }
    break;
  case 'leav':
    fig = gm_FindChar(figId);
    if (fig == 0)
      break;
    txt_Format(big, 0x189c, inn, fig->id);
    for (j = 0; j < n; j++) {
      if ((mem[j]->kind == 6 || mem[j]->kind == 7) &&
          mem[j]->netId != fig->netId)
        he_MessageBoxQuickjump(mem[j]->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                               ch_EmptyName);
    }
    if (boss->kind == 6 || boss->kind == 7) {
      if (n - 1 == 0) {
        char s1[0x100];
        char s2[0x100];

        txt_Format(s1, 0x1895, inn, fig->id);
        txt_Format(s2, 0x1897);
        txt_Format(big, (intptr_t)"%s%s", s1, s2);
      } else {
        txt_Format(big, 0x1895, inn, fig->id);
      }
      he_MessageBoxQuickjump(boss->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                             ch_EmptyName);
    }
    if (n == 4) {
      txt_Format(big, 0x1899, inn);
      for (i = 0; i < 768; i++) {
        c = &ai_Chars[i];
        if ((c->kind == 6 || c->kind == 7) && c->netId != boss->netId) {
          for (k = 0; k < 4; k++) {
            if (c->netId == mem[k]->netId)
              break;
          }
          if (k < 4)
            he_MessageBoxQuickjump(c->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                                   ch_EmptyName);
        }
      }
    }
    break;
  case 'new ':
    txt_Format(big, 0x1898, inn);
    for (i = 0; i < 768; i++) {
      c = &ai_Chars[i];
      if ((c->kind == 6 || c->kind == 7) && c->netId != boss->netId)
        he_MessageBoxQuickjump(c->netId, -1, big, 0, 0x5ec, inn->id, -1, 0,
                               ch_EmptyName);
    }
    break;
  }
}
/* 0x542100, the run handler of the inn meeting event 0x2a ("Stammtisch", he_AllocStammtisch; its scripts
   he_StammtischCommand): the inn (innId) must have its table object 0x12d, else it waits 5 minutes. With an inn owner
   who is alive, not the player and not of kind 0xf: in state 1 the meeting is announced ('new ', the state counted
   down), else when the meeting time has come it is held ('exec') (before that it waits an hour); either way the next
   meeting is planned a day ahead at a random hour 0x13 .. 0x16. Without such an owner the table is cleared once
   ('cler' request, the state raised) and the meeting planned again
   @deep deep s35: two hunks, both in the boss / state == 1 arm. (1) the original decrements m->innState in
   edi (mov edi,[esi+0xc0]; dec edi; store; edi held the -1 constant until the 'new ' call), ours in eax: a
   candidate, not a temp; m->innState = m->innState - 1, --m->innState, a named st local (function or block scope)
   are all = control (single-use locals fold); the dec after e->end = ai_Time is worse (M8). (2) the shared
   tail at the meeting gm_AddTime call: the original merges add esp to one 0x3c after cm_SendExSetHE with
   push 4 before the min store, ours add esp,0x30 after the call. min / hour swapped in the arm: worse
   (21/245), both copies 23. The e->end / meeting code once after the if / else: 193. climb round 1 and
   initgen (bld, table, boss): nothing. */
void he_RunStammtisch(AIJOB *e) {
  AIJOB *m = e;
  AIBLD *bld;
  AIOBJ *table;
  AICHAR *boss;
  G17TABLEMSG cmd;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  gm_FindById(&bld, 0, 0, m->innInnId);
  if (bld == 0) {
    gm_AddTime(&e->end, 0, 5, 0);
    cm_SendExSetHE(-1, e);
    return;
  }
  table = gm_Query(bld->objList, 2, 6, 0, 0x12d);
  if (table == 0) {
    gm_AddTime(&e->end, 0, 5, 0);
    cm_SendExSetHE(-1, e);
    return;
  }
  if (bld->owner != 0xffff && (boss = &ai_Chars[bld->owner]) != 0 &&
      boss != ai_PlayerChar && boss->health != 0 && boss->kind != 0xf) {
    if (m->innState == 1) {
      he_StammtischCommand('new ', bld, table, -1);
      m->innState--;
      e->end = ai_Time;
      gm_AddTime(&e->end, 1, 0, 0);
      m->innMeeting = ai_Time;
      gm_AddTime(&m->innMeeting, 0x18, 0, 0);
    } else {
      if (gm_MinutesBetween(&ai_Time, &m->innMeeting) > 0) {
        gm_AddTime(&e->end, 1, 0, 0);
        cm_SendExSetHE(0, e);
        return;
      }
      he_StammtischCommand('exec', bld, table, -1);
      e->end = ai_Time;
      gm_AddTime(&e->end, 1, 0, 0);
      m->innMeeting = ai_Time;
      gm_AddTime(&m->innMeeting, 0x18, 0, 0);
    }
    m->innMeeting.min = 0;
    m->innMeeting.hour = util_Random(4) + 0x13;
    cm_SendExSetHE(0, e);
    return;
  }
  if (m->innState == 0) {
    cmd.op = 'cler';
    cmd.charId = -1;
    cmd.bldId = bld->id;
    cm_BeginGroup("stammtisch clear HE");
    cm_SendTableRequest(&cmd);
    cm_EndGroup("stammtisch clear HE");
    m->innState++;
  }
  e->end = ai_Time;
  gm_AddTime(&e->end, 1, 0, 0);
  m->innMeeting = ai_Time;
  gm_AddTime(&m->innMeeting, 0x18, 0, 0);
  m->innMeeting.min = 0;
  m->innMeeting.hour = util_Random(4) + 0x13;
  cm_SendExSetHE(0, e);
}
/* 0x542490, a Ghidra miss (disassembled): the event of the building `from`: sets its end clock to a day ahead at 7:00;
   with the building gone it is posted again (key -1), else a building without an object of kind 0x1b5 gets one
   (cm_SendObject1b5, its value all -1) and the event is posted (key 0) */
void he_AllocTavern(AIJOB *e) {
  AIBLD *bld = 0;
  G17B7 v;

  if ((e->opts & 4) != 0)
    return;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->end.hour = 7;
  e->end.min = 0;
  gm_FindById(&bld, 0, 0, e->from);
  if (bld == 0) {
    cm_SendExSetHE(-1, e);
    return;
  }
  if (gm_Query(bld->objList, 1, 0, 0x1b5) == 0) {
    v.sermon.text1 = -1;
    v.sermon.text2 = -1;
    v.sermon.priest = -1;
    cm_SendObject1b5(bld->id, v);
  }
  e->exSlot = -1;
  cm_SendExSetHE(0, e);
}

void ai_ShowTavernHelperNews(struct AICHAR *param_1, struct AICHAR *param_2,
                             int param_3);

/* 0x542590, a Ghidra miss (disassembled): the run handler of the tavern event 0x2b of the building `from` (no owner:
   again in a day at 7:00). Stage 0: an AI owner may hire a helper (ai_ChooseObjectTarget on the tavern's object
   0x1b5), a player's helper is hired when the object says so (hired): then stage 1 in an hour, else again in a day.
   Stage 1 waits 1 .. 2 hours. Stage 2: the hired helper is done: its news (ai_ShowTavernHelperNews), the object is
   reset (no helper), and when the tavern pays out (gm_HandOutMoney) its owner gets the takings (the news 0x19a7 for a
   player) and the building's field 0x69 the amount; again in a day at 7:00 */
void he_RunTavern(AIJOB *e) {
  AIBLD *bld = 0;
  AIOBJ *t;
  AICHAR *helper;
  char buf[0x100];

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  gm_FindById(&bld, 0, 0, e->from);
  if (bld == 0) {
    cm_SendExSetHE(-1, e);
    return;
  }
  if (bld->owner == 0xffff) {
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 7;
    cm_SendExSetHE(0, e);
    return;
  }
  t = gm_Query(bld->objList, 1, 0, 0x1b5);
  switch (e->stage) {
  case 0:
    if (ai_Chars[bld->owner].kind == 6 || ai_Chars[bld->owner].kind == 7) {
      if (t != 0 && t->sermon.enabled != 0) {
        gm_AddTime(&e->end, 1, 0, 0);
        e->exSlot = cm_SendExSetHE(1, e);
      } else {
        gm_AddTime(&e->end, 0x18, 0, 0);
        e->end.hour = 7;
        e->exSlot = cm_SendExSetHE(0, e);
      }
    } else {
      if (t != 0) {
        if (ai_ChooseObjectTarget(&ai_Chars[bld->owner], t) != 0) {
          gm_AddTime(&e->end, 1, 0, 0);
          e->exSlot = cm_SendExSetHE(1, e);
        } else {
          gm_AddTime(&e->end, 0x18, 0, 0);
          e->end.hour = 7;
          e->exSlot = cm_SendExSetHE(0, e);
        }
      } else {
        gm_AddTime(&e->end, 0x18, 0, 0);
        e->end.hour = 7;
        e->exSlot = cm_SendExSetHE(0, e);
      }
    }
    return;
  case 1:
    gm_AddTime(&e->end, util_Random(2) + 1, 0, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 2:
    if (t != 0 && t->sermon.enabled != 0) {
      GMHANDOUT out;
      unsigned char no, none;
      int noId;

      no = 0;
      none = 0xff;
      noId = -1;
      out.partner = 0;
      helper = gm_FindChar(t->sermon.priest);
      if (helper != 0) {
        out.partner = helper;
        ai_ShowTavernHelperNews(&ai_Chars[bld->owner], helper, (int)bld);
      }
      cm_BeginFieldBlock(t, t->objId);
      cm_AddFieldDelta(1, 1, 0x22, &no);
      cm_AddFieldDelta(1, 1, 0x1c, &none);
      cm_AddFieldDelta(1, 1, 0x1d, &none);
      cm_AddFieldDelta(4, 1, 0x1e, &noId);
      cm_SendFieldDeltas();
      if (gm_HandOutMoney(bld, &out) != 0) {
        if (ai_Chars[bld->owner].kind == 6 || ai_Chars[bld->owner].kind == 7) {
          txt_Format(buf, 0x19a7, out.count, out.sum);
          he_ShowNews(ai_Chars[bld->owner].netId, -1, buf, 0, 0x5ff,
                      ch_EmptyName);
        }
        cm_SendMoveGoods(ai_Chars[bld->owner].netId, -1, ai_OwnPlayer, out.sum);
        cm_BeginFieldBlock(bld, bld->id);
        cm_AddFieldDelta(4, 1, 0x69, &out.sum);
        cm_SendFieldDeltas();
      }
    }
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 7;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x542960, the alloc handler of the offer event 0x2c between the figures partner1 (+0xac) and partner2 (+0xb0):
   sets the event's end clock to ai_Time and the offer clock (+0xc5) to now + 0x18 units, hour 0xa, minute 0; when
   opts bit 2 is set it walks the other pending 0x2c offers of the same kind: an offer of the same figure only
   shows the news 0x1bbe and re-posts this event at once, an older one of another figure moves our clock to its
   time; at the end the offer is created (cm_SendHandOverCrimes, +0xd4) and the event posted */
void he_AllocOffer(AIJOB *e) {
  AIJOB *o2;
  AICHAR *q, *p;
  AIJOB *r;
  unsigned char fl;
  char buf[0x100];

  q = gm_FindChar(e->offerWho[1]);
  p = gm_FindChar(e->offerWho[0]);
  e->offerAt.clock = ai_Time;
  gm_AddTime(&e->offerAt.clock, 0x18, 0, 0);
  e->offerAt.clock.hour = 0xa;
  e->offerAt.clock.min = 0;
  e->end = ai_Time;
  fl = e->opts;
  if ((fl & 2) != 0) {
    r = he_FindEvent(1, 0, 0x2c);
    while (r != 0) {
      o2 = r;
      if (o2->id != e->id && o2->offerAt.kind == e->offerAt.kind) {
        if (o2->offerWho[0] == e->offerWho[0]) {
          txt_Format(buf, 0x1bbe, p->id, q->id);
          he_ShowNews(p->netId, p->netId, buf, 0, 0x5f5, (char *)0);
          e->end = ai_Time;
          e->exSlot = cm_SendExSetHE(-1, e);
          return;
        }
        if (e->offerAt.clock.year <= o2->offerAt.clock.year) {
          e->offerAt.clock = o2->offerAt.clock;
          gm_AddTime(&e->offerAt.clock, 0x18, 0, 0);
          e->offerAt.clock.hour = 0xa;
          e->offerAt.clock.min = 0;
        }
      }
      r = he_NextEvent();
    }
    e->offerHandle =
        cm_SendHandOverCrimes(e->offerWho[0], e->offerWho[1], e->id, 1);
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x542b60, a Ghidra miss (disassembled): the run handler of the wedding offer event (see 0x542960; AIJOB.offer*). Stage 0
   waits for the answer to the offer (cm_GetSlotState of the offer handle: 1 accepted, 2 refused). Accepted: the end
   clock becomes the offer's clock, the partner and the suitor get the news 0x1bc0 / 0x1bbf ("_NACHRICHTEN_HS_16" /
   "_NACHRICHTEN_HS_15"), the guests who[3] / who[4] the news 0x1bc1 (HS_11) and who[2] / who[5] the news 0x1bc2
   (HS_12) when they are players, and the event goes on to stage 1. Refused: the suitor hears 0x1bbe and the event is
   posted again two minutes on. Stage 1 sends the wedding party (G28REC, kind 2, flags 0xa2, its 5 or 6 members, 45
   minutes from now, hosted by the player) and posts the event again */
void he_RunWeddingOffer(AIJOB *e) {
  AICHAR *partner, *suitor, *g2, *g3, *g4, *g5;
  char ok;
  G28REC m;
  char buf[0x200];

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    ok = cm_GetSlotState(e->offerHandle);
    if (ok == 0)
      return;
    partner = gm_FindChar(e->offerWho[1]);
    suitor = gm_FindChar(e->offerWho[0]);
    g2 = gm_FindChar(e->offerWho[2]);
    g3 = gm_FindChar(e->offerWho[3]);
    g4 = gm_FindChar(e->offerWho[4]);
    g5 = gm_FindChar(e->offerWho[5]);
    if (ok == 1) {
      e->end = e->offerAt.clock;
      if (partner->kind == 6 || partner->kind == 7) {
        txt_Format(buf, 0x1bc0, suitor->id, &e->end, e->end.hour, g2->id,
                   g3->id, g4->id);
        he_ShowNews(partner->netId, partner->netId, buf, 0, 0x5f5,
                    "_NACHRICHTEN_HS_16");
      }
      if (suitor->kind == 6 || partner->kind == 7) {
        txt_Format(buf, 0x1bbf, partner->id, &e->end, e->end.hour, g2->id,
                   g3->id, g4->id);
        he_ShowNews(suitor->netId, suitor->netId, buf, 1, 0x5f5,
                    "_NACHRICHTEN_HS_15");
      }
      txt_Format(buf, 0x1bc1, suitor->id, partner->id, &e->end, e->end.hour);
      if (g3->kind == 6 || g3->kind == 7)
        he_ShowNews(g3->netId, g3->netId, buf, 0, 0x5f5, "_NACHRICHTEN_HS_11");
      if (g4->kind == 6 || g4->kind == 7)
        he_ShowNews(g4->netId, g4->netId, buf, 0, 0x5f5, "_NACHRICHTEN_HS_11");
      txt_Format(buf, 0x1bc2, suitor->id, partner->id, &e->end, e->end.hour);
      if (g2->kind == 6 || g2->kind == 7)
        he_ShowNews(g2->netId, g2->netId, buf, 0, 0x5f5, "_NACHRICHTEN_HS_12");
      if (g5 != 0 && (g5->kind == 6 || g5->kind == 7))
        he_ShowNews(g5->netId, g5->netId, buf, 0, 0x5f5, "_NACHRICHTEN_HS_12");
      cm_SendExSetHE(1, e);
      return;
    }
    if (ok == 2) {
      if (suitor->kind == 6 || partner->kind == 7) {
        txt_Format(buf, 0x1bbe, partner->id);
        he_ShowNews(suitor->netId, suitor->netId, buf, 0, 0x5f5, 0);
      }
      e->end = ai_Time;
      e->end.min += 2;
      cm_SendExSetHE(-1, e);
    }
    return;
  case 1:
    memset(&m, 0, sizeof(m));
    m.offerKind = e->offerAt.kind;
    m.eventId = e->id;
    m.members[0] = e->offerWho[0];
    m.members[1] = e->offerWho[1];
    m.members[2] = e->offerWho[2];
    m.members[3] = e->offerWho[3];
    m.members[4] = e->offerWho[4];
    m.members[5] = e->offerWho[5];
    m.used = (e->offerWho[5] != -1) + 5;
    m.kind = 2;
    m.flags = 0xa2;
    m.thing = -1;
    m.host = ai_Chars[ai_PlayerId].netId;
    m.time = ai_Time;
    gm_AddTime(&m.time, 0, 0x2d, 0);
    cm_SendNewParty(&m);
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x543020, the alloc handler of the quarrel event 0x2e between the figures partner1 (+0xac) and partner2 (+0xb0):
   re-posts the event in 0x30 units, takes 0x14 relation points of partner2 towards partner1, tells partner1 (news
   0x175a) and reports the crime (gv_Accuse 0x13, 1, partner2, partner1) with the home building (AICHAR.bld2) id of
   partner2, else of partner1 */

void he_AllocQuarrel(AIJOB *e) {
  AICHAR *a, *b;
  AIBLD *t;
  int id;
  char buf[0x200];
  unsigned char fl;

  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  fl = e->opts;
  e->exSlot = -1;
  if ((fl & 2) != 0) {
    if (a == 0 || b == 0) {
      e->end = ai_Time;
      cm_SendExSetHE(-1, e);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x30, 0, 0);
    cm_SendExSetHE(0, e);
    cm_SendRelations(b->netId, a->netId, -20, 1);
    if (a->kind == 6 || a->kind == 7) {
      txt_Format(buf, 0x175a, b->id, b->id);
      he_ShowNews(a->netId, -1, buf, 0, 0x5fb, ch_EmptyName);
    }
    t = b->bld2;
    id = -1;
    if (t != 0) {
      id = t->id;
    } else {
      t = a->bld2;
      if (t != 0)
        id = t->id;
    }
    gv_Accuse(0x13, 1, e->partner2, e->partner1, id);
  }
}
/* 0x543180, the run handler of the quarrel event 0x2e: tells partner2 (news 0x175d, message 0x5fa) when its option 2
   is set, then re-posts the event in one unit (stage 0 only); a missing partner ends it at the current time */

void he_RunQuarrel(AIJOB *e) {
  AICHAR *a, *b;
  char buf[0x100];

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  if (b == 0 || a == 0) {
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (e->stage == 0) {
    if ((e->opts & 2) != 0) {
      txt_Format(buf, 0x175d, a->id);
      he_ShowNews(b->netId, -1, buf, 0, 0x5fa, (char *)0);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
  }
}
/* 0x5432f0, a Ghidra miss (disassembled): the run handler of the master exam event ("Meisterpruefung") of the three
   characters who[0] (the master), who[1] (the one told) and who[2] (the candidate); gone ones end it, and a candidate
   who is no player skips to stage 2. Stage 0 opens the window "Berufe\Messagebox_Meisterpruefung" (news 0x5ec) with
   the text 0x1763 and the voice "_NACHRICHTEN_HS_20", due in a day. Stage 1 waits for the answer in that window
   (d2_ClickedId 0: passed, 1: failed) or for the due time (then stage 2). Stage 2 decides by chance
   (gm_Mix(who[1], who[0], 4) + a random 0 .. 1 below 1: failed). Passed: who[1] hears 0x1764 and the master's
   relation to the candidate drops by 20; failed: 0x1765 and who[1] and the candidate drop by 15 each way */
void he_RunMasterExam(AIJOB *e) {
  AICHAR *p, *q, *r;
  float f;
  char buf[0x100];

  p = gm_FindChar(e->offerWho[0]);
  q = gm_FindChar(e->offerWho[1]);
  r = gm_FindChar(e->offerWho[2]);
  if (e->stage == -2 || p == 0 || q == 0 || r == 0) {
    he_FreeEvent(e);
    if (e->slot != 0)
      he_ReleaseSlot(e);
    return;
  }
  if (e->stage == -1 || (r->kind != 6 && r->kind != 7))
    e->stage = 2;
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_SetForm(e->slot->win, 0);
    io_PrintText(0x1763, q->id, p->id);
    e->start = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    snd_PlayVoice(-7, 0, "_NACHRICHTEN_HS_20", 0);
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_ReleaseSlot(e);
      e->stage = 2;
      return;
    }
    if (d2_ClickedForm != e->slot->win || d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      txt_Format(buf, 0x1764, r->id, p->id);
      he_ShowNews(q->netId, q->netId, buf, 0, 0x5fa, 0);
      cm_SendRelations(p->netId, r->netId, -20, 1);
    } else if (d2_ClickedId == 1) {
      txt_Format(buf, 0x1765, r->id, p->id);
      he_ShowNews(q->netId, q->netId, buf, 0, 0x5fa, 0);
      cm_SendRelations(q->netId, r->netId, -15, 1);
      cm_SendRelations(r->netId, q->netId, -15, 1);
    }
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  case 2:
    f = gm_Mix(q, p, 4);
    if (util_RandomF() + f >= 1.0f) {
      txt_Format(buf, 0x1764, r->id, p->id);
      he_ShowNews(q->netId, q->netId, buf, 0, 0x5fa, 0);
      cm_SendRelations(p->netId, r->netId, -20, 1);
    } else {
      txt_Format(buf, 0x1765, r->id, p->id);
      he_ShowNews(q->netId, q->netId, buf, 0, 0x5fa, 0);
      cm_SendRelations(q->netId, r->netId, -15, 1);
      cm_SendRelations(r->netId, q->netId, -15, 1);
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x5436a0, the alloc handler of the feast event 0x37 (its run handler he_RunFeast): stage 0, end clock in 0x18
   units, hour 0x14; with inviteGuests set every guest gets the invitation message 0x36 carrying the feast time and
   event id (flag 9 for the players, else 1), then the event is posted */

void he_AllocFeast(AIJOB *e) {
  AIMSG msg;
  AICHAR *c;
  int *pp;
  int k;
  unsigned char fl;

  fl = e->opts;
  e->stage = 0;
  if ((fl & 4) == 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 0x14;
    e->end.min = 0;
    if (e->inviteGuests == 1) {
      pp = e->festGuests;
      for (k = 4; k != 0; k--, pp++) {
        c = gm_FindChar(*pp);
        if (c != 0) {
          msg.type = 0x36;
          msg.to = c->netId;
          msg.fromId = -1;
          msg.arg[4] = 1;
          msg.inviteWhen = e->end;
          msg.arg[5] = e->id;
          if (c->kind == 6 || c->kind == 7)
            msg.flags = 9;
          else
            msg.flags = 1;
          cm_SendLongMessage(&msg);
        }
      }
    }
    cm_SendExSetHE(0, e);
  }
}

/* 0x5437c0, the run handler of the feast event: the host is the event's character, the guests and the menu /
   musician picks come from the feast table object (gm_Query kind 0x17) of the building e->from, or from the event's
   own words when it names no building; a building without a feast table only re-posts the event. Stage 0 has the
   feast evaluated (ai_EvalFest, sending its effects) and, when that returns 0 for a player host (kind 6 / 7), tells
   the host the news 0x5fd: the text 0x1787 with the cost, then one line 0x1788 per guest (0x178f + 3 * the guest's
   verdict + a random 0 .. 2); it re-posts the event, as stage 1 does. The original clears only the group's first
   4 bytes, and without a building it tests the guests of a null table (*(int *)0x1c ..) before it looks up the
   event's own guests: both kept */
void he_RunFeast(AIJOB *e) {
  AIBLD *bld = 0;
  AIOBJ *table = 0;
  AICHAR *c;
  int k, n, verdict;
  char text[0x800];
  char line[0x100];

  if (e->stage == -2 || e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  gm_FindById(&bld, 0, 0, e->from);
  if (bld != 0 && (table = gm_Query(bld->objList, 1, 0, 0x17)) == 0) {
    e->end = ai_Time;
    cm_SendExSetHE(-1, e);
    return;
  }
  switch (e->stage) {
  case 0: {
    AIGRP g;

    MEM_ZERO(&g, 4);
    n = 0;
    g.leader = &ai_Chars[e->chr];
    if (table != 0) {
      g.essen = table->festEssen;
      g.musik = table->festMusik;
      for (k = 0; k < 4; k++) {
        if (table->festGuests[k] != -1 &&
            (c = gm_FindChar(table->festGuests[k])) != 0)
          g.mem[n++].ch = c;
      }
    } else {
      g.essen = e->festEssen;
      g.musik = e->festMusik;
      for (k = 0; k < 4; k++) {
        if (table->festGuests[k] != -1 &&
            (c = gm_FindChar(e->festGuests[k])) != 0)
          g.mem[n++].ch = c;
      }
    }
    g.n = (unsigned char)n;
    if (ai_EvalFest(&g, 1) == 0 &&
        (g.leader->kind == 6 || g.leader->kind == 7)) {
      txt_Format(text, 0x1787, g.cost);
      for (k = 0; k < g.n; k++) {
        verdict = util_Random(3) + 0x178f +
                  g.mem[k].d * 3; /* the guest's verdict text */
        txt_Format(line, 0x1788, g.mem[k].ch->id, verdict);
        strcat(text, line);
      }
      he_ShowNews(g.leader->netId, -1, text, 0x20, 0x5fd, ch_EmptyName);
    }
    e->end = ai_Time;
    cm_SendExSetHE(-1, e);
    return;
  }
  case 1:
    e->end = ai_Time;
    cm_SendExSetHE(-1, e);
    return;
  }
}

/* 0x543ac0, a Ghidra miss (disassembled): the run handler of the master exam at a feast (kind 0x36). The examiner is
   the owner of the building e->from, the guests read from its feast table object (gm_Query kind 0x17), or (examAt 1)
   the host of the feast event examFeast (kind 0x37) with that event's guests; the candidate is the event's character,
   and one who is no player (kind 6 / 7) skips to stage 2. Stage 0 opens the window
   "Berufe\Messagebox_Meisterpruefung" (news 0x5ec) with the text 0x1770 / 0x1771 and the voice "_NACHRICHTEN_HS_28",
   due in a day. Stage 1 waits for the answer in that window (d2_ClickedId 0: passed, 1: failed) or for the due time
   (then stage 2); stage 2 decides by ai_MasterExamPassed. Passed: the examiner hears 0x1785; failed: the candidate
   leaves the feast's guests (the table's field, or the feast event re-posted) and the examiner hears 0x1786; either
   only while the candidate is a guest. The text 0x1771 reads the owner of a null building: kept as the original */
void he_RunFeastExam(AIJOB *e) {
  AIBLD *bld = 0;
  AIOBJ *table = 0;
  AIJOB *feast = 0;
  AICHAR *master, *cand;
  int i, none;
  char buf[0x200];

  if (e->stage == -1 || e->stage == -2) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  if (e->examAt == 0) {
    gm_FindById(&bld, 0, 0, e->from);
    if (bld == 0) {
      if (e->slot != 0)
        he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    table = gm_Query(bld->objList, 1, 0, 0x17);
    if (table == 0 || bld->owner == 0xffff) {
      if (e->slot != 0)
        he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    master = &ai_Chars[bld->owner];
    if (master == 0) {
      if (e->slot != 0)
        he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
  } else if (e->examAt == 1) {
    feast = he_FindEvent(2, 1, e->examFeast, 0, 0x37);
    if (feast == 0) {
      if (e->slot != 0)
        he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    master = &ai_Chars[feast->chr];
    if (master == 0) {
      if (e->slot != 0)
        he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
  } else {
    he_FreeEvent(e);
    return;
  }
  cand = &ai_Chars[e->chr];
  if (cand->kind != 6 && cand->kind != 7)
    e->stage = 2;
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_SetForm(e->slot->win, 0);
    if (e->examAt == 0)
      io_PrintText(0x1770, bld->owner, cand->id, e->examText, bld, master->id,
                   cand->id);
    else
      io_PrintText(0x1771, bld->owner, cand->id, e->examText, master->id,
                   cand->id);
    e->start = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    snd_PlayVoice(-7, 0, "_NACHRICHTEN_HS_28", 0);
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_ReleaseSlot(e);
      e->stage++;
      return;
    }
    if (d2_ClickedForm != e->slot->win)
      return;
    none = -1;
    if (d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      if (e->examAt == 0) {
        for (i = 0; i < 4; i++)
          if (table->festGuests[i] == cand->netId)
            break;
      } else {
        for (i = 0; i < 4; i++)
          if (feast->festGuests[i] == cand->netId)
            break;
      }
      if (i < 4) {
        txt_Format(buf, 0x1785, cand->id);
        he_ShowNews(master->netId, -1, buf, 0, 0x5ec, 0);
      }
    } else if (d2_ClickedId == 1) {
      if (e->examAt == 0) {
        for (i = 0; i < 4; i++)
          if (table->festGuests[i] == cand->netId) {
            cm_BeginFieldBlock(table, table->objId);
            cm_AddFieldDelta(4, 1, 0x1c + i * 4,
                             &none); /* table->festGuests[i] = -1 */
            cm_SendFieldDeltas();
            break;
          }
      } else {
        for (i = 0; i < 4; i++)
          if (feast->festGuests[i] == cand->netId) {
            feast->festGuests[i] = -1;
            cm_SendExSetHE(0, e);
            break;
          }
      }
      if (i < 4) {
        txt_Format(buf, 0x1786, cand->id);
        he_ShowNews(master->netId, -1, buf, 0, 0x5ec, 0);
      }
    }
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  case 2:
    if (ai_MasterExamPassed(master, cand) == 1) {
      if (e->examAt == 0) {
        for (i = 0; i < 4; i++)
          if (table->festGuests[i] == cand->netId)
            break;
      } else {
        for (i = 0; i < 4; i++)
          if (feast->festGuests[i] == cand->netId)
            break;
      }
      if (i < 4) {
        txt_Format(buf, 0x1785, cand->id);
        he_ShowNews(master->netId, -1, buf, 0, 0x5ec, 0);
      }
    } else {
      none = -1;
      if (e->examAt == 0) {
        for (i = 0; i < 4; i++)
          if (table->festGuests[i] == cand->netId) {
            cm_BeginFieldBlock(table, table->objId);
            cm_AddFieldDelta(4, 1, 0x1c + i * 4,
                             &none); /* table->festGuests[i] = -1 */
            cm_SendFieldDeltas();
            break;
          }
      } else {
        for (i = 0; i < 4; i++)
          if (feast->festGuests[i] == cand->netId) {
            feast->festGuests[i] = -1;
            cm_SendExSetHE(0, e);
            break;
          }
      }
      if (i < 4) {
        txt_Format(buf, 0x1786, cand->id);
        he_ShowNews(master->netId, -1, buf, 0, 0x5ec, 0);
      }
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x544070, a Ghidra miss (disassembled): the alloc handler of the tribute event 0x35, once it is started (opts bit 4
   clear). Without its collector (idbc) the event is re-posted; with more than four tribute events running it is
   re-posted and the event's character hears the delay (ai_ShowTributeDelayedNews). Else it runs from now to a day
   later (tributeEnd), the first round due in a minute; the character pays 1 (gm_SendMoneyDelta) and is accused
   (gv_Accuse 3, 1 with the collector and the character's home building), the round robin over all 0x300 characters
   starts at a random one with a random stride, and the character's skill 4 is kept. A collector holding the good
   0x15c re-posts it and tells of the claim (ai_ShowTributeClaimNews), else ai_ShowTributeCollectNews and the event is
   posted with key 0 */
void he_AllocTribute(AIJOB *e) {
  AICHAR *coll;
  int n = 0;

  if (e->opts & 4)
    return;
  coll = gm_FindChar(e->idbc);
  if (coll == 0) {
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (he_FindEvent(1, 0, 0x35) != 0) {
    do
      n++;
    while (he_NextEvent() != 0);
    if (n > 4) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      ai_ShowTributeDelayedNews(&ai_Chars[e->chr]);
      return;
    }
  }
  e->end = ai_Time;
  e->start = ai_Time;
  e->tributeEnd = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  gm_AddTime(&e->tributeEnd, 0x18, 0, 0);
  gm_SendMoneyDelta(ai_Chars[e->chr].netId, -1);
  gv_Accuse(3, 1, ai_Chars[e->chr].netId, e->idbc,
            ai_Chars[e->chr].bld2 != 0 ? ai_Chars[e->chr].bld2->id : -1);
  e->tributeNext = util_Random(0x300);
  e->tributeStride = ai_CharWalkSteps[util_Random(0x10)];
  e->tributeSkill = gm_GetSkill(&ai_Chars[e->chr], 4);
  e->tributeLeft = 0x300;
  if (ai_InventoryHas(coll, 0x15c) != 0) {
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(-1, e);
    ai_ShowTributeClaimNews(coll, &ai_Chars[e->chr]);
    return;
  }
  ai_ShowTributeCollectNews(coll);
  e->exSlot = cm_SendExSetHE(0, e);
}

/* ---- drafted out of address order (the big 0x53f6b0 / 0x541b40 / 0x5437c0 are still missing above this point; move the functions below into address order when those exist) ---- */

/* 0x544330, the run handler of the tribute event 0x35: ends it at stage -1 / -2; runs once started (opts bit 4
   clear) and once its last post is settled (exSlot -1 or cm_GetSlotState nonzero). Without its collector (idbc) it
   re-posts itself a minute later. Else one round visits up to 0x10 of the characters left (from tributeNext, stepping
   tributeStride mod 0x300): each living one (id not 0xffff, health above 0) of a kind below 10 other than the
   collector gets the relation change 1 - 10 * gm_Mix2(tributeSkill, its skill 4) from him, doubled while the
   event's character holds the good 0x2c5. While tributeEnd is later than now the next round is due in an hour,
   else the event is re-posted a minute later */
void he_RunTribute(AIJOB *ev) {
  AIJOB *e = ev;
  AICHAR *coll, *owner;
  int mul, left, next, i, delta;
  float f;

  coll = gm_FindChar(e->idbc);
  owner = gm_FindChar(e->netId);
  mul = 1;
  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(ev);
    return;
  }
  if ((e->opts & 4) || (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0))
    return;
  e->exSlot = -1;
  if (coll == 0) {
    gm_AddTime(&e->end, 0, 1, 0);
    cm_SendExSetHE(-1, ev);
    return;
  }
  if (owner != 0)
    mul = (ai_InventoryHas(owner, 0x2c5) != 0) + 1;
  left = e->tributeLeft;
  next = e->tributeNext;
  for (i = 0; left != 0 && i < 0x10;
       i++, left = --e->tributeLeft, next = (e->tributeStride + next) % 0x300) {
    if (ai_Chars[next].id != 0xffff && ai_Chars[next].netId != e->idbc &&
        ai_Chars[next].kind < 10 && ai_Chars[next].health > 0) {
      f = -gm_Mix2(e->tributeSkill, gm_GetSkill(&ai_Chars[next], 4));
      delta = (int)(f * 10.0f + 1.0f) * mul;
      cm_SendRelations(e->idbc, ai_Chars[next].netId, delta, 1);
    }
  }
  e->tributeNext = next;
  e->end = ai_Time;
  if (gm_CompareTime(&e->tributeEnd, &ai_Time) == 1) {
    gm_AddTime(&e->end, 1, 0, 0);
    return;
  }
  gm_AddTime(&e->end, 0, 1, 0);
  e->exSlot = cm_SendExSetHE(-1, ev);
}
/* 0x544550, draws the three picks of the pair event 0x41 for the partners a and b (its handlers 0x544630 /
   0x544840): twelve values from half a's level (gm_CharLevel) on, shuffled; the first three go to pairPick with the
   prices (pick + 1) * (a's worth + b's worth, each at least 32000) / 640 in pairPrice */
void he_DrawPairPicks(AIJOB *e, AICHAR *a, AICHAR *b) {
  int tab[12];
  int base, i, wa, wb;

  base = gm_CharLevel(a->id, 0) / 2;
  wa = gm_GetWorth(a->id) > 32000 ? gm_GetWorth(a->id) : 32000;
  wb = gm_GetWorth(b->id) > 32000 ? gm_GetWorth(b->id) : 32000;
  for (i = 0; i < 12; i++)
    tab[i] = i + base;
  gm_Shuffle(12, tab);
  for (i = 0; i < 3; i++) {
    e->pairPick[i] = (unsigned char)tab[i];
    e->pairPrice[i] = (int)((float)((unsigned char)tab[i] + 1) *
                            (float)(wa + wb) * 0.0015625f);
  }
}
/* 0x544630, the alloc handler of the courtship event 0x41, run when posted (opts bit 2): the partners partner1 and
   partner2 must exist and be of different sex, else it is re-posted two minutes later. Their relatives[0] links are
   cleared (sent as field deltas); while another courtship names partner1 as its partner2 it is re-posted two minutes
   later as well. Else its first round is due tomorrow at 8:00, the rounds start at 0 of 0x5c6620(partner1,
   partner2), the picks are drawn (he_DrawPairPicks) and it is posted with key 0 */
void he_AllocCourtship(AIJOB *e) {
  AICHAR *a, *b;
  AIJOB *r;

  e->stage = 0;
  if ((e->opts & 2) == 0)
    return;
  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  if (a == 0 || b == 0 || a->sex == b->sex) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (a->relatives[0] != -1) {
    int none = -1;

    cm_BeginFieldBlock(a, a->netId);
    cm_AddFieldDelta(4, 1, 0x5c, &none); /* a->relatives[0] = -1 */
    cm_SendFieldDeltas();
  }
  if (b->relatives[0] != -1) {
    int none = -1;

    cm_BeginFieldBlock(b, b->netId);
    cm_AddFieldDelta(4, 1, 0x5c, &none); /* b->relatives[0] = -1 */
    cm_SendFieldDeltas();
  }
  for (r = he_FindEvent(1, 0, 0x41); r != 0; r = he_NextEvent()) {
    if (r->partner2 == a->netId) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
  }
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->end.min = 0;
  e->stage = 0;
  e->pairRound = 0;
  e->end.hour = 8;
  e->pairRounds = (char)ai_CourtshipRounds(e->partner1, e->partner2);
  e->pairDrawn = 0;
  he_DrawPairPicks(e, a, b);
  e->pairDone = 0;
  e->exSlot = -1;
  cm_SendExSetHE(0, e);
}

unsigned int ai_MarriageTest(int param_1, int param_2);

/* 0x544840, a Ghidra miss (disassembled): the run handler of the courtship event 0x41 (see he_AllocCourtship) of
   partner1 (a) and partner2 (b), of different sex. Ending it (stage -1 / -2) after it was posted clears the flag
   0x40000 of the one partner left when the other is gone. While a partner is missing it is re-posted two minutes
   later; it waits for its last post to settle (exSlot). Stage 0 asks ai_MarriageTest: -0x405 / -0x406 tell a the
   refusal 0x42f6 / 0x42f7; -0x403 and 0 tell a player a (kind 6) how b's family stands (0x1ceb .., naming b's
   relatives[1] while alive and b no kind 5, else b); 1 recomputes the rounds (ai_CourtshipRounds) and counts one;
   once pairRound reaches pairRounds it is posted with key 1, else a player hears the rounds left (0x1cf3 / 0x1cf4),
   a kind 5 a counts 1 .. 2 rounds, others one by a chance of 1 in 4, and the next round is due tomorrow at 8:00 with
   new picks. Stage 1 links the partners (group "werbung": each other's relatives[0], b takes a's family w050, both
   get the flag 0x40000) and posts it with key 5. Stage 4 re-posts it. Stage 5: when they are each other's
   relatives[0], both relations go to 0x7f, a player or kind 5 a hears 0x1d31 and the partner of sex 1 gets f07c 1.1,
   b's reserved grave entry is ordered, and the wedding party (G28REC kind 6, flags 0xb2, two hours on, between 7 and
   22 o'clock) is sent with the event posted with key 4; else a player a hears the family text again */
void he_RunCourtship(AIJOB *e) {
  AICHAR *a, *b;
  unsigned int r;
  char news[0x200];
  char gave[0x200];

  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  if (e->stage == -1 || e->stage == -2) {
    if (e->opts & 2) {
      if (b != 0 && (b->flags1c8 & 0x40000) && a == 0)
        cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x40000);
      else if (a != 0 && (a->flags1c8 & 0x40000) && b == 0)
        cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x40000);
    }
    he_FreeEvent(e);
  } else {
    if (e->opts & 4)
      return;
    if (a == 0 || b == 0 || a->sex == b->sex) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
      return;
    e->exSlot = -1;
    switch (e->stage) {
    case 0:
      r = ai_MarriageTest(e->partner1, e->partner2);
      if (r == -0x405) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 2, 0);
        e->exSlot = cm_SendExSetHE(-1, e);
        txt_Format(gave, 0x42f6, b->id);
        he_ShowNews(a->netId, a->netId, gave, 1, 0x5f4, 0);
        return;
      }
      if (r == -0x406) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 2, 0);
        e->exSlot = cm_SendExSetHE(-1, e);
        txt_Format(gave, 0x42f7, b->id);
        he_ShowNews(a->netId, a->netId, gave, 1, 0x5f4, 0);
        return;
      }
      if (r == -0x400 || r == -0x401 || r == -0x402) {
        e->end = ai_Time;
        break;
      }
      if (r == -0x403) {
        if (a->kind == 6) {
          AICHAR *c1, *c2;
          char line[0x200];

          c1 = gm_FindChar(b->relatives[1]);
          c2 = gm_FindChar(b->relatives[0]);
          if (c1 != 0 && c1->health > 0 && b->kind != 5) {
            txt_Format(line, 0x1ceb, c1->id, a->id);
            txt_Format(line + strlen(line), 0x1cee);
            txt_Format(line + strlen(line), 0x1cf2, b->id);
            txt_Format(line + strlen(line), 0x1cef, c2->id);
            txt_Format(line + strlen(line), 0x1cf0, c1->id);
          } else {
            txt_Format(line, 0x1ceb, b->id, a->id);
            txt_Format(line + strlen(line), 0x1cee);
            txt_Format(line + strlen(line), 0x1cf1);
            txt_Format(line + strlen(line), 0x1cef, c2->id);
            txt_Format(line + strlen(line), 0x1cf0, b->id);
          }
          he_ShowNews(a->netId, a->netId, line, 1, 0x5f4, 0);
        }
        e->end = ai_Time;
        break;
      }
      if (r == 0) {
        if (a->kind == 6) {
          AICHAR *c1;
          char line[0x200];

          c1 = gm_FindChar(b->relatives[1]);
          if (c1 != 0 && c1->health > 0 && b->kind != 5) {
            txt_Format(line, 0x1ceb, c1->id, a->id);
            txt_Format(line + strlen(line), 0x1cec);
            txt_Format(line + strlen(line), 0x1cf2, b->id);
            txt_Format(line + strlen(line), 0x1ced);
            txt_Format(line + strlen(line), 0x1cf0, c1->id);
          } else {
            txt_Format(line, 0x1ceb, b->id, a->id);
            txt_Format(line + strlen(line), 0x1cec);
            txt_Format(line + strlen(line), 0x1cf1);
            txt_Format(line + strlen(line), 0x1ced);
            txt_Format(line + strlen(line), 0x1cf0, b->id);
          }
          he_ShowNews(a->netId, a->netId, line, 1, 0x5f4, 0);
        }
        e->end = ai_Time;
        break;
      }
      if (r == 1) {
        e->pairRounds = (char)ai_CourtshipRounds(e->partner1, e->partner2);
        e->pairRound++;
      }
      if (e->pairRound >= e->pairRounds) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 2, 0);
        e->exSlot = cm_SendExSetHE(1, e);
        return;
      }
      if (a->kind == 6) {
        char line[0x200];

        txt_Format(line, 0x1cf3);
        txt_Format(line + strlen(line), 0x1cf4, b->id, 0x5d,
                   e->pairRounds - e->pairRound, 0x5d);
        he_ShowNews(a->netId, a->netId, line, 0, 0x5f4, 0);
      } else if (a->kind == 5) {
        e->pairRound += (char)util_Random(2) + 1;
      } else if ((short)util_Random(4) == 0) {
        e->pairRound++;
      }
      e->end = ai_Time;
      gm_AddTime(&e->end, 0x18, 0, 0);
      e->end.hour = 8;
      e->pairDrawn = 1;
      he_DrawPairPicks(e, a, b);
      e->exSlot = -1;
      cm_SendExSetHE(0, e);
      return;
    case 1:
      cm_BeginGroup("werbung");
      cm_BeginFieldBlock(b, b->netId);
      cm_AddFieldDelta(4, 1, 0x5c, &a->netId); /* b->relatives[0] = a->netId */
      cm_AddFieldDelta(2, 1, 0x50, &a->w050);  /* b->w050 = a->w050 */
      cm_SendFieldDeltas();
      cm_BeginFieldBlock(a, a->netId);
      cm_AddFieldDelta(4, 1, 0x5c, &b->netId); /* a->relatives[0] = b->netId */
      cm_SendFieldDeltas();
      cm_SendSetField(b->netId, 0x1c8, 4, 0x40000, 0);
      cm_SendSetField(a->netId, 0x1c8, 4, 0x40000, 0);
      cm_EndGroup("werbung");
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(5, e);
      return;
    case 5:
      /* each other's relatives[0]: the original tests both, bitwise (and edx, eax; test dl, 1) */
      if (!((a->relatives[0] == b->netId) & (b->relatives[0] == a->netId) &
            1)) {
        if (a->kind == 6) {
          AICHAR *c1, *c2;
          char line[0x200];

          c1 = gm_FindChar(b->relatives[1]);
          c2 = gm_FindChar(b->relatives[0]);
          if (c1 != 0 && c1->health > 0 && b->kind != 5) {
            txt_Format(line, 0x1ceb, c1->id, a->id);
            txt_Format(line + strlen(line), 0x1cee);
            txt_Format(line + strlen(line), 0x1cf2, b->id);
            txt_Format(line + strlen(line), 0x1cef, c2->id);
            txt_Format(line + strlen(line), 0x1cf0, c1->id);
          } else {
            txt_Format(line, 0x1ceb, b->id, a->id);
            txt_Format(line + strlen(line), 0x1cee);
            txt_Format(line + strlen(line), 0x1cf1, b->id);
            txt_Format(line + strlen(line), 0x1cef, c2->id);
            txt_Format(line + strlen(line), 0x1cf0, b->id);
          }
          he_ShowNews(a->netId, a->netId, line, 1, 0x5f4, 0);
        }
        e->end = ai_Time;
        break;
      }
      {
        AICHAR *who;
        AIBLD *yard;
        GVENTRY *entry;
        G28REC party;

        cm_SendRelations(a->netId, b->netId, 0x7f - ai_Relations[a->id][b->id],
                         1);
        cm_SendRelations(b->netId, a->netId, 0x7f - ai_Relations[b->id][a->id],
                         1);
        if (a->kind == 6 || a->kind == 5) {
          who = a;
          if (a->sex != 1)
            who = b;
          txt_Format(news, 0x1d31, b->id);
          he_ShowNews(a->netId, a->netId, news, 0, 0x5f4, 0);
          cm_SendFloatDelta(who->netId, 0x7c, 1.1f - who->pregnancy);
        }
        if (gv_FindReservedEntry(b, &yard, &entry) != 0)
          gv_OrderSetGraveHolder(0, yard, entry->size,
                                 gv_EntryIndex(yard->yard, entry));
        MEM_ZERO(&party, sizeof(party));
        party.members[0] = a->netId;
        party.members[1] = b->netId;
        party.host = ai_Chars[ai_PlayerId].netId;
        party.kind = 6;
        party.flags = 0xb2;
        party.thing = -1;
        party.used = 2;
        party.time = ai_Time;
        gm_AddTime(&party.time, 2, 0, 0);
        party.time.min = 0;
        if (party.time.hour > 0x16) {
          party.time.year++;
          party.time.hour = 0xb;
        } else if (party.time.hour < 7) {
          party.time.hour = 0xb;
        }
        e->end = party.time;
        e->pairDone = 1;
        e->exSlot = -1;
        cm_SendExSetHE(4, e);
        cm_SendNewParty(&party);
        return;
      }
    case 4:
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    default:
      return;
    }
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
  }
}
/* 0x5455e0, the alloc handler of the random-message event 0x42 (ai_PostRandomMessages wraps a random message in
   it): the due clock is now at a random hour 10 .. 19, minute 0 .. 0x3a and second 0 */

void he_AllocRandomMessage(AIJOB *e) {

  e->end = ai_Time;
  e->end.hour = (short)(util_Random(10) + 10);
  e->end.min = util_Random(0x3b);
  e->end.sec = 0;
}
/* 0x545640, the run handler of the random-message event 0x42: runs the message it wraps (a G14MSG at 0xac) unless
   the event is cancelled (stage -2), then frees the event record */
void he_RunRandomMessage(AIJOB *e) {

  if (e->stage != -2)
    ai_RunMessage(&e->msg);
  he_FreeEvent(e);
}
/* 0x545670, a Ghidra miss (disassembled): the alloc handler of the patrol event 0x43, once it is started (opts bit
   4 clear): the start clock is now; of the buildings of kind 6 (gm_BuildQuery 1, 6) up to 8 with a scene object,
   other than the target and the start and not of type 0x47, within 950 of the target's object are collected, and
   up to four of them in a random order (gm_Shuffled) become its way (patrolWay, else -1); prints the
   "STREIFE_INIT" line (not shown), its first step is due in a second, and it is posted with key 0 */
void he_AllocPatrol(AIJOB *e) {
  AIBLD *target, *b;
  D3OBJECT *p, *q;
  int cand[8];
  int pick[8];
  char buf[0x100];
  int n = 0;
  int k;
  float dx, dy, dz, dist;

  if (e->opts & 4)
    return;
  e->start = ai_Time;
  memset(cand, -1, sizeof(cand));
  target = gm_BuildQuery(1, 1, e->patrolTarget);
  for (b = gm_BuildQuery(1, 6); b != 0; b = gm_BuildNext()) {
    if (n >= 8)
      break;
    p = b->object;
    if (p != 0 && b->id != target->id && b->id != e->patrolStart &&
        b->type != 0x47) {
      q = target->object;
      dx = p->pos.x - q->pos.x;
      dy = p->pos.y - q->pos.y;
      dz = p->pos.z - q->pos.z;
      dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
      if (dist <= 950.0f)
        cand[n++] = b->id;
    }
  }
  if (n != 0) {
    memset(e->patrolWay, -1, sizeof(e->patrolWay));
    gm_Shuffled((unsigned char)n, pick);
    for (k = 0; k < n && k < 4; k++)
      e->patrolWay[k] = cand[pick[k]];
  }
  sprintf(buf, "STREIFE_INIT: Target: %i, Way: %i, %i, %i, %i, Start: %i",
          e->patrolTarget, e->patrolWay[0], e->patrolWay[1], e->patrolWay[2],
          e->patrolWay[3], e->patrolStart);
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 0, 1);
  e->patrolStep = 0;
  e->patrolRound = 0;
  e->patrolWait = -1;
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x545840, a Ghidra miss (disassembled): the run handler of the patrol event 0x43 (he_AllocPatrol); each stage
   posts the next one with cm_SendExSetHE, due after gm_AddTime (hours, minutes, seconds). While none of the four
   patrolGuards is found the event is put off a minute and ends (-1). Stage -2 runs stage 1 once and frees the event;
   a set patrolWait enters stage 0x400. Stage 0 sends the guards with a scene character to the target building
   ("Streife"; "GOTO_TARGET: %i", not shown; the others are dropped) -> 2; stage 2 / 0x400 wait while a guard's
   scene character has actions queued (0x400 looks every 4 minutes and clears patrolWait) -> 3; stage 3 sends them
   to the next way point (patrolStep) with a random gesture ("gestik/..." once or twice; "GOTO_NEXT: %i") -> 2, past
   the last one counts patrolRound and starts at the target again -> 0, and 8 hours (0x1e0 minutes) after the start
   turns home -> 1; stage 1 sends them to the start building's object 0x146 and pays the event's character for
   each guard 3 .. 6 rolls of random(v * (v + 1)) + 2v, v = sk82 / 42 + 1 (gm_PlayerFactor of the sum: the news
   0x1a6a and cm_SendMoveGoods; "GOTO_START: %i") -> -1, the end; a building not found ends it as well */
void he_RunPatrol(AIJOB *e) {
  AIBLD *b;
  AIOBJ *o;
  AICHAR *c;
  char line[0x40];
  char text[0x200];
  int i, k, v, pay;
  int gone = 0, leaving = 0, paid, sum;

  if (e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4) {
    if (e->stage == -2)
      he_FreeEvent(e);
    return;
  }
  for (i = 0; i < 4; i++) {
    if (gm_FindChar(e->patrolGuards[i]) != 0)
      break;
    gone++;
  }
  if (gone == 4) {
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (e->stage == -2) {
    leaving = 1;
    e->stage = 1;
  }
  if (e->patrolWait != -1)
    e->stage = 0x400;
  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, e->patrolTarget);
    if (b == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    for (i = 0; i < 4; i++) {
      if (e->patrolGuards[i] == -1)
        continue;
      c = gm_FindChar(e->patrolGuards[i]);
      if (c != 0 && c->scene != 0) {
        sv_MoveToGroup(0, 0, c->id, e);
        cm_SendChrStop(e->patrolGuards[i]);
        cm_SendChrGotoBuilding(e->patrolGuards[i], b->id, -1, 0, 1, "Streife");
      } else {
        e->patrolGuards[i] = -1;
      }
    }
    sprintf(line, "GOTO_TARGET: %i", b->id);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 1:
    b = gm_BuildQuery(1, 1, e->patrolStart);
    if (b == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    o = gm_Query(b->objList, 1, 0, 0x146);
    paid = 0;
    sum = 0;
    for (i = 0; i < 4; i++) {
      if (e->patrolGuards[i] == -1)
        continue;
      c = gm_FindChar(e->patrolGuards[i]);
      if (c != 0 && c->scene != 0) {
        v = (int)((float)c->sk82 * 0.023809524f + 1.0f);
        for (k = util_Random(4) + 3; k > 0; k--)
          sum += util_Random((v + 1) * v) + v * 2;
        paid++;
        cm_SendChrStop(e->patrolGuards[i]);
        cm_SendChrGotoBuilding(e->patrolGuards[i], b->id, o->objId, 0, 0,
                               "Streife");
        sv_MoveToGroup(0, 0, c->id, e);
      } else {
        e->patrolGuards[i] = -1;
      }
    }
    if (leaving) {
      he_FreeEvent(e);
      return;
    }
    if (paid != 0) {
      pay = gm_PlayerFactor(sum, ai_OwnPlayer);
      txt_Format(text, 0x1a6a, pay);
      he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec, b->id,
                             -1, 0, (char *)0);
      cm_SendMoveGoods(ai_Chars[e->chr].netId, -1, ai_OwnPlayer, pay);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    sprintf(line, "GOTO_START: %i", b->id);
    return;
  case 2:
    for (i = 0; i < 4; i++) {
      if (e->patrolGuards[i] != -1 &&
          (c = gm_FindChar(e->patrolGuards[i])) != 0 && c->scene != 0 &&
          c->scene->actions != 0)
        return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(3, e);
    return;
  case 0x400:
    for (i = 0; i < 4; i++) {
      if (e->patrolGuards[i] != -1 &&
          (c = gm_FindChar(e->patrolGuards[i])) != 0 && c->scene != 0 &&
          c->scene->actions != 0) {
        gm_AddTime(&e->end, 0, 4, 0);
        e->exSlot = cm_SendExSetHE(0x400, e);
        return;
      }
    }
    e->end = ai_Time;
    e->patrolWait = -1;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(3, e);
    return;
  case 3:
    if (e->patrolStep <= 3 && e->patrolWay[e->patrolStep] != -1) {
      if (gm_MinutesBetween(&e->start, &ai_Time) > 0x1e0) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 2, 0);
        e->exSlot = cm_SendExSetHE(1, e);
        return;
      }
      b = gm_BuildQuery(1, 1, e->patrolWay[e->patrolStep]);
      e->patrolStep++;
      if (b == 0) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 2, 0);
        e->exSlot = cm_SendExSetHE(1, e);
        return;
      }
      for (i = 0; i < 4; i++) {
        if (e->patrolGuards[i] == -1)
          continue;
        c = gm_FindChar(e->patrolGuards[i]);
        if (c != 0 && c->scene != 0) {
          char gestures[3][0x20] = {"gestik/kopf_kratzen",
                                    "gestik/durch_haar_fahr",
                                    "gestik/kinn_kratzen"};

          sv_MoveToGroup(0, 0, c->id, e);
          cm_SendChrStop(e->patrolGuards[i]);
          cm_SendChrGotoBuilding(e->patrolGuards[i], b->id, -1, 0, 1,
                                 "Streife");
          k = util_Random(2) + 1;
          cm_SendChrAnim(e->patrolGuards[i], gestures[util_Random(3)], k);
        } else {
          e->patrolGuards[i] = -1;
        }
      }
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(2, e);
      sprintf(line, "GOTO_NEXT: %i", b->id);
      return;
    }
    if (gm_MinutesBetween(&e->start, &ai_Time) > 0x1e0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(1, e);
      return;
    }
    e->patrolStep = 0;
    e->patrolRound++;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(0, e);
    return;
  }
}
/* 0x546100, the alloc handler of the raid event 0x44 ("Razzia", its run handler he_RunRaid): when it runs when due
   and its target building (gm_BuildQuery kind 1) is gone, it ends the event at once; either way it posts the event
   again in a second */

void he_AllocRaid(AIJOB *e) {

  if ((e->opts & 2) != 0) {
    if (gm_BuildQuery(1, 1, e->raidTarget) == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 0, 1);
      e->exSlot = cm_SendExSetHE(-1, e);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x5461c0, a Ghidra miss (disassembled): the run handler of the raid event 0x44 ("Razzia"; the raiders are ids[],
   the buildings raidTarget / raidStart). It waits for the event's cm send slot (exSlot); stage -2 (left) runs
   stage 1 once and frees the event. Stage 0 sends the raiders to the target ("Razzia"; the others are dropped) -> 2,
   while the target has an owner, else the event ends (-1, as when a building is not found); stage 2 waits until no
   raider's scene character has actions queued -> 3; stage 3 rolls random(0x4b) + 100 * the start building's spy
   report on the target (its object 0xca: (100 + reportKnow) / 100, 5 with gm_AllowAll) against 125 * (1 + 0.01 *
   gm_BuildingSkill(target, 5, 1)): above it a fight party of kind 3 (G28REC.raid: the target's living
   people against the raiders, half an hour on) is posted -> 4, but with no defender or no raider the target
   is looted (cm_LootStock, the news 0x1c54 / 0x1c55 to the players among owner and raider) -> 1; not above it
   the raid fails (the news 0x114b with the start building's fight role, 0x1c56 to a player owner) -> -1;
   stage 4 waits for the party's slot and keeps its id -> 5, stage 5 until the party is over -> 1; stage 1
   (only with opts 2) sends the living raiders back to the start building's object 0x146 -> -1; stage -1
   sends them to its main room and frees the event. The opts tests of the stages 0 and 2 are
   @original `(opts == 0) & 2`, never true. */
void he_RunRaid(AIJOB *e) {
  AIBLD *b, *home;
  AICHAR *c, *raider;
  AIOBJ *o;
  G28REC party;
  char text[0x800];
  int i, n, k, loot, role;
  float chance = 1.0f, defence;
  int leaving = 0, idle;

  if (e->stage == -2) {
    if ((e->opts & 2) == 0) {
      he_FreeEvent(e);
      return;
    }
    leaving = 1;
    e->stage = 1;
  }
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if ((e->opts == 0) & 2)
      return;
    b = gm_BuildQuery(1, 1, e->raidTarget);
    if (b == 0 || b->owner == 0xffff) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    for (i = 0; i < 8; i++) {
      if (e->ids[i] == -1)
        continue;
      c = gm_FindChar(e->ids[i]);
      if (c != 0) {
        sv_MoveToGroup(b, 0, c->id, e);
        cm_SendChrStop(e->ids[i]);
        cm_SendChrGotoBuilding(e->ids[i], b->id, -1, 0, 0, "Razzia");
      } else {
        e->ids[i] = -1;
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 1:
    if ((e->opts & 2) == 0)
      return;
    home = gm_BuildQuery(1, 1, e->raidStart);
    if (home == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    o = gm_Query(home->objList, 1, 0, 0x146);
    for (i = 0; i < 8; i++) {
      if (e->ids[i] == -1)
        continue;
      c = gm_FindChar(e->ids[i]);
      if (c != 0 && c->health > 0) {
        cm_SendChrStop(e->ids[i]);
        cm_SendChrGotoBuilding(e->ids[i], home->id, o->objId, 0, 0, "Razzia");
        sv_MoveToGroup(home, 0, c->id, e);
      } else {
        e->ids[i] = -1;
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    if (leaving) {
      he_FreeEvent(e);
      return;
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 2:
    if ((e->opts == 0) & 2)
      return;
    idle = 1;
    for (i = 0; i < 8; i++) {
      if (e->ids[i] != -1 && (c = gm_FindChar(e->ids[i])) != 0 &&
          c->scene->actions != 0) {
        idle = 0;
        break;
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    if (idle)
      e->exSlot = cm_SendExSetHE(3, e);
    else
      e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 3:
    if ((e->opts & 2) == 0)
      return;
    b = gm_BuildQuery(1, 1, e->raidTarget);
    c = &ai_Chars[b->owner];
    raider = &ai_Chars[e->chr];
    defence = (float)(gm_BuildingSkill(b, 5, 1) * 0.01 + 1.0);
    home = gm_BuildQuery(1, 1, e->raidStart);
    o = gm_Query(home->objList, 1, 0, 0xca);
    for (; o != 0; o = gm_QueryNext())
      if (o->reportBld == b->id)
        break;
    if (o != 0)
      chance = (float)((o->reportKnow + 100.0) * 0.01);
    if (gm_AllowAll != 0)
      chance = 5.0f;
    if ((float)util_Random(0x4b) + chance * 100.0f > defence * 125.0f) {
      memset(&party, 0, sizeof(party));
      party.kind = 3;
      party.flags = 0xa2;
      party.thing = b->id;
      party.host = ai_Chars[ai_PlayerId].netId;
      party.used = 2;
      party.variant = 2;
      party.members[0] = raider->netId;
      party.members[1] = c->netId;
      for (i = 0; i < 16; i++) {
        party.fight.attackers[i] = -1;
        party.fight.defenders[i] = -1;
      }
      n = 0;
      for (i = 0; i < 768 && n < 16 && n < 6; i++) {
        if (ai_Chars[i].health != 0 && ai_Chars[i].bld == b) {
          party.fight.defenders[n] = ai_Chars[i].netId;
          n++;
        }
      }
      for (i = 0; i < 3; i++)
        party.fight.carts[i] = -1;
      home = gm_BuildQuery(1, 1, e->raidStart);
      party.fight.attackerBld = home->id;
      k = 0;
      for (i = 0; i < 8 && k < 6; i++) {
        if (e->ids[i] != -1) {
          party.fight.attackers[k] = e->ids[i];
          k++;
        }
      }
      if (k != 0 && n != 0) {
        party.time = ai_Time;
        gm_AddTime(&party.time, 0, 0x1e, 0);
        e->raidSlot = cm_SendNewParty(&party);
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 0, 1);
        e->stage = 4;
        return;
      }
    } else {
      role = cm_FightRole(gm_BuildQuery(1, 1, e->raidStart)) + 0x1125;
      txt_Format(text, 0x114b, role, b->owner, b, role);
      he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5f0, (char *)0);
      if (ai_Chars[b->owner].kind == 6 || ai_Chars[b->owner].kind == 7) {
        txt_Format(text, 0x1c56, b);
        he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, text, 0, 0x5f0,
                               b->id, -1, 0, (char *)0);
      }
      e->stage = -1;
      return;
    }
    home = gm_BuildQuery(1, 1, e->raidStart);
    b = gm_BuildQuery(1, 1, e->raidTarget);
    loot = cm_LootStock(b, home, &ai_Chars[e->chr], &ai_Chars[b->owner]);
    if (ai_Chars[b->owner].kind == 6 || ai_Chars[b->owner].kind == 7) {
      txt_Format(text, 0x1c54, b, loot);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, text, 0, 0x5f0,
                             b->id, -1, 0, (char *)0);
    }
    if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
      txt_Format(text, 0x1c55, b->owner, b, loot);
      he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5f0, (char *)0);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    e->stage = 1;
    return;
  case 4:
    if (cm_GetSlotState(e->raidSlot) == 0)
      return;
    e->raidParty = ((G28REC *)cm_GetSlotValue(e->raidSlot))
                       ->id; /* the slot's value: the party record made */
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 1, 0);
    e->stage = 5;
    return;
  case 5:
    if (cm_PartyById(e->raidParty) != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    e->stage = 1;
    return;
  case -1:
    if (e->opts & 2) {
      home = gm_BuildQuery(1, 1, e->raidStart);
      o = gm_GetGebaeudeHauptraum(home);
      for (i = 0; i < 8; i++) {
        if (e->ids[i] != -1 && (c = gm_FindChar(e->ids[i])) != 0) {
          cm_SendChrStop(e->ids[i]);
          cm_SendChrGotoBuilding(e->ids[i], home->id, o->objId, 0, 0, "Razzia");
          sv_MoveToGroup(home, 0, c->id, 0);
        }
      }
    }
    he_FreeEvent(e);
    return;
  }
}

int gv_HeldCrimeIdsOf(int culprit, int *out, unsigned short t);

/* 0x546c40, a Ghidra miss (disassembled): the alloc handler of the fight event 0x45 between partner1 (a) and
   partner2 (b), its run handler 0x546ef0 the end: the event is due from now, stage 2. Unless it is started (opts 2)
   nothing more; with a or b gone, a already fighting (flags1c8 0x100) or b already fought (0x200) it ends in two
   minutes. With +0xb4 set (id3) it runs a day and a player b hears the news 0x1e18 (code -4); else it runs four
   days, a player b hears 0x1d5b, a is accused of the crime 0x16 against b (at a's home, else b's: gv_Accuse), a's
   relation to b gets 0x34, up to three crimes of b whose evidence a holds are dropped (gv_HeldCrimeIdsOf in a
   random order, cm_SendDropEvidence), a player a counts the mission event 0xb, code -2. Both get their flag and
   cm_SendMoneyDelta(a, code) */
void he_AllocFight(AIJOB *e) {
  AICHAR *a, *b;
  char text[0x100];
  int pick[16];
  int crimes[32];
  int code, place, n, i;
  AIBLD *home;

  e->end = ai_Time;
  e->stage = 2;
  if ((e->opts & 2) == 0)
    return;
  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  if (a == 0 || (a->flags1c8 & 0x100) != 0 || b == 0 ||
      (b->flags1c8 & 0x200) != 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (e->id3 != 0) {
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.min = 0;
    if (b->kind == 6 || b->kind == 7) {
      txt_Format(text, 0x1e18, a->id);
      he_ShowNews(b->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_NEU_04");
    }
    code = -4;
  } else {
    gm_AddTime(&e->end, 0x60, 0, 0);
    e->end.min = 0;
    code = -2;
    if (b->kind == 6 || b->kind == 7) {
      txt_Format(text, 0x1d5b, a->id, a->id);
      he_ShowNews(b->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_HS_21");
    }
    place = -1;
    home = a->bld2;
    if (home != 0)
      place = home->id;
    else {
      home = b->bld2;
      if (home != 0)
        place = home->id;
    }
    gv_Accuse(0x16, 1, a->netId, b->netId, place);
    cm_SendRelations(a->netId, b->netId, 0x34, 1);
    n = gv_HeldCrimeIdsOf(b->netId, crimes, a->id);
    gm_Shuffled(n < 0x10 ? n : 0x10, pick);
    for (i = 0; i < 3 && n != 0; i++, n--)
      cm_SendDropEvidence(crimes[pick[i]], a->netId, 0);
    if (a->kind == 6)
      ai_CountMissionEvent(a, 0xb);
  }
  cm_SendSetField(a->netId, 0x1c8, 4, 0x100, 0);
  cm_SendSetField(b->netId, 0x1c8, 4, 0x200, 0);
  cm_SendMoneyDelta(a->netId, code);
}
/* 0x546ef0, a Ghidra miss (disassembled): the run handler of the fight event 0x45 (he_AllocFight): at stage 2
   (started, opts 2) both fighters lose their flag (flags1c8 0x100 / 0x200); with both found the outcome id3 tells:
   1 / 2 a player partner2 (b) hears the news 0x1e19 / 0x1e20, else a's relation to b drops by 0x68 and b hears
   0x1d5d, a player a's news 0x1d5c goes to b as well; the event ends in two minutes. Stage -1 / -2 (left) clears
   the flags (when started) and frees the event */
void he_RunFight(AIJOB *e) {
  AICHAR *a, *b;
  char text[0x100];

  switch (e->stage) {
  case 2:
    if ((e->opts & 2) == 0)
      return;
    a = gm_FindChar(e->partner1);
    if (a != 0)
      cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x100);
    b = gm_FindChar(e->partner2);
    if (b != 0)
      cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x200);
    if (a != 0 && b != 0) {
      if (e->id3 == 1) {
        if (b->kind == 6 || b->kind == 7) {
          txt_Format(text, 0x1e19, a->id);
          he_ShowNews(b->netId, -1, text, 0, 0x5fb, (char *)0);
        }
      } else if (e->id3 == 2) {
        if (b->kind == 6 || b->kind == 7) {
          txt_Format(text, 0x1e20, a->id);
          he_ShowNews(b->netId, -1, text, 0, 0x5fb, (char *)0);
        }
      } else {
        cm_SendRelations(a->netId, b->netId, -0x68, 1);
        if (b->kind == 6 || b->kind == 7) {
          txt_Format(text, 0x1d5d, a->id);
          he_ShowNews(b->netId, b->netId, text, 0, 0x5fb, (char *)0);
        }
        if (a->kind == 6 || a->kind == 7) {
          txt_Format(text, 0x1d5c, b->id);
          he_ShowNews(b->netId, b->netId, text, 0, 0x5fb, (char *)0);
        }
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case -1:
  case -2:
    if (e->opts & 2) {
      a = gm_FindChar(e->partner1);
      if (a != 0)
        cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x100);
      b = gm_FindChar(e->partner2);
      if (b != 0)
        cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x200);
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x547170, the alloc handler of the duel challenge event 0x46 (its run handler he_RunDuelChallenge): the start and
   the due clock are now, the event runs two units later */

void he_AllocDuelChallenge(AIJOB *e) {

  e->start = ai_Time;
  e->end = ai_Time;
  gm_AddTime(&e->end, 2, 0, 0);
}
/* 0x5471e0, the duel intro: lets both duellists (p2 / p3, 0x4c4a60 flag 0x400) hear the news 0x1d83 / 0x1d82 (messages 0x5fa / 0x5fb, "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00" for the first) and posts the event (state 2) */

void he_DuelAccepted(AIJOB *e, AICHAR *p2, AICHAR *p3) {
  char buf[1024];

  cm_SendSetField(p2->netId, 0x1c8, 4, 0x400, 0);
  cm_SendSetField(p3->netId, 0x1c8, 4, 0x400, 0);
  if (p2->kind == 6 || p2->kind == 7) {
    txt_Format(buf, 0x1d83, p3->id, &e->end, p3->id);
    he_ShowNews(p2->netId, p2->netId, buf, 0, 0x5fa,
                "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
  }
  if (p3->kind == 6 || p3->kind == 7) {
    txt_Format(buf, 0x1d82, p2->id, &e->end, p2->id);
    he_ShowNews(p3->netId, -1, buf, 0, 0x5fb,
                "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
  }
  cm_SendExSetHE(2, e);
}

void amt_ChangeDistrictOpinion(struct AICHAR *c, int d,
                               int v); /* 0x4ea550, amt.c */

/* 0x5472d0, a Ghidra miss (disassembled): the challenge of the insult event ("Special\Beleidigung") is declined
   (the second choice, or no choice in time) by q, challenged by p (the characters partner1 / partner2 of the
   event ev it runs for): a player p hears the news 0x1d81 (0x1d68 + 1 for a q of sex 1) and both lose the flag
   0x400 (flags1c8); q's district (the district of its office, else a random 1 .. 3) loses
   9 + 8 * p's skill 4 + random(8) of its opinion of q (amt_ChangeDistrictOpinion, district 0 without an office),
   p's relation to q drops by 0x14, and ev ends now */
void he_DuelDeclined(AIJOB *ev, AICHAR *p, AICHAR *q) {
  char text[0x400];
  AMTKIND office;
  AMTREC seat;
  int district = 0, txt;

  if (p->kind == 6 || p->kind == 7) {
    if (q->sex != 0)
      txt = 0x1d69;
    else
      txt = 0x1d68;
    txt_Format(text, 0x1d81, q->id, q->id, txt);
    he_ShowNews(p->netId, p->netId, text, 0, 0x5fb, (char *)0);
    cm_SendSetField(p->netId, 0x1c8, 4, 0, 0x400);
    cm_SendSetField(q->netId, 0x1c8, 4, 0, 0x400);
  }
  if (q->officeKind != 0) {
    if (amt_FindOffice(q, &office, &seat) != 0)
      district = office.col;
    else
      district = util_Random(3) + 1;
  }
  amt_ChangeDistrictOpinion(
      q, district, -9 - (int)(gm_GetSkill(p, 4) * 8.0f) - util_Random(8));
  cm_SendRelations(p->netId, q->netId, -0x14, 1);
  ev->end = ai_Time;
  cm_SendExSetHE(-1, ev);
}
/* 0x547430, a Ghidra miss (disassembled): the run handler of the duel challenge event 0x46 (its alloc handler
   0x547170): duelId names the duel event, its partner1 the challenger p, partner2 the challenged q. With the
   stage -1 / -2 or the duel, p or q gone both events end (the slot released, the duel posted -1). Stage 0 opens
   the event slot "Special\Beleidigung" (no slot: the event is freed), plays "NeueMessage_s_01" (unless the game
   state is 2), prints the news 0x1d6c, p's special-amount row (ai_AmountRowStatus / ai_DrawAmountRow, its control
   clickable) and the news 0x1d6b; the answer is due in two hours. Stage 1: past that time, or with the second
   choice, q declines (he_DuelDeclined); the first choice accepts (he_DuelAccepted); then the slot is released and
   the event freed */
void he_RunDuelChallenge(AIJOB *e) {
  AIJOB *duel;
  AICHAR *q = 0, *p = 0;
  LCAMOUNTROW row; /* p's special-amount row */

  duel = he_FindEvent(1, 1, e->duelDuelId);
  if (duel != 0) {
    q = gm_FindChar(duel->partner2);
    p = gm_FindChar(duel->partner1);
  }
  if (e->stage == -1 || e->stage == -2 || duel == 0 || q == 0 || p == 0) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    if (duel != 0) {
      duel->end = ai_Time;
      cm_SendExSetHE(-1, duel);
    }
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Special\\Beleidigung", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    if (ai_GameState != 2)
      sb_PlaySample(snd_SystemBank, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
    d2_SetForm(e->slot->win, 1);
    io_PrintText(0x1d6c);
    d2_SetForm(e->slot->win, 2);
    row.rec = p;
    if (ai_AmountRowStatus(&row) != 0) {
      ai_DrawAmountRow(d2_LastWindowPtr->w / 2 - 0x28, 0, d2_LastWindow, &row);
      d2_Objs[row.ctl[0]].interactive = 1;
      d2_Objs[row.ctl[0]].style = 3;
      d2_Objs[row.ctl[0]].user = row.rec;
    }
    d2_SetForm(e->slot->win, 3);
    io_PrintText(0x1d6b, duel->duelNewsArg1, p->id, duel->duelNewsArg2, p->id);
    e->start = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 2, 0, 0);
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_DuelDeclined(duel, p, q);
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (d2_ClickedForm != e->slot->win)
      return;
    if (d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0)
      he_DuelAccepted(duel, p, q);
    else if (d2_ClickedId == 1)
      he_DuelDeclined(duel, p, q);
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
}
/* 0x547750, a Ghidra miss (disassembled): the alloc handler of the insult event 0x47 (its run handler 0x547ba0),
   partner1 (a) insults partner2 (b): it is due the next day at 6:30 (no cm slot yet). Once started (opts 2): when
   a or b is gone and one of them is already in a quarrel (flags1c8 0x400; @original read through the pointer
   that may be 0) it ends in two minutes. a is accused of the crime 4 against b (at a's home, else b's). A player b
   gets the long message 0x46 (to b, the event's id in arg[0], its time six hours past zero) that starts the duel
   challenge (he_RunDuelChallenge) -> 1, both in a quarrel. Else b answers by itself: with util_RandomF() +
   gm_Mix(b, a, 3) of 1 or more it challenges (both in a quarrel, a player a hears the duel intro news 0x1d83)
   -> 2; below, it declines as he_DuelDeclined does (a hears 0x1d81, b's district's opinion and b's relation to a
   drop) and the event ends in two minutes */
void he_AllocInsult(AIJOB *e) {
  AICHAR *a, *b;
  AMTKIND office;
  AMTREC seat;
  int place, district, amt;

  e->exSlot = -1;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->end.hour = 6;
  e->end.min = 0x1e;
  if ((e->opts & 2) == 0)
    return;
  a = gm_FindChar(e->partner1);
  b = gm_FindChar(e->partner2);
  if (a == 0 || b == 0) {
    if ((a->flags1c8 & 0x400) != 0 || (b->flags1c8 & 0x400) != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
  }
  place = -1;
  if (a->bld2 != 0)
    place = a->bld2->id;
  else if (b->bld2 != 0)
    place = b->bld2->id;
  gv_Accuse(4, 1, a->netId, b->netId, place);
  if (b->kind == 6 || b->kind == 7) {
    AIMSG msg;

    memset(&msg, 0, sizeof(msg));
    msg.to = b->netId;
    msg.fromId = b->netId;
    msg.type = 0x46;
    msg.flags = 9;
    msg.arg[0] = e->id;
    gm_AddTime2(&msg.time, b->id, 6, 0, 0); /* the second argument unused */
    cm_SendLongMessage(&msg);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 6;
    e->end.min = 0x1e;
    e->exSlot = cm_SendExSetHE(1, e);
    cm_SendSetField(a->netId, 0x1c8, 4, 0x400, 0);
    cm_SendSetField(b->netId, 0x1c8, 4, 0x400, 0);
    return;
  }
  if (util_RandomF() + gm_Mix(b, a, 3) >= 1.0f) {
    cm_SendSetField(a->netId, 0x1c8, 4, 0x400, 0);
    cm_SendSetField(b->netId, 0x1c8, 4, 0x400, 0);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 6;
    e->end.min = 0x1e;
    if (a->kind == 6 || a->kind == 7) {
      char text[0x100];

      txt_Format(text, 0x1d83, b->id, &e->end, b->id);
      he_ShowNews(a->netId, a->netId, text, 0, 0x5fa,
                  "_DUELL_INTRO_EVENT_DUELLANTEN_HS_00");
    }
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  }
  district = 0;
  if (a->kind == 6 || a->kind == 7) {
    char text[0x100];
    int txt;

    if (b->sex != 0)
      txt = 0x1d69;
    else
      txt = 0x1d68;
    txt_Format(text, 0x1d81, b->id, b->id, txt);
    he_ShowNews(a->netId, a->netId, text, 0, 0x5fa, (char *)0);
  }
  if (b->officeKind != 0) {
    if (amt_FindOffice(b, &office, &seat) != 0)
      district = office.col;
    else
      district = util_Random(3) + 1;
  }
  amt = -9 - (int)(gm_GetSkill(a, 4) * 8.0f);
  amt -= util_Random(8);
  amt_ChangeDistrictOpinion(b, district, amt);
  cm_SendRelations(b->netId, a->netId, -0x14, 1);
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 2, 0);
  e->exSlot = cm_SendExSetHE(-1, e);
}
/* 0x547ba0, a Ghidra miss (disassembled): the run handler of the insult event 0x47 (he_AllocInsult), once its cm
   slot is answered: stage 2 (the insulted challenged) posts a fight party of kind 4 between partner1 (a) and
   partner2 (b) half an hour from now (G28REC, held by the player's character, flags 0xa2); stages 2 and 1 (a
   player's challenge sent, he_RunDuelChallenge goes on) take the quarrel flag 0x400 (flags1c8) from both and end
   the event in two minutes; stage -1 / -2 (left) does the same when it was started and frees the event; all only
   once started (opts 2) */
void he_RunInsult(AIJOB *e) {
  AICHAR *a, *b;

  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 2:
    if ((e->opts & 2) == 0)
      return;
    a = gm_FindChar(e->partner1);
    b = gm_FindChar(e->partner2);
    if (a != 0) {
      if (b != 0) {
        G28REC party;

        memset(&party, 0, sizeof(party));
        party.host = ai_Chars[ai_PlayerId].netId;
        party.members[0] = a->netId;
        party.kind = 4;
        party.flags = 0xa2;
        party.thing = -1;
        party.used = 2;
        party.variant = 0;
        party.members[1] = b->netId;
        party.time = ai_Time;
        gm_AddTime(&party.time, 0, 0x1e, 0);
        cm_SendNewParty(&party);
      }
      cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x400);
    }
    if (b != 0)
      cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x400);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 1:
    if ((e->opts & 2) == 0)
      return;
    a = gm_FindChar(e->partner1);
    b = gm_FindChar(e->partner2);
    if (a != 0)
      cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x400);
    if (b != 0)
      cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x400);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case -2:
  case -1:
    if (e->opts & 2) {
      a = gm_FindChar(e->partner1);
      b = gm_FindChar(e->partner2);
      if (a != 0)
        cm_SendSetField(a->netId, 0x1c8, 4, 0, 0x400);
      if (b != 0)
        cm_SendSetField(b->netId, 0x1c8, 4, 0, 0x400);
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x547ee0, the alloc handler of the "RndGeselle" (a random journeyman) event 0x4a (its run handler he_RunGeselle):
   the building g->geselleBldId must exist (else the event is freed); g->geselleSlot is cm_SendMessage3d's slot for the journeyman
   of the building's kind record byte at +0x22f (0x24d bytes per kind, ai_BTypes); the clock is six units ahead */

void he_AllocGeselle(AIJOB *e) {
  AIJOB *g = e;
  AIBLD *b = 0;
  AIBTYPE *t;

  gm_FindById(&b, 0, 0, g->geselleBldId);
  if (b == 0)
    he_FreeEvent(e);
  t = &ai_BTypes[b->type];
  g->geselleSlot = cm_SendMessage3d(b, 0, t->title, 0);
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 6, 0);
}
/* 0x547f90, a Ghidra miss (disassembled): the run handler of the "RndGeselle" event 0x4a (a random journeyman):
   pushes the end four units ahead, frees the event at stage -2 or when its building is gone; at stage 0, once the
   cm slot is answered, sends the new character it holds to the building ("RndGeselle"), shows the news newsId
   (the character, its title text 0x20d / 0x230 by sex + title, the receiver) in a quick-jump message box and frees
   the event
   @deep near-byte sweep s22: left only bld / chr in each other's slot (frame 0x200 > 0x80: unstable
   density sort of two count-3 locals, c2frame L bld, chr -> A chr, bld; the original needs bld one
   reference more or chr one fewer). Declaration order / init order / init statements late / text as a
   block local: = control or order hunks only. */

void he_RunGeselle(AIJOB *e) {
  AIJOB *g = e;
  char text[0x200];
  AIBLD *bld = 0;
  AICHAR *chr = 0;
  AICHAR *c;
  int title;

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 4, 0);
  gm_FindById(&bld, 0, 0, g->geselleBldId);
  gm_FindById(0, 0, &chr, g->geselleChrId);
  if (e->stage == -2 || bld == 0)
    he_FreeEvent(e);
  if (e->stage == 0 && cm_GetSlotState(g->geselleSlot) != 0) {
    c = (AICHAR *)cm_GetSlotValue(g->geselleSlot);
    if (c != 0) {
      title = (c->sex ? 0x230 : 0x20d) + (unsigned char)c->title;
      cm_SendChrGotoBuilding(c->netId, g->geselleBldId, g->geselleBldArg, 0, 0,
                             "RndGeselle");
      txt_Format(text, g->geselleNewsId, c->id, title, chr);
      he_MessageBoxQuickjump(g->geselleChrId, g->geselleChrId, text, 0, 0x5ec,
                             g->geselleBldId, g->geselleBldArg, 0,
                             "_NACHRICHTEN_HS_00");
    }
    he_FreeEvent(e);
  }
}
/* 0x548110, the alloc / start handler of the insult news event 0x4b (its run handler he_RunInsultNews): an event
   not started yet (opts 4 clear) gets the end clock 0x18 units ahead; once it is due (opts 2) both partners are
   looked up, a gone one ends it with the clock copied (posted -1), and for a player partner (kind 6 / 7) the news
   0x1d64 about partner1 goes to partner2's netId; the event is then posted (state 0) */

void he_AllocInsultNews(AIJOB *e) {
  char text[0x400];
  AICHAR *a, *b;

  e->exSlot = -1;
  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    if ((e->opts & 2) != 0) {
      b = gm_FindChar(e->partner2);
      a = gm_FindChar(e->partner1);
      if (a == 0 || b == 0) {
        e->end = ai_Time;
        cm_SendExSetHE(-1, e);
        return;
      }
      if (b->kind == 6 || b->kind == 7) {
        txt_Format(text, 0x1d64, a->id, &e->end, a->id);
        he_ShowNews(b->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_HS_20");
      }
    }
    cm_SendExSetHE(0, e);
  }
}

void gm_ChangeRelationToJobs(unsigned short a, int b);
void ai_PlagueNews(void);
/* clang-format off */
int ai_PickActionBuilding(struct AICHAR *p, int a, __int64 mask, int lo, float hi, int *out);  /* 0x4a63f0, @original: amt_ai.c defines lo as a float; this unit passes it as an int, he_AllocBrawl its (null) home building through a register (push edi) */
/* clang-format on */

/* 0x548230, the run handler of the insult news event (type 0x4b, whose start handler is 0x548110): a pending cm
   slot still in state 0 keeps it; a freed state (-2) ends it, a negative one frees it, and in state 0 with opts
   bit 2 it is posted again two minutes later (the end time = the clock now, cm_SendExSetHE) */
void he_RunInsultNews(AIJOB *e) {
  int st;

  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  st = e->stage;
  e->exSlot = -1;
  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    if ((e->opts & 2) == 0)
      return;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  he_FreeEvent(e);
}
/* 0x5482c0, the shared alloc / start handler of the event types 0x51 and 0x56 (the payment event, he_RunPayment):
   the end clock is the game time one day (0x18 hours) ahead */

void he_AllocNextDay(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
}
/* 0x548300, the run handler of the countdown event 0x51 (he_AllocNextDay): while the stage is 0 it counts the
   event's byte +0xac down and returns; at 0 (or in the state -2) it frees the event */

void he_RunCountdown(AIJOB *e) {
  AIJOB *c = e;

  if (e->stage != -2) {
    if (e->stage != 0)
      return;
    if (c->countdownRuns > 0) {
      c->countdownRuns--;
      return;
    }
  }
  he_FreeEvent(e);
}
/* 0x548330, the alloc handler of the history comment event 0x52 (the KOMMENTARE text command, ai_CommandComments,
   posts the message): the end clock is one day (0x18 hours) ahead and the entry index the message carries is kept
   with its successor (entry + 1) */

void he_AllocComment(AIJOB *e) {
  AIJOB *c = e;

  e->end = ai_Time;
  c->commentNext = c->commentEntry + 1;
  gm_AddTime(&e->end, 0x18, 0, 0);
}
/* 0x548380, the run handler of the history comment event 0x52 (he_AllocComment): it frees the record in the
   stage 0 or -2 */

void he_RunComment(AIJOB *e) {

  if (e->stage == -2 || e->stage == 0)
    he_FreeEvent(e);
}
/* 0x5483a0, the alloc handler of the character payouts event 0x53 (he_RunCharPayouts): the word +0xb0 is -1, the
   end clock is the start clock with 2 .. 5 hours added, the stage is 0 */

void he_AllocCharPayouts(AIJOB *e) {
  AIJOB *f = e;

  f->festPayoutBld = -1;
  e->end = e->start;
  e->end.hour += (short)util_Random(4) + 2;
  e->stage = 0;
}
/* 0x5483f0 (the Ghidra function 0x548410 starts after the free in the state -2), the run handler of event 0x53:
   formats the news 0x10c2 (the own player slot's name text at +0x20, one of the texts 0x10c4 .. 0x10c6); every
   living character (health >= 2) of kind 5 / 6 / 7 looks for a building of the kinds 7 / 22
   (ai_PickActionBuilding); kinds 6 / 7 get the news; with a building found it is paid 1% of its worth times
   2 .. 5 by the own player (cm_SendMoveGoodsUnchecked) and kinds 6 / 7 get the news 0x10c3 (the building, the
   amount); then frees the event */

void he_RunCharPayouts(AIJOB *ev) {
  char news[0x800];
  char line[0x200];
  AICHAR *c;
  union {
    struct {
      unsigned int lo, hi;
    } s;
    __int64 q;
  } kinds;
  AIBLD *bld;
  int i, at, amount;

  if (ev->stage == -2) {
    he_FreeEvent(ev);
    return;
  }
  txt_Format(news, 0x10c2, ai_PlayerSlots[ai_OwnPlayer].townName,
             util_Random(3) + 0x10c4);
  kinds.s.lo =
      (1 << 22) |
      (1
       << 7); /* ai_PassesBuildingFilter's kind mask: the building kinds 22 and 7 */
  kinds.s.hi = 0;
  bld = 0;
  for (i = 0; i < 0x300; i++) {
    c = &ai_Chars[i];
    if (c->id != 0xffff && c->health >= 2 &&
        (c->kind == 6 || c->kind == 7 || c->kind == 5)) {
      if (ai_PickActionBuilding(c, 4, kinds.q, 0, 100.0f, &at) != 0)
        gm_FindById(&bld, 0, 0, at);
      if (c->kind == 6 || c->kind == 7)
        he_ShowNews(c->netId, -1, news, 0x20, 0x601, (char *)0);
      if (bld != 0) {
        amount = (int)(gm_GetWorth(c->id) * 0.01f) * (util_Random(4) + 2);
        cm_SendMoveGoodsUnchecked(c->netId, -1, ai_OwnPlayer, amount);
        if (c->kind == 6 || c->kind == 7) {
          txt_Format(line, 0x10c3, bld, amount);
          he_ShowNews(c->netId, -1, line, 0, 0x5ff, (char *)0);
        }
      }
    }
    bld = 0;
  }
  he_FreeEvent(ev);
}
/* 0x5485b0, the run handler of the master exam fee event 0x54: stage -1 / -2 releases its slot and frees it; once
   started, stage 0 opens the message box "Berufe\Messagebox_Meisterpruefung" with the news 0x10b1 (the character,
   the fee: 3% of its worth) and goes to stage 1; stage 1 waits for the answer: yes (0) moves the fee between the
   player's character and the event's character (cm_SendMoveGoods) and changes the character's relation to jobs by
   +8, no (1) by -6; both release the slot and free the event */

void he_RunMasterExamFee(AIJOB *e) {
  int fee;

  if (e->stage == -1 || e->stage == -2) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  if (gm_CompareTime(&ai_Time, &e->start) == -1)
    return;
  switch (e->stage) {
  case 0:
    fee = (int)(gm_GetWorth(e->chr) * 0.03f);
    if (e->slot == 0)
      he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    d2_SetForm(e->slot->win, 0);
    io_PrintText((intptr_t)"$C");
    io_PrintText(0x10b1, e->chr, fee);
    e->stage = 1;
    return;
  case 1:
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm == e->slot->win && d2_ClickedId != -1) {
      if (d2_ClickedId == 0) {
        cm_SendMoveGoods(ai_PlayerChar->netId, ai_Chars[e->chr].netId,
                         ai_OwnPlayer, (int)(gm_GetWorth(e->chr) * 0.03f));
        gm_ChangeRelationToJobs(e->chr, 8);
        he_ReleaseSlot(e);
        he_FreeEvent(e);
        return;
      }
      if (d2_ClickedId == 1) {
        gm_ChangeRelationToJobs(e->chr, -6);
        he_ReleaseSlot(e);
        he_FreeEvent(e);
        return;
      }
    }
  }
}
/* 0x548750, the alloc handler of the master exam payment event 0x55 (he_RunMasterExamPay): the due (end) clock is
   the start clock 3 hours ahead */

void he_AllocMasterExamPay(AIJOB *e) {

  e->end = e->start;
  gm_AddTime(&e->end, 3, 0, 0);
}
/* 0x548790, a Ghidra miss: the run handler of the master exam payment event 0x55: stage -1 / -2 releases its slot
   and frees it; once started, stage 0 keeps the fee (5% of the character's worth), opens the message box
   "Berufe\Messagebox_Meisterpruefung" with the news 0x10b4 and goes to stage 1 (no box: frees the event); stage 1
   ends the event past its end time, else waits for the answer: yes (0) moves the fee between the player's character
   and the event's character (cm_SendMoveGoodsUnchecked) and posts the AI message 0x56 (flags 0x11) with it to the
   character, no (1) only ends it */

void he_RunMasterExamPay(AIJOB *e) {
  AIMSG m;
  int fee;

  if (e->stage == -1 || e->stage == -2) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  if (gm_CompareTime(&ai_Time, &e->start) == -1)
    return;
  switch (e->stage) {
  case 0:
    fee = (int)(gm_GetWorth(e->chr) * 0.05f);
    e->examPayFee = fee;
    if (e->slot == 0)
      he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_SetForm(e->slot->win, 0);
    io_PrintText((intptr_t)"$C");
    io_PrintText(0x10b4, e->chr, fee);
    e->stage = 1;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm == e->slot->win && d2_ClickedId != -1) {
      if (d2_ClickedId == 0) {
        memset(&m, 0, sizeof(m));
        fee = e->examPayFee;
        cm_SendMoveGoodsUnchecked(ai_PlayerChar->netId, ai_Chars[e->chr].netId,
                                  ai_OwnPlayer, fee);
        m.type = 0x56;
        m.fromId = -1;
        m.to = ai_Chars[e->chr].netId;
        m.flags = 0x11;
        m.fee.what = 4;
        m.fee.amount = fee;
        cm_SendLongMessage(&m);
        he_ReleaseSlot(e);
        he_FreeEvent(e);
        return;
      }
      if (d2_ClickedId == 1) {
        he_ReleaseSlot(e);
        he_FreeEvent(e);
        return;
      }
    }
  }
}
/* 0x5489b0, a Ghidra miss: the run handler of the payment event 0x56: stage -2 frees it; at stage 0 it counts
   wait down, then rolls random(0x100) against the character's first skill / 2 + 64: below it the character gets
   twice the amount (the news 0x10b5), else half of it (the news 0x10b6), both by cm_SendMoveGoods from the own
   player; then frees the event */

void he_RunPayment(AIJOB *e) {
  AIJOB *p = e;
  char text[0x418];
  int r;

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0)
    return;
  if (p->paymentWait > 0) {
    p->paymentWait--;
    return;
  }
  r = util_Random(0x100);
  if (r < ai_Chars[e->chr].skills[0] * 0.5 + 64.0) {
    txt_Format(text, 0x10b5, p->paymentAmount * 2);
    he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0, 0x5ff,
                (char *)0);
    cm_SendMoveGoods(ai_Chars[e->chr].netId, -1, ai_OwnPlayer,
                     p->paymentAmount * 2);
  } else {
    txt_Format(text, 0x10b6, (int)(p->paymentAmount * 0.5f));
    he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0, 0x5ff,
                (char *)0);
    cm_SendMoveGoods(ai_Chars[e->chr].netId, -1, ai_OwnPlayer,
                     (int)(p->paymentAmount * 0.5f));
  }
  he_FreeEvent(e);
}
/* 0x548b70, the alloc handler shared by the store sale event 0x57 (he_RunStoreSale) and the building decay event
   0x58 (he_RunBuildingDecay): the due clock is the start clock, and on half of the calls it frees the event at once */

void he_AllocRandomHalf(AIJOB *e) {

  e->end = e->start;
  if ((short)util_Random(2) != 0)
    he_FreeEvent(e);
}
/* 0x548bb0, a Ghidra miss: the run handler of event 0x57: stage -2 frees it; at stage 0 it collects up to 16 of
   the character's buildings (owner query, gm_BuildQuery key 4) of class 1 or of type kind 9, picks one at random
   and sells a quarter (at least 1) of every good in its store object (0x2a, else 0x116) for the own player
   (cm_SendExSellObject, logged as "cm_RequestSellObjekt(..)" into a buffer nobody reads), adding up their prices;
   a character of kind 6 with a total gets the news 0x10b7 (the building, the total) in a quick-jump box; then frees
   the event */

void he_RunStoreSale(AIJOB *e) {
  char text[0x418];
  char log[0x400];
  AIBLD *sel[16];
  int n = 0, total = 0, amount;
  AIBLD *b;
  AIBTYPE *t;
  AIOBJ *store;
  AIOBJ *good;

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0)
    return;
  b = gm_BuildQuery(1, 4, e->chr);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  do {
    if (n >= 16)
      break;
    t = &ai_BTypes[b->type];
    if (gm_BuildingClass(b->type) == 1 || t->kind == 9)
      sel[n++] = b;
  } while ((b = gm_BuildNext()) != 0);
  if (n == 0) {
    he_FreeEvent(e);
    return;
  }
  b = sel[util_Random(n)];
  if (b != 0) {
    store = gm_Query(b->objList, 2, 6, 0, 0x2a);
    if (store == 0)
      store = gm_Query(b->objList, 2, 6, 0, 0x116);
    if (store != 0) {
      for (good = gm_Query(store->list, 1, 5); good != 0;
           good = gm_QueryNext()) {
        amount = (int)(gm_ListAmount(store, good) * 0.25f);
        if (amount < 1)
          amount = 1;
        sprintf(log, "cm_RequestSellObjekt(%i, %i, %i, %i, %i, %i)", -1,
                store->objId, good->id, amount, ai_OwnPlayer, 0);
        cm_SendExSellObject(-1, store->objId, good->id, amount, ai_OwnPlayer,
                            0);
        total = (int)(gm_GoodsPrice(good->id, ai_OwnPlayer) * amount + total);
      }
    }
  }
  if (ai_Chars[e->chr].kind == 6 && total != 0) {
    txt_Format(text, 0x10b7, b, total);
    he_MessageBoxQuickjump(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text,
                           0, 0x5ec, b->id, -1, 0, (char *)0);
  }
  he_FreeEvent(e);
}
/* 0x548de0, a Ghidra miss: the run handler of event 0x58: stage -2 frees it; at stage 0 it collects up to 16 of
   the character's buildings (gm_BuildQuery key 4) of class 6, picks one at random and lowers its state by 50
   (gm_ChangeBuildingState); a character of kind 6 gets the news 0x10b8 (the building) in a quick-jump box; then
   frees the event */

void he_RunBuildingDecay(AIJOB *e) {
  char text[0x418];
  AIBLD *sel[16];
  int n = 0;
  AIBLD *b;

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0)
    return;
  b = gm_BuildQuery(1, 4, e->chr);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  do {
    if (n >= 16)
      break;
    if (gm_BuildingClass(b->type) == 6)
      sel[n++] = b;
  } while ((b = gm_BuildNext()) != 0);
  if (n == 0) {
    he_FreeEvent(e);
    return;
  }
  b = sel[util_Random(n)];
  if (b != 0)
    gm_ChangeBuildingState(b, -50);
  if (ai_Chars[e->chr].kind == 6) {
    txt_Format(text, 0x10b8, b);
    he_MessageBoxQuickjump(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text,
                           0, 0x5ec, b->id, -1, 0, (char *)0);
  }
  he_FreeEvent(e);
}
/* 0x548ef0, the alloc handler of the repost event 0x5a (he_RunRepostEvent): the due clock is the game time 0x60
   hours (four days) ahead */

void he_AllocRepostEvent(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 0x60, 0, 0);
}
/* 0x548f30, the run handler of the HE event type 0x5a, a one-shot event without the pending-slot check of
   0x548230: a freed state (-2) ends it, a negative one frees it, and in state 0 with opts bit 2 it is posted
   again two minutes later (the end time = the clock now, cm_SendExSetHE) */

void he_RunRepostEvent(AIJOB *e) {
  int st = e->stage;

  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    if ((e->opts & 2) == 0)
      return;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  he_FreeEvent(e);
}
/* 0x548fa0, the run handler of the fine event 0x5b (the trial's sentence 1, gv_PassSentence: 3% of the character's
   worth): a stage of -2 or below ends it, a negative one frees it, and at stage 0 it takes the amount +0xac from the
   event's character (cm_SendMoveGoods with -1 as the destination, under the own player) and counts one payment
   down; with payments left it is posted again 0x18 hours on, else it is freed */

void he_RunFinePayment(AIJOB *e) {
  int st = e->stage;

  if (st >= -2) {
    if (st >= 0) {
      if (st != 0)
        return;
      cm_SendMoveGoods(-1, ai_Chars[e->chr].netId, ai_OwnPlayer,
                       e->punishAmount);
      e->punishDays = e->punishDays - 1;
      if (e->punishDays != 0) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0x18, 0, 0);
        return;
      }
    }
    he_FreeEvent(e);
  }
}
/* 0x549040, the alloc handler of the trial-punishment events 0x5b and 0x5c (he_RunFinePayment,
   he_RunPilloryPunishment): the due clock +0x52 is the clock now, five minutes on */

void he_AllocPunishment(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 5, 0);
}
/* 0x549080, the run handler of the pillory-punishment event 0x5c (the trial's sentences 0 and 2, gv_PassSentence):
   a stage of -2 or below ends it, a negative one frees it, and at stage 0 it registers an AP event of the event's
   character (e->chr) named TXT_PILLORY_PUNISHMENT, the negated amount +0xac as its income, counts one payment down
   and, with payments left, posts the event again 0x18 hours on, else frees it */

void he_RunPilloryPunishment(AIJOB *e) {
  int st = e->stage;

  if (st >= -2) {
    if (st >= 0) {
      if (st != 0)
        return;
      he_AddApEvent(e->chr, txt_Ptrs[TXT_PILLORY_PUNISHMENT], -e->punishAmount,
                    0);
      e->punishDays = e->punishDays - 1;
      if (e->punishDays != 0) {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0x18, 0, 0);
        return;
      }
    }
    he_FreeEvent(e);
  }
}
/* 0x549110, the alloc handler of the offspring event 0x5d (he_RunOffspring): the event starts at stage 0 with no
   chance built up */

void he_AllocOffspring(AIJOB *e) {
  AIJOB *s = e;

  e->stage = 0;
  s->offspringChance = 0;
}
/* 0x549120, a Ghidra miss (disassembled): the run handler of the offspring event 0x5d: frees it when the character or
   its partner (relatives[0]) is dead or at stage -2. Stage 0 counts the living children (relatives[3..7]); with all
   five it frees the event, else f = ((5 - n) * 0.2)^2 and a roll random + (1 - f) < f * chance moves it to stage 1
   (one year on), otherwise chance grows by f * 0.1. Stage 1 waits three runs (a year each); then a character of kind
   6 gets a party of kind 7 (flags 0x20) with its partner half an hour from now, and cm_SendCreateCharacter creates the
   child (the two parents in an order by the character's sex, the home building's id or -1); back to stage 0, 1 .. 8 years on */

void he_RunOffspring(AIJOB *e) {
  AIJOB *s = e;
  int home = -1;
  AICHAR *c, *partner;
  int i, n;
  float f, odds;

  c = &ai_Chars[e->chr];
  partner = gm_FindChar(c->relatives[0]);
  if (partner == 0 || partner->health == 0 || c->health == 0 ||
      e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0) {
    if (e->stage == 1) {
      if (s->offspringChance >= 3.0) {
        if (c->kind == 6) {
          G28REC party;

          memset(&party, 0, sizeof(party));
          party.host = c->netId;
          party.members[0] = c->netId;
          party.members[1] = partner->netId;
          party.kind = 7;
          party.flags = 0x20;
          party.thing = -1;
          party.used = 2;
          party.time = ai_Time;
          gm_AddTime(&party.time, 0, 0x1e, 0);
          cm_SendNewParty(&party);
        }
        s->offspringChance = 0;
        if (c->bld2 != 0)
          home = c->bld2->id;
        if (c->sex == 0)
          cm_SendCreateCharacter(8, c->netId, partner->netId, 0, home, 0, 0, 2);
        else
          cm_SendCreateCharacter(8, partner->netId, c->netId, 0, home, 0, 0, 2);
        e->stage = 0;
        e->end.year += util_Random(8) + 1;
      } else {
        s->offspringChance += 1.0;
        e->end.year++;
      }
    }
  } else {
    n = 0;
    for (i = 0; i < 5; i++) {
      if (c->relatives[3 + i] != -1 && gm_FindChar(c->relatives[3 + i]) != 0)
        n++;
    }
    if (n == 5) {
      he_FreeEvent(e);
      return;
    }
    f = (5.0f - n) * 0.2f;
    f = f * f;
    odds = f * s->offspringChance;
    if (util_RandomF() + (1.0f - f) < odds) {
      e->stage = 1;
      e->end.year++;
      s->offspringChance = 0;
    } else
      s->offspringChance += f * 0.1;
  }
}
/* 0x5493a0, the alloc handler of the trial event (type 0x5e, the run handler 0x549430): it looks for another
   running 0x5e event of its player (he_FindEvent (2, 0, 0x5e, 2, chr), skipping itself); none: the event starts
   in state 0 with unkb8 cleared and is posted, else it ends at the clock now (posted as failed) */

void he_StartTrialEvent(AIJOB *e) {
  AIJOB *found = he_FindEvent(2, 0, 0x5e, 2, e->chr);

  if (found != 0) {
    do {
      if (found == e) {
        found = he_NextEvent();
      } else {
        e->end = ai_Time;
        e->exSlot = cm_SendExSetHE(-1, e);
        return;
      }
    } while (found != 0);
  }
  e->stage = 0;
  e->trialRounds = 0;
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x549430, a Ghidra miss (disassembled): the run handler of the trial event 0x5e (the character e->chr's trial
   with the teacher, a character found by its netId): stage -2 / -1 frees it; nothing while it is not started or
   its last post is not settled. Stage 0 holds a round: the news 0x1a9b, a day on, the round's cost to the
   teacher's AP events; the third round posts the event to stage 1. Stage 1 raises the two abilities of the job's
   title group (gm_JobSlots) by 16 .. 31 each, gives the character the job and tells the teacher (the news 0x1a9c
   with the job title, the female forms 0x5f on); without the teacher it ends now */

void he_RunTrialEvent(AIJOB *e) {
  AIJOB *t = e;
  char text[0x100];
  AICHAR *c, *teacher;
  int skillA, skillB;
  unsigned char raise;

  if (e->stage == -2 || e->stage == -1) {
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
    c = &ai_Chars[e->chr];
    teacher = gm_FindChar(t->trialTeacher);
    if (teacher == 0) {
      e->end = ai_Time;
      cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, 0x1a9b, c->id);
    e->trialRounds++;
    e->end.hour += 0x18;
    cm_SendExSetHE(e->trialRounds >= 3, e);
    he_AddApEvent(teacher->id, text, 0, -t->trialCost);
    return;
  case 1:
    c = &ai_Chars[e->chr];
    gm_JobSlots(gm_TitleGroup(t->trialJob), &skillA, &skillB);
    cm_BeginFieldBlock(c, c->netId);
    raise = (unsigned char)(util_Random(0x10) + 0x10);
    cm_AddFieldValues(1, 1, skillA + 0x80, &raise); /* 0x80: AICHAR.skills */
    raise = (unsigned char)(util_Random(0x10) + 0x10);
    cm_AddFieldValues(1, 1, skillB + 0x80, &raise);
    cm_SendFieldDeltas();
    cm_SendSetJob(c->netId, t->trialJob);
    teacher = gm_FindChar(t->trialTeacher);
    if (teacher == 0) {
      e->end = ai_Time;
      cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, 0x1a9c, c->id,
               (c->sex != 0 ? 0x18f : 0x130) + t->trialJob);
    he_ShowNews(teacher->netId, teacher->netId, text, 0, 0x5f4, (char *)0);
    e->end = ai_Time;
    cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x5496f0, the alloc handler of the next trial step event (type 0x5f, the run handler 0x549770), like the
   trial's own alloc handler 0x5493a0 without the posting: it looks for another running 0x5f event of its player
   (he_FindEvent (2, 0, 0x5f, 2, chr), skipping itself); none: the event starts in state 0 with its step count
   cleared, else it ends at the clock now */

void he_StartNextTrialStep(AIJOB *e) {
  AIJOB *found = he_FindEvent(2, 0, 0x5f, 2, e->chr);

  if (found != 0) {
    do {
      if (found == e) {
        found = he_NextEvent();
      } else {
        e->end = ai_Time;
        e->exSlot = cm_SendExSetHE(-1, e);
        return;
      }
    } while (found != 0);
  }
  e->stage = 0;
  e->trialSteps = 0;
}
/* 0x549770, a Ghidra miss (disassembled): the run handler of the next trial step event 0x5f (the character e->chr
   taught by the teacher, a character found by its netId): stage -2 / -1 frees it; nothing while it is not started
   or its last post is not settled. Stage 0 is a step: both skills (ai_ApplyTrialStep) raised, the news 0x1a9e, a
   day on, the step's cost to the teacher's AP events; the fifth step moves it to stage 1. Stage 1 tells the
   teacher (the news 0x1a9f), counts the course in the teacher's player record and ends the event now; without
   the teacher it ends now */

void he_RunTrialSteps(AIJOB *e) {
  AIJOB *t = e;
  char text[0x100];
  AICHAR *c, *teacher;
  AIFIN *fin;

  if (e->stage == -2 || e->stage == -1) {
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
    c = &ai_Chars[e->chr];
    teacher = gm_FindChar(t->trialStepTeacher);
    if (teacher == 0) {
      e->end = ai_Time;
      cm_SendExSetHE(-1, e);
      return;
    }
    ai_ApplyTrialStep(c, t->trialStepSkill[0]);
    ai_ApplyTrialStep(c, t->trialStepSkill[1]);
    txt_Format(text, 0x1a9e, c->id);
    e->trialSteps++;
    e->stage = e->trialSteps >= 5;
    e->end.hour += 0x18;
    he_AddApEvent(teacher->id, text, 0, -t->trialStepCost);
    return;
  case 1:
    c = &ai_Chars[e->chr];
    teacher = gm_FindChar(t->trialStepTeacher);
    if (teacher == 0) {
      e->end = ai_Time;
      cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, 0x1a9f, c->id);
    he_ShowNews(teacher->netId, teacher->netId, text, 0, 0x5f4, (char *)0);
    fin = gm_PlayerRecord(teacher);
    if (fin != 0)
      fin->taught++;
    e->end = ai_Time;
    cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x549970, a Ghidra miss (disassembled): the alloc handler of the training event 0x60: frees it when the trained
   skill of its character is at the cap 252 already, or when the character has another 0x60 event running
   (he_FindEvent (2, 2, chr, 0, 0x60), skipping itself); else it raises the skill by 0x15 less a random part of
   2 * (skill / 42 + 3), starts at stage 0, due 5 hours from now (a second with gm_AllowAll), started now */

void he_StartTraining(AIJOB *e) {
  AIJOB *t = e;
  AIJOB *found;

  if ((float)ai_Chars[e->chr].skills[t->trainSkill] >= 252.0f) {
    he_FreeEvent(e);
    return;
  }
  found = he_FindEvent(2, 2, e->chr, 0, 0x60);
  if (found != 0) {
    do {
      if (found != e) {
        he_FreeEvent(e);
        return;
      }
      found = he_NextEvent();
    } while (found != 0);
  }
  t->trainRange = (unsigned char)((int)(ai_Chars[e->chr].skills[t->trainSkill] *
                                            (1.0f / 42.0f) +
                                        1.0f) +
                                  2) *
                  2;
  t->trainBase = 0x15;
  e->stage = 0;
  e->end = ai_Time;
  if (gm_AllowAll != 0)
    gm_AddTime(&e->end, 0, 0, 1);
  else
    gm_AddTime(&e->end, 5, 0, 0);
  e->start = ai_Time;
}
/* 0x549aa0, the run handler of the training event 0x60: stage -2 frees it; at stage 0 the skill rises by base less
   a random part of range, at most to the cap 252 (cm_SendAddSkill). For a player character (kind 6) a new level
   (the value / 42) posts the AI message 0x6a (flags 9) with the skill and its level, else the news 0x16f2 with
   the skill's name 0x16f3 + skill and the sound "tal_0<skill>"; then the skills' message (cm_SendSkillsChanged)
   and the event is freed */

void he_RunTraining(AIJOB *e) {
  AIJOB *t = e;
  char text[0x800];
  char sound[0x20];
  AIMSG msg;
  AICHAR *c;
  int rise, skill, cur, level;

  switch (e->stage) {
  case -2:
    he_FreeEvent(e);
    return;
  case 0:
    rise = t->trainBase - util_Random(t->trainRange);
    c = &ai_Chars[e->chr];
    skill = t->trainSkill;
    cur = c->skills[skill];
    if ((float)(cur + rise) > 252.0f)
      rise = (int)(252.0f - (float)cur);
    cm_SendAddSkill(c->netId, skill, rise);
    if (c->kind == 6) {
      skill = t->trainSkill;
      cur = c->skills[skill];
      level = (int)((cur + rise) * (1.0f / 42.0f));
      if (level > (int)(cur * (1.0f / 42.0f))) {
        MEM_ZERO(&msg, sizeof(msg));
        msg.type = 0x6a;
        msg.to = c->netId;
        msg.fromId = -1;
        msg.time = ai_Time;
        msg.flags = 9;
        msg.skillLevel.skill = t->trainSkill;
        msg.skillLevel.level = level;
        cm_SendLongMessage(&msg);
      } else {
        sprintf(sound, "tal_0%i", skill);
        txt_Format(text, (intptr_t)"%s%s", 0x16f2, t->trainSkill + 0x16f3);
        he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                    0x5fd, sound);
      }
    }
    cm_SendSkillsChanged(c->netId);
    he_FreeEvent(e);
  }
}
/* 0x549ce0, begins the plague event 0x59 (its run handler 0x54a020 calls it at stage 5): from a random one of the
   0x100 buildings on, the first whose type is of kind 7 starts it: a random walk index and step, the AI message
   0x78 (flags 9) about it to every player character (kind 6 / 7), four carriers ("PEST", kind 0xe, job 0x12)
   created at it, it is their home; due a minute from now, posted at stage 0, and the plague news
   (ai_PlagueNews). Without such a building the event is posted as failed */

void he_BeginPlague(AIJOB *e) {
  AIJOB *p = e;
  AIMSG msg;
  AIBLD *b;
  int n = 0x100;
  int i;

  e->end = ai_Time;
  i = util_Random(0x100);
  do {
    b = &ai_Blds[i];
    if (ai_BTypes[b->type].kind == 7) {
      p->plagueWalk = util_Random(0x100);
      p->plagueStep = ai_RandomStrides[util_Random(0x10)];
      D3_ZERO(&msg, sizeof(msg));
      msg.plague.bld = b->id;
      msg.plague.target = b->id;
      msg.plague.next = -1;
      msg.plague.walk = p->plagueWalk;
      msg.plague.step = p->plagueStep;
      msg.plague.left = p->plagueLeft;
      msg.fromId = -1;
      msg.type = 0x78;
      msg.flags = 9;
      msg.time = ai_Time;
      for (i = 0; i < 768; i++) {
        if (ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7) {
          msg.to = ai_Chars[i].netId;
          cm_SendLongMessage(&msg);
        }
      }
      p->plagueCarriers[0] =
          cm_SendSpawnCharacter(0xe, b->id, -1, 0x12, 0, 0, "PEST");
      p->plagueCarriers[1] =
          cm_SendSpawnCharacter(0xe, b->id, -1, 0x12, 0, 0, "PEST");
      p->plagueCarriers[2] =
          cm_SendSpawnCharacter(0xe, b->id, -1, 0x12, 0, 0, "PEST");
      p->plagueCarriers[3] =
          cm_SendSpawnCharacter(0xe, b->id, -1, 0x12, 0, 0, "PEST");
      p->plagueHome = b->id;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(0, e);
      ai_PlagueNews();
      return;
    }
    n--;
    i = (i + 1) % 0x100;
  } while (n != 0);
  e->exSlot = cm_SendExSetHE(-1, e);
}

void ai_PlagueMessage(struct AICHAR *c, void *bld);
float util_RandomF2();
/* 0x549f70, the alloc handler of the plague event 0x59 ("Pest", he_RunPlague): opts bit 2 leaves it alone; another
   running 0x59 event (skipping itself) ends it at the clock now, posted as failed (cm_SendExSetHE -1, its slot
   kept); else it starts at stage 5 with the due clock at its start clock, its slot -1, and is posted (5) */

void he_StartPlague(AIJOB *e) {
  AIJOB *found;

  if ((e->opts & 4) != 0)
    return;
  found = he_FindEvent(1, 0, 0x59);
  while (found != 0) {
    if (found != e) {
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    found = he_NextEvent();
  }
  e->stage = 5;
  e->end = e->start;
  e->exSlot = -1;
  cm_SendExSetHE(5, e);
}
/* 0x54a020, a Ghidra miss (disassembled; 1720 B): the run handler of the plague event 0x59 ("Pest"): stage -1 / -2
   stops and kills the four carriers when the event is freed with the option 2, and frees it; nothing while it is
   not started or its last post is not settled. Stage 5 begins it (he_BeginPlague). Stage 0 turns the carriers'
   creation slots into their ids (-1: not created). Stage 1 walks the 0x100 buildings by the step from the walk
   index to the next owned building of a kind in the mask (kinds 4, 8, 14, 18 .. 22, 31, 32; the debug text
   "EvtPest: next target = %G") and sends the carriers there ("Pest"); none: it ends. Stage 2 waits until every
   carrier is at the target's door, then infects: of the target's owner's building up to 16 characters of kind 0 in
   it, a random share of them (at least one) and with 1 in 8 a character of kind 1 in it catch the plague
   (gm_CatchPlague), the owner with 1 in 256; any infection posts the plague message, and each value below 1000
   makes the character ill (he_CharIllness, illness 1). While left counts down it goes on to the next target,
   else the carriers go home. Stage 3 waits until every carrier is home, then the event ends */

void he_RunPlague(AIJOB *e) {
  AIJOB *p = e;
  AIBLD *o;
  AIBTYPE *bt;
  AICHAR *c, *owner, *other;
  int *carrier;
  unsigned lo, hi;
  int i, n, k, cnt, m, any;
  AICHAR *r;
  float a, otherValue;
  float value[16];
  int ids[16];
  char text[0x200];

  if (e->stage == -1 || e->stage == -2) {
    if (e->opts & 2) {
      carrier = p->plagueCarriers;
      for (i = 4; i != 0; i--) {
        c = gm_FindChar(*carrier);
        if (c != 0) {
          cm_SendChrStop(c->netId);
          cm_SendKillCharacter(c->netId, 1);
        }
        carrier++;
      }
    }
    he_FreeEvent(e);
    return;
  }
  if (e->opts & 4)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  if (e->stage == 5)
    he_BeginPlague(e);
  switch (e->stage) {
  case 0:
    carrier = p->plagueCarriers;
    for (i = 4; i != 0; i--) {
      if (cm_GetSlotState(*carrier) == 1 &&
          (r = cm_GetSlotValue(*carrier)) != 0)
        *carrier = r->netId;
      else
        *carrier = -1;
      carrier++;
    }
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(1, e);
    break;
  case 1:
    n = 0x100;
    k = p->plagueWalk;
    do {
      o = &ai_Blds[k];
      hi = 0;
      bt = &ai_BTypes[o->type];
      lo = 0;
      if ((unsigned char)bt->kind > 0x1f)
        hi = 1 << ((unsigned char)bt->kind - 0x20);
      else
        lo = 1 << (unsigned char)bt->kind;
      if (o->owner != 0xffff && ((lo & 0x807c4110) != 0 || (hi & 1) != 0))
        break;
      o = 0;
      n--;
      k = (k + p->plagueStep) % 0x100;
    } while (n != 0);
    p->plagueWalk = (p->plagueStep + k) % 0x100;
    if (o == 0) {
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, (intptr_t)"EvtPest: next target = %G", o);
    n = 0;
    carrier = p->plagueCarriers;
    for (i = 4; i != 0; i--) {
      c = gm_FindChar(*carrier);
      if (c != 0) {
        cm_SendChrStop(c->netId);
        cm_SendChrGotoBuilding(c->netId, o->id, -1, 0, 1, "Pest");
        n++;
      }
      carrier++;
    }
    gm_AddTime(&e->end, 0, n > 0 ? 5 : 0x14, 0);
    p->plagueTarget = o->id;
    e->exSlot = cm_SendExSetHE(2, e);
    break;
  case 2:
    gm_FindById(&o, 0, 0, p->plagueTarget);
    gm_AddTime(&e->end, 0, 5, 0);
    if (o == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    for (i = 0; i < 4; i++) {
      c = gm_FindChar(p->plagueCarriers[i]);
      if (c != 0 && sv_IsAtDoor(c, o) == 0) {
        e->stage = 2;
        gm_AddTime(&e->end, 0, 5, 0);
        e->exSlot = cm_SendExSetHE(2, e);
        return;
      }
    }
    if (o->owner != 0xffff) {
      any = 0;
      other = 0;
      otherValue = 1000.0f;
      owner = &ai_Chars[o->owner];
      memset(ids, -1, sizeof(ids));
      cnt = 0;
      for (k = 0; k < 768; k++) {
        if (cnt >= 16)
          break;
        if (ai_Chars[k].kind == 0 && ai_Chars[k].bld == o) {
          value[cnt] = 1000.0f;
          ids[cnt] = k;
          cnt++;
        } else if (ai_Chars[k].kind == 1 && ai_Chars[k].bld == o)
          other = &ai_Chars[k];
      }
      if (cnt != 0) {
        a = util_RandomF2();
        if (a > 0.8f)
          a = 1.0f;
        a = a * cnt;
        if (!(a > 1.0f))
          a = 1.0f;
        m = (int)a;
        for (i = 0; i < m; i++) {
          any = 1;
          value[i] = gm_CatchPlague(&ai_Chars[ids[i]]);
        }
        if (other != 0 && util_Random(8) == 0) {
          otherValue = gm_CatchPlague(other);
          any = 1;
        }
        if (util_Random(0x100) == 0)
          gm_CatchPlague(owner);
        if (any)
          ai_PlagueMessage(owner, o);
        for (i = 0; i < m; i++) {
          if (value[i] < 1000.0f)
            he_CharIllness(e, &ai_Chars[ids[i]], owner, o, 1, value[i]);
        }
        if (otherValue < 1000.0f)
          he_CharIllness(e, other, owner, o, 1, otherValue);
      }
    }
    if (--p->plagueLeft <= 0) {
      gm_FindById(&o, 0, 0, p->plagueHome);
      if (o == 0) {
        e->exSlot = cm_SendExSetHE(-1, e);
        return;
      }
      n = 0;
      carrier = p->plagueCarriers;
      for (i = 4; i != 0; i--) {
        c = gm_FindChar(*carrier);
        if (c != 0) {
          cm_SendChrStop(c->netId);
          cm_SendChrGotoBuilding(c->netId, o->id, -1, 0, 1, "Pest");
          n++;
        }
        carrier++;
      }
      gm_AddTime(&e->end, 0, n > 0 ? 1 : 10, 0);
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(1, e);
    break;
  case 3:
    gm_AddTime(&e->end, 0, 5, 0);
    gm_FindById(&o, 0, 0, p->plagueHome);
    if (o == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    for (i = 0; i < 4; i++) {
      c = gm_FindChar(p->plagueCarriers[i]);
      if (c != 0 && sv_IsAtDoor(c, o) == 0) {
        e->stage = 3;
        gm_AddTime(&e->end, 0, 5, 0);
        e->exSlot = cm_SendExSetHE(3, e);
        return;
      }
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    break;
  }
}
/* 0x54a6f0, a Ghidra miss: the alloc handler of the pickpocket gang event 0x61: counts the members (the ids[]
   not -1); without any it frees the event, else no targets yet, the first member next, started now and due two
   minutes from now */

void he_StartGang(AIJOB *e) {
  AIJOB *g = e;
  int *id;
  int i;

  g->gangMembers = 0;
  id = e->ids;
  for (i = 6; i != 0; i--) {
    if (*id++ != -1)
      g->gangMembers++;
  }
  if (g->gangMembers == 0) {
    he_FreeEvent(e);
    return;
  }
  for (i = 0; i < (int)(sizeof(g->gangTargets) / sizeof(g->gangTargets[0]));
       i++)
    g->gangTargets[i] = -1;
  g->gangNext = 0;
  g->gangStart = ai_Time;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 2, 0);
}

/* 0x54a7b0, a Ghidra miss (disassembled; 1646 B): the run handler of the pickpocket gang event 0x61 ("Taschendieb";
   the gang is ids[0..5], its home building e->from, whose owner is the leader when it has one). Freed (stage -2),
   without a leader or 0x1e0 minutes after the start it goes to stage 1, else it takes the next member found (none:
   back to the first, wait) and is due in six minutes. Stage 1 calls the gang home: each member's take (3 .. 6
   rolls of its skill 2's level) adds up, the leader gets it (gm_PlayerFactor, + 1% per skill point of the home
   building), the building's round sum and the leader's player record count it, and a leader of kind 6 without a
   master with the flag 1 gets the news 0x19f4; then the event is freed. Stage 0 lets an idle member steal at its
   target: of up to 32 random characters (alive, kind below 10, not of title 1 / 2, not the leader) the first
   whose goods are worth the take; it notices the thief when its skill 2 beats the thief's by more than a roll of
   0x7e (the news 0x19f3), else it loses the take (the news 0x19f2); then the member walks to a random building of
   a random other kind (10 / 5 / 7 / 0x16 / 0xf, kind 10 when there is none) */

void he_RunGang(AIJOB *e) {
  AIJOB *g = e;
  AICHAR *member, *leader, *c, *victim;
  AIBLD *s, *b, *o;
  AIBTYPE *bt;
  AIOBJ *room;
  AIFIN *fin;
  int dt, idx, i, k, n, r, lvl, loot, sum, v, amt, tries, kind, diff;
  union {
    int kinds[5];   /* the building kinds to pick from */
    AIBLD *blds[5]; /* then the buildings of the kind (the same slots) */
  } pick;
  char text[0x400];

  dt = gm_MinutesBetween(&g->gangStart, &ai_Time);
  idx = 0;
  member = 0;
  leader = gm_FindChar(g->gangLeader);
  s = gm_BuildQuery(1, 1, e->from);
  if (s != 0 && s->owner != 0xffff)
    leader = &ai_Chars[s->owner];
  if (e->stage == -2 || leader == 0) {
    e->stage = 1;
  } else {
    member = 0;
    for (;;) {
      if (g->gangNext < 6) {
        member = gm_FindChar(e->ids[g->gangNext]);
        idx = g->gangNext;
        g->gangNext++;
        if (member == 0)
          continue;
      } else if (member == 0) {
        g->gangNext = 0;
        return;
      }
      break;
    }
    e->stage = dt > 0x1e0;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 6, 0);
    g->gangNext = g->gangNext % 6;
  }
  switch (e->stage) {
  case 0:
    if (member == 0 || member->scene->actions != 0)
      return;
    b = gm_BuildQuery(1, 1, g->gangTargets[idx]);
    n = 0;
    pick.kinds[0] = 10;
    pick.kinds[1] = 5;
    pick.kinds[2] = 7;
    pick.kinds[3] = 0x16;
    pick.kinds[4] = 0xf;
    kind = pick.kinds[util_Random(5)];
    if (b != 0) {
      lvl = (int)(member->skills[2] * (1.0f / 42.0f) + 1.0f);
      loot = (util_Random((lvl + 1) * lvl) + lvl * 2) * 2;
      v = gm_PlayerFactor(loot, ai_OwnPlayer);
      if (g->gangMembers != 0) {
        victim = 0;
        tries = 0x20;
        do {
          r = util_Random(0x300);
          tries--;
          if (ai_Chars[r].id != 0xffff && ai_Chars[r].health > 0 &&
              ai_Chars[r].kind < 10 && ai_Chars[r].title != 2 &&
              ai_Chars[r].title != 1 && ai_Chars[r].netId != leader->netId) {
            victim = &ai_Chars[r];
            if (gm_GetGoodsValue(victim) < v)
              victim = 0;
          }
        } while (victim == 0 && tries != 0);
        g->gangMembers--;
        if (victim != 0) {
          diff = victim->skills[2] - member->skills[2];
          if (diff > util_Random(0x7e)) {
            if (victim->kind == 6 || victim->kind == 7) {
              txt_Format(text, 0x19f3);
              he_ShowNews(victim->netId, victim->netId, text, 0, 0x5f0,
                          (char *)0);
            }
          } else {
            cm_SendMoveGoodsUnchecked(-1, victim->netId, ai_OwnPlayer, v);
            if (victim->kind == 6 || victim->kind == 7) {
              txt_Format(text, 0x19f2, v);
              he_ShowNews(victim->netId, victim->netId, text, 0, 0x5f0,
                          "_NACHRICHTEN_HS_19");
            }
          }
        }
      }
      bt = &ai_BTypes[b->type];
      do
        kind = pick.kinds[util_Random(5)];
      while ((unsigned char)bt->kind == kind);
    }
    o = gm_BuildQuery(1, 5, kind);
    if (o == 0)
      o = gm_BuildQuery(1, 5, 10);
    else {
      do {
        if (n >= 4)
          break;
        pick.blds[n++] = o;
      } while ((o = gm_BuildNext()) != 0);
      o = pick.blds[util_Random(n)];
    }
    sv_MoveToGroup(o, 0, member->id, e);
    cm_SendChrStop(member->netId);
    cm_SendChrGotoBuilding(member->netId, o->id, -1, 0, 1, "Taschendieb");
    g->gangTargets[idx] = o->id;
    return;
  case 1:
    s = gm_BuildQuery(1, 1, e->from);
    sum = 0;
    if (s != 0 && leader != 0) {
      room = gm_GetGebaeudeHauptraum(s);
      for (i = 0; i < 6; i++) {
        c = gm_FindChar(e->ids[i]);
        if (c != 0) {
          lvl = (int)(c->skills[2] * (1.0f / 42.0f) + 1.0f);
          for (k = util_Random(4) + 3; k > 0; k--)
            sum += (util_Random((lvl + 1) * lvl) + lvl * 2) * 2;
          cm_SendChrStop(c->netId);
          cm_SendChrGotoBuilding(c->netId, s->id, room->objId, 0, 0,
                                 "Taschendieb");
          sv_MoveToGroup(0, 0, c->id, 0);
        }
      }
      sum = gm_PlayerFactor(sum, ai_OwnPlayer);
      amt = (int)((gm_BuildingSkill(s, 1, 1) * 0.01f + 1.0f) * sum);
      cm_SendMoveGoodsUnchecked(leader->netId, -1, ai_OwnPlayer, amt);
      s->roundSums[0] += amt;
      if (leader->kind == 6) {
        fin = gm_PlayerRecord(leader);
        if (fin != 0)
          fin->gangTakings += amt;
        c = gm_FindCharacterByMaster(s);
        if (c == 0 || (c->flags1b4 & 1) == 0) {
          txt_Format(text, 0x19f4, amt);
          he_ShowNews(leader->netId, leader->netId, text, 0, 0x5f0,
                      ch_EmptyName);
        }
      }
    }
    he_FreeEvent(e);
    return;
  }
}

int ls_GetLanguage();

/* 0x54ae20, the alloc handler of the protection-ask event 0x63 (he_RunProtectionAsk): the due clock +0x52 is the
   clock now, two minutes on */

void he_AllocProtectionAsk(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 2, 0);
}
/* 0x54ae60, a Ghidra miss: the run handler of the event 0x63, the protection money question to a player victim
   ("Berufe\Messagebox_SCHUTZGELD"): it answers the protection money event 0x62 whose id it holds (AIJOB.protection*).
   A gone event or victim building frees it. Stage 0 opens the window with the news 0x1a8c (the collector, the
   amount and the building, their order by the language) and gives the answer three hours; stage 1 frees it when
   that is over, else waits for a button: 0 pays (the event 0x62 goes on in stage 3 with the answer 1, the
   building gets the flag 0x100 at +0x5a, its owner pays the collector, the collector's home building counts the
   money), 1 refuses (the answer 0); the answer's time is now (offline: 6:00 of today) */

void he_RunProtectionAsk(AIJOB *e) {
  AIJOB *p;
  AIJOB *q;
  AIBLD *b = 0, *home;
  AITIME now;

  p = he_FindEvent(1, 1, e->u.id);
  q = p;
  if (p != 0)
    b = gm_BuildQuery(1, 1, q->protectionVictim);
  if (e->stage == -2 || e->stage == -1 || p == 0 || b == 0) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
  }
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_SCHUTZGELD", 0x5f3);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_SetForm(e->slot->win, 0);
    switch (ls_GetLanguage()) {
    case 0:
      io_PrintText(0x1a8c, p->chr, q->protectionAmount, b);
      break;
    case 1:
      io_PrintText(0x1a8c, p->chr, b, q->protectionAmount);
      break;
    }
    e->start = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 3, 0, 0);
    snd_QueueVoice(-7, 0, "_NACHRICHTEN_HS_34", 0, 0);
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (d2_ClickedForm != e->slot->win || d2_ClickedId == -1)
      return;
    now = ai_Time;
    if (net_Conn.s == -1) {
      now.hour = 6;
      now.min = 0;
    }
    if (d2_ClickedId == 0) {
      e->stage = 3;
      q->protectionAnswer = 1;
      p->end = now;
      cm_SendExSetHE(3, p);
      cm_SendSetField(b->id, 0x5a, 2, 0x100, 0);
      cm_SendMoveGoodsUnchecked(ai_Chars[p->chr].netId,
                                ai_Chars[b->owner].netId, 0,
                                q->protectionAmount);
      if (q->protectionHome != -1) {
        home = gm_BuildQuery(1, 1, q->protectionHome);
        home->roundSums[0] += q->protectionAmount;
      }
    } else if (d2_ClickedId == 1) {
      e->stage = 3;
      q->protectionAnswer = 0;
      p->end = now;
      cm_SendExSetHE(3, p);
    }
    he_ReleaseSlot(e);
    he_FreeEvent(e);
  }
}

/* 0x54b170, the alloc handler of the protection-money event 0x62 (he_RunProtection): its slot is -1 and, when its
   opts bit 2 is clear, its answer is -1 (open), its due clock two minutes on, stage 1, and it is posted
   (cm_SendExSetHE 1, the slot kept) */

void he_StartProtection(AIJOB *e) {
  AIJOB *p = e;

  e->exSlot = -1;
  if ((e->opts & 4) == 0) {
    p->protectionAnswer = -1;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->stage = 1;
    e->exSlot = cm_SendExSetHE(1, e);
  }
}
/* 0x54b1e0, a Ghidra miss: the run handler of the protection money event 0x62 ("Schutzgeld", AIJOB.protection*: the
   collector +0xac, the victim building +0xb0, the amount, the answer, the collector's home building and room).
   Freed (stage -1 / -2) it clears the building's flag 0x100 at +0x5a (a posted event only) and frees the event;
   it waits while not started or while its cm slot is busy; without the collector, the building or its owner it
   ends in two minutes. Stage 1 sends the collector to the building, stage 2 (once the collector is idle) sizes
   the amount (6.5% of the building's equipment value) and asks: a player owner gets the question event 0x63
   (he_RunProtectionAsk) and three hours, else the answer is 2 for a building already paying (the flag 0x100),
   1 (pays) for an owner whose sel is 0xb or when a roll stays below 0.001 * its mood[11][2], else a coin toss.
   Stage 3 reports: paid, the building gets the flag 0x100, the owner pays the collector, the home building
   counts it, the news 0x1a8d, stage 4 in 48 hours; refused (0x1a8e) or else (0x1a8f), stage 4 in five minutes.
   Stage 4 shows the news 0x1a90 to both when paid and sends the collector home
   @deep s49: draft 148 -> shape 8. Fixed: the 0x63 question's wait is gm_AddTime(&e->end, 3, 0, 0) (3
   hours; the original pushes 0, 0, 3). Levers: the owner as an int index local read at each use (owner =
   b->owner; ai_Chars[owner].kind / .netId) instead of an AICHAR pointer: the original's byte-offset CSE
   (lea edx,[eax+eax*8]; shl edx,2) kept across the memset (148 -> 28); the fill order fromId, to, type,
   flags, arg[0], time (719 orders: shape 8). Left: the original loads b->id (mov ecx,[ebp+1]) before the
   netId (mov eax,[edx+ai_CharInts]); ours the other way, so the to / fromId stores swap ecx / eax. No
   lever: unsigned short owner (10), to re-read through b->owner (208), owner read before the amount (65),
   msg as a block local, memset(.., sizeof(AIMSG)), every fill order (p1-0-.. = 8 with order 20), climb
   round 1 (155 mutants: nothing). prior: Read all of it against the original and rewrote it typed (AIJOB /
   AIJOB.protection* / AIMSG / AIBLD / AICHAR): fixed the meaning errors - stage 3 goes to stage 4 with
   cm_SendExSetHE(4) (the original's ebx = 4, not 1), the AIMSG fields (to +8, fromId +0xc, time, flags
   +0x36, arg[0]; no store at +0x34), the owner's sel / mood[11][2] at stride 0x21c (was 0x14), the roll's
   direction (!(mood * 0.001f > util_RandomF()): test ah,5 / jnp), the refused / other branches as two full
   copies, text[0x200] (frame 0x2fc equal). 580 = 580 instructions, the frame and switch table equal. Left,
   scheduling and allocation only: the owner record addressed as a byte offset kept in edx (lea
   edx,[eax+eax*8]; shl edx,2; mov al,[edx+ai_Chars+2], reused for [edx+ai_CharInts] after the memset)
   where ours forms the pointer (lea edx,[eax*4+ai_Chars]); the AIMSG stores and the ai_Time copies in
   another order / with ecx<->edx swapped (tried 8 field orders, the best kept); the cm_SendSetField /
   amount load order in the paid branch and the 0x1a8d txt_Format argument loads. The M8 at +0x20a is the
   aligner pairing ours' mov edx,[ai_Time+8] with the original's mov edx,[ai_TimeHourW] inside the same
   14-byte ai_Time copy, both copying in the same order (registers swapped) (references: M8 at +0x20a: ours
   refers to ai_Time+0x8 (0x770ae8), the original's field to 0x770ae4 (ai_TimeHourW), explained: the ref:
   line is the ai_Time struct copy into e->end, the same four loads in the same order on both sides with
   ecx/edx/eax renamed; the aligner pairs different loads, no other object is referenced) */

void he_RunProtection(AIJOB *e) {
  AIJOB *q = e;
  AIBLD *b, *home;
  AICHAR *c;
  int owner;
  AIMSG msg;
  char text[0x200];

  b = gm_BuildQuery(1, 1, q->protectionVictim);
  c = gm_FindChar(q->protectionCollector);
  if (e->stage == -1 || e->stage == -2) {
    if (b != 0 && (e->opts & 2) != 0)
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x100);
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  if (c == 0 || b == 0 || b->owner == 0xffff) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->stage = -1;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  switch (e->stage) {
  case 1:
    sv_MoveToGroup(b, 0, c->id, e);
    cm_SendChrStop(c->netId);
    cm_SendChrGotoBuilding(c->netId, b->id, -1, 0, 1, "Schutzgeld");
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->stage = 2;
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 2:
    if (c->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      e->stage = 2;
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    q->protectionAmount = (int)((float)gm_EquipmentValue(b, 100) * 0.065f);
    owner = b->owner;
    if (ai_Chars[owner].kind == 6 || ai_Chars[owner].kind == 7) {
      memset(&msg, 0, sizeof(msg));
      msg.fromId = b->id;
      msg.to = ai_Chars[owner].netId;
      msg.type = 0x63;
      msg.flags = 9;
      msg.arg[0] = e->id;
      msg.time = ai_Time;
      cm_SendLongMessage(&msg);
      e->end = ai_Time;
      gm_AddTime(&e->end, 3, 0, 0);
      e->stage = 3;
      q->protectionAnswer = 2;
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, util_Random(0x10) + 2, 0);
    e->stage = 3;
    if ((b->flags5aw & 0x100) != 0)
      q->protectionAnswer = 2;
    else if (ai_Chars[b->owner].sel != 0xb &&
             !(ai_Chars[b->owner].mood[11][2] * 0.001f > util_RandomF()))
      q->protectionAnswer = util_Random(2);
    else
      q->protectionAnswer = 1;
    e->exSlot = cm_SendExSetHE(3, e);
    return;
  case 3:
    if (q->protectionAnswer == 1) {
      cm_SendSetField(b->id, 0x5a, 2, 0x100, 0);
      cm_SendMoveGoodsUnchecked(ai_Chars[e->chr].netId,
                                ai_Chars[b->owner].netId, 0,
                                q->protectionAmount);
      if (q->protectionHome != -1) {
        home = gm_BuildQuery(1, 1, q->protectionHome);
        home->roundSums[0] += q->protectionAmount;
      }
      e->end = ai_Time;
      e->start = ai_Time;
      gm_AddTime(&e->end, 0x30, 0, 0);
      e->stage = 4;
      e->exSlot = cm_SendExSetHE(4, e);
      txt_Format(text, 0x1a8d, b->owner, b, q->protectionAmount);
      he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                  0x5f3, "_NACHRICHTEN_HS_84");
      return;
    }
    if (q->protectionAnswer == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      e->stage = 4;
      e->exSlot = cm_SendExSetHE(4, e);
      txt_Format(text, 0x1a8e, b->owner, b);
      he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                  0x5f3, "_NACHRICHTEN_HS_85");
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    e->stage = 4;
    e->exSlot = cm_SendExSetHE(4, e);
    txt_Format(text, 0x1a8f, b->owner, b);
    he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0, 0x5f3,
                "_NACHRICHTEN_HS_85");
    return;
  case 4:
    if (q->protectionAnswer == 1) {
      txt_Format(text, 0x1a90, b);
      he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                  0x5f3, (char *)0);
      he_ShowNews(ai_Chars[b->owner].netId, ai_Chars[b->owner].netId, text, 0,
                  0x5f3, (char *)0);
    }
    sv_MoveToGroup(b, 0, c->id, 0);
    cm_SendChrStop(c->netId);
    cm_SendChrGotoBuilding(c->netId, q->protectionHome, q->protectionHomeRoom,
                           0, 0, "Schutzgeld");
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 2, 0);
    e->stage = -1;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x54b9b0, the alloc handler of the audit event 0x64 (he_RunAudit): the due clock is the clock now, two minutes
   on; the audited building (AIJOB.auditBld), when it is still there, gets its field 0x5a (size 2) set to 0x800
   (cm_SendSetField) */

void he_StartAudit(AIJOB *e) {
  AIJOB *a = e;
  AIBLD *b = gm_BuildQuery(1, 1, a->auditBld);

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 2, 0);
  if (b != 0)
    cm_SendSetField(b->id, 0x5a, 2, 0x800, 0);
}
/* 0x54ba20, a Ghidra miss: the run handler of the audit event 0x64 ("BetriebsPr\xfc" "fung", AIJOB.audit*: the
   inspector +0xac checks the building +0xb0 for the character AIJOB.chr). A freed event, a gone inspector or
   building or a building without an owner frees it. Stage 0 sends the inspector to the building (stage 1 in ten
   minutes); stage 1 waits (four minutes) while the inspector is busy, then judges: the shortfall is
   (100 - the building's level) * 0.01; when it is at most 0.2 and no cart (gm_Query kind 0x1d) of the building
   is filled below 80%, nobody is fined (the news 0x1a76 to the character, 0x1a78 to the owner); else the owner
   pays the character equipment value * shortfall * 0.07 (the news 0x1a75 / 0x1a77 to players). Stage 2 sends the
   inspector home and frees the event */
void he_RunAudit(AIJOB *e) {
  AIJOB *a = e;
  AIBLD *b;
  AICHAR *c;
  AIOBJ *o;
  int found, fine;
  float shortfall;
  char text[0x400];

  b = gm_BuildQuery(1, 1, a->auditBld);
  c = gm_FindChar(a->auditInspector);
  if (e->stage == -2 || c == 0 || b == 0 || b->owner == 0xffff) {
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    sv_MoveToGroup(b, 0, c->id, e);
    cm_SendChrStop(c->netId);
    cm_SendChrGotoBuilding(c->netId, b->id, -1, 0, 1,
                           "BetriebsPr\xfc"
                           "fung");
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->stage = 1;
    return;
  case 1:
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 4, 0);
    if (c->scene->actions != 0) {
      e->stage = 1;
      return;
    }
    shortfall = (100.0f - gm_BuildingLevel(b)) * 0.01f;
    found = 0;
    for (o = gm_Query(0, 2, 7, 4, 0x1d); o != 0; o = gm_QueryNext()) {
      if (o->bldId == b->id && o->fill < 0x50) {
        found = 1;
        break;
      }
    }
    if (!(shortfall > 0.2) && found == 0) {
      txt_Format(text, 0x1a76, b->owner, b);
      he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                  0x5f0, "_NACHRICHTEN_HS_88");
      txt_Format(text, 0x1a78, e->chr, b);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, ai_Chars[b->owner].netId,
                             text, 0, 0x5f0, b->id, -1, 0,
                             "_NACHRICHTEN_HS_86");
      e->stage = 2;
      return;
    }
    fine = (int)(gm_EquipmentValue(b, 100) * shortfall * 0.07f);
    cm_SendMoveGoodsUnchecked(ai_Chars[e->chr].netId, ai_Chars[b->owner].netId,
                              0, fine);
    if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
      txt_Format(text, 0x1a75, fine, b->owner, b);
      he_ShowNews(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId, text, 0,
                  0x5f0, "_NACHRICHTEN_HS_87");
    }
    if (ai_Chars[b->owner].kind == 6 || ai_Chars[b->owner].kind == 7) {
      txt_Format(text, 0x1a77, e->chr, b, fine);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, ai_Chars[b->owner].netId,
                             text, 0, 0x5f0, b->id, -1, 0,
                             "_NACHRICHTEN_HS_86");
    }
    e->stage = 2;
    return;
  case 2:
    sv_MoveToGroup(b, 0, c->id, 0);
    cm_SendChrStop(c->netId);
    cm_SendChrGotoBuilding(c->netId, a->auditHome, a->auditHomeRoom, 0, 0,
                           "BetriebsPr\xfc"
                           "fung");
    he_FreeEvent(e);
    return;
  }
}
/* 0x54be20, the allocation handler of the patrol gathering event 0x65: unless the event is paused (opts 4) it clears
   the fight party (-1) and the gathering's dc, sets the start and due clocks to now, makes it due a minute later and
   posts it at once (cm_SendExSetHE 0, state 0, the slot in exSlot) */

void he_StartGathering(AIJOB *e) {
  AIJOB *g = e;

  if ((e->opts & 4) == 0) {
    g->gatheringParty = -1;
    g->gatheringDc = 0;
    e->start = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x54bec0, a Ghidra miss: the run handler of the patrol gathering event 0x65 ("Patrol", AIJOB.gathering*: the figures
   ids[0..5] gather at the scene object named place). Freed (stage -2) it frees a not yet started event, else it
   sends the figures home once (stage 5) and then frees it; stage -1 frees it. Each step is due from now. Stage 0
   sends the figures there (stage 1 in five minutes); stage 1 waits (four minutes) while one is busy, then starts
   the gathering (stage 2 in ten minutes); stage 2 gives up a day after the start (stage 5), else looks for an
   event 0x48 at the same place of another character: on a coin toss the two meet in a fight party (G28REC kind 3,
   in 30 minutes: the opponent's figures defend, ours raid, stage 3), else the figures idle about the place
   (he_CharacterBehavior) for ten minutes more. Stage 3 waits for the party's slot (stage 4 with its id, stage 5
   without), stage 4 waits until the party is over, stage 5 sends the figures home and ends the event */
void he_RunGathering(AIJOB *e) {
  AIJOB *g = e;
  AIJOB *p, *q;
  AICHAR *c;
  D3OBJECT *o;
  int *id;
  int i, k, n, freeIt;
  unsigned short mine, theirs;
  int *r;
  G28REC party;
  AITIME giveUp;
  D3VECTOR4 pos;

  freeIt = 0;
  if (e->stage == -2) {
    if ((e->opts & 4) != 0) {
      he_FreeEvent(e);
      return;
    }
    e->stage = 5;
    freeIt = 1;
  }
  if (e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  e->end = ai_Time;
  switch (e->stage) {
  case 0:
    for (id = e->ids, k = 6; k != 0; k--, id++) {
      c = gm_FindChar(*id);
      if (c != 0 && c->scene != 0) {
        sv_MoveToGroup(0, 0, c->id, e);
        cm_SendChrStop(c->netId);
        cm_SendChrGotoBuilding(c->netId, -1, -1, g->gatheringPlace, 1,
                               "Patrol");
      }
    }
    gm_AddTime(&e->end, 0, 5, 0);
    e->exSlot = cm_SendExSetHE(1, e);
    return;
  case 1:
    for (i = 0; i < 6; i++) {
      c = gm_FindChar(e->ids[i]);
      if (c != 0 && c->scene != 0 && c->scene->actions != 0) {
        gm_AddTime(&e->end, 0, 4, 0);
        e->exSlot = cm_SendExSetHE(1, e);
        return;
      }
    }
    e->start = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 2:
    giveUp = e->start;
    gm_AddTime(&giveUp, 0x18, 0, 0);
    if (gm_CompareTime(&ai_Time, &giveUp) > 0) {
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(5, e);
      return;
    }
    q = he_FindEvent(1, 0, 0x48);
    p = q;
    if (q != 0) {
      do {
        if (strcmp(g->gatheringPlace, q->gatheringPlace) == 0 &&
            e->chr != q->chr)
          break;
        q = he_NextEvent();
        p = q;
      } while (q != 0);
    }
    if (p != 0 && (short)util_Random(2) != 0) {
      theirs = p->chr;
      mine = e->chr;
      if (theirs != mine) {
        memset(&party, 0, sizeof(party));
        party.kind = 3;
        party.flags = 0xa2;
        party.thing = -1;
        party.used = 2;
        party.variant = 4;
        party.host = ai_Chars[ai_PlayerId].netId;
        party.members[0] = ai_Chars[mine].netId;
        party.members[1] = ai_Chars[theirs].netId;
        for (i = 0; i < 16; i++) {
          party.fight.attackers[i] = -1;
          party.fight.defenders[i] = -1;
        }
        for (n = 0, i = 0; i < 8 && n < 6; i++) {
          if (p->ids[i] != -1)
            party.fight.defenders[n++] = p->ids[i];
        }
        for (n = 0, i = 0; i < 6 && n < 6; i++) {
          if (e->ids[i] != -1)
            party.fight.attackers[n++] = e->ids[i];
        }
        party.fight.carts[0] = -1;
        party.fight.carts[1] = -1;
        party.fight.carts[2] = -1;
        party.fight.attackerBld = g->gatheringHome;
        party.time = ai_Time;
        gm_AddTime(&party.time, 0, 0x1e, 0);
        g->gatheringPartySlot = cm_SendNewParty(&party);
        e->stage = 3;
        gm_AddTime(&e->end, 0, 10, 0);
        e->exSlot = cm_SendExSetHE(3, e);
        return;
      }
    }
    gm_AddTime(&e->end, 0, 10, 0);
    if (d3_CurrentScene == 0 &&
        (o = d3_FindObject(0, 0x140, 0, g->gatheringPlace)) != 0) {
      d3_PointToWorld(o, &o->pos, &pos.v);
      he_CharacterBehavior(e, &pos.v);
    }
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 3:
    gm_AddTime(&e->end, 0, 1, 0);
    if (cm_GetSlotState(g->gatheringPartySlot) == 0) {
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    r = (int *)cm_GetSlotValue(g->gatheringPartySlot);
    if (r == 0) {
      e->exSlot = cm_SendExSetHE(5, e);
      return;
    }
    g->gatheringParty = *r;
    e->exSlot = cm_SendExSetHE(4, e);
    return;
  case 4:
    gm_AddTime(&e->end, 0, 5, 0);
    if (cm_PartyById(g->gatheringParty) != 0) {
      e->exSlot = cm_SendExSetHE(4, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(5, e);
    return;
  case 5:
    for (id = e->ids, k = 6; k != 0; k--, id++) {
      c = gm_FindChar(*id);
      if (c != 0 && c->scene != 0) {
        sv_MoveToGroup(0, 0, c->id, 0);
        cm_SendChrStop(c->netId);
        cm_SendChrGotoBuilding(c->netId, g->gatheringHome, g->gatheringHomeRoom,
                               0, 0, "Patrol");
      }
    }
    gm_AddTime(&e->end, 0, 2, 0);
    if (freeIt) {
      he_FreeEvent(e);
      return;
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x54c4c0, the allocation handler of the simulation events 0x66 (the accident simulation) and 0x70 (the disease
   simulation): the due clock is now at hour 0xa with its minute and second cleared, and AIJOB.simCursor, simStep and
   done are cleared (the run starts at the first character) */
void he_AllocSim(AIJOB *e) {

  e->end = ai_Time;
  e->end.hour = 0xa;
  e->end.min = 0;
  e->end.sec = 0;
  e->simCursor = 0;
  e->simStep = 0;
  e->simDone = 0;
}

/* 0x54c510, the test of a character for the accident simulation: alive (id not 0xffff, health not 0), kind 0, with
   a building whose id is the building of its model record (the one it was sent to): then ai_IsLocalWorker, else 0 */
int he_IsAtWork(AICHAR *rec) {
  AICHAR *c = rec;
  int ok = 1;

  if (c->id == 0xffff)
    ok = 0;
  if (c->health == 0)
    ok = 0;
  if (c->kind == 0 && ok && c->bld != 0 && c->scene != 0 &&
      c->scene->group == c->bld->id)
    return ai_IsLocalWorker(rec);
  return 0;
}
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* 0x54c570, a Ghidra miss: the run handler of the work accident simulation, event 0x66 (AIJOB.sim*; the text
   "RunSimUnfall: calculating at <Day ..>" is formatted and never shown). Freed (stage -2) it frees the event.
   A round starts with a random stride of 16 numbers prime to 0x300 and a random first character; each run (stage
   0) visits the next 12 characters of the round: a worker at its building (he_IsAtWork) whose building has an
   owner has an accident (he_CharAccident) when a roll of 0 .. 100 stays below 25 - 20 * the building's skill 2
   * 0.0125: it loses 50 + random(1 + 255 * (2 - skill * 0.0125), clamped to 0 .. 2) health, and the accident
   gets the health gm_AddHealth leaves. After all 0x300 the round is over: due the next day at 10:00, else due in
   30 minutes, the next day at 10:00 once that is 18:00 or later */
void he_RunAccidentSim(AIJOB *e) {
  AIBLD *b;
  int n, cur, skill;
  float roll, lim, health;
  int primes[16];
  char text[0x200];

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  txt_Format(text,
             (intptr_t)"-------> RunSimUnfall: calculating at <Day = %i Time = "
                       "%i.2:%i.2>",
             ai_Time.year, ai_Time.hour, ai_Time.min);
  if (e->simStep == 0) {
    primes[0] = 1;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 0xb;
    primes[5] = 0xd;
    primes[6] = 0x11;
    primes[7] = 0x13;
    primes[8] = 0x2ed;
    primes[9] = 0x2ef;
    primes[10] = 0x2f3;
    primes[11] = 0x2f5;
    primes[12] = 0x2f9;
    primes[13] = 0x2fb;
    primes[14] = 0x2fd;
    primes[15] = 0x2ff;
    e->simStep = primes[util_Random(0x10)];
    e->simCursor = util_Random(0x300);
  }
  if (e->stage != 0)
    return;
  cur = e->simCursor;
  for (n = 12; n != 0; n--) {
    if (he_IsAtWork(&ai_Chars[cur]) != 0 &&
        ai_Chars[cur].bld->owner != 0xffff) {
      roll = util_RandomF() * 100.0f;
      skill = gm_BuildingSkill(ai_Chars[cur].bld, 2, 1);
      if (25.0f - 20.0f * (skill * 0.0125f) > roll) {
        lim = MIN(MAX(2.0f - skill * 0.0125f, 0.0f), 2.0f);
        health =
            gm_AddHealth(cur, -50 - util_Random((int)(lim * 255.0f + 1.0f)));
        b = ai_Chars[cur].bld;
        he_CharAccident(e, &ai_Chars[cur], &ai_Chars[b->owner], b, health, 0);
      }
    }
    cur = (e->simStep + cur) % 0x300;
    e->simDone++;
  }
  e->simCursor = cur;
  if (e->simDone >= 0x300) {
    e->simCursor = 0;
    e->simStep = 0;
    e->simDone = 0;
    e->end.year++;
    e->end.min = 0;
    e->end.hour = 0xa;
    return;
  }
  gm_AddTime(&e->end, 0, 0x1e, 0);
  if (e->end.hour >= 0x12) {
    e->end.min = 0;
    e->end.hour = 0xa;
    e->end.year++;
  }
}
/* 0x54c870, the allocation handler of the auction event 0x67: unless the event is paused (opts 4) its due clock is
   now plus a day at 9:00, and it is posted at once (cm_SendExSetHE 0, state 0, the slot in exSlot) */
void he_StartAuctionEvent(AIJOB *e) {

  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 9;
    e->end.min = 0;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x54c8e0, a Ghidra miss: the run handler of the auction event 0x67 (AIJOB.auction*: the building +0xac, the start
   price +0xb0). Stage -1 frees it; a not yet started event waits. Stage 0 announces the auction (the news 0x11be
   with the building and the price, 0x601, to every living player character; no building: the event ends) and
   is due the next day at 13:30 (stage 1). Stage 1 invites as bidders up to 8 living player characters (kind 6 /
   7, not held, worth at least the price), then the 8 worthiest such characters of the kinds 3 .. 5, and posts the
   auction party (G28REC kind 10, cm_RunAuction) for 30 minutes from now when there is one; the event ends */
void he_RunAuctionEvent(AIJOB *e) {
  AIJOB *a = e;
  AIBLD *b;
  int n, i, j, k, v, found;
  int best[8];
  int val[8];
  G28REC party;
  char text[0x200];

  if (e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, a->auctionBld);
    if (b == 0) {
      cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, 0x11be, b, a->auctionPrice);
    for (k = 0; k < 0x300; k++) {
      if ((ai_Chars[k].kind == 6 || ai_Chars[k].kind == 7) &&
          ai_Chars[k].health > 0)
        he_ShowNews(ai_Chars[k].netId, ai_Chars[k].netId, text, 0, 0x601,
                    (char *)0);
    }
    e->end.year++;
    e->end.hour = 0xd;
    e->end.min = 0x1e;
    e->exSlot = cm_SendExSetHE(1, e);
    return;
  case 1:
    memset(best, -1, sizeof(best));
    memset(val, 0, sizeof(val));
    memset(&party, 0, sizeof(party));
    n = 0;
    for (k = 0; k < 0x300 && n < 8; k++) {
      if ((ai_Chars[k].kind == 6 || ai_Chars[k].kind == 7) &&
          ai_Chars[k].health > 0 && ai_Chars[k].heldRounds == 0 &&
          gm_GetGoodsValue(&ai_Chars[k]) >= a->auctionPrice)
        party.members[n++] = ai_Chars[k].netId;
    }
    for (k = 0; k < 0x300; k++) {
      if (ai_Chars[k].health > 0 && ai_Chars[k].heldRounds == 0 &&
          (ai_Chars[k].kind == 5 || ai_Chars[k].kind == 3 ||
           ai_Chars[k].kind == 4)) {
        v = gm_GetGoodsValue(&ai_Chars[k]);
        if (v < a->auctionPrice)
          continue;
        found = 0;
        for (i = 0; i < 8; i++) {
          if (best[i] == -1) {
            found = 1;
            break;
          }
          if (v > val[i]) {
            for (j = 7; j > i; j--) {
              best[j] = best[j - 1];
              val[j] = val[j - 1];
            }
            found = 1;
            break;
          }
        }
        if (found) {
          best[i] = ai_Chars[k].netId;
          val[i] = v;
        }
      }
    }
    for (i = 0; i < 8 && n < 8; i++) {
      if (best[i] != -1)
        party.members[n++] = best[i];
    }
    if (n != 0) {
      party.host = ai_Chars[ai_PlayerId].netId;
      party.auction.price = a->auctionPrice;
      party.kind = 0xa;
      party.flags = 0x22;
      party.thing = -1;
      party.used = n;
      party.auction.building = a->auctionBld;
      party.auction.zero84 = 0;
      party.time = ai_Time;
      gm_AddTime(&party.time, 0, 0x1e, 0);
      cm_SendNewParty(&party);
      e->end = ai_Time;
    } else
      e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}
/* 0x54cc20, the allocation handler of the title ceremony event 0x69: the due clock copies the start clock, the stage is
   0 and the sent flag is cleared */
void he_StartTitleCeremony(AIJOB *e) {
  AIJOB *t = e;

  e->end = e->start;
  e->stage = 0;
  t->titleSent = 0;
}
/* 0x54cc50, a Ghidra miss: the run handler of the title ceremony event 0x69 (AIJOB.title*: the character +0xb0 gets the
   title +0xac), run only on the game of its player (AIJOB.chr is ai_PlayerId) in a running game once it is due.
   Freed, ended, without its player or its character it frees the event. Stage 0 opens the window
   ("SPECIAL\TITEL" when the character is the player's own, "SPECIAL\TITEL_ANDERE" for another one): for the own
   character it sends the title once (field 0xd) and shows the news 0x42a3 / 0x42a1 / 0x429f (titles 9 / 8 / 7),
   0x1618 (the citizenship, 2) or 0x1617 (with the player's name, the end clock, the character and the title's
   text by sex) with the fanfare by the title's height and the herald's voice, then the click sound; for another
   character the news 0x42a4 / 0x42a2 / 0x42a0, 0x161b or 0x161a with the rival's voice; then the news 0x161c below
   (stage 1). Stage 1 frees the event when the window is answered (button 0, or the event bar's confirmation of
   its slot); without a window it starts over */
void he_RunTitleCeremony(AIJOB *e) {
  AIJOB *t = e;
  AICHAR *own, *c;
  int text;

  own = &ai_Chars[e->chr];
  if (ai_PlayerId != e->chr || ai_GameState == 0)
    return;
  if (gm_CompareTime(&e->end, &ai_Time) == 1)
    return;
  c = gm_FindChar(t->titleCh);
  if (e->stage == -2 || e->stage == -1 || own->id == 0xffff || c == 0) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    if (e->slot == 0) {
      if (c == own)
        he_OpenEventSlot(e, 0, 0, "SPECIAL\\TITEL", 0x5fd);
      else
        he_OpenEventSlot(e, 0, 0, "SPECIAL\\TITEL_ANDERE", 0x5fe);
    }
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_CentreViewWindows(e->slot->win);
    d2_SetForm(e->slot->win, 1);
    if (c == own) {
      if (t->titleSent == 0) {
        cm_BeginFieldBlock(c, c->netId);
        cm_AddFieldDelta(1, 1, 0xd, &t->titleTitle);
        cm_SendFieldDeltas();
        t->titleSent = 1;
      }
      if (t->titleTitle == 9)
        io_PrintText(0x42a3, &e->end);
      else if (t->titleTitle == 8)
        io_PrintText(0x42a1, &e->end);
      else if (t->titleTitle == 7)
        io_PrintText(0x429f, &e->end);
      else if (t->titleTitle != 2)
        io_PrintText(
            0x1617, ai_PlayerSlots[ai_OwnPlayer].townName, &e->end, c->id,
            (c->sex == 0 ? t->titleTitle + 0x114 : t->titleTitle + 0x11e));
      else {
        if (c->sex != 0)
          text = 0x120;
        else
          text = 0x116;
        io_PrintText(0x1618, ai_PlayerSlots[ai_OwnPlayer].townName, &e->end,
                     c->id, text);
      }
      if (t->titleTitle == 2) {
        snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftKurz", 0, 100);
        snd_QueueVoice(-8, 0, "_VERLEIHUNG_BUERGERRECHT", 0, 0xfa);
        snd_QueueVoice(-8, 0,
                       c->sex == 0 ? "_TITEL_MAENNLICH" : "_TITEL_WEIBLICH",
                       t->titleTitle, 100);
        snd_QueueVoice(-7, 0, "MausclickLinks_s_01", -1, 0);
      } else {
        if (t->titleTitle <= 3)
          snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftKurz", 0, 100);
        else if (t->titleTitle < 6)
          snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftMittel", 0, 100);
        else
          snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftLang", 0, 100);
        if (t->titleTitle < 7) {
          snd_QueueVoice(-8, 0, "_VERLEIHUNG_TITEL", 0, 0xfa);
          snd_QueueVoice(-8, 0,
                         c->sex == 0 ? "_TITEL_MAENNLICH" : "_TITEL_WEIBLICH",
                         t->titleTitle, 100);
        } else if (t->titleTitle == 7)
          snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_ERHALTEN_HS_02", -1, 100);
        else if (t->titleTitle == 8)
          snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_ERHALTEN_HS_03", -1, 100);
        else if (t->titleTitle == 9)
          snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_ERHALTEN_HS_04", -1, 100);
        snd_QueueVoice(-7, 0, "MausclickLinks_s_01", -1, 0);
      }
    } else {
      if (t->titleTitle == 9) {
        if (c->sex != 0)
          text = 0x127;
        else
          text = 0x11d;
        io_PrintText(0x42a4, c->id, text, c->id);
      } else if (t->titleTitle == 8) {
        if (c->sex != 0)
          text = 0x126;
        else
          text = 0x11c;
        io_PrintText(0x42a2, c->id, text, c->id);
      } else if (t->titleTitle == 7) {
        if (c->sex != 0)
          text = 0x125;
        else
          text = 0x11b;
        io_PrintText(0x42a0, c->id, text, c->id);
      } else if (t->titleTitle != 2)
        io_PrintText(
            0x161a, c->id, c->id,
            (c->sex == 0 ? t->titleTitle + 0x114 : t->titleTitle + 0x11e),
            c->id);
      else
        io_PrintText(0x161b, c->id);
      if (t->titleTitle == 2)
        snd_QueueVoice(-8, 0, "_VERLEIHUNG_BUERGERRECHT_KONKURENT", 0, 100);
      else if (t->titleTitle < 7) {
        snd_QueueVoice(-8, 0, "_VERLEIHUNG_TITEL_KONKURENT", 0, 100);
        snd_QueueVoice(-8, 0,
                       c->sex == 0 ? "_TITEL_MAENNLICH" : "_TITEL_WEIBLICH",
                       t->titleTitle, 100);
      } else if (t->titleTitle == 7)
        snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_FB_HS_02", -1, 100);
      else if (t->titleTitle == 8)
        snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_FB_HS_03", -1, 100);
      else if (t->titleTitle == 9)
        snd_QueueVoice(-7, 0, "_VERLEIHUNG_TITEL_FB_HS_04", -1, 100);
    }
    d2_SetForm(e->slot->win, 2);
    io_PrintText(0x161c);
    e->stage = 1;
    return;
  case 1:
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win && he_SlotConfirmed == 0)
      return;
    if (d2_ClickedId == 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (he_SlotConfirmed == 0 || he_ActiveSlot != e->slot)
      return;
    he_SlotConfirmed = 0;
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
}
/* 0x54d190, the allocation handler of the inn simulation event 0x68 ("SIM_WIRTSHAUS"; AIJOB.simCursor): the due clock
   is now at 22:30 with its second cleared, and AIJOB.simCursor and step are cleared (the round starts at the first
   character) */
void he_StartInnSim(AIJOB *e) {

  e->end = ai_Time;
  e->end.hour = 0x16;
  e->end.min = 0x1e;
  e->end.sec = 0;
  e->simCursor = 0;
  e->simStep = 0;
}

typedef struct
    HEINN { /* he_RunInnSim's list of the inns (he_FindGuestInn walks it, 12 bytes each) */
  AIBLD
  *inn; /* 0x0, the inn (a building of kind 0x16), 0: the end of the list */
  AIOBJ *drink1; /* 0x4, its bar's good 0x179, 0: none */
  AIOBJ *drink2; /* 0x8, its bar's good 0x17a, 0: none */
} HEINN;

/* 0x54d1e0, looks a character up in the inn simulation's list: finds the inn whose building id is the building of the
   character's model record and whose building has an owner; stores its index in *out and returns 1, else 0 */
int he_FindGuestInn(AICHAR *rec, HEINN *tab, int *out) {
  AICHAR *c = rec;
  AIBLD *b;
  int i;

  if (c->id == 0xffff || c->health == 0 || c->kind != 0)
    return 0;
  if (c->scene == 0 || ai_CanAct(rec) == 0)
    return 0;
  for (i = 0; i < 16; i++) {
    b = tab[i].inn;
    if (b == 0)
      return 0;
    if (b->id == c->scene->group && b->owner != 0xffff) {
      *out = i;
      return 1;
    }
  }
  return 0;
}

/* he_RunInnSim's guest count: the inn's field +0x69 counts `guests` more */
#define HE_INN_GUEST(r)                                                        \
  {                                                                            \
    cm_BeginFieldBlock((r).inn, (r).inn->id);                                  \
    cm_AddFieldValues(2, 1, (char *)&(r).inn->inn.guests - cm_FieldObject,     \
                      &guests);                                                \
    cm_SendFieldDeltas();                                                      \
  }
/* he_RunInnSim's sale of a drink to the guest ai_Chars[i] (cm_SendExSellObject: one of the good): 0.65 of the
   price from the guest, the price to the inn's owner, the takings (+0x65) and the guests (+0x6b) of the inn, then the guest count */
#define HE_INN_SALE(r, drink, good, price)                                     \
  {                                                                            \
    cm_BeginGroup("SIM_WIRTSHAUS");                                            \
    cm_SendExSellObject(-1, (r).drink->ownerId, good, 1, ai_OwnPlayer, 0);     \
    cm_SendMoveGoodsUnchecked(-1, ai_Chars[i].netId, ai_OwnPlayer,             \
                              (int)((float)price * 0.65f));                    \
    cm_SendMoveGoodsUnchecked(ai_Chars[(r).inn->owner].netId, -1,              \
                              ai_OwnPlayer, price);                            \
    cm_BeginFieldBlock((r).inn, (r).inn->id);                                  \
    cm_AddFieldValues(4, 1, (char *)&(r).inn->inn.takings - cm_FieldObject,    \
                      &price);                                                 \
    cm_AddFieldValues(2, 1, (char *)&(r).inn->inn.served - cm_FieldObject,     \
                      &guests);                                                \
    cm_SendFieldDeltas();                                                      \
    cm_EndGroup("SIM_WIRTSHAUS");                                              \
    HE_INN_GUEST(r);                                                           \
  }
/* 0x54d260, a Ghidra miss: the run handler of the inn simulation, event 0x68 ("SIM_WIRTSHAUS"; AIJOB.simCursor).
   Freed (stage -2) it frees the event. It lists up to 16 inns (buildings of kind 0x16) with their bar object (kind
   0x2a, 6) and its two drinks (the goods 0x179 / 0x17a, 0: none); each run (stage 0) visits the next 0x180
   characters: one sitting in an inn (he_FindGuestInn) whose wealth (gm_GetGoodsValue) is above 0.65 * the dearer
   drink (the prices 1.5 * gm_GoodsPrice) buys either drink at random when the inn has both, else the first one it
   can afford, else the second: the inn sells one (cm_SendExSellObject), the guest pays 0.65 of the price, the
   inn's owner gets the price, and the inn's fields +0x65 (the takings) / +0x6b (3 .. 6 guests) count it; a guest
   counts at +0x69 too, so does one who could afford the first drink of an inn without the second. After the last
   character the round is over (due the next day at 22:30), else due in 15 minutes */

void he_RunInnSim(AIJOB *e) {
  unsigned int first;
  HEINN inns[16];
  int i, n, end, idx, wealth, price1, price2, lim, guests;

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  D3_ZERO(inns, sizeof(inns));
  n = 0;
  inns[0].inn = gm_BuildQuery(1, 5, 0x16);
  while (inns[n].inn != 0 && n < 16) {
    AIOBJ *bar = gm_Query((void *)inns[n].inn->objList, 2, 0, 0x2a, 6);

    if (bar != 0) {
      inns[n].drink1 = gm_Query(bar->list, 1, 0, 0x179);
      inns[n].drink2 = gm_Query(bar->list, 1, 0, 0x17a);
    }
    n++;
    inns[n].inn = gm_BuildNext();
  }
  if (e->stage != 0)
    return;
  first = e->simCursor;
  end = first + 0x180;
  for (i = first; i < end; i++) {
    if (he_FindGuestInn(&ai_Chars[i], inns, &idx) == 0)
      continue;
    price1 = (int)(gm_GoodsPrice(0x179, ai_OwnPlayer) * 1.5);
    price2 = (int)(gm_GoodsPrice(0x17a, ai_OwnPlayer) * 1.5);
    guests = util_RandomInt(4) + 3;
    wealth = gm_GetGoodsValue(&ai_Chars[i]);
    lim = price1 > price2 ? price1 : price2;
    if ((float)wealth > (float)lim * 0.65f && inns[idx].drink1 != 0 &&
        inns[idx].drink2 != 0) {
      if (util_Random(2) != 0) {
        HE_INN_SALE(inns[idx], drink1, 0x179, price1);
      } else {
        HE_INN_SALE(inns[idx], drink2, 0x17a, price2);
      }
    } else if (wealth > price1 && inns[idx].drink1 != 0) {
      HE_INN_SALE(inns[idx], drink1, 0x179, price1);
    } else if (wealth > price2) {
      if (inns[idx].drink2 != 0) {
        HE_INN_SALE(inns[idx], drink2, 0x17a, price2);
      } else if (wealth > price1) {
        HE_INN_GUEST(inns[idx]);
      }
    }
  }
  e->simCursor = end;
  if (end >= 0x300) {
    e->simCursor = 0;
    e->simStep = 0;
    e->end.year++;
    e->end.hour = 0x16;
    e->end.min = 0x1e;
    return;
  }
  gm_AddTime(&e->end, 0, 0xf, 0);
}

unsigned short hmt_RecordCount(void);
unsigned short hmt_RandomRecord(short k);
unsigned short hmt_RandomTextOffset(unsigned short k);
const struct G11REC *hmt_GetRecord(unsigned short k);

/* 0x54d790, the allocation handler of the skill level-up event 0x6a: the due clock copies the start clock and the
   variant is a random 0 .. 5 (one of six texts per skill) */
void he_StartSkillUp(AIJOB *e) {
  AIJOB *s = e;

  e->end = e->start;
  s->skillUpVariant = util_Random(6);
}
/* 0x54d7d0, the run handler of the skill level-up event 0x6a of the own player ("SPECIAL\TALENT_STUFE"): shows the
   news 0x16c8, one of six texts of the skill (0x16c9 + skill * 6 + variant) with the fanfare and its voice
   ("_TALENT_MAIN"), the level's news and voice ("_TALENT_STUFE") or below level 6 the skill's master news
   ("_TALENT_MAX"), then 0x16f1; stage 1 waits for the click and frees the event */

void he_RunSkillUp(AIJOB *e) {
  AIJOB *s = e;
  AICHAR *own;

  own = &ai_Chars[e->chr];
  if (ai_PlayerId != e->chr || ai_GameState == 0)
    return;
  if (gm_CompareTime(&e->end, &ai_Time) == 1)
    return;
  if (e->stage == -2 || e->stage == -1 || own->id == 0xffff) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    if (e->slot == 0)
      he_OpenEventSlot(e, 0, 0, "SPECIAL\\TALENT_STUFE", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_CentreViewWindows(e->slot->win);
    d2_SetForm(e->slot->win, 1);
    io_PrintText(0x16c8);
    io_PrintText(s->skillUpVariant + s->skillUpSkill * 6 + 0x16c9);
    snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftKurz", 0, 100);
    snd_QueueVoice(-8, 0, "_TALENT_MAIN",
                   s->skillUpVariant + s->skillUpSkill * 6, 0xfa);
    if (s->skillUpLevel < 6) {
      io_PrintText(s->skillUpLevel + 0x16e6);
      snd_QueueVoice(-8, 0, "_TALENT_STUFE", s->skillUpLevel - 1, 100);
    } else {
      io_PrintText(s->skillUpSkill + 0x16ec);
      snd_QueueVoice(-8, 0, "_TALENT_MAX", s->skillUpSkill, 100);
    }
    snd_QueueVoice(-7, 0, "MausclickLinks_s_01", -1, 0);
    d2_SetForm(e->slot->win, 2);
    io_PrintText(0x16f1);
    e->stage = 1;
    return;
  case 1:
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win && he_SlotConfirmed == 0 &&
        d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (he_SlotConfirmed == 0 || he_ActiveSlot != e->slot)
      return;
    he_SlotConfirmed = 0;
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
}
/* 0x54da20, a Ghidra miss: the init of the bard event 0x6b (its run handler he_RunBard): unless the event is not
   started yet (opts bit 2), +0xac = the number of the hmt records (the song's subject is drawn from them), +0xb4 =
   -1 (no script yet), the due clock is the clock now and the event is posted in state 0; it does nothing while
   opts still says the event is not started yet (bit 4) */

void he_StartBard(AIJOB *e) {
  AIJOB *b = e;

  if ((e->opts & 4) == 0) {
    b->bardRec = (unsigned short)hmt_RecordCount();
    b->bardScript = -1;
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x54da80, the run handler of the bard event: stage 0 draws the song's subject (an hmt record and its text) and
   sets the due clock 3 + random(4) ahead at 10:00; stage 1 shows the news 0x1e29 to every player figure (kinds 6 /
   7); stage 2 creates the bard (SpecialEvents\barde\barde_create.esc, marked 'DrBh', run with the record's text
   set) and keeps it until 20:00, then stops it; it frees the gfx info once the own player has the flag 0x20000;
   stage 3 clears the flag 0x20000 of everybody and ends the event a day later at 6:00 */

void he_RunBard(AIJOB *e) {
  char text[0x200];
  AIJOB *b = e;
  int i;
  EVTSCRIPT *sc;
  const struct G11REC *rec;
  int scene;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if ((e->opts & 4) != 0)
      return;
    b->bardRec = hmt_RandomRecord(b->bardRec);
    b->bardTextOff = hmt_RandomTextOffset(b->bardRec);
    e->end = ai_Time;
    e->end.year += util_Random(4) + 3;
    e->end.hour = 0xa;
    e->end.min = 0;
    cm_SendExSetHE(1, e);
    e->exSlot = -1;
    return;
  case 1:
    if ((e->opts & 4) != 0)
      return;
    txt_Format(text, 0x1e29);
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].id != 0xffff &&
          (ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7))
        he_ShowNews(ai_Chars[i].netId, e->id, text, 0, 0x601, ch_EmptyName);
    }
    gm_AddTime(&e->end, 0, 5, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 2:
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    sc = evt_FindById(b->bardScript);
    if (e->end.hour < 0x14) {
      if (sc == 0 || sc->tag[0] != HE_BARD_MARK) {
        b->bardScript = -1;
        rec = hmt_GetRecord(b->bardRec);
        sprintf(text, "%i", rec->textSet);
        scene = d3_CurrentScene;
        d3if_SelectScene(0, 1);
        sc = evt_Load("SpecialEvents\\barde\\barde_create.esc");
        if (sc != 0) {
          sc->tag[0] = HE_BARD_MARK;
          b->bardScript = sc->id;
          evt_RunScriptArgs(sc, 1, rec->textSet);
          sc->group = 0;
        }
        d3if_SelectScene(scene, 1);
      }
      e->stage = 2;
      if (e->gfx != 0 && (ai_Chars[ai_PlayerId].flags1c8 & 0x20000) != 0) {
        he_FreeGfxInfo(e->gfx);
        e->gfx = 0;
      }
      return;
    }
    if (sc != 0 && sc->tag[0] == HE_BARD_MARK)
      evt_Stop(sc);
    gm_AddTime(&e->end, 0, 5, 0);
    e->stage = 3;
    return;
  case 3:
    if ((e->opts & 2) != 0) {
      for (i = 0; i < 768; i++) {
        if (ai_Chars[i].id != 0xffff && (ai_Chars[i].flags1c8 & 0x20000) != 0)
          cm_SendSetField(ai_Chars[i].netId, 0x1c8, 4, 0, 0x20000);
      }
    }
    e->end = ai_Time;
    e->end.year++;
    e->end.hour = 6;
    e->end.min = 0;
    if (e->gfx != 0) {
      he_FreeGfxInfo(e->gfx);
      e->gfx = 0;
    }
    if ((e->opts & 2) != 0)
      e->exSlot = cm_SendExSetHE(0, e);
    e->exSlot = -1;
    return;
  }
}

struct ORDSTATS;
float ord_GetStatistics(struct ORDSTATS *o);

/* 0x54de60, a Ghidra miss: the init of the population event 0x6d (its run handler he_RunPopulation): the due clock
   is the clock now, the round's count and the newcomer chance are cleared and the event is posted in state 0; it
   does nothing while opts still says the event is not started yet (bit 4) */
void he_StartPopulation(AIJOB *e) {
  AIJOB *p = e;

  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    p->populationCount = 0;
    p->populationChance = 0.0f;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x54dec0, the run handler of the population event: stage 1 rates the town (ord_GetStatistics: the free room
   (sumA - chars) / sumA, the share without a home col[3]): few homeless (< 0.1) -> stage 2, newcomers; many
   (> 0.3) -> stage 6, deaths; else stage 7 from 15:00. Stage 2 draws against chance every hour until 20:00: a
   newcomer is created (cm_SendCreateCharacter, stage 3: it gets a free home, (51 .. 100) * 32 money and its fields
   2 / 0xc set); stage 6 likewise kills a homeless figure of kind 0 without a workplace (-2000 health); stage 7 gives
   a homeless figure of kind 0 / 1 a free home every ten minutes until 22:00, then the event rests until 6:00 */

void he_RunPopulation(AIJOB *e) {
  AIJOB *p = e;
  AIBLD *b;
  AICHAR *c;
  int found, zero, id, n, i, j;
  ORDKIND kind;
  ORDSTATS st;
  float x;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  switch (e->stage) {
  case 0:
    p->populationChance *= 0.0f;
    p->populationStep = 0.0f;
    p->populationCount = 0;
    gm_AddTime(&e->end, 0, 0, 5);
    e->exSlot = cm_SendExSetHE(1, e);
    break;
  case 1:
    ord_GetStatistics(&st);
    x = (float)(st.sumA - st.chars) / st.sumA;
    p->populationChance = 1.0f - x;
    p->populationStep = x / (p->populationCount + 2);
    gm_AddTime(&e->end, 1, 0, 0);
    if (st.col[3] < 0.1) {
      p->populationChance = (2.0f - st.score) * p->populationChance;
      e->exSlot = cm_SendExSetHE(2, e);
      break;
    }
    if (st.col[3] > 0.3) {
      p->populationChance =
          (float)fabs((st.score + 1.0f) * p->populationChance);
      p->populationStep = (float)fabs(p->populationStep);
      e->exSlot = cm_SendExSetHE(6, e);
      break;
    }
    e->end = ai_Time;
    e->end.hour = 0xf;
    e->exSlot = cm_SendExSetHE(7, e);
    break;
  case 2:
    if (ai_Time.hour >= 0x14) {
      e->end = ai_Time;
      e->end.min++;
      e->exSlot = cm_SendExSetHE(7, e);
      return;
    }
    if (util_RandomF() > p->populationChance) {
      p->populationSlot = -1;
      p->populationSlot = cm_SendCreateCharacter(
          0xff, -1, -1, util_Random(0xc) + 0xf, -1, 0, 0, 2);
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 0, 1);
      e->exSlot = cm_SendExSetHE(3, e);
      break;
    }
    p->populationChance -= p->populationStep;
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    e->exSlot = cm_SendExSetHE(2, e);
    break;
  case 3:
    if (cm_GetSlotState(p->populationSlot) == 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 0, 1);
      e->exSlot = cm_SendExSetHE(3, e);
      break;
    }
    if (cm_GetSlotState(p->populationSlot) == 2) {
      gm_AddTime(&e->end, 1, 0, 0);
      p->populationSlot = -1;
      e->exSlot = cm_SendExSetHE(6, e);
      return;
    }
    c = (AICHAR *)cm_GetSlotValue(p->populationSlot);
    b = 0;
    id = util_Random(2);
    zero = 0;
    if (c == 0) {
      gm_AddTime(&e->end, 1, 0, 0);
      p->populationSlot = -1;
      e->exSlot = cm_SendExSetHE(6, e);
      return;
    }
    found = 0;
    n = 0x100;
    i = util_Random(0x100);
    while (found == 0 && n != 0) {
      b = &ai_Blds[i];
      if (ai_BTypes[b->type].kind == 1 &&
          ord_GetKindRecord(b->type, &kind) != 0 &&
          (unsigned short)b->residents < kind.residents)
        found = 1;
      n--;
      i = (i + 1) % 0x100;
    }
    if (found != 0)
      cm_SendBoss(c->netId, b->id);
    cm_SendMoveGoodsUnchecked(c->netId, -1, ai_OwnPlayer,
                              (util_Random(0x32) + 0x33) << 5);
    cm_BeginFieldBlock(c, c->netId);
    cm_AddFieldDelta(1, 1, 2, &zero);
    cm_AddFieldDelta(1, 1, 0xc, &id);
    cm_SendFieldDeltas();
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    p->populationCount++;
    e->exSlot = cm_SendExSetHE(1, e);
    break;
  case 6:
    if (ai_Time.hour >= 0x14) {
      e->end = ai_Time;
      e->end.min++;
      e->exSlot = cm_SendExSetHE(7, e);
      return;
    }
    if (util_RandomF() > p->populationChance) {
      i = util_Random(0x300);
      n = 0x300;
      do {
        if (ai_Chars[i].id != 0xffff && ai_Chars[i].health != 0 &&
            ai_Chars[i].kind == 0 && ai_Chars[i].bld == 0) {
          gm_AddHealth(i, -2000);
          p->populationCount++;
          break;
        }
        n--;
        i = (i + 1) % 0x300;
      } while (n != 0);
      p->populationSlot = -1;
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 0x1e, 0);
      e->exSlot = cm_SendExSetHE(1, e);
      return;
    }
    p->populationChance -= p->populationStep;
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    e->exSlot = cm_SendExSetHE(6, e);
    break;
  case 7:
    b = 0;
    found = 0;
    i = util_Random(0x300);
    n = 0x300;
    do {
      if (ai_Chars[i].id != 0xffff && ai_Chars[i].health != 0 &&
          ((ai_Chars[i].kind == 0 && ai_Chars[i].bld2 == 0) ||
           (ai_Chars[i].kind == 1 && ai_Chars[i].bld2 == 0))) {
        found = 1;
        break;
      }
      n--;
      i = (i + 1) % 0x300;
    } while (n != 0);
    if (found != 0) {
      found = 0;
      n = 0x100;
      j = util_Random(0x100);
      while (found == 0 && n != 0) {
        b = &ai_Blds[j];
        if (ai_BTypes[b->type].kind == 1 &&
            ord_GetKindRecord(b->type, &kind) != 0 &&
            (unsigned short)b->residents < kind.residents)
          found = 1;
        n--;
        j = (j + 1) % 0x100;
      }
      if (found != 0)
        cm_SendBoss(ai_Chars[i].netId, b->id);
    }
    gm_AddTime(&e->end, 0, 0xa, 0);
    if (e->end.hour >= 0x16) {
      e->end = ai_Time;
      e->end.year++;
      e->end.min = 0;
      e->end.hour = 6;
      e->exSlot = cm_SendExSetHE(0, e);
      break;
    }
    if (e->end.hour < 0xf) {
      e->end = ai_Time;
      e->end.min++;
      e->exSlot = cm_SendExSetHE(0, e);
      break;
    }
    e->exSlot = cm_SendExSetHE(7, e);
    break;
  }
}

/* 0x54e770, the allocation handler of the "Geliebte" (lover) event 0x6f (its run handler he_RunLover): looks up its
   keeper +0xac and its lover +0xb0 (both even while the event is not started yet), then, unless opts still says so
   (bit 4), the due clock is the clock now + a day and the event is posted at once. A gone lover or one already kept
   (AICHAR flag 0x800000) ends it (posted -1); else the lover is marked kept (cm_SendSetField 0x1c8 bit 0x800000), the
   keeper's relation to it falls by 0x32, the rounds / the daily pay / the spare id are set (0 / 2 / -1) and the event
   is posted with the key 2 */
void he_StartLover(AIJOB *e) {
  AIJOB *l = e;
  AICHAR *lover = gm_FindChar(l->loverLover);
  AICHAR *keeper = gm_FindChar(l->loverKeeper);

  if ((e->opts & 4) != 0)
    return;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  if (lover == 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if ((lover->flags1c8 & HE_LOVER_FLAG) != 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  cm_BeginGroup("Alloc_Geliebte");
  cm_SendSetField(lover->netId, 0x1c8, 4, HE_LOVER_FLAG, 0);
  cm_SendRelations(keeper->netId, lover->netId, 0x32, 1);
  cm_EndGroup("Alloc_Geliebte AI");
  l->loverRounds = 0;
  l->loverPay = 2;
  e->idbc = -1;
  e->exSlot = cm_SendExSetHE(2, e);
}
/* 0x54e890, the run handler of the lover event ("Geliebte"): stage 2 waits for the posting (cm_GetSlotState: 1 goes
   on, 2 ends it); while the keeper lives, every day the keeper pays the lover (an AP event of -pay with the news
   0xb4 / 0xb5 by the lover's sex) and the rounds count up; stage 1 or a dead keeper ends the affair (the lover's
   flag 0x800000 cleared, at stage 1 the relation falls by (2 + rounds) * 5); stage -2 frees it with the relation
   -(8 + rounds) * 5 */

void he_RunLover(AIJOB *e) {
  char text[0x200];
  AIJOB *l = e;
  AICHAR *lover, *keeper;
  int h;

  lover = gm_FindChar(l->loverLover);
  keeper = gm_FindChar(l->loverKeeper);
  if (e->stage == -1) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage == -2) {
    if ((e->opts & 4) != 0) {
      he_FreeEvent(e);
      return;
    }
    if (lover != 0) {
      cm_SendSetField(lover->netId, 0x1c8, 4, 0, HE_LOVER_FLAG);
      if (keeper != 0)
        cm_SendRelations(keeper->netId, lover->netId, (-8 - l->loverRounds) * 5,
                         1);
    }
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (lover == 0) {
    gm_AddTime(&e->end, 0, 2, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  if (e->stage == 2) {
    h = cm_GetSlotState(e->exSlot);
    if (h == 0)
      return;
    if (h == 1) {
      gm_AddTime(&e->end, 0, 2, 0);
      cm_SendExSetHE(0, e);
      return;
    }
    if (h == 2) {
      gm_AddTime(&e->end, 0, 2, 0);
      cm_SendExSetHE(-1, e);
    }
    return;
  }
  if (keeper != 0 && keeper->health != 0) {
    if (e->stage == 1) {
      cm_SendSetField(lover->netId, 0x1c8, 4, 0, HE_LOVER_FLAG);
      cm_SendRelations(keeper->netId, lover->netId, (-2 - l->loverRounds) * 5,
                       1);
      gm_AddTime(&e->end, 0, 2, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (e->stage == 3) {
      e->end = ai_Time;
      cm_SendExSetHE(0, e);
      return;
    }
    if (lover->sex == 1)
      txt_Format(text, 0xb4, lover->id);
    else
      txt_Format(text, 0xb5, lover->id);
    he_AddApEvent(e->chr, text, -l->loverPay, 0);
    l->loverRounds++;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->exSlot = cm_SendExSetHE(0, e);
    return;
  }
  cm_SendSetField(lover->netId, 0x1c8, 4, 0, HE_LOVER_FLAG);
  gm_AddTime(&e->end, 0, 2, 0);
  e->exSlot = cm_SendExSetHE(-1, e);
}
/* 0x54eb80, a Ghidra miss: the figure record test of the street simulation: alive, kind below 10, and (0x47e840 or 0x47e7f0 non zero) */

int he_IsSimCandidate(AICHAR *rec) {
  AICHAR *c = rec;

  if (c->id == 0xffff)
    return 0;
  if (c->health == 0)
    return 0;
  if (c->kind >= 10)
    return 0;
  if (ai_IsLocalWorker(rec) != 0)
    return 1;
  return ai_CanAct(rec) != 0;
}
/* 0x54ebd0, the run handler of the disease simulation, event 0x70 (AIJOB.sim*, the twin of he_RunAccidentSim; the text
   "RunSimKrankheiten: calculating at <Day ..>" is formatted and never shown). Freed (stage -2) it frees the event.
   A round starts with a random stride of 16 numbers prime to 0x300 and a random first character; each run (stage
   0) visits the next 12 characters of the round: a candidate (he_IsSimCandidate) falls ill when a roll of 0 .. 100
   stays below its risk: without a home 25 - 10 * random (three quarters of it with the item 0x2b3), less the home's
   skill 8 * 0.0125 * 20 (0.02 for a home of kind other than 2). gm_CatchDisease draws the disease and its health;
   a worker whose building has an owner is reported (he_CharIllness), else a player figure (kind 6 / 7) healthier
   than that hears the news 0x163c. After all 0x300 the round is over: due the next day at 10:00, else due in 30
   minutes, the next day at 10:00 once that is 18:00 or later */
void he_RunDiseaseSim(AIJOB *e) {
  AICHAR *c;
  AIBLD *b;
  int n, cur, kind;
  float roll, immunity, risk, health;
  int primes[16];
  char text[0x200];

  if (e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  txt_Format(text,
             (intptr_t)"-------> RunSimKrankheiten: calculating at <Day = %i "
                       "Time = %i.2:%i.2>",
             ai_Time.year, ai_Time.hour, ai_Time.min);
  if (e->simStep == 0) {
    primes[0] = 1;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 0xb;
    primes[5] = 0xd;
    primes[6] = 0x11;
    primes[7] = 0x13;
    primes[8] = 0x2ed;
    primes[9] = 0x2ef;
    primes[10] = 0x2f3;
    primes[11] = 0x2f5;
    primes[12] = 0x2f9;
    primes[13] = 0x2fb;
    primes[14] = 0x2fd;
    primes[15] = 0x2ff;
    e->simStep = primes[util_Random(0x10)];
    e->simCursor = util_Random(0x300);
  }
  if (e->stage != 0)
    return;
  cur = e->simCursor;
  for (n = 12; n != 0; n--) {
    c = &ai_Chars[cur];
    if (he_IsSimCandidate(c) != 0) {
      roll = util_RandomF() * 100.0f;
      risk = 0.0f;
      immunity = 0.0f;
      if (ai_Chars[cur].bld2 != 0) {
        if (ai_BTypes[ai_Chars[cur].bld2->type].kind == 2)
          immunity =
              20.0f * (gm_BuildingSkill(ai_Chars[cur].bld2, 8, 1) * 0.0125f);
        else
          immunity =
              20.0f * (gm_BuildingSkill(ai_Chars[cur].bld2, 8, 1) * 0.02f);
      } else
        risk = (float)(25.0 - util_RandomF() * 20.0f * 0.5);
      if (ai_InventoryHas(c, 0x2b3) != 0)
        risk *= 0.75f;
      if (roll < risk - immunity && gm_CatchDisease(c, &kind, &health) != 0) {
        b = ai_Chars[cur].bld;
        if (b != 0 && b->owner != 0xffff && &ai_Chars[b->owner] != 0)
          he_CharIllness(e, c, &ai_Chars[b->owner], b, kind, health);
        else if (gm_CharacterHealth(c) > health &&
                 (ai_Chars[cur].kind == 6 || ai_Chars[cur].kind == 7)) {
          txt_Format(text, 0x163c, kind + 0x1632);
          he_ShowNews(ai_Chars[cur].netId, -1, text, 0, 0x5f7, ch_EmptyName);
        }
      }
    }
    cur = (e->simStep + cur) % 0x300;
    e->simDone++;
  }
  e->simCursor = cur;
  if (e->simDone >= 0x300) {
    e->end.hour = 0xa;
    e->simCursor = 0;
    e->simStep = 0;
    e->simDone = 0;
    e->end.year++;
    return;
  }
  gm_AddTime(&e->end, 0, 0x1e, 0);
  if (e->end.hour >= 0x12) {
    e->end.min = 0;
    e->end.hour = 0xa;
    e->end.year++;
  }
}
/* 0x54ef70, the init of the "Dunkle Ecke" (dark corner) robbery event 0x74: no carrier, a random walk over the
   buildings, 5 + random(4) steps, due a minute from now; it ends at once when another player's robbery runs at the
   same victim, or the victim building or its job table (object 0x12c) is gone; else the job table gets the year,
   and the carrier figure (cm_SendSpawnCharacter 0xe "DunkleEcke") is spawned at the victim */

void he_StartDarkCorner(AIJOB *e) {
  AIJOB *d = e;
  AIJOB *o;
  AIBLD *bld;
  AIOBJ *jt;

  if ((e->opts & 4) != 0)
    return;
  d->darkCornerCarrier = -1;
  d->darkCornerCursor = util_Random(0x100);
  d->darkCornerStep = ai_RandomStrides[util_Random(0x10)];
  d->darkCornerSteps = util_Random(4) + 5;
  d->darkCornerLoot = 0;
  d->darkCornerTarget = -1;
  e->end = ai_Time;
  e->start = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  for (o = he_FindEvent(1, 0, 0x74); o != 0; o = he_NextEvent()) {
    if (o->id != e->id && o->darkCornerVictim == d->darkCornerVictim) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
  }
  gm_FindById(&bld, 0, 0, d->darkCornerVictim);
  if (bld == 0 || (jt = gm_Query(bld->objList, 2, 6, 0, 0x12c)) == 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  {
    int year;

    year = ai_Time.year;
    cm_BeginFieldBlock(jt, jt->objId);
    cm_AddFieldDelta(4, 1, (char *)&jt->cornerYear - cm_FieldObject, &year);
    cm_SendFieldDeltas();
  }
  cm_BeginGroup("Dunkle Ecke");
  d->darkCornerCarrier =
      cm_SendSpawnCharacter(0xe, bld->id, -1, 0, 0, 0, "DunkleEcke");
  e->exSlot = cm_SendExSetHE(0, e);
  cm_EndGroup("Dunkle Ecke");
}
/* 0x54f160, the run handler of the "Dunkle Ecke" robbery event 0x74 (AIJOB.darkCorner*): stage 0 waits for the carrier
   figure (its id once spawned, else a day later stage 4); stage 1 walks the buildings to the next target of a kind
   in the mask 0x1a7fcc3a6 other than the victim ("Dunkle Ecke: next target = %G") and sends the carrier there;
   stage 2 waits until it is at the door, counts the steps down and raises the loot level by the chance of the
   target owner's skill 2, then sends the carrier on (stage 1) or, its steps done, to the victim (stage 3); stage 3
   at the victim (stage 4 at once) takes up to loot (0 .. 3; stage 4 draws it against the victim owner's skill 2)
   open crimes of others from ai_Crimes as proofs (cm_SendProofExecuted), writes them into the victim's job table
   and tells its owner (the news 0x18a9 / 0x18aa); freed with the flag 2 it removes the carrier */

void he_RunDarkCorner(AIJOB *e) {
  char text[0x400];
  AIJOB *d = e;
  AIBLD *bld;
  AICHAR *c;
  AIOBJ *jt;
  unsigned lo, hi;
  AIBTYPE *bt;
  int n, idx, i, k;
  int loot[3];
  float skill;

  if (e->stage == -1 || e->stage == -2) {
    if ((e->opts & 2) != 0) {
      c = gm_FindChar(d->darkCornerCarrier);
      if (c != 0) {
        cm_SendChrStop(c->netId);
        cm_SendKillCharacter(c->netId, 1);
      }
    }
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  switch (e->stage) {
  case 0:
    if (cm_GetSlotState(d->darkCornerCarrier) == 1) {
      d->darkCornerCarrier =
          ((AICHAR *)cm_GetSlotValue(d->darkCornerCarrier))->netId;
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(1, e);
      return;
    }
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->exSlot = cm_SendExSetHE(4, e);
    return;
  case 1:
    idx = d->darkCornerCursor;
    n = 0x100;
    do {
      bld = &ai_Blds[idx];
      lo = 0;
      bt = &ai_BTypes[bld->type];
      hi = 0;
      if ((unsigned char)bt->kind > 0x1f)
        hi = 1 << ((unsigned char)bt->kind - 0x20);
      else
        lo = 1 << (unsigned char)bt->kind;
      if (((lo & 0xa7fcc3a6) != 0 || (hi & 1) != 0) &&
          bld->id != d->darkCornerVictim)
        break;
      bld = 0;
      n--;
      idx = (idx + d->darkCornerStep) % 0x100;
    } while (n != 0);
    d->darkCornerCursor = (d->darkCornerStep + idx) % 0x100;
    if (bld == 0) {
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, (intptr_t)"Dunkle Ecke: next target = %G", bld);
    c = gm_FindChar(d->darkCornerCarrier);
    if (c != 0) {
      cm_SendChrStop(c->netId);
      cm_SendChrGotoBuilding(c->netId, bld->id, -1, 0, 1, "Dunkle Ecke");
      gm_AddTime(&e->end, 0, 5, 0);
      d->darkCornerTarget = bld->id;
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 2:
    gm_FindById(&bld, 0, 0, d->darkCornerTarget);
    gm_AddTime(&e->end, 0, 5, 0);
    if (bld == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    c = gm_FindChar(d->darkCornerCarrier);
    if (c == 0) {
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (sv_IsAtDoor(c, bld) == 0) {
      e->stage = 2;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    d->darkCornerSteps--;
    skill = gm_GetSkill(&ai_Chars[bld->owner], 2);
    if (d->darkCornerLoot < 1)
      d->darkCornerLoot++;
    else
      d->darkCornerLoot += util_RandomF() * 0.5f < skill ? 1 : 0;
    if (d->darkCornerLoot > 2)
      d->darkCornerSteps = 0;
    gm_FindById(&bld, 0, 0, d->darkCornerVictim);
    if (bld == 0 || bld->owner == 0xffff) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (d->darkCornerSteps <= 0) {
      cm_SendChrStop(c->netId);
      cm_SendChrGotoBuilding(c->netId, bld->id, d->darkCornerAmount, 0, 0,
                             "Dunkle Ecke");
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(1, e);
    return;
  case 3:
    gm_AddTime(&e->end, 0, 5, 0);
    gm_FindById(&bld, 0, 0, d->darkCornerVictim);
    if (bld == 0 || bld->owner == 0xffff) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    c = gm_FindChar(d->darkCornerCarrier);
    if (c != 0 && sv_IsAtDoor(c, bld) == 0) {
      e->stage = 3;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    d->darkCornerLoot = MAX(MIN(d->darkCornerLoot, 3), 0);
    if (d->darkCornerLoot != 0) {
      int w;

      loot[0] = -1;
      loot[1] = -1;
      loot[2] = -1;
      idx = util_Random(0x200);
      w = ai_CharWalkSteps[util_Random(8)];
      n = 0x200;
      i = 0;
      while (n != 0 && i < d->darkCornerLoot) {
        if (ai_Crimes[idx].id != -1 && ai_Crimes[idx].state == 1 &&
            ai_Crimes[idx].culprit != ai_Chars[bld->owner].netId &&
            gm_CompareTime(&e->start, &ai_Crimes[idx].time) != 1)
          loot[i++] = ai_Crimes[idx].id;
        n--;
        idx = (idx + w) % 0x200;
      }
      d->darkCornerLoot = i;
      for (k = 0; k < i; k++)
        cm_SendProofExecuted(loot[k], ai_Chars[bld->owner].netId);
      jt = gm_Query(bld->objList, 2, 6, 0, 0x12c);
      if (jt != 0) {
        cm_BeginFieldBlock(jt, jt->objId);
        for (k = 0; k < 3; k++)
          cm_AddFieldDelta(4, 1, (char *)&jt->recs[k] - cm_FieldObject,
                           &loot[k]);
        cm_SendFieldDeltas();
      }
    }
    if (d->darkCornerLoot != 0) {
      txt_Format(text, 0x18a9);
      he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5ec,
                             bld->id, d->darkCornerAmount, 0, ch_EmptyName);
    } else {
      txt_Format(text, 0x18aa);
      he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5ec,
                             bld->id, d->darkCornerAmount, 0, ch_EmptyName);
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    break;
  case 4:
    gm_FindById(&bld, 0, 0, d->darkCornerVictim);
    if (bld == 0 || bld->owner == 0xffff) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    d->darkCornerLoot = 0;
    for (k = 3; k != 0; k--) {
      float s = gm_GetSkill(&ai_Chars[bld->owner], 2);
      d->darkCornerLoot += util_RandomF() * 0.66f < s ? 1 : 0;
    }
    if (d->darkCornerLoot != 0) {
      int w;

      loot[0] = -1;
      loot[1] = -1;
      loot[2] = -1;
      idx = util_Random(0x200);
      w = ai_CharWalkSteps[util_Random(8)];
      n = 0x200;
      i = 0;
      while (n != 0 && i < d->darkCornerLoot) {
        if (ai_Crimes[idx].id != -1 && ai_Crimes[idx].state == 1 &&
            ai_Crimes[idx].culprit != ai_Chars[bld->owner].netId &&
            gm_CompareTime(&e->start, &ai_Crimes[idx].time) != 1)
          loot[i++] = ai_Crimes[idx].id;
        n--;
        idx = (idx + w) % 0x200;
      }
      d->darkCornerLoot = i;
      for (k = 0; k < i; k++)
        cm_SendProofExecuted(loot[k], ai_Chars[bld->owner].netId);
      jt = gm_Query(bld->objList, 2, 6, 0, 0x12c);
      if (jt != 0) {
        cm_BeginFieldBlock(jt, jt->objId);
        for (k = 0; k < 3; k++)
          cm_AddFieldDelta(4, 1, (char *)&jt->recs[k] - cm_FieldObject,
                           &loot[k]);
        cm_SendFieldDeltas();
      }
    }
    if (d->darkCornerLoot != 0) {
      txt_Format(text, 0x18a9);
      he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5ec,
                             bld->id, d->darkCornerAmount, 0, ch_EmptyName);
    } else {
      txt_Format(text, 0x18aa);
      he_MessageBoxQuickjump(ai_Chars[bld->owner].netId, -1, text, 0, 0x5ec,
                             bld->id, d->darkCornerAmount, 0, ch_EmptyName);
    }
    e->end = ai_Time;
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}

int mem_IsValid(void *p);

/* 0x54fb50, a Ghidra miss: the init of the effect event: the object +0xac (0x4fea50) must have a scene record (+0x61) and the effect word +0xc2 a table record (0x5ba620) with a duration (+4): +0xb4 = now + that duration (0x4fe140), +0xb0 = 0, state 0; else the event is freed */
void he_StartEffectEvent(AIJOB *e) {
  AIBLD *bld;
  G9DOMIZIL *d;

  gm_FindById(&bld, 0, 0, e->bldId);
  if (bld != 0 && bld->object != 0 &&
      (d = ai_FindUsableGood(e->effectGood)) != 0) {
    if (d->minutes != 0) {
      e->end6c = ai_Time;
      gm_AddTime(&e->end6c, 0, d->minutes, 0);
      e->effectObj = 0;
      e->stage = 0;
      return;
    }
  }
  he_FreeEvent(e);
}
/* 0x54fc00, the smoke emitter of the effect event: creates the effect 0x177 ("Rauch", the colour 0x64ffa0, a
   30 / 2 / 7.5 / 0.4 / 1 emitter) on the scene record (AIBLD.object) of the building o and returns its handle */

D3PARTSYS *he_CreateSmokeEffect(AIBLD *o) {
  AIBLD *bld = o;
  unsigned char col[4];
  int *color = (int *)col;
  D3VECTOR4 v;

  col[2] = 0xa0;
  col[1] = 0xff;
  col[0] = 0x64;
  v.x = 0.0f;
  v.y = 200.0f;
  v.z = 0.0f;
  return d3t_CreateEmitter(bld->object, "Rauch", 1, *color, &v.v, 0x12c, 1,
                           30.0f, 2.0f, 7.5f, 0.4f, 1.0f);
}
/* 0x54fc70, the points emitter of the effect event (like he_CreateSmokeEffect, the other colour 0x321e50 and
   size): creates the effect 0x178 ("punkte_nm_2", a 50 / 1 / 2 / 0.5 / 0.5 emitter) on the scene record
   (AIBLD.object) of the building o and returns its handle */

D3PARTSYS *he_CreatePointsEffect(AIBLD *o) {
  AIBLD *bld = o;
  unsigned char col[4];
  int *color = (int *)col;
  D3VECTOR4 v;

  col[2] = 0x50;
  col[1] = 0x1e;
  col[0] = 0x32;
  v.x = 0.0f;
  v.y = 50.0f;
  v.z = 0.0f;
  return d3t_CreateEmitter(bld->object, "punkte_nm_2", 1, *color, &v.v, 0x12c,
                           1, 50.0f, 1.0f, 2.0f, 0.5f, 0.5f);
}
/* 0x54fce0, the run handler of the effect event 0x76: stage 0 creates the emitter on the building's scene object
   (he_CreateSmokeEffect for the Domizil good 0x177, he_CreatePointsEffect for 0x178, in scene 0) and goes on to 1
   (no emitter: -1); stage 1 waits for the end time end6c, then stops the emitter's spawning and goes to 2; stage
   2 waits until the emitter has run out (flag 2) and ends; freed (-1 / -2) it deletes a valid emitter */

void he_RunEffectEvent(AIJOB *e) {
  AIBLD *bld;
  int scene;

  switch (e->stage) {
  case 0:
    gm_FindById(&bld, 0, 0, e->bldId);
    if (bld == 0 || bld->object == 0) {
      he_FreeEvent(e);
      return;
    }
    scene = d3_CurrentScene;
    d3if_SelectScene(0, 1);
    if (e->effectGood == 0x177)
      e->effectObj = he_CreateSmokeEffect(bld);
    else if (e->effectGood == 0x178)
      e->effectObj = he_CreatePointsEffect(bld);
    d3if_SelectScene(scene, 1);
    e->stage = e->effectObj != 0 ? 1 : -1;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end6c) == 1) {
      if (e->effectObj != 0 && mem_IsValid(e->effectObj) != 0)
        e->effectObj->spawnCount = 0;
      e->stage = 2;
      return;
    }
    if (e->effectObj == 0)
      e->stage = 0;
    return;
  case 2:
    if (e->effectObj == 0 || (e->effectObj->flags & 2) != 0)
      e->stage = -1;
    return;
  case -2:
  case -1:
    gm_FindById(&bld, 0, 0, e->bldId);
    if (e->effectObj != 0 && mem_IsValid(e->effectObj) != 0) {
      scene = d3_CurrentScene;
      d3if_SelectScene(0, 1);
      par_Delete(e->effectObj);
      d3if_SelectScene(scene, 1);
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x54fe80, the init of the send-home event 0x77 (its run handler he_RunSendHomeEvent): the due clock is now and
   homeUntil (+0xb0) is now + the minutes of the Domizil record 0x178; without that record (or without minutes) the
   event is freed */

void he_StartSendHomeEvent(AIJOB *e) {
  G9DOMIZIL *goods;

  e->end = ai_Time;
  goods = ai_FindUsableGood(0x178);
  if (goods != 0 && goods->minutes != 0) {
    e->homeUntil = ai_Time;
    gm_AddTime(&e->homeUntil, 0, goods->minutes, 0);
    return;
  }
  he_FreeEvent(e);
}
/* 0x54ff20, the run handler of the send-home event 0x77 (its init 0x54fe80): every 30 minutes until homeUntil, each
   living character standing in the building bldId and sent there (model->bldId) who has a home goes home with a
   chance of one half: its action is cleared (messages 0x47 / 0x4d) and it walks to its home object ("Unkendunk");
   a missing building or a freed event (-1 / -2) frees it */

void he_RunSendHomeEvent(AIJOB *e) {
  AIBLD *bld;
  AIOBJ *home;
  AICHAR *c;
  int i;

  if (e->stage < -2)
    return;
  if (e->stage < 0) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage != 0)
    return;
  bld = gm_FindBuildingById(e->bldId);
  if (bld == 0) {
    he_FreeEvent(e);
    return;
  }
  for (i = 0; i < 768; i++) {
    if (ai_Chars[i].health > 0 && ai_Chars[i].scene != 0 &&
        ai_Chars[i].bld == bld && ai_Chars[i].bld2 != 0 &&
        util_RandomF() > 0.5 && ai_Chars[i].scene->group == e->bldId) {
      c = &ai_Chars[i];
      home = gm_HomeObject(c->bld2);
      cm_SendCharClear(c->netId, 0, 0);
      cm_SendCharHalt(c->netId);
      if (home != 0)
        cm_SendChrGotoBuilding(c->netId, c->bld2->id, home->objId, 0, 0,
                               "Unkendunk");
    }
  }
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 0x1e, 0);
  if (gm_CompareTime(&ai_Time, &e->homeUntil) == 1)
    he_FreeEvent(e);
}

/* 0x550070, creates the reaper object ("Sensenmann", in scene 0) of the reaper event: both buildings reaperFrom and
   reaperTo must have a 3D object with a mesh driver; the first time it stands above reaperFrom's object (its height
   + 80) turned (y angle) towards the same point above reaperTo's, later at the cached reaperPos / reaperRot; the
   object's position and angles are cached (reaperPlaced = 1), its flags set and "*sensenmann.baf" played, the clock
   reaperClock started. 1 = created, 0 = a building or the object missing */
int he_CreateReaper(AIJOB *e) {
  int scene = d3_CurrentScene;
  AIBLD *bld, *from, *to;
  D3VECTOR4 pos, target, rot,
      dir; /* padded to 16 bytes, as the engine keeps them */
  D3OBJECT *obj;

  d3if_SelectScene(0, 1);
  gm_FindById(&bld, 0, 0, e->reaperFrom);
  if (bld != 0 && bld->object != 0 && bld->object->info != 0 &&
      bld->object->info->mesh != 0) {
    from = bld;
    gm_FindById(&bld, 0, 0, e->reaperTo);
    if (bld != 0 && bld->object != 0 && bld->object->info != 0 &&
        bld->object->info->mesh != 0) {
      to = bld;
      if (e->reaperPlaced == 0) {
        d3_PointToWorld(from->object, &from->object->pos, &pos.v);
        pos.y = pos.y + from->object->info->mesh->radius + 80.0f;
        d3_PointToWorld(to->object, &to->object->pos, &target.v);
        target.y = target.y + to->object->info->mesh->radius + 80.0f;
        rot.x = 0.0f;
        rot.y = 0.0f;
        rot.z = 0.0f;
        dir.x = target.x - pos.x;
        dir.y = target.y - pos.y;
        dir.z = target.z - pos.z;
        rot.y = d3_VecAngle2(&d3_ZAxis.v, &dir.v);
      } else {
        rot.x = e->reaperRot.x;
        rot.y = e->reaperRot.y;
        rot.z = e->reaperRot.z;
        pos.x = e->reaperPos.x;
        pos.y = e->reaperPos.y;
        pos.z = e->reaperPos.z;
        d3_PointToWorld(to->object, &to->object->pos, &target.v);
        target.y = target.y + to->object->info->mesh->radius + 80.0f;
        dir.x = target.x - pos.x;
        dir.y = target.y - pos.y;
        dir.z = target.z - pos.z;
      }
      obj = d3_CreateObject(0, &pos.v, &rot.v, "Sensenmann");
      e->reaper = obj;
      if (obj != 0) {
        e->reaperPlaced = 1;
        e->reaperRot.x = obj->rotation.x;
        e->reaperRot.y = obj->rotation.y;
        e->reaperRot.z = obj->rotation.z;
        e->reaperPos.x = obj->pos.x;
        e->reaperPos.y = obj->pos.y;
        e->reaperPos.z = obj->pos.z;
        obj->objectFlags &= ~2;
        e->reaper->stateFlags |= 0xc;
        e->reaper->flags &= ~4;
        d3t_PlayAnim(e->reaper, "*sensenmann.baf", 1);
        e->reaperClock = d3_Time;
        d3if_SelectScene(scene, 1);
        return 1;
      } else {
        d3if_SelectScene(scene, 1);
        return 0;
      }
    }
  }
  d3if_SelectScene(scene, 1);
  return 0;
}

/* 0x550370, one step of the reaper's flight to the building reaperTo (in scene 0): while the object follows a path
   animation only the clock reaperClock is refreshed; else the target is the point 80 above the ground under
   reaperTo's object: closer than 45 (horizontally) the flight ends (reaperPlaced = 0, returns 2); otherwise the
   object moves along the direction by the time since reaperClock times a speed of 0.5 + 0.25 per cm_SpeedLevel,
   rising (0.978 per time unit, with a tenth of the step) while it is less than 80 above the ground there, and its
   position and angles are cached; 1 = flying, 0 = the object or the building missing
   @deep deep s48: all 64 operand orders of the three dir *= step and target = dir + at lines are one code
   (VC6 orders the operands itself); (dir.y) / (at.y) parentheses, a (float) cast: = control; the
   assignment inside the sum (target.y = (dir.y = step * dir.y) + at.y: fpu 23, all three: 19), the scale
   and sum interleaved (20), dir.y scaled first (12); dist as sqrt(x*x + z*z) with dir.y = 0.0f anywhere: =
   control (same code, plainer). Left: target.y's fld at.y / fadd dir.y at 0x5505bf. prior: deep s24: dist
   written as the full length sqrt(x*x + y*y + z*z) with dir.y = 0.0f (VC6 folds the zero term: every term
   order = control; kept, it gives the dir.y = 0 store its use). flip.py --want the original's fld dir.y /
   fadd at.y for target.y: 5 hits, the only non-local one deletes dir.y = 0.0f (then the order is right but
   the original's zero store is missing: draft 1); dir.y = 0.0f at each position of the first dir block: =
   control or worse (5..19). Left: target.y = dir.y + at.y emitted as fld at.y / fadd dir.y (the original
   dir.y first, as x and z). */
int he_MoveReaper(AIJOB *e) {
  int scene = d3_CurrentScene;
  AIBLD *bld;
  D3VECTOR4 target, at, dir;
  float dist, step;
  int ret;

  d3if_SelectScene(0, 1);
  if (e->reaper != 0 && e->reaper->info != 0 && e->reaper->info->mesh != 0) {
    gm_FindById(&bld, 0, 0, e->reaperTo);
    if (bld != 0 && bld->object != 0 && bld->object->info != 0 &&
        bld->object->info->mesh != 0) {
      if (e->reaper->path != 0) {
        e->reaperClock = d3_Time;
        d3if_SelectScene(scene, 1);
        return 1;
      }
      d3_PointToWorld(bld->object, &bld->object->pos, &target.v);
      d3_PointToWorld(e->reaper, &e->reaper->pos, &at.v);
      dir.x = target.x - at.x;
      dir.y = 0.0f;
      dir.z = target.z - at.z;
      dist = (float)sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
      {
        int x, z;
        float ground;

        d3_GetHeightAt(d3_Scenes[0].hmap, &target.v, &x, &z, &ground);
        target.y = ground + 80.0f;
      }
      dir.x = target.x - at.x;
      dir.y = target.y - at.y;
      dir.z = target.z - at.z;
      if (dist < 45.0f) {
        ret = 2;
        e->reaperPlaced = 0;
      } else {
        D3SM *hm = d3_Scenes[0].hmap;
        int x, z;
        float h;

        ret = 1;
        step = (float)d3_Time - e->reaperClock;
        step = ((float)cm_GetSpeedLevel() * 0.25f + 0.5f) * step;
        e->reaperClock = d3_Time;
        d3_Normalize(&dir.v);
        dir.x = step * dir.x;
        dir.y = step * dir.y;
        dir.z = step * dir.z;
        target.x = dir.x + at.x;
        target.y = dir.y + at.y;
        target.z = dir.z + at.z;
        d3_GetHeightAt(hm, &target.v, &x, &z, &h);
        if (h + 80.0f > target.y) {
          target.y = step * 0.978 + target.y;
          target.x = step * dir.x * 0.1f + at.x;
          target.z = step * dir.z * 0.1f + at.z;
        }
        e->reaperRot.x = e->reaper->rotation.x;
        e->reaperRot.y = e->reaper->rotation.y;
        e->reaperRot.z = e->reaper->rotation.z;
        e->reaperPos.x = target.x;
        e->reaperPos.y = target.y;
        e->reaperPos.z = target.z;
        d3_SetObjectPos(e->reaper, &target.v);
      }
      d3if_SelectScene(scene, 1);
      return ret;
    }
  }
  d3if_SelectScene(scene, 1);
  return 0;
}
/* 0x5506c0, turns the reaper towards its next target: both the reaper object and the building reaperTo's object
   need a mesh driver; the target is the point above reaperTo's object (its height + 80), the object's angles are
   set from the direction to it (d3_VecAngle2 writes them), cached in reaperRot with the reaper's own world
   position in reaperPos, and reaperPlaced = 1. 1 = done, 0 = an object missing */
int he_AimReaper(AIJOB *e) {
  int scene = d3_CurrentScene;
  AIBLD *bld;
  D3VECTOR4 target, at, dir;

  d3if_SelectScene(0, 1);
  if (e->reaper != 0 && e->reaper->info != 0 && e->reaper->info->mesh != 0) {
    gm_FindById(&bld, 0, 0, e->reaperTo);
    if (bld != 0 && bld->object != 0 && bld->object->info != 0 &&
        bld->object->info->mesh != 0) {
      d3_PointToWorld(bld->object, &bld->object->pos, &target.v);
      target.y = target.y + bld->object->info->mesh->radius + 80.0f;
      d3_PointToWorld(e->reaper, &e->reaper->pos, &at.v);
      dir.x = target.x - at.x;
      dir.y = target.y - at.y;
      dir.z = target.z - at.z;
      d3_VecAngle2(&dir.v, &e->reaper->rotation);
      e->reaperRot.x = e->reaper->rotation.x;
      e->reaperRot.y = e->reaper->rotation.y;
      e->reaperRot.z = e->reaper->rotation.z;
      e->reaperPos.x = at.x;
      e->reaperPos.y = at.y;
      e->reaperPos.z = at.z;
      e->reaperPlaced = 1;
      d3if_SelectScene(scene, 1);
      return 1;
    }
  }
  d3if_SelectScene(scene, 1);
  return 0;
}
int d3t_PlaceObjectV(struct D3OBJECT *camera, struct D3VECTOR *pos,
                     struct D3VECTOR *dir, int unk, char flags);

/* 0x550850, turns the reaper around towards the building reaperTo once it arrived: both objects need a mesh driver;
   the angle between the object's forward axis (its z axis in the world) and the direction to the point above
   reaperTo's object (its height + 80) is added to its y angle, and d3t_PlaceObjectV moves it to its own position
   with those angles over 0x78 (flags 8). 1 = done, 0 = an object missing */
int he_TurnReaper(AIJOB *e) {
  int scene = d3_CurrentScene;
  AIBLD *bld;
  D3VECTOR4 rot, target, at, dir;
  float angle;

  d3if_SelectScene(0, 1);
  if (e->reaper != 0 && e->reaper->info != 0 && e->reaper->info->mesh != 0) {
    gm_FindById(&bld, 0, 0, e->reaperTo);
    if (bld != 0 && bld->object != 0 && bld->object->info != 0 &&
        bld->object->info->mesh != 0) {
      d3_PointToWorld(bld->object, &bld->object->pos, &target.v);
      target.y = target.y + bld->object->info->mesh->radius + 80.0f;
      d3_PointToWorld(e->reaper, &e->reaper->pos, &at.v);
      dir.x = target.x - at.x;
      dir.y = target.y - at.y;
      dir.z = target.z - at.z;
      d3_DirToWorld(e->reaper, &d3_ZAxis.v, &rot.v);
      angle = d3_VecAngle2(&rot.v, &dir.v);
      if (e->reaper == 0) {
        d3if_SelectScene(scene, 1);
        return 0;
      }
      rot.x = e->reaper->rotation.x;
      rot.y = e->reaper->rotation.y;
      rot.z = e->reaper->rotation.z;
      rot.y = rot.y + angle;
      d3t_PlaceObjectV(e->reaper, &at.v, &rot.v, 0x78, 8);
      d3if_SelectScene(scene, 1);
      return 1;
    }
  }
  d3if_SelectScene(scene, 1);
  return 0;
}
void ai_PlagueMessageAll(void);

/* 0x5509f0, the allocation handler of the reaper event ("Sensenmann"): due now; from reaperNext it walks the 0x100
   buildings by reaperStep (mod 0x100) for the next one in use whose kind is in the 64-bit mask 0x1807c4110 (as the
   plague event, he_RunPlague), notes where the next walk starts, and flies the reaper to it (reaperTo, read even when
   none was found) by creating its object; nothing found or no object: the record is freed. Posted again 15 minutes
   later */
void he_StartReaper(AIJOB *e) {
  char text[0x200];
  AIBLD *o;
  AIBTYPE *bt;
  unsigned int lo, hi;
  int n, k;

  e->end = ai_Time;
  n = 0x100;
  k = e->reaperNext;
  do {
    o = &ai_Blds[k];
    hi = 0;
    bt = &ai_BTypes[o->type];
    lo = 0;
    if ((unsigned char)bt->kind > 0x1f)
      hi = 1 << ((unsigned char)bt->kind - 0x20);
    else
      lo = 1 << (unsigned char)bt->kind;
    if (o->owner != 0xffff && ((lo & 0x807c4110) != 0 || (hi & 1) != 0))
      break;
    o = 0;
    n--;
    k = (k + e->reaperStep) % 0x100;
  } while (n != 0);
  e->reaperNext = (e->reaperStep + k) % 0x100;
  if (o == 0)
    he_FreeEvent(e);
  else
    txt_Format(text, (intptr_t)"EvtSensenmann: next target = %G", o);
  e->reaperTo = o->id;
  if (he_CreateReaper(e) == 0)
    he_FreeEvent(e);
  gm_AddTime(&e->end, 0, 0xf, 0);
}
/* 0x550b60, the run handler of the reaper event ("Sensenmann"): freed (-1 / -2) it deletes the reaper object, stops
   its track and frees the record; it (re)creates the object when there is none (failing: freed) and starts the track
   "cd2\DerSeuchenzug.mp3" once (he_ReaperMusic). Stage 0 flies (he_MoveReaper, again in 2 minutes); arrived, the
   target becomes reaperFrom and while reaperLeft > 0 the next building of the kind mask is the new target (none:
   -1), at 0 the reaper turns back to reaperHome; turned (he_TurnReaper) it goes to stage 2 in 15 minutes, else -1.
   Stage 2 aims it (he_AimReaper) and flies on (0), or ends with the plague message to all (-1) */
void he_RunReaper(AIJOB *e) {
  char text[0x200];
  AIBLD *o;
  AIBTYPE *bt;
  unsigned int lo, hi;
  int n, k, r;

  if (e->stage == -2 || e->stage == -1) {
    if (e->reaper != 0)
      d3if_Delete(e->reaper);
    if (he_ReaperMusic != 0)
      cm_EndSpecialTrack();
    he_ReaperMusic = 0;
    he_FreeEvent(e);
    return;
  }
  if (e->reaper == 0 && he_CreateReaper(e) == 0) {
    he_FreeEvent(e);
    if (he_ReaperMusic != 0)
      cm_EndSpecialTrack();
    he_ReaperMusic = 0;
    return;
  }
  if (he_ReaperMusic == 0) {
    cm_PlaySpecialTrack("cd2\\DerSeuchenzug.mp3");
    if (snd_TrackHandles.current != 0)
      he_ReaperMusic = 1;
  }
  e->end = ai_Time;
  switch (e->stage) {
  case 0:
    r = he_MoveReaper(e);
    if (r == 1) {
      e->stage = 0;
      gm_AddTime(&e->end, 0, 2, 0);
      return;
    }
    if (r == 2) {
      e->reaperFrom = e->reaperTo;
      if (e->reaperLeft <= 0) {
        if (e->reaperLeft == 0) {
          e->reaperTo = e->reaperHome;
          if (he_TurnReaper(e) != 0) {
            gm_AddTime(&e->end, 0, 0xf, 0);
            e->reaperLeft--;
            e->stage = 2;
            return;
          }
          gm_AddTime(&e->end, 0, 2, 0);
        }
        e->stage = -1;
        return;
      }
      n = 0x100;
      k = e->reaperNext;
      do {
        o = &ai_Blds[k];
        lo = 0;
        bt = &ai_BTypes[o->type];
        hi = 0;
        if ((unsigned char)bt->kind > 0x1f)
          hi = 1 << ((unsigned char)bt->kind - 0x20);
        else
          lo = 1 << (unsigned char)bt->kind;
        if (o->owner != 0xffff && ((lo & 0x807c4110) != 0 || (hi & 1) != 0))
          break;
        o = 0;
        n--;
        k = (k + e->reaperStep) % 0x100;
      } while (n != 0);
      e->reaperNext = (e->reaperStep + k) % 0x100;
      if (o == 0) {
        e->stage = -1;
        return;
      }
      txt_Format(text, (intptr_t)"EvtSensenmann: next target = %G", o);
      e->reaperTo = o->id;
      e->reaperLeft--;
      if (he_TurnReaper(e) != 0) {
        gm_AddTime(&e->end, 0, 0xf, 0);
        e->stage = 2;
      } else {
        gm_AddTime(&e->end, 0, 2, 0);
        e->stage = -1;
      }
      return;
    }
    gm_AddTime(&e->end, 0, 2, 0);
    e->stage = -1;
    return;
  case 2:
    gm_AddTime(&e->end, 0, 2, 0);
    if (he_AimReaper(e) != 0) {
      e->stage = 0;
    } else {
      ai_PlagueMessageAll();
      e->stage = -1;
    }
  }
}
/* 0x550ea0, the init of the ranking event 0x79 (its run handler he_RunRanking): stage 0 and the due clock today at
   7:00 (hour 7, minute 0) */

void he_StartRanking(AIJOB *e) {

  e->stage = 0;
  e->end = ai_Time;
  e->end.hour = 7;
  e->end.min = 0;
}

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

/* 0x550ee0, the run handler of the ranking event: in the stage 0, every hour of the day, it ranks the players
   (gm_RankPlayers) and sends the ranking over the network (udp_Send): a head packet with the column titles and the own
   player's name, then a line per ranked player; at 21 o'clock it goes to stage 1, which waits a day (0x18 hours) and
   starts again at 7:00 */
void he_RunRanking(AIJOB *e) {
  int cnt = 8;
  GMRANK recs[8];
  HERANKHEAD head;
  HERANKLINE line;
  char tmp[0x100];
  AICHAR *c;
  int i;

  switch (e->stage) {
  case 1:
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 7;
    e->end.min = 0;
    e->stage = 0;
    return;
  case 0:
    gm_RankPlayers(&cnt, recs);
    head.one = 1;
    head.kind = 3;
    head.size = 0xcf;
    for (i = 0; i < 5; i++) {
      txt_Format(tmp, (intptr_t)"%s", 0x16b7 + i);
      strncpy(head.titles[i], tmp, 0x18);
      head.titles[i][0x17] = 0;
    }
    strcpy(head.player, ai_PlayerSlots[ai_OwnPlayer].townName);
    strcpy(head.worthTitle, "Verm\xf6gen");
    strcpy(head.pointsTitle, "Gewinnpunkte");
    head.count = (unsigned char)cnt;
    udp_Send((char *)&head, head.size);
    for (i = 0; i < cnt; i++) {
      line.one = 1;
      line.kind = 2;
      line.size = 0xb9;
      c = &ai_Chars[recs[i].id];
      line.netId = c->netId;
      line.worth = gm_ConvertMoney(recs[i].worth, ai_OwnPlayer);
      line.points = recs[i].points;
      line.count = (unsigned char)cnt;
      if (c->kind == 6 || c->kind == 7)
        line.player = 1;
      else
        line.player = 2;
      memcpy(line.skills, c->skills, 5);
      strncpy(line.name, c->name, 0x18);
      line.name[0x17] = 0;
      txt_Format(tmp, (intptr_t)"%s", (c->sex != 0 ? 0x18f : 0x130) + c->jobId);
      strncpy(line.job, tmp, 0x20);
      line.job[0x1f] = 0;
      txt_Format(tmp, (intptr_t)"%s", (c->sex != 0 ? 0x11e : 0x114) + c->level);
      strncpy(line.rank, tmp, 0x20);
      line.job[0x1f] = 0; /* sic: the original ends job again, not rank */
      txt_Format(tmp, (intptr_t)"%s",
                 (c->sex != 0 ? 0x27b : 0x253) + c->officeKind);
      strncpy(line.office, tmp, 0x24);
      line.office[0x23] = 0;
      txt_Format(tmp, (intptr_t)"%s",
                 (c->sex != 0 ? 0x27b : 0x253) + c->secondOffice);
      strncpy(line.office2, tmp, 0x24);
      line.office2[0x23] = 0;
      udp_Send((char *)&line, line.size);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 1, 0, 0);
    if (e->end.hour >= 0x15)
      e->stage++;
  }
}
/* 0x5512c0, the alloc handler of the walk event 0x7a (its run handler he_RunWalk): stage 0; unless opts still says
   the event is not started yet (bit 4) it frees the ten walk slots (+0xac: character and target -1, stage / state /
   step / building index 0), sets the due clock today at 11:00 and posts the event (handle in exSlot) */

void he_StartWalk(AIJOB *e) {
  AIJOB *w = e;
  int i;

  e->stage = 0;
  if ((e->opts & 4) == 0) {
    for (i = 0; i < 10; i++) {
      w->walkSlots[i].chr = -1;
      w->walkSlots[i].target = -1;
      w->walkSlots[i].stage = 0;
      w->walkSlots[i].state = 0;
      w->walkSlots[i].step = 0;
      w->walkSlots[i].bldIndex = 0;
    }
    e->end = ai_Time;
    e->end.hour = 0xb;
    e->end.min = 0;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}

/* 0x551340, steps one slot of the walk event 0x5512c0: a free slot gives 0; the character (gm_FindChar) walks to
   its building (gm_FindById): while it is not at the door yet (sv_IsAtDoor) and the hour is before 22 the result is
   2 (still on its way); else, or when the character or the building is gone, the slot is freed, a character with a
   scene model is stopped (cm_SendChrStop, message 0x57) and its field 0x1c8 loses the bit 0x40000000, result 0 */
int he_StepWalkSlot(HEWALKSLOT *s) {
  AICHAR *c;
  AIBLD *bld;

  if (s->chr == -1)
    return 0;
  c = gm_FindChar(s->chr);
  if (c == 0) {
    s->chr = -1;
    s->target = -1;
    s->stage = 0;
    s->state = 0;
    s->step = 0;
    s->bldIndex = 0;
    return 0;
  }
  gm_FindById(&bld, 0, 0, s->target);
  if (bld == 0) {
    if (c->scene != 0) {
      cm_SendChrDelete(s->chr);
      cm_SendSetField(c->netId, 0x1c8, 4, 0, 0x40000000);
    }
    s->chr = -1;
    s->target = -1;
    s->stage = 0;
    s->state = 0;
    s->step = 0;
    s->bldIndex = 0;
    return 0;
  }
  if (sv_IsAtDoor(c, bld) == 0 && ai_Time.hour < 0x16)
    return 2;
  if (c->scene != 0) {
    cm_SendChrStop(c->netId);
    cm_SendChrDelete(s->chr);
  }
  s->chr = -1;
  s->target = -1;
  s->stage = 0;
  s->state = 0;
  s->step = 0;
  s->bldIndex = 0;
  cm_SendSetField(c->netId, 0x1c8, 4, 0, 0x40000000);
  return 0;
}

/* 0x551440, fills a free slot of the walk event 0x5512c0 with a character on a walk through town: none (-1) when
   the n walkers plus the weather (snow 1, rain 4) reach 10, the slot is in use or it is before 11 o'clock; a
   partner for the player's character is looked for (ai_FindPartnersRandomWalk, the two kind masks 0x20a0 /
   0x402c20, the second first when (n - m) / (n + 1) is below 0.66); its building is its own (bld2)
   or one picked for the player (ai_PickActionBuilding); a random roll below n / 10 gives none; else the character
   gets the bit 0x40000000 of field 0x1c8, the slot its id, the building, stage 1, state 9 (0x29 with +0x1f0), a
   random step and the building's index, and it is placed on the stage there: the result is the message's handle */
int he_FillWalkSlot(HEWALKSLOT *slot, int n, int m) {
  int kinds[2];
  int tgt = -1;
  unsigned short id;
  AICHAR *ch;
  int idx;
  union {
    struct {
      unsigned int lo, hi;
    } s;
    __int64 q;
  } mask;

  kinds[0] = HE_WALK_PARTNERS1;
  kinds[1] = HE_WALK_PARTNERS2;
  if (n + (d3t_Snow != 0) + (d3t_Rain != 0 ? 2 : 0) * 2 >= 10 ||
      slot->state != 0 || ai_Time.hour < 0xb)
    return -1;
  if ((float)(n - m) / (float)(n + 1) < 0.66f) {
    kinds[0] = HE_WALK_PARTNERS2;
    kinds[1] = HE_WALK_PARTNERS1;
  }
  if (ai_FindPartnersRandomWalk(&ai_Chars[ai_PlayerId], 1, &kinds[0], 0.0f,
                                100.0f, &id) == 0 &&
      ai_FindPartnersRandomWalk(&ai_Chars[ai_PlayerId], 1, &kinds[1], 0.0f,
                                100.0f, &id) == 0)
    return -1;
  ch = &ai_Chars[id];
  mask.s.lo = 0xa7f4c3a0;
  mask.s.hi = 1; /* HE_WALK_BUILDINGS, set as two dwords */
  if (ch->bld2 != 0)
    tgt = ch->bld2->id;
  else if (ai_PickActionBuilding(&ai_Chars[ai_PlayerId], 0, mask.q, 0, 100.0f,
                                 &tgt) == 0)
    return -1;
  if (util_RandomF() > n * 0.1f) {
    AIBLD *bld;

    gm_FindById(&bld, 0, 0, tgt);
    if (bld == 0)
      return -1;
    idx = bld - ai_Blds;
    cm_SendSetField(ch->netId, 0x1c8, 4, 0x40000000, 0);
    slot->chr = ch->netId;
    slot->target = tgt;
    slot->stage = 1;
    slot->state = 9;
    if (ch->v1f0 != 0)
      slot->state = 0x29;
    slot->step = (unsigned char)ai_RandomStrides[util_Random(0x10)];
    slot->bldIndex = (unsigned char)idx;
    slot->holdHour = 0xff;
    return cm_SendPlaceOnStage(ch->netId, tgt, -1);
  }
  return -1;
}
/* 0x5516a0, plays a random gesture animation (cm_SendChrAnim) on the character c: one of four draws, each queuing one
   to three animations ("gestik/haende_reiben" ends every one) */
void he_PlayGestures(AICHAR *c) {
  switch (util_Random(4)) {
  case 0:
    cm_SendChrAnim(c->netId, "gestik/haende_reiben", 1);
    break;
  case 1:
    cm_SendChrAnim(c->netId, "gestik/herranwinken", 1);
    cm_SendChrAnim(c->netId, "gestik/haende_reiben", 1);
    break;
  case 2:
    cm_SendChrAnim(c->netId, "gestik/kinn_kratzen", 1);
    cm_SendChrAnim(c->netId, "gestik/haende_reiben", 1);
    break;
  case 3:
    cm_SendChrAnim(c->netId, "gestik/durch_haar_fahr", 1);
    cm_SendChrAnim(c->netId, "gestik/herranwinken", 1);
    cm_SendChrAnim(c->netId, "gestik/haende_reiben", 1);
    break;
  }
}

int he_PickNearBuilding(AICHAR *c, int n, AIBLD **blds, int *bldId, int *objId);

/* 0x551780, steps a character's walk through town (a slot of the walk event 0x5512c0): a character that is gone
   frees the slot; one whose building is gone looks for the next one at once; else it waits until it is at the
   building's door, a character whose scene model stands in a building is held there (bit 0x1000 of field 0x1c8
   cleared, its hour noted) until the next hour, then released (the bit set, cm_SendCharHalt); a walk with more
   stages than 10 less the budget (2 + a random 0 .. 5 + the weather) ends (state 4); every budget / 2 + 1 stages it
   plays an animation (he_PlayGestures) instead of walking on. The next building: above an even roll one of the up to
   0x20 inns (gm_BuildQuery 1, 5, 0x16) the one he_PickNearBuilding picks (only looked up by gm_FindBuildingById, the
   walk keeps its building), else the next of the 0x100 buildings in steps of
   the slot's step whose kind is in HE_WALK_BUILDINGS; the character is sent there (cm_SendChrGotoBuilding
   "Sim Politicians", its flag 0 for the kinds 0x16 / 7 / 0xf, else 1) */
void he_StepWalk(HEWALKSLOT *s) {
  AIBLD *b = 0;
  int held;
  int budget;
  AIBLD *inns[0x20];
  AICHAR *c;
  CHARACTER *model;
  int weather, n, hour;
  int idx = 0;
  unsigned int lo, hi;
  AIBTYPE *bt;

  c = gm_FindChar(s->chr);
  if (c == 0) {
    s->chr = -1;
    s->target = -1;
    s->stage = 0;
    s->state = 0;
    s->step = 0;
    s->bldIndex = 0;
    s->holdHour = 0xff;
    return;
  }
  gm_FindById(&b, 0, 0, s->target);
  held = 0;
  if (b != 0) {
    weather = (d3t_Rain != 0 ? 2 : 0) + (d3t_Snow != 0);
    budget = weather + util_Random(6) + 2;
    if (sv_IsAtDoor(c, b) == 0)
      return;
    model = c->scene;
    if (model != 0 && model->group != -1 && model->scriptGroup != -1) {
      hour = s->holdHour;
      s->state |= 0x40;
      held = 1;
      if (hour == 0xff) {
        s->holdHour = (signed char)ai_Time.hour;
        cm_SendSetField(c->netId, 0x1c8, 4, 0, 0x1000);
        return;
      }
      if (ai_Time.hour <= hour + 1)
        return;
      s->state &= ~0x40;
      cm_SendSetField(c->netId, 0x1c8, 4, 0x1000, 0);
      cm_SendCharHalt(c->netId);
      s->holdHour = 0xff;
    }
    if (10 - s->stage < budget) {
      s->state |= 4;
      return;
    }
    if ((s->state & 0x10) == 0) {
      budget = budget / 2 + 1;
      if ((s->stage + 2) % budget == 0 && held == 0) {
        s->stage++;
        he_PlayGestures(c);
        s->state |= 0x10;
        return;
      }
    }
  }
  s->state &= ~0x10;
  cm_SendChrStop(c->netId);
  if (util_RandomF() > 0.5f) {
    AIBLD *e = gm_BuildQuery(1, 5, 0x16);
    int bldId, objId;

    n = 0;
    if (e != 0) {
      do {
        if (n >= 0x20)
          break;
        if (e->owner != 0xffff && e->object != 0)
          inns[n++] = e;
        e = gm_BuildNext();
      } while (e != 0);
      if (n != 0 && he_PickNearBuilding(c, n, inns, &bldId, &objId) != 0)
        gm_FindBuildingById(bldId);
    }
  } else {
    /* the budget is the step from here, held the buildings left */
    held = 0x100;
    idx = s->bldIndex;
    budget = s->step;
    idx = (idx + budget) % 0x100;
    do {
      b = &ai_Blds[idx];
      if (b->type != 0) {
        bt = &ai_BTypes[b->type];
        lo = 0;
        hi = 0;
        if (bt->kind > 0x1f)
          hi = 1 << (bt->kind - 0x20);
        else
          lo = 1 << bt->kind;
        if (b->object != 0 &&
            ((lo & (unsigned int)HE_WALK_BUILDINGS) != 0 ||
             (hi & (unsigned int)(HE_WALK_BUILDINGS >> 32)) != 0))
          break;
        b = 0;
      }
      held--;
      idx = (idx + budget) % 0x100;
    } while (held != 0);
  }
  if (b == 0) {
    s->state |= 4;
    return;
  }
  s->bldIndex = (unsigned char)idx;
  s->target = b->id;
  s->stage++;
  bt = &ai_BTypes[b->type];
  if (bt->kind == 0x16 || bt->kind == 7 || bt->kind == 0xf)
    cm_SendChrGotoBuilding(s->chr, s->target, -1, 0, 0, "Sim Politicians");
  else
    cm_SendChrGotoBuilding(s->chr, s->target, -1, 0, 1, "Sim Politicians");
}
/* 0x551b70, the run handler of the walk event 0x7a (its alloc handler he_StartWalk): the state -1 / -2 frees the
   record, and a record with the option 4 or a pending cm slot (exSlot, cm_GetSlotState) does nothing; else the due
   clock is set to now and posted 5 minutes later, and after 17:00 the ten slots are stepped by he_StepWalkSlot (a
   slot still walking counts; when none walks, the due clock moves to midnight of the next day), before that each
   slot is stepped by he_StepWalkSlot (state 4, done) or he_StepWalk and the ones with state 1 counted; then up to
   ten tries to fill a free slot (he_FillWalkSlot) post the event again 1 minute later */
void he_RunWalk(AIJOB *e) {
  AIJOB *w = e;
  int st = e->stage;
  int n, i, r;
  HEWALKSLOT *s;

  if (st == -1 || st == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 5, 0);
  e->exSlot = -1;
  n = 0;
  if (e->end.hour >= 0x11) {
    s = w->walkSlots;
    for (i = 10; i != 0; i--) {
      if (he_StepWalkSlot(s) == 2)
        n++;
      s++;
    }
    if (n == 0) {
      e->end.hour = (unsigned short)n; /* n is 0 here */
      e->end.year = e->end.year + 1;
    }
    cm_SendExSetHE(0, e);
    return;
  }
  for (i = 0; i < 10; i++) {
    if ((w->walkSlots[i].state & 4) != 0)
      he_StepWalkSlot(&w->walkSlots[i]);
    else
      he_StepWalk(&w->walkSlots[i]);
    if ((w->walkSlots[i].state & 1) != 0)
      n++;
  }
  for (i = 0; i < 10; i++) {
    r = he_FillWalkSlot(&w->walkSlots[i], n, 0);
    e->exSlot = r;
    if (r != -1) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 1, 0);
      break;
    }
  }
  cm_SendExSetHE(0, e);
}
/* 0x551d00, the alloc handler of the six-group event (type 0x7d, the run handler 0x551d70 walks its six figure
   groups at +0xb0): gm_Shuffled fills the six ids and each is incremented (0 -> the first figure), the due time
   is the clock now with hour 9 / min 0, and the state becomes 0xc */

void he_InitSixGroupEvent(AIJOB *e) {
  int i;
  int *q;

  gm_Shuffled(6, e->groups);
  for (q = e->groups, i = 0; i < 6; i++)
    *q++ += 1;
  e->end = ai_Time;
  e->stage = 0xc;
  e->end.hour = 9;
  e->end.min = 0;
}

/* 0x551d70, the run handler of the six-group event 0x7d (he_InitSixGroupEvent): at stage 0xc it tells every player
   character (kind 6 / 7) the news (text 0x10bc, of the variant 1 0x10be, with the own player's name) and starts
   stage 0 an hour later; the stages 0 .. 5 take the officials of the column groups[stage] (amt_GetColumnOffices, up
   to 6): of the variant 1 an official of level 9 / 6 sends an office message two times in three; every official who
   is not of kind 3 loses 3 x level + random(3 x level) of opinion with each character whose building he owns, and a
   player character among them who lost any is told (0x10bd / 0x10bf); then the next stage an hour later. Other
   stages free the event */
void he_RunSixGroupEvent(AIJOB *ev) {
  AMTKIND kind;
  AMTREC offices[6];
  char text[0x800];
  AMTREC *o;
  int col;
  AICHAR *p, *c;
  int n, i, k, hit;

  if (ev->stage == 0xc) {
    if (ev->grpMode == 0)
      txt_Format(text, 0x10bc, ai_PlayerSlots[ai_OwnPlayer].townName);
    else
      txt_Format(text, 0x10be, ai_PlayerSlots[ai_OwnPlayer].townName);
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7)
        he_ShowNews(ai_Chars[i].netId, -1, text, 0x20, 0x600, ch_EmptyName);
    }
    ev->stage = 0;
    gm_AddTime(&ev->end, 1, 0, 0);
    return;
  }
  if (ev->stage < 0 || ev->stage >= 6) {
    he_FreeEvent(ev);
    return;
  }
  col = ev->groups[ev->stage];
  n = amt_GetColumnOffices(col, 6, offices);
  for (k = 0; k < n; k++) {
    o = &offices[k];
    p = gm_FindChar(o->owner);
    if (p != 0 && amt_GetKind(o->kind, &kind) != 0) {
      if (ev->grpMode == 1 && (kind.level == 9 || kind.level == 6) &&
          util_Random(3) != 0)
        amt_SendOfficeMessage(o->idx, 0, 0, 4, 0xff);
      if (p->kind != 3) {
        hit = 0;
        for (i = 0; i < 768; i++) {
          c = &ai_Chars[i];
          if (c->bld != 0 && c->netId != p->netId && c->bld->owner == p->id) {
            hit++;
            cm_SendRelations(p->netId, c->netId,
                             -util_Random(kind.level * 3) - kind.level * 3, 1);
          }
        }
        if (hit != 0 && (p->kind == 6 || p->kind == 7)) {
          if (ev->grpMode == 0) {
            txt_Format(text, 0x10bd, p->id);
            he_ShowNews(p->netId, -1, text, 1, 0x5fd, ch_EmptyName);
          } else {
            txt_Format(text, 0x10bf, p->id);
            he_ShowNews(p->netId, -1, text, 1, 0x5fd, ch_EmptyName);
          }
        }
      }
    }
  }
  ev->stage++;
  gm_AddTime(&ev->end, 1, 0, 0);
}
/* 0x552040, the stage-0 start handler of the exam events 0x7e (the master exam question, its run handler
   he_RunExamQuestion) and 0x36 (the feast exam, he_RunFeastExam): the due clock is now + 2 hours and the stage 0 */

void he_StartExam(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 2, 0, 0);
  e->stage = 0;
}
/* 0x552090, the run handler of the master exam question 0x7e (its alloc handler he_StartExam): the stages -1 / -2
   free it (and its slot); stage 0 opens the slot "Berufe\Messagebox_Meisterpruefung" (none: the event is freed),
   centres it and prints the question 0x10b9 (the own player's name, the character), then waits in stage 1: past
   the due time, or on the second answer, it ends; the first answer marks the character's exam event (examId, found
   with he_FindEvent) accepted. No slot in stage 1 opens it again */
void he_RunExamQuestion(AIJOB *e) {

  if (e->stage == -1 || e->stage == -2) {
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
    io_PrintText(0x10b9, ai_PlayerSlots[ai_OwnPlayer].townName, e->chr);
    e->stage = 1;
    return;
  case 1:
    if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win || d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      he_FindEvent(2, 2, e->chr, 1, e->examBoxExamId)->examOfferAccepted = 1;
      he_ReleaseSlot(e);
      he_FreeEvent(e);
    } else if (d2_ClickedId == 1) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
    }
    return;
  }
}

/* 0x552200, the stage-0 start handler of the master exam offer event 0x7f (its run handler he_RunExamOffer): the
   stage 0, the due clock now with the hour 9 + random(3) and the minute random(4) * 15, no answer yet */
void he_StartExamOffer(AIJOB *e) {
  AIJOB *o = e;
  int r;

  e->stage = 0;
  e->end = ai_Time;
  e->end.hour = (unsigned short)(util_Random(3) + 9);
  r = util_Random(4);
  o->examOfferAccepted = 0;
  e->end.min = r * 15;
}
/* 0x552270, the run handler of the exam offer event 0x7f (its alloc handler he_StartExamOffer): stage 0 asks the
   character (+0xac) the master exam question, the message 0x7e that becomes he_RunExamQuestion's event (the
   character, this event's id, due in two hours, flags 9), and waits 8 hours (stage 1); then, accepted (he_RunExamQuestion
   set accepted), the character loses (1 - skill 3) / 2 of its health (the skill at least 0.1), the own player is
   paid 6% of its worth times the skill (cm_SendMoveGoodsUnchecked) and the character is told 0x10ba, else 0x10bb;
   then, as any other stage, the event is freed */
void he_RunExamOffer(AIJOB *e) {
  float skill;
  int worth, pay;
  AIMSG m;
  char text[0x800];
  AICHAR *c;

  if (e->stage < 0 || e->stage > 1) {
    he_FreeEvent(e);
    return;
  }
  if (e->stage == 0) {
    memset(&m, 0, sizeof(m));
    m.type = 0x7e;
    m.fromId = -1;
    m.time = ai_Time;
    m.to = e->examOfferChr;
    m.exam.chr = e->examOfferChr;
    m.flags = 9;
    m.exam.examId = e->id;
    m.exam.due = ai_Time;
    gm_AddTime(&m.exam.due, 2, 0, 0);
    cm_SendLongMessage(&m);
    e->stage = 1;
    e->end = ai_Time;
    gm_AddTime(&e->end, 8, 0, 0);
  } else if (e->stage == 1) {
    if (e->examOfferAccepted != 0) {
      c = &ai_Chars[e->chr];
      if (gm_GetSkill(c, 3) > 0.1f)
        skill = gm_GetSkill(c, 3);
      else
        skill = 0.1f;
      worth = gm_GetWorth(c->id);
      gm_AddHealth(
          c->id, -(int)((int)gm_CharacterHealth(c) * ((1.0f - skill) * 0.5f)));
      pay = (int)(worth * skill * 0.06f);
      cm_SendMoveGoodsUnchecked(e->examOfferChr, -1, ai_OwnPlayer, pay);
      txt_Format(text, 0x10ba, pay);
      he_ShowNews(e->examOfferChr, -1, text, 0x20, 0x5fd, ch_EmptyName);
    } else {
      txt_Format(text, 0x10bb);
      he_ShowNews(e->examOfferChr, -1, text, 0x20, 0x5fd, ch_EmptyName);
    }
    he_FreeEvent(e);
  }
}
/* 0x5524e0, the stage-0 start handler shared by the events 0x80 and 0x81 (the conversion): unless its option 4
   says it is not started yet, the due clock is a copy of the start clock and the event is posted at once (its
   cm slot kept in exSlot) */

void he_StartDue(AIJOB *e) {

  if ((e->opts & 4) == 0) {
    e->end = e->start;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}

/* 0x552520, the run handler of the delay event 0x80 (its start handler he_StartDue): a negative stage or no day
   left (AIJOB.delayDays) frees the record; a record with the option 4 does nothing; else a day is counted off and the
   event is posted a day later (its cm slot kept in exSlot) */
void he_RunDelay(AIJOB *e) {
  AIJOB *d = e;

  if (e->stage < 0 || d->delayDays <= 0) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  d->delayDays = d->delayDays - 1;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x5525a0, the run handler of the conversion event 0x81 (its alloc handler he_StartDue): while it has rounds and
   characters left, each round (a day apart) turns up to n = min(left, ceil(left + rounds)) characters whose b00c
   (the kind the person tooltip names) is `from` to the other kind (1 - from, a field delta of AICHAR +0xc), walking
   the 0x300 characters from a random one (ids in use, kinds up to 4); found fewer than n, it tries again 5 minutes
   later. A negative stage, no rounds or no characters left free the event, flag 4 of opts holds it */
void he_RunConversion(AIJOB *e) {
  AIJOB *cv = e;
  int cnt = 0;
  int to = 1 - cv->convertFrom;
  int n, ring, left;
  AICHAR *c;

  if (e->stage < 0 || cv->convertRounds <= 0 || cv->convertLeft <= 0) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  n = (int)((double)cv->convertLeft <
                    ceil((double)(cv->convertLeft + cv->convertRounds))
                ? (double)cv->convertLeft
                : ceil((double)(cv->convertRounds + cv->convertLeft)));
  ring = util_Random(0x300);
  left = 0x300;
  while (left != 0) {
    if (cnt >= n)
      break;
    if (ai_Chars[ring].id != 0xffff && ai_Chars[ring].kind <= 4 &&
        ai_Chars[ring].faith == cv->convertFrom) {
      c = &ai_Chars[ring];
      cm_BeginFieldBlock(c, c->netId);
      cm_AddFieldDelta(1, 1, 0xc, &to);
      cm_SendFieldDeltas();
      cnt++;
    }
    left--;
    ring = (ring + 1) % 0x300;
  }
  if (cnt < n) {
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  cv->convertRounds--;
  cv->convertLeft -= n;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0x18, 0, 0);
  e->exSlot = cm_SendExSetHE(0, e);
}
/* 0x5527c0, the stage-0 start handler of the skill-bonus event 0x82 (its run handler 0x552820; AIJOB.skillBonus*
   hold the bonus words): unless its option 4 says it is not started yet, the due clock is now + the
   bonus's duration (AIJOB.skillBonusHours) and the event is posted at once (its cm slot kept in exSlot) */

void he_StartSkillBonus(AIJOB *e) {
  AIJOB *b = e;

  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    gm_AddTime(&e->end, b->skillBonusHours, 0, 0);
    e->exSlot = cm_SendExSetHE(0, e);
  }
}
/* 0x552820, the run handler of the skill-bonus event 0x82 (its start handler he_StartSkillBonus): the states -1 / -2
   free the record; else, unless its option 4 says it is not started yet, the bonus is over: the due clock is set to
   now and the event is ended with the cm slot handle -1 (the next call frees it) */

void he_RunSkillBonus(AIJOB *e) {
  int st = e->stage;

  if (st == -1 || st == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  e->end = ai_Time;
  e->exSlot = cm_SendExSetHE(-1, e);
}
/* 0x552880, the start handler of the applicants event 0x86 (its run handler he_RunApplicants): unless its option 4
   says it is not started yet, the due clock is now at 17:00, moved a day on when it was already past 17:00; the
   office is unset, the highest kind looked at is 0x1b, both applicant handles are -1 and the event is posted at
   once (its cm slot kept in exSlot) */

void he_StartApplicants(AIJOB *e) {
  AIJOB *a = e;

  if ((e->opts & 4) == 0) {
    e->end = ai_Time;
    if (e->end.hour >= 0x11)
      gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.hour = 0x11;
    e->end.min = 0;
    a->applicantsOffice = 0;
    a->applicantsMaxKind = 0x1b;
    a->applicantsApplicant[0] = -1;
    a->applicantsApplicant[1] = -1;
    e->exSlot = cm_SendExSetHE(0, e);
  }
}

int amt_InitApplicant(struct AICHAR *c, int k);
int amt_GetOpenOffice(int k);
int amt_CreateApplicant(int k);

/* 0x552920, the run handler of the applicants event 0x86 (its alloc handler he_StartApplicants): stage -1 / -2 free it,
   flag 4 of opts or a pending post (exSlot) holds it. Stage 0 asks for the highest office kind up to maxKind that is
   open for one more applicant (amt_GetOpenOffice) and creates two applicants for it (amt_CreateApplicant; the second
   only two times in three); no kind (or maxKind 0): it starts over a day later at 17 o'clock with maxKind 0x1b.
   Stage 1 waits for both created characters (cm_GetSlotState 1: initialised as applicants, amt_InitApplicant; 2: gone)
   and when both are done posts the event 5 minutes later; else, as after stage 0, the event is posted again now
   (cm_SendExSetHE 1) */
void he_RunApplicants(AIJOB *e) {
  AIJOB *ap = e;
  int done, r;
  AICHAR *c;

  if (e->stage == -1 || e->stage == -2) {
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if (ap->applicantsMaxKind == 0) {
      gm_AddTime(&e->end, 0x18, 0, 0);
      e->end.hour = 0x11;
      e->end.min = 0;
      ap->applicantsOffice = 0;
      ap->applicantsMaxKind = 0x1b;
      ap->applicantsApplicant[0] = -1;
      ap->applicantsApplicant[1] = -1;
      e->exSlot = cm_SendExSetHE(0, e);
      return;
    }
    ap->applicantsOffice = amt_GetOpenOffice(ap->applicantsMaxKind);
    if (ap->applicantsOffice == 0) {
      gm_AddTime(&e->end, 0x18, 0, 0);
      e->end.hour = 0x11;
      e->end.min = 0;
      ap->applicantsOffice = 0;
      ap->applicantsMaxKind = 0x1b;
      ap->applicantsApplicant[0] = -1;
      ap->applicantsApplicant[1] = -1;
      e->exSlot = cm_SendExSetHE(0, e);
      return;
    }
    ap->applicantsApplicant[0] = amt_CreateApplicant(ap->applicantsOffice);
    ap->applicantsApplicant[1] =
        util_Random(3) != 0 ? amt_CreateApplicant(ap->applicantsOffice) : -1;
    break;
  case 1:
    done = 0;
    if (ap->applicantsApplicant[0] == -1) {
      done = 1;
    } else {
      r = cm_GetSlotState(ap->applicantsApplicant[0]);
      if (r == 1) {
        done = r;
        c = (AICHAR *)cm_GetSlotValue(ap->applicantsApplicant[0]);
        amt_InitApplicant(c, ap->applicantsOffice);
        ap->applicantsApplicant[0] = -1;
      } else if (r == 2) {
        ap->applicantsApplicant[0] = -1;
        done = 1;
      }
    }
    if (ap->applicantsApplicant[1] == -1) {
      done++;
    } else {
      r = cm_GetSlotState(ap->applicantsApplicant[1]);
      if (r == 1) {
        done++;
        c = (AICHAR *)cm_GetSlotValue(ap->applicantsApplicant[1]);
        amt_InitApplicant(c, ap->applicantsOffice);
        ap->applicantsApplicant[1] = -1;
      } else if (r == 2) {
        ap->applicantsApplicant[1] = -1;
        done++;
      }
    }
    if (done == 2) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(0, e);
      return;
    }
    break;
  default:
    return;
  }
  e->end = ai_Time;
  e->exSlot = cm_SendExSetHE(1, e);
}

int ai_TutorialOpenIntro();
int ai_TutorialTick();
int ai_TutorialCloseIntro();
void ai_TutorialClearHost(void);
void sv_PopTo(void (*v)());

/* 0x552b90, the alloc handler of the tutorial intro event 0x87: makes the record the tutorial's host (0x578120);
   when the tutorial is not running the record is freed, else it starts in stage 0 */
void he_AllocTutorialIntro(AIJOB *ev) {
  if (ai_TutorialSetHost(ev) != 0) {
    he_FreeEvent(ev);
    return;
  }
  ev->stage = 0;
}
/* 0x552bc0, the run handler of the tutorial intro event 0x87 (only in a running game, ai_GameState): stage 0
   opens the tutorial's main event (ai_TutorialOpenIntro: 0 -> stage 1, nonzero -> 2), stage 1 ticks it
   (nonzero -> 2), stage 2 closes it and detaches its host, frees the record, sets ai_GameOver and pops back
   to main_GameLoop */

void he_RunTutorialIntro(AIJOB *ev) {
  if (ai_GameState == 0)
    return;
  switch (ev->stage) {
  case 0:
    ev->stage = (ai_TutorialOpenIntro() != 0) + 1;
    break;
  case 1:
    if (ai_TutorialTick() != 0)
      ev->stage = 2;
    break;
  case 2:
    ai_TutorialCloseIntro();
    ai_TutorialClearHost();
    he_FreeEvent(ev);
    ai_GameOver = 1;
    sv_PopTo(main_GameLoop);
    break;
  }
}
/* 0x552c30, the alloc handler of the imperial office award event 0xa5 (AIJOB.award*): the due clock AIJOB.end
   and the award's clock (0xac) are now, stage 0 */

void he_StartOfficeAward(AIJOB *e) {
  AIJOB *a = e;

  e->end = ai_Time;
  a->awardWhen = ai_Time;
  e->stage = 0;
}
/* 0x552ca0, the run handler of the imperial office award event 0xa5 (AIJOB.award*: the character +0xbc gets the
   office +0xc0, 0x23 .. 0x25), run only on the game of its player (AIJOB.chr is ai_PlayerId) in a running game once
   it is due. Freed, ended, without its player or its character it frees the event. Stage 0 opens the window
   ("SPECIAL\TITEL" when the character is the player's own, "SPECIAL\TITEL_ANDERE" for another one); for the own
   character it plays the fanfare, the herald's address by the character's title (9 / 8 / other: _02 / _01 / _00)
   and sex, the office's voice (the voice buffer keeps the address for another office kind) and the click sound and
   shows the news 0x42ab / 0x42af / 0x42ad (offices 0x25 / 0x24 / 0x23) with the address text 0x42a5 .. 0x42aa,
   the award's clock and the office's text by sex; for another character the news 0x42ac / 0x42b0 / 0x42ae with
   the character; then the news 0x161c below (stage 1). Stage 1 frees the event when the window is answered
   (button 0, or the event bar's confirmation of its slot); without a window it starts over */
void he_RunOfficeAward(AIJOB *e) {
  AIJOB *a = e;
  AICHAR *own, *c;
  int addrNews, officeNews;

  own = &ai_Chars[e->chr];
  if (ai_PlayerId != e->chr || ai_GameState == 0)
    return;
  if (gm_CompareTime(&e->end, &ai_Time) == 1)
    return;
  c = gm_FindChar(a->awardCh);
  if (e->stage == -2 || e->stage == -1 || own->id == 0xffff || c == 0) {
    if (e->slot != 0)
      he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    if (e->slot == 0) {
      if (c == own)
        he_OpenEventSlot(e, 0, 0, "SPECIAL\\TITEL", 0x5fd);
      else
        he_OpenEventSlot(e, 0, 0, "SPECIAL\\TITEL_ANDERE", 0x5fe);
    }
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_CentreViewWindows(e->slot->win);
    d2_SetForm(e->slot->win, 1);
    if (c == own) {
      char voice[0x200];

      officeNews = 0;
      if (c->level == 9) {
        addrNews = 0x42a9;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_02");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_02");
      } else if (c->level == 8) {
        addrNews = 0x42a7;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_01");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_01");
      } else {
        addrNews = 0x42a5;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_W_00");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_ANREDE_HS_M_00");
      }
      if (c->sex == 1)
        addrNews++;
      snd_QueueVoice(-7, 0, "FanfarePositivHeldenhaftLang", 0, 100);
      snd_QueueVoice(-7, 0, voice, 0, 100);
      if (a->awardOffice == 0x25) {
        officeNews = 0x42ab;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_00");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_00");
      } else if (a->awardOffice == 0x24) {
        officeNews = 0x42af;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_02");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_02");
      } else if (a->awardOffice == 0x23) {
        officeNews = 0x42ad;
        if (c->sex == 1)
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_WEIBLICH_HS_01");
        else
          strcpy(voice, "_VERLEIHUNG_REICHSAMT_MAENNLICH_HS_01");
      }
      snd_QueueVoice(-7, 0, voice, 0, 100);
      snd_QueueVoice(-7, 0, "MausclickLinks_s_01", -1, 0);
      io_PrintText(officeNews, addrNews, &a->awardWhen,
                   c->sex == 0 ? 0x253 : a->awardOffice + 0x27b);
    } else {
      officeNews = 0;
      if (a->awardOffice == 0x25)
        officeNews = 0x42ac;
      else if (a->awardOffice == 0x24)
        officeNews = 0x42b0;
      else if (a->awardOffice == 0x23)
        officeNews = 0x42ae;
      io_PrintText(officeNews, c->id,
                   c->sex == 0 ? 0x253 : a->awardOffice + 0x27b);
    }
    d2_SetForm(e->slot->win, 2);
    io_PrintText(0x161c);
    e->stage = 1;
    return;
  case 1:
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win && he_SlotConfirmed == 0)
      return;
    if (d2_ClickedId == 0) {
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (he_SlotConfirmed == 0 || he_ActiveSlot != e->slot)
      return;
    he_SlotConfirmed = 0;
    he_ReleaseSlot(e);
    he_FreeEvent(e);
  }
}

void he_FreeEventNow(AIJOB *r);

/* 0x553060, registers the alloc / run handler pairs of the event types 0x22 .. 0xa5 (he_SetEventHandlers; the pair of a type is (alloc, run); 1 = a registration failed; 0x52b350 (type, 0, 0, 0x507 / 0x50e, -1) registers the message type of a few of them). The handlers above 0x553060 are the ones of this file; 0x56f040 is a forwarder to the free (0x53e1f0); the rest lives in the stretch 0x553880 .. 0x575700 (drafts to come) */
int he_RegisterEventTypes22(void) {
  if (he_SetEventHandlers(0x22, he_NoHandler, he_NoHandler) != 0)
    return 1;
  if (he_SetEventHandlers(0x29, he_RunDueNow, he_FreeEventNow) != 0)
    return 1;
  if (he_SetEventHandlers(0x2a, he_AllocStammtisch, he_RunStammtisch) != 0)
    return 1;
  if (he_SetEventHandlers(0x2b, he_AllocTavern, he_RunTavern) != 0)
    return 1;
  if (he_SetEventHandlers(0x2c, he_AllocOffer, he_RunWeddingOffer) != 0)
    return 1;
  if (he_SetEventHandlers(0x2d, he_FreeEventNow, he_FreeEventNow) != 0)
    return 1;
  if (he_SetEventHandlers(0x2e, he_AllocQuarrel, he_RunQuarrel) != 0)
    return 1;
  if (he_SetEventHandlers(0x2f, he_RunDueNow, he_RunMasterExam) != 0)
    return 1;
  if (he_SetEventHandlers(0x30, he_FreeEventNow, he_FreeEventNow) != 0)
    return 1;
  if (he_SetEventHandlers(0x37, he_AllocFeast, he_RunFeast) != 0)
    return 1;
  if (he_SetEventHandlers(0x36, he_StartExam, he_RunFeastExam) != 0)
    return 1;
  if (he_SetEventHandlers(0x35, he_AllocTribute, he_RunTribute) != 0)
    return 1;
  if (he_SetEventHandlers(0x41, he_AllocCourtship, he_RunCourtship) != 0)
    return 1;
  if (he_SetEventHandlers(0x42, he_AllocRandomMessage, he_RunRandomMessage) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x43, he_AllocPatrol, he_RunPatrol) != 0)
    return 1;
  sv_RegisterActivity(0x43, 0x0, 0x0, 0x507, -1);
  if (he_SetEventHandlers(0x44, he_AllocRaid, he_RunRaid) != 0)
    return 1;
  if (he_SetEventHandlers(0x45, he_AllocFight, he_RunFight) != 0)
    return 1;
  if (he_SetEventHandlers(0x46, he_AllocDuelChallenge, he_RunDuelChallenge) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x47, he_AllocInsult, he_RunInsult) != 0)
    return 1;
  if (he_SetEventHandlers(0x4a, he_AllocGeselle, he_RunGeselle) != 0)
    return 1;
  if (he_SetEventHandlers(0x4b, he_AllocInsultNews, he_RunInsultNews) != 0)
    return 1;
  if (he_SetEventHandlers(0x51, he_AllocNextDay, he_RunCountdown) != 0)
    return 1;
  if (he_SetEventHandlers(0x52, he_AllocComment, he_RunComment) != 0)
    return 1;
  if (he_SetEventHandlers(0x53, he_AllocCharPayouts, he_RunCharPayouts) != 0)
    return 1;
  if (he_SetEventHandlers(0x54, he_AllocDueIsStart, he_RunMasterExamFee) != 0)
    return 1;
  if (he_SetEventHandlers(0x55, he_AllocMasterExamPay, he_RunMasterExamPay) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x56, he_AllocNextDay, he_RunPayment) != 0)
    return 1;
  if (he_SetEventHandlers(0x57, he_AllocRandomHalf, he_RunStoreSale) != 0)
    return 1;
  if (he_SetEventHandlers(0x58, he_AllocRandomHalf, he_RunBuildingDecay) != 0)
    return 1;
  if (he_SetEventHandlers(0x5a, he_AllocRepostEvent, he_RunRepostEvent) != 0)
    return 1;
  if (he_SetEventHandlers(0x5b, he_AllocPunishment, he_RunFinePayment) != 0)
    return 1;
  if (he_SetEventHandlers(0x5c, he_AllocPunishment, he_RunPilloryPunishment) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x5d, he_AllocOffspring, he_RunOffspring) != 0)
    return 1;
  if (he_SetEventHandlers(0x5e, he_StartTrialEvent, he_RunTrialEvent) != 0)
    return 1;
  if (he_SetEventHandlers(0x5f, he_StartNextTrialStep, he_RunTrialSteps) != 0)
    return 1;
  if (he_SetEventHandlers(0x60, he_StartTraining, he_RunTraining) != 0)
    return 1;
  if (he_SetEventHandlers(0x59, he_StartPlague, he_RunPlague) != 0)
    return 1;
  if (he_SetEventHandlers(0x61, he_StartGang, he_RunGang) != 0)
    return 1;
  sv_RegisterActivity(0x61, 0x0, 0x0, 0x507, -1);
  if (he_SetEventHandlers(0x63, he_AllocProtectionAsk, he_RunProtectionAsk) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x62, he_StartProtection, he_RunProtection) != 0)
    return 1;
  sv_RegisterActivity(0x62, 0x0, 0x0, 0x50e, -1);
  if (he_SetEventHandlers(0x64, he_StartAudit, he_RunAudit) != 0)
    return 1;
  sv_RegisterActivity(0x64, 0x0, 0x0, 0x507, -1);
  if (he_SetEventHandlers(0x65, he_StartGathering, he_RunGathering) != 0)
    return 1;
  sv_RegisterActivity(0x65, 0x0, 0x0, 0x507, -1);
  if (he_SetEventHandlers(0x66, he_AllocSim, he_RunAccidentSim) != 0)
    return 1;
  if (he_SetEventHandlers(0x67, he_StartAuctionEvent, he_RunAuctionEvent) != 0)
    return 1;
  if (he_SetEventHandlers(0x68, he_StartInnSim, he_RunInnSim) != 0)
    return 1;
  if (he_SetEventHandlers(0x69, he_StartTitleCeremony, he_RunTitleCeremony) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x6a, he_StartSkillUp, he_RunSkillUp) != 0)
    return 1;
  if (he_SetEventHandlers(0x6b, he_StartBard, he_RunBard) != 0)
    return 1;
  if (he_SetEventHandlers(0x6d, he_StartPopulation, he_RunPopulation) != 0)
    return 1;
  if (he_SetEventHandlers(0x6f, he_StartLover, he_RunLover) != 0)
    return 1;
  if (he_SetEventHandlers(0x70, he_AllocSim, he_RunDiseaseSim) != 0)
    return 1;
  if (he_SetEventHandlers(0x74, he_StartDarkCorner, he_RunDarkCorner) != 0)
    return 1;
  if (he_SetEventHandlers(0x76, he_StartEffectEvent, he_RunEffectEvent) != 0)
    return 1;
  if (he_SetEventHandlers(0x77, he_StartSendHomeEvent, he_RunSendHomeEvent) !=
      0)
    return 1;
  if (he_SetEventHandlers(0x78, he_StartReaper, he_RunReaper) != 0)
    return 1;
  if (he_SetEventHandlers(0x79, he_StartRanking, he_RunRanking) != 0)
    return 1;
  if (he_SetEventHandlers(0x7a, he_StartWalk, he_RunWalk) != 0)
    return 1;
  if (he_SetEventHandlers(0x7b, he_FreeEventNow, he_FreeEventNow) != 0)
    return 1;
  if (he_SetEventHandlers(0x7d, he_InitSixGroupEvent, he_RunSixGroupEvent) != 0)
    return 1;
  if (he_SetEventHandlers(0x7e, he_StartExam, he_RunExamQuestion) != 0)
    return 1;
  if (he_SetEventHandlers(0x7f, he_StartExamOffer, he_RunExamOffer) != 0)
    return 1;
  if (he_SetEventHandlers(0x80, he_StartDue, he_RunDelay) != 0)
    return 1;
  if (he_SetEventHandlers(0x81, he_StartDue, he_RunConversion) != 0)
    return 1;
  if (he_SetEventHandlers(0x82, he_StartSkillBonus, he_RunSkillBonus) != 0)
    return 1;
  if (he_SetEventHandlers(0x86, he_StartApplicants, he_RunApplicants) != 0)
    return 1;
  if (he_SetEventHandlers(0x87, he_AllocTutorialIntro, he_RunTutorialIntro) !=
      0)
    return 1;
  return he_SetEventHandlers(0xa5, he_StartOfficeAward, he_RunOfficeAward) != 0;
}

/* 0x5538b0, ends every started event (opts & 3) the character p (its AICHAR record, by its netId; nothing for a
   free slot) takes part in: the pair events 0x41, 0x6f and 0x45 (either partner; the other one is looked up with
   gm_FindChar first), the offer events 0x2c (as the suitor or a guest (who[0], who[2], who[5]) the offer's
   crimes are handed over first, cm_SendHandOverCrimes (who[0], who[1], the event's id, 0); as the partner who[1]
   only ended), the events 0x47 (either partner), the trials 0x5e and the trial steps 0x5f (as the teacher)
   @deep deep s38: the 0x45 loop with gm_FindChar + he_EndEventNow written in each arm (as the 0x41 loop):
   one gm_FindChar call with the push per arm and add esp,8 merged as the original (28 -> 25 ins). Left:
   (1) the constant 3 of the seven (e->opts & 3) tests gets bl in ours (const#0#3, c2trace: prio -134 but
   sav 13 -> ebx; push/pop ebx), the original tests with the immediate and never touches ebx; changing k of
   the constants to another value (probe, 1..8 sites) keeps a register: no count threshold; ternary /
   single-call / b = a forms of the 0x45 loop: worse. Only this function in the image tests [reg+0x78],3
   more than once (grep_orig). Open: what makes the constant no candidate (a bitfield test? opts typed
   differently?). (2) the 0x2c loop's e->id / who[1] loads in edx / eax swapped (scratch rotation, probably
   follows (1)). */
void he_EndPersonEvents(AICHAR *p) {
  AICHAR *c = p;
  AIJOB *e;
  int a, b;

  if (c == 0 || c->id == 0xffff)
    return;
  for (e = he_FindEvent(1, 0, 0x41); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) == 0)
      continue;
    if (e->partner1 == c->netId) {
      gm_FindChar(e->partner2);
      he_EndEventNow(e);
    } else if (e->partner2 == c->netId) {
      gm_FindChar(e->partner1);
      he_EndEventNow(e);
    }
  }
  for (e = he_FindEvent(1, 0, 0x6f); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) == 0)
      continue;
    a = e->partner1;
    if (a == c->netId)
      b = e->partner2;
    else if (e->partner2 == c->netId)
      b = a;
    else
      continue;
    gm_FindChar(b);
    he_EndEventNow(e);
  }
  for (e = he_FindEvent(1, 0, 0x45); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) == 0)
      continue;
    a = e->partner1;
    b = e->partner2;
    if (a == c->netId) {
      gm_FindChar(b);
      he_EndEventNow(e);
    } else if (b == c->netId) {
      gm_FindChar(a);
      he_EndEventNow(e);
    }
  }
  for (e = he_FindEvent(1, 0, 0x2c); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) == 0)
      continue;
    a = e->offerWho[0];
    if (a == c->netId || e->offerWho[2] == c->netId ||
        e->offerWho[5] == c->netId) {
      cm_SendHandOverCrimes(a, e->offerWho[1], e->id, 0);
      he_EndEventNow(e);
    } else if (e->offerWho[1] == c->netId) {
      he_EndEventNow(e);
    }
  }
  for (e = he_FindEvent(1, 0, 0x47); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) == 0)
      continue;
    if (e->partner1 == c->netId || e->partner2 == c->netId)
      he_EndEventNow(e);
  }
  for (e = he_FindEvent(1, 0, 0x5e); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) != 0 && e->trialTeacher == c->netId)
      he_EndEventNow(e);
  }
  for (e = he_FindEvent(1, 0, 0x5f); e != 0; e = he_NextEvent()) {
    if ((e->opts & 3) != 0 && e->trialStepTeacher == c->netId)
      he_EndEventNow(e);
  }
}

/* 0x553ae0, the detection check of an attack on a building (he_RunRobbery asks it with the range 2500.0f, he_RunBurglary with 5000.0f): looks
   for a free watch event 0x43 (no attack bound to it yet, of another character than the attacker's event) one of
   whose four characters stands closer to the building than the range (the 3D distance of its body to the
   building's object). Found: the event goes to d->found, its characters are stopped, the one that saw it beckons
   ("gestik/herranwinken"), all are sent to the building ("Detected") with a scornful gesture
   ("gestik/abfaellig" 1 .. 2), the event is bound to the attack (attackId), due 8 minutes from now and posted
   again (cm_SendExSetHE 0x400); 1. Nothing found (or no building object): 0. The question comes as an integer
   (intptr_t): the callers treat their HEDETECT as escaped (he_RunBurglary keeps d.found loaded across gv_Accuse;
   @original: a HEDETECT * parameter frees d for the allocator, he_RunRobbery byte -> draft, he_RunBurglary 10 bytes
   shorter) */
int he_DetectAttack(intptr_t p) {
  HEDETECT *d = (HEDETECT *)p;
  AIJOB *e, *best;
  AIJOB *w;
  AICHAR *seen, *c;
  int i;
  float dx, dy, dz, dist;
  D3OBJECT *a, *b;

  best = 0;
  seen = 0;
  if (d->bld == 0 || d->bld->object == 0)
    return 0;
  for (e = he_FindEvent(1, 0, 0x43); e != 0; e = he_NextEvent()) {
    if (best != 0)
      break;
    w = e;
    if (w->patrolWait != -1 || e->netId == d->ev->netId)
      continue;
    for (i = 0; i < 4; i++) {
      if (w->patrolGuards[i] == -1)
        continue;
      seen = gm_FindChar(w->patrolGuards[i]);
      if (seen == 0)
        continue;
      a = d->bld->object;
      b = seen->scene->obj;
      dx = a->pos.x - b->pos.x;
      dy = a->pos.y - b->pos.y;
      dz = a->pos.z - b->pos.z;
      dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
      if (dist < d->range) {
        best = e;
        break;
      }
    }
  }
  if (best == 0)
    return 0;
  d->found = best;
  w = best;
  for (i = 0; i < 4; i++) {
    if (w->patrolGuards[i] == -1)
      continue;
    c = gm_FindChar(w->patrolGuards[i]);
    if (c == 0)
      continue;
    cm_SendChrStop(w->patrolGuards[i]);
    if (seen->netId == w->patrolGuards[i])
      cm_SendChrAnim(w->patrolGuards[i], "gestik/herranwinken", 2);
    cm_SendChrGotoBuilding(w->patrolGuards[i], d->bld->id, -1, 0, 1,
                           "Detected");
    cm_SendChrAnim(w->patrolGuards[i], "gestik/abfaellig", util_Random(2) + 1);
  }
  w->patrolWait = d->ev->id;
  best->end = ai_Time;
  gm_AddTime(&best->end, 0, 8, 0);
  cm_SendExSetHE(0x400, best);
  return 1;
}
/* 0x553cc0, 1 unless the building `p` has a protection money event 0x62 that was paid (AIJOB.protectionVictim is its
   id and answer 1): only an unprotected building is attacked or robbed; a null building gives 1 */

int he_NoProtectionEvent(AIBLD *p) {
  AIBLD *b = p;
  AIJOB *e;
  AIJOB *pr;

  if (b == 0)
    return 1;
  for (e = he_FindEvent(1, 0, 0x62); e != 0; e = he_NextEvent()) {
    pr = e;
    if (pr->protectionVictim == b->id && pr->protectionAnswer == 1)
      return 0;
  }
  return 1;
}
/* 0x553d10, 1 unless a quarrel event 0x2e is running between the characters a and b (its partner1 / partner2 are
   their netIds), then 0 */

int he_NoEvent2ePair(AICHAR *a, AICHAR *b) {
  AICHAR *ca = a;
  AICHAR *cb = b;
  AIJOB *e;

  for (e = he_FindEvent(1, 0, 0x2e); e != 0; e = he_NextEvent()) {
    if (cb->netId == e->partner1 && e->partner2 == ca->netId)
      return 0;
  }
  return 1;
}
/* 0x553d60, 1 unless an insult news event 0x4b is running from the character a to b (its partner1 / partner2 are
   their netIds), then 0 */

int he_NoEvent4bPair(AICHAR *a, AICHAR *b) {
  AICHAR *ca = a;
  AICHAR *cb = b;
  AIJOB *e;

  for (e = he_FindEvent(1, 0, 0x4b); e != 0; e = he_NextEvent()) {
    if (cb->netId == e->partner2 && ca->netId == e->partner1)
      return 0;
  }
  return 1;
}
/* 0x553db0, 1 unless a pamphlet event 0x35 of the character *a is running about the character b (AIJOB.idbc is
   that character's netId; ai_PamphletAmountCB), then 0; *count (when given) receives the number of a's pamphlets */

int he_NoEvent35Pair(AICHAR *a, AICHAR *b, int *count) {
  AICHAR *c = b;
  AIJOB *e;
  int n = 0;

  e = he_FindEvent(2, 2, a->id, 0, 0x35);
  while (e != 0) {
    if (c->netId == e->idbc)
      return 0;
    e = he_NextEvent();
    n++;
  }
  if (count != 0)
    *count = n;
  return 1;
}
/* 0x553e10, the alloc handler of the sale event 2: the due clock (AIJOB.end) is now, one second later with
   gm_AllowAll set, else after the production time (AIGOOD.workTime) of the good sold (AIJOB.orderGood) */

void he_AllocSale(AIJOB *e) {
  AIJOB *s = e;
  AIGOOD *good;

  good = (&ai_Goods[s->orderGood]);
  e->end = ai_Time;
  if (gm_AllowAll != 0)
    gm_AddTime(&e->end, 0, 0, 1);
  else
    gm_AddTime(&e->end, 0, good->workTime, 0);
}

void he_MessageBoxQuickjump(int a1, int a2, char *text, int fl, int a5, int a6,
                            int a7, char *jump, char *text2);

/* 0x553e90, the run handler of the sale event 2 (AIJOB.sale*; its init he_AllocSale sets it due after the good's
   production time): stage 0 goes to 1; stage 1, once due, sells the object obj of the building AIJOB.from
   (cm_SendExSellObject: the good, one piece, to the own player) and keeps the send slot (stage 2); a gone
   building frees the event. Stage 2 waits for the slot and its object: a grave (0x1f9 / 0x1fd / 0x201) opens a
   grave order of the size 1 / 2 / 3 for the building's owner (gv_OrderOpenSize), a 0x12d sends the message 0x2a
   to the player character; an owner of the kind 6 (a player character) gets the news 0x606 (0x60b when the
   building's master is a kind 1 character with flags1b4 bit 0 and notify is set): the text 0x1c2b with the
   quick jump to "ob_<NAME>" of the good while the object is still in the building (not a 0xfd), else 0x1c2d;
   the object gets the bits 0xa0. Then the sys message 4 (the building, the object's id) and the event is freed */
void he_RunSale(AIJOB *e) {
  AIJOB *s = e;
  AIOBJ *p, *q;
  AIBLD *b;
  unsigned short ty;
  AIGOOD *g;
  int tid;

  switch (e->stage) {
  case 0:
    e->stage = 1;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0) {
      he_FreeEvent(e);
      return;
    }
    gm_Query(b->objList, 1, 1, s->saleObj);
    s->saleSlot =
        cm_SendExSellObject(s->saleObj, -1, s->orderGood, 1, ai_OwnPlayer, 0);
    e->stage = e->stage + 1;
    return;
  case 2:
    if (cm_GetSlotState(s->saleSlot) == 0)
      return;
    p = (AIOBJ *)cm_GetSlotValue(s->saleSlot);
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0 || p == 0) {
      he_FreeEvent(e);
      return;
    }
    ty = p->type;
    if (ty == 0x1f9)
      gv_OrderOpenSize(&ai_Chars[b->owner], b, 1);
    else if (ty == 0x1fd)
      gv_OrderOpenSize(&ai_Chars[b->owner], b, 2);
    else if (ty == 0x201)
      gv_OrderOpenSize(&ai_Chars[b->owner], b, 3);
    else if (ty == 0x12d) {
      AIMSG msg;

      D3_ZERO(&msg, sizeof(msg));
      msg.type = 0x2a;
      msg.to = ai_PlayerChar->netId;
      msg.fromId = b->id;
      msg.arg[0] = b->id;
      msg.flags = 2;
      cm_SendLongMessage(&msg);
    }
    if (ai_Chars[b->owner].kind == 6) {
      char text[0x400];
      char jump[0x80];
      char name[0x80];

      q = gm_Query(b->objList, 1, 1, s->saleObj);
      g = (&ai_Goods[s->orderGood]);
      if (q != 0 && q->type != 0xfd) {
        tid = 0x606;
        if (ai_BTypes[b->type].kind != 6) {
          AICHAR *m = gm_FindCharacterByMaster(b);

          if (m != 0 && m->kind == 1 && (m->flags1b4 & 1) != 0 &&
              s->saleNotify != 0)
            tid = 0x60b;
        }
        strcpy(name, g->name);
        strupr(name);
        sprintf(jump, "ob_%s", name);
        txt_Format(text, 0x1c2b, b, s->orderGood * 2 + 0x9a8);
        he_MessageBoxQuickjump(ai_Chars[b->owner].netId, e->from, text, 0, tid,
                               b->id, s->saleObj, jump, "_NACHRICHTEN_HS_53");
      } else {
        tid = 0x606;
        if (ai_BTypes[b->type].kind != 6) {
          AICHAR *m = gm_FindCharacterByMaster(b);

          if (m != 0 && m->kind == 1 && (m->flags1b4 & 1) != 0 &&
              s->saleNotify != 0)
            tid = 0x60b;
        }
        txt_Format(text, 0x1c2d, b, s->orderGood * 2 + 0x9a8);
        he_MessageBoxQuickjump(ai_Chars[b->owner].netId, e->from, text, 0, tid,
                               b->id, -1, 0, "_NACHRICHTEN_HS_54");
      }
      p->flags13 |= 0xa0;
    }
    {
      HESOLDMSG m;

      q = gm_Query(b->objList, 1, 1, s->saleObj);
      m.due = ai_Time;
      gm_AddTime(&m.due, 0, 0, 1);
      m.sold.bld = b->id;
      m.sold.objId = q->objId;
      cm_SendExSysMessage(4, &m);
    }
    he_FreeEvent(e);
  }
}

/* 0x554320, the run handler of the customers event 6 (AIJOB.customers*; its alloc handler he_AllocCustomersHire): stages -2 / -1
   free it, stage 0 goes to 1. Stage 1, once due: the building AIJOB.from (gone: freed); when the job cost of its
   kind (gm_JobCost for the owner) is above the owner's goods value (gm_GetGoodsValue) the owner gets the news
   0x1a40 and the event is freed; else the first kind with customers left (count[] > 0) has a customer of the kind
   `kind` spawned at the building (cm_SendMessage3d, its slot), none: freed; due an hour later (stage 2). Stage 2
   waits for the spawn: none ("Einwohnerlimit erreicht!", the population limit) frees the event; else the customer
   (person) walks to the target object's entrance ("dummy_EINGANG"; the building's main object when target is -1),
   stage 3 an hour later. Stage 3 serves one: the customer pays the job cost (cm_SendMoveGoodsUnchecked) to the
   event's character, whose player record counts it (AIFIN.customerPaid), a player character (kind 6 / 7)
   gets the news 0x1bab (0x60c when the building's master is a character with flags1b4 bit 0, else 0x5f2); with
   customers left stage 1 again after 30 .. 39 minutes, else the event is freed */
void he_RunCustomers(AIJOB *e) {
  AIJOB *c = e;
  AIBLD *b;
  AICHAR *p, *m, *owner;
  AIOBJ *o;
  AIFIN *f;
  int i, cost;
  char text[0x400];

  switch (e->stage) {
  case -2:
  case -1:
    break;
  case 0:
    e->stage = e->stage + 1;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    owner = &ai_Chars[b->owner];
    cost = (int)gm_JobCost(owner, b->type, -1, 1);
    if (cost > gm_GetGoodsValue(&ai_Chars[b->owner])) {
      txt_Format(text, 0x1a40, b);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, e->from, text, 0, 0x5f2,
                             b->id, c->customersTarget, 0, 0);
      he_FreeEvent(e);
      return;
    }
    for (i = 0; i < 12; i++) {
      if (c->tourCounters[i] > 0) {
        c->customersSlot = cm_SendMessage3d(b, 0, c->hireTitle, 0);
        break;
      }
    }
    if (i >= 12)
      break;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    e->stage = e->stage + 1;
    return;
  case 2:
    if (c->customersSlot == -1 || cm_GetSlotState(c->customersSlot) == 0)
      return;
    p = (AICHAR *)cm_GetSlotValue(c->customersSlot);
    if (p == 0) {
      he_ShowNews(ai_Chars[e->chr].netId, -1, "$2AEinwohnerlimit erreicht!", 0,
                  0x5f2, 0);
      he_FreeEvent(e);
      return;
    }
    c->customersPerson = p->netId;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    if (c->customersTarget == -1) {
      o = gm_BuildingMainObject(b);
      if (o != 0)
        c->customersTarget = o->objId;
    }
    cm_RequestChrMoveToUniverse(c->customersPerson, e->from, c->customersTarget,
                                "dummy_EINGANG");
    e->stage = 3;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    return;
  case 3:
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    p = gm_FindChar(c->customersPerson);
    for (i = 0; i < 12; i++) {
      if (p != 0 && c->tourCounters[i] > 0) {
        owner = &ai_Chars[b->owner];
        cost = (int)gm_JobCost(owner, b->type, -1, 1);
        c->tourCounters[i]--;
        if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
          m = gm_FindCharacterByMaster(b);
          txt_Format(text, 0x1bab, cost, p->id, b);
          if (m != 0 && (m->flags1b4 & 1) != 0)
            he_MessageBoxQuickjump(ai_Chars[e->chr].netId, b->id, text, 0,
                                   0x60c, b->id, c->customersTarget, 0,
                                   "_NACHRICHTEN_HS_00");
          else
            he_MessageBoxQuickjump(ai_Chars[e->chr].netId, b->id, text, 0,
                                   0x5f2, b->id, c->customersTarget, 0,
                                   "_NACHRICHTEN_HS_00");
        }
        cm_SendMoveGoodsUnchecked(p->netId, ai_Chars[e->chr].netId,
                                  ai_OwnPlayer, cost);
        f = gm_PlayerRecord(&ai_Chars[e->chr]);
        if (f != 0)
          f->customerPaid += cost;
        break;
      }
    }
    for (i = 0; i < 12; i++) {
      if (c->tourCounters[i] > 0)
        break;
    }
    if (i < 12) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, util_Random(10) + 0x1e, 0);
      e->stage = 1;
      return;
    }
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x554820, the allocation handler of the customers / hire events (6 / 7): the due clock is the start clock,
   posted 0xf minutes later */

void he_AllocCustomersHire(AIJOB *ev) {
  ev->end = ev->start;
  gm_AddTime(&ev->end, 0, 0xf, 0);
}
/* 0x554860, the run handler of the hire event 7 (AIJOB.hire*; its alloc handler he_AllocCustomersHire), he_RunCustomers' frame
   with one count: stages -2 / -1 free it, stage 0 goes to 1. Stage 1, once due: the building AIJOB.from (gone:
   freed); when the job's cost (gm_JobCost for the owner) is above the owner's goods value the owner gets the news
   0x1a41 and the event is freed; else, with hires left, a character with the building type's job jobs[job] is
   spawned at the building (cm_SendMessage3d, its slot; stage 2), none left: freed. Stage 2 waits for the spawn:
   none ("Einwohnerlimit erreicht!", the population limit) frees the event; else the new character (person) gets the
   job, title 0 (ai_PermsDirty), and with hires left one is counted: it pays the cost (cm_SendMoveGoodsUnchecked) to
   the event's character, a player character (kind 6 / 7) gets the news 0x1bb1; it walks to the target object's
   entrance ("dummy_EINGANG"; target 0: the building's main room object, -1: its 0xfd object); with hires left
   stage 1 again 10 .. 19 minutes later, else the event is freed */
void he_RunHire(AIJOB *e) {
  AIJOB *h = e;
  AIBLD *b;
  AIBTYPE *bt;
  AICHAR *p, *n;
  AIOBJ *o;
  int i, cost, tgt;
  AICHAR *owner;
  char text[0x400];

  switch (e->stage) {
  case -2:
  case -1:
    break;
  case 0:
    e->stage = e->stage + 1;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    owner = &ai_Chars[b->owner];
    cost = (int)gm_JobCost(owner, b->type, h->hireJob, -1);
    bt = &ai_BTypes[b->type];
    if (cost > gm_GetGoodsValue(&ai_Chars[b->owner])) {
      txt_Format(text, 0x1a41, b);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, e->from, text, 0, 0x5f2,
                             b->id, h->hireTarget, 0, 0);
      he_FreeEvent(e);
      return;
    }
    for (i = 0; i < 1; i++) {
      if (h->hireCount[i] > 0) {
        h->hireSlot = cm_SendMessage3d(b, 1, 0, bt->jobs[h->hireJob]);
        break;
      }
    }
    if (i >= 1)
      break;
    e->stage = e->stage + 1;
    return;
  case 2:
    if (cm_GetSlotState(h->hireSlot) == 0)
      return;
    p = (AICHAR *)cm_GetSlotValue(h->hireSlot);
    if (p == 0) {
      he_ShowNews(ai_Chars[e->chr].netId, -1, "Einwohnerlimit erreicht!", 0,
                  0x5f8, 0);
      he_FreeEvent(e);
      return;
    }
    ai_PermsDirty = 1;
    h->hirePerson = p->netId;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    bt = &ai_BTypes[b->type];
    n = (AICHAR *)cm_GetSlotValue(h->hireSlot);
    n->jobId = bt->jobs[h->hireJob];
    n->title = 0;
    for (i = 0; i < 1; i++) {
      if (h->hireCount[i] > 0) {
        owner = &ai_Chars[b->owner];
        cost = (int)gm_JobCost(owner, b->type, h->hireJob, -1);
        h->hireCount[i]--;
        if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
          txt_Format(text, 0x1bb1, cost, p->id, b);
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, b->id, text, 0, 0x5f2,
                                 b->id, h->hireTarget, 0, "_NACHRICHTEN_HS_03");
        }
        cm_SendMoveGoodsUnchecked(p->netId, ai_Chars[e->chr].netId,
                                  ai_OwnPlayer, cost);
        break;
      }
    }
    tgt = h->hireTarget;
    if (tgt != 0) {
      if (tgt == -1) {
        o = gm_Query(b->objList, 1, 0, 0xfd);
        tgt = o != 0 ? o->objId : -1;
      }
    } else {
      o = gm_Query(b->objList, 1, 0, b->mainRoom);
      tgt = o != 0 ? o->objId : -1;
    }
    cm_RequestChrMoveToUniverse(h->hirePerson, e->from, tgt, "dummy_EINGANG");
    for (i = 0; i < 1; i++) {
      if (h->hireCount[i] > 0)
        break;
    }
    if (i < 1) {
      gm_AddTime(&e->end, 0, util_Random(10) + 10, 0);
      e->stage = 1;
      return;
    }
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}

int gm_LevelPayout(int v, int kind);

/* 0x554cb0, he_AllocTransport (its error texts), the allocation handler of the transport event 15 (AIJOB.transport*): due
   now (the start clock) with the second clock, the start building, the cart and the goal building looked up (any
   missing: the event is freed). An escorted cart (AIOBJ.flags20 bit 0) bound for a kind 0xa building goes to the
   nearest kind 0xa building instead (d3_PointToWorld of their objects), which replaces the old goal in the ordering
   event's ids too. The mode by gm_IsHomeType of the two (start and goal both homes and the same building: the error
   "Start and goal are the same!" and the event is freed), the travel sum, due an hour later; the cart's walk speed
   from its load (fill * 0.01 * 0.5 + 0.9, -0.4 for the cart 0x136, +0.3 for 0x135) times the driver building's
   skill 0x11 (gm_BuildingSkill, * 0.01 + 1), kept as speed; the cart is marked 0x40 (sent with opts bit 1) and bound
   to the event, the event's AIJOB.from is the cart. An escorted cart gets the escort kind by its goods' value
   (gm_StallGoodsList: value / 16000 + random 0 .. 1, at most 2), and the escort is paid (gm_LevelPayout, sent with
   opts bit 1) */
void he_AllocTransport(AIJOB *e) {
  AIJOB *t = e;
  AIOBJ *o;
  AIBLD *from, *to, *b, *best, *drv;
  AIJOB *r;
  CHARACTER *ch;
  int home1, home2, k, skill, pay;
  float mind, dist, dx, dy, dz;
  D3VECTOR4 p1, p2; /* d3_PointToWorld writes past the vector */
  AIRECIPE goods;
  char text[0x100];

  home1 = 0;
  home2 = 0;
  t->transportSlotE8 = -1;
  t->transportRounds = 0;
  e->end = e->start;
  t->transportStarted = 0;
  e->clock60 = e->start;
  from = gm_BuildQuery(1, 1, t->transportStart);
  if (from == 0)
    goto fail;
  gm_FindById(0, &o, 0, t->transportCart);
  if (o == 0)
    goto fail;
  to = gm_BuildQuery(1, 1, t->transportGoal);
  if (to == 0)
    goto fail;
  if (ai_BTypes[to->type].kind == 0xa && o != 0 && (o->flags20 & 1) != 0) {
    best = to;
    mind = 1e8f;
    d3_PointToWorld(from->object, &from->object->pos, &p1.v);
    for (b = gm_BuildQuery(1, 5, 0xa); b != 0; b = gm_BuildNext()) {
      d3_PointToWorld(b->object, &b->object->pos, &p2.v);
      dx = p2.x - p1.x;
      dy = p2.y - p1.y;
      dz = p2.z - p1.z;
      dist = (float)sqrt(dz * dz + dy * dy + dx * dx);
      if (dist < mind) {
        mind = dist;
        best = b;
      }
    }
    if (best != to) {
      if (t->transportOrder != 0 && t->transportOrder != -1) {
        r = he_FindEvent(1, 1, t->transportOrder);
        if (r != 0) {
          for (k = 0; k < 3; k++) {
            if (r->orderStopsC4[k] == to->id)
              r->orderStopsC4[k] = best->id;
            if (r->orderStopsB8[k] == to->id)
              r->orderStopsB8[k] = best->id;
          }
          if (r->orderBld == to->id)
            r->orderBld = best->id;
        }
      }
      t->transportGoal = best->id;
      to = best;
    }
  }
  if (gm_IsHomeType(from) != 0)
    home1 = 1;
  if (gm_IsHomeType(to) != 0)
    home2 = 1;
  if (home1 != 0 && home2 == 0)
    t->transportMode = 2;
  else if (home1 == 0 && home2 != 0)
    t->transportMode = 1;
  else if (home1 == 0 && home2 == 0)
    t->transportMode = 3;
  else {
    t->transportMode = 4;
    if (from == to) {
      err_Message("he_AllocTransport(): Start and goal are the same!");
      he_FreeEvent(e);
      return;
    }
  }
  t->transportTravel = to->travel30 + from->travel30;
  t->transportAt = from->id;
  t->transportStarted = 0;
  gm_AddTime(&e->end, 0, 0, 1);
  if (o != 0) {
    drv = gm_FindBuildingById(o->bldId);
    ch = o->sceneObj;
    ch->walkSpeed = o->fill * 0.01f * 0.5 + 0.9;
    if (o->type == 0x136)
      ch->walkSpeed = ch->walkSpeed - 0.4;
    else if (o->type == 0x135)
      ch->walkSpeed = ch->walkSpeed + 0.3;
    if (drv != 0) {
      skill = gm_BuildingSkill(drv, 0x11, 1);
      ch->walkSpeed = (skill * 0.01 + 1.0) * ch->walkSpeed;
      t->transportSpeed = ch->walkSpeed;
    }
    o->flags13 |= 0x40;
    if ((e->opts & 2) != 0)
      cm_SendSetField(o->objId, 0x13, 1, 0x40, 0);
    o->job24 = e;
    e->from = o->objId;
    if ((o->flags20 & 1) != 0) {
      gm_StallGoodsList(o, &goods);
      if (goods.value > 0) {
        t->transportEscorts = goods.value / 16000 + util_Random(2);
      } else
        t->transportEscorts = 0;
      t->transportEscorts = t->transportEscorts > 2 ? 2 : t->transportEscorts;
      if (t->transportEscorts != 0) {
        sprintf(text, "he_AllocTransport(): master choose eskorte type %i",
                t->transportEscorts);
        o->escort = (char)t->transportEscorts;
        pay = gm_LevelPayout(goods.value, o->escort);
        if ((e->opts & 2) != 0)
          cm_SendMoveGoodsUnchecked(-1, ai_Chars[e->chr].netId, ai_OwnPlayer,
                                    pay);
      } else
        o->escort = 0;
    }
    e->exSlot = -1;
    t->transportRoute = -1;
    return;
  }
fail:
  he_FreeEvent(e);
}
typedef struct
    HETRANSPORTERS { /* the transporter dummies he_RandomTransporter collects (0x84 bytes) */
  struct D3OBJECT *obj[0x20]; /* 0x00 */
  int n;                      /* 0x80, the count */
} HETRANSPORTERS;

/* 0x5551c0, an object callback of 0x438d40: objects whose name contains "dummy_TRANSPORTER" are collected into the
   context (an HETRANSPORTERS); returns 1 while there is room */

char he_CollectTransporter(D3OBJECT *o, void *ctx) {
  HETRANSPORTERS *l = ctx;

  if (strstr(o->name, "dummy_TRANSPORTER") != 0) {
    l->obj[l->n] = o;
    l->n = l->n + 1;
  }
  return l->n < 0x20;
}
/* 0x555210, collects the transporter dummies of the object obj (d3_ForEachObject (scene 0x5fb5b0, obj, 0x100,
   0x5551c0, list); the object's sibling list is cleared during the walk unless its state bit 1 is set) and
   returns a random one of them, 0 when the list is empty */

struct D3OBJECT *he_RandomTransporter(struct D3OBJECT *obj) {
  HETRANSPORTERS list;
  D3OBJECT *o = obj;
  D3OBJECT *save;

  memset(&list, 0, sizeof(list));
  list.n = 0;
  if (o != 0 && (o->state & 1) == 0) {
    save = o->next;
    o->next = 0;
    d3_ForEachObject(d3_DefaultScene, o, 0x100, he_CollectTransporter, &list);
    o->next = save;
  } else {
    d3_ForEachObject(d3_DefaultScene, o, 0x100, he_CollectTransporter, &list);
  }
  if (list.n == 0)
    return 0;
  return list.obj[util_Random(list.n)];
}
/* 0x5552c0, sets the speed factor (+0x1a0 of the record at +0x3b of `p`) from the event's value +0xc0: * the first constant when 0x76061c points to a value above 100, else * the second when 0x760618 points above 200, else unchanged; a second stage (+0xf1 == 2) multiplies it once more */

void he_SetCartSpeed(AIJOB *ev, AIOBJ *cart) {
  AIJOB *t = ev;
  CHARACTER *ch = cart->sceneObj;

  if (d3t_Snow != 0 && d3t_Snow->count > 0x64)
    ch->walkSpeed = (float)(t->transportSpeed * 0.7);
  else if (d3t_Rain != 0 && d3t_Rain->count > 0xc8)
    ch->walkSpeed = (float)(t->transportSpeed * 0.8);
  else
    ch->walkSpeed = t->transportSpeed;
  if (t->transportWeatherStage == 2)
    ch->walkSpeed = (float)(ch->walkSpeed * 0.8);
}

int d3_VecEqual(const struct D3VECTOR *a, const struct D3VECTOR *b, float eps);

/* 0x555350, the leg of the transport event 15 (AIJOB.transport*) of mode 2 (only the start a home), called by its run
   handler 0x556600 each round: the cart (gm_FindObjectInst; none: nothing) gets its speed (he_SetCartSpeed). The
   first round stops it and sends it to the goal ("Trans") with the route from the 0x44 building to the start
   (cm_SendCartRoute). Later rounds, once the cart's character is idle in the main scene and has not moved since
   the last round (d3_VecEqual within 100.0) or after more than 6 rounds: a goal that is not of the type 10 gets the
   route on to the 0x45 building and the cart's state 0 (cm_SendCartState), the cart's bit 0x40 is cleared
   (cm_SendSetField), the arrival news 0x1c43 (goal of the type 10), 0x1c41 (with 0x1c39, the start, the goal's
   owner and the goal; goals of other kinds than 0x1d / 0x1f) or 0x1c44 goes to a player owner (kind 6 / 7) unless
   the transport window shows the goal (or a market stall 0x92 .. 0x97 / 0x2db of a type 10 goal), the cart is
   escorted (flags20 bit 0) or the transport is quiet, with the quick jump to the goal's main object; the event is
   posted again (cm_SendExSetHE 3). The current scene is selected again at the end */
void he_TransportFromHome(AIJOB *e) {
  AIJOB *t = e;
  AIBLD *guards, *from, *to;
  AIBTYPE *bt;
  AIOBJ *tr, *o;
  CHARACTER *ch;
  int sc;
  char text[0x400];

  guards = gm_BuildQuery(1, 0, 0x44);
  gm_BuildQuery(1, 0, 0x45);
  from = gm_BuildQuery(1, 1, t->transportStart);
  bt = &ai_BTypes[from->type];
  to = gm_BuildQuery(1, 1, t->transportGoal);
  sc = d3_CurrentScene;
  tr = gm_FindObjectInst(t->transportCart);
  if (tr == 0)
    return;
  he_SetCartSpeed(e, tr);
  if (t->transportStarted == 0) {
    cm_SendChrStop(tr->objId);
    cm_SendChrGotoBuilding(tr->objId, to->id, -1, 0, 1, "Trans");
    t->transportRoute = cm_SendCartRoute(guards->id, from->id, tr->objId);
    t->transportStarted = 1;
  } else {
    ch = tr->sceneObj;
    if (ch != 0 && ch->actions == 0 &&
        ((ch->scene == &d3_Scenes[0] &&
          d3_VecEqual(&ch->obj->pos, &t->transportLastPos, 100.0f) != 0) ||
         t->transportRounds > 6)) {
      if (gm_IsType10(to) == 0) {
        t->transportRoute = cm_SendCartRoute(to->id, guards->id, tr->objId);
        cm_SendCartState(tr->objId, 0);
      }
      cm_SendSetField(tr->objId, 0x13, 1, 0, 0x40);
      if (gm_IsType10(to) != 0)
        txt_Format(text, 0x1c43);
      else {
        if (bt->kind != 0x1d && bt->kind != 0x1f)
          txt_Format(text, 0x1c41, 1, 0x1c39, from, to->owner, to);
        else if (gm_IsType10(to) != 0)
          txt_Format(text, 0x1c43);
        else
          txt_Format(text, 0x1c44, to);
      }
      if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
          (sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           (ai_PlayerBuilding != to &&
            (gm_IsType10(to) == 0 || sv_PanelShown == 0 ||
             ((sv_PanelShown->type < 0x92 || sv_PanelShown->type > 0x97) &&
              sv_PanelShown->type != 0x2db)))) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0) {
        o = gm_BuildingMainObject(to);
        if (o != 0)
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 0x608, to->id, o->objId, 0, 0);
        else
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 0x608, to->id, -1, 0, 0);
      }
      e->exSlot = cm_SendExSetHE(3, e);
    }
  }
  d3if_SelectScene(sc, 1);
}

/* 0x555690, the leg of the transport event 15 (AIJOB.transport*) of mode 1 (only the goal a home), called by its run
   handler 0x556600 each round: the cart (gm_FindObjectInst; none: nothing) gets its speed (he_SetCartSpeed). The
   first round stops it, puts it on the road (cm_SendCartState 1) unless the start is of the type 10, sends it to the
   goal ("Trans") and, again unless the start is of the type 10, gives it the route from the 0x44 building to the
   start (cm_SendCartRoute). Later rounds, once the cart is at the goal's door (sv_IsCartAtDoor), give it the route
   on from the goal to the 0x44 building and write the arrival news: 0x1c3b (with 0x1c39 and the goal's player slot)
   for a kind 0x47 goal, 0x1c3d (the start's player slot, the goal's owner and the goal) for a kind 0x47 start, else
   0x1c3f (the goal's owner and the goal) or, for goals of the kinds 0x1d / 0x1f, 0x1c43 (type 10) / 0x1c44 with
   the icon 0x608; the goal types 0x1e / 0x1f / 0x20 add the quick jump "_NACHRICHTEN_HS_58" / "_57" / "_56". The
   news goes to the event's character unless the transport window shows the goal, the cart is escorted (flags20
   bit 0) or the transport is quiet; the event is posted again (cm_SendExSetHE 3) and the scene selected again */
void he_TransportToHome(AIJOB *e) {
  AIJOB *t = e;
  AIBLD *guards, *from, *to;
  AIBTYPE *bt;
  AIOBJ *tr;
  int sc, icon;
  char quick[0x104];
  char text[0x400];

  guards = gm_BuildQuery(1, 0, 0x44);
  gm_BuildQuery(1, 0, 0x45);
  from = gm_BuildQuery(1, 1, t->transportStart);
  to = gm_BuildQuery(1, 1, t->transportGoal);
  sc = d3_CurrentScene;
  tr = gm_FindObjectInst(t->transportCart);
  if (tr == 0)
    return;
  he_SetCartSpeed(e, tr);
  if (t->transportStarted == 0) {
    cm_SendChrStop(tr->objId);
    if (gm_IsType10(from) == 0)
      cm_SendCartState(tr->objId, 1);
    cm_SendChrGotoBuilding(tr->objId, to->id, -1, 0, 0, "Trans");
    if (gm_IsType10(from) == 0)
      t->transportRoute = cm_SendCartRoute(guards->id, from->id, tr->objId);
    t->transportStarted = 1;
  } else if (sv_IsCartAtDoor(tr, to) != 0) {
    t->transportRoute = cm_SendCartRoute(to->id, guards->id, tr->objId);
    if (to->type == 0x47) {
      txt_Format(text, 0x1c3b, 1, 0x1c39, ai_PlayerSlots[to->playerSlot].name);
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                               0x609, to->id, -1, 0, "_NACHRICHTEN_HS_59");
    } else if (from->type == 0x47) {
      txt_Format(text, 0x1c3d, 1, 0x1c39, ai_PlayerSlots[from->playerSlot].name,
                 to->owner, to);
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                               0x609, to->id, -1, 0, "_NACHRICHTEN_HS_60");
    } else {
      bt = &ai_BTypes[to->type];
      icon = 0x609;
      if (to->type == 0x1e)
        strcpy(quick, "_NACHRICHTEN_HS_58");
      else if (to->type == 0x1f)
        strcpy(quick, "_NACHRICHTEN_HS_57");
      else if (to->type == 0x20)
        strcpy(quick, "_NACHRICHTEN_HS_56");
      else
        quick[0] = 0;
      if (bt->kind != 0x1d && bt->kind != 0x1f)
        txt_Format(text, 0x1c3f, 1, 0x1c39, to->owner, to);
      else {
        icon = 0x608;
        if (gm_IsType10(to) != 0)
          txt_Format(text, 0x1c43);
        else
          txt_Format(text, 0x1c44, to);
      }
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0) {
        if (quick[0] != 0)
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 icon, to->id, -1, 0, quick);
        else
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 icon, to->id, -1, 0, 0);
      }
    }
    e->exSlot = cm_SendExSetHE(3, e);
  }
  d3if_SelectScene(sc, 1);
}

/* 0x555b60, "he_TransportStadtStadt" (its debug text), the leg of the transport event 15 (AIJOB.transport*) of mode 3
   (neither building a home), called by its run handler 0x556600 each round. The cart travels in two stages by
   AIJOB.transportAt. At the start (at == the start's id, not started): in scene 0 the goal's transporter dummy
   (he_RandomTransporter, else its object) gives the point the cart walks to, the cart is looked up in the 0x44
   building's objects (a start of the type 10) or the start's (else gm_FindObjectInst), gets its speed, its place on
   the ground cell of that point (lastPos) and, unless the start is of the type 10, its state 1 and the route from
   the 0x44 building to the start; then it walks to the cell, the scene is selected again and `at` becomes the 0x44
   building. At the 0x44 building: the cart (its objects, else gm_Query 2) records the target of its walk action
   while it walks; idle and not moved (d3_VecEqual within 300.0) or after more than 6 rounds, it has arrived: the
   bit 0x40 is cleared, a goal not of the type 10 gets the cart's state 0 and the route on to the 0x44 building,
   the news 0x1c43 (type 10) / 0x1c44 goes to the event's character unless the transport window shows the goal (or
   a market stall 0x92 .. 0x97 / 0x2db of a type 10 goal), the cart is escorted or the transport is quiet, `at`
   becomes the goal and the event is posted again (cm_SendExSetHE 3); arrived after 6 rounds while still far from
   its last place gives the debug text "character-action not attached but target should be reached" */
void he_TransportStadtStadt(AIJOB *ev) {
  /* clang-format off */
    AIJOB *t = ev;
    AIBLD *guards, *from, *to;
    AIOBJ *tr;
    D3OBJECT *o;
    CHARACTER *ch;
    D3SM *hmap;
    D3OBJECT *bo;
    CHACTION *walk;
    int sc;
    char text[0x400];
    char err[0x400];

    guards = gm_BuildQuery(1, 0, 0x44);
    gm_BuildQuery(1, 0, 0x45);
    from = gm_BuildQuery(1, 1, t->transportStart);
    to = gm_BuildQuery(1, 1, t->transportGoal);
    if (t->transportAt == from->id && t->transportStarted == 0) {
        D3VECTOR4 back, pos;

        sc = d3_CurrentScene;
        d3if_SelectScene(0, 1);
        o = he_RandomTransporter(to->object);
        if (o != 0)
            d3_PointToWorld(o, &o->pos, &pos.v);
        else
            d3_PointToWorld(to->object, &to->object->pos, &pos.v);
        if (gm_IsType10(from) != 0)
            tr = gm_Query(guards->objList, 1, 1, t->transportCart);
        else
            tr = gm_Query(from->objList, 1, 1, t->transportCart);
        if (tr == 0)
            tr = gm_FindObjectInst(t->transportCart);
        if (tr != 0) {
            int px, pz;
            float py;

            ch = tr->sceneObj;
            he_SetCartSpeed(ev, tr);
            hmap = ch_GetHMap(ch);
            t->transportStarted = 1;
            d3_GetHeightAt(hmap, &pos.v, &px, &pz, &py);
            t->transportLastPos.x = pos.x;
            t->transportLastPos.y = pos.y;
            t->transportLastPos.z = pos.z;
            if (gm_IsType10(from) == 0) {
                if (from->object != 0) {
                    o = he_RandomTransporter(from->object);
                    if (o != 0)
                        d3_PointToWorld(o, &o->pos, &back.v);
                    else {
                        bo = to->object;
                        back.x = bo->pos.x;
                        back.y = bo->pos.y;
                        back.z = bo->pos.z;
                    }
                }
                cm_SendCartState(tr->objId, 1);
            }
            cm_SendChrWalkTo(tr->objId, px, pz, 0);
            if (gm_IsType10(from) == 0)
                t->transportRoute = cm_SendCartRoute(guards->id, t->transportStart, t->transportCart);
        } else
            gm_Query(0, 2, 7, 1, t->transportCart);
        d3if_SelectScene(sc, 1);
        t->transportAt = guards->id;
        return;
    }
    if (t->transportAt != guards->id)
        return;
    tr = gm_Query(guards->objList, 1, 1, t->transportCart);
    if (tr == 0)
        tr = gm_Query(0, 2, 7, 1, t->transportCart);
    if (tr != 0) {
        ch = tr->sceneObj;
        he_SetCartSpeed(ev, tr);
        walk = ch->actions;
        if (walk != 0 && walk->type == 0x2d) {
            t->transportLastPos.x = walk->u.walk.tpos.x;
            t->transportLastPos.y = walk->u.walk.tpos.y;
            t->transportLastPos.z = walk->u.walk.tpos.z;
        }
        if (ch->actions == 0 && (d3_VecEqual(&ch->obj->pos, &t->transportLastPos, 300.0f) != 0 || t->transportRounds > 6)) {
            cm_SendSetField(tr->objId, 0x13, 1, 0, 0x40);
            if (gm_IsType10(to) == 0) {
                cm_SendCartState(tr->objId, 0);
                t->transportRoute = cm_SendCartRoute(to->id, guards->id, t->transportCart);
            }
            if (gm_IsType10(to) != 0)
                txt_Format(text, 0x1c43);
            else
                txt_Format(text, 0x1c44, to);
            if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow
                 || (ai_PlayerBuilding != to
                     && (gm_IsType10(to) == 0 || sv_PanelShown == 0
                         || (ai_PlayerBuilding != to
                             && (gm_IsType10(to) == 0
                                 || ((sv_PanelShown->type < 0x92 || sv_PanelShown->type > 0x97) && sv_PanelShown->type != 0x2db))))))
                && (tr->flags20 & 1) == 0 && t->transportQuiet == 0) {
                AIOBJ *mo = gm_BuildingMainObject(to);

                if (mo != 0)
                    he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, tr->objId, text, 0, 0x608, to->id, mo->objId, 0, 0);
                else
                    he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, tr->objId, text, 0, 0x608, to->id, -1, 0, 0);
            }
            t->transportAt = t->transportGoal;
            ev->exSlot = cm_SendExSetHE(3, ev);
            if (ch->actions == 0 && t->transportRounds > 6 && d3_VecEqual(&ch->obj->pos, &t->transportLastPos, 100.0f) == 0)
                sprintf(err, "he_TransportStadtStadt(): character-action not attached but target should be reached : %s",
                        txt_Ptrs[0x48e + to->type * 14]);
        }
    } else {
        __asm int 3                                     /* the original traps here and repeats the query */
        gm_Query(0, 2, 7, 1, t->transportCart);
    }
  /* clang-format on */
}

/* 0x556080, the leg of the transport event 15 (AIJOB.transport*) of mode 4 (both buildings homes), called by its run
   handler 0x556600 each round: the cart (gm_FindObjectInst; none: nothing) gets its speed (he_SetCartSpeed). The
   first round stops it, sends it to the goal ("Trans") and gives it the route from the 0x44 building to the start
   (cm_SendCartRoute). Later rounds, once the cart is at the goal's door (sv_IsCartAtDoor): the route on from the
   goal to the 0x44 building, the cart moves into the goal's scene universe at "dummy_TRANSPORTER_ENTRY", which is
   selected; with a transporter dummy and a height map there it walks to the ground cell of `pos` (the original
   never sets pos: no d3_PointToWorld here, unlike the other legs); its bit 0x40 is cleared and the arrival news
   goes out as in he_TransportToHome (0x1c3b / 0x1c3d / 0x1c3f / 0x1c43 / 0x1c44 with the quick jumps
   "_NACHRICHTEN_HS_56" .. "_60"), the event is posted again (cm_SendExSetHE 3). Not at the door after more than
   16 rounds with the cart's character idle: it is sent to the goal again and the rounds start over. The scene
   selected at the start is selected again at the end */
void he_TransportHomeHome(AIJOB *e) {
  AIJOB *t = e;
  AIBLD *guards, *from, *to;
  AIBTYPE *bt;
  AIOBJ *tr;
  CHARACTER *ch;
  D3VECTOR4 pos;
  int sc, u, px, pz;
  float py;
  char quick[0x104];
  char text[0x400];

  guards = gm_BuildQuery(1, 0, 0x44);
  gm_BuildQuery(1, 0, 0x45);
  from = gm_BuildQuery(1, 1, t->transportStart);
  to = gm_BuildQuery(1, 1, t->transportGoal);
  sc = d3_CurrentScene;
  tr = gm_FindObjectInst(t->transportCart);
  if (tr == 0)
    return;
  he_SetCartSpeed(e, tr);
  if (t->transportStarted == 0) {
    cm_SendChrStop(tr->objId);
    cm_SendChrGotoBuilding(tr->objId, to->id, -1, 0, 1, "Trans");
    t->transportRoute = cm_SendCartRoute(guards->id, from->id, tr->objId);
    t->transportStarted = 1;
  } else if (sv_IsCartAtDoor(tr, to) != 0) {
    t->transportRoute = cm_SendCartRoute(to->id, guards->id, tr->objId);
    cm_RequestChrMoveToUniverse(tr->objId, to->id, -1,
                                "dummy_TRANSPORTER_ENTRY");
    u = init_BuildingSceneUniverse(to);
    d3if_SelectScene(u, 1);
    if (he_RandomTransporter(0) != 0 && d3_Scenes[u].hmap != 0 &&
        d3_GetHeightAt(d3_Scenes[u].hmap, &pos.v, &px, &pz, &py) != 0)
      cm_SendChrWalkTo(tr->objId, px, pz, u);
    cm_SendSetField(tr->objId, 0x13, 1, 0, 0x40);
    if (to->type == 0x47) {
      txt_Format(text, 0x1c3b, 1, 0x1c39, ai_PlayerSlots[to->playerSlot].name);
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                               0x609, to->id, -1, 0, "_NACHRICHTEN_HS_59");
    } else if (from->type == 0x47) {
      txt_Format(text, 0x1c3d, 1, 0x1c39, ai_PlayerSlots[from->playerSlot].name,
                 to->owner, to);
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                               0x609, to->id, -1, 0, "_NACHRICHTEN_HS_60");
    } else {
      bt = &ai_BTypes[to->type];
      if (to->type == 0x1e)
        strcpy(quick, "_NACHRICHTEN_HS_58");
      else if (to->type == 0x1f)
        strcpy(quick, "_NACHRICHTEN_HS_57");
      else if (to->type == 0x20)
        strcpy(quick, "_NACHRICHTEN_HS_56");
      else
        quick[0] = 0;
      if (bt->kind != 0x1d && bt->kind != 0x1f)
        txt_Format(text, 0x1c3f, 1, 0x1c39, to->owner, to);
      else if (gm_IsType10(to) != 0)
        txt_Format(text, 0x1c43);
      else
        txt_Format(text, 0x1c44, to);
      if ((sv_Frames[sv_FrameDepth].cb != ai_TransportWindow ||
           ai_FallbackBuilding != to) &&
          (tr->flags20 & 1) == 0 && t->transportQuiet == 0) {
        if (quick[0] != 0)
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 0x609, to->id, -1, 0, quick);
        else
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, tr->objId, text, 0,
                                 0x609, to->id, -1, 0, 0);
      }
    }
    e->exSlot = cm_SendExSetHE(3, e);
  } else if (t->transportStarted != 0 && t->transportRounds > 0x10) {
    ch = tr->sceneObj;
    if (ch != 0 && ch->actions == 0) {
      cm_SendChrGotoBuilding(tr->objId, to->id, -1, 0, 1, "Trans");
      t->transportRounds = 0;
    }
  }
  d3if_SelectScene(sc, 1);
}
/* 0x556600, "he_RunTransport" (its debug text), the run handler of the transport event 15 (AIJOB.transport*; registered
   with he_AllocTransport). A posted record (opts 2) waits for its cm slot. Without the 0x44 / 0x45 buildings, the
   start or the goal the stage becomes -1; without the cart the event is freed. By AIJOB.stage:
   -2: the event goes to the player's character (he_SetEventChar) and on to the stage 1 (the cart at the 0x44
       building or the start) or -1 (at the goal).
   -1: the end: the cart (gm_Query 2) is damaged (-2, three times in four) and the event's window closed (a posted
       record), its bit 0x40 and its job cleared, the event freed.
    0: due one second later, posted with the next stage.
    1: once due and the cart's route sent (a failed route: stage -1), the leg of the mode (he_TransportFromHome /
       ToHome / StadtStadt / HomeHome) runs, the rounds count up and the next round is due in 5 minutes. In the 5th
       round a random 0 .. 29 above the cart's fill rattles it (news 0x1c46 with the good, cm_SendFreeObject) and ends
       the transport; from then on, once, the weather (snow -15, rain -10) and the skill of the cart's building
       (+100) give the chance that the cart arrives undamaged: else it is damaged (-10, the news 0x1c45 to a player
       owner of an unescorted cart) and slowed (weatherStage 2), else weatherStage 1.
    2: once the route is sent: the sys message 4 for the goal one second later, the cart noise "Karrenrumpeln_r"
       when the player looks at the goal, posted with the stage 3.
    3: a quiet transport goes on to the stage 4, else to -1.
    4: the cart unloads at its point for the player slot of a kind 0x47 goal (else the own player), stage 5.
    5: at the building of the cart's route point that takes the load (ai_IsBuildingOpen) the cart hands it over
       (rt_LoadAtPoint) and the transport ends (-1); no such point: -1; else it waits 15 minutes */
void he_RunTransport(AIJOB *e) {
  AIJOB *t = e;
  AIBLD *guards, *market, *from, *to, *b;
  AIOBJ *tr, *c;
  RTPOINT *p;
  HESOLDMSG m;
  int mode;
  char pl;
  float chance;
  char text[0x400];

  if ((e->opts & 2) != 0 && e->exSlot != -1) {
    if (cm_GetSlotState(e->exSlot) == 0)
      return;
    e->exSlot = -1;
  }
  guards = gm_BuildQuery(1, 0, 0x44);
  market = gm_BuildQuery(1, 0, 0x45);
  from = gm_BuildQuery(1, 1, t->transportStart);
  to = gm_BuildQuery(1, 1, t->transportGoal);
  if (guards == 0 || from == 0 || to == 0 || market == 0)
    e->stage = -1;
  tr = gm_FindObjectInst(t->transportCart);
  if (tr == 0) {
    he_FreeEvent(e);
    return;
  }
  switch (e->stage) {
  case 0:
    if ((e->opts & 2) == 0)
      return;
    t->transportSlotE8 = -1;
    gm_AddTime(&e->end, 0, 0, 1);
    e->exSlot = cm_SendExSetHE(e->stage + 1, e);
    return;
  case 1: {
    AIOBJ *o;

    if ((e->opts & 2) == 0)
      return;
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    if (t->transportRoute != -1 && cm_GetSlotState(t->transportRoute) == 0)
      return;
    if (t->transportRoute != -1 && cm_GetSlotState(t->transportRoute) == 2) {
      e->exSlot = cm_SendExSetHE(-1, e);
      break;
    }
    t->transportRoute = -1;
    mode = t->transportMode;
    if (mode == 2)
      he_TransportFromHome(e);
    else if (mode == 1)
      he_TransportToHome(e);
    else if (mode == 3)
      he_TransportStadtStadt(e);
    else if (mode == 4)
      he_TransportHomeHome(e);
    else
      err_Message("he_RunTransport: invalid type!");
    t->transportRounds++;
    e->clock60 = ai_Time;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    if (t->transportRounds == 5) {
      gm_FindById(0, &o, 0, t->transportCart);
      if (util_Random(0x1e) > o->fill) {
        txt_Format(text, 0x1c46, o->id * 2 + 0x9a8);
        he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec, 0);
        cm_SendFreeObject(o->objId);
        e->exSlot = cm_SendExSetHE(-1, e);
        return;
      }
    }
    if (t->transportWeatherStage != 0 || t->transportRounds < 5)
      return;
    chance = 0;
    gm_FindById(0, &o, 0, t->transportCart);
    b = gm_FindBuildingById(o->bldId);
    if (b != 0)
      chance = gm_BuildingSkill(b, 2, 1) + 100.0f;
    if (d3t_Snow != 0 && d3t_Snow->count > 100)
      chance -= 15.0f;
    else if (d3t_Rain != 0 && d3t_Rain->count > 200)
      chance -= 10.0f;
    if (util_Random(0x69) > o->fill * (float)(chance * 0.01)) {
      if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
          (o->flags20 & 1) == 0) {
        txt_Format(text, 0x1c45);
        he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x608, 0);
      }
      gm_ChangeObjektZustand(o->objId, -10);
      t->transportWeatherStage = 2;
      return;
    }
    t->transportWeatherStage = 1;
    return;
  }
  case 2:
    if (!e->opts & 2) /* the original's test: `!` before `&`, never true */
      return;
    if (t->transportRoute != -1 && cm_GetSlotState(t->transportRoute) == 0)
      return;
    t->transportRoute = -1;
    gm_BuildQuery(1, 1, t->transportGoal);
    m.due = ai_Time;
    gm_AddTime(&m.due, 0, 0, 1);
    b = gm_BuildQuery(1, 1, t->transportGoal);
    m.sold.bld = b->id;
    cm_SendExSysMessage(4, &m);
    if (ai_PlayerBuilding == b || ai_FallbackBuilding == b)
      sb_PlaySample(snd_TransportBank, "Karrenrumpeln_r", 1, 0x3f, 0x7f, 0, 0);
    e->exSlot = cm_SendExSetHE(3, e);
    return;
  case 3:
    if ((e->opts & 2) == 0)
      return;
    if (t->transportQuiet != 0)
      e->exSlot = cm_SendExSetHE(4, e);
    else
      e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 4:
    if ((e->opts & 2) == 0)
      return;
    pl = ai_OwnPlayer;
    b = gm_BuildQuery(1, 1, t->transportGoal);
    if (b->type == 0x47)
      pl = (char)b->playerSlot;
    rt_UnloadAtPoint(tr, pl);
    e->exSlot = cm_SendExSetHE(5, e);
    return;
  case 5:
    if ((e->opts & 2) == 0)
      return;
    p = rt_PointAt(tr->route, tr->routeIdx);
    if (p == 0 || (b = gm_FindBuildingById(p->buildingId)) == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (ai_IsBuildingOpen(b, 0, 0) != 0) {
      pl = ai_OwnPlayer;
      if (b->type == 0x47)
        pl = (char)b->playerSlot;
      rt_LoadAtPoint(tr, pl);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0xf, 0);
    return;
  case -2:
    he_SetEventChar(e, ai_PlayerChar->id);
    if (t->transportAt == guards->id)
      e->exSlot = cm_SendExSetHE(1, e);
    else if (t->transportAt == to->id)
      e->exSlot = cm_SendExSetHE(-1, e);
    else if (t->transportAt == from->id)
      e->exSlot = cm_SendExSetHE(1, e);
    return;
  case -1:
    c = gm_Query(0, 2, 7, 1, t->transportCart);
    if ((e->opts & 2) != 0 && c != 0) {
      if (util_Random(100) > 75)
        gm_ChangeObjektZustand(c->objId, -2);
      if (t->transportSlotE8 != -1)
        d2_RemoveWindow(t->transportSlotE8);
    }
    if (c != 0) {
      c->job24 = 0;
      c->flags13 &= ~0x40;
    }
    he_FreeEvent(e);
    return;
  }
}

/* 0x556dc0, the allocation handler of the event 16 (AIJOB.cartRepair*; run by 0x556ed0): the work ends `per` minutes per
   point after the start (done), the event is due one second after the start; a cart already under such work (flags13
   bit 0x20) frees the event, else it gets the bit (cm_SendSetField 0x13); the clock60 starts now and the cart's byte
   +0x12 is to rise by `points`, to 100 at most (target). Reasoned: a repair of the cart (its run handler changes
   the object's state, gm_ChangeObjektZustand, and the transport damages the same byte) */
void he_AllocCartRepair(AIJOB *e) {
  AIJOB *r = e;
  AIOBJ *o = 0;

  r->cartRepairDone = e->start;
  gm_AddTime(&r->cartRepairDone, 0, r->cartRepairPer * r->cartRepairPoints, 0);
  e->end = e->start;
  gm_AddTime(&e->end, 0, 0, 1);
  gm_FindById(0, &o, 0, r->cartRepairCart);
  if (o != 0) {
    if ((o->flags13 & 0x20) != 0) {
      he_FreeEvent(e);
      return;
    }
    cm_SendSetField(o->objId, 0x13, 1, 0x20, 0);
  }
  e->clock60 = ai_Time;
  r->cartRepairTarget = o->fill + r->cartRepairPoints >= 100
                            ? 100
                            : o->fill + r->cartRepairPoints;
}
/* 0x556ed0, the run handler of the event 16 (AIJOB.cartRepair*; allocated by he_AllocCartRepair), by AIJOB.stage:
   0: the cart (gm_Query 2; gone: the event is freed) below its target gets the minutes since the last round /
      `per` points (gm_ChangeObjektZustand) and the next round is due in 2 * per minutes; at the target the next
      stage. The clock60 is set to now.
   1: done: with `notify` the news 0x1c49 (the cart's good) goes to the event's character with the quick jump
      "_NACHRICHTEN_HS_55" to the main object of the building (AIJOB.from); the cart's bit 0x20 is cleared, its byte
      +0x12 set to the target (a field delta) and the event freed.
   -2 / -1: cancelled: the cart's bit 0x20 is cleared and the event freed */
void he_RunCartRepair(AIJOB *e) {
  AIJOB *r = e;
  AIOBJ *o = 0, *q;
  int mins;
  char v;
  char text[0x80];

  switch (e->stage) {
  case 0:
    mins = gm_MinutesBetween(&e->clock60, &ai_Time);
    o = gm_Query(0, 2, 7, 1, r->cartRepairCart);
    if (o == 0) {
      o = gm_Query(0, 2, 7, 1, r->cartRepairCart);
      he_FreeEvent(e);
      return;
    }
    if (o->fill < r->cartRepairTarget) {
      gm_ChangeObjektZustand(r->cartRepairCart, mins / r->cartRepairPer);
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, r->cartRepairPer * 2, 0);
    } else
      e->stage++;
    e->clock60 = ai_Time;
    return;
  case 1:
    gm_FindById(0, &o, 0, r->cartRepairCart);
    if (r->cartRepairNotify != 0) {
      txt_Format(text, 0x1c49, o->id * 2 + 0x9a8);
      q = gm_BuildingMainObject(gm_FindBuildingById(e->from));
      if (q != 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                               e->from, q->objId, 0, "_NACHRICHTEN_HS_55");
      else
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                               e->from, -1, 0, "_NACHRICHTEN_HS_55");
    }
    cm_SendSetField(o->objId, 0x13, 1, 0, 0x20);
    v = (char)r->cartRepairTarget;
    cm_BeginFieldBlock(o, o->objId);
    cm_AddFieldDelta(1, 1, 0x12, &v);
    cm_SendFieldDeltas();
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    gm_FindById(0, &o, 0, r->cartRepairCart);
    if (o != 0)
      cm_SendSetField(o->objId, 0x13, 1, 0, 0x20);
    he_FreeEvent(e);
    return;
  }
}
/* 0x557160, the allocation handler of the message box event 17 (AIJOB.msgBox*): state 0 and no voice; a character
   that is not a player character (kind 6) frees the record at once */

void he_AllocMessageBox(AIJOB *ev) {
  AIJOB *m = ev;

  ev->stage = 0;
  m->msgBoxVoice = 0;
  if (ai_Chars[ev->chr].kind != 6)
    he_FreeEvent(ev);
}

void sv_SelectPanelObject(struct AIBLD *o, int b, char *c);

/* 0x557190, the run handler of the message box event 17 (AIJOB.msgBox*; allocated by he_AllocMessageBox), only for the player's
   own character while a game runs. Stage 0 opens the event window by the flavour flags: 2 a quick jump
   ("misc\EventMessagebox_QJ", with 1 "_QJ_BIG"; the news 0x1ba2 when the player stands at that building and its
   object, else 0x1ba1), 1 "misc\EventMessagebox_BIG" / 0x20 "misc\EventMsgbox_History" (news 0x1ba3), 4
   "misc\EventMessagebox_Cutscenes", 0x40 "misc\EventMessagebox_Help", else "misc\EventMessagebox" (news 0x7d); no
   window: the event is freed. The text goes into the form 0, the sound "NeueMessage_s_01" plays (game state not 2),
   8 activates the window, 0x10 speaks the text after the text's NUL (snd_QueueVoice); the box stays 24 hours for a
   cutscene, else 8 (16 when that ends before 6 o'clock). Stage 1: a cutscene box follows its party (gone: -1; due
   and running: done, unless a quick jump's party is flagged 0x10; due and not running: the player leaves it, -1);
   other boxes end when due. A click on the window: 0 carries the quick jump out (sv_SelectPanelObject on the
   building and object), 1 (or the slot confirmed) dismisses it and leaves a cutscene's party; both stop the voice,
   unpause a help box and close the window. Stages -2 / -1 stop the voice, unpause and close it */
void he_RunMessageBox(AIJOB *e) {
  AIJOB *m = e;
  AIBLD *bld;
  G28REC *p;
  char speak[0x80];

  if (ai_PlayerId != e->chr || ai_GameState == 0)
    return;
  switch (e->stage) {
  case 0:
    if ((m->msgBoxFlags & 2) != 0) {
      bld = 0;
      if ((m->msgBoxFlags & 1) != 0)
        he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox_QJ_BIG", m->msgBoxPic);
      else
        he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox_QJ", m->msgBoxPic);
      if (e->slot == 0) {
        he_FreeEvent(e);
        return;
      }
      if (ai_PlayerBuilding != 0)
        bld = ai_PlayerBuilding;
      else if (ai_FallbackBuilding != 0)
        bld = ai_FallbackBuilding;
      d2_SetForm(e->slot->win, 1);
      if (bld != 0 && bld->id == m->msgBoxBld && m->msgBoxSel == 0 &&
          ((sv_PanelShown != 0 && sv_PanelShown->objId == m->msgBoxObj) ||
           m->msgBoxObj == -1))
        io_PrintText(0x1ba2);
      else
        io_PrintText(0x1ba1);
    } else if ((m->msgBoxFlags & 1) != 0) {
      he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox_BIG", m->msgBoxPic);
      if (e->slot != 0) {
        d2_SetForm(e->slot->win, 1);
        io_PrintText(0x1ba3);
      }
    } else if ((m->msgBoxFlags & 0x20) != 0) {
      he_OpenEventSlot(e, 0, 0, "misc\\EventMsgbox_History", m->msgBoxPic);
      if (e->slot != 0) {
        d2_SetForm(e->slot->win, 1);
        io_PrintText(0x1ba3);
      }
    } else if ((m->msgBoxFlags & 4) != 0) {
      he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox_Cutscenes",
                       m->msgBoxPic);
    } else if ((m->msgBoxFlags & 0x40) != 0) {
      he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox_Help", m->msgBoxPic);
    } else {
      he_OpenEventSlot(e, 0, 0, "misc\\EventMessagebox", m->msgBoxPic);
      if (e->slot != 0) {
        d2_SetForm(e->slot->win, 1);
        io_PrintText(0x7d);
      }
    }
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_CentreViewWindows(e->slot->win);
    d2_SetForm(e->slot->win, 0);
    io_PrintText((intptr_t)"%s", e->text);
    if (ai_GameState != 2)
      sb_PlaySample(snd_SystemBank, "NeueMessage_s_01", 1, 0x3f, 0x7f, 0, 0);
    if ((m->msgBoxFlags & 8) != 0)
      he_ActivateSlot(e->slot);
    if ((m->msgBoxFlags & 0x10) != 0) {
      char *s = e->text + strlen(e->text) + 1;

      memcpy(speak, s, strlen(s) + 1);
      m->msgBoxVoice = snd_QueueVoice(-7, 0, speak, 0, 0x7d0);
    }
    e->start = ai_Time;
    e->end = ai_Time;
    if ((m->msgBoxFlags & 4) != 0)
      gm_AddTime(&e->end, 0x18, 0, 0);
    else {
      gm_AddTime(&e->end, 8, 0, 0);
      if (e->end.hour < 6)
        gm_AddTime(&e->end, 8, 0, 0);
    }
    e->stage++;
    return;
  case 1:
    if ((m->msgBoxFlags & 4) != 0) {
      p = cm_PartyById(m->msgBoxParty);
      if (p == 0)
        e->stage = -1;
      else if (gm_CompareTime(&ai_Time, &p->time) > 0) {
        if ((p->flags & 0x80) != 0) {
          if ((m->msgBoxFlags & 2) == 0 || m->msgBoxBld == -1 ||
              (p->flags & 0x10) == 0)
            p->done = 1;
          he_ReleaseSlot(e);
          he_FreeEvent(e);
          return;
        }
        if ((ai_GameFlags & 8) != 0)
          cm_RemovePartyMember(m->msgBoxParty, ai_Chars[ai_PlayerId].netId);
        else if ((ai_GameFlags & 4) != 0)
          cm_SendLeaveParty(m->msgBoxParty, ai_Chars[ai_PlayerId].netId);
        e->stage = -1;
      }
    } else if (gm_CompareTime(&ai_Time, &e->end) > 0) {
      if ((m->msgBoxFlags & 0x40) != 0 && (ai_GameFlags & 4) == 0)
        tb_Paused = 0;
      he_ReleaseSlot(e);
      he_FreeEvent(e);
      return;
    }
    if (e->slot == 0)
      return;
    if (d2_ClickedForm != e->slot->win &&
        (he_SlotConfirmed == 0 || he_ActiveSlot != e->slot))
      return;
    if (d2_ClickedId != -1 ||
        (he_SlotConfirmed != 0 && he_ActiveSlot == e->slot)) {
      if (d2_ClickedId != 0) {
        if (d2_ClickedId == 1 || he_SlotConfirmed != 0) {
          if ((m->msgBoxFlags & 4) != 0 &&
              (p = cm_PartyById(m->msgBoxParty)) != 0) {
            if ((p->flags & 0x80) != 0) {
              if ((m->msgBoxFlags & 2) == 0 || m->msgBoxBld == -1 ||
                  (p->flags & 0x10) == 0)
                p->done = 1;
            } else if ((ai_GameFlags & 8) != 0)
              cm_RemovePartyMember(m->msgBoxParty, ai_Chars[ai_PlayerId].netId);
            else if ((ai_GameFlags & 4) != 0)
              cm_SendLeaveParty(m->msgBoxParty, ai_Chars[ai_PlayerId].netId);
          }
          if ((m->msgBoxFlags & 0x10) != 0 && m->msgBoxVoice != 0) {
            sb_Stop(m->msgBoxVoice, 0);
            m->msgBoxVoice = 0;
          }
          if ((m->msgBoxFlags & 0x40) != 0 && (ai_GameFlags & 4) == 0)
            tb_Paused = 0;
          if (dm_L.lclick != 0) {
            di_GuiClick = 1;
            di_ClearButtons();
          }
          he_ReleaseSlot(e);
          he_FreeEvent(e);
        }
        he_SlotConfirmed = 0;
      } else {
        if ((m->msgBoxFlags & 4) != 0) {
          p = cm_PartyById(m->msgBoxParty);
          if ((m->msgBoxFlags & 2) == 0 || m->msgBoxBld == -1 ||
              (p->flags & 0x10) == 0)
            p->done = 1;
        }
        if ((m->msgBoxFlags & 2) != 0) {
          bld = gm_BuildQuery(1, 1, m->msgBoxBld);
          if (bld == 0)
            return;
          sv_SelectPanelObject(bld, m->msgBoxObj, &m->msgBoxSel);
        }
        if ((m->msgBoxFlags & 0x10) != 0 && m->msgBoxVoice != 0) {
          sb_Stop(m->msgBoxVoice, 0);
          m->msgBoxVoice = 0;
        }
        if ((m->msgBoxFlags & 0x40) != 0 && (ai_GameFlags & 4) == 0)
          tb_Paused = 0;
        if (dm_L.lclick != 0) {
          di_GuiClick = 1;
          di_ClearButtons();
        }
        he_ReleaseSlot(e);
        he_FreeEvent(e);
        return;
      }
    }
    return;
  case -2:
  case -1:
    if ((m->msgBoxFlags & 0x10) != 0 && m->msgBoxVoice != 0) {
      sb_Stop(m->msgBoxVoice, 0);
      m->msgBoxVoice = 0;
    }
    if ((m->msgBoxFlags & 0x40) != 0 && (ai_GameFlags & 4) == 0)
      tb_Paused = 0;
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
}

void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c, struct AIJOB *g);

/* 0x5578a0, the run handler of the slot order event 18 (AIJOB.slotOrder*, the type 0x12 message ai_BuySlots posts;
   allocated by he_AllocSlotOrderStore). Stage 0 goes on to 1. Stage 1, once due: with the workshop object (gm_FindById) and
   the event's building (AIJOB.from; either gone: the event is freed), one slot a round is added: of the first
   kind (lvl1c) while add1c lasts, then of the second (lvl1d) while add1d lasts, each only below the building
   type's limit (AIBTYPE.min0 / min1; an object of type 0x116 has max116 for both), as a field delta of 1. Both
   counts done: the news 0x1bba (the building) goes to the event's character with the quick jump to the
   building's main object (icon 0x5f6, 0x60b for a master's character with flags1b4 bit 0) and the event is freed;
   else the next round is due in 15 minutes. Stages -2 / -1 free the event */
void he_RunSlotOrder(AIJOB *e) {
  AIJOB *s = e;
  AIOBJ *o, *q;
  AIBLD *b;
  AIBTYPE *bt;
  AICHAR *m;
  int one, lim0, lim1, tid;
  char text[0x400];

  switch (e->stage) {
  case 0:
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    gm_FindById(0, &o, 0, s->slotOrderObj);
    if (o == 0)
      break;
    one = 1;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0)
      break;
    bt = &ai_BTypes[b->type];
    if (o->type != 0x116) {
      lim0 = bt->min0;
      lim1 = bt->min1;
    } else {
      lim0 = bt->max116;
      lim1 = lim0;
    }
    if (s->slotOrder1c > 0) {
      s->slotOrder1c--;
      if (o->lvl1c < lim0) {
        cm_BeginFieldBlock(o, o->objId);
        cm_AddFieldValues(1, 1, (char *)&o->lvl1c - cm_FieldObject, &one);
        cm_SendFieldDeltas();
      }
    } else if (s->slotOrder1d > 0) {
      s->slotOrder1d--;
      if (o->lvl1d < lim1) {
        cm_BeginFieldBlock(o, o->objId);
        cm_AddFieldValues(1, 1, (char *)&o->lvl1d - cm_FieldObject, &one);
        cm_SendFieldDeltas();
      }
    }
    if (s->slotOrder1d == 0 && s->slotOrder1c == 0) {
      tid = 0x5f6;
      b = gm_BuildQuery(1, 1, e->from);
      if (b == 0)
        break;
      m = gm_FindCharacterByMaster(b);
      if (m != 0 && (m->flags1b4 & 1) != 0)
        tid = 0x60b;
      q = gm_BuildingMainObject(b);
      txt_Format(text, 0x1bba, b);
      if (q != 0)
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, tid, b->id,
                               q->objId, 0, 0);
      else
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, tid, b->id,
                               -1, 0, 0);
      he_FreeEvent(e);
      return;
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0xf, 0);
    return;
  case -2:
  case -1:
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x557b30, the allocation handler shared by the slot order event 18 and the store extension event 19: the due
   clock (AIJOB.end) starts as the start clock, two hours later */

void he_AllocSlotOrderStore(AIJOB *e) {

  e->end = e->start;
  gm_AddTime(&e->end, 2, 0, 0);
}
/* 0x557b70, the run handler of the store extension event 19 (AIJOB.storeExt*; allocated by he_AllocSlotOrderStore, its debug
   name "he_RunLagerErweitern"). Stage 0 goes on to 1. Stage 1, once due: the store object (gm_FindById; gone: the
   text "Wrong LagerID" and the event is freed) gets one more unit of capacity (AIOBJ.count + 1, a field delta of
   4 bytes); while rounds are left the next one is due in 15 minutes, after the last the news 0x1bbb (the event's
   building, AIJOB.from) goes to the event's character with the quick jump to the building's main object (icon
   0x606, 0x60b for a master's character with flags1b4 bit 0) and the event is freed. Stages -2 / -1 free the
   event */
void he_RunStoreExtension(AIJOB *e) {
  AIJOB *x = e;
  AIOBJ *o, *q;
  AIBLD *b;
  AICHAR *m;
  int one, tid;
  char text[0x400];

  switch (e->stage) {
  case 0:
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    one = 1;
    gm_FindById(0, &o, 0, x->storeExtObj);
    if (o != 0) {
      cm_BeginFieldBlock(o, o->objId);
      cm_AddFieldValues(4, 1, (char *)&o->count - cm_FieldObject, &one);
      cm_SendFieldDeltas();
      if (--x->storeExtRounds <= 0) {
        tid = 0x606;
        b = gm_BuildQuery(1, 1, e->from);
        if (b == 0)
          break;
        m = gm_FindCharacterByMaster(b);
        if (m != 0 && (m->flags1b4 & 1) != 0)
          tid = 0x60b;
        q = gm_BuildingMainObject(b);
        txt_Format(text, 0x1bbb, b);
        if (q != 0)
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, tid,
                                 b->id, q->objId, 0, 0);
        else
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, tid,
                                 b->id, -1, 0, 0);
        he_FreeEvent(e);
        return;
      } else {
        e->end = ai_Time;
        gm_AddTime(&e->end, 0, 0xf, 0);
      }
    } else {
      err_Message("he_RunLagerErweitern():Wrong LagerID...");
      he_FreeEvent(e);
    }
    return;
  case -2:
  case -1:
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x557d70, the allocation handler of the herb gathering event 20 (AIJOB.herbs*): every gatherer id (AIJOB.ids, AIJOB.herbsN
   of them) that exists is moved to the event's group (sv_MoveToGroup); with none the event is freed, else stage 1
   and due in 5 minutes */

void he_AllocHerbGathering(AIJOB *e) {
  AIJOB *h = e;
  AICHAR *p;
  int i, any = 0;

  for (i = 0; i < h->herbsN; i++) {
    p = gm_FindChar(e->ids[i]);
    if (p != 0) {
      any |= 1;
      sv_MoveToGroup(0, 0, p->id, e);
    }
  }
  if (any == 0) {
    he_FreeEvent(e);
    return;
  }
  e->end = ai_Time;
  e->stage = 1;
  gm_AddTime(&e->end, 0, 5, 0);
}

/* 0x557e20, the run handler of the herb gathering event 20 (AIJOB.herbs*; allocated by he_AllocHerbGathering, which gathers the
   group). Outside the day hours of the season (gm_DayStartHours .. gm_DayEndHours) it waits 5 minutes, except when
   cancelled; without the event's character it is freed. Stage 1: the nearest building of type 0xb to the event's
   building (AIJOB.from, by the 3D distance of their objects; none: cancelled) becomes the field and the gatherers
   are sent there ("Kr\344uter"). Stage 2: once all are at its door, the next stage in 10 minutes. Stage 3: they are
   sent back to the room; none left: freed. Stage 4: once all are home they leave the group and the harvest
   ((9 + random 6) per gatherer, times 1 + the building's skill 0x1e (type kind ' ') or 0xb / 90, halved in season 3
   without the building's flag 0x2000) goes into the building's store object 0x2a (gm_FreeCapacity, sold to the
   own player by cm_SendExSellObject); the news 0x1802 + 0x1803 (or 0x1804 for nothing) goes to the character of
   kind 6 / 7 unless its master has flags1b4 bit 0. Stages -2 / -1 send the gatherers back and free the event */
void he_RunHerbGathering(AIJOB *e) {
  AIJOB *h = e;
  AIBLD *nearest;
  int season;
  char text[0x400], line[0x200];

  season = gm_ClockSeason(&ai_Time);
  nearest = 0;
  if (!(gm_DayEndHours[season] <= (float)ai_Time.hour ||
        (float)ai_Time.hour < gm_DayStartHours[season]) ||
      e->stage == -1 || e->stage == -2) {
    if (e->chr != 0xffff && e->netId != -1) {
      switch (e->stage) {
      case 1: {
        float best, d, dx, dy, dz;
        D3VECTOR4 pos, at;
        D3OBJECT *obj;
        AIBLD *b, *f;
        int i;

        b = gm_BuildQuery(1, 1, e->from);
        if (b != 0) {
          best = 1e8f;
          obj = b->object;
          d3_PointToWorld(obj, &obj->pos, &at.v);
          for (f = gm_BuildQuery(1, 5, 0xb); f != 0; f = gm_BuildNext()) {
            obj = f->object;
            d3_PointToWorld(obj, &obj->pos, &pos.v);
            dx = pos.x - at.x;
            dy = pos.y - at.y;
            dz = pos.z - at.z;
            d = (float)sqrt(dx * dx + dy * dy + dz * dz);
            if (d < best) {
              best = d;
              nearest = f;
            }
          }
        }
        if (nearest == 0) {
          e->stage = -1;
          return;
        }
        h->herbsField = nearest->id;
        for (i = 0; i < h->herbsN; i++) {
          if (gm_FindChar(e->ids[i]) != 0) {
            cm_SendChrStop(e->ids[i]);
            cm_SendChrGotoBuilding(e->ids[i], nearest->id, -1, 0, 0,
                                   "Kr\344uter");
          }
        }
        e->stage++;
        return;
      }
      case 2: {
        AIBLD *f;
        AICHAR *c;
        int i;

        f = gm_BuildQuery(1, 1, h->herbsField);
        if (f == 0) {
          e->stage = -1;
          return;
        }
        for (i = 0; i < h->herbsN; i++) {
          c = gm_FindChar(e->ids[i]);
          if (c != 0 && sv_IsAtDoor(c, f) == 0) {
            e->stage = 2;
            gm_AddTime(&e->end, 0, 5, 0);
            return;
          }
        }
        e->stage = 3;
        gm_AddTime(&e->end, 0, 10, 0);
        return;
      }
      case 3: {
        AIBLD *b;
        int i, any;

        any = 0;
        b = gm_BuildQuery(1, 1, e->from);
        if (b == 0) {
          e->stage = -1;
          return;
        }
        for (i = 0; i < h->herbsN; i++) {
          if (gm_FindChar(e->ids[i]) != 0) {
            any |= 1;
            cm_SendChrStop(e->ids[i]);
            cm_SendChrGotoBuilding(e->ids[i], b->id, h->herbsRoom, 0, 0,
                                   "Kr\344uter");
          }
        }
        if (any == 0)
          break;
        e->stage = 4;
        gm_AddTime(&e->end, 0, 5, 0);
        return;
      }
      case 4: {
        AIBLD *b;
        AIOBJ *o;
        AICHAR *c, *m;
        int i, amount, got;

        b = gm_BuildQuery(1, 1, e->from);
        if (b == 0)
          break;
        for (i = 0; i < h->herbsN; i++) {
          c = gm_FindChar(e->ids[i]);
          if (c != 0 && sv_IsAtDoor(c, b) == 0) {
            e->stage = 4;
            gm_AddTime(&e->end, 0, 5, 0);
            return;
          }
        }
        for (i = 0; i < h->herbsN; i++) {
          c = gm_FindChar(e->ids[i]);
          if (c != 0)
            sv_MoveToGroup(0, 0, c->id, 0);
        }
        o = gm_Query(b->objList, 2, 6, 0, 0x2a);
        if (o == 0)
          break;
        season = gm_ClockSeason(&ai_Time);
        if (ai_BTypes[b->type].kind == ' ')
          amount = (int)((util_Random(6) + 9) * h->herbsN *
                         (gm_BuildingSkill(b, 0x1e, 1) * (1.0 / 90) + 1.0));
        else
          amount = (int)((util_Random(6) + 9) * h->herbsN *
                         (gm_BuildingSkill(b, 0xb, 1) * (1.0 / 90) + 1.0));
        if (season == 3 && (b->flags5aw & 0x2000) == 0)
          amount = (int)(amount * 0.5);
        got = gm_FreeCapacity(o, h->herbsGood, amount);
        if (h->herbsGood == 0)
          break;
        m = gm_FindCharacterByMaster(b);
        if (got != 0) {
          cm_SendExSellObject(o->objId, -1, h->herbsGood, got, ai_OwnPlayer, 0);
          txt_Format(text, 0x1802, 0x17fd, b);
          txt_Format(line, 0x1803, got, h->herbsGood * 2 + 0x9a8);
          strcat(text, line);
          if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
              (m == 0 || (m->flags1b4 & 1) == 0))
            he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                                   b->id, h->herbsRoom, 0, 0);
          break;
        }
        txt_Format(text, 0x1804, 0x17fd, b);
        if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
            (m == 0 || (m->flags1b4 & 1) == 0))
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                                 b->id, h->herbsRoom, 0, 0);
        break;
      }
      case -2:
      case -1: {
        AIBLD *b;
        int i;

        b = gm_BuildQuery(1, 1, e->from);
        if (b != 0) {
          for (i = 0; i < h->herbsN; i++) {
            if (gm_FindChar(e->ids[i]) != 0) {
              cm_SendChrStop(e->ids[i]);
              cm_SendChrGotoBuilding(e->ids[i], b->id, h->herbsRoom, 0, 0,
                                     "Kr\344uter");
            }
          }
        }
        break;
      }
      default:
        return;
      }
    }
    he_FreeEvent(e);
    return;
  }
  gm_AddTime(&e->end, 0, 5, 0);
}
/* 0x5584d0, the allocation handler of the animal hunt event 21 (AIJOB.hunt*): every hunter id (AIJOB.ids, AIJOB.huntN of
   them) that exists is moved to the event's group (sv_MoveToGroup); the due clock starts as the start clock, one
   minute later (the stage is kept) */

void he_AllocAnimalHunt(AIJOB *e) {
  AIJOB *h = e;
  AICHAR *p;
  int i;

  for (i = 0; i < h->huntN; i++) {
    p = gm_FindChar(e->ids[i]);
    if (p != 0)
      sv_MoveToGroup(0, 0, p->id, e);
  }
  e->end = e->start;
  gm_AddTime(&e->end, 0, 1, 0);
}
/* 0x558550, the run handler of the animal hunt event 21 (AIJOB.hunt*; allocated by he_AllocAnimalHunt, which gathers the
   group). Stage 0: every hunter with a building (AICHAR.bld) is sent to its room there ("Getier"); the catch is due
   in 2 units + random 30. Stage 1, once due: with the event's building (AIJOB.from; gone: cancelled) its object
   0xdd (else its main object) is the quick jump and its store object 0x2a (none: cancelled) gets the catch,
   (5 + random 5) times 1 + the building's skill 0xb / 100, sold to the own player (cm_SendExSellObject); the news
   0x1809 + 0x180a (0x1805, the building) goes to the event's character of kind 6 / 7 unless its master has flags1b4
   bit 0. The original passes the quick jump backwards: -1 with the object, the object's objId without one (it
   reads address 2). Then the stage is -1. Stages -2 / -1 release the hunters from the group and free the event */
void he_RunAnimalHunt(AIJOB *e) {
  AIJOB *h = e;
  AIBLD *b;
  AIOBJ *q, *o;
  AICHAR *c, *m;
  double rate;
  int i, amount;
  char text[0x100], line[0x100];

  switch (e->stage) {
  case 0:
    for (i = 0; i < h->huntN; i++) {
      c = gm_FindChar(e->ids[i]);
      if (c != 0 && c->bld != 0) {
        cm_SendChrStop(e->ids[i]);
        cm_SendChrGotoBuilding(e->ids[i], c->bld->id, h->huntRoom, 0, 0,
                               "Getier");
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 2, util_Random(0x1e), 0);
    e->stage++;
    return;
  case 1:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0) {
      e->stage = -1;
      return;
    }
    q = gm_Query(b->objList, 1, 0, 0xdd);
    if (q == 0)
      q = gm_BuildingMainObject(b);
    o = gm_Query(b->objList, 2, 6, 0, 0x2a);
    if (o != 0) {
      m = gm_FindCharacterByMaster(b);
      rate = gm_BuildingSkill(b, 0xb, 1) * 0.01 + 1.0;
      amount = (int)((util_Random(5) + 5) * rate);
      cm_SendExSellObject(o->objId, -1, h->huntGood, amount, ai_OwnPlayer, 0);
      txt_Format(text, 0x1809, 0x1805, b);
      txt_Format(line, 0x180a, amount, h->huntGood * 2 + 0x9a8);
      strcat(text, line);
      if ((ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) &&
          (m == 0 || (m->flags1b4 & 1) == 0)) {
        if (q != 0) {
          he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                                 b->id, -1, 0, 0);
          e->stage = -1;
          return;
        }
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5ec,
                               b->id, q->objId, 0, 0);
      }
    }
    e->stage = -1;
    return;
  case -2:
  case -1:
    for (i = 0; i < h->huntN; i++) {
      c = gm_FindChar(e->ids[i]);
      if (c != 0)
        sv_MoveToGroup(c->bld, 0, c->id, 0);
    }
    he_FreeEvent(e);
    return;
  }
}
/* 0x5588c0, the allocation handler of the study event 22 (AIJOB.study*): without the character (or while it is on a job
   of kind 0x16) or the event's building (AIJOB.from) the event is freed; else the start and due clocks are now, the
   character joins the event's group at the building in its room (the object of type 1 with the objId AIJOB.studyRoom,
   if given; sv_MoveToGroup), the clock60 is now, the event is due in 30 minutes and ends at the latest 6 units
   after that; a latest end past midnight (its hour below 6) gets the hour - the due hour + 29 */
void he_AllocStudy(AIJOB *e) {
  AIJOB *s = e;
  AICHAR *c;
  AIBLD *b;
  AIOBJ *room = 0;

  c = gm_FindChar(s->studyChr);
  if (c == 0 || (c->job != 0 && c->job->kind == 0x16)) {
    he_FreeEvent(e);
    return;
  }
  b = gm_BuildQuery(1, 1, e->from);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  if (s->studyRoom != -1)
    room = gm_Query(b->objList, 2, 6, 1, s->studyRoom);
  e->end = ai_Time;
  e->start = ai_Time;
  if (room != 0)
    sv_MoveToGroup(b, room, c->id, e);
  else
    sv_MoveToGroup(b, 0, c->id, e);
  e->clock60 = ai_Time;
  gm_AddTime(&e->end, 0, 0x1e, 0);
  s->studyUntil = e->end;
  gm_AddTime(&s->studyUntil, 6, 0, 0);
  if (s->studyUntil.hour < 6)
    s->studyUntil.hour = s->studyUntil.hour - e->end.hour + 0x1d;
}
/* 0x558a40, the run handler of the study event 22 (AIJOB.study*; allocated by he_AllocStudy). Stage 0, every 30
   minutes: without the character or once its skill (AICHAR.skills[AIJOB.studySkill]) is 252 the next stage; without
   the event's building (AIJOB.from) the event is freed. Else the working minutes since the clock60
   (gm_WorkMinutesBetween; up to the latest end, which also ends the stage) give the gain
   minutes / 30 * 8 * (1 + the building's skill 0xc / 100), divided by 1 + the skill / 252 and capped at 252, sent as
   a field delta of the skill byte. Stage 1: unless the building's master has flags1b4 bit 0, the news 0x1bc8 (the
   character, the building) goes to the event's character with the quick jump to the building's room (object 0x60
   of a type kind 4, 0x145 of kind 0x13, else gm_GetGebaeudeHauptraum; none: no news) and "_NACHRICHTEN_HS_81";
   the character leaves the group and the event is freed. Stages -2 / -1 free the event */
void he_RunStudy(AIJOB *e) {
  AIJOB *s = e;
  AICHAR *c;
  AIBLD *b;
  AIOBJ *q;
  AICHAR *m;
  AIBTYPE *bt;
  float mins;
  unsigned char gain;
  unsigned char *skill;
  char text[0x200];

  switch (e->stage) {
  case 0:
    c = gm_FindChar(s->studyChr);
    if (c != 0 && c->skills[s->studySkill] < 252.0f) {
      b = gm_BuildQuery(1, 1, e->from);
      if (b == 0)
        break;
      if (gm_CompareTime(&ai_Time, &s->studyUntil) < 0)
        mins = (float)gm_WorkMinutesBetween(&e->clock60, &ai_Time, b);
      else {
        mins = (float)gm_WorkMinutesBetween(&e->clock60, &s->studyUntil, b);
        e->stage = 1;
      }
      gain = (unsigned char)((gm_BuildingSkill(b, 0xc, 1) * 0.01 + 1.0) *
                             ((mins / 30.0) * 8.0));
      skill = &c->skills[s->studySkill];
      gain = (unsigned char)(gain / (*skill / 252.0f + 1.0));
      if (gain + *skill > 252.0f)
        gain = (unsigned char)(252.0f - *skill);
      cm_BeginFieldBlock(c, c->netId);
      cm_AddFieldValues(
          1, 1, (char *)&c->skills[s->studySkill] - cm_FieldObject, &gain);
      cm_SendFieldDeltas();
      e->end = ai_Time;
      e->clock60 = ai_Time;
      gm_AddTime(&e->end, 0, 0x1e, 0);
      return;
    }
    e->stage = 1;
    return;
  case 1:
    c = gm_FindChar(s->studyChr);
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0 || c == 0)
      break;
    m = gm_FindCharacterByMaster(b);
    if (m == 0 || (m->flags1b4 & 1) == 0) {
      q = 0;
      bt = &ai_BTypes[b->type];
      if (bt->kind == 4)
        q = gm_Query(b->objList, 1, 0, 0x60);
      else if (bt->kind == 0x13)
        q = gm_Query(b->objList, 1, 0, 0x145);
      if (q == 0)
        q = gm_GetGebaeudeHauptraum(b);
      if (q != 0) {
        txt_Format(text, 0x1bc8, c->id, b);
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, e->from, text, 0, 0x5f2,
                               b->id, q->objId, ch_EmptyName,
                               "_NACHRICHTEN_HS_81");
      }
    }
    sv_MoveToGroup(b, 0, c->id, 0);
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x558de0, the allocation handler of the event type 0x17: its due clock starts as the event's own clock (AIJOB.ev17Due) */

void he_AllocEvent17(AIJOB *e) {
  AIJOB *v = e;

  e->end = v->ev17Due;
}
/* 0x558e10, the run handler of the event type 0x17: state 3 sets its due clock to now + 1 minute, state 9 frees the record */

void he_RunEvent17(AIJOB *e) {

  switch (e->stage) {
  case 3:
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 1, 0);
    break;
  case 9:
    he_FreeEvent(e);
    break;
  }
}
/* 0x558e70, the allocation handler of the sabotage event 25 ("SABOTAGE"): the due clock is now + 1 minute; with no
   building (AIJOB.from -1) the first inn (kind 0x16, else 0xf) is taken; the saboteur is -1 and the spawn request's
   slot goes to AIJOB.sabotageSlot */

void he_AllocSabotage(AIJOB *e) {
  AIJOB *s = e;
  AIBLD *b;

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  if (e->from == -1) {
    b = gm_BuildQuery(1, 5, 0x16);
    if (b == 0)
      b = gm_BuildQuery(1, 5, 0xf);
    if (b != 0)
      e->from = b->id;
  }
  s->sabotageSaboteur = -1;
  s->sabotageSlot =
      cm_SendSpawnCharacter(0, e->from, -1, 0, 1, 0x174, "SABOTAGE");
}

int ord_DispatchOrder(int id, struct AICHAR *c, ORDMSG *m);

/* 0x558f10, the run handler of the sabotage event 25 (AIJOB.sabotage*; allocated by he_AllocSabotage, which asks for the
   saboteur, "SABOTAGE"). Every stage waits while a cm request is pending (AIJOB.sabotageSlot). Stage 0: the spawned
   saboteur (none: cancelled) is paid for by the event's character (its player record's spyPaid, a money move to the
   own player) and joins the event's group. 1: it walks to the target building (gone: cancelled). 2: once arrived
   (its scene character has no actions left; else 4 more minutes) the next stage. 3: a watch event may see it
   (he_DetectAttack, range 4000): then the owner accuses the event's character (gv_Accuse 0x18) and the stage is 7;
   else it picks something up ("spezial/einhaendig_vom_boden_nehmen") and walks back. 4, once due: a random
   1.0 + gm_Mix (attacker, owner, 2) of at least 1 against an owner without the item 0x2c0 succeeds: the news 0x1735
   to the attacker, 0x1736 ("_NACHRICHTEN_HS_18") to an owner of kind 6 / 7 or a relation loss of 25, the accusation,
   the news 0x1737 to the other players, the explosions in 10 minutes; an owner with the item 0x2c0 catches it (the
   attacker loses money: the news 0x1013 / 0x1011 "_NACHRICHTEN_HS_17"), else it fails (the news 0x1738 / 0x1739,
   the accusation) and the event is cancelled. 5: the first blast posts the explosion message 0x4f (strength
   20 + random 16 - 3 * the type's level) and plays "Explosion"; every blast up to the first one (blasts < 1) shows
   smoke, earth and an explosion (3 times bigger for the first in the town scene) at a random dummy object of the
   building ("dummy_TUER" / "dummy_FAHNE" / "dummy_RAUCH_0") and the next follows in random 2 minutes; after it the
   stage is 6. 6: back home (else 4 more minutes) it is cancelled. 7: the accusation answered, the proof goes to the
   watch (cm_SendProofExecuted), the stage is 8 in 10 minutes. 8: while the watch event still holds it 6 more
   minutes, then the saboteur walks home (stage 6). Stages -2 / -1 kill the saboteur and free the event */
void he_RunSabotage(AIJOB *e) {
  AIJOB *x = e;
  AIBLD *b;
  AICHAR *c;
  char text[0x400];

  if (x->sabotageSlot != -1 && cm_GetSlotState(x->sabotageSlot) == 0)
    return;
  switch (e->stage) {
  case 0: {
    AIFIN *fin;

    if (x->sabotageSlot != -1 && cm_GetSlotState(x->sabotageSlot) == 0)
      return;
    c = (AICHAR *)cm_GetSlotValue(x->sabotageSlot);
    if (c != 0) {
      fin = gm_PlayerRecord(&ai_Chars[e->chr]);
      if (fin != 0)
        fin->spyPaid += x->sabotageFee;
      x->sabotageSaboteur = c->netId;
      sv_MoveToGroup(0, 0, c->id, e);
      cm_SendMoveGoodsUnchecked(-1, ai_Chars[e->chr].netId, ai_OwnPlayer,
                                x->sabotageFee);
      e->stage++;
      x->sabotageSlot = -1;
      return;
    }
    x->sabotageSaboteur = -1;
    e->stage = -1;
    return;
  }
  case 1:
    b = gm_BuildQuery(1, 1, x->sabotageTarget);
    if (b == 0) {
      e->stage = -1;
      return;
    }
    x->sabotageSlot = cm_SendChrGotoBuilding(x->sabotageSaboteur, b->id, -1, 0,
                                             1, "Sabotage");
    e->stage++;
    break;
  case 2:
    x->sabotageSlot = -1;
    c = gm_FindChar(x->sabotageSaboteur);
    if (c == 0) {
      e->stage = -1;
      return;
    }
    if (c->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      e->stage = 2;
      return;
    }
    e->stage++;
    return;
  case 3: {
    HEDETECT d;

    b = gm_BuildQuery(1, 1, x->sabotageTarget);
    if (b == 0 || b->owner == 0xffff) {
      e->stage = -1;
      return;
    }
    d.bld = b;
    d.range = 4000.0f;
    d.ev = e;
    d.found = 0;
    if (he_DetectAttack((intptr_t)&d) != 0) {
      x->sabotageSlot = gv_Accuse(0x18, 1, ai_Chars[e->chr].netId,
                                  ai_Chars[b->owner].netId, x->sabotageTarget);
      x->sabotageWatch = d.found->id;
      e->stage = 7;
      e->end = ai_Time;
      return;
    }
    cm_SendChrAnim(x->sabotageSaboteur, "spezial/einhaendig_vom_boden_nehmen",
                   1);
    cm_SendChrGotoBuilding(x->sabotageSaboteur, e->from, -1, 0, 1, "Sabotage");
    e->stage++;
    break;
  }
  case 7: {
    AIJOB *w;
    CRIME *cr;

    if (x->sabotageSlot != -1 && cm_GetSlotState(x->sabotageSlot) == 0)
      return;
    b = gm_BuildQuery(1, 1, x->sabotageTarget);
    w = he_FindEvent(1, 1, x->sabotageWatch);
    if (b == 0 || w == 0 || w->patrolWait != e->id || x->sabotageSlot == -1) {
      e->stage = -1;
      return;
    }
    c = gm_FindChar(x->sabotageWatch);
    cr = (CRIME *)cm_GetSlotValue(x->sabotageSlot);
    if (cr != 0 && c != 0)
      cm_SendProofExecuted(cr->id, c->netId);
    e->stage = 8;
    gm_AddTime(&e->end, 0, 10, 0);
    return;
  }
  case 8: {
    AIJOB *w;

    w = he_FindEvent(1, 1, x->sabotageWatch);
    if (w == 0) {
      e->stage = -1;
      return;
    }
    if (w->patrolWait == e->id) {
      gm_AddTime(&e->end, 0, 6, 0);
      return;
    }
    cm_SendChrGotoBuilding(x->sabotageSaboteur, e->from, -1, 0, 1, "Sabotage");
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 4, 0);
    e->stage = 6;
    break;
  }
  case 4: {
    float chance;
    AICHAR *me, *owner;
    int i;
    int ok;

    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    x->sabotageBlasts = 0;
    b = gm_BuildQuery(1, 1, x->sabotageTarget);
    if (b == 0 || b->owner == 0xffff) {
      e->stage = -1;
      return;
    }
    owner = &ai_Chars[b->owner];
    me = &ai_Chars[e->chr];
    chance = gm_Mix(me, owner, 2);
    ok = 0;
    if (util_RandomF() + chance >= 1.0f && ai_InventoryHas(owner, 0x2c0) == 0) {
      ok = 1;
      txt_Format(text, 0x1735, owner->id, b);
      he_MessageBoxQuickjump(me->netId, -1, text, 0, 0x5f0, b->id, -1, 0, 0);
      if (b->owner != 0xffff) {
        if (owner->kind == 6 || owner->kind == 7) {
          txt_Format(text, 0x1736, b);
          he_MessageBoxQuickjump(owner->netId, -1, text, 0, 0x5f0, b->id, -1, 0,
                                 "_NACHRICHTEN_HS_18");
        } else
          cm_SendRelations(me->netId, owner->netId, -0x19, 1);
        gv_Accuse(0x18, 1, ai_Chars[e->chr].netId, ai_Chars[b->owner].netId,
                  b->id);
      }
      for (i = 0; i < 768; i++) {
        if ((ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7) &&
            ai_Chars[i].netId != owner->netId &&
            ai_Chars[i].netId != me->netId) {
          txt_Format(text, 0x1737, owner->id, b);
          he_MessageBoxQuickjump(ai_Chars[i].netId, -1, text, 0, 0x5f0, b->id,
                                 -1, 0, 0);
        }
      }
    }
    if (!ok) {
      owner = &ai_Chars[b->owner];
      me = &ai_Chars[e->chr];
      if (ai_InventoryHas(owner, 0x2c0) != 0) {
        gm_SendMoneyDelta(me->netId, -1);
        if (me->kind == 6 || me->kind == 7) {
          txt_Format(text, 0x1013, owner->id, b);
          he_ShowNews(me->netId, -1, text, 0, 0x5fa, 0);
        }
        if (owner->kind == 6 || owner->kind == 7) {
          txt_Format(text, 0x1011, b);
          he_ShowNews(owner->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_HS_17");
        }
        e->stage++;
        return;
      }
      txt_Format(text, 0x1738, b->owner, b);
      he_MessageBoxQuickjump(me->netId, -1, text, 0, 0x5f0, b->id, -1, 0, 0);
      if (b->owner != 0xffff) {
        txt_Format(text, 0x1739, b);
        he_MessageBoxQuickjump(owner->netId, -1, text, 0, 0x5f0, b->id, -1, 0,
                               0);
        gv_Accuse(0x18, 1, ai_Chars[e->chr].netId, ai_Chars[b->owner].netId,
                  b->id);
        e->stage = -1;
        break;
      }
      e->stage = -1;
      return;
    }
    e->stage++;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    return;
  }
  case 5:
    if (x->sabotageBlasts < 1) {
      int scene;
      D3COLOR col;
      /* @original the pad word is an int: its 0 stores use the cached zero register */
      struct {
        union {
          struct {
            float x, y, z;
          };
          D3VECTOR v;
        };
        int w;
      } a = {-243.0f, -90.0f, 190.0f, 0};
      struct {
        union {
          struct {
            float x, y, z;
          };
          D3VECTOR v;
        };
        int w;
      } dir = {-50.0f, 0, 38.0f, 0};
      float scale = 1.0f;
      char dummies[3][0x40] = {"dummy_TUER", "dummy_FAHNE", "dummy_RAUCH_0"};

      D3OBJECT *o;
      AIBTYPE *bt;
      struct SBSAMPLE *snd;

      scene = d3_CurrentScene;
      b = gm_BuildQuery(1, 1, x->sabotageTarget);
      if (b == 0) {
        e->stage = -1;
        return;
      }
      if (x->sabotageBlasts == 0 && d3_CurrentScene == 0) {
        snd = sb_GetSample(0, "Explosion");
        if (snd != 0)
          d3snd_PlayAt(snd, b->object, 0x6b, 12200.0f);
        scale = 3.0f;
      }
      d3if_SelectScene(0, 1);
      o = b->object;
      if (o != 0) {
        if (x->sabotageBlasts == 0) {
          AIMSG msg;

          msg.type = 0x4f;
          msg.fromId = -1;
          msg.flags = 2;
          msg.extraFlag = 0;
          bt = &ai_BTypes[b->type];
          msg.to = ai_Chars[e->chr].netId;
          msg.time = ai_Time;
          msg.arg[0] = b->id;
          msg.arg[1] = util_Random(0x10) - bt->cap247 * 3 + 0x14;
          cm_SendLongMessage(&msg);
        } else {
          o = d3_FindObject(b->object, 0x100, 0, dummies[util_Random(3)]);
          if (o != 0)
            d3_PointToWorld(o, &o->pos, &a.v);
          else
            o = d3_FindObject(b->object, 0x100, 0, "dummy_TUER");
        }
        if (o != 0 && scene == 0) {
          d3_PointToWorld(o, &o->pos, &a.v);
          a.x = util_Random(0x40) + a.x - 32.0f;
          a.y = util_Random(0x40) + a.y;
          a.z = util_Random(0x40) + a.z - 32.0f;
          col.a = 0x3f;
          col.r = 0xc0;
          col.g = 0xc0;
          col.b = 0xc0;
          d3t_CreateSmoke((void *)scene, &a.v, 0x1e, 15.0f, 50.0f, 100.0f,
                          150.0f, 140.0f, 35.0f, &dir.v, 0x190, 6, col);
          d3t_CreateEarth((void *)scene, &a.v, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f,
                          -3.0f, 4.0f, 7.0f, 8.0f, col);
          d3t_CreateExplosion((void *)scene, &a.v, (int)(scale * 40.0f),
                              scale * 140.0f, scale * 100.0f, 20.0f, 60.0f,
                              0x50);
        }
      }
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, util_Random(2), 0);
      x->sabotageBlasts++;
      d3if_SelectScene(scene, 1);
      return;
    }
    e->stage = 6;
    return;
  case 6:
    c = gm_FindChar(x->sabotageSaboteur);
    if (c == 0) {
      e->stage = -1;
      return;
    }
    if (c->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      e->stage = 6;
      return;
    }
    e->stage = -1;
    return;
  case -2:
  case -1:
    if (x->sabotageSaboteur != -1)
      cm_SendKillCharacter(x->sabotageSaboteur, 1);
    he_FreeEvent(e);
    return;
  }
}
/* 0x559d20, the allocation handler of the spying event 24 (AIJOB.spying*; run handler 0x55a030). Not yet started (opts
   4): nothing. Without the character spied on, or when another spying event of the same character on it exists,
   the event is ended (cm_SendExSetHE -1). The walk over the buildings starts at random with a random stride, the
   event is due in a minute; the spying events with a spy are counted. Without the target building one of the
   gypsyFilter kinds is picked (ai_PickActionBuilding, up to 100.0; none: ended). The end is 3 days + AIJOB.spyingDays
   from now (4 when order 0x26 of the event's character answers 2). Inside the cm group "Spionage": for a player's
   event, a victim of kind 6 / 7 or fewer than 8 spies a spy is spawned at the target ("SPIONAGE") and the event
   started (cm_SendExSetHE 0), else it is due at the end (cm_SendExSetHE 4) */
void he_AllocSpying(AIJOB *e) {
  AIJOB *s = e;
  AIBLD *tgt;
  int spawn = 0, spies = 0;
  AICHAR *victim, *me;
  AIJOB *o;
  ORDMSG ord;

  if ((e->opts & 4) != 0)
    return;
  s->spyingSpy = -1;
  victim = gm_FindChar(s->spyingVictim);
  if (victim == 0) {
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
  s->spyingCursor = util_Random(0x100);
  s->spyingStep = ai_RandomStrides[util_Random(0x10)];
  s->spyingB8 = 0;
  s->spyingAt = -1;
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 1, 0);
  for (o = he_FindEvent(1, 0, 0x18); o != 0; o = he_NextEvent()) {
    if (e->chr == o->chr && o->id != e->id &&
        o->spyingVictim == s->spyingVictim) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (o->spyingSpy != -1)
      spies++;
  }
  gm_FindById(&tgt, 0, 0, s->spyingTarget);
  if (tgt == 0) {
    ai_PickActionBuilding(&ai_Chars[e->chr], 6, gypsyFilter, 0, 100.0f,
                          &s->spyingTarget);
    gm_FindById(&tgt, 0, 0, s->spyingTarget);
    if (tgt == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
  }
  memset(&ord, 0, sizeof(ord));
  ord.kind = 1;
  me = &ai_Chars[e->chr];
  e->end = ai_Time;
  s->spyingUntil = ai_Time;
  if (ord_DispatchOrder(0x26, me, &ord) == 2)
    gm_AddTime(&s->spyingUntil, (s->spyingDays + 4) * 24, 0, 0);
  else
    gm_AddTime(&s->spyingUntil, (s->spyingDays + 3) * 24, 0, 0);
  if (me->kind == 6 || victim->kind == 6 || victim->kind == 7)
    spawn = 1;
  else if (spies < 8)
    spawn = 1;
  cm_BeginGroup("Spionage");
  if (spawn != 0) {
    s->spyingSpy =
        cm_SendSpawnCharacter(0x11, tgt->id, -1, 0, 0, 0, "SPIONAGE");
    e->exSlot = cm_SendExSetHE(0, e);
  } else {
    e->end = s->spyingUntil;
    e->exSlot = cm_SendExSetHE(4, e);
  }
  cm_EndGroup("Spionage");
}
/* 0x55a030, the run handler of the spying event 24 (AIJOB.spying*; allocated by he_AllocSpying). Not yet started (opts
   4) or while a request is pending: nothing. Stage 0: the spawned spy is paid for by the event's character (its
   player record's spyPaid, a money move to the own player), joins the group and the event starts (stage 1); no spy:
   due at the end (stage 4). 1: the walk over the 0x100 buildings finds the next of the kinds 0x1a7fcc3a6 that is
   not the target ("Spionage: next target = %G"), the spy is sent there (stage 2; none or no spy: ended). 2: once at
   its door, before the end the next round (stage 1), at the end the spy goes to the target (stage 3). 3: there,
   the event's character gets the news 0x1734 (the victim) and the event ends. 4: ended. Stages -2 / -1: a started
   event's spy is stopped and killed, the event freed */
void he_RunSpying(AIJOB *e) {
  char text[0x400];
  AIJOB *s = e;
  AIBLD *bld = 0;
  AICHAR *c;
  AIFIN *fin;
  unsigned lo, hi;
  int n, idx;
  AIBTYPE *bt;

  if (e->stage == -1 || e->stage == -2) {
    if ((e->opts & 2) != 0 && s->spyingSpy != -1) {
      c = gm_FindChar(s->spyingSpy);
      if (c != 0) {
        cm_SendChrStop(c->netId);
        cm_SendKillCharacter(c->netId, 1);
      }
    }
    he_FreeEvent(e);
    return;
  }
  if ((e->opts & 4) != 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  switch (e->stage) {
  case 0:
    if (s->spyingSpy != -1 && cm_GetSlotState(s->spyingSpy) == 0)
      return;
    c = (AICHAR *)cm_GetSlotValue(s->spyingSpy);
    if (c != 0) {
      fin = gm_PlayerRecord(&ai_Chars[e->chr]);
      if (fin != 0)
        fin->spyPaid += s->spyingFee;
      s->spyingSpy = c->netId;
      cm_SendMoveGoodsUnchecked(-1, ai_Chars[e->chr].netId, ai_OwnPlayer,
                                s->spyingFee);
      sv_MoveToGroup(0, 0, c->id, e);
      e->end = ai_Time;
      e->exSlot = cm_SendExSetHE(1, e);
      return;
    }
    s->spyingSpy = -1;
    e->end = s->spyingUntil;
    e->exSlot = cm_SendExSetHE(4, e);
    return;
  case 1:
    idx = s->spyingCursor;
    n = 0x100;
    do {
      bld = &ai_Blds[idx];
      bt = &ai_BTypes[bld->type];
      hi = 0;
      lo = 0;
      if (bt->kind > 0x1f)
        hi = 1 << (bt->kind - 0x20);
      else
        lo = 1 << bt->kind;
      if (((lo & 0xa7fcc3a6) != 0 || (hi & 1) != 0) &&
          bld->id != s->spyingTarget)
        break;
      bld = 0;
      n--;
      idx = (idx + s->spyingStep) % 0x100;
    } while (n != 0);
    s->spyingCursor = (s->spyingStep + idx) % 0x100;
    if (bld == 0) {
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    txt_Format(text, (intptr_t)"Spionage: next target = %G", bld);
    c = gm_FindChar(s->spyingSpy);
    if (c != 0) {
      cm_SendChrStop(c->netId);
      cm_SendChrGotoBuilding(c->netId, bld->id, -1, 0, 1, "Spionage");
      gm_AddTime(&e->end, 0, 5, 0);
      s->spyingAt = bld->id;
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 2:
    gm_FindById(&bld, 0, 0, s->spyingAt);
    gm_AddTime(&e->end, 0, 5, 0);
    if (bld == 0) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    c = gm_FindChar(s->spyingSpy);
    if (c == 0) {
      gm_AddTime(&e->end, 0, 1, 0);
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (sv_IsAtDoor(c, bld) == 0) {
      e->stage = 2;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(2, e);
      return;
    }
    gm_FindById(&bld, 0, 0, s->spyingTarget);
    if (bld == 0 || bld->owner == 0xffff) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    if (gm_CompareTime(&s->spyingUntil, &ai_Time) == -1) {
      cm_SendChrStop(c->netId);
      cm_SendChrGotoBuilding(c->netId, bld->id, -1, 0, 1, "Spionage");
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    e->exSlot = cm_SendExSetHE(1, e);
    return;
  case 3:
    gm_AddTime(&e->end, 0, 5, 0);
    gm_FindById(&bld, 0, 0, s->spyingTarget);
    if (bld == 0 || bld->owner == 0xffff) {
      e->exSlot = cm_SendExSetHE(-1, e);
      return;
    }
    c = gm_FindChar(s->spyingSpy);
    if (c != 0 && sv_IsAtDoor(c, bld) == 0) {
      e->stage = 3;
      gm_AddTime(&e->end, 0, 5, 0);
      e->exSlot = cm_SendExSetHE(3, e);
      return;
    }
    c = gm_FindChar(s->spyingVictim);
    if (c != 0) {
      txt_Format(text, 0x1734, c->id);
      he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5fa, 0);
    }
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  case 4:
    gm_AddTime(&e->end, 0, 1, 0);
    e->exSlot = cm_SendExSetHE(-1, e);
    return;
  }
}

/* 0x55a5f0, the allocation handler of the brawl event 26 (AIJOB.brawl*, "PRUEGEL"; run handler he_RunBrawl): due now;
   without a hiring building (AIJOB.from -1) the first building of the kind 0x16, else 0xf, is taken; the thug is
   spawned there (cm_SendSpawnCharacter, "PRUEGEL"; its slot kept, no thug yet), and the building it goes to is
   the victim's home, else the victim's first building, else one of the gypsyFilter kinds the event's character
   picks (ai_PickActionBuilding, up to 100.0); none at all: the original reads the id through a null building */
void he_AllocBrawl(AIJOB *e) {
  AIJOB *br = e;
  AICHAR *victim;
  AIBLD *b, *home;
  int at;

  gm_FindChar(br->brawlVictim);
  e->end = ai_Time;
  if (e->from == -1) {
    b = gm_BuildQuery(1, 5, 0x16);
    if (b == 0)
      b = gm_BuildQuery(1, 5, 0xf);
    if (b != 0)
      e->from = b->id;
  }
  br->brawlThug = -1;
  br->brawlSlot =
      cm_SendSpawnCharacter(0x11, e->from, -1, 0, 2, 0x154, "PRUEGEL");
  victim = gm_FindChar(br->brawlVictim);
  if (victim->bld2 != 0)
    home = victim->bld2;
  else
    home = gm_BuildQuery(1, 4, victim->id);
  if (home == 0) {
    if (ai_PickActionBuilding(&ai_Chars[e->chr], 6, gypsyFilter, (int)home,
                              100.0f, &at) != 0)
      home = gm_BuildQuery(1, 1, at);
  }
  br->brawlMeet = home->id;
}

/* 0x55a730, the run handler of the brawl event 26 (AIJOB.brawl*, "Pr\xfcgel"; allocated by he_AllocBrawl). Once
   started, an event without its thug is cancelled. Stage 0: the spawn answered (none: cancelled), the thug is paid
   for by the event's character (its player record's spyPaid, a money move to the own player) and joins the event's
   group. 1: it walks to the meeting building (gone: stage 4). 2: once arrived (no actions left; else 4 more
   minutes) stage 7. 7: a watch event may see it (he_DetectAttack, range 4000): the victim accuses the event's
   character (gv_Accuse 0x15) and the stage is 8; else stage 4. 8: the accusation answered, the proof goes to the
   watch (cm_SendProofExecuted), stage 9 in 10 minutes. 9: while the watch event still holds it 6 more minutes,
   then the thug walks home (stage 5). 3: the thug walks home. 4, once due: the brawl. A victim with the item 0x2c0
   costs the attacker (the news 0x1012 / 0x1010 "_NACHRICHTEN_HS_17"), one with 0x17c only tells the attacker
   (0xff3); else ai_BrawlWin decides: a win tells both (0x173b / 0x173a) and the victim pays (2 with the item
   0x2b4, else 1 less), a loss tells both (0x173d / 0x173c); then the accusation (gv_Accuse 0x15) and, for a
   victim not a player, a relation loss of 25. 5: back home (else 4 more minutes) it is cancelled. Stages -2 / -1
   kill the thug and free the event */
void he_RunBrawl(AIJOB *e) {
  AIJOB *br = e;
  AIBLD *b;
  AICHAR *c, *me, *victim;
  int won, out;
  char text[0x400];

  if (e->stage > 0 && (br->brawlThug == 0 || br->brawlThug == -1))
    e->stage = -2;
  switch (e->stage) {
  case 0: {
    AIFIN *fin;

    if (br->brawlSlot != -1 && cm_GetSlotState(br->brawlSlot) == 0)
      return;
    c = (AICHAR *)cm_GetSlotValue(br->brawlSlot);
    if (c != 0) {
      fin = gm_PlayerRecord(&ai_Chars[e->chr]);
      if (fin != 0)
        fin->spyPaid += br->brawlFee;
      br->brawlThug = c->netId;
      cm_SendMoveGoodsUnchecked(-1, ai_Chars[e->chr].netId, ai_OwnPlayer,
                                br->brawlFee);
      sv_MoveToGroup(0, 0, c->id, e);
      e->stage++;
      br->brawlSlot = -1;
      return;
    }
    e->stage = -1;
    br->brawlSlot = -1;
    return;
  }
  case 1:
    b = gm_BuildQuery(1, 1, br->brawlMeet);
    if (b != 0) {
      br->brawlSlot =
          cm_SendChrGotoBuilding(br->brawlThug, b->id, -1, 0, 1, "Pr\xfcgel");
      e->stage++;
      break;
    }
    e->stage = 4;
    break;
  case 2:
    br->brawlSlot = -1;
    c = gm_FindChar(br->brawlThug);
    if (c == 0) {
      e->stage = -1;
      return;
    }
    if (c->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      e->stage = 2;
      return;
    }
    e->stage = 7;
    return;
  case 7: {
    HEDETECT d;

    b = gm_BuildQuery(1, 1, br->brawlMeet);
    victim = gm_FindChar(br->brawlVictim);
    if (b != 0 && victim != 0) {
      d.bld = b;
      d.range = 4000.0f;
      d.ev = e;
      d.found = 0;
      if (he_DetectAttack((intptr_t)&d) != 0) {
        br->brawlSlot =
            gv_Accuse(0x15, 1, ai_Chars[e->chr].netId, victim->netId, b->id);
        br->brawlWatch = d.found->id;
        e->stage = 8;
        e->end = ai_Time;
        return;
      }
    }
    e->stage = 4;
    return;
  }
  case 8: {
    AIJOB *w;
    CRIME *cr;

    if (br->brawlSlot != -1 && cm_GetSlotState(br->brawlSlot) == 0)
      return;
    b = gm_BuildQuery(1, 1, br->brawlPlace);
    w = he_FindEvent(1, 1, br->brawlWatch);
    if (b == 0 || w == 0 || w->patrolWait != e->id || br->brawlSlot == -1) {
      e->stage = -1;
      return;
    }
    c = gm_FindChar(br->brawlWatch);
    cr = (CRIME *)cm_GetSlotValue(br->brawlSlot);
    if (cr != 0 && c != 0)
      cm_SendProofExecuted(cr->id, c->netId);
    e->stage = 9;
    gm_AddTime(&e->end, 0, 10, 0);
    return;
  }
  case 9: {
    AIJOB *w;

    w = he_FindEvent(1, 1, br->brawlWatch);
    if (w == 0) {
      e->stage = -1;
      return;
    }
    if (w->patrolWait == e->id) {
      gm_AddTime(&e->end, 0, 6, 0);
      return;
    }
    cm_SendChrGotoBuilding(br->brawlThug, e->from, -1, 0, 1, "Pr\xfcgel");
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 4, 0);
    e->stage = 5;
    return;
  }
  case 3:
    cm_SendChrGotoBuilding(br->brawlThug, e->from, -1, 0, 1, "Pr\xfcgel");
    e->stage++;
    break;
  case 4:
    if (gm_CompareTime(&e->end, &ai_Time) >= 0)
      return;
    me = &ai_Chars[e->chr];
    victim = gm_FindChar(br->brawlVictim);
    if (victim == 0) {
      e->stage = -1;
      return;
    }
    won = ai_BrawlWin(me, victim, &out);
    if (ai_InventoryHas(victim, 0x2c0) != 0) {
      gm_SendMoneyDelta(me->netId, -1);
      if (me->kind == 6 || me->kind == 7) {
        txt_Format(text, 0x1012, victim->id, 2);
        he_ShowNews(me->netId, -1, text, 0, 0x5fa, 0);
      }
      if (victim->kind == 6 || victim->kind == 7) {
        txt_Format(text, 0x1010);
        he_ShowNews(victim->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_HS_17");
      }
      e->stage++;
      return;
    }
    if (ai_InventoryHas(victim, 0x17c) != 0) {
      if (me->kind == 6 || me->kind == 7) {
        txt_Format(text, 0xff3);
        he_ShowNews(me->netId, -1, text, 0, 0x5fa, 0);
      }
      e->stage++;
      return;
    }
    if (won != 0) {
      if (victim->kind == 6 || victim->kind == 7) {
        txt_Format(text, 0x173b, 2);
        he_ShowNews(victim->netId, -1, text, 0, 0x5fb, "_NACHRICHTEN_HS_17");
      }
      if (me->kind == 6 || me->kind == 7) {
        txt_Format(text, 0x173a, victim->id);
        he_ShowNews(me->netId, -1, text, 0, 0x5fa, 0);
      }
      if (ai_InventoryHas(victim, 0x2b4) != 0)
        gm_SendMoneyDelta(br->brawlVictim, -1);
      else
        gm_SendMoneyDelta(br->brawlVictim, -2);
    } else {
      if (victim->kind == 6 || victim->kind == 7) {
        txt_Format(text, 0x173d);
        he_ShowNews(victim->netId, -1, text, 0, 0x5fb, 0);
      }
      if (me->kind == 6 || me->kind == 7) {
        txt_Format(text, 0x173c, victim->id);
        he_ShowNews(me->netId, -1, text, 0, 0x5fa, 0);
      }
    }
    gv_Accuse(0x15, 1, ai_Chars[e->chr].netId, br->brawlVictim, br->brawlPlace);
    if (victim->kind == 6 || victim->kind == 7) {
      e->stage++;
      return;
    }
    cm_SendRelations(me->netId, victim->netId, -0x19, 1);
    e->stage++;
    return;
  case 5:
    c = gm_FindChar(br->brawlThug);
    if (c == 0) {
      e->stage = -1;
      return;
    }
    if (c->scene->actions != 0) {
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 4, 0);
      return;
    }
    e->stage = -1;
    return;
  case -2:
  case -1:
    if (br->brawlThug != -1)
      cm_SendKillCharacter(br->brawlThug, 1);
    he_FreeEvent(e);
    return;
  }
}
/* 0x55af70, the allocation handler of the theft event 27 (AIJOB.theft*; run handler he_RunTheft): due in 4 + random 3
   hours; without the building robbed, or one of the kinds 0xb / 0xc / 0xd, the event is freed. Else the building's
   field 0x5a is set to 2 (cm_SendSetField) and the round counter cleared; for an event shown when due (opts 2) at
   a building with a master, not of the type 0x27, every other player gets the news 0x17f4 ("_NACHRICHTEN_HS_43",
   the master, the building and the loot); a building of the kind 5 whose master is no player hands its object
   list's money to the master (cm_SendMoveGoods). No cm request is pending (exSlot -1) */
void he_AllocTheft(AIJOB *e) {
  AIJOB *t = e;
  AICHAR *master = 0;
  AIBLD *b;
  AIBTYPE *bt;
  int i, n;
  char text[0x800];

  e->end = ai_Time;
  gm_AddTime(&e->end, util_Random(3) + 4, 0, 0);
  b = gm_BuildQuery(1, 1, t->theftBld);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  bt = &ai_BTypes[b->type];
  if (bt->kind == 0xd || bt->kind == 0xc || bt->kind == 0xb) {
    he_FreeEvent(e);
    return;
  }
  cm_SendSetField(b->id, 0x5a, 2, 2, 0);
  t->theftRounds = 0;
  if (b->masterId != 0xffff) {
    master = &ai_Chars[b->masterId];
    if (master != 0 && (e->opts & 2) != 0 && b->type != 0x27) {
      for (i = 0; i < 768; i++) {
        if ((ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7) &&
            ai_Chars[i].netId != master->netId) {
          txt_Format(text, 0x17f4, master->id, b, t->theftLoot);
          he_MessageBoxQuickjump(ai_Chars[i].netId, -1, text, 0, 0x5ec, b->id,
                                 -1, ch_EmptyName, "_NACHRICHTEN_HS_43");
        }
      }
    }
  }
  if (bt->kind == 5 && master != 0 && master->kind != 6 && master->kind != 7 &&
      (n = gm_SumListMoney(b->objList)) != 0)
    cm_SendMoveGoods(master->netId, b->id, ai_OwnPlayer, n);
  e->exSlot = -1;
}
/* 0x55b140, the run handler of the theft event 27 (AIJOB.theft*; allocated by he_AllocTheft). A shown event (opts 2)
   waits while its cm request is pending. Stage 0, from the third round on: without the building, or one of the
   kinds 0xb / 0xc / 0xd, the event is freed; a shown event at a building not of the type 0x27 (or of it with a
   player for owner) rolls random 100 against 50 * loot / (the building's equipment value + 256): above it the
   theft message 0x6e (the building, the loot) goes to the event's character, the event is posted
   (cm_SendExSetHE -1) and the building's field 0x5a mark taken back; every round counts up and is due again in 4 +
   random 3 hours. Stages -2 / -1 take the mark back (when the building still exists) and free the event */
void he_RunTheft(AIJOB *e) {
  AIJOB *t = e;
  AIBLD *b;
  AIBTYPE *bt;
  float value, chance;
  int r;
  AIMSG msg;

  if ((e->opts & 2) != 0 && e->exSlot != -1) {
    if (cm_GetSlotState(e->exSlot) == 0)
      return;
    e->exSlot = -1;
  }
  switch (e->stage) {
  case 0:
    if (t->theftRounds >= 2) {
      b = gm_BuildQuery(1, 1, t->theftBld);
      if (b == 0) {
        he_FreeEvent(e);
        return;
      }
      bt = &ai_BTypes[b->type];
      if (bt->kind == 0xd || bt->kind == 0xc || bt->kind == 0xb) {
        he_FreeEvent(e);
        return;
      }
      if ((e->opts & 2) != 0 &&
          (b->type != 0x27 ||
           (b->owner != 0xffff &&
            (ai_Chars[b->owner].kind == 6 || ai_Chars[b->owner].kind == 7)))) {
        value = (float)gm_EquipmentValue(b, b->level) + 256.0f;
        chance = (float)t->theftLoot / value;
        r = util_Random(100);
        if ((float)r > chance * 50.0f) {
          memset(&msg, 0, sizeof(msg));
          msg.type = 0x6e;
          msg.fromId = -1;
          msg.flags = 1;
          msg.to = ai_Chars[e->chr].netId;
          msg.time = ai_Time;
          msg.arg[2] = t->theftBld;
          msg.arg[4] = t->theftLoot;
          cm_SendLongMessage(&msg);
          e->exSlot = cm_SendExSetHE(-1, e);
          cm_SendSetField(b->id, 0x5a, 2, 0, 2);
        }
      }
    }
    t->theftRounds++;
    e->end = ai_Time;
    gm_AddTime(&e->end, util_Random(3) + 4, 0, 0);
    return;
  case -2:
  case -1:
    b = gm_BuildQuery(1, 1, t->theftBld);
    if (b == 0) {
      he_FreeEvent(e);
      return;
    }
    cm_SendSetField(b->id, 0x5a, 2, 0, 2);
    he_FreeEvent(e);
    return;
  }
}

/* 0x55b3e0, the allocation handler of the repair event 28 (AIJOB.repair*; run handler he_RunRepair): without the
   building the event is freed; else it is the event's place, the building's field 0x5a gets the mark 4
   (cm_SendSetField), the clocks start now, the event is due in 10 minutes, and the planned end is 10 minutes per
   point from then, times 0.4 / 0.6 / 0.8 for an event character of the rank 9 and up / 8 / 7 */
void he_AllocRepair(AIJOB *e) {
  AIJOB *r = e;
  AIBLD *b;
  AICHAR *c;
  float f;

  b = gm_BuildQuery(1, 1, r->repairBld);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  e->from = b->id;
  cm_SendSetField(b->id, 0x5a, 2, 4, 0);
  e->clock60 = ai_Time;
  e->end = ai_Time;
  e->start = ai_Time;
  gm_AddTime(&e->end, 0, 10, 0);
  r->repairUntil = e->end;
  c = &ai_Chars[e->chr];
  if (c->level >= 9)
    f = 0.4f;
  else if (c->level == 8)
    f = 0.6f;
  else if (c->level == 7)
    f = 0.8f;
  else
    f = 1.0f;
  f = f * r->repairPoints * 10.0;
  gm_AddTime(&r->repairUntil, 0, (int)f, 0);
}
/* 0x55b530, the run handler of the repair event 28 (AIJOB.repair*; allocated by he_AllocRepair). Stage 0: without the
   building the event is freed; else the minutes since AIJOB.clock60, one point per 10 (rounded), are taken off the
   points left and added to the building's state (gm_ChangeBuildingState). Points left: the clocks restart and it is
   due in 10 minutes. Done: the event's character (a player) gets the news 0x17cb with the building type's name
   (the text 0x48e + 14 * type; "_NACHRICHTEN_HS_68"; the news 0x60b when the building's master is a kind 1
   character with flags1b4 bit 0, else 0x5f6) and the stage is -1. Stages -2 / -1 clear the building's 0x5a mark
   4 and free the event */
void he_RunRepair(AIJOB *e) {
  AIJOB *r = e;
  AIBLD *b;
  AICHAR *m;
  int n, news;
  char text[0x100];

  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, r->repairBld);
    if (b == 0)
      break;
    n = (int)(gm_MinutesBetween(&e->clock60, &ai_Time) * 0.1 + 0.5);
    r->repairPoints -= n;
    gm_ChangeBuildingState(b, n);
    if (r->repairPoints > 0) {
      e->clock60 = ai_Time;
      e->end = ai_Time;
      gm_AddTime(&e->end, 0, 10, 0);
      return;
    }
    news = 0x5f6;
    m = gm_FindCharacterByMaster(b);
    if (m != 0 && m->kind == 1 && (m->flags1b4 & 1) != 0)
      news = 0x60b;
    txt_Format(text, 0x17cb, 0x48e + b->type * 14);
    if (e->chr != 0xffff &&
        (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7))
      he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, news, b->id,
                             -1, 0, "_NACHRICHTEN_HS_68");
    e->stage = -1;
    return;
  case -2:
  case -1:
    b = gm_BuildQuery(1, 1, r->repairBld);
    if (b != 0)
      cm_SendSetField(b->id, 0x5a, 2, 0, 4);
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x55b720, the allocation handler of the building event 0x1e (run handler he_RunUpgrade, which clears the mark
   and tells the master; reasoned: the upgrade to the next building type): started and due now; without the
   building (AIJOB.bldId) the event is freed; it lasts 30 minutes with gm_AllowAll, else a day per v243 the next
   type has more than this one (at least a day); the building is the event's place; a building already marked
   0x40 in its field 0x5a frees the event, else the mark is set (cm_SendSetField) */
void he_AllocUpgrade(AIJOB *e) {
  AIBLD *b;
  AIBTYPE *bt;
  int hours;

  e->end = ai_Time;
  e->start = ai_Time;
  b = gm_BuildQuery(1, 1, e->bldId);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  if (gm_AllowAll == 0) {
    bt = &ai_BTypes[b->type];
    hours = (bt[1].v243 - bt->v243) * 24;
    if (hours <= 0)
      hours = 24;
    gm_AddTime(&e->end, hours, 0, 0);
  } else
    gm_AddTime(&e->end, 0, 30, 0);
  e->from = b->id;
  if ((b->flags5aw & 0x40) != 0) {
    he_FreeEvent(e);
    return;
  }
  b->flags5aw |= 0x40;
  cm_SendSetField(b->id, 0x5a, 2, 0x40, 0);
}
/* 0x55b830, the run handler of the building event 0x1e (allocated by he_AllocUpgrade). Stage 0: without the
   building (AIJOB.bldId) the event is freed; a player's event character (kind 6) gets the news 0x17e7 about the
   building ("_NACHRICHTEN_HS_51"; the news 0x60b when the building's master has flags1b4 bit 0, else 0x5f6); for
   an event character of the kind 5 / 6 every other player gets the news 0x1c32 with the type's text 0x49c + 14 *
   type ("_NACHRICHTEN_HS_52"); the message 0x3a (cm_SendUpgradeDone) goes out for the building, its 0x5a mark 0x40 is
   cleared and the event freed. Stages -2 / -1 clear the mark and free the event */
void he_RunUpgrade(AIJOB *e) {
  AIBLD *b, *at;
  AICHAR *m, *me;
  int i, news;
  char text[0x400];

  news = 0x5f6;
  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0) {
      m = gm_FindCharacterByMaster(b);
      if (m != 0 && (m->flags1b4 & 1) != 0)
        news = 0x60b;
      me = &ai_Chars[e->chr];
      if (me->kind == 6) {
        txt_Format(text, 0x17e7, b);
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId,
                               text, 0, news, b->id, -1, 0,
                               "_NACHRICHTEN_HS_51");
      }
      if (me->kind == 5 || me->kind == 6) {
        for (i = 0; i < 768; i++) {
          if ((ai_Chars[i].kind == 6 || ai_Chars[i].kind == 7) && i != me->id) {
            txt_Format(text, 0x1c32, e->chr, e->chr, 0x49c + b->type * 14);
            he_MessageBoxQuickjump(ai_Chars[i].netId, -1, text, 0, 0x607, b->id,
                                   -1, 0, "_NACHRICHTEN_HS_52");
          }
        }
      }
      cm_SendUpgradeDone(b->id);
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x40);
    }
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    at = gm_BuildQuery(1, 1, e->bldId);
    if (at != 0)
      cm_SendSetField(at->id, 0x5a, 2, 0, 0x40);
    he_FreeEvent(e);
    return;
  }
}
/* 0x55ba00, the allocation handler of the event type 0x1f: both clocks now, then the due clock 1 second later (5 hours with
   gm_AllowAll); the building +0xac (none: the record is freed) is copied to +0x10 and gets the field 0x5a / 2 / 0x80
   while the 0x80 bit of its byte +0x5a is clear */

void he_AllocEvent1f(AIJOB *e) {
  AIBLD *b;

  e->end = ai_Time;
  e->start = ai_Time;
  if (gm_AllowAll != 0)
    gm_AddTime(&e->end, 0, 0, 1);
  else
    gm_AddTime(&e->end, 5, 0, 0);
  b = gm_BuildQuery(1, 1, e->bldId);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  e->from = b->id;
  if ((b->flags5a & 0x80) == 0)
    cm_SendSetField(b->id, 0x5a, 2, 0x80, 0);
}
/* 0x55bad0, the run handler of the building event 0x1f (AIJOB.upgradeGood; its init he_AllocEvent1f sets the building's 0x5a
   mark 0x80). Stage 0: the building (when found) makes one piece of the good for the own player
   (cm_SendExSellObject) and its mark 0x80 is cleared; stage 1: the event character gets the news 0x1c2b about the
   good's object in the building ("_NACHRICHTEN_HS_53"; 0x60b when the building is no kind 6 and its master is a
   kind 1 character with flags1b4 bit 0, else 0x606), a home type sends the sys message 4 (HESOLDMSG: the building,
   its object of key 4 = 2), and the event is freed. Stages -2 / -1 clear the mark and free the event */

void he_RunEvent1f(AIJOB *e) {
  AIJOB *g = e;
  AIBLD *b;
  AIOBJ *o, *q;
  AICHAR *m;
  AIBTYPE *bt;
  int news;
  char text[0x400];
  HESOLDMSG msg;

  news = 0x606;
  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0) {
      cm_SendExSellObject(b->id, -1, g->upgradeGood, 1, ai_OwnPlayer, 0);
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x80);
    }
    e->stage++;
    return;
  case 1:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0) {
      o = gm_Query(b->objList, 1, 0, g->upgradeGood);
      if (o != 0) {
        bt = &ai_BTypes[b->type];
        txt_Format(text, 0x1c2b, b, g->upgradeGood * 2 + 0x9a8);
        if (bt->kind != 6) {
          m = gm_FindCharacterByMaster(b);
          if (m != 0 && m->kind == 1 && (m->flags1b4 & 1) != 0)
            news = 0x60b;
        }
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId,
                               text, 0, news, b->id, o->objId, 0,
                               "_NACHRICHTEN_HS_53");
      }
      if (gm_IsHomeType(b)) {
        q = gm_Query(b->objList, 1, 4, 2);
        msg.due = ai_Time;
        gm_AddTime(&msg.due, 0, 0, 1);
        msg.sold.bld = b->id;
        msg.sold.objId = q->objId;
        cm_SendExSysMessage(4, &msg);
      }
    }
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0)
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x80);
    he_FreeEvent(e);
    return;
  }
}
/* 0x55bd20, the allocation handler of the demolition event 0x20 (he_RunDemolish): the building (AIJOB.bldId, when
   found) gets the message 0x5a / 2 / 0x400, the due clock is now */

void he_AllocDemolish(AIJOB *e) {
  AIBLD *b;

  b = gm_BuildQuery(1, 1, e->bldId);
  if (b != 0)
    cm_SendSetField(b->id, 0x5a, 2, 0x400, 0);
  e->end = ai_Time;
}
/* 0x55bd80, the run handler of the demolition event 0x20 ("GebAbreissen"; its init he_AllocDemolish sets the building's
   0x5a mark 0x400). Stage 0 (the building found): every character working in the building (AICHAR.bld) is halted
   when it has a model and sent home (gm_CharacterHome: to its home object, else into the building), the due
   clock is set 5 minutes from now. Stage 1: unless the building is of the kind 0xf, every other player (kind 6 / 7,
   not the owner) gets the news 0x1c52 (0x5ed, "_NACHRICHTEN_HS_67") and the building is destroyed
   (cm_SendBuildingDestroyed); the event is freed. Stages -2 / -1 free the event */

void he_RunDemolish(AIJOB *e) {
  AIBLD *b;
  AICHAR *c;
  int i, homeBld, homeObj;
  char text[0x400];

  switch (e->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b == 0)
      return;
    for (i = 0; i < 768; i++) {
      c = &ai_Chars[i];
      if (c->bld == b) {
        if (c->scene != 0)
          cm_SendCharHalt(c->netId);
        if (gm_CharacterHome(c, &homeBld, &homeObj) != 0) {
          if (homeObj != -1)
            cm_SendChrGotoBuilding(c->netId, homeBld, homeObj, 0, 0,
                                   "GebAbreissen");
          else
            cm_SendChrGotoBuilding(c->netId, homeBld, -1, 0, 1, "GebAbreissen");
        }
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 5, 0);
    e->stage++;
    return;
  case 1:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0 && ai_BTypes[b->type].kind != 0xf) {
      for (i = 0; i < 768; i++) {
        c = &ai_Chars[i];
        if ((c->kind == 6 || c->kind == 7) && c->id != b->owner) {
          txt_Format(text, 0x1c52, b->owner, b);
          he_ShowNews(c->netId, -1, text, 0, 0x5ed, "_NACHRICHTEN_HS_67");
        }
      }
      cm_SendBuildingDestroyed(b->id);
    }
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    he_FreeEvent(e);
    return;
  }
}

/* 0x55bf50, the allocation handler of the building purchase event 0x21: the building (AIJOB.bldId) gets the message
   0x5a / 2 / 0x200, the due clock is now + 10 .. 19 minutes */

void he_AllocBuyBuilding(AIJOB *e) {
  AIBLD *b;

  b = gm_FindBuildingById(e->bldId);
  e->end = ai_Time;
  gm_AddTime(&e->end, 0, util_Random(10) + 10, 0);
  cm_SendSetField(b->id, 0x5a, 2, 0x200, 0);
}
/* 0x55bfd0, the run handler of the building purchase event 0x21 (AIJOB.buy*: the buyer offers price for the building).
   Stage 0: a building whose master is a player (kind 6 / 7) opens the event box "misc\EventMessagebox_NULL" with
   the text 0x17e8 and waits for the answer (stage 1); a computer master decides once the event is due: the
   building's equipment value (gm_EquipmentValue) times (1.5 - liking * 0.01) times a factor (15; 5 for the
   master's own home, 1.2 when it is of a lower type than the home; else 8 for a master of the kind 5 / 6 / 7 with at
   most one building of the type, 1.6 otherwise) must stay below the price. Yes (stage 1: d2_ClickedId 0): the
   buyer gets the news 0x17e9, the master the price (cm_SendMoveGoodsUnchecked) and the buyer the building
   (cm_SendOwnership; also as the owner when the master owned it); no (1): the news 0x17ea; both clear the
   building's 0x5a mark 0x200 and free the event (the computer's no frees it twice, the original's). Stages -2 /
   -1 clear the mark and free the event */

void he_RunBuyBuilding(AIJOB *ev) {
  AIJOB *p = ev;
  AICHAR *buyer;
  AIBLD *b, *home;
  AIBTYPE *bt;
  int n, value;
  float factor;
  float liking;
  char text[0x400];

  switch (ev->stage) {
  case 0:
    buyer = gm_FindChar(p->buyBuyer);
    b = gm_FindBuildingById(ev->bldId);
    if (buyer == 0 || b == 0) {
      he_FreeEvent(ev);
      return;
    }
    if (ai_Chars[b->masterId].kind == 6 || ai_Chars[b->masterId].kind == 7) {
      he_OpenEventSlot(ev, 0, 0, "misc\\EventMessagebox_NULL", 0x5ec);
      d2_SetForm(ev->slot->win, 0);
      io_PrintText(0x17e8, buyer->id, b, p->buyPrice);
      ev->stage++;
      return;
    }
    if (gm_CompareTime(&ev->end, &ai_Time) >= 0)
      return;
    factor = 15.0f;
    buyer = gm_FindChar(p->buyBuyer);
    b = gm_FindBuildingById(ev->bldId);
    bt = &ai_BTypes[b->type];
    value = gm_EquipmentValue(b, b->level);
    if (bt->kind == 2) {
      home = ai_Chars[b->masterId].bld2;
      if (home != 0) {
        if (home == b)
          factor = 5.0f;
        else if (ai_Chars[b->masterId].bld2 != 0 &&
                 ai_Chars[b->masterId].bld2->type < b->type)
          factor = 1.2f;
      }
    } else {
      n = 0;
      /* @original bt is taken again here (the original's dead lea of the type record after the kind read) */
      bt = &ai_BTypes[b->type];
      if (gm_BuildQuery(2, 4, ai_Chars[b->masterId].id, 5,
                        (unsigned char)bt->kind) != 0) {
        do
          n++;
        while (gm_BuildNext() != 0);
      }
      if (n <= 1 &&
          (ai_Chars[b->masterId].kind == 6 || ai_Chars[b->masterId].kind == 7 ||
           ai_Chars[b->masterId].kind == 5))
        factor = 8.0f;
      else
        factor = 1.6f;
    }
    liking = gm_Liking(buyer->id, b->masterId, 1) * 0.01f;
    if (p->buyPrice > (float)((1.5 - liking) * factor) * value) {
      txt_Format(text, 0x17e9, b->owner, b);
      he_MessageBoxQuickjump(buyer->netId, -1, text, 0, 0x5ec, b->id, -1, 0, 0);
      cm_SendSetField(b->id, 0x5a, 2, 2, 0x200);
      cm_SendMoveGoodsUnchecked(ai_Chars[b->masterId].netId, buyer->netId,
                                ai_OwnPlayer, p->buyPrice);
      if (b->owner == b->masterId)
        cm_SendOwnership(b->id, buyer->netId, buyer->netId);
      else
        cm_SendOwnership(b->id, buyer->netId, -1);
      cm_SendSetField(b->id, 0x5a, 2, 0, 2);
    } else {
      txt_Format(text, 0x17ea, b->owner, b);
      he_MessageBoxQuickjump(buyer->netId, -1, text, 0, 0x5ec, b->id, -1, 0, 0);
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x200);
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
    }
    he_FreeEvent(
        ev); /* the original's: the decline above frees the record once more */
    return;
  case 1:
    if (d2_ClickedForm != ev->slot->win || d2_ClickedId == -1)
      return;
    buyer = gm_FindChar(p->buyBuyer);
    b = gm_FindBuildingById(ev->bldId);
    if (d2_ClickedId == 0) {
      txt_Format(text, 0x17e9, b->owner, b);
      he_MessageBoxQuickjump(buyer->netId, -1, text, 0, 0x5ec, b->id, -1, 0, 0);
      cm_SendSetField(b->id, 0x5a, 2, 2, 0x200);
      cm_SendMoveGoodsUnchecked(ai_Chars[b->masterId].netId, buyer->netId,
                                ai_OwnPlayer, p->buyPrice);
      if (b->owner == b->masterId)
        cm_SendOwnership(b->id, buyer->netId, buyer->netId);
      else
        cm_SendOwnership(b->id, buyer->netId, -1);
      cm_SendSetField(b->id, 0x5a, 2, 0, 2);
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
      return;
    }
    if (d2_ClickedId != 1)
      return;
    txt_Format(text, 0x17ea, b->owner, b);
    he_MessageBoxQuickjump(buyer->netId, -1, text, 0, 0x5ec, b->id, -1, 0, 0);
    cm_SendSetField(b->id, 0x5a, 2, 0, 0x200);
    he_ReleaseSlot(ev);
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    b = gm_FindBuildingById(ev->bldId);
    if (b != 0)
      cm_SendSetField(b->id, 0x5a, 2, 0, 0x200);
    he_ReleaseSlot(ev);
    he_FreeEvent(ev);
    return;
  }
}
/* 0x55c540, the allocation handler of the loan event 0x23 (AIJOB.loan*; run handler he_RunKredit): the
   due clock is now, the payback date is days days from now at 8:00, daysLeft = days. A posted event (opts 2) whose
   building has a player owner (kind 6 / 7) gives the owner the news 0x18d7 (the partner, the building, amount,
   interest, days, the building's money: its object of the player's moneyGood) and reports the owner for the law
   0xe with the interest (gv_Accuse) */

void he_AllocKredit(AIJOB *e) {
  AIJOB *l = e;
  AIBLD *b;
  AICHAR *owner, *partner;
  AIOBJ *o;
  int cash;
  char text[0x200];

  e->end = ai_Time;
  l->loanDue = ai_Time;
  gm_AddTime(&l->loanDue, l->loanDays * 24, 0, 0);
  l->loanDue.hour = 8;
  l->loanDue.min = 0;
  l->loanDue.sec = 0;
  l->loanDaysLeft = l->loanDays;
  b = gm_BuildQuery(1, 1, e->bldId);
  if (b == 0 || (e->opts & 2) == 0)
    return;
  owner = &ai_Chars[b->owner];
  partner = gm_FindChar(l->loanPartner);
  if (owner->kind == 6 || owner->kind == 7) {
    cash = 0;
    o = gm_Query(b->objList, 1, 0, ai_PlayerSlots[ai_OwnPlayer].moneyGood);
    if (o != 0)
      cash = o->count;
    txt_Format(text, 0x18d7, partner->id, b, l->loanAmount, l->loanInterest,
               l->loanDays, 0x5d, cash);
    he_MessageBoxQuickjump(owner->netId, -1, text, 0, 0x5ec, b->id, -1, 0, 0);
    gv_Accuse(0xe, l->loanInterest, owner->netId, l->loanPartner, b->id);
  }
}
/* 0x55c700, the run handler of the loan event 0x23 (AIJOB.loan*), daily while the send slot exSlot is free. Stage 0: a
   posted event (opts 2) charges the interest (interest % of amount): without the partner the building's owner gets
   the news 0x18e7 and the event goes to the cm (cm_SendExSetHE); a partner short of goods value pays by
   ai_LiquidateAssets (the news 0x18e8, shown to the partner when the owner is a player), else by
   cm_SendMoveGoodsUnchecked; either way the building's roundSums[2] grows by it. A missing building prints the
   debug text "he_RunKredit(): Could not find GebaeudeId '%i'" and frees the event. Once daysLeft runs out the
   partner pays the amount back (ai_LiquidateAssets; the news 0x18e9, or 0x18ea with "_NACHRICHTEN_HS_69" when
   short), a player owner gets the news 0x18d8, and the event is freed. Stages -2 / -1 tell the owner 0x18e7 when
   the partner is gone and free the event */

void he_RunKredit(AIJOB *e) {
  AIJOB *l = e;
  AIBLD *b;
  AICHAR *owner, *partner;
  float due;
  int value, n, paid;
  char dbg[0x80];
  char text[0x400];
  char text2
      [0x800]; /* reasoned: the original's frame 0xc8c holds 0x400 more than the three buffers use */

  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  e->exSlot = -1;
  switch (e->stage) {
  case 0:
    if (e->opts & 2) {
      b = gm_BuildQuery(1, 1, e->bldId);
      if (b != 0) {
        partner = gm_FindChar(l->loanPartner);
        owner = &ai_Chars[b->owner];
        if (partner == 0) {
          txt_Format(text, 0x18e7, l->loanAmount);
          he_ShowNews(owner->netId, -1, text, 0, 0x5ff, 0);
          e->exSlot = cm_SendExSetHE(-1, e);
          return;
        }
        due = l->loanAmount * (l->loanInterest * 0.01);
        value = gm_GetGoodsValue(partner);
        if (value < due) {
          n = (int)due;
          txt_Format(text2, 0x18e8, n);
          paid = ai_LiquidateAssets(b->id, partner, n, text2);
          b->roundSums[2] += paid;
          if (owner->kind == 6 || owner->kind == 7)
            he_ShowNews(l->loanPartner, -1, text2, 0, 0x5ff, 0);
        } else {
          cm_SendMoveGoodsUnchecked(b->id, l->loanPartner, ai_OwnPlayer,
                                    (int)due);
          b->roundSums[2] += due;
        }
      } else {
        sprintf(dbg, "he_RunKredit(): Could not find GebaeudeId '%i'",
                e->bldId);
        he_FreeEvent(e);
        return;
      }
    }
    if (--l->loanDaysLeft >= 0)
      return;
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b == 0)
      break;
    owner = &ai_Chars[b->owner];
    partner = gm_FindChar(l->loanPartner);
    if ((e->opts & 2) == 0)
      break;
    value = gm_GetGoodsValue(partner);
    if (value < l->loanAmount)
      txt_Format(text, 0x18ea, l->loanAmount);
    else
      txt_Format(text, 0x18e9, l->loanAmount);
    ai_LiquidateAssets(b->id, partner, l->loanAmount, text);
    if (value < l->loanAmount)
      he_ShowNews(l->loanPartner, -1, text, 0, 0x5ff, "_NACHRICHTEN_HS_69");
    else
      he_ShowNews(l->loanPartner, -1, text, 0, 0x5ff, ch_EmptyName);
    if (owner->kind == 6 || owner->kind == 7) {
      txt_Format(text2, 0x18d8, partner->id, b, l->loanAmount);
      he_ShowNews(owner->netId, -1, text2, 0, 0x5ff, 0);
    }
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0) {
      partner = gm_FindChar(l->loanPartner);
      owner = &ai_Chars[b->owner];
      if (partner == 0) {
        txt_Format(text2, 0x18e7, l->loanAmount);
        he_ShowNews(owner->netId, -1, text2, 0, 0x5ff, 0);
      }
    }
    break;
  default:
    return;
  }
  he_FreeEvent(e);
}
/* 0x55cb00, the run handler of the event 0x24 (AIJOB.ev24*): stage 0 counts daysLeft down; once it is below 0 and the
   character AIJOB.ownerCh is found, a player character (kind 6 / 7) gets the long message 0x26 (to and arg[0] the
   character, from -1, now, flags 9), the character's job becomes jobId - 1 (cm_SendSetJob) and the event is freed.
   Stages -2 / -1 free the event */

void he_RunEvent24(AIJOB *e) {
  AIJOB *w = e;
  AICHAR *c;
  AIMSG msg;

  switch (e->stage) {
  case 0:
    w->ev24DaysLeft--;
    c = gm_FindChar(e->ownerCh);
    if (w->ev24DaysLeft < 0 && c != 0) {
      if (c->kind == 6 || c->kind == 7) {
        memset(&msg, 0, sizeof(msg));
        msg.type = 0x26;
        msg.to = e->ownerCh;
        msg.fromId = -1;
        msg.flags = 9;
        msg.time = ai_Time;
        msg.arg[0] = e->ownerCh;
        cm_SendLongMessage(&msg);
      }
      cm_SendSetJob(c->netId, c->jobId - 1);
      he_FreeEvent(e);
    }
    return;
  case -2:
  case -1:
    he_FreeEvent(e);
    return;
  }
}

/* 0x55cc10, the run handler of the master exam announcement, event 0x25 (its init he_RunDueNow), once due. Stage 0
   opens the event box "Berufe\Messagebox_Meisterpruefung" (picture 0x5fd; none: the event is freed); for the
   character AIJOB.ownerCh it speaks the training voice of its title group (gm_TitleGroup of its jobId: the
   "BERUF_TRAINING_SPIELER_MAENNLICH" / "_WEIBLICH" variant group - 1, from the ADDON_ bank for the groups above
   12) and prints the text 0x159a (the character, the text 0x1556 + titles left + 1, the group's text from 0x159b,
   0x15ab for a woman); stage 1. Stage 1 waits for the answer: yes (d2_ClickedId 0) selects the object of the
   kind 0x13 of the character's home bld2 in the panel (sv_SelectPanelObject), yes and no (1) close the box and
   free the event. Stages -2 / -1 close and free */
void he_RunMasterExamNotice(AIJOB *ev) {
  AICHAR *c;
  AIOBJ *o;
  struct SBBANK *bank;
  int left, group, text;

  if (gm_CompareTime(&ai_Time, &ev->end) < 0)
    return;
  switch (ev->stage) {
  case 0:
    he_OpenEventSlot(ev, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5fd);
    if (ev->slot == 0) {
      he_FreeEvent(ev);
      return;
    }
    c = gm_FindChar(ev->ownerCh);
    if (c != 0) {
      left = gm_TitlesLeft(c->jobId) + 1;
      text = (c->sex != 0 ? 0x10 : 0) + 0x159b;
      group = gm_TitleGroup(c->jobId);
      if (c->sex == 0) {
        if (group <= 12) {
          bank = sb_FindBank("BERUF_TRAINING_SPIELER_MAENNLICH");
          snd_QueueVoice(-8, bank, "BERUF_TRAINING_SPIELER_MAENNLICH",
                         group - 1, 0);
        } else {
          bank = sb_FindBank("ADDON_BERUF_TRAINING_SPIELER_MAENNLICH");
          snd_QueueVoice(-8, bank, "BERUF_TRAINING_SPIELER_MAENNLICH",
                         group - 13, 0);
        }
      } else {
        if (group <= 12) {
          bank = sb_FindBank("BERUF_TRAINING_SPIELER_WEIBLICH");
          snd_QueueVoice(-8, bank, "BERUF_TRAINING_SPIELER_WEIBLICH", group - 1,
                         0);
        } else {
          bank = sb_FindBank("ADDON_BERUF_TRAINING_SPIELER_WEIBLICH");
          snd_QueueVoice(-8, bank, "BERUF_TRAINING_SPIELER_WEIBLICH",
                         group - 13, 0);
        }
      }
      io_PrintText(0x159a, c->id, left + 0x1556, group + text, 4);
    }
    ev->stage++;
    return;
  case 1:
    if (d2_ClickedForm != ev->slot->win || d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      c = gm_FindChar(ev->ownerCh);
      if (c->bld2 != 0) {
        o = gm_Query((void *)c->bld2->objList, 2, 0, 0x13, 6);
        sv_SelectPanelObject(c->bld2, o->objId, ch_EmptyName);
      }
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
      return;
    }
    if (d2_ClickedId == 1) {
      he_ReleaseSlot(ev);
      he_FreeEvent(ev);
    }
    return;
  case -2:
  case -1:
    he_ReleaseSlot(ev);
    he_FreeEvent(ev);
    return;
  }
}
/* 0x55ce00, the allocation handler of the passed master exam event 0x26: the event 0x25 record of the same character
   is ended (stage -1), the due clock is now */

void he_AllocMasterExamPass(AIJOB *e) {
  AIJOB *exam;

  gm_FindChar(e->ownerCh);
  exam = he_FindEvent(2, 2, e->chr, 0, 0x25);
  if (exam != 0)
    exam->stage = -1;
  e->end = ai_Time;
}
/* 0x55ce60, the run handler of the passed master exam, event 0x26 (AIJOB.examPass*), on the player's own machine
   (ai_PlayerId is AIJOB.chr) while a game runs and once started; the first run notes the character's job and
   newJob = job - 1. Stage 0 opens the event box "Berufe\Meisterpruefung_BESTANDEN" (none: the event is freed),
   prints the text 0x15c3 (the player's name, now, the new job's title text 0x130 + newJob (0x18f for a woman), the
   group's text, the text 0x158a + group), gives the character newJob (cm_SendSetJob) and, for a kind 5 / 6 / 7
   character, tells every other player the news 0x1c1f and clears its flags1c8 bit 31. Stage 1 queues the
   ceremony voices: a fanfare by the titles left, "SELBST", the job list "brk_<group>" (the BERUF_LISTE bank of
   the sex, ADDON_ for the groups above 12), the building list, "GEZEICHNET", the signature
   "_BERUFE_VEREINIGUNG_UNTERSCHRIFT" and the click. Stage 2 waits for the box's answer (or a confirmed slot)
   and closes and frees it. Stages -2 / -1 close and free */

void he_RunMasterExamPassed(AIJOB *e) {
  AIJOB *x = e;
  AICHAR *c, *o;
  struct SBBANK *list, *sign, *bld, *self;
  int i, group, left, sexText;
  char bank[0x40];
  char text[0x400];

  if (ai_PlayerId != e->chr || ai_GameState == 0)
    return;
  if (gm_CompareTime(&e->start, &ai_Time) > 0)
    return;
  if (x->examPassNewJob == 0) {
    c = gm_FindChar(e->ownerCh);
    if (c != 0) {
      x->examPassJob = c->jobId;
      x->examPassNewJob = c->jobId - 1;
    }
  }
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Berufe\\Meisterpruefung_BESTANDEN", 0x5ec);
    if (e->slot == 0) {
      he_FreeEvent(e);
      return;
    }
    d2_SetForm(e->slot->win, 0);
    d2_CentreViewWindows(e->slot->win);
    c = gm_FindChar(e->ownerCh);
    sexText = (c->sex != 0 ? 0x5f : 0) + 0x130;
    group = gm_TitleGroup(x->examPassJob);
    left = gm_TitlesLeft(x->examPassJob) + 1;
    d2_SetForm(e->slot->win, 1);
    io_PrintText(0x15c3, ai_PlayerSlots[ai_OwnPlayer].townName, &ai_Time,
                 x->examPassNewJob + sexText,
                 (int)((float)((left - 1) * 0.5) + (group * 3 + 0x155a)),
                 group + 0x158a);
    cm_SendSetJob(c->netId, x->examPassNewJob);
    if (c->kind == 6 || c->kind == 7 || c->kind == 5) {
      txt_Format(text, 0x1c1f, c->id, x->examPassJob + sexText,
                 x->examPassNewJob + sexText);
      for (i = 0; i < 768; i++) {
        o = &ai_Chars[i];
        if ((o->kind == 6 || o->kind == 7) && o->netId != c->netId)
          he_ShowNews(o->netId, -1, text, 0, 0x5fe, 0);
      }
      c->flags1c8 &= 0x7fffffff;
    }
    e->stage++;
    return;
  case 1:
    c = gm_FindChar(e->ownerCh);
    group = gm_TitleGroup(x->examPassJob);
    left = gm_TitlesLeft(x->examPassJob) + 1;
    sprintf(bank, "brk_%02i", group);
    self = sb_FindBank("BERUF_BESTANDEN");
    if (group > 12) {
      if (c->sex == 0)
        list = sb_FindBank("ADDON_BERUF_LISTE_MAENNLICH");
      else
        list = sb_FindBank("ADDON_BERUF_LISTE_WEIBLICH");
      bld = sb_FindBank("ADDON_GEBAEUDE_LISTE");
      sign = sb_FindBank("ADDON_BERUFE_VEREINIGUNG_UNTERSCHRIFT");
    } else {
      if (c->sex == 0)
        list = sb_FindBank("BERUF_LISTE_MAENNLICH");
      else
        list = sb_FindBank("BERUF_LISTE_WEIBLICH");
      bld = sb_FindBank("GEBAEUDE_LISTE");
      sign = sb_FindBank("BERUFE_VEREINIGUNG_UNTERSCHRIFT");
    }
    if (left < 3)
      snd_QueueVoice(-7, 0, "FanfarePositivKurz", -1, 0);
    else if (left < 5)
      snd_QueueVoice(-7, 0, "FanfarePositivMittel", -1, 0);
    else
      snd_QueueVoice(-7, 0, "FanfarePositivLang", -1, 0);
    snd_QueueVoice(-6, self, "SELBST", 1, 0);
    snd_QueueVoice(-8, list, bank, left - 2, 0);
    snd_QueueVoice(-6, self, "SELBST", 0, 0);
    left--;
    snd_QueueVoice(-8, bld, bank, (int)(3.0 - (left + 1.0) * 0.5), 0);
    snd_QueueVoice(-6, self, "GEZEICHNET", -1, 0);
    snd_QueueVoice(-8, sign, "_BERUFE_VEREINIGUNG_UNTERSCHRIFT",
                   group > 12 ? group - 13 : group - 1, 0);
    snd_QueueVoice(-7, 0, "MausclickLinks_s_01", -1, 0);
    e->stage++;
    return;
  case 2:
    if (e->slot == 0) {
      e->stage = 0;
      return;
    }
    if (d2_ClickedForm != e->slot->win &&
        (he_SlotConfirmed == 0 || he_ActiveSlot != e->slot))
      return;
    if (d2_ClickedId != -1 ||
        (he_SlotConfirmed != 0 && he_ActiveSlot == e->slot)) {
      if (d2_ClickedId != 0) {
        if (d2_ClickedId == 1 || he_SlotConfirmed != 0) {
          he_ReleaseSlot(e);
          he_FreeEvent(e);
          he_SlotConfirmed = 0;
        }
      } else {
        he_ReleaseSlot(e);
        he_FreeEvent(e);
      }
    }
    return;
  case -2:
  case -1:
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    return;
  }
}

struct G15PLANT *veg_FindPlantId(struct G15PLANT *p, int id);

/* 0x55d310, the allocation handler of the event type 0x27: the building +0xac (none: the record is freed) is asked for its
   skill 0x10 / 1, the due clock is now + 0x18 hours with its minute field cleared */
void he_AllocEvent27(AIJOB *e) {
  AIBLD *b;

  b = gm_BuildQuery(1, 1, e->bldId);
  if (b != 0) {
    gm_BuildingSkill(b, 0x10, 1);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0x18, 0, 0);
    e->end.min = 0;
  } else {
    he_FreeEvent(e);
  }
}
/* 0x55d390, the run handler of the event type 0x27 (a payment from a player into a building): stages -2 / -1 free the
   record, a later stage leaves it; at stage 0 the building AIJOB.bldId (none: freed) gets the amount in the paying
   player's money good (cm_SendExSellObject, the good GMPLAYERSLOT.moneyGood of the player slot AIJOB.payer), the
   event character the news 0x190b (the player's name, the amount); then the record is freed */
void he_RunEvent27(AIJOB *e) {
  AIJOB *p = e;
  AIBLD *b;
  char text[0x400];

  switch (e->stage) {
  case -2:
  case -1:
    he_FreeEvent(e);
    break;
  case 0:
    b = gm_BuildQuery(1, 1, e->bldId);
    if (b != 0) {
      txt_Format(text, 0x190b, ai_PlayerSlots[p->payer].name, p->ev27Amount);
      he_ShowNews(ai_Chars[e->chr].netId, -1, text, 0, 0x5ff, (char *)0);
      cm_SendExSellObject(b->id, -1, ai_PlayerSlots[p->payer].moneyGood,
                          p->ev27Amount, ai_OwnPlayer, 0);
    }
    he_FreeEvent(e);
    break;
  }
}
/* 0x55d490, the allocation handler of the harvest event: due in a second, stage 0; the building harvestBld, its plant
   harvestPlant and the worker harvestWorker. A plant missing or held by another event (fallId) lets the worker leave
   the building's group and frees the record, as does a missing worker or one already harvesting (job kind 0x28).
   Else the worker joins the group at the building's object 0xfd, the plant is taken under the event's id
   (cm_SetPlant, fall 1; its send slot to harvestSlot), no script runs yet and the plant's type is noted */
void he_AllocHarvest(AIJOB *e) {
  AIBLD *b;
  AICHAR *c;
  G15PLANT *pl, *plants;
  AIOBJ *o;

  e->end = ai_Time;
  gm_AddTime(&e->end, 0, 0, 1);
  e->stage = 0;
  b = gm_BuildQuery(1, 1, e->harvestBld);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  plants = b->plants;
  pl = veg_FindPlantId(plants, e->harvestPlant);
  c = gm_FindChar(e->harvestWorker);
  if (pl == 0 || pl->fallId != -1) {
    if (c != 0)
      sv_MoveToGroup(b, 0, c->id, 0);
    he_FreeEvent(e);
    return;
  }
  if (c == 0 || c->jobKind == 0x28) {
    he_FreeEvent(e);
    return;
  }
  o = gm_Query(b->objList, 1, 0, 0xfd);
  sv_MoveToGroup(b, o, c->id, e);
  e->harvestSlot = cm_SetPlant(e->harvestBld, pl->x, pl->z, pl->type, 1, e->id);
  e->harvestType = pl->type;
  e->harvestScript = -1;
}
/* 0x55d5c0, the run handler of the harvest event, by its stage (the jump table 0x55dbc0 after the code): the building
   harvestBld, its plant harvestPlant and the worker harvestWorker; a missing plant or one another event holds (fallId)
   lets the worker leave the building's group (0x524260) and frees the record. Stage 0 waits for the plant message slot,
   then in the building's scene plays the cutscene "Ernten_start_<tree>" ("%slocations/<type>/<script>_<type>.esc" at
   the spot "sp_<worker>", the worker's scene character runs it), else drops the slot; due in a second. Stage 1: due in
   the plant's state x the goods' work time / 4 minutes. Stage 2 stops the script and plays "Ernten_end_<tree>"; due in
   ten minutes. Stage 3 clears the plant (cm_SetPlant), sells the yield 1 << (state - 1) of the goods into the store
   object 0x2a (0x4c4880), posts the next harvest order (message 0x28, ai_SendJobOrders' kind) for the first plant of
   the same tree at the same or a later state within the tree's reach, lets the worker go and frees the record.
   Stages -2 / -1 put the plant back under the event's id and free the record. The case -2 / -1 body and the shared
   tails lie after the last case (0x55db60 ..), the jump table after them: one function, 0x55d5c0 .. 0x55dbd8. */

void he_RunHarvest(AIJOB *e) {
  AIBLD *b;
  AICHAR *c;
  G15PLANT *pl, *plants, *ripe;
  G15TREE *t;
  AIBTYPE *bt;
  EVTSCRIPT *sc;
  AIOBJ *store;
  AIGOOD *g;
  struct CHARACTER *ch;

  int i, size;
  char spot[0x40];
  char path[0x80];
  char name[0x80];

  b = gm_BuildQuery(1, 1, e->harvestBld);
  if (b == 0) {
    he_FreeEvent(e);
    return;
  }
  plants = b->plants;
  pl = veg_FindPlantId(plants, e->harvestPlant);
  c = gm_FindChar(e->harvestWorker);
  if (pl == 0 || c == 0 || (pl->fallId != -1 && pl->fallId != e->id)) {
    if (c != 0)
      sv_MoveToGroup(b, 0, c->id, 0);
    he_FreeEvent(e);
    return;
  }
  ch = c->scene;
  t = veg_FindType(pl->type);
  switch (e->stage) {
    AIMSG m;

  case 0:
    if (cm_GetSlotState(e->harvestSlot) == 0)
      return;
    if (d3_CurrentScene == init_BuildingSceneUniverse(b)) {
      struct VFSDIR *dir;
      bt = &ai_BTypes[b->type];
      sprintf(name, "Ernten_start_%s", t->name);
      sprintf(path, "%slocations/%s/%s_%s.esc", evt_Path, bt->name, name,
              bt->name);
      if (vfs_FindFile(path, vfs_Root, &dir) != 0 &&
          (sc = evt_LoadScript(path)) != 0) {
        sprintf(spot, "sp_%i", e->harvestWorker);
        evt_RunScriptArgs(sc, 3, spot, pl->obj, pl->state / t->states);
        sc->character = ch;
        ch->scriptId = sc->id;
        e->harvestScript = sc->id;
      }
    } else
      e->harvestSlot = -1;
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0, 1);
    e->stage++;
    break;
  case 1:
    e->harvestSlot = -1;
    g = (&ai_Goods[pl->type]);
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, (int)(pl->state * g->workTime * 0.25), 0);
    e->stage++;
    return;
  case 2:
    if (e->harvestScript != -1)
      evt_Stop(evt_FindById(e->harvestScript));
    if (d3_CurrentScene == init_BuildingSceneUniverse(b)) {
      struct VFSDIR *dir;
      bt = &ai_BTypes[b->type];
      sprintf(name, "Ernten_end_%s", t->name);
      sprintf(path, "%slocations/%s/%s_%s.esc", evt_Path, bt->name, name,
              bt->name);
      if (vfs_FindFile(path, vfs_Root, &dir) != 0 &&
          (sc = evt_LoadScript(path)) != 0) {
        sprintf(spot, "sp_%i", e->harvestWorker);
        evt_RunScriptArgs(sc, 3, spot, pl->obj, pl->state / t->states);
        sc->character = ch;
        ch->scriptId = sc->id;
        e->harvestScript = sc->id;
      }
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 10, 0);
    e->stage++;
    return;
  case 3:
    cm_SetPlant(e->harvestBld, pl->x, pl->z, 0, 0, -1);
    store = gm_Query(b->objList, 2, 0, 0x2a, 6);
    if (store != 0)
      cm_SendExSellObject(store->objId, -1, pl->type, 1 << (pl->state - 1),
                          ai_OwnPlayer, 0);
    ripe = 0;
    for (i = 0; i < 0x40; i++) {
      if (plants[i].state != -1 && plants[i].id != e->harvestPlant &&
          plants[i].state >= pl->state && pl->type == plants[i].type &&
          pl->x < t->size + plants[i].x + 2 &&
          pl->x > plants[i].x - (size = t->size) - 2 &&
          pl->z < size + plants[i].z + 2 && pl->z > plants[i].z - size - 2) {
        ripe = &plants[i];
        break;
      }
    }
    if (ripe != 0) {
      i = ripe->id;
      memset(&m, 0, sizeof(m));
      m.type = 0x28;
      m.to = ai_Chars[e->chr].netId;
      m.nIds = 1;
      m.fromId = b->id;
      m.time = ai_Time;
      m.arg[0] = b->id;
      m.reserved14 = 0;
      m.arg[3] = i;
      m.arg[1] = e->harvestWorker;
      m.flags = 1;
      cm_SendLongMessage(&m);
    }
    sv_MoveToGroup(b, 0, c->id, 0);
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    cm_SetPlant(e->harvestBld, pl->x, pl->z, pl->type, 0, e->id);
    he_FreeEvent(e);
    return;
  }
}
/* 0x55dbe0, the run handler of the dismissal event 0x31 ("Entlassen"): stages -2 / -1 free the record, a later stage
   leaves it. At stage 0 the worker AIJOB.dismissWorker (missing or dead: stage -1) loses its building (AICHAR.bld is sent
   as 0); the building's owner's liking of it drops to -30 at most (cm_SendRelations by -30 - the liking when that is
   above -30, else by 0). The worker is cleared and halted and sent home (gm_CharacterHome: to its home object, else
   into the building); the record is freed */
void he_RunDismissal(AIJOB *ev) {
  AIJOB *d = ev;
  AICHAR *c;
  int drop = 0;
  int homeBld, homeObj;

  switch (ev->stage) {
  case -2:
  case -1:
    he_FreeEvent(ev);
    break;
  case 0:
    c = gm_FindChar(d->dismissWorker);
    if (c == 0 || c->health == 0) {
      ev->stage = -1;
      return;
    }
    drop = 0;
    if (c->bld != 0) {
      cm_BeginFieldBlock(c, c->netId);
      cm_AddFieldValue(4, 1, (char *)&c->bld - cm_FieldObject, &drop);
      cm_SendFieldValues();
      if (gm_Opinion(c->bld->owner, c->id) > -30)
        drop = -30 - gm_Opinion(c->bld->owner, c->id);
      cm_SendRelations(ai_Chars[c->bld->owner].netId, c->netId, drop, 1);
    }
    cm_SendCharClear(c->netId, 0, 0);
    cm_SendCharHalt(c->netId);
    if (gm_CharacterHome(c, &homeBld, &homeObj) != 0) {
      if (homeObj != -1)
        cm_SendChrGotoBuilding(c->netId, homeBld, homeObj, 0, 0, "Entlassen");
      else
        cm_SendChrGotoBuilding(c->netId, homeBld, -1, 0, 1, "Entlassen");
    }
    he_FreeEvent(ev);
    break;
  }
}
#define HE_PROMOTION_BIT                                                       \
  0x1000000 /* bit 24 of AICHAR.flags1cc: the promotion alloc handler 0x55dd70 sets it, the run handler 0x55de30 clears it (cm_SendSetField(id, 0x1cc, 4, bit, 0)); the meaning is a reasoned guess */

/* 0x55dd70, the allocation handler of the event type 0x32 (the promotion, its run handler 0x55de30): when another record of
   the type 0x32 is already running for the same figure (+0xac) this one is freed; else +0xb0 = -1, the due clock is now + 1
   second and a figure that does not exist frees the record; a record with the option bit 2 sends the field 0x1cc / 4 /
   HE_PROMOTION_BIT to the figure */

void he_AllocEvent32(AIJOB *j) {
  AIJOB *e;
  AICHAR *p;

  for (e = he_FindEvent(1, 0, 0x32); e != 0; e = he_NextEvent()) {
    if (e != j && j->ownerCh == e->ownerCh) {
      he_FreeEvent(j);
      return;
    }
  }
  j->dropSlot = -1;
  j->end = ai_Time;
  gm_AddTime(&j->end, 0, 0, 1);
  p = gm_FindChar(j->ownerCh);
  if (p == 0) {
    he_FreeEvent(j);
    return;
  }
  if ((j->opts & 2) != 0)
    cm_SendSetField(p->netId, 0x1cc, 4, HE_PROMOTION_BIT, 0);
}
/* 0x55de30, the run handler of the promotion event 0x32 (its alloc handler he_AllocEvent32), by its stage (the jump
   table 0x55e168 after the code); it waits for the event's send slot, needs the character AIJOB.ownerCh (missing: freed)
   and, while the character's model stands in a building, that it is the event's building AIJOB.from. Stage 0: with the
   option 2 the old rank is dropped (gm_DropRank, its slot to dropSlot). Stage 1 (not with the option 4): once the drop
   is sent the event is posted (cm_SendExSetHE 2). Stage 2 stops the script the scene character runs. Stage 3, once it
   runs none: the scene character is made anew in its scene at its place and angles (gm_CreateCharModel, keeping its
   groups and the object in its right hand) and plays "Effekte/befoerdern.esc" there. Stages 2 / 3 without a scene
   character and 3 / -2 / -1 end the event: with the option 2 HE_PROMOTION_BIT is cleared again, the record is freed */
void he_RunPromotion(AIJOB *e) {
  AICHAR *c;
  AIBLD *b;
  struct CHARACTER *ch;
  EVTSCRIPT *sc;
  char *s, *d;
  int group, scriptGroup;
  D3VECTOR4 pos;
  D3VECTOR4 rot;

  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  c = gm_FindChar(e->ownerCh);
  if (c == 0) {
    he_FreeEvent(e);
    return;
  }
  if (c->scene != 0 && (b = gm_FindBuildingById(e->from)) != 0 &&
      c->scene->group != b->id)
    return;
  switch (e->stage) {
  case 0:
    if ((e->opts & 2) != 0)
      e->dropSlot = gm_DropRank(c);
    e->stage++;
    return;
  case 1:
    if ((e->opts & 4) != 0)
      return;
    if (e->dropSlot != -1 && cm_GetSlotState(e->dropSlot) == 0)
      return;
    e->dropSlot = -1;
    e->exSlot = cm_SendExSetHE(2, e);
    return;
  case 2:
    if (c->scene == 0) {
      if ((e->opts & 2) != 0)
        cm_SendSetField(c->netId, 0x1cc, 4, 0, HE_PROMOTION_BIT);
      he_FreeEvent(e);
      return;
    }
    if (c->scene->scriptId != -1)
      evt_Stop(evt_FindById(c->scene->scriptId));
    e->stage++;
    return;
  case 3:
    if (c->scene->scriptId != -1)
      return;
    if (c->scene != 0) {
      int saved = d3_CurrentScene;
      int scene = d3t_SceneIndex(c->scene->scene);
      char hand[0x80] = "";

      d3if_SelectScene(scene, 1);
      ch = c->scene;
      pos.x = ch->obj->pos.x;
      pos.y = ch->obj->pos.y;
      pos.z = ch->obj->pos.z;
      rot.x = ch->obj->rotation.x;
      rot.y = ch->obj->rotation.y;
      rot.z = ch->obj->rotation.z;
      group = ch->group;
      scriptGroup = ch->scriptGroup;
      s = ch->handObject;
      d = hand;
      while ((*d++ = *s++) != 0)
        ;
      ch_Delete(ch);
      c->scene = 0;
      c->ownName[0] = 0;
      c->scene = gm_CreateCharModel(c, scene, &pos.v, &rot.v, 0, 0);
      if (c->scene != 0) {
        c->scene->group = group;
        c->scene->scriptGroup = scriptGroup;
        if (hand[0] != 0)
          ch_SetHandObject(c->scene, 2, hand);
        sc = evt_Load("Effekte/befoerdern.esc");
        if (sc != 0) {
          evt_RunScriptArgs(sc, 5, (int)pos.x, (int)pos.y, (int)pos.z, 0x28,
                            0xb4);
          if (scriptGroup != -1)
            sc->group = scriptGroup;
          else
            sc->group = group;
          sc->ownScene = 1;
        }
      }
      d3if_SelectScene(saved, 1);
    }
    if ((e->opts & 2) != 0)
      cm_SendSetField(c->netId, 0x1cc, 4, 0, HE_PROMOTION_BIT);
    he_FreeEvent(e);
    return;
  case -2:
  case -1:
    if ((e->opts & 2) != 0)
      cm_SendSetField(c->netId, 0x1cc, 4, 0, HE_PROMOTION_BIT);
    he_FreeEvent(e);
    return;
  }
}
/* 0x55e180, the allocation handler of the event 0x33 (a worker quits, he_RunWorkerQuits): the character AIJOB.ownerCh
   must exist and not be kind 0x14, else the record is freed; the due clock is the start clock */

void he_AllocWorkerQuits(AIJOB *ev) {
  AICHAR *c;

  c = gm_FindChar(ev->ownerCh);
  if (c != 0 && c->kind != 0x14) {
    ev->end = ev->start;
    return;
  }
  he_FreeEvent(ev);
}
/* 0x55e1d0, the run handler of the event 0x33 (its alloc handler he_AllocWorkerQuits), a worker who quits: stages -2 / -1 free
   the record, a later stage leaves it. At stage 0 the character AIJOB.ownerCh must still work in a building (AICHAR.bld)
   whose owner it likes -26 or less (gm_Opinion), else the record is freed. It is cleared and halted, loses its building
   (AICHAR.bld sent as 0) and is sent home (gm_CharacterHome: to its home object, else into the building; the walk tag
   "Entlassen"); the owner's liking of it drops by 5 and the owner gets the message box 0x1bac (the character, the
   building; 0x5f2, quick jump to the building's main object, "_NACHRICHTEN_HS_01"); the record is freed */
void he_RunWorkerQuits(AIJOB *ev) {
  AICHAR *c;
  AIBLD *b;
  AIOBJ *o;
  int v = 0;
  int homeBld, homeObj;
  char text[0x400];

  switch (ev->stage) {
  case -2:
  case -1:
    he_FreeEvent(ev);
    break;
  case 0:
    c = gm_FindChar(ev->ownerCh);
    if (c == 0 || c->bld == 0 || gm_Opinion(c->bld->owner, c->id) > -26) {
      he_FreeEvent(ev);
      return;
    }
    cm_SendCharClear(c->netId, 0, 0);
    cm_SendCharHalt(c->netId);
    cm_BeginFieldBlock(c, c->netId);
    cm_AddFieldValue(4, 1, (char *)&c->bld - cm_FieldObject, &v);
    cm_SendFieldValues();
    if (gm_CharacterHome(c, &homeBld, &homeObj) != 0) {
      if (homeObj != -1)
        cm_SendChrGotoBuilding(c->netId, homeBld, homeObj, 0, 0, "Entlassen");
      else
        cm_SendChrGotoBuilding(c->netId, homeBld, -1, 0, 1, "Entlassen");
    }
    v = -5;
    cm_SendRelations(ai_Chars[c->bld->owner].netId, c->netId, v, 1);
    o = gm_BuildingMainObject(c->bld);
    txt_Format(text, 0x1bac, c->id, c->bld);
    b = c->bld;
    he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, text, 0, 0x5f2, b->id,
                           o->objId, 0, "_NACHRICHTEN_HS_01");
    he_FreeEvent(ev);
    break;
  }
}
/* 0x55e3a0, the allocation handler of the events 0x24, 0x34, 0x54 and 0x94: the due clock is the start clock */

void he_AllocDueIsStart(AIJOB *ev) { ev->end = ev->start; }
/* 0x55e3d0, the run handler of the event 0x34 (its alloc handler he_AllocDueIsStart), a worker who steals: stages -2 / -1 free
   the record, a later stage leaves it. At stage 0 the character AIJOB.ownerCh must work in a building (AICHAR.bld)
   whose owner it likes -26 or less (gm_Opinion), else the record is freed. One good of the building's store (the
   object 0x2a, else 0x116; up to 0x20 goods of its list) is picked at random and taken out of the store
   (cm_SendExSellObject to nobody, one piece); the event character gets the message box 0x1bb9 (the building, the
   good's name 0x9a8 + 2 * good, its price; 0x5f2, quick jump to the building's main object, "_NACHRICHTEN_HS_09");
   the record is freed (reasoned: a theft, from the dislike and the good leaving the store unpaid) */
void he_RunWorkerTheft(AIJOB *e) {
  AICHAR *c;
  AIBLD *b;
  AIOBJ *store, *o, *g;
  AIOBJ *goods[0x20];
  int n, price;
  char text[0x400];

  switch (e->stage) {
  case -2:
  case -1:
    he_FreeEvent(e);
    break;
  case 0:
    c = gm_FindChar(e->ownerCh);
    if (c == 0 || (b = c->bld) == 0 || gm_Opinion(b->owner, c->id) > -26) {
      he_FreeEvent(e);
      return;
    }
    store = gm_Query(b->objList, 2, 6, 0, 0x2a);
    if (store == 0)
      store = gm_Query(b->objList, 2, 6, 0, 0x116);
    o = gm_BuildingMainObject(b);
    if (store != 0) {
      n = 0;
      memset(goods, 0, sizeof(goods));
      for (g = gm_Query(store->list, 1, 5); g != 0; g = gm_QueryNext())
        goods[n++] = g;
      if (n != 0 && (g = goods[util_Random(n)]) != 0) {
        price = (int)gm_GoodsPrice(g->id, ai_OwnPlayer);
        cm_SendExSellObject(-1, store->objId, g->id, 1, ai_OwnPlayer, 0);
        txt_Format(text, 0x1bb9, c->bld, 0x9a8 + 2 * g->id, price);
        he_MessageBoxQuickjump(ai_Chars[e->chr].netId, -1, text, 0, 0x5f2,
                               b->id, o->objId, 0, "_NACHRICHTEN_HS_09");
      }
    }
    he_FreeEvent(e);
    break;
  }
}
/* 0x55e5c0, the allocation handler of the event 0x38 (he_RunEvent38): the due clock is the game clock plus 4 hours */

void he_AllocEvent38(AIJOB *ev) {
  ev->end = ai_Time;
  gm_AddTime(&ev->end, 4, 0, 0);
}
/* 0x55e600, the run handler of the event 0x38 (its alloc handler he_AllocEvent38 makes it due in 4 hours): stages -2 / -1
   free the record, a later stage leaves it. At stage 0 the building AIJOB.from (none: freed) is looked up and the
   event character's relation to every character working there (AICHAR.bld) changes by 20 times AIJOB.ev38Amount /
   gm_PlayerFactor (1000, the own player); an event character of the kind 6 / 7 (a player) gets the message box
   0x19ab (the building; 0x5ec, quick jump to it); the record is freed */
void he_RunEvent38(AIJOB *e) {
  AIJOB *x = e;
  AIBLD *b;
  int i, d;
  char text[0x100];

  switch (e->stage) {
  case -2:
  case -1:
    he_FreeEvent(e);
    break;
  case 0:
    b = gm_BuildQuery(1, 1, e->from);
    if (b == 0) {
      he_FreeEvent(e);
      return;
    }
    d = x->ev38Amount / gm_PlayerFactor(1000, ai_OwnPlayer) * 20;
    for (i = 0; i < 768; i++) {
      if (ai_Chars[i].id != 0xffff && ai_Chars[i].bld == b)
        cm_SendRelations(ai_Chars[e->chr].netId, ai_Chars[i].netId, d, 0);
    }
    if (ai_Chars[e->chr].kind == 6 || ai_Chars[e->chr].kind == 7) {
      txt_Format(text, 0x19ab, b);
      he_MessageBoxQuickjump(ai_Chars[e->chr].netId, ai_Chars[e->chr].netId,
                             text, 0, 0x5ec, b->id, -1, 0, (char *)0);
    }
    he_FreeEvent(e);
    break;
  }
}
/* 0x55e730, the run handler of the event 0x39 (AIJOB.bail*, its alloc handler he_AllocEvent39_3e): the held character
   and the payer (gm_FindChar; either gone: the record is freed). A payer that is no player (kind 6 / 7) waits for
   the due time and then decides (stage 2); stages -2 / -1 close the slot and free the record. Stage 0 opens
   "Berufe\Messagebox_Meisterpruefung" (0x5ec) and prints the request 0x19b2 (the held character, the amount);
   stage 1 reads the answer: yes tells the held character 0x19b3 (the payer) and frees it (message 0x5b takes its
   held rounds back), no tells it 0x19b4 (the payer, the amount). Stage 2 pays by gm_LikingChance (the amount
   against 16000 per held round): paid as yes, refused as no and the held character's relation to the payer
   changes (cm_SendRelations 10, 1) */
void he_RunEvent39(AIJOB *e) {
  AIJOB *x = e;
  AICHAR *held, *payer;
  char text[0x100];

  held = gm_FindChar(x->bailHeld);
  payer = gm_FindChar(x->bailPayer);
  if (held == 0 || payer == 0) {
    he_FreeEvent(e);
    return;
  }
  if (payer->kind != 6 && payer->kind != 7) {
    if (gm_CompareTime(&e->end, &ai_Time) > 0)
      return;
    e->stage = 2;
  }
  switch (e->stage) {
  case 0:
    he_OpenEventSlot(e, 0, 0, "Berufe\\Messagebox_Meisterpruefung", 0x5ec);
    d2_SetForm(e->slot->win, 0);
    io_PrintText(0x19b2, held->id, x->bailAmount, held->id, held->id);
    e->stage++;
    return;
  case 1:
    if (d2_ClickedForm != e->slot->win || d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      txt_Format(text, 0x19b3, payer->id);
      he_ShowNews(held->netId, held->netId, text, 0, 0x5fa, 0);
      cm_SendMessage5b(held->netId, -held->heldRounds, 0);
    } else if (d2_ClickedId == 1) {
      txt_Format(text, 0x19b4, payer->id, x->bailAmount);
      he_ShowNews(held->netId, held->netId, text, 0, 0x5fa, 0);
    }
    /* fall through: the answer closes the slot */
  case -2:
  case -1:
    he_ReleaseSlot(e);
    he_FreeEvent(e);
    break;
  case 2:
    if (gm_LikingChance(held->id, payer->id, x->bailAmount,
                        held->heldRounds * 16000) != 0) {
      txt_Format(text, 0x19b3, payer->id);
      he_ShowNews(held->netId, held->netId, text, 0, 0x5fa, 0);
      cm_SendMessage5b(held->netId, -held->heldRounds, 0);
    } else {
      txt_Format(text, 0x19b4, payer->id, x->bailAmount);
      he_ShowNews(held->netId, held->netId, text, 0, 0x5fa, 0);
      cm_SendRelations(held->netId, payer->netId, 10, 1);
    }
    he_FreeEvent(e);
    break;
  }
}

/* 0x55e9d0, the allocation handler of the daily routine event 0x3a (he_PostEvent3a posts it at the start of the day): its words +0xb0 = 3 and +0xac = 0, the start and end clocks are now, the end clock set to 6:15 (gm_SetTime) */
void he_AllocRoutine(AIJOB *ev) {
  AIJOB *r = ev;

  r->routineStep = 3;
  r->routineChrIdx = 0;
  gm_ClockSeason(&ai_Time);
  ev->end = ai_Time;
  ev->start = ai_Time;
  gm_SetTime(&ev->end, 6, 0xf, 0);
}
/* 0x55ea60, where the character `p` works: 1 with *bldId its current building's id and *contact the object to go
   to there (-1: none), 0 when it is not at work now: no character, the kinds 0xd / 0xe, no building or model, a busy
   job kind (0x3f, 0x40, 0x48, 0x3c, 0x49, 0x44, 0x62, 0x61, 0x65, 0x64, 0x14, 0x75, 0x1a, 0x18, 0xa1) or held
   (AICHAR.heldRounds). In a home (gm_IsHomeType) the contact is the object 0x37 (the job kinds 3 / 8 / 9) or 0xfd of
   the building's objects, none when it is of the type 0xfd; 0 when the model's script group is that object.
   Elsewhere 0 when the model was sent to this building already, else the contact is the building's main object */
int he_FigureContact(AICHAR *p, int *bldId, int *contact) {
  int id = -1;
  AIOBJ *o;
  unsigned char kind;

  if (p == 0 || p->kind == 0xd || p->kind == 0xe || p->bld == 0 ||
      p->scene == 0)
    return 0;
  kind = p->jobKind;
  if (kind == 0x3f || kind == 0x40 || kind == 0x48 || kind == 0x3c ||
      kind == 0x49 || kind == 0x44 || kind == 0x62 || kind == 0x61 ||
      kind == 0x65 || kind == 0x64 || kind == 0x14 || kind == 0x75 ||
      kind == 0x1a || kind == 0x18 || kind == 0xa1)
    return 0;
  if (p->heldRounds != 0)
    return 0;
  if (gm_IsHomeType(p->bld) == 0) {
    if (p->scene->group == p->bld->id)
      return 0;
    o = gm_BuildingMainObject(p->bld);
    if (o == 0)
      return 0;
  } else {
    if (p->jobKind == 3 || p->jobKind == 8 || p->jobKind == 9)
      o = gm_Query((void *)p->bld->objList, 1, 0, 0x37);
    else
      o = gm_Query((void *)p->bld->objList, 1, 0, 0xfd);
    if (o == 0)
      goto done;
    if (o->objId == p->scene->scriptGroup)
      return 0;
    if (o->type == 0xfd)
      goto done;
  }
  id = o->objId;
done: /* no contact object: -1 */
  *bldId = p->bld->id;
  *contact = id;
  return 1;
}
/* 0x55eba0, where the character `p` is to be found: 1 with *bldId the building, *objId the object there (-1: none)
   and, for a `scene` pointer, the scene to show (init_BuildingSceneUniverse for a home, init_ObjectSceneUniverse for
   the object, else -1); 0 for the kinds 0xd / 0xe and, in a building, for the building kinds 4, 0x10, 0x13, 0x1d,
   0x1e, the busy job kinds (as he_FigureContact) or held (AICHAR.heldRounds). Without an own building (bld2) the
   place is its home (gm_CharacterHome; the scene 0 when neither applies). In a home building the object is 0x2c (else
   0x109; none: 0); otherwise its own building bld2 and its home object (gm_HomeObject), unless it is in a home */
int he_FindFigurePlace(AICHAR *p, int *bldId, int *objId, int *scene) {
  AIOBJ *o = 0;
  AIBLD *b = 0;
  int id = -1;
  unsigned char k;
  AIBLD *home;
  AIBTYPE *bt;

  if (p->kind == 0xd || p->kind == 0xe)
    return 0;
  if (p->bld != 0) {
    bt = &ai_BTypes[p->bld->type];
    if (bt->kind == 4 || bt->kind == 0x10 || bt->kind == 0x13 ||
        bt->kind == 0x1d || bt->kind == 0x1e)
      return 0;
    k = p->jobKind;
    if (k == 0x3f || k == 0x40 || k == 0x48 || k == 0x3c || k == 0x49 ||
        k == 0x44 || k == 0x62 || k == 0x61 || k == 0x65 || k == 0x64 ||
        k == 0x14 || k == 0x75 || k == 0x1a || k == 0x18 || k == 0xa1)
      return 0;
    if (p->heldRounds != 0)
      return 0;
  }
  if (p->bld2 == 0) {
    home = gm_CharacterHome(p, bldId, objId);
    if (home == 0)
      return 0;
    if (scene != 0) {
      o = gm_FindObjectInst(*objId);
      if (gm_IsHomeType(home) != 0) {
        *scene = init_BuildingSceneUniverse(home);
        return 1;
      }
      if (o != 0) {
        *scene = init_ObjectSceneUniverse(o);
        return 1;
      }
      *scene = 0;
      return 1;
    }
  } else {
    if (p->bld != 0 && gm_IsHomeType(p->bld) != 0) {
      o = gm_Query((void *)p->bld->objList, 1, 0, 0x2c);
      if (o == 0) {
        o = gm_Query((void *)p->bld->objList, 1, 0, 0x109);
        if (o == 0)
          return 0;
      }
      b = p->bld;
    }
    if (o == 0 && p->bld2 != 0 && (p->bld == 0 || gm_IsHomeType(p->bld) == 0)) {
      o = gm_HomeObject(p->bld2);
      b = p->bld2;
    }
    if (b == 0)
      return 0;
    if (o != 0)
      id = o->objId;
    if (scene != 0) {
      if (gm_IsHomeType(b) != 0)
        *scene = init_BuildingSceneUniverse(b);
      else if (o != 0)
        *scene = init_ObjectSceneUniverse(o);
      else
        *scene = -1;
    }
    *bldId = b->id;
    *objId = id;
  }
  return 1;
}

/* 0x55ee40, picks one of the `n` buildings `blds` for the character `c` (the inns of he_StepWalk's walk):
   each one without the flag 1 of flags5a, with a 3D object and the character's own building (bld2) placed, scores
   1 - its distance to that building / the largest such distance (at least 0.01) plus 0.0125 times its skill 9
   (gm_BuildingSkill); the best one (the first when none beats -1) gives *bldId its id and *objId its object 0x120's
   id; 1 when that building has a 3D object */
int he_PickNearBuilding(AICHAR *c, int n, AIBLD **blds, int *bldId,
                        int *objId) {
  float maxDist = 0.01f;
  float best = -1.0f;
  float score[0x20];
  float dx, dy, dz, d;
  D3OBJECT *a, *h;
  AIOBJ *o;
  int i, pick = 0;

  for (i = 0; i < n; i++) {
    if ((blds[i]->flags5a & 1) == 0 && blds[i]->object != 0 && c->bld2 != 0 &&
        c->bld2->object != 0) {
      a = blds[i]->object;
      h = c->bld2->object;
      dx = a->pos.x - h->pos.x;
      dy = a->pos.y - h->pos.y;
      dz = a->pos.z - h->pos.z;
      d = (float)sqrt(dx * dx + dy * dy + dz * dz);
      score[i] = d;
      if (d > maxDist)
        maxDist = d;
    }
  }
  for (i = 0; i < n; i++) {
    score[i] = (float)(gm_BuildingSkill(blds[i], 9, 1) * 0.0125 +
                       (1.0f - score[i] / maxDist));
    if (best < score[i]) {
      best = score[i];
      pick = i;
    }
  }
  o = gm_Query(blds[pick]->objList, 1, 0, 0x120);
  *bldId = blds[pick]->id;
  *objId = o->objId;
  return blds[pick]->object != 0;
}
/* 0x55efc0, the run handler of the daily routine event 0x3a (AIJOB.routine*, its alloc handler he_AllocRoutine): stages
   -2 / -1 free the record. Every character with a job or a title, a building and a model counts.
   Stage 0, the morning: the first character not yet sent (flags1c8 bit 0x1000) whose workplace (he_FigureContact)
   is not where it was sent last is sent to work: into a home or a building without a 3D object it moves at once
   ("dummy_EINGANG"), else, unless its building's owner is a player (kind 6 / 7) or 0x20 characters are in the scene,
   it walks there ("Go to work") once the hour is one before the day start (gm_DayStartHours) or it is 7000 or less
   away; a sent one makes the event due in 5 minutes. From the day start every remaining one moves at once; then the
   event is due at the day end (gm_DayEndHours) in stage 1.
   Stage 1, the evening (the day it started only, not with the game flag 0x80): of up to 0x20 inns with an owner and
   a 3D object, the characters not at their place (he_FindFigurePlace; buildings of the kinds 4, 0x10, 0x13 do not
   count) and not yet sent home (bit 0x800) leave: those of the players' buildings all, then the first other one;
   a rich one (goods worth over 3200) goes to an inn half the time (he_PickNearBuilding, "Go to wirtshaus"), else
   home ("Go home"; up to 0x40 of the players'); with any sent, the event is due in 5 minutes. Two hours past the day
   end every remaining one with an own building moves at once (to the inn, its place or the door "dummy_TUER") and
   the record is freed */
void he_RunRoutine(AIJOB *ev) {
  AIJOB *r = ev;
  AICHAR *c;
  AIBLD *b;
  AIBLD *inns[0x20];
  AIBTYPE *bt;
  D3VECTOR4 from, to;
  float dx, dy, dz, dist;
  int count = 0;
  int season, i, n;

  season = gm_ClockSeason(&ai_Time);
  switch (ev->stage) {
  case -2:
    he_FreeEvent(ev);
    return;
  case -1:
    he_FreeEvent(ev);
    return;
  case 0:
    for (i = 0; i < 768 && count < 1; i++) {
      int bld, contact;

      c = &ai_Chars[i];
      if ((c->title != 0 || c->jobId != 0) && c->bld != 0 && c->scene != 0 &&
          (c->flags1c8 & 0x1000) == 0 &&
          he_FigureContact(c, &bld, &contact) != 0 && bld != c->scene->group) {
        if (gm_IsHomeType(c->bld) == 0 && c->bld->object != 0) {
          if (ai_Chars[c->bld->owner].kind != 6 &&
              ai_Chars[c->bld->owner].kind != 7 && ch_Count(0, 0) < 0x20) {
            b = gm_FindBuildingById(c->scene->group);
            dist = 0.0f;
            if (b != 0 && b->object != 0) {
              d3_PointToWorld(c->bld->object, &c->bld->object->pos, &from.v);
              d3_PointToWorld(b->object, &b->object->pos, &to.v);
              dx = from.x - to.x;
              dy = from.y - to.y;
              dz = from.z - to.z;
              dist = (float)sqrt(dx * dx + dy * dy + dz * dz);
            }
            if (dist < 7000.0f &&
                (float)ai_Time.hour < gm_DayStartHours[season] - 1.0f) {
              cm_SendCharHalt(c->netId);
              cm_SendChrGotoBuilding(c->netId, bld, contact, 0, 0,
                                     "Go to work");
              c->flags1c8 |= 0x1000;
              count++;
            }
          }
        } else {
          cm_SendCharHalt(c->netId);
          cm_RequestChrMoveToUniverse(c->netId, bld, contact, "dummy_EINGANG");
          cm_RequestChrMove(c->netId, bld, contact, ch_EmptyName);
          c->flags1c8 |= 0x1000;
        }
        r->routineChrIdx = i;
      }
    }
    if (count != 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 5, 0);
    }
    if ((float)ai_Time.hour >= gm_DayStartHours[season]) {
      for (i = 0; i < 768; i++) {
        int bld, contact;

        if ((ai_Chars[i].title != 0 || ai_Chars[i].jobId != 0) &&
            ai_Chars[i].bld != 0 && ai_Chars[i].scene != 0 &&
            (ai_Chars[i].flags1c8 & 0x1000) == 0 &&
            he_FigureContact(&ai_Chars[i], &contact, &bld) != 0 &&
            contact != ai_Chars[i].scene->group) {
          cm_SendCharHalt(ai_Chars[i].netId);
          cm_RequestChrMoveToUniverse(ai_Chars[i].netId, contact, bld,
                                      "dummy_EINGANG");
          cm_RequestChrMove(ai_Chars[i].netId, contact, bld, ch_EmptyName);
          ai_Chars[i].flags1c8 |= 0x1000;
        }
      }
      ev->end = ai_Time;
      gm_SetTime(&ev->end, (unsigned char)gm_DayEndHours[season], 0, 0);
      ev->stage = 1;
      r->routineChrIdx = 0;
    }
    return;
  case 1:
    if ((ai_GameFlags & 0x80) != 0 || ai_Time.year != ev->start.year) {
      he_FreeEvent(ev);
      return;
    }
    b = gm_BuildQuery(1, 5, 0x16);
    n = 0;
    for (; b != 0; b = gm_BuildNext()) {
      if (n >= 0x20)
        break;
      if (b->owner != 0xffff && b->object != 0)
        inns[n++] = b;
    }
    for (i = 0; i < 768; i++) {
      int place, obj;

      c = &ai_Chars[i];
      if ((c->title != 0 || c->jobId != 0) && c->bld != 0 && c->scene != 0) {
        bt = &ai_BTypes[c->bld->type];
        if (bt->kind != 4 && bt->kind != 0x10 && bt->kind != 0x13 &&
            he_FindFigurePlace(c, &place, &obj, 0) != 0 &&
            (place != c->scene->group || obj != c->scene->scriptGroup) &&
            (c->flags1c8 & 0x800) == 0 &&
            (ai_Chars[c->bld->owner].kind == 6 ||
             ai_Chars[c->bld->owner].kind == 7)) {
          cm_SendCharHalt(c->netId);
          if (n != 0 && gm_GetGoodsValue(c) > 0xc80 &&
              (short)util_Random(2) != 0) {
            if (he_PickNearBuilding(c, n, inns, &place, &obj) != 0)
              cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0,
                                     "Go to wirtshaus");
          } else if (obj == -1) {
            cm_SendChrGotoBuilding(c->netId, place, obj, 0, 1, "Go home");
          } else if (count < 0x40) {
            cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0, "Go home");
          }
          c->flags1c8 |= 0x800;
          cm_SendSetField(c->netId, 0x1c8, 4, 0x800, 0x1000);
          r->routineChrIdx = i;
          count++;
        }
      }
    }
    for (i = 0; i < 768 && count < 1; i++) {
      int place, obj;

      c = &ai_Chars[i];
      if ((c->title != 0 || c->jobId != 0) && c->bld != 0 && c->scene != 0) {
        bt = &ai_BTypes[c->bld->type];
        if (bt->kind != 4 && bt->kind != 0x10 && bt->kind != 0x13 &&
            he_FindFigurePlace(c, &place, &obj, 0) != 0 &&
            (place != c->scene->group || obj != c->scene->scriptGroup) &&
            (c->flags1c8 & 0x800) == 0) {
          cm_SendCharHalt(c->netId);
          if (n != 0 && gm_GetGoodsValue(c) > 0xc80 &&
              (short)util_Random(2) != 0) {
            if (he_PickNearBuilding(c, n, inns, &place, &obj) != 0)
              cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0,
                                     "Go to wirtshaus");
          } else if (obj == -1) {
            cm_SendChrGotoBuilding(c->netId, place, obj, 0, 1, "Go home");
          } else {
            cm_SendChrGotoBuilding(c->netId, place, obj, 0, 0, "Go home");
          }
          c->flags1c8 |= 0x800;
          cm_SendSetField(c->netId, 0x1c8, 4, 0x800, 0x1000);
          count++;
          r->routineChrIdx = i;
        }
      }
    }
    if (count != 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 5, 0);
    }
    if ((float)ai_Time.hour > gm_DayEndHours[season] + 2.0f) {
      for (i = 0; i < 768; i++) {
        int bld, contact;

        if ((ai_Chars[i].title != 0 || ai_Chars[i].jobId != 0) &&
            ai_Chars[i].bld != 0 && ai_Chars[i].bld2 != 0 &&
            ai_Chars[i].scene != 0) {
          bt = &ai_BTypes[ai_Chars[i].bld->type];
          if (bt->kind != 4 && bt->kind != 0x10 && bt->kind != 0x13 &&
              he_FindFigurePlace(&ai_Chars[i], &bld, &contact, 0) != 0 &&
              (bld != ai_Chars[i].scene->group ||
               contact != ai_Chars[i].scene->scriptGroup) &&
              (ai_Chars[i].flags1c8 & 0x800) == 0) {
            cm_SendCharHalt(ai_Chars[i].netId);
            if (n != 0 && gm_GetGoodsValue(&ai_Chars[i]) > 0xc80 &&
                (short)util_Random(2) != 0) {
              if (he_PickNearBuilding(&ai_Chars[i], n, inns, &bld, &contact) !=
                  0) {
                cm_RequestChrMoveToUniverse(ai_Chars[i].netId, bld, contact,
                                            "dummy_EINGANG");
                cm_RequestChrMove(ai_Chars[i].netId, bld, contact,
                                  ch_EmptyName);
              }
            } else if (contact != -1) {
              cm_RequestChrMoveToUniverse(ai_Chars[i].netId, bld, contact,
                                          "dummy_EINGANG");
              cm_RequestChrMove(ai_Chars[i].netId, bld, contact, ch_EmptyName);
            } else {
              cm_RequestChrMoveToUniverse(ai_Chars[i].netId, bld, -1,
                                          "dummy_TUER");
            }
            ai_Chars[i].flags1c8 |= 0x800;
            cm_SendSetField(ai_Chars[i].netId, 0x1c8, 4, 0x800, 0x1000);
          }
        }
      }
      he_FreeEvent(ev);
    }
    return;
  }
}
/* 0x55fa20, the allocation handler of the market event 0x3b: the due clock is now, set to 5:00 (gm_SetTime); its copy at +0x60 is that 5:00 clock and the due clock moves one hour later (gm_AddTime (.., 1, 0, 0)) */

void he_AllocMarket(AIJOB *ev) {
  ev->end = ai_Time;
  gm_SetTime(&ev->end, 5, 0, 0);
  ev->clock60 = ev->end;
  gm_AddTime(&ev->end, 1, 0, 0);
}
#define HE_SUPERVISOR_MONEY                                                    \
  5120000 /* the market supervisor tops the player's money up to it */
float gm_StockPrice(int p,
                    int n); /* 0x4ffa10 (f3gm.c; f3gm.h does not declare it) */

/* 0x55fa90, the run handler "he_RunMarktSupervisor" of the market event 0x3b (its alloc handler he_AllocMarket):
   without a market building, or past 20:00, the record is freed; it runs once per new minute count since its last
   run (AIJOB.clock60). Stages below -2 and above 0 do nothing; -2 / -1 give it the player's character
   (he_SetEventChar) and stage 0. Stage 0 tops the player's money up to 5120000 and walks the goods of the stock blocks
   (GMSTOCK, a copy each, sent back as a delta with cm_SendGoodsDelta), scaled by the minutes passed / 60 and 1 / 14:
   the own player's market goods (kinds 0x25 / 0x17) by their market object (gm_FindMarketObject; none: the debug
   text "Could not find markt-lager") buy (below half the stock in store) or sell (above three quarters), the mean
   drifting with the stock; its other goods sell the whole units of the accumulated f2c (a third, at least 1, not
   with the game flag 0x80) or buy 1 .. 3 a quarter of the time; the other players' buildings (1 .. 3, up to the first empty slot) sell from
   their object 0x1db and buy into 0x1dc. Each mean is kept between a quarter (at least 1) and three times the
   demand and reset by a random roll when it strays beyond 1.5 / 2.5 times or below 0.4 / 0.8 times of it; the
   price is refreshed (gm_StockPrice) on most rolls. From 22:00 the record is freed, else it is due in an hour
   @deep s50: 122 -> 2 ins (shape, size equal). Levers that moved it: amount = min(k, n) for pass 2's sold
   amount (amount = n after if (k < n) n = k was copy-propagated into n: the original keeps amount's own
   home); the hourly share in pass 1's form at all sites; one g for the passes; f one local for pass 1 and
   pass 4 with the free capacity read back into it (f memory-live in pass 4 conflicts with g, so the packer
   puts f with amount and pass 3's have, g alone: the original's frame); have per pass (block locals), n
   one local; pass 3's mean as mean + (g - have) * 0.4. Left (order 4): pass 4's s2.mean = (float)(g * 0.5
   + s2.mean) right after cm_SendExSellObject: the original has call; fld g; fmul 0.5; fadd [s2.mean]; add
   esp,0x18; fstp, ours call; fld g; fmul; add esp,0x18; fadd; fstp. c2dag's graph of ours: add esp prio
   32768 (h=4), fadd 229376 after fmul with latency 3 (17/3:7): with latencies the add fills the stall, so
   the original's add must be ready later or its fadd not wait. No lever (= control): every spelling of the
   sum (operand order, (float) placement, 0.5 / .5 / 2.0 / (double), += forms, min(), the clamp after it as
   min / if), (int)f through k first, s2 as pl-block / initialised local, a label before the call or the
   statement (no region effect); 0.5f or g / 2 give fmul dword (fpu 6); the statement before the call: M10.
   c2pass: no tail / adjust pass moves it (the scheduler or the x87 stackifier). flip --want on the three
   lines: no single mutation. climb: 3 rounds, beam 8 (1700 mutants): nothing below 2. prior: s49: 156 -> 122 ins, 964 = 964 instructions,
   size 3479 -> 3463 (the original 3459, padded equal). Levers: the end as if (ai_Time.hour < 22) { next
   run } else he_FreeEvent(ev) (VC6 then cross-jumps the free into the first guard's block as the original:
   the tail hunk and one he_FreeEvent copy gone, 156 -> 137); the rolls' bound as (s.demand * 1.5f) /
   s.mean (without the parentheses VC6 reassociates it into 1.5f / mean * demand: 137 -> 125); the hourly
   share as (minutes * (1.0 / 60)) * (demand * (1.0f / 14)) at the three sites (the fild / fmul 1/60 / fld
   / fmul / fmulp order: 125 -> 122, but the slot hunks grow 106 -> 160). No lever: if / else at the first
   guard, minutes / 60.0, no (float) cast, the bound as < from the other side (167). Left: the frame
   packing only (dcp frame: the original's [esp+0xc] is shared by five of our slots, its [esp+0x20] by two;
   ours minutes at [esp+0x30], the original [esp+0x28]; pass 2's n has a stack home written at each
   definition in ours, the original keeps it in edi and stores only amount = n into [esp+0x10]). Next:
   c2frame --names on the variable sets of the passes (one s / n / k per pass?). */
void he_RunMarketSupervisor(AIJOB *ev) {
  GMSTOCK *rec;
  GMSTOCK s;
  AIOBJ *o, *q, *st;
  AIBLD *b;
  AIGOOD *good;
  int minutes, i, pl, inStore, amount, k, n;
  float g, f;

  if (ai_MarketBuilding == 0) {
    he_FreeEvent(ev);
    return;
  }
  minutes = gm_MinutesBetween(&ev->clock60, &ai_Time);
  if (ai_Time.hour > 20) {
    he_FreeEvent(ev);
    return;
  }
  if (minutes == 0)
    return;
  ev->clock60 = ai_Time;
  switch (ev->stage) {
  case 0:
    break;
  case -2:
  case -1:
    he_SetEventChar(ev, ai_PlayerChar->id);
    ev->stage = 0;
    return;
  default:
    return;
  }

  if (gm_CharCurrency(ai_PlayerChar, ai_OwnPlayer) < HE_SUPERVISOR_MONEY)
    cm_SendMoveGoods(ai_PlayerChar->netId, -1, ai_OwnPlayer,
                     HE_SUPERVISOR_MONEY);

  for (i = 0; i < 0x55; i++) {

    rec = &gm_StockBlocks[ai_OwnPlayer].goods[i];
    if (rec->item == 0)
      continue;
    good = ai_Goods + rec->item;
    s = *rec;
    if (rec->amount == 0 || (good->type != 0x25 && good->type != 0x17))
      continue;
    o = gm_FindMarketObject(s.item);
    if (o == 0) {
      char text[0x100];

      sprintf(text, "he_RunMarktSupervisor(): Could not find markt-lager:%s",
              txt_Ptrs[TXT_OBJECT_NAMES + 2 * s.item]);
      continue;
    }
    q = gm_Query(o->list, 2, 6, 0, s.item);
    if (q != 0)
      inStore = gm_ListAmount(o, q);
    else
      inStore = 0;
    util_Random(10);
    f = (float)(s.stock * (1.0f / 14) * (minutes * (1.0 / 60)));
    f = (util_Random(100) + 80.0f) * f * 0.01f;
    if (f != 0.0f && 1.0f > f)
      f = 1.0f;
    if (inStore < s.stock * 0.5) {
      s.daily[0] = (int)(s.daily[0] + f);
      if (s.mean > s.demand * 0.5)
        cm_SendExSellObject(o->objId, -1, s.item, (int)f, ai_OwnPlayer, 0);
      s.mean += (float)(s.stock * (1.0f / 14) * (minutes * (1.0 / 60))) * 0.8f;
    } else if (inStore > s.stock * 0.75) {
      f = (float)(s.stock * (1.0f / 14) * (minutes * (1.0 / 60)));
      s.mean = s.mean - f * 0.6f;
      s.mean = (float)(s.mean > s.demand * 0.25 ? s.mean : s.demand * 0.25);
      if (1.0f > s.mean)
        s.mean = 1.0f;
      if (1.0f > f)
        f = 1.0f;
      cm_SendExSellObject(-1, o->objId, s.item, (int)f, ai_OwnPlayer, 0);
      s.daily[1] = (int)(s.daily[1] + f);
    }
    if (s.demand * 1.5f < s.mean) {
      if (util_RandomF() > (s.demand * 1.5f) / s.mean)
        s.mean = s.demand * 0.4f;
    } else if (s.demand * 0.4f > s.mean) {
      if (util_RandomF() > s.mean / (s.demand * 0.4f))
        s.mean = s.demand * 1.5f;
    }
    if (util_Random(100) > 10 || ai_Time.hour == 12)
      s.price = gm_StockPrice(ai_OwnPlayer, i);
    cm_SendGoodsDelta(&s, ai_OwnPlayer);
  }

  for (i = 0; i < 0x55; i++) {
    rec = &gm_StockBlocks[ai_OwnPlayer].goods[i];
    if (rec->item == 0)
      continue;
    good = ai_Goods + rec->item;
    if (rec->amount == 0 || good->type == 0x25 || good->type == 0x17)
      continue;
    s = *rec;
    o = gm_FindMarketObject(s.item);
    if (o == 0)
      continue;
    q = gm_Query(o->list, 1, 0, s.item);
    if (q != 0)
      amount = gm_ListAmount(o, q);
    else
      amount = 0;
    util_Random(10);
    g = (float)(s.demand * (1.0f / 14) * (minutes * (1.0 / 60)));
    if (g != 0.0f)
      s.f2c += g;
    if (s.f2c >= 1.0f) {
      n = (int)s.f2c;
      s.f2c = s.f2c - n;
    } else {
      n = 0;
    }
    k = (int)(float)amount;
    if (amount != n)
      n = amount;
    amount = min(k, n);
    if (amount != 0) {
      s.mean = s.mean - g * 0.6f;
      s.daily[1] += amount;
      s.mean = (float)(s.mean > 1.0 ? s.mean : 1.0);
      k = (int)(amount * 0.33);
      if (k < 1)
        k = 1;
      if ((ai_GameFlags & 0x80) == 0)
        cm_SendExSellObject(-1, o->objId, s.item, k, ai_OwnPlayer, 0);
    } else {
      s.mean += g * 0.8f;
      if (util_RandomF() < 0.25) {
        k = util_Random(3) + 1;
        cm_SendExSellObject(o->objId, -1, s.item, k, ai_OwnPlayer, 0);
        s.mean += k * g * 0.6f;
      }
      s.mean = (float)(s.mean < s.demand * 3.0 ? s.mean : s.demand * 3.0);
    }
    if (s.demand * 1.5f < s.mean) {
      if (util_RandomF() > (s.demand * 1.5f) / s.mean)
        s.mean = amount > s.demand * 0.5 ? s.demand * 0.4f : s.demand * 0.8f;
    } else if (s.demand * 0.4f > s.mean) {
      if (util_RandomF() > s.mean / (s.demand * 0.4f))
        s.mean = amount == 0 ? s.demand * 1.5f : s.demand * 1.2f;
    }
    if (util_Random(100) > 10 || ai_Time.hour == 12)
      s.price = gm_StockPrice(ai_OwnPlayer, i);
    cm_SendGoodsDelta(&s, ai_OwnPlayer);
  }

  for (pl = 1; pl < 4; pl++) {
    if (ai_PlayerSlots[pl].name[0] == 0)
      break;
    b = gm_FindPlayerBuilding(pl);
    if (b == 0)
      continue;
    st = gm_Query(b->objList, 2, 0, 0x1db, 6);
    if (st == 0)
      continue;
    for (i = 0; i < 0x55; i++) {
      int have;

      s = gm_StockBlocks[pl].goods[i];
      if (s.item == 0)
        continue;
      q = gm_Query(st->list, 1, 0, s.item);
      if (q == 0)
        continue;
      have = gm_ListAmount(st, q);
      g = (float)(s.demand * (1.0f / 14) * (minutes * (1.0 / 60)));
      s.f2c += g;
      if (s.f2c >= 1.0f) {
        n = (int)s.f2c;
        s.f2c = s.f2c - n;
      } else {
        n = 0;
      }
      if (have != 0) {
        if (n < have)
          have = n;
        if (have > 0) {
          if (have < 1)
            have = 1;
          cm_SendExSellObject(-1, st->objId, s.item, have, ai_OwnPlayer, 0);
        }
      }
      if (have < g) {
        s.mean = (float)(s.mean + (g - have) * 0.4);
        s.mean = (float)(s.mean < s.demand * 3.0 ? s.mean : s.demand * 3.0);
      } else {
        s.mean = (float)(s.mean - g * 0.5);
        s.mean = (float)(s.mean > s.demand * 0.25 ? s.mean : s.demand * 0.25);
        if (1.0f > s.mean)
          s.mean = 1.0f;
      }
      if (s.demand * 2.5f < s.mean) {
        if (util_RandomF() > (s.demand * 2.5f) / s.mean)
          s.mean = s.demand * 0.8f;
      } else if (s.demand * 0.8f > s.mean) {
        if (util_RandomF() > s.mean / (s.demand * 0.8f))
          s.mean = s.demand * 2.5f;
      }
      if (util_Random(100) > 75)
        s.price = gm_StockPrice(pl, i);
      cm_SendGoodsDelta(&s, pl);
    }
    st = gm_Query(b->objList, 2, 0, 0x1dc, 6);
    if (st == 0)
      continue;
    for (i = 0; i < 0x55; i++) {
      GMSTOCK s2;
      int have;

      s2 = gm_StockBlocks[pl].goods[i];
      if (s2.item == 0)
        continue;
      q = gm_Query(st->list, 1, 0, s2.item);
      if (q == 0)
        continue;
      g = (float)(s2.demand * (1.0f / 14) * (minutes * (1.0 / 60)));
      f = util_Random(3) + g;
      f = (float)gm_FreeCapacity(st, s2.item, (int)(1.0f > f ? 1.0f : f));
      have = gm_ListAmount(st, q);
      if (have < s2.demand * 0.5) {
        cm_SendExSellObject(st->objId, -1, s2.item, (int)f, ai_OwnPlayer, 0);
        s2.mean = (float)(g * 0.5 + s2.mean);
        s2.mean =
            (float)(s2.mean < s2.demand * 3.0 ? s2.mean : s2.demand * 3.0);
      } else {
        s2.mean = (float)(s2.mean - g * 0.1);
        s2.mean =
            (float)(s2.mean > s2.demand * 0.25 ? s2.mean : s2.demand * 0.25);
        if (1.0f > s2.mean)
          s2.mean = 1.0f;
      }
      if (util_Random(100) > 75)
        s2.price = gm_StockPrice(pl, i);
      cm_SendGoodsDelta(&s2, pl);
    }
  }
  if (ai_Time.hour < 22) {
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 1, 0, 0);
    ev->stage = 0;
  } else
    he_FreeEvent(ev);
}
/* 0x560820, the alloc handler of the kidnap event 0x3c (AIJOB.kidnap*; ai_CalcMeisterDiebe posts it for a thieves' guild,
   its run handler he_RunKidnap): the record is cancelled (stage -1) when another event 0x3c (he_FindEvent / he_NextEvent)
   has the same building or the same character, when the guild (gm_BuildQuery) already holds a hostage (AIBLD.hostage
   not -1), or when the character is held (AICHAR.heldRounds); it is due in a second */
void he_AllocEvent3c(AIJOB *ev) {
  AIJOB *x = ev;
  AIJOB *e;
  AIBLD *b;
  AICHAR *c;

  for (e = he_FindEvent(1, 0, 0x3c); e != 0; e = he_NextEvent()) {
    if (e != x && (e->kidnapGuild == x->kidnapGuild ||
                   e->kidnapVictim == x->kidnapVictim))
      break;
  }
  b = gm_BuildQuery(1, 1, x->kidnapGuild);
  if (e != 0 || (b != 0 && b->hostage != -1))
    ev->stage = -1;
  c = gm_FindChar(x->kidnapVictim);
  if (c != 0 && c->heldRounds != 0)
    ev->stage = -1;
  ev->end = ai_Time;
  gm_AddTime(&ev->end, 0, 0, 1);
}
/* 0x560900, the run handler of the kidnap event 0x3c (AIJOB.kidnap*, its alloc handler he_AllocEvent3c; ai_CalcMeisterDiebe
   posts it for a thieves' guild): the gang is the up to 8 characters of AIJOB.ids (-1: none).
   Stage 0 sends the gang (sv_MoveToGroup into the event, stopped) to the main room of the target building
   ("Entführen"; no building or room: cancelled) and waits 30 minutes in stage 1; stage 1 waits (10 minutes more)
   until every gang member with a model stands at the target's door, then stage 2 in a second. Stage 2 (no guild,
   victim or master, or a held victim: cancelled) sends the gang back to the guild and rolls the kidnap: the guild's
   skill 15, the gang's size and mean skill 3 against the victim's skill 3; a victim with the item 0x17c escapes (the
   master is told 0xff4). A kidnap into a guild without a hostage moves the victim into its cell ("dummy_EINGANG_ZELLE",
   object 0x65), tells the master (0x19bc, quick jump to the cell), the victim (0x19be) and, for a victim of the kinds
   6 / 5, every other player (0x19c0), makes it the guild's hostage (field 0x65), holds the victim (message 0x5b, 5)
   and sends the master the ransom message 0x3d; a failed one tells the master 0x19bd and the victim 0x19bf and costs
   each gang member half its life value plus a random share. The gang is released (sv_MoveToGroup) and the record
   freed. Stages -2 / -1 send the gang back to the target building and free the record */
void he_RunKidnap(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b;
  AIOBJ *room = 0;
  AIOBJ *cell;
  AICHAR *c, *victim, *master;
  char text[0x200];
  int ok = 0;
  int n = 0;
  int k;
  int cancel;
  float sum, ratio;

  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, x->kidnapTarget);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    room = gm_GetGebaeudeHauptraum(b);
    if (room == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1) {
        sv_MoveToGroup(0, 0, gm_FindChar(ev->ids[k])->id, ev);
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], b->id, room->objId, 0, 1,
                               "Entf\374hren");
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0x1e, 0);
    ev->stage = 1;
    return;
  case 1:
    b = gm_FindBuildingById(x->kidnapTarget);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1) {
        c = gm_FindChar(ev->ids[k]);
        if (c->scene != 0 && sv_IsAtDoor(c, b) == 0) {
          ev->end = ai_Time;
          gm_AddTime(&ev->end, 0, 10, 0);
          return;
        }
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = 2;
    return;
  case 2:
    victim = gm_FindChar(x->kidnapVictim);
    master = gm_FindChar(ai_Chars[ev->chr].netId);
    b = gm_BuildQuery(1, 1, x->kidnapGuild);
    if (b == 0 || victim == 0 || master == 0 || victim->heldRounds != 0)
      cancel = 1; /* no guild, victim or master, or a held victim */
    else
      cancel = 0;
    if (cancel) {
      ev->stage = -1;
      return;
    }
    room = gm_GetGebaeudeHauptraum(b);
    sum = 0.0f;
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1) {
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], b->id, room->objId, 0, 0,
                               "Entf\374hren");
        n++;
        sum += gm_FindChar(ev->ids[k])->skills[3];
      }
    }
    ratio = (gm_BuildingSkill(b, 0xf, 1) * 0.01f + 1.0) *
            ((n * 0.1f + 1.0f) * (sum / n));
    ratio /= victim->skills[3];
    if (util_RandomF() + 0.5f < ratio)
      ok = 1;
    if (ai_InventoryHas(victim, 0x17c) != 0) {
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0xff4);
        he_ShowNews(master->netId, -1, text, 0, 0x5fa, 0);
      }
      ev->stage = -1;
      return;
    }
    if (ok) {
      if (b->hostage != -1) {
        ev->stage = -1;
        return;
      }
      cell = gm_Query(b->objList, 1, 0, 0x65);
      if (victim->scene != 0) {
        cm_SendChrStop(victim->netId);
        cm_RequestChrMoveToUniverse(victim->netId, b->id, cell->objId,
                                    "dummy_EINGANG_ZELLE");
      }
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0x19bc, 0x19c1, victim->id, victim->id, b);
        he_MessageBoxQuickjump(master->netId, master->netId, text, 0, 0x5fa,
                               b->id, cell->objId, 0, "_NACHRICHTEN_HS_71");
      }
      if (victim->kind == 6 || victim->kind == 7) {
        txt_Format(text, 0x19be);
        he_ShowNews(victim->netId, victim->netId, text, 0, 0x5fb,
                    "_NACHRICHTEN_HS_26");
      }
      if (victim->kind == 6 || victim->kind == 5) {
        for (k = 0; k < 768; k++) {
          if ((ai_Chars[k].kind == 6 || ai_Chars[k].kind == 7) &&
              ai_Chars[k].netId != victim->netId &&
              ai_Chars[k].netId != master->netId) {
            txt_Format(text, 0x19c0, victim->id);
            he_ShowNews(ai_Chars[k].netId, -1, text, 0, 0x5ec,
                        "_NACHRICHTEN_HS_73");
          }
        }
      }
      cm_BeginFieldBlock(b, b->id);
      cm_AddFieldDelta(4, 1, (char *)&b->hostage - cm_FieldObject,
                       &victim->netId);
      cm_SendFieldDeltas();
      cm_SendMessage5b(victim->netId, 5, 0);
      {
        AIMSG m;

        memset(&m, 0, sizeof(m));
        m.type = 0x3d;
        m.to = master->netId;
        m.fromId = b->id;
        m.time = ai_Time;
        m.flags = 0x12;
        m.arg[0] = victim->netId;
        m.arg[1] = b->id;
        cm_SendLongMessage(&m);
      }
    } else {
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0x19bd, victim->id, 0x19c1);
        he_ShowNews(master->netId, master->netId, text, 1, 0x5f0,
                    "_NACHRICHTEN_HS_72");
      }
      if (victim->kind == 6 || victim->kind == 7) {
        txt_Format(text, 0x19bf, master->id);
        he_ShowNews(victim->netId, victim->netId, text, 1, 0x5fa, 0);
      }
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1) {
          c = gm_FindChar(ev->ids[k]);
          gm_AddHealth(c->id,
                       (int)-(util_Random((int)c->f01c) * 0.7 + c->f01c * 0.5));
        }
      }
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0)
        sv_MoveToGroup(b, 0, c->id, 0);
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    b = gm_BuildQuery(1, 1, x->kidnapTarget);
    if (b != 0)
      room = gm_GetGebaeudeHauptraum(b);
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        cm_SendChrStop(ev->ids[k]);
        if (b != 0) {
          if (room != 0)
            cm_SendChrGotoBuilding(ev->ids[k], b->id, room->objId, 0, 0,
                                   "Entf\374hren");
          sv_MoveToGroup(b, 0, c->id, 0);
        }
      }
    }
    he_FreeEvent(ev);
    return;
  }
}
/* 0x561130, the allocation handler of the ransom event 0x3d (he_RunRansom): the due clock and the kidnap time are now */

void he_AllocRansom(AIJOB *ev) {
  AIJOB *x = ev;

  ev->end = ai_Time;
  x->ransomSince = ai_Time;
}

struct AIBLD *gm_NearestBuilding(struct AIBLD *b, unsigned kind);
int d3_VecEqual(const struct D3VECTOR *a, const struct D3VECTOR *b, float eps);

/* 0x561190, the run handler of the ransom event 0x3d (AIJOB.ransom*, its alloc handler he_AllocRansom): stage 0 (no guild or
   victim: cancelled) makes the victim the guild's hostage when it holds none. A victim no longer held
   (AICHAR.heldRounds 0) is told 0x19da, walks back to where its figure stands ("Lösegeld") and the guild's hostage
   field is sent -1; the record is freed. A victim still held is told 0x19c2 (the kidnap time), the guild owner gets the
   AP event of text 0x3fd8 (-2), and when the guild has a character whose master it is with the flag 1 (+0x1b4), the
   victim gets the ransom message 0x3e: its worth (at most 1604000) times 2 / 4 / 6 / 10 % by its held rounds
   1 / 2 / 3 / 4 or more. The news and the message only for an event with option 2. Stages -2 / -1 release the
   victim (heldRounds 0) and free the record */
void he_RunRansom(AIJOB *ev) {
  AIJOB *x = ev;
  AICHAR *victim, *owner, *payer;
  AIBLD *b;
  char text[0x200];
  int worth;
  float share, ransom;

  switch (ev->stage) {
  case 0:
    victim = gm_FindChar(x->ransomVictim);
    b = gm_BuildQuery(1, 1, x->ransomGuild);
    if (b == 0 || victim == 0) {
      ev->stage = -1;
      return;
    }
    owner = &ai_Chars[b->owner];
    if (b->hostage == -1)
      b->hostage = victim->netId;
    if (victim->heldRounds <= 0) {
      int none = -1;

      if (ev->opts & 2) {
        int bld, obj;

        txt_Format(text, 0x19da);
        he_ShowNews(victim->netId, victim->netId, text, 0, 0x5fb, 0);
        if (victim->scene != 0 &&
            he_FindFigurePlace(victim, &bld, &obj, 0) != 0)
          cm_SendChrGotoBuilding(victim->netId, bld, obj, 0, 0, "L\366segeld");
        cm_BeginFieldBlock(b, b->id);
        cm_AddFieldDelta(4, 1, (char *)&b->hostage - cm_FieldObject, &none);
        cm_SendFieldDeltas();
      }
      he_FreeEvent(ev);
      return;
    }
    payer = gm_FindCharacterByMaster(b);
    if (!(ev->opts & 2))
      return;
    he_AddApEvent(owner->id, txt_Ptrs[0x3fd8], -2, 0);
    txt_Format(text, 0x19c2, &x->ransomSince);
    he_ShowNews(victim->netId, victim->netId, text, 0, 0x5f0, 0);
    if (payer == 0 || !(payer->flags1b4 & 1))
      return;
    if (victim->heldRounds >= 4)
      share = 0.1f;
    else if (victim->heldRounds == 3)
      share = 0.06f;
    else if (victim->heldRounds == 2)
      share = 0.04f;
    else if (victim->heldRounds == 1)
      share = 0.02f;
    worth = gm_GetWorth(victim->id);
    ransom = (1604000.0f < (float)worth ? 1604000.0f : (float)worth) * share;
    {
      AIMSG m;

      m.type = 0x3e;
      m.to = victim->netId;
      m.fromId = b->id;
      m.flags = 9;
      m.arg[0] = m.to;
      m.arg[2] = (int)ransom;
      m.arg[1] = ai_Chars[ev->chr].netId;
      cm_SendLongMessage(&m);
    }
    return;
  case -2:
  case -1:
    victim = gm_FindChar(x->ransomVictim);
    if (victim != 0)
      victim->heldRounds = 0;
    he_FreeEvent(ev);
    return;
  }
}
/* 0x561470, the allocation handler the events 0x39 and 0x3e share: the due clock is now + 1 hour + a random
   0 .. 0x1d minutes less 0x14 */

void he_AllocEvent39_3e(AIJOB *e) {

  e->end = ai_Time;
  gm_AddTime(&e->end, 1, util_Random(0x1e) - 0x14, 0);
}
/* 0x5614c0, the run handler of the ransom demand event 0x3e (AIJOB.ransomDemand*; he_RunRansom sends its message, alloc handler
   he_AllocEvent39_3e): no victim or master: freed. A victim that is no player character (kind 6 / 7) decides when the
   event is due (stage 2). Stage 0 opens the window "locations\diebesgilde\Diebesgilde_Loesegeld_Msg" with the
   demand 0x19cb; stage 1 waits for its click: 0 pays (the master is told 0x19d4, the guild's hostage field is sent -1,
   the victim is released (message 0x5b, minus its held rounds), the ransom moves from the victim to the master, the
   victim's figure walks back ("L\366segeld"), the guild's field 0x69, the master's player record and the guild's
   roundSums[0] count the ransom), 1 refuses (the master gets the message box 0x19d5 with a quick jump to the guild);
   either way the record ends (stage -1). Stage 2, the AI victim: pays as above in 79 of 100 (stage 3), else the
   master is told 0x19d5 and the record freed. Stage 3 hands the victim's ransom event 0x3d (he_FindEvent) to the cm
   (cm_SendExSetHE) and frees the record; stages -2 / -1 free it */
void he_RunRansomDemand(AIJOB *ev) {
  AIJOB *x = ev;
  AIJOB *r;
  AICHAR *victim, *master;
  AIBLD *b;
  AIFIN *fin;
  char text[0x200];

  victim = gm_FindChar(x->ransomDemandVictim);
  master = gm_FindChar(x->ransomDemandMaster);
  if (victim == 0 || master == 0) {
    he_FreeEvent(ev);
    return;
  }
  if (victim->kind != 6 && victim->kind != 7 &&
      (ev->stage == 0 || ev->stage == 2)) {
    if (gm_CompareTime(&ev->end, &ai_Time) > 0)
      return;
    ev->stage = 2;
  }
  switch (ev->stage) {
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  case 0:
    he_OpenEventSlot(
        ev, 0, 0, "locations\\diebesgilde\\Diebesgilde_Loesegeld_Msg", 0x5ec);
    d2_SetForm(ev->slot->win, 0);
    io_PrintText(0x19cb, x->ransomDemandRansom);
    ev->stage++;
    return;
  case 1:
    if (d2_ClickedForm != ev->slot->win || d2_ClickedId == -1)
      return;
    if (d2_ClickedId == 0) {
      int none, bld, obj;

      none = -1;
      b = gm_BuildQuery(1, 1, ev->from);
      txt_Format(text, 0x19d4, victim->id, x->ransomDemandRansom, victim->id);
      he_ShowNews(master->netId, master->netId, text, 0, 0x5fa, 0);
      if (b != 0) {
        cm_BeginFieldBlock(b, b->id);
        cm_AddFieldDelta(4, 1, (char *)&b->hostage - cm_FieldObject, &none);
        cm_SendFieldDeltas();
      }
      cm_SendMessage5b(victim->netId, -victim->heldRounds, 0);
      cm_SendMoveGoodsUnchecked(master->netId, victim->netId, ai_OwnPlayer,
                                x->ransomDemandRansom);
      if (victim->scene != 0 && he_FindFigurePlace(victim, &bld, &obj, 0) != 0)
        cm_SendChrGotoBuilding(victim->netId, bld, obj, 0, 0, "L\366segeld");
      if (b != 0) {
        fin = gm_PlayerRecord(master);
        cm_BeginFieldBlock(b, b->id);
        cm_AddFieldValues(4, 1, 0x69,
                          &x->ransomDemandRansom); /* 0x69: AIBLD.daySum */
        cm_SendFieldDeltas();
        if (fin != 0)
          fin->ransomTakings += x->ransomDemandRansom;
        b->roundSums[0] += x->ransomDemandRansom;
      }
      ev->stage = 3;
    } else if (d2_ClickedId == 1) {
      b = gm_BuildQuery(1, 1, ev->from);
      if (b == 0) {
        he_FreeEvent(ev);
        return;
      }
      txt_Format(text, 0x19d5, victim->id);
      he_MessageBoxQuickjump(master->netId, master->netId, text, 0, 0x5f0,
                             b->id, -1, 0, 0);
    }
    ev->stage = -1;
    return;
  case 2:
    if (util_Random(100) > 0x14) {
      int none, bld, obj;

      none = -1;
      b = gm_BuildQuery(1, 1, ev->from);
      if (b == 0) {
        he_FreeEvent(ev);
        return;
      }
      txt_Format(text, 0x19d4, victim->id, x->ransomDemandRansom, victim->id);
      he_ShowNews(master->netId, ev->from, text, 0, 0x5fa, 0);
      cm_BeginFieldBlock(b, b->id);
      cm_AddFieldDelta(4, 1, (char *)&b->hostage - cm_FieldObject, &none);
      cm_SendFieldDeltas();
      cm_SendMessage5b(victim->netId, -victim->heldRounds, 0);
      cm_SendMoveGoodsUnchecked(master->netId, victim->netId, ai_OwnPlayer,
                                x->ransomDemandRansom);
      if (victim->scene != 0 && he_FindFigurePlace(victim, &bld, &obj, 0) != 0)
        cm_SendChrGotoBuilding(victim->netId, bld, obj, 0, 0, "L\366segeld");
      cm_BeginFieldBlock(b, b->id);
      cm_AddFieldValues(4, 1, 0x69,
                        &x->ransomDemandRansom); /* 0x69: AIBLD.daySum */
      cm_SendFieldDeltas();
      fin = gm_PlayerRecord(master);
      if (fin != 0)
        fin->ransomTakings += x->ransomDemandRansom;
      b->roundSums[0] += x->ransomDemandRansom;
      ev->stage = 3;
      return;
    }
    txt_Format(text, 0x19d5, victim->id);
    he_ShowNews(master->netId, master->netId, text, 0, 0x5fb, 0);
    he_FreeEvent(ev);
    return;
  case 3:
    for (r = he_FindEvent(1, 0, 0x3d); r != 0; r = he_NextEvent()) {
      if (r->ransomVictim == x->ransomDemandVictim) {
        ev->exSlot = cm_SendExSetHE(-1, ev);
        break;
      }
    }
    he_FreeEvent(ev);
    return;
  }
}
/* 0x5619a0, the allocation handler of the burglary event 0x3f (he_RunBurglary): an older burglary event against the
   same building makes this one stage -1 (freed on its first run); its due clock is the game clock plus 1 second */

void he_AllocBurglary(AIJOB *ev) {
  AIJOB *x = ev;
  AIJOB *o;

  for (o = he_FindEvent(1, 0, 0x3f); o != 0; o = he_NextEvent()) {
    if (o != ev && o->targetBld == x->targetBld) {
      ev->stage = -1;
      break;
    }
  }
  ev->end = ai_Time;
  gm_AddTime(&ev->end, 0, 0, 1);
}
/* 0x561a20, the run handler of the burglary event 0x3f ("Einbruch", AIJOB.burglary*; its alloc handler he_AllocBurglary): the
   gang is the up to 8 characters of AIJOB.ids (-1: none); the function runs to 0x5628dc with its jump table 0x5628bc.
   Stage 0 sends the gang (sv_MoveToGroup into the event) to the target building (none: cancelled) and waits 4 minutes;
   stage 1 waits (4 minutes more) until every member with a model stands at the target's door, then stage 2 in a
   second. Stage 2 asks the watch (he_DetectAttack, range 5000): a patrol that sees it accuses the event's character
   (gv_Accuse 0x17, the cm slot kept) and is bound (stage 3); else the gang breaks in (stage 5 in 15 minutes).
   Stage 3 waits for the accusation, then the patrol's character executes the proof (stage 4, 10 minutes); stage 4
   waits (6 minutes) while the patrol is still bound, then the guild's master pays the patrol's character a reward
   (gm_PlayerFactor of 550 + a random 0 .. 199; the news 0x19ea / 0x19eb), the patrol's start building counts it (field
   0x65), every gang member loses 100 + a random 0 .. 99 health and the gang walks back to the guild ("Entdeckt"); the
   record ends. Stage 5 brings the gang into the guild (gm_SkillPoints 2 each) and rolls the theft: the guild's spy
   report on the target (object 0xca: reportKnow %, at least 0.1 %) less 0.35 * 1 % of the target's skill 7 against a
   random number, and only an unprotected target (he_NoProtectionEvent); the accusation 0x17 is made either way. A
   theft moves the share of the owner's worth (gm_BuildingValues) times 1 .. 1.05 and the guild's skill 1 bonus from
   the owner to the master, and with a guild store (0x116) each goods of the target's stall (0x2a) but 0x1c1 .. 0x1c7
   and 0x2af / 0x2b0, by half a chance, n * 0.1 of its amount (at least 1, n the gang's size) is sold into the store and
   counted at its price; the loot list goes to the master (0x19e6, "_NACHRICHTEN_HS_74") and the owner is told 0x19e8
   ("_NACHRICHTEN_HS_27"); a failed one tells the master 0x19e7 ("_NACHRICHTEN_HS_75") and the owner 0x19e9. The spy
   report moves out of the guild and the record is freed. Stages -2 / -1 send the gang back to the guild and free it */
void he_RunBurglary(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b, *g, *gb;
  AIOBJ *room = 0, *stall, *store = 0, *it;
  AICHAR *c, *owner, *master = 0, *guard;
  AIJOB *w;
  AIJOB *patrol;
  AIFIN *fin;
  CRIME *cr;
  char text[0x200];
  char line[0x100];
  int k, ok, amt, skill;
  int n = 0;
  AIOBJ *report = 0;
  float know, sk;

  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        sv_MoveToGroup(b, 0, c->id, ev);
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], b->id, -1, 0, 1, "Einbruch");
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 4, 0);
    ev->stage = 1;
    return;
  case 1:
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0 &&
          c->scene != 0 && sv_IsAtDoor(c, b) == 0) {
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 4, 0);
        return;
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = 2;
    return;
  case 2:
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b != 0) {
      HEDETECT d;

      owner = &ai_Chars[b->owner];
      d.bld = b;
      d.range = 5000.0f;
      d.ev = ev;
      d.found = 0;
      if (he_DetectAttack((intptr_t)&d) != 0) {
        patrol = d.found;
        x->burglarySlot =
            gv_Accuse(0x17, 1, ai_Chars[ev->chr].netId, owner->netId, b->id);
        x->burglaryWatch = patrol->id;
        x->burglaryGuardBld = patrol->patrolStart;
        ev->stage = 3;
        ev->end = ai_Time;
        return;
      }
    }
    ev->stage = 5;
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0xf, 0);
    return;
  case 3:
    if (x->burglarySlot != -1 && cm_GetSlotState(x->burglarySlot) == 0)
      return;
    b = gm_BuildQuery(1, 1, x->targetBld);
    w = he_FindEvent(1, 1, x->burglaryWatch);
    if (b == 0 || w == 0 || w->patrolWait != ev->id || x->burglarySlot == -1) {
      ev->stage = -1;
      return;
    }
    guard = &ai_Chars[w->chr];
    cr = (CRIME *)cm_GetSlotValue(x->burglarySlot);
    if (guard != 0 && cr != 0)
      cm_SendProofExecuted(cr->id, guard->netId);
    ev->stage = 4;
    gm_AddTime(&ev->end, 0, 10, 0);
    return;
  case 4:
    w = he_FindEvent(1, 1, x->burglaryWatch);
    if (w == 0)
      ev->stage = -1;
    else if (w->patrolWait == ev->id)
      gm_AddTime(&ev->end, 0, 6, 0);
    else {
      b = gm_BuildQuery(1, 1, x->targetBld);
      if (b != 0) {
        int reward;

        g = gm_BuildQuery(1, 1, x->burglaryGuild);
        if (g != 0)
          master = gm_FindChar(ai_Chars[g->owner].netId);
        guard = &ai_Chars[w->chr];
        if (guard != 0 && master != 0) {
          reward = gm_PlayerFactor(util_Random(200) + 0x226, ai_OwnPlayer);
          txt_Format(text, 0x19ea, b, reward, guard->id);
          he_ShowNews(master->netId, master->netId, text, 1, 0x5f0,
                      "_NACHRICHTEN_HS_76");
          txt_Format(text, 0x19eb, b, reward);
          he_ShowNews(guard->netId, guard->netId, text, 1, 0x5f0,
                      "_NACHRICHTEN_HS_77");
          cm_SendMoveGoodsUnchecked(guard->netId, master->netId, ai_OwnPlayer,
                                    reward);
        }
        gb = gm_BuildQuery(1, 1, x->burglaryGuardBld);
        if (gb != 0) {
          cm_BeginFieldBlock(gb, gb->id);
          cm_AddFieldValues(4, 1, 0x65, &reward); /* 0x65: AIBLD.earnings */
          cm_SendFieldDeltas();
        }
      }
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0)
          gm_AddHealth(c->id, -100 - util_Random(100));
      }
      g = gm_BuildQuery(1, 1, x->burglaryGuild);
      if (g != 0) {
        room = gm_GetGebaeudeHauptraum(g);
        for (k = 0; k < 8; k++) {
          if (ev->ids[k] != -1) {
            cm_SendChrStop(ev->ids[k]);
            cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                   "Entdeckt");
          }
        }
      }
      ev->stage = -1;
    }
    return;
  case 5:
    b = gm_BuildQuery(1, 1, x->targetBld);
    g = gm_BuildQuery(1, 1, x->burglaryGuild);
    if (g != 0)
      master = gm_FindChar(ai_Chars[g->owner].netId);
    if (b == 0 || master == 0) {
      ev->stage = -1;
      return;
    }
    owner = &ai_Chars[b->owner];
    if (owner == 0) {
      ev->stage = -1;
      return;
    }
    if (g != 0) {
      room = gm_GetGebaeudeHauptraum(g);
      store = gm_Query(g->objList, 2, 6, 0, 0x116);
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
          cm_SendChrStop(ev->ids[k]);
          cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                 "Einbruch");
          n++;
          gm_SkillPoints(c, 2);
          sv_MoveToGroup(g, 0, c->id, 0);
        }
      }
      for (report = gm_Query(g->objList, 1, 0, 0xca); report != 0;
           report = gm_QueryNext()) {
        if (report->reportBld == b->id)
          break;
      }
      if (report != 0)
        know = (float)(report->reportKnow * 0.01);
      else
        know = 0.0f;
      if (0.001f > know)
        know = 0.001f;
      owner = &ai_Chars[b->owner];
      skill = gm_BuildingSkill(b, 7, 1);
      sk = skill * 0.01f;
      ok = util_RandomF() < (know = (float)(know - sk * 0.35));
    } else
      ok = 0;
    if (he_NoProtectionEvent(b) == 0)
      ok = 0;
    gv_Accuse(0x17, 1, ai_Chars[g->owner].netId, owner->netId, b->id);
    if (ok) {
      char loot[0x400];
      int vals[2];
      int money;

      loot[0] = ch_EmptyName[0];
      memset(loot + 1, 0, sizeof(loot) - 1);
      b = gm_BuildQuery(1, 1, x->targetBld);
      stall = gm_Query(b->objList, 2, 6, 0, 0x2a);
      gm_BuildingValues(b, vals);
      money = vals[0];
      money = (int)((util_Random(50) * 0.001f + 1.0) * money);
      money = (int)((gm_BuildingSkill(g, 1, 1) * 0.0025f + 1.0f) * money);
      money = money < 0 ? 0 : money;
      txt_Format(line, (intptr_t)"$Z%T$A", money);
      strcat(loot, line);
      cm_SendMoveGoodsUnchecked(master->netId, owner->netId, ai_OwnPlayer,
                                money);
      cm_BeginFieldBlock(g, g->id);
      cm_AddFieldValues(4, 1, 0x69, &money); /* 0x69: AIBLD.daySum */
      cm_SendFieldDeltas();
      if (stall != 0) {
        if (store != 0) {
          for (it = gm_Query(stall->list, 1, 5); it != 0; it = gm_QueryNext()) {
            if (util_Random(100) > 0x32 && it->id != 0x1c7 && it->id != 0x1c4 &&
                it->id != 0x1c5 && it->id != 0x1c6 && it->id != 0x2af &&
                it->id != 0x2b0 && it->id != 0x1c1 && it->id != 0x1c2 &&
                it->id != 0x1c3) {
              amt = gm_ListAmount(stall, it);
              amt = (int)(amt * (n * 0.1));
              if (amt < 1)
                amt = 1;
              sprintf(line, "%i %s$A", amt,
                      txt_Ptrs[TXT_OBJECT_NAMES + 2 * it->id]);
              strcat(loot, line);
              cm_SendExSellObject(store->objId, stall->objId, it->id, amt,
                                  ai_OwnPlayer, 0);
              money = (int)(gm_GoodsPrice(it->id, ai_OwnPlayer) * amt + money);
            }
          }
        } else
          strcpy(loot, txt_Ptrs[0x19ec]);
      }
      fin = gm_PlayerRecord(master);
      if (fin != 0)
        fin->burglaryTakings += money;
      g->roundSums[0] += money;
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0x19e6, 0x19c1, owner->id, b);
        strcat(text, loot);
        he_MessageBoxQuickjump(master->netId, master->netId, text, 1, 0x5f0,
                               b->id, -1, 0, "_NACHRICHTEN_HS_74");
      }
      if (owner->kind == 6 || owner->kind == 7) {
        txt_Format(text, 0x19e8, b, money);
        he_MessageBoxQuickjump(owner->netId, owner->netId, text, 0, 0x5f0,
                               b->id, -1, 0, "_NACHRICHTEN_HS_27");
      }
    } else {
      b = gm_BuildQuery(1, 1, x->targetBld);
      if (b != 0) {
        if (master->kind == 6 || master->kind == 7) {
          txt_Format(text, 0x19e7, owner->id, b, 0x19c1);
          he_MessageBoxQuickjump(master->netId, master->netId, text, 1, 0x5f0,
                                 b->id, -1, 0, "_NACHRICHTEN_HS_75");
        }
        if (owner->kind == 6 || owner->kind == 7) {
          txt_Format(text, 0x19e9, b);
          he_MessageBoxQuickjump(owner->netId, owner->netId, text, 1, 0x5f0,
                                 b->id, -1, 0, 0);
        }
      }
    }
    if (report != 0 && (gb = gm_BuildQuery(1, 1, x->burglaryGuild)) != 0)
      cm_SendMoveObject(gb->id, -1, report->objId);
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    g = gm_BuildQuery(1, 1, x->burglaryGuild);
    if (g != 0)
      room = gm_GetGebaeudeHauptraum(g);
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        cm_SendChrStop(ev->ids[k]);
        if (g != 0 && room != 0)
          cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                 "Einbruch");
        else
          cm_SendChrGotoBuilding(ev->ids[k], -1, -1, 0, 0, "Einbruch");
        sv_MoveToGroup(0, 0, c->id, 0);
      }
    }
    he_FreeEvent(ev);
    return;
  }
}
/* 0x5628e0, the run handler of the building spying event 0x40 ("GebSpionage", AIJOB.bldSpy*; alloc handler
   he_AllocDueInOne): stage 0 sends the spies (sv_MoveToGroup into the event) to the target building (none:
   cancelled), 10 minutes; stage 1 waits (5 minutes more) until every spy with a model stands at the door with its
   actions done, then sets the spying time: the target's rank * 120 * 252 / the spies' mean skill 2 points (at least 1),
   by their number, at most 2880 minutes (no spy: freed). Stage 2 brings them back to their building and writes the
   report (message 0x5e, HESPYREPORT): a tenth of the owner's worth (at most 1.6 million), the price of the target's
   stall goods, its skill 7 and the knowledge: n * the mean skill 2 points (at least 42) / 4 by the target's rank,
   + a random -2 .. 1, within 2 .. 100; a player master (kind 6 / 7) without a character of the building with the
   flag 1 (+0x1b4) gets the message box 0x19f8 ("_NACHRICHTEN_HS_78", a quick jump to the main object). The record is
   freed. Stages -2 / -1 send the spies back and free it
   @deep s52: shape, only frame slots differ (dcp asmdiff: the stores / loads of two slots). Done this
   session, each read from the original with the pushes pending: the stall amount as a float local (a
   meaning fix: fild / fstp dword before the price call), all = 1 before case 1's building query, case 2
   with its own exits (if (n == 0) { he_FreeEvent(ev); return; } and he_FreeEvent(ev); return; at its end
   instead of break: ev's split pieces then keep edi, owner / master stay in memory / ebx as the original),
   the main object fetched into a local before the message box (obj = gm_BuildingMainObject(g): the call
   ahead of every push, master->netId loaded late into ecx), sum = 0 before n = 0 in cases 1 and 2 (the 0
   register in ebx through cases 1 / 2; with it the knowledge product is fild n; fimul sum as written).
   Left: the original's +0x10 holds n with case 1's two loop countdowns, case 2's countdown and the v temp,
   +0x14 room / all / worth / goods; ours has the two case 1 countdowns with room / goods / worth at +0x10
   and n / all / case 2's countdown / the v temp at +0x14 (everything else agrees: +0x18 b / owner / case
   -1's countdown, +0x1c sum, +0x24 mean / master, +0x2c spy). The packer replayed (c2frame --names counts
   and conflicts, each local joins the newest compatible slot, equal counts in the order of their last
   reference): the original's slots need room packed before n, i.e. n counted 4 or less (ours 6: the n = 0
   store, the store behind the loop and the use, per case), or room 7 (ours 5), or goods 7, or both case 1
   countdowns counted 5 (a doubled latch). = control: continue forms of case 1's loops, n = sum = 0 chains,
   declaration order (reversed: the packing order does not follow it), n / sum inits at the declaration,
   room / spy inits as statements, the main object in room or it instead of obj, spy as the loop character
   of the other cases. Worse: separate n / sum variables for case 2, cases -2 / -1 as two written-out
   bodies (not merged: the table differs), the message box per p == 0 / flag arm or per kind. flip --want
   '_n. = -1084': only meaning changes. prior: s51: the exits: the message-box arm's own he_FreeEvent +
   return dropped (the arm falls into the break -> free), case 2's no-spy exit as break (246 -> 178); the
   spying time as (rank * 120.0) * (252.0f / (int)mean) / n (the original's fmul 120.0 right after the rank
   fild, s49's parenthesised product) and all = 1 set after the b == 0 guard, right before the door loop
   (178 -> 170). Size 1934 -> 1883 (orig 1910): the original keeps its own he_FreeEvent copy for case 2's n
   == 0 exit (written out with return: 234, the other copies then do not merge as now). Left: 0 in ebx
   through the whole function in the original (cmp reg,ebx / push ebx; ours test / push 0 in cases 1 / 2:
   one 0 reference more in the original makes 0 a candidate), case 1's loop: the original has &ids[k] in
   ebp and the countdown in [esp+0x10], ours ebx / ebp; the frame slots of spy / room / all. No lever: spy
   = 0 right before case 2's loop (worse). */
void he_RunBuildingSpying(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b, *g;
  AICHAR *c, *owner, *master, *spy = 0, *p;
  AIOBJ *room = 0, *stall, *it, *obj;
  HESPYREPORT rec;
  char text[0x400];
  int k, n, sum, all, worth, goods, know;
  double mean;
  float t, v, amt;

  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      c = gm_FindChar(ev->ids[k]);
      if (c != 0) {
        cm_SendChrStop(c->netId);
        cm_SendChrGotoBuilding(c->netId, b->id, -1, 0, 1, "GebSpionage");
        sv_MoveToGroup(b, 0, c->id, ev);
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 10, 0);
    ev->stage = 1;
    return;
  case 1:
    all = 1;
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    for (k = 0; k < 8; k++) {
      c = gm_FindChar(ev->ids[k]);
      if (c != 0 && c->scene != 0 && sv_IsAtDoor(c, b) == 0 &&
          c->scene->actions != 0)
        all = 0;
    }
    if (all != 0) {
      sum = 0;
      n = 0;
      for (k = 0; k < 8; k++) {
        c = gm_FindChar(ev->ids[k]);
        if (c != 0) {
          sum += gm_SkillPoints(c, 2);
          n++;
        }
      }
      if (n == 0)
        break;
      sum /= n;
      mean = 1.0 > sum ? 1.0 : sum;
      b = gm_BuildQuery(1, 1, x->targetBld);
      if (b == 0) {
        ev->stage = -1;
        return;
      }
      t = (float)((gm_BuildingRank(b) * 120.0) * (252.0f / (int)mean) / n);
      t = 2880.0f < t ? 2880.0f : t;
      ev->start = ai_Time;
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, (int)t, 0);
      ev->stage = 2;
      return;
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 5, 0);
    return;
  case 2:
    g = gm_BuildQuery(1, 1, x->bldSpyHome);
    if (g == 0) {
      ev->stage = -1;
      return;
    }
    master = gm_FindChar(ai_Chars[g->owner].netId);
    room = gm_GetGebaeudeHauptraum(g);
    sum = 0;
    n = 0;
    for (k = 0; k < 8; k++) {
      c = gm_FindChar(ev->ids[k]);
      if (c != 0) {
        sum += gm_SkillPoints(c, 2);
        spy = c;
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                               "GebSpionage");
        sv_MoveToGroup(g, 0, c->id, 0);
        n++;
      }
    }
    if (n == 0) {
      he_FreeEvent(ev);
      return;
    }
    sum /= n;
    sum = (int)(42.0f > sum ? 42.0f : sum);
    b = gm_BuildQuery(1, 1, x->targetBld);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    owner = &ai_Chars[b->owner];
    stall = gm_Query(b->objList, 2, 6, 0, 0x2a);
    worth = gm_GetWorth(owner->id);
    if (worth >= 1600000)
      worth = 1600000;
    rec.worth = (int)(worth * 0.1);
    goods = 0;
    if (stall != 0) {
      for (it = gm_Query(stall->list, 1, 5); it != 0; it = gm_QueryNext()) {
        amt = (float)gm_ListAmount(stall, it);
        goods += amt * gm_GoodsPrice(it->id, ai_OwnPlayer);
      }
    }
    v = (float)n * sum * 0.25f;
    know = (int)(v / gm_BuildingRank(b));
    know += util_Random(4) - 2;
    if (know > 100)
      know = 100;
    else if (know < 2)
      know = 2;
    rec.when = ai_Time;
    rec.bld = b->id;
    rec.goods = goods;
    rec.skill = gm_BuildingSkill(b, 7, 1);
    rec.know = know;
    cm_SendSpyReport(g, &rec);
    if (master->kind == 6 || master->kind == 7) {
      p = gm_FindCharacterByMaster(g);
      if (spy != 0 && (p == 0 || (p->flags1b4 & 1) == 0)) {
        txt_Format(text, 0x19f8, spy->id, owner->id, b);
        obj = gm_BuildingMainObject(g);
        he_MessageBoxQuickjump(master->netId, master->netId, text, 1, 0x5f0,
                               x->bldSpyHome, obj->objId, 0,
                               "_NACHRICHTEN_HS_78");
      }
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    g = gm_BuildQuery(1, 1, x->bldSpyHome);
    if (g != 0)
      room = gm_GetGebaeudeHauptraum(g);
    for (k = 0; k < 8; k++) {
      c = gm_FindChar(ev->ids[k]);
      if (c != 0) {
        cm_SendChrStop(ev->ids[k]);
        if (g != 0)
          cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                 "GebSpionage");
        sv_MoveToGroup(0, 0, c->id, 0);
      }
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x563070, the allocation handler of the ambush event 0x48 (he_RunAmbush): the due clock and the give-up time are now,
   the give-up time 48 hours ahead and the due clock 1 second ahead */

void he_AllocAmbush(AIJOB *ev) {
  AIJOB *x = ev;

  ev->end = ai_Time;
  x->ambushUntil = ai_Time;
  gm_AddTime(&x->ambushUntil, 0x30, 0, 0);
  gm_AddTime(&ev->end, 0, 0, 1);
}

/* 0x5630f0, the run handler of the ambush event 0x48 ("\334berfall", AIJOB.ambush*; alloc handler he_AllocAmbush): waits for
   its cm slot (AIJOB.exSlot) first. Stage 0 sends the gang to the place (with option 2: sv_MoveToGroup into the
   event, their mean skills[2]; no member: the event ends) and waits 30 minutes. Stage 1 (option 2) checks that every
   member stands within 25000 of the place (scene object, d3_PointToWorld), lets them idle (he_CharacterBehavior)
   and, when they all do, picks up to three transports (event 15) of other characters (all of one owner) not taken
   yet whose cart stands within 1500 of the place or whose goods' value suits the gang's level (skill / 42: 0 ..
   5 from 100 .. 500 up to above 700); when one was taken, with a chance of 80 of 100 (30 while an event 0x51 runs,
   none with gm_AllowAll) and no fight 3 running (cm_FindPartyOfKind), the gang raids them: a fight party (G28REC kind 3, flags
   0xa2, variant 1 | 8 at a "STADT" place) of the gang's building owner against the transports' owner, the carts'
   objects in fight.carts, the carts' escorts armed (ai_ArmGateGuards; one cart of escort 2: kinds 2 and 1), the gang
   as raiders, in 15 minutes (stage 2). Else it waits 10 .. 14 minutes more until the event's time is up (then the
   cm ends it). Stage 2 waits for the party's slot (no party: cm slot 1), stage 3 waits (5 minutes) while the party
   runs, then ends a second later. Stages -2 / -1 send the gang (option 2) home and free the record */
void he_RunAmbush(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b;
  AICHAR *c;
  AIJOB *t, *busy;
  AIOBJ *cart;
  AIOBJ *cartObj[3];
  AIJOB *carts[3];
  D3OBJECT *o;
  D3VECTOR4 pos;
  int *p;
  int k, n, all, nearby, rich, scene, owner, chance, value, level;

  if (ev->exSlot != -1 && cm_GetSlotState(ev->exSlot) == 0)
    return;
  ev->exSlot = -1;
  switch (ev->stage) {
  case 0:
    if (ev->opts & 2) {
      n = 0;
      x->ambushSkill = 0;
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
          sv_MoveToGroup(0, 0, c->id, ev);
          cm_SendChrGotoBuilding(ev->ids[k], -1, -1, x->ambushPlace, 1,
                                 "\334berfall");
          x->ambushSkill += c->skills[2];
          n++;
        }
      }
      if (n != 0)
        x->ambushSkill /= n;
      else {
        ev->exSlot = cm_SendExSetHE(-1, ev);
        x->ambushSkill = 0;
        return;
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0x1e, 0);
    ev->stage++;
    return;
  case 1:
    if (ev->opts & 2) {
      all = 1;
      cartObj[0] = 0;
      cartObj[1] = 0;
      cartObj[2] = 0;
      n = 0;
      owner = -1;
      scene = d3_CurrentScene;
      d3if_SelectScene(0, 1);
      o = d3_FindObject(0, 0x100, 0, x->ambushPlace);
      if (o != 0)
        d3_PointToWorld(o, &o->pos, &pos.v);
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0 &&
            d3_VecEqual(&c->scene->obj->pos, &pos.v, 25000.0f) == 0) {
          all = 0;
          break;
        }
      }
      he_CharacterBehavior(ev, &pos.v);
      busy = he_FindEvent(1, 0, 0x51);
      t = he_FindEvent(1, 0, 0xf);
      for (; all != 0 && o != 0 && t != 0 && n < 3; t = he_NextEvent()) {
        AIRECIPE goods;
        CHARACTER *task;

        if (t->transportAmbushed != 0 || t->chr == ev->chr ||
            (owner != -1 && owner != ai_Chars[t->chr].netId))
          continue;
        nearby = 0;
        rich = 0;
        cart = gm_FindObjectInst(t->transportCart);
        if (cart == 0)
          continue;
        task = cart->sceneObj;
        if (d3_VecEqual(&task->obj->pos, &pos.v, 1500.0f) != 0)
          nearby = 1;
        gm_StallGoodsList(cart, &goods);
        value = goods.value;
        if (value <= 0)
          continue;
        level = (int)(x->ambushSkill * 0.023809524f);
        if (level == 0 && value > 100 && value < 500)
          rich = 1;
        else if (level == 1) {
          if (value > 200 && value < 750)
            rich = 1;
        } else if (level == 2) {
          if (value > 300 && value < 1000)
            rich = 1;
        } else if (level == 3) {
          if (value > 500 && value < 1500)
            rich = 1;
        } else if (level == 4) {
          if (value > 600 && value < 1750)
            rich = 1;
        } else if (level == 5 && value > 700)
          rich = 1;
        if (rich != 0 || nearby != 0) {
          carts[n] = t;
          owner = ai_Chars[t->chr].netId;
          t->transportAmbushed = 1;
          cartObj[n] = gm_Query(0, 2, 7, 1, t->transportCart);
          n++;
        }
      }
      chance = busy != 0 ? 30 : 80;
      if (gm_AllowAll)
        chance = 0;
      d3if_SelectScene(scene, 1);
      if (n != 0 && cm_FindPartyOfKind(3, -1) == 0 &&
          util_Random(100) > chance) {
        G28REC party;

        b = gm_BuildQuery(1, 1, ev->from);
        if (b == 0)
          break;
        memset(&party, 0, sizeof(party));
        party.kind = 3;
        party.flags = 0xa2;
        party.thing = -1;
        party.used = 2;
        party.host = ai_Chars[ai_PlayerId].netId;
        party.members[0] = ai_Chars[b->owner].netId;
        party.members[1] = owner;
        party.variant = 1;
        if (o != 0 && strstr(o->name, "STADT") != 0)
          party.variant |= 8;
        for (k = 0; k < 16; k++) {
          party.fight.attackers[k] = -1;
          party.fight.defenders[k] = -1;
        }
        for (k = 0; k < 3; k++) {
          if (cartObj[k] != 0)
            party.fight.carts[k] = cartObj[k]->objId;
          else
            party.fight.carts[k] = -1;
        }
        for (k = 0; k < n; k++) {
          if (cartObj[k]->escort == 2 && n == 1) {
            ai_ArmGateGuards(&party, cartObj[k]->escort);
            ai_ArmGateGuards(&party, 1);
          } else
            ai_ArmGateGuards(&party, cartObj[k]->escort);
        }
        party.fight.attackerBld = b->id;
        memcpy(party.fight.attackers, ev->ids, sizeof(ev->ids));
        party.time = ai_Time;
        gm_AddTime(&party.time, 0, 0xf, 0);
        x->ambushPartySlot = cm_SendNewParty(&party);
        ev->end = ai_Time;
        ev->stage = 2;
        return;
      }
    }
    if (gm_CompareTime(&ai_Time, &x->ambushUntil) < 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, util_Random(5) + 10, 0);
      return;
    }
    ev->exSlot = cm_SendExSetHE(-1, ev);
    return;
  case 2:
    if (cm_GetSlotState(x->ambushPartySlot) == 0)
      return;
    p = (int *)cm_GetSlotValue(x->ambushPartySlot);
    if (p == 0) {
      ev->exSlot = cm_SendExSetHE(1, ev);
      return;
    }
    x->ambushParty = *p;
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 1, 0);
    ev->stage = 3;
    return;
  case 3:
    if (cm_PartyById(x->ambushParty) != 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 5, 0);
      return;
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = -1;
    return;
  case -2:
  case -1:
    if (ev->opts & 2) {
      b = gm_BuildQuery(1, 1, ev->from);
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
          if (b != 0)
            cm_SendChrGotoBuilding(c->netId, b->id, -1, 0, 0, "\334berfall");
          sv_MoveToGroup(0, 0, c->id, 0);
        }
      }
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x563980, the allocation handler of the events 0x31, 0x40, 0x49 and 0x75: the due clock is the game clock plus 1 second */

void he_AllocDueInOne(AIJOB *ev) {
  ev->end = ai_Time;
  gm_AddTime(&ev->end, 0, 0, 1);
}
/* 0x5639c0, the run handler of the attack event 0x49 ("Angriff"; alloc handler he_AllocDueInOne): a gang (ids[]) from
   the building raidStart attacks the building raidTarget, with the raid event's words (AIJOB.raid*, as he_RunRaid).
   Stage 0 sends the gang to the target (no target or start building: freed), 10 minutes; stage 1 waits (10 minutes)
   while a member's scene character has actions queued, then stage 2 in a second. Stage 2 (no target: ends) rolls
   random(0x4b) + 100 * the start building's spy report on the target (object 0xca: (reportKnow + 100) / 100, else 1;
   10 with gm_AllowAll) against 125 * (1 + 0.01 * the target's skill 5): above it a fight party of kind 3 (variant 2:
   up to six living people of the target against up to six of the gang, in 30 minutes) is posted (stage 3), but with
   no defender or no attacker the target is looted (cm_LootStock, the start building's roundSums[0] counts it, the
   message boxes 0x1c54 to the owner and 0x1c55 to the event's character; stage 5); either way the spy report moves
   out of the start building. Not above it the attack fails (0x114b with the start building's fight role to the
   event's character, 0x1c56 to a player owner; stage 5). Stage 3 waits for the party's slot and keeps its id (stage
   4), stage 4 waits (5 minutes) until the party is over (stage 5 in a second); stages 5 / -2 / -1 send the gang to
   the start building's main room and free the record */
void he_RunAttack(AIJOB *ev) {
  AIBLD *b, *home;
  AICHAR *c, *owner, *me;
  AIOBJ *o, *room = 0;
  G28REC party;
  char text[0x800];
  int i, n, k, loot, role;
  float chance = 1.0f, defence;

  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, ev->raidTarget);
    home = gm_BuildQuery(1, 1, ev->raidStart);
    if (b == 0 || home == 0)
      break;
    for (i = 0; i < 8; i++) {
      if (ev->ids[i] != -1) {
        c = gm_FindChar(ev->ids[i]);
        cm_SendChrStop(ev->ids[i]);
        cm_SendChrGotoBuilding(ev->ids[i], b->id, -1, 0, 0, "Angriff");
        sv_MoveToGroup(b, 0, c->id, ev);
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 10, 0);
    ev->stage = 1;
    return;
  case 1:
    for (i = 0; i < 8; i++) {
      if (ev->ids[i] != -1 && (c = gm_FindChar(ev->ids[i]))->scene != 0 &&
          c->scene->actions != 0) {
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 10, 0);
        return;
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = 2;
    return;
  case 2:
    b = gm_BuildQuery(1, 1, ev->raidTarget);
    if (b == 0) {
      ev->stage = -1;
      return;
    }
    owner = &ai_Chars[b->owner];
    me = &ai_Chars[ev->chr];
    defence = (float)(gm_BuildingSkill(b, 5, 1) * 0.01 + 1.0);
    home = gm_BuildQuery(1, 1, ev->raidStart);
    o = gm_Query(home->objList, 1, 0, 0xca);
    for (; o != 0; o = gm_QueryNext())
      if (o->reportBld == b->id)
        break;
    if (o != 0)
      chance = (float)((o->reportKnow + 100.0) * 0.01);
    if (gm_AllowAll != 0)
      chance = 10.0f;
    if ((float)util_Random(0x4b) + chance * 100.0f > defence * 125.0f) {
      memset(&party, 0, sizeof(party));
      party.kind = 3;
      party.flags = 0xa2;
      party.thing = b->id;
      party.used = 2;
      party.host = ai_Chars[ai_PlayerId].netId;
      party.members[0] = me->netId;
      party.members[1] = owner->netId;
      party.variant = 2;
      for (i = 0; i < 16; i++) {
        party.fight.attackers[i] = -1;
        party.fight.defenders[i] = -1;
      }
      n = 0;
      for (i = 0; i < 768 && n < 6; i++) {
        if (ai_Chars[i].health != 0 && ai_Chars[i].bld == b) {
          party.fight.defenders[n] = ai_Chars[i].netId;
          n++;
        }
      }
      for (i = 0; i < 3; i++)
        party.fight.carts[i] = -1;
      home = gm_BuildQuery(1, 1, ev->raidStart);
      party.fight.attackerBld = home->id;
      k = 0;
      for (i = 0; i < 8 && k < 6; i++) {
        if (ev->ids[i] != -1) {
          party.fight.attackers[k] = ev->ids[i];
          k++;
        }
      }
      if (k != 0 && n != 0) {
        party.time = ai_Time;
        gm_AddTime(&party.time, 0, 0x1e, 0);
        ev->raidSlot = cm_SendNewParty(&party);
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 0, 1);
        ev->stage = 3;
      } else {
        home = gm_BuildQuery(1, 1, ev->raidStart);
        b = gm_BuildQuery(1, 1, ev->raidTarget);
        loot = cm_LootStock(b, home, &ai_Chars[ev->chr], &ai_Chars[b->owner]);
        if (home != 0)
          home->roundSums[0] += loot;
        txt_Format(text, 0x1c54, b, loot);
        he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, text, 0, 0x5f0,
                               b->id, -1, 0, (char *)0);
        txt_Format(text, 0x1c55, b->owner, b, loot);
        he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, -1, text, 0, 0x5f0,
                               b->id, -1, 0, (char *)0);
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 0, 1);
        ev->stage = 5;
      }
      if (o != 0 && (home = gm_BuildQuery(1, 1, ev->raidStart)) != 0)
        cm_SendMoveObject(home->id, -1, o->objId);
      return;
    }
    home = gm_BuildQuery(1, 1, ev->raidStart);
    b = gm_BuildQuery(1, 1, ev->raidTarget);
    role = cm_FightRole(home) + 0x1125;
    txt_Format(text, 0x114b, role, b->owner, b, role);
    he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, -1, text, 0, 0x5f0, b->id,
                           -1, 0, (char *)0);
    if (ai_Chars[b->owner].kind == 6 || ai_Chars[b->owner].kind == 7) {
      txt_Format(text, 0x1c56, b);
      he_MessageBoxQuickjump(ai_Chars[b->owner].netId, -1, text, 0, 0x5f0,
                             b->id, -1, 0, (char *)0);
    }
    ev->stage = 5;
    return;
  case 3:
    if (cm_GetSlotState(ev->raidSlot) == 0)
      return;
    ev->raidParty = ((G28REC *)cm_GetSlotValue(ev->raidSlot))->id;
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 1, 0);
    ev->stage = 4;
    return;
  case 4:
    if (cm_PartyById(ev->raidParty) != 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 5, 0);
      return;
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = 5;
    return;
  case 5:
  case -2:
  case -1:
    home = gm_BuildQuery(1, 1, ev->raidStart);
    if (home != 0)
      room = gm_GetGebaeudeHauptraum(home);
    for (i = 0; i < 8; i++) {
      if (ev->ids[i] != -1 && (c = gm_FindChar(ev->ids[i])) != 0) {
        cm_SendChrStop(c->netId);
        if (home != 0)
          cm_SendChrGotoBuilding(c->netId, home->id, room->objId, 0, 0,
                                 "Angriff");
        sv_MoveToGroup(0, 0, c->id, 0);
      }
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x5642e0, the allocation handler of the fire event 0x4e (AIJOB.fire*), as the storm's he_AllocStorm: the buildings of
   kind 6 (gm_BuildQuery (1, 6) / gm_BuildNext) that are no home / type 10, have a scene object and are not of a
   building type of kind 3 are collected (at most 0x100); blds[1..15] = -1, blds[0] is the target: the event's own
   building, else a random pick of the list; the ones whose scene position (d3_PointToWorld) lies within radius of
   the target's become blds[1..15]; center is the target's id. The due clock is now; after the hour 20 it is moved to
   the next year field at 8 .. 17 o'clock, but the clock is then set to now again and only an hour below 7 is moved
   to 8 .. 17 */
void he_AllocFire(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *list[0x100];
  AIBLD *b, *c;
  AIBTYPE *t;
  D3OBJECT *o;
  D3VECTOR4 p1, p2;
  unsigned short n = 0, k = 1;
  int i;

  for (b = gm_BuildQuery(1, 6); b != 0; b = gm_BuildNext()) {
    t = &ai_BTypes[b->type];
    if (gm_IsHomeType(b) == 0 && gm_IsType10(b) == 0 && b->object != 0 &&
        t->kind != 3)
      list[n++] = b;
  }
  for (i = 1; i < 0x10; i++)
    x->fireBlds[i] = -1;
  if (x->fireBlds[0] == -1) {
    c = list[util_Random(n)];
    x->fireBlds[0] = c->id;
  } else {
    c = gm_BuildQuery(1, 1, x->fireBlds[0]);
  }
  for (i = 0; i < n && k < 0x10; i++) {
    b = list[i];
    o = b->object;
    d3_PointToWorld(o, &o->pos, &p1.v);
    o = c->object;
    d3_PointToWorld(o, &o->pos, &p2.v);
    if (b != c && d3_VecEqual(&p1.v, &p2.v, (float)x->fireRadius) != 0)
      x->fireBlds[k++] = b->id;
  }
  x->fireCenter = c->id;
  ev->end = ai_Time;
  if (ev->end.hour > 20) {
    ev->end.hour = util_Random(10) + 8;
    ev->end.year++;
  }
  ev->end = ai_Time;
  if (ev->end.hour < 7)
    ev->end.hour = util_Random(10) + 8;
}
/* 0x5644e0, the run handler of the fire event 0x4e (AIJOB.fire*; alloc handler he_AllocFire): stage 0 plays the voice
   "Brand_Beginn"; stage 1 (when due) picks the nearest of blds[] (not -1, not center) to the center building by the
   scene positions (d3_PointToWorld, at most 1e8 away) as the new center (none: -1); stage 2 (no center: on to 3)
   sets the center's entry in blds[] to -1 and sends the explosion message 0x4f for it (to the event's character,
   the building, 25, the flag 1 and this event's id), back to stage 1 in 10 minutes; stage 3 waits (10 minutes) while
   a burning event 0x4f of this fire runs, then plays "Brand_Ende" and frees the record; stages -2 / -1 free it */
void he_RunFire(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *c, *b;
  AIJOB *e;
  D3VECTOR4 p1, p2;
  AIBLD *nearest = 0;
  float best = 100000000.0f;
  float dx, dy, dz, d;
  int k;

  switch (ev->stage) {
  case 0:
    snd_QueueVoice(-8, 0, "Brand_Beginn", -1, 100);
    ev->stage++;
    return;
  case 1:
    c = gm_BuildQuery(1, 1, x->fireCenter);
    for (k = 0; k < 16; k++) {
      if (c != 0 && x->fireBlds[k] != -1 && x->fireBlds[k] != c->id &&
          (b = gm_BuildQuery(1, 1, x->fireBlds[k])) != 0) {
        d3_PointToWorld(c->object, &c->object->pos, &p1.v);
        d3_PointToWorld(b->object, &b->object->pos, &p2.v);
        dx = p1.x - p2.x;
        dy = p1.y - p2.y;
        dz = p1.z - p2.z;
        d = (float)sqrt(dx * dx + dy * dy + dz * dz);
        if (d < best) {
          best = d;
          nearest = b;
        }
      }
    }
    if (nearest != 0)
      x->fireCenter = nearest->id;
    else
      x->fireCenter = -1;
    ev->end = ai_Time;
    ev->stage++;
    return;
  case 2:
    if (x->fireCenter != -1) {
      c = gm_BuildQuery(1, 1, x->fireCenter);
      for (k = 0; c != 0 && k < 16; k++) {
        AIMSG m;

        if (x->fireBlds[k] == c->id) {
          x->fireBlds[k] = -1;
          m.type = 0x4f;
          m.to = ai_Chars[ev->chr].netId;
          m.fromId = c->id;
          m.time = ai_Time;
          m.flags = 2;
          m.arg[0] = c->id;
          m.arg[1] = 0x19;
          m.extraFlag = 1;
          m.srcEvent = ev->id;
          cm_SendLongMessage(&m);
        }
      }
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 10, 0);
      ev->stage = 1;
      return;
    }
    ev->stage++;
    return;
  case 3:
    for (e = he_FindEvent(1, 0, 0x4f); e != 0; e = he_NextEvent()) {
      if (e->burnFire == ev->id) {
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 10, 0);
        return;
      }
    }
    snd_QueueVoice(-8, 0, "Brand_Ende", -1, 100);
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  }
}
/* 0x564860, the allocation handler of the burning event 0x4f (AIJOB.burn*): helpers[] = -1, the due clock and the second
   clock are now, state 0; no building bld: the record is freed; else the burning time is scaled by the distance
   (d3_PointToWorld positions) to the nearest building of kind 3 (gm_NearestBuilding) times 0.001, at most 1.5
   (none: 1.0) */
void he_AllocBurn(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b, *n;
  D3VECTOR4 p1, p2;
  float dx, dy, dz;
  float
      scale; /* a float: the original keeps the 1.0f a load (fld dword [1.0f]) joined with the distance */

  memset(x->burnHelpers, -1, sizeof x->burnHelpers);
  ev->end = ai_Time;
  ev->clock60 = ai_Time;
  x->burnState = 0;
  b = gm_BuildQuery(1, 1, x->burnBld);
  if (b == 0) {
    he_FreeEvent(ev);
    return;
  }
  n = gm_NearestBuilding(b, 3);
  if (n != 0) {
    d3_PointToWorld(b->object, &b->object->pos, &p1.v);
    d3_PointToWorld(n->object, &n->object->pos, &p2.v);
    dx = p1.x - p2.x;
    dy = p1.y - p2.y;
    dz = p1.z - p2.z;
    scale = sqrt(dx * dx + dy * dy + dz * dz);
    scale *= 0.001;
  } else {
    scale = 1.0f;
  }
  scale = min(1.5, scale);
  ev->exSlot = -1;
  x->burnDuration = (int)(x->burnDuration * scale);
}
/* 0x5649b0, the run handler of the burning event 0x4f (AIJOB.burn*; alloc handler he_AllocBurn): a posted event (opts 2)
   waits for its cm slot. Stage 0, every 4 minutes while state < 3 (the building gone: on to stage 1; its flag
   0x5a bit 0: stage -1): on the building's scene object the fire grows by one step: state 0 plays "Stichflamme_s"
   at it and, for the player's building, the voice "Brand_Betroffen" and (news) the message box 0x42d6; state 1
   attaches the loop "Brand_l"; the step's dummy ("dummy_FAHNE", "dummy_RAUCH_0", "dummy_BRAND", else the first)
   gives the place (+-32 in x / z, 20 down) where the script "specialEvents\hausbrand.esc" is run as
   "brand_he_<id>_<state>"; at state 1 a posted event sends the healthy characters of job kind 0 / 4 sent to the
   building (at most 16, helpers[]) to the nearest building of kind 3 to scoop water ("arbeit/schoepfen"). Stage 1,
   every 4 minutes: the building loses the worked minutes since the second clock / 3 in state (the burning time
   less that times the rain factor); the player hears "Brand_Zerstoert" (level 25 / 10 / 0 voices, at most every
   0x20d ticks); below state 3 back to stage 0; the helpers at the door ("dummy_TUER", 80 away) go back into the
   building, the others to the water; burnt down or gone: the event ends (cm_SendExSetHE). Stages -2 / -1: the
   helpers are sent back into the building, the three scripts stopped, the building's sound freed, the record freed */
void he_RunBurn(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b, *n;
  AICHAR *c;
  D3OBJECT *o;
  EVTSCRIPT *sc;
  struct SBSAMPLE *smp;
  struct D3SOUND *snd;
  int i, k, dmg, left, scene;
  float f, f6;
  double r;

  if ((ev->opts & 2) != 0 && ev->exSlot != -1) {
    if (cm_GetSlotState(ev->exSlot) == 0)
      return;
    ev->exSlot = -1;
  }
  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, x->burnBld);
    if (b != 0 && (b->flags5a & 1) != 0) {
      ev->stage = -1;
      return;
    }
    if (b != 0 && x->burnState < 3) {
      D3VECTOR4 p = {-243.0f, -90.0f, 190.0f};
      char names[3][64] = {"dummy_FAHNE", "dummy_RAUCH_0", "dummy_BRAND"};
      char text[0x400];

      scene = d3_CurrentScene;
      if (b->object != 0) {
        d3if_SelectScene(0, 1);
        if (x->burnState == 1) {
          smp = sb_GetSample(0, "Brand_l");
          if (smp != 0) {
            snd = d3snd_Attach(smp, b->object, 0x6b, 2200.0f);
            if (snd != 0)
              d3snd_Play(snd, 0, 0, 0);
          }
        } else if (x->burnState == 0) {
          smp = sb_GetSample(0, "Stichflamme_s");
          if (smp != 0)
            d3snd_PlayAt(smp, b->object, 0x6b, 2200.0f);
          if (b->owner == ai_PlayerId) {
            snd_QueueVoice(-8, 0, "Brand_Betroffen", 0, 100);
            if (x->burnNews != 0) {
              txt_Format(text, 0x42d6, b);
              he_MessageBoxQuickjump(ai_Chars[ai_PlayerId].netId, -1, text, 0,
                                     0x5ed, b->id, -1, 0, ch_EmptyName);
            }
          }
        }
        o = d3_FindObject(b->object, 0x100, 0, names[x->burnState]);
        if (o != 0)
          d3_PointToWorld(o, &o->pos, &p.v);
        else
          o = d3_FindObject(b->object, 0x100, 0, "dummy_FAHNE");
        if (o != 0) {
          d3_PointToWorld(o, &o->pos, &p.v);
          p.x = p.x + util_Random(0x40) - 32.0f;
          p.z = p.z + util_Random(0x40) - 32.0f;
          p.y -= 20.0;
          sc = evt_Load("specialEvents\\hausbrand.esc");
          if (sc != 0) {
            sprintf(sc->name, "brand_he_%i_%i", ev->id, x->burnState);
            evt_RunScriptArgs(sc, 3, (int)p.x, (int)p.y, (int)p.z);
            sc->group = 0;
          }
        }
      } else if ((ev->opts & 2) != 0) {
        ev->exSlot = cm_SendExSetHE(-1, ev);
        return;
      }
      ev->end = ai_Time;
      ev->clock60 = ai_Time;
      gm_AddTime(&ev->end, 0, 4, 0);
      d3if_SelectScene(scene, 1);
    } else {
      ev->stage++;
    }
    if (b == 0)
      ev->end = ai_Time;
    if ((ev->opts & 2) != 0 && x->burnState == 1) {
      k = 0;
      n = gm_NearestBuilding(b, 3);
      if (n != 0) {
        for (i = 0; i < 768; i++) {
          if (ai_Chars[i].health != 0 && ai_Chars[i].scene != 0 &&
              ai_Chars[i].scene->group == b->id &&
              (ai_Chars[i].jobKind == 0 || ai_Chars[i].jobKind == 4) &&
              k < 16) {
            c = &ai_Chars[i];
            x->burnHelpers[k] = c->netId;
            cm_SendCharClear(x->burnHelpers[k], 0, 0);
            cm_SendChrStop(x->burnHelpers[k]);
            cm_SendChrGotoBuilding(x->burnHelpers[k], n->id, -1, 0, 1, "Brand");
            cm_SendChrAnim(x->burnHelpers[k], "arbeit/schoepfen",
                           util_Random(2) + 1);
            k++;
          }
        }
      }
    }
    if (x->burnState < 3)
      x->burnState++;
    return;
  case 1:
    if ((ev->opts & 2) == 0)
      return;
    b = gm_BuildQuery(1, 1, x->burnBld);
    if (x->burnDuration > 0 && b != 0) {
      D3VECTOR4 p;

      f = 1.0f;
      f6 = gm_FixedWorkMinutesBetween(&ev->clock60, &ai_Time) * 0.16666667f;
      dmg = (int)(f6 + f6);
      if (d3t_Rain != 0) {
        r = d3t_Rain->count * 0.002;
        f = (float)(r * 0.7 + 1.0);
      }
      x->burnDuration = (int)(x->burnDuration - dmg * f);
      gm_ChangeBuildingState(b, -dmg);
      if (b->owner == ai_PlayerId && tb_Calls > x->burnVoiceAt + 0x20d) {
        left = b->level - dmg;
        if (left <= 0) {
          snd_QueueVoice(-8, 0, "Brand_Zerstoert", 2, 100);
          x->burnVoiceAt = tb_Calls;
        } else if (left <= 10) {
          snd_QueueVoice(-8, 0, "Brand_Zerstoert", 1, 100);
          x->burnVoiceAt = tb_Calls;
        } else if (left <= 25) {
          snd_QueueVoice(-8, 0, "Brand_Zerstoert", 0, 100);
          x->burnVoiceAt = tb_Calls;
        }
      }
      ev->end = ai_Time;
      ev->clock60 = ai_Time;
      gm_AddTime(&ev->end, 0, 4, 0);
      if (x->burnState < 3)
        ev->stage = 0;
      b = 0;
      n = 0;
      for (k = 0; k < 16; k++) {
        if (x->burnHelpers[k] != -1) {
          if (b == 0) {
            b = gm_BuildQuery(1, 1, x->burnBld);
            n = gm_NearestBuilding(b, 3);
          }
          c = gm_FindChar(x->burnHelpers[k]);
          if (c != 0 && c->scene != 0 && c->scene->group == -1 &&
              CH_ACTIONS(c->scene) == 0) {
            o = d3_FindObject(b->object, 0x100, 0, "dummy_TUER");
            if (o != 0) {
              d3_PointToWorld(o, &o->pos, &p.v);
              if (d3_VecEqual(&c->scene->obj->pos, &p.v, 80.0f) == 0)
                cm_SendChrGotoBuilding(x->burnHelpers[k], b->id, -1, 0, 1,
                                       "Brand");
              else if (n != 0)
                cm_SendChrGotoBuilding(x->burnHelpers[k], n->id, -1, 0, 1,
                                       "Brand");
            }
          }
        }
      }
    }
    if (x->burnDuration <= 0 || b == 0)
      ev->exSlot = cm_SendExSetHE(-1, ev);
    return;
  case -2:
  case -1: {
    char name[0x100];

    b = gm_BuildQuery(1, 1, x->burnBld);
    if ((ev->opts & 2) != 0 && b != 0) {
      for (k = 0; k < 16; k++) {
        if (x->burnHelpers[k] != -1) {
          cm_SendChrStop(x->burnHelpers[k]);
          cm_SendChrGotoBuilding(x->burnHelpers[k], b->id, -1, 0, 0, "Brand");
        }
      }
    }
    for (k = 0; k < 3; k++) {
      sprintf(name, "brand_he_%i_%i", ev->id, k);
      sc = evt_FindByName(name);
      if (sc != 0)
        evt_Stop(sc);
    }
    if (b != 0 && b->object != 0 && b->object->sound != 0)
      d3snd_Free(b->object->sound);
    he_FreeEvent(ev);
    return;
  }
  }
}
/* 0x5652b0, the allocation handler of the storm (WIRBELSTURM) event 0x50: the buildings of kind 6 (gm_BuildQuery (1, 6) / gm_BuildNext) that are no home / type 10 and have a scene object are collected (at most 0x100); stormBlds[1..15] = -1, stormBlds[0] is the target: the event's own building id, else a random pick of the list; the nearby ones within radius +0xf0 (d3_VecEqual on their scene positions) become stormBlds[1..15]; the two words +0x100 / +0x104 = 0; the due clock is now */

void he_AllocStorm(AIJOB *ev) {
  AIBLD *list[0x100];
  AIBLD *b, *c;
  int n, i;
  unsigned short k;

  n = 0;
  k = 1;
  for (b = gm_BuildQuery(1, 6); b != 0; b = gm_BuildNext()) {
    if (gm_IsHomeType(b) == 0 && gm_IsType10(b) == 0 && b->object != 0)
      list[n++ & 0xffff] = b;
  }
  for (i = 1; i < 0x10; i++)
    ev->stormBlds[i] = -1;
  if (ev->stormBlds[0] == -1) {
    c = list[util_Random(n)];
    ev->stormBlds[0] = c->id;
  } else {
    c = gm_BuildQuery(1, 1, ev->stormBlds[0]);
  }
  for (i = 0; i < (n & 0xffff) && k < 0x10; i++) {
    b = list[i];
    if (b != c && d3_VecEqual(&b->object->pos, &c->object->pos,
                              (float)ev->stormRadius) != 0)
      ev->stormBlds[k++] = b->id;
  }
  ev->stormW100 = 0;
  ev->stormW104 = 0;
  ev->end = ai_Time;
}
/* 0x565410, the run handler of the storm event (type 0x50, its alloc handler 0x5652b0): state 0 writes the storm forecast into
   sv_Weather for the three hours after now (clouds 1000, storm 3) and runs again two hours ahead; state 1 damages the stock of
   the 16 buildings the alloc handler collected (gm_ChangeBuildingState, -(random(5) + 5)) once, then frees the record */

void he_RunStormEvent(AIJOB *e) {
  AIBLD *b;
  int i;

  switch (e->stage) {
  case 0:
    for (i = ai_Time.hour + 1; i < ai_Time.hour + 4; i++) {
      sv_Weather.clouds[i] = 1000;
      sv_Weather.storm[i] = 3;
    }
    e->end.hour = ai_Time.hour + 2;
    e->end.min = 0;
    e->stage = e->stage + 1;
    return;
  case 1: {
    int n, dmg;
    AIBLD *b;

    if ((e->opts & 2) != 0 && e->stormDue != 0) {
      for (n = 0; n < 0x10; n++) {
        if (e->stormBlds[n] != -1 &&
            (b = gm_BuildQuery(1, 1, e->stormBlds[n])) != 0) {
          dmg = util_Random(5) + 5;
          gm_ChangeBuildingState(b, -dmg);
        }
      }
      e->stormDue = 0;
    }
    he_FreeEvent(e);
    return;
  }
  case -2:
  case -1:
    he_FreeEvent(e);
    return;
  default:
    return;
  }
}
/* 0x565500, the allocation handler of the healing event 0x6c (he_RunHealing): the character AIJOB.ownerCh is sent into
   its building (the message's from) and that room, the health left is 200, the clocks are now and the next run is
   400 minutes ahead */

void he_AllocHealing(AIJOB *ev) {
  AIJOB *x = ev;
  AICHAR *c;
  AIBLD *b;
  AIOBJ *f;

  f = 0;
  c = gm_FindChar(x->healCharId);
  b = gm_FindBuildingById(ev->from);
  if (x->healRoom != -1)
    f = gm_FindObjectInst(x->healRoom);
  sv_MoveToGroup(b, f, c->id, ev);
  x->healAmount = 200;
  x->healEnd = ai_Time;
  ev->start = ai_Time;
  ev->end = ai_Time;
  ev->clock60 = ai_Time;
  gm_AddTime(&x->healEnd, 0, 400, 0);
}

/* 0x565620, the run handler of the healing event 0x6c (its alloc handler he_AllocHealing): stage 0 heals the character
   AIJOB.ownerCh step by step - the minutes since the last step (AIJOB.clock60) times 0.5 is the step, the health ratio
   times 100.0 plus the step must stay below 100.0 (gm_HealthRatio, gm_AddHealth), else the stage advances; the due clock
   is 10 minutes ahead and the last step time is now. Stage 1 releases the character from the job (sv_MoveToGroup with no
   group) and tells its owner (news 0x1a18, the voice "_NACHRICHTEN_HS_80"), then frees the record; the stages -2 / -1 release
   it and free it too */

void he_RunHealing(AIJOB *ev) {
  AIJOB *x = ev;
  AICHAR *c;
  AIBLD *b;
  int d;
  float step;
  float v;
  char text[0x200];

  switch (ev->stage) {
  case 0:
    c = gm_FindChar(x->healCharId);
    if (c == 0) {
      he_FreeEvent(ev);
      return;
    }
    d = gm_MinutesBetween(&ev->clock60, &ai_Time);
    step = 5.0f * ((float)d * 0.1f);
    v = gm_HealthRatio(c) * 100.0;
    if (x->healAmount > 0 && step + v < 100.0f) {
      gm_AddHealth(c->id, (int)step);
      x->healAmount = (int)((double)x->healAmount - step);
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 10, 0);
    } else {
      ev->stage++;
    }
    ev->clock60 = ai_Time;
    return;
  case 1:
    c = gm_FindChar(x->healCharId);
    b = gm_FindBuildingById(ev->from);
    if (c != 0 && b != 0) {
      sv_MoveToGroup(b, 0, c->id, 0);
      txt_Format(text, 0x1a18, b, c->id);
      he_MessageBoxQuickjump(ai_Chars[ev->chr].netId, -1, text, 0, 0x5f2,
                             ev->from, -1, 0, "_NACHRICHTEN_HS_80");
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    c = gm_FindChar(x->healCharId);
    if (c != 0)
      sv_MoveToGroup(0, 0, c->id, 0);
    he_FreeEvent(ev);
    return;
  default:
    return;
  }
}
/* 0x565850, the allocation handler of the new-worker event 0x6e (AIJOB.newWorker*): no building bld: the record is freed;
   a building of type kind 2 creates a character (cm_SendCreateCharacter kind 2, 0x16 + random(5), the title of
   group random(12) + 1 rank 1), the others ask for a worker of the type's last job (the last nonzero of jobs[],
   cm_SendMessage3d with the type's rank title2); slot is the message's send slot; the due clock is now */
void he_AllocNewWorker(AIJOB *ev) {
  AIJOB *w = ev;
  AIBLD *b;
  AIBTYPE *t;
  int i, title;
  int job = 0;

  b = gm_FindBuildingById(w->newWorkerBld);
  if (b == 0) {
    he_FreeEvent(ev);
    return;
  }
  t = &ai_BTypes[b->type];
  if (t->kind != 2) {
    for (i = 5; i >= 0; i--) {
      if (t->jobs[i] != 0) {
        job = t->jobs[i];
        break;
      }
    }
    w->newWorkerSlot = cm_SendMessage3d(b, 1, t->title2, job);
  } else {
    title = gm_TitleNumber(util_Random(12) + 1, 1);
    w->newWorkerSlot = cm_SendCreateCharacter(2, -1, -1, util_Random(5) + 0x16,
                                              -1, title, 0, 2);
  }
  ev->end = ai_Time;
}
/* 0x565940, the run handler of the new-worker event 0x6e: when the hire message's slot (0xac) is done, its value (the new worker) and the building (0xb4) are taken; the building's master (0x25, a character index) gets the ownership message 0x38 and the worker the reward (0x4c47e0 with gm_PlayerFactor (0xbb8, ai_OwnPlayer)); with a share (0xbc) the master (kinds 6 / 7 get the news 0x17e6) also gets it and the worker is sent to its place ("InitBetrieb"); the record is always freed, stages -1 / -2 free it */

void he_RunNewWorker(AIJOB *ev) {
  AIJOB *w = ev;
  AICHAR *r, *own;
  AIBLD *o;
  int st, v[2];
  char text[0x400];

  st = ev->stage;
  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    if (cm_GetSlotState(w->newWorkerSlot) == 0)
      return;
    r = (AICHAR *)cm_GetSlotValue(w->newWorkerSlot);
    o = gm_FindBuildingById(w->newWorkerBld);
    if (r != 0 && o != 0) {
      if (o->masterId != 0xffff)
        cm_SendOwnership(o->id, ai_Chars[o->masterId].netId, r->netId);
      else
        cm_SendOwnership(o->id, r->netId, r->netId);
      cm_SendMoveGoods(r->netId, -1, ai_OwnPlayer,
                       gm_PlayerFactor(0xbb8, ai_OwnPlayer));
      if (w->newWorkerShare != 0) {
        own = &ai_Chars[o->masterId];
        if (own != 0) {
          if (own->kind == 6 || own->kind == 7) {
            txt_Format(text, 0x17e6, o, r->id, w->newWorkerShare);
            he_MessageBoxQuickjump(own->netId, -1, text, 0, 0x5ec, o->id, -1, 0,
                                   "_NACHRICHTEN_HS_30");
          }
          cm_SendMoveGoods(own->netId, -1, ai_OwnPlayer, w->newWorkerShare);
        }
        cm_SendOwnership(o->id, r->netId, r->netId);
        if (he_FigureContact(r, &v[0], &v[1]) != 0)
          cm_SendChrGotoBuilding(r->netId, v[0], v[1], 0, 0, "InitBetrieb");
      }
    }
  }
  he_FreeEvent(ev);
}
/* 0x565b00, the allocation handler of the player's death event 0x71 (its run handler he_RunDiePlayer): the player
   (AICHAR, +0xac) must exist (else the error message and free); his health +8 is cleared and the next run is now */

void he_AllocDiePlayer(AIJOB *ev) {
  AICHAR *p;

  p = gm_FindChar(ev->ownerCh);
  if (p == 0) {
    err_Message("he_AllocDiePlayer: player not found!");
    he_FreeEvent(ev);
    return;
  }
  p->health = 0;
  ev->end = ai_Time;
}
/* 0x565b60, the run handler of the player's death event 0x71 (its alloc handler he_AllocDiePlayer): stage 0 stops
   his figure's follow script (0x4284a0 / 0x429e90) and moves him out of his group; stage 1 waits until that script
   is gone; stage 2 clears his health, his building and his scene record, lays the figure down (0x405610, 0x40b2f0
   (obj, 0x36, 1): the animation name "bewegung/zu_boden_sinken" at +0xf0) and runs again an hour later; stage 3
   informs the owner 0x4c4e00 (netId, 1) when the event option 2 is set; then the record is freed */

void he_RunDiePlayer(AIJOB *ev) {
  AICHAR *p, *q;
  CHACTION *a;
  int o;

  switch (ev->stage) {
  case 0:
    p = gm_FindChar(ev->ownerCh);
    if (p != 0) {
      if (p->scene != 0 && (o = p->scene->scriptId) != -1)
        evt_Stop(evt_FindById(o));
      sv_MoveToGroup(0, 0, p->id, 0);
      ev->stage++;
      return;
    }
    break;
  case 1:
    q = gm_FindChar(ev->ownerCh);
    if (q != 0) {
      if (q->scene != 0 && q->scene->scriptId != -1)
        return;
      ev->stage++;
      return;
    }
    break;
  case 2:
    p = gm_FindChar(ev->ownerCh);
    if (p != 0) {
      p->health = 0;
      sv_MoveToGroup(0, 0, p->id, 0);
      p->bld = 0;
      if (p->scene != 0) {
        ch_StopActions(p->scene);
        a = ch_AddAction(p->scene, 0x36, 1);
        strcpy(a->u.name, "bewegung/zu_boden_sinken");
      }
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 1, 0, 0);
      ev->stage++;
      return;
    }
    break;
  case 3:
    q = gm_FindChar(ev->ownerCh);
    if (q != 0 && (ev->opts & 2) != 0)
      cm_SendKillCharacter(q->netId, 1);
    break;
  case -2:
  case -1:
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x565d10, the allocation handler of the kill-player event 0x72 (AIJOB.kill*, its run handler he_RunKillPlayer): the
   character (+0xac) must exist (else the error message and free); when another event of the type 0x72 already kills
   him this one is freed, else the party +0xb0, its slot +0xb4 and the cm slot +0x84 are -1 and the due clock is the
   start clock */

void he_AllocKillPlayer(AIJOB *ev) {
  AIJOB *x = ev;
  AICHAR *p;
  AIJOB *o;

  p = gm_FindChar(x->killChr);
  if (p == 0) {
    err_Message("he_AllocKillPlayer: player not found!");
    he_FreeEvent(ev);
    return;
  }
  for (o = he_FindEvent(1, 0, 0x72); o != 0; o = he_NextEvent()) {
    if (o != ev && o->killChr == x->killChr) {
      he_FreeEvent(ev);
      return;
    }
  }
  x->killSlot = -1;
  ev->end = ev->start;
  x->killParty = -1;
  ev->exSlot = -1;
}
/* 0x565db0, the run handler of the kill-player event 0x72 (AIJOB.kill*; alloc handler he_AllocKillPlayer): stages -1 / -2 and
   a character gone free the record; while the character is in a scene party (partyId, not in stage 6) the next run
   is 5 minutes ahead. Stage 0: no scene character: a posted event (opts 2) goes to stage 3, else freed; its script is
   stopped, the character leaves its group (sv_MoveToGroup), a posted event tells the owner of its building
   (characters of kind 6 / 7) the news 0x42f4, bld = 0. Stage 1 waits for the script to end. Stage 2 lays the scene
   character down (0x36 "bewegung/zu_boden_sinken"), the next run 30 minutes ahead (opts 4: freed at once). Stage 3:
   characters of kind 6 / 7 get a funeral party (G28REC kind 8, flags 0xa0, in 30 minutes, the character its host and
   member: cm_SendNewParty, slot) and stage 6, the others stage 4 in 2 minutes. Stage 4: the successor
   (ai_FindSuccessor; none: stage 5) inherits (gm_InheritEstate) and, for kinds 5 / 6 / 7, a lower b00d is raised
   to the dead one's; the character is killed (cm_SendKillCharacter), the record freed. Stage 5: the player's
   character inherits. Stage 6 polls the party's slot (2: stage 4, else party = its value, stage 7 in two hours).
   Stage 7: a living character frees the record; a party gone: stage 4, else two hours more */
void he_RunKillPlayer(AIJOB *ev) {
  AIJOB *x = ev;
  AICHAR *p, *h;
  AIBLD *q;
  CHACTION *a;
  G28REC m;
  char text[0x400];
  int r;
  int id;

  if (ev->stage == -1) {
    he_FreeEvent(ev);
    return;
  }
  p = gm_FindChar(x->killChr);
  if (p == 0) {
    he_FreeEvent(ev);
    return;
  }
  if (p->partyId != -1 && ev->stage != 6) {
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 5, 0);
    return;
  }
  switch (ev->stage) {
  case 0:
    if (p->scene == 0) {
      if ((ev->opts & 2) == 0) {
        he_FreeEvent(ev);
        return;
      }
      ev->stage = 3;
      return;
    }
    if (p->scene->scriptId != -1)
      evt_Stop(evt_FindById(p->scene->scriptId));
    sv_MoveToGroup(0, 0, p->id, 0);
    if ((ev->opts & 2) != 0 && (q = p->bld) != 0 &&
        (ai_Chars[q->owner].kind == 6 || ai_Chars[q->owner].kind == 7)) {
      txt_Format(text, 0x42f4, p->id, q);
      he_MessageBoxQuickjump(ai_Chars[p->bld->owner].netId, p->bld->id, text, 0,
                             0x60a, p->bld->id, -1, ch_EmptyName, ch_EmptyName);
    }
    p->bld = 0;
    ev->stage++;
    return;
  case 1:
    if (p->scene != 0 && p->scene->scriptId != -1)
      return;
    ev->stage++;
    return;
  case 2:
    if (p->scene != 0) {
      ch_StopActions(p->scene);
      a = ch_AddAction(p->scene, 0x36, 1);
      if (a != 0)
        strcpy(a->u.name, "bewegung/zu_boden_sinken");
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0x1e, 0);
    ev->stage++;
    if ((ev->opts & 4) != 0)
      he_FreeEvent(ev);
    return;
  case 3:
    if (p->kind != 6 && p->kind != 7) {
      gm_AddTime(&ev->end, 0, 2, 0);
      ev->stage = 4;
      return;
    }
    memset(&m, 0, sizeof(m));
    m.kind = 8;
    m.flags = 0xa0;
    m.time = ai_Time;
    gm_AddTime(&m.time, 0, 0x1e, 0);
    id = p->netId;
    m.thing = -1;
    m.used = 1;
    m.host = id;
    m.members[0] = id;
    x->killSlot = cm_SendNewParty(&m);
    gm_AddTime(&ev->end, 0, 1, 0);
    ev->stage = 6;
    return;
  case 4:
    h = ai_FindSuccessor(p);
    if (h == 0) {
      ev->stage = 5;
      return;
    }
    gm_InheritEstate(p, h);
    if ((p->kind == 6 || p->kind == 7 || p->kind == 5) && p->level > h->level) {
      cm_BeginFieldBlock(h, h->netId);
      cm_AddFieldDelta(1, 1, 0xd, &p->level);
      cm_SendFieldDeltas();
    }
    cm_SendKillCharacter(p->netId, gm_MayRemoveChar(p));
    he_FreeEvent(ev);
    return;
  case 5:
    gm_InheritEstate(p, ai_PlayerChar);
    cm_SendKillCharacter(p->netId, gm_MayRemoveChar(p));
    he_FreeEvent(ev);
    return;
  case 6:
    r = cm_GetSlotState(x->killSlot);
    if (r == 0)
      return;
    if (r == 2) {
      ev->end = ai_Time;
      ev->stage = 4;
      return;
    }
    ev->end = ai_Time;
    x->killParty = ((G28REC *)cm_GetSlotValue(x->killSlot))
                       ->id; /* the slot's value: the new party */
    gm_AddTime(&ev->end, 2, 0, 0);
    ev->stage = 7;
    return;
  case 7:
    if (p->health > 0) {
      he_FreeEvent(ev);
      return;
    }
    if (cm_PartyById(x->killParty) == 0) {
      x->killSlot = -1;
      x->killParty = -1;
      ev->end = ai_Time;
      ev->stage = 4;
      return;
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 2, 0, 0);
    return;
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  }
}
/* 0x5662d0, the allocation handler of the night watchman (type 0x73): the start and due clocks are now, the speaker
   +0xac is random(5) - 5 (the voice source of the run's announcements), the first run at the morning hour
   gm_DayStartHours[season] */

void he_AllocNightWatch(AIJOB *ev) {
  AIJOB *x = ev;

  ev->end = ai_Time;
  ev->start = ai_Time;
  x->nightWatchSpeaker = util_Random(5) - 5;
  ev->end.hour = (unsigned short)gm_DayStartHours[gm_ClockSeason(&ai_Time)];
  ev->end.min = 0;
}
/* 0x566370, the run handler of the night watchman event 0x73 (AIJOB.nightWatch*): freed once the year changed since its
   start; the season (gm_ClockSeason) picks the morning hour gm_DayStartHours[] and the evening hour
   gm_DayEndHours[]. Stage 0 waits for the morning hour (hour in [h, h + 1)), then rings the bell
   "_NACHTWAECHTER_GLOCKEN_SFX_SHORT" (ai_GameState) and, with the switch byte 1 and random(10) > 7, the speaker
   announces ("_NACHTWAECHTER_ANKUENDIGUNGEN", the morning time 7 / 8 / autumn 8 / 9, random(10) > 7: a morning
   saying); the next run at the evening hour. Stage 1 the same for the evening hour (19 / 20 / autumn 20 / 21, the
   evening saying); the next run at 22:30. Stage 2 at 22:30 .. 22:49 rings the bell and (switch byte 1, random(10) > 7)
   "_NACHTWAECHTER_NACHTS_ENDE", then frees the record. A stage still waiting sets its due clock to now and adds a
   second to the game clock ai_Time (gm_AddTime on ai_Time, not on the due clock) */
void he_RunNightWatch(AIJOB *ev) {
  AIJOB *x = ev;
  int season;

  if (ai_Time.year != ev->start.year) {
    he_FreeEvent(ev);
    return;
  }
  season = gm_ClockSeason(&ai_Time);
  switch (ev->stage) {
  case 0:
    if (!(ai_Time.hour >= gm_DayStartHours[season] &&
          ai_Time.hour < gm_DayStartHours[season] + 1.0f)) {
      ev->end = ai_Time;
      break;
    }
    if (ai_GameState != 0)
      snd_QueueVoice(-7, 0, "_NACHTWAECHTER_GLOCKEN_SFX_SHORT", -1, 0xfa);
    if (ai_GameSwitches.byte[1] != 0 && ai_GameState != 0 &&
        util_Random(10) > 7 && ai_GameState != 0) {
      snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_ANKUENDIGUNGEN",
                     -1, 0xfa);
      if (gm_DayStartHours[season] == 7.0f) {
        snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_MORGENS_ZEIT_7",
                       -1, 0xfa);
      } else if (gm_DayStartHours[season] == 8.0f) {
        if (season == 2)
          snd_QueueVoice(x->nightWatchSpeaker, 0,
                         "_NACHTWAECHTER_MORGENS_ZEIT_HERBST", -1, 0xfa);
        else
          snd_QueueVoice(x->nightWatchSpeaker, 0,
                         "_NACHTWAECHTER_MORGENS_ZEIT_8", -1, 0xfa);
      } else if (gm_DayStartHours[season] == 9.0f) {
        snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_MORGENS_ZEIT_9",
                       -1, 0x3e8);
      }
      if (util_Random(10) > 7)
        snd_QueueVoice(x->nightWatchSpeaker, 0,
                       "_NACHTWAECHTER_MORGENS_SPRUECHE", -1, 0x3e8);
    }
    ev->end = ai_Time;
    ev->end.hour = (unsigned short)gm_DayEndHours[season];
    ev->end.min = 0;
    ev->stage++;
    return;
  case 1:
    if (!(ai_Time.hour >= gm_DayEndHours[season] &&
          ai_Time.hour < gm_DayEndHours[season] + 1.0f)) {
      ev->end = ai_Time;
      break;
    }
    if (ai_GameState != 0)
      snd_QueueVoice(-7, 0, "_NACHTWAECHTER_GLOCKEN_SFX_SHORT", -1, 0xfa);
    if (ai_GameSwitches.byte[1] != 0 && ai_GameState != 0 &&
        util_Random(10) > 7 && ai_GameState != 0) {
      snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_ANKUENDIGUNGEN",
                     -1, 0xfa);
      if (gm_DayEndHours[season] == 19.0f) {
        snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_ABENDS_ZEIT_7",
                       -1, 0xfa);
      } else if (gm_DayEndHours[season] == 20.0f) {
        if (season == 2)
          snd_QueueVoice(x->nightWatchSpeaker, 0,
                         "_NACHTWAECHTER_ABENDS_ZEIT_8_HERBST", -1, 0xfa);
        else
          snd_QueueVoice(x->nightWatchSpeaker, 0,
                         "_NACHTWAECHTER_ABENDS_ZEIT_8", -1, 0xfa);
      } else if (gm_DayEndHours[season] == 21.0f) {
        snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_ABENDS_ZEIT_9",
                       -1, 0xfa);
      }
      if (util_Random(10) > 7)
        snd_QueueVoice(x->nightWatchSpeaker, 0,
                       "_NACHTWAECHTER_ABENDS_SPRUECHE", -1, 0x3e8);
    }
    ev->end = ai_Time;
    ev->end.hour = 0x16;
    ev->end.min = 0x1e;
    ev->stage++;
    return;
  case 2:
    if (ai_Time.hour < 0x16 || ai_Time.min < 0x1e || ai_Time.min >= 0x32) {
      ev->end = ai_Time;
      break;
    }
    if (ai_GameState != 0) {
      snd_QueueVoice(-7, 0, "_NACHTWAECHTER_GLOCKEN_SFX_SHORT", -1, 0xfa);
      if (ai_GameSwitches.byte[1] != 0 && util_Random(10) > 7)
        snd_QueueVoice(x->nightWatchSpeaker, 0, "_NACHTWAECHTER_NACHTS_ENDE",
                       -1, 0xfa);
    }
    he_FreeEvent(ev);
    return;
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  default:
    return;
  }
  gm_AddTime(&ai_Time, 0, 0, 1);
}
/* 0x566830, the run handler of the robbery event 0x75 ("Raubzug", AIJOB.robbery*; alloc handler he_AllocDueInOne), the
   burglary's twin (he_RunBurglary): the gang is AIJOB.ids. Stage 0 sends the gang to the target ("Raubzug"; no
   target: freed), stage 1 waits (4 minutes) until every member with a scene character is at its door; stage 2: a
   patrol that sees it (he_DetectAttack, range 2500) makes the accusation 0x17 (gv_Accuse, the slot kept) and binds
   it (stage 3); else the gang breaks in, each member with a gesture of three (cm_SendChrAnim), stage 5 in 15 minutes.
   Stage 3 waits for the accusation, then the patrol's character executes the proof (stage 4, 10 minutes); stage 4
   waits (6 minutes) while the patrol is still bound, then the gang's player pays the patrol's character a reward
   (gm_PlayerFactor of 550 + a random 0 .. 199; the news 0x19ea / 0x19eb), the patrol's start building counts it
   (field 0x65), every member loses 100 + a random 0 .. 99 health and the gang walks home ("Entdeckt"); freed.
   Stage 5 (no target or player: stage -2) brings the gang home (gm_SkillPoints 2 each) and accuses the owner's
   building; an unprotected target (he_NoProtectionEvent) loses 0.35 of its worth (gm_BuildingValues) to the
   player and, with a home store (0x116), each goods of the target's stall (0x2a), by half a chance, n * 0.1 of its
   amount (at least 1, n the gang's size) sold into the store and counted at its price (no store: the loot is lost);
   the player gets the loot list (0x1a85), the owner 0x1a86; a failed robbery tells the player 0x19e7 and the owner
   0x19e9; freed. Stages -2 / -1 send the gang home ("Raubzug") and free the record */
void he_RunRobbery(AIJOB *ev) {
  AIJOB *x = ev;
  AIBLD *b, *g, *gb;
  AICHAR *c, *owner, *master, *guard;
  AIOBJ *room = 0, *stall, *store = 0, *it;
  int n = 0;
  AIJOB *w;
  AIJOB *patrol;
  AIFIN *fin;
  CRIME *cr;

  char names[3][64] = {"gestik/mit_faust_droh", "gestikg/herranwinken",
                       "spezial/meckern"};
  char text[0x200];
  char line[0x100];
  int k, ok, amt, id;

  switch (ev->stage) {
  case 0:
    b = gm_BuildQuery(1, 1, x->robberyTarget);
    if (b == 0)
      break;
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        sv_MoveToGroup(b, 0, c->id, ev);
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], b->id, -1, 0, 1, "Raubzug");
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 4, 0);
    ev->stage = 1;
    return;
  case 1:
    id = x->robberyTarget;
    b = gm_BuildQuery(1, 1, id);
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0 &&
          c->scene != 0 && sv_IsAtDoor(c, b) == 0) {
        ev->end = ai_Time;
        gm_AddTime(&ev->end, 0, 4, 0);
        return;
      }
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0, 1);
    ev->stage = 2;
    return;
  case 2:
    b = gm_BuildQuery(1, 1, x->robberyTarget);
    if (b != 0) {
      HEDETECT d;

      owner = &ai_Chars[b->owner];
      d.bld = b;
      d.range = 2500.0f;
      d.ev = ev;
      d.found = 0;
      if (he_DetectAttack((intptr_t)&d) != 0) {
        patrol = d.found;
        x->robberySlot =
            gv_Accuse(0x17, 1, ai_Chars[ev->chr].netId, owner->netId, b->id);
        x->robberyWatch = patrol->id;
        x->robberyGuardBld = patrol->patrolStart;
        ev->stage = 3;
        ev->end = ai_Time;
        return;
      }
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        sv_MoveToGroup(b, 0, c->id, ev);
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], b->id, -1, 0, 0, "Raubzug");
        cm_SendChrAnim(ev->ids[k], names[util_Random(3)], 1);
      }
    }
    ev->stage = 5;
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 0, 0xf, 0);
    return;
  case 3:
    if (x->robberySlot != -1 && cm_GetSlotState(x->robberySlot) == 0)
      return;
    b = gm_BuildQuery(1, 1, x->robberyTarget);
    w = he_FindEvent(1, 1, x->robberyWatch);
    if (b == 0 || w == 0 || w->patrolWait != ev->id || x->robberySlot == -1) {
      ev->stage = -1;
      return;
    }
    guard = gm_FindChar(x->robberyWatch);
    cr = (CRIME *)cm_GetSlotValue(x->robberySlot);
    if (guard != 0 && cr != 0)
      cm_SendProofExecuted(cr->id, guard->netId);
    ev->stage = 4;
    gm_AddTime(&ev->end, 0, 10, 0);
    return;
  case 4:
    w = he_FindEvent(1, 1, x->robberyWatch);
    if (w == 0) {
      ev->stage = -1;
      return;
    }
    if (w->patrolWait == ev->id) {
      gm_AddTime(&ev->end, 0, 6, 0);
      return;
    }
    b = gm_BuildQuery(1, 1, x->robberyTarget);
    if (b != 0) {
      int reward;

      master = gm_FindChar(ai_Chars[ev->chr].netId);
      guard = &ai_Chars[w->chr];
      if (guard != 0 && master != 0) {
        reward = gm_PlayerFactor(util_Random(200) + 0x226, ai_OwnPlayer);
        txt_Format(text, 0x19ea, b, reward, guard->id);
        he_ShowNews(master->netId, master->netId, text, 1, 0x5f0,
                    "_NACHRICHTEN_HS_76");
        txt_Format(text, 0x19eb, b, reward);
        he_ShowNews(guard->netId, guard->netId, text, 1, 0x5f0,
                    "_NACHRICHTEN_HS_77");
        cm_SendMoveGoodsUnchecked(guard->netId, master->netId, ai_OwnPlayer,
                                  reward);
      }
      gb = gm_BuildQuery(1, 1, x->robberyGuardBld);
      if (gb != 0) {
        cm_BeginFieldBlock(gb, gb->id);
        cm_AddFieldValues(4, 1, 0x65, &reward); /* 0x65: AIBLD.earnings */
        cm_SendFieldDeltas();
      }
    }
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0)
        gm_AddHealth(c->id, -100 - util_Random(100));
    }
    g = gm_BuildQuery(1, 1, x->robberyHome);
    if (g == 0)
      break;
    room = gm_GetGebaeudeHauptraum(g);
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1) {
        cm_SendChrStop(ev->ids[k]);
        cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                               "Entdeckt");
      }
    }
    break;
  case 5:
    b = gm_BuildQuery(1, 1, x->robberyTarget);
    master = gm_FindChar(ai_Chars[ev->chr].netId);
    if (b == 0 || master == 0) {
      ev->stage = -2;
      return;
    }
    owner = &ai_Chars[b->owner];
    g = gm_BuildQuery(1, 1, x->robberyHome);
    if (g != 0) {
      room = gm_GetGebaeudeHauptraum(g);
      store = gm_Query(g->objList, 2, 6, 0, 0x116);
      for (k = 0; k < 8; k++) {
        if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
          cm_SendChrStop(ev->ids[k]);
          cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                 "Raubzug");
          n++;
          gm_SkillPoints(c, 2);
          sv_MoveToGroup(g, 0, c->id, 0);
        }
      }
      ok = 1;
      gv_Accuse(0x17, ok, ai_Chars[ev->chr].netId, owner->netId, b->id);
    } else {
      ok = 0;
    }
    if (he_NoProtectionEvent(b) != 0 && ok) {
      char loot[0x400];
      int vals[2];
      int money;

      loot[0] = ch_EmptyName[0];
      memset(loot + 1, 0, sizeof(loot) - 1);
      b = gm_BuildQuery(1, 1, x->robberyTarget);
      stall = gm_Query(b->objList, 2, 6, 0, 0x2a);
      gm_BuildingValues(b, vals);
      money = (int)(vals[0] * 0.35);
      txt_Format(line, (intptr_t)"$Z%T$A", money);
      strcat(loot, line);
      cm_SendMoveGoods(master->netId, owner->netId, ai_OwnPlayer, money);
      cm_BeginFieldBlock(g, g->id);
      cm_AddFieldValues(4, 1, 0x69, &money); /* 0x69: AIBLD.daySum */
      cm_SendFieldDeltas();
      if (stall != 0) {
        if (store != 0) {
          for (it = gm_Query(stall->list, 1, 5); it != 0; it = gm_QueryNext()) {
            if (util_Random(100) > 0x32) {
              amt = gm_ListAmount(stall, it);
              amt = (int)(amt * (n * 0.1));
              if (amt < 1)
                amt = 1;
              sprintf(line, "%i %s$A", amt,
                      txt_Ptrs[TXT_OBJECT_NAMES + 2 * it->id]);
              strcat(loot, line);
              cm_SendExSellObject(store->objId, stall->objId, it->id, amt,
                                  ai_OwnPlayer, 0);
              money = (int)(gm_GoodsPrice(it->id, ai_OwnPlayer) * amt + money);
            }
          }
        } else {
          strcpy(loot, "Leider besitzt Ihr keinen Lagerraum und m\xfc\xdft "
                       "einiges Diebsgut zur\xfc"
                       "cklassen!");
        }
      }
      fin = gm_PlayerRecord(master);
      if (fin != 0)
        fin->burglaryTakings += money;
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0x1a85, owner->id, b);
        strcat(text, loot);
        he_MessageBoxQuickjump(master->netId, master->netId, text, 1, 0x5f0,
                               b->id, -1, 0, ch_EmptyName);
      }
      if (owner->kind == 6 || owner->kind == 7) {
        txt_Format(text, 0x1a86, b, money);
        he_MessageBoxQuickjump(owner->netId, owner->netId, text, 0, 0x5f0,
                               b->id, -1, 0, ch_EmptyName);
      }
    } else {
      b = gm_BuildQuery(1, 1, x->robberyTarget);
      if (b == 0)
        break;
      if (master->kind == 6 || master->kind == 7) {
        txt_Format(text, 0x19e7, owner->id, b, 0x19c1);
        he_MessageBoxQuickjump(master->netId, master->netId, text, 1, 0x5f0,
                               b->id, -1, 0, ch_EmptyName);
      }
      if (owner->kind == 6 || owner->kind == 7) {
        txt_Format(text, 0x19e9, b);
        he_MessageBoxQuickjump(owner->netId, owner->netId, text, 1, 0x5f0,
                               b->id, -1, 0, 0);
      }
    }
    break;
  case -2:
  case -1:
    g = gm_BuildQuery(1, 1, x->robberyHome);
    if (g != 0)
      room = gm_GetGebaeudeHauptraum(g);
    for (k = 0; k < 8; k++) {
      if (ev->ids[k] != -1 && (c = gm_FindChar(ev->ids[k])) != 0) {
        cm_SendChrStop(ev->ids[k]);
        if (g != 0 && room != 0)
          cm_SendChrGotoBuilding(ev->ids[k], g->id, room->objId, 0, 0,
                                 "Raubzug");
        else
          cm_SendChrGotoBuilding(ev->ids[k], -1, -1, 0, 0, "Raubzug");
        sv_MoveToGroup(0, 0, c->id, 0);
      }
    }
    break;
  default:
    return;
  }
  he_FreeEvent(ev);
}
/* 0x567620, the allocation handler of the title-period event 0x7c (he_RunTitleDue): the due clock is now plus
   20 minutes */

void he_AllocTitleDue(AIJOB *ev) {
  ev->end = ai_Time;
  gm_AddTime(&ev->end, 0, 0x14, 0);
}

float gm_TitlePeriodServed(int n, struct AITIME *out);

/* 0x567660, the run handler of the title-period event 0x7c (alloc handler he_AllocTitleDue): stages -1 / -2 free the record;
   stage 0: a character already told (flags1c8 bit 31) is asked again in 4 hours; one whose title period is not
   served yet (gm_TitlePeriodServed below 1.0) in 20 minutes; else he gets the message 0x25 (flags 9, arg[0] his
   netId, arg[2] 2: cm_SendLongMessage), the bit 31 is set and the next run is 4 hours ahead */
void he_RunTitleDue(AIJOB *ev) {
  AIMSG m;
  AITIME due;

  switch (ev->stage) {
  case 0:
    if ((ai_Chars[ev->chr].flags1c8 & 0x80000000) != 0) {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 4, 0, 0);
      return;
    }
    if (gm_TitlePeriodServed(ev->chr, &due) >= 1.0) {
      memset(&m, 0, sizeof(m));
      m.type = 0x25;
      m.fromId = -1;
      m.flags = 9;
      m.arg[2] = 2;
      m.arg[0] = m.to = ai_Chars[ev->chr].netId;
      cm_SendLongMessage(&m);
      ai_Chars[ev->chr].flags1c8 |= 0x80000000;
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 4, 0, 0);
    } else {
      ev->end = ai_Time;
      gm_AddTime(&ev->end, 0, 0x14, 0);
    }
    return;
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  }
}
/* 0x567810, "he_OpenHelpEvents": reads the tutorial hint script "<game path>\tutorial\<name>.ini" into he_Hints
   (cleared first): per line not containing "//" the ':' separated fields are the text label (txt_FindKey; an unknown
   label: the message "he_OpenHelpEvents(): invalid textlabel:%s", built and not shown), the due day, hour and minute;
   the reading stops at the end of the file or past the table's end; an unopenable file gives the message box
   "he_OpenHelpEvents(): Could not open help-definition!" */
void he_OpenHelpEvents(char *name) {
  char sep[2] = ":";
  char path[260];
  char label[0x100], line[0x100], msg[0x400];
  int n;
  FILE *f;
  char *t;
  int k, i;

  sprintf(path, "%s\\tutorial\\%s.ini", main_GamePath, name);
  for (i = 0; i < 0x200; i++)
    ((int *)he_Hints)[i] = 0;
  f = fopen(path, "rt");
  if (f == 0) {
    MessageBoxA(0, "he_OpenHelpEvents(): Could not open help-definition!",
                "Error", 0x30);
    return;
  }
  n = 0;
  for (;;) {
    memset(line, 0, sizeof(line));
    fgets(line, 0x100, f);
    if (strstr(line, "//") == 0) {
      k = 0;
      for (t = strtok(line, sep); t != 0; t = strtok(0, sep)) {
        if (k == 0) {
          strcpy(label, t);
          he_Hints[n].text = txt_FindKey(label);
          if (he_Hints[n].text == -1)
            sprintf(msg, "he_OpenHelpEvents(): invalid textlabel:%s", label);
        } else if (k == 1) {
          he_Hints[n].year = atoi(t);
        } else if (k == 2) {
          he_Hints[n].hourW = atoi(t);
        } else if (k == 3) {
          he_Hints[n].min = atoi(t);
        }
        k++;
      }
      n++;
      if (n > 128)
        return;
    }
    if (feof(f)) {
      fclose(f);
      return;
    }
  }
}
/* 0x5679b0, the allocation handler of the tutorial hint event 0x83 (he_RunHint): the hint script is picked by the
   job id (+0x164) of the local player (gm_TitleGroup: 1 / 2 / 3 "help_events_hw", 5 / 6 "help_events_alpa",
   7 "help_events_kirche", 4 "help_events_wirt", 0xb "help_events_dieb") and read by he_OpenHelpEvents; the due
   clock is the first hint entry's */

void he_AllocHint(AIJOB *ev) {
  int k;

  k = gm_TitleGroup(ai_Chars[ai_PlayerId].jobId);
  if (k == 1 || k == 2 || k == 3)
    he_OpenHelpEvents("help_events_hw");
  else if (k == 5 || k == 6)
    he_OpenHelpEvents("help_events_alpa");
  else if (k == 7)
    he_OpenHelpEvents("help_events_kirche");
  else if (k == 4)
    he_OpenHelpEvents("help_events_wirt");
  else if (k == 0xb)
    he_OpenHelpEvents("help_events_dieb");
  ev->end = ai_Time;
  ev->end.year = he_Hints[0].year;
  ev->end.hour = he_Hints[0].hour;
  ev->end.min = he_Hints[0].min;
}
/* 0x567a80, the run handler of the tutorial hint event 0x83: state 0 shows the he_Hints entry of the event's index (its text id through he_ShowNews to the local player, when the hint option ai_GamePanel.byte[1] is on), steps to the next entry and sets the next run to that entry's due clock; an empty entry ends (state 1); stages -1 / -2 free the record */

void he_RunHint(AIJOB *ev) {
  AIJOB *h = ev;
  int st, v;

  st = ev->stage;
  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    v = he_Hints[h->hintEntry].text;
    if (v != 0 && v != -1 && ai_GamePanel.byte[1] != 0)
      he_ShowNews(ai_Chars[ai_PlayerId].netId, -1, txt_Ptrs[v], 0x40, 0x5f9, 0);
    h->hintEntry++;
    if (he_Hints[h->hintEntry].text == 0) {
      ev->stage = 1;
      return;
    }
    ev->end = ai_Time;
    ev->end.year = he_Hints[h->hintEntry].year;
    ev->end.hour = he_Hints[h->hintEntry].hour;
    ev->end.min = he_Hints[h->hintEntry].min;
    return;
  }
  he_FreeEvent(ev);
}
/* 0x567b80, the allocation handler of the tips event 0x84 (he_RunTip): the first run is today, 4 days later when a
   tutorial hint event 0x83 exists; at 8:00; gm_Shuffled fills the tip order table he_TipOrder */

void he_AllocTip(AIJOB *ev) {
  ev->end = ai_Time;
  if (he_FindEvent(1, 0, 0x83) != 0)
    ev->end.year = ai_Time.year + 4;
  else
    ev->end.year = ai_Time.year;
  ev->end.hour = 8;
  ev->end.min = 0;
  gm_Shuffled(0x1a, he_TipOrder);
}
/* 0x567c00, the run handler of the tips event 0x84: state 0 shows the next of the 27 tip texts (TXT_TIP_TEXTS[he_TipOrder[entry]]) to the local player while the tips option ai_GamePanel.byte[3] is on, steps the entry and sets the next run to random(4) + 8 units; with the tips off it runs again in 1 unit; stages -1 / -2 free the record */

void he_RunTip(AIJOB *ev) {
  AIJOB *t = ev;
  int st;

  st = ev->stage;
  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    if (ai_GamePanel.byte[3] != 0) {
      he_ShowNews(ai_Chars[ai_PlayerId].netId, -1,
                  txt_Ptrs[TXT_TIP_TEXTS + he_TipOrder[t->tipEntry]], 0, 0x5f9,
                  0);
      t->tipEntry++;
      if (t->tipEntry > 0x1a)
        ev->stage = 1;
      ev->end = ai_Time;
      gm_AddTime(&ev->end, util_Random(4) + 8, 0, 0);
      return;
    }
    ev->end = ai_Time;
    gm_AddTime(&ev->end, 1, 0, 0);
    return;
  }
  he_FreeEvent(ev);
}
/* 0x567d20, the allocation handler of the tutorial building tour event 0x85 (he_RunTutorialBuildingTour): the due
   clock is today at 7:00 */

void he_AllocTutorialBuildingTour(AIJOB *ev) {
  ev->end = ai_Time;
  ev->end.hour = 7;
  ev->end.min = 0;
}
/* 0x567d60, the run handler of the tutorial event 0x85 (only while cm_TutorialActive, else stage -1 frees it):
   stage 0 (in a running game, ai_GameState) sets the character's kind byte to 5; stage 1 before 22:00 collects
   the character's buildings (gm_BuildQuery(1, 4, chr), at most 0x40) plus the market building, picks one at
   random and shows it in the panel (sv_SelectPanelObject; in 3 of 4 cases, unless it is the market, at its main
   object or main room), the next run random(2) hours and random(0x3c) minutes from now; from 22:00 the next
   stage; stage 2 sets the kind byte to 6 and frees the event */
void he_RunTutorialBuildingTour(AIJOB *ev) {
  int n;
  AIBLD *pick;
  AIBLD *b;
  AIOBJ *o;
  AIBLD *list
      [0x40]; /* the market goes in after at most 0x40 buildings: one past the end, as in the original's frame */

  n = 0;
  if (cm_TutorialActive == 0)
    ev->stage = -1;
  switch (ev->stage) {
  case 0:
    if (ai_GameState == 0)
      return;
    ai_Chars[ev->chr].kind = 5;
    ev->stage++;
    return;
  case 1:
    if (ai_Time.hour >= 22) {
      ev->stage++;
      return;
    }
    for (b = gm_BuildQuery(1, 4, ev->chr); b != 0 && n < 0x40;
         b = gm_BuildNext())
      list[n++] = b;
    list[n++] = ai_MarketBuilding;
    if (n != 0) {
      pick = list[util_Random(n)];
      if (util_Random(4) != 0 && pick != ai_MarketBuilding) {
        o = gm_BuildingMainObject(pick);
        if (o == 0)
          o = gm_GetGebaeudeHauptraum(pick);
        if (o != 0)
          sv_SelectPanelObject(pick, o->objId, ch_EmptyName);
        else
          sv_SelectPanelObject(pick, -1, ch_EmptyName);
      } else {
        sv_SelectPanelObject(pick, -1, ch_EmptyName);
      }
    }
    ev->end = ai_Time;
    ev->end.hour += util_Random(2);
    ev->end.min = util_Random(0x3c);
    return;
  case 2:
    ai_Chars[ev->chr].kind = 6;
    /* fall through */
  case -2:
  case -1:
    he_FreeEvent(ev);
    return;
  default:
    return;
  }
}
/* 0x567f00, the allocation handler of the guard patrol event 0xa6 (he_RunPatrolEvent): its first run is today
   at 6:00 (end = ai_Time, then hour 6 and min 0) and its sound slot exSlot -1 */

void he_AllocPatrolEvent(AIJOB *ev) {
  ev->end = ai_Time;
  ev->exSlot = -1;
  ev->end.hour = 6;
  ev->end.min = 0;
}

/* 0x567f50, one step of a guard cart c on the patrol event 0xa6 ev (he_RunPatrolEvent), unless the cart runs a job:
   below a fill of 40 + random(32) percent the cart is refilled (the message 0x10 to its owner, gm_ObjectBuildingOwner,
   for 100 - fill, due in 10 seconds; the owner pays 100 - fill times 0.008 of the cart's price, cm_SendMoveGoods);
   else at the building of its route's current point: at the route's start it first waits the steps its level allows
   (12, 8, 4, 2, 0); once at that building's door (and the building is no town market, or the cart belongs to the
   patrol building) it moves on to the next point of the route (wrapping to 0; the field send's cm slot goes to
   ev->exSlot), else, in a building, it sends the message 0xf (the cart, the building it is in, the point's building)
   @deep deep s32: the hunk is the order of the message 0xf fill (the last block): the original stores the
   ai_Time words, to and car first, then type / fromId / flags just before the time's last word, loads
   bld->id and at->id after those (m has escaped through the first branch's cm_SendLongMessage: pointer
   loads wait for the stores), pushes &m, and only then stores n and ch (and flag9e). Ours stores n / ch
   before the push in every order: 720 orders of type/fromId/to/flags/time/car (best p160 = fromId, to,
   time, car, type, flags: 8 ins but draft, code 20), x the 6 orders of n/ch/flag9e on the six best (no
   gain), 4000 sampled orders of all nine (10 ins at best), climb --ops move,swap 4 rounds from the tree
   and from p160 (8). A fresh block-local m in each branch puts the n / ch stores after the push as the
   original but also the type / fromId / flags stores, and hoists bld->id above the memset (8 ins / 71
   bytes, draft): the escape is right, the store/push order is not. Not kept (every 8-ins row grades
   draft). (declaration set: not byte under the declaration sets tried (best shape)) */
void he_PatrolStep(AIJOB *ev, AIOBJ *c) {
  AICHAR *owner;
  RTPOINT *p;
  AIBLD *at;
  AIBLD *bld;
  int n; /* the goods to refill, then the next route point */
  int count;
  int waits[5];
  float price;
  AIMSG m;

  if (c->job24 != 0)
    return;
  owner = gm_ObjectBuildingOwner(c);
  if (c->fill < util_Random(0x20) + 0x28) {
    memset(&m, 0, sizeof(m));
    m.fromId = m.to = owner->netId;
    m.type = 0x10;
    m.flags = 1;
    m.time = ai_Time;
    gm_AddTime(&m.time, 0, 0, 10);
    m.car = c->objId;
    m.dst[0] = 5;
    m.u.s.cost = 0;
    m.n = 100 - c->fill;
    price = gm_ItemPrice(c->id, 100) * 0.008f;
    n = 100 - c->fill;
    cm_SendMoveGoods(-1, owner->netId, ai_OwnPlayer, (int)(n * price));
    cm_SendLongMessage(&m);
    return;
  }
  p = rt_PointAt(c->route, c->routeIdx);
  if (p == 0 || (at = gm_FindBuildingById(p->buildingId)) == 0)
    return;
  if (c->routeIdx == 0) {
    waits[0] = 12;
    waits[1] = 8;
    waits[2] = 4;
    waits[3] = 2;
    waits[4] = 0;
    if (++c->patrolWait < waits[c->patrolLevel])
      return;
    c->patrolWait = 0;
  }
  if (sv_IsCartAtDoor(c, at) != 0 &&
      (gm_IsType10(at) == 0 || c->ownerId == he_PatrolBuilding->id)) {
    count = rt_PointCount(c->route);
    n = c->routeIdx + 1;
    if (n >= count)
      n = 0;
    cm_BeginFieldBlock(c, c->objId);
    cm_AddFieldValue(4, 1, (char *)&c->routeIdx - cm_FieldObject, &n);
    ev->exSlot = cm_SendFieldValues();
    return;
  }
  bld = gm_ObjectBuilding(c);
  if (bld == 0)
    return;
  memset(&m, 0, sizeof(m));
  m.type = 0xf;
  m.fromId = -1;
  m.to = owner->netId;
  m.flags = 2;
  m.time = ai_Time;
  m.car = c->objId;
  m.n = bld->id;
  m.ch = at->id;
  m.flag9e = 1;
  cm_SendLongMessage(&m);
}
/* 0x568220, the run handler of the guard patrol event 0xa6 (only while the game state byte ai_GameState is set; waits for
   the sound handle exSlot): state 0 looks up the patrol building (kind 0x44) and calls he_PatrolStep for every guard group
   cart (gm_Query (0, 2, 7, 4, 0x1d)) that has a route, is not flagged and has a pause counter; it runs again 15 minutes
   later; the negative states free the record */

void he_RunPatrolEvent(AIJOB *e) {
  AIOBJ *g;
  int st;

  if (ai_GameState == 0)
    return;
  if (e->exSlot != -1 && cm_GetSlotState(e->exSlot) == 0)
    return;
  st = e->stage;
  e->exSlot = -1;
  if (st < -2)
    return;
  if (st >= 0) {
    if (st != 0)
      return;
    he_PatrolBuilding = gm_BuildQuery(1, 0, 0x44);
    for (g = gm_Query(0, 2, 7, 4, 0x1d); g != 0; g = gm_QueryNext()) {
      if (g->route != 0 && (g->flags20 & 1) == 0 && (g->flags13 & 0x20) == 0 &&
          g->patrolOn != 0)
        he_PatrolStep(e, g);
    }
    e->end = ai_Time;
    gm_AddTime(&e->end, 0, 0xf, 0);
    return;
  }
  he_FreeEvent(e);
}
/* 0x568310, registers the event types 0x02 .. 0xa6 (second part, after 0x553060): he_SetEventHandlers (type, alloc, run) for each (a non-zero result = out of table space: return 1), the type texts 0x52b350 (type, name, 0, menu id, icon) for the types with an entry in the event list, and the tip table 0x505ca0 (0x1a, 0x6fa1e0); returns 0 */
int he_RegisterEventTypes02(void) {
  if (he_SetEventHandlers(2, he_AllocSale, he_RunSale) != 0)
    return 1;
  if (he_SetEventHandlers(6, he_AllocCustomersHire, he_RunCustomers) != 0)
    return 1;
  if (he_SetEventHandlers(7, he_AllocCustomersHire, he_RunHire) != 0)
    return 1;
  if (he_SetEventHandlers(15, he_AllocTransport, he_RunTransport) != 0)
    return 1;
  if (he_SetEventHandlers(16, he_AllocCartRepair, he_RunCartRepair) != 0)
    return 1;
  if (he_SetEventHandlers(17, he_AllocMessageBox, he_RunMessageBox) != 0)
    return 1;
  if (he_SetEventHandlers(18, he_AllocSlotOrderStore, he_RunSlotOrder) != 0)
    return 1;
  if (he_SetEventHandlers(19, he_AllocSlotOrderStore, he_RunStoreExtension) !=
      0)
    return 1;
  if (he_SetEventHandlers(20, he_AllocHerbGathering, he_RunHerbGathering) != 0)
    return 1;
  sv_RegisterActivity(20, 0, 1, 1280, 174);
  if (he_SetEventHandlers(21, he_AllocAnimalHunt, he_RunAnimalHunt) != 0)
    return 1;
  sv_RegisterActivity(21, "Getier", 1, 1280, 174);
  if (he_SetEventHandlers(22, he_AllocStudy, he_RunStudy) != 0)
    return 1;
  sv_RegisterActivity(22, "Trainieren", 0, 1289, -1);
  if (he_SetEventHandlers(23, he_AllocEvent17, he_RunEvent17) != 0)
    return 1;
  if (he_SetEventHandlers(25, he_AllocSabotage, he_RunSabotage) != 0)
    return 1;
  if (he_SetEventHandlers(24, he_AllocSpying, he_RunSpying) != 0)
    return 1;
  if (he_SetEventHandlers(26, he_AllocBrawl, he_RunBrawl) != 0)
    return 1;
  if (he_SetEventHandlers(27, he_AllocTheft, he_RunTheft) != 0)
    return 1;
  if (he_SetEventHandlers(28, he_AllocRepair, he_RunRepair) != 0)
    return 1;
  if (he_SetEventHandlers(30, he_AllocUpgrade, he_RunUpgrade) != 0)
    return 1;
  if (he_SetEventHandlers(32, he_AllocDemolish, he_RunDemolish) != 0)
    return 1;
  if (he_SetEventHandlers(33, he_AllocBuyBuilding, he_RunBuyBuilding) != 0)
    return 1;
  if (he_SetEventHandlers(31, he_AllocEvent1f, he_RunEvent1f) != 0)
    return 1;
  if (he_SetEventHandlers(35, he_AllocKredit, he_RunKredit) != 0)
    return 1;
  if (he_SetEventHandlers(36, he_AllocDueIsStart, he_RunEvent24) != 0)
    return 1;
  if (he_SetEventHandlers(37, he_RunDueNow, he_RunMasterExamNotice) != 0)
    return 1;
  if (he_SetEventHandlers(38, he_AllocMasterExamPass, he_RunMasterExamPassed) !=
      0)
    return 1;
  if (he_SetEventHandlers(39, he_AllocEvent27, he_RunEvent27) != 0)
    return 1;
  if (he_SetEventHandlers(40, he_AllocHarvest, he_RunHarvest) != 0)
    return 1;
  sv_RegisterActivity(40, 0, 1, 1279, 188);
  if (he_SetEventHandlers(49, he_AllocDueInOne, he_RunDismissal) != 0)
    return 1;
  if (he_SetEventHandlers(50, he_AllocEvent32, he_RunPromotion) != 0)
    return 1;
  if (he_SetEventHandlers(51, he_AllocWorkerQuits, he_RunWorkerQuits) != 0)
    return 1;
  if (he_SetEventHandlers(52, he_AllocDueIsStart, he_RunWorkerTheft) != 0)
    return 1;
  if (he_SetEventHandlers(56, he_AllocEvent38, he_RunEvent38) != 0)
    return 1;
  if (he_SetEventHandlers(57, he_AllocEvent39_3e, he_RunEvent39) != 0)
    return 1;
  if (he_SetEventHandlers(58, he_AllocRoutine, he_RunRoutine) != 0)
    return 1;
  if (he_SetEventHandlers(59, he_AllocMarket, he_RunMarketSupervisor) != 0)
    return 1;
  if (he_SetEventHandlers(60, he_AllocEvent3c, he_RunKidnap) != 0)
    return 1;
  sv_RegisterActivity(60, 0, 0, 1284, -1);
  if (he_SetEventHandlers(61, he_AllocRansom, he_RunRansom) != 0)
    return 1;
  if (he_SetEventHandlers(62, he_AllocEvent39_3e, he_RunRansomDemand) != 0)
    return 1;
  if (he_SetEventHandlers(63, he_AllocBurglary, he_RunBurglary) != 0)
    return 1;
  sv_RegisterActivity(63, 0, 0, 1290, -1);
  if (he_SetEventHandlers(64, he_AllocDueInOne, he_RunBuildingSpying) != 0)
    return 1;
  sv_RegisterActivity(64, 0, 0, 1283, -1);
  if (he_SetEventHandlers(72, he_AllocAmbush, he_RunAmbush) != 0)
    return 1;
  sv_RegisterActivity(72, 0, 0, 1282, -1);
  if (he_SetEventHandlers(73, he_AllocDueInOne, he_RunAttack) != 0)
    return 1;
  sv_RegisterActivity(73, 0, 0, 1290, -1);
  if (he_SetEventHandlers(78, he_AllocFire, he_RunFire) != 0)
    return 1;
  if (he_SetEventHandlers(79, he_AllocBurn, he_RunBurn) != 0)
    return 1;
  if (he_SetEventHandlers(80, he_AllocStorm, he_RunStormEvent) != 0)
    return 1;
  if (he_SetEventHandlers(108, he_AllocHealing, he_RunHealing) != 0)
    return 1;
  sv_RegisterActivity(108, "Heilen", 0, 1285, -1);
  if (he_SetEventHandlers(110, he_AllocNewWorker, he_RunNewWorker) != 0)
    return 1;
  if (he_SetEventHandlers(113, he_AllocDiePlayer, he_RunDiePlayer) != 0)
    return 1;
  if (he_SetEventHandlers(114, he_AllocKillPlayer, he_RunKillPlayer) != 0)
    return 1;
  if (he_SetEventHandlers(115, he_AllocNightWatch, he_RunNightWatch) != 0)
    return 1;
  if (he_SetEventHandlers(117, he_AllocDueInOne, he_RunRobbery) != 0)
    return 1;
  sv_RegisterActivity(117, 0, 0, 1282, -1);
  if (he_SetEventHandlers(124, he_AllocTitleDue, he_RunTitleDue) != 0)
    return 1;
  if (he_SetEventHandlers(131, he_AllocHint, he_RunHint) != 0)
    return 1;
  if (he_SetEventHandlers(132, he_AllocTip, he_RunTip) != 0)
    return 1;
  if (he_SetEventHandlers(133, he_AllocTutorialBuildingTour,
                          he_RunTutorialBuildingTour) != 0)
    return 1;
  if (he_SetEventHandlers(166, he_AllocPatrolEvent, he_RunPatrolEvent) != 0)
    return 1;
  gm_Shuffled(0x1a, he_TipOrder);
  return 0;
}

/* dcp unit split: the functions of he_b the rest of he uses */
void he_AllocRecipeResearch(struct AIJOB *ev);
void he_RunRecipeResearch(struct AIJOB *ev);
void he_AllocResearchRecipe(struct AIJOB *ev);
void he_RunResearchRecipe(struct AIJOB *ev);
void he_AllocTrainShare(struct AIJOB *ev);
void he_RunTrainShare(struct AIJOB *ev);
void he_AllocAlchemistDay(AIJOB *e);
void he_RunAlchemistDay(struct AIJOB *ev);
void he_AllocSecretRoom(AIJOB *e);
void he_RunSecretRoom(struct AIJOB *ev);
void he_AllocEvent9a(struct AIJOB *ev);
void he_FreeEventNow(AIJOB *r);
void he_AllocDomizilEvent(AIJOB *e);
void he_RunDomizilEvent(struct AIJOB *ev);
void he_AllocHaunting(struct AIJOB *ev);
void he_RunHaunting(struct AIJOB *ev);
void he_AllocDecay(struct AIJOB *ev);
void he_RunDecay(struct AIJOB *ev);
void he_AllocPlunder(struct AIJOB *ev);
void he_RunPlunder(struct AIJOB *ev);
void he_PlunderTakePrice(int *a, AICHAR *c);
void he_PlunderFailNews(int *a, AICHAR *c);
void he_RunPlunderOffer(struct AIJOB *ev);
void he_AllocMasterWork(struct AIJOB *ev);
void he_RunMasterWork(struct AIJOB *ev);
void he_AllocGraveCare(struct AIJOB *ev);
void he_RunGraveCare(struct AIJOB *ev);
void he_AllocDeathDue(struct AIJOB *ev);
void he_RunDeathDue(struct AIJOB *ev);
void he_AllocGraveTraining(struct AIJOB *ev);
void he_RunGraveTraining(struct AIJOB *ev);
void he_AllocMeeting(struct AIJOB *ev);
void he_RunMeeting(struct AIJOB *ev);
void he_AllocMeetingScene(struct AIJOB *ev);
void he_RunMeetingScene(struct AIJOB *ev);
void he_AllocPlunderOfferLease(struct AIJOB *ev);
void he_AnswerGraveLease(struct AIJOB *ev);
void he_ExamCancelled(struct AIJOB *ev);
void he_RunGraveLease(struct AIJOB *ev);
void he_AllocGraveyardWorkers(struct AIJOB *ev);
void he_RunGraveyardWorkers(struct AIJOB *ev);
void he_RunGraveyardTheft(struct AIJOB *ev);
void he_AllocCouncil(struct AIJOB *ev);
void he_RunCouncil(struct AIJOB *ev);
void he_AllocGypsyApproach(struct AIJOB *ev);
void he_RunGypsyApproach(struct AIJOB *ev);
void he_GypsyApproach(struct AICHAR *pl, struct AICHAR *per, int a);
void he_GypsyDisease(AICHAR *pl, AICHAR *per);
void he_GypsyRumour(AICHAR *pl, AICHAR *per);
void he_GypsyWorkerQuits(AICHAR *pl, AICHAR *per);
void he_GypsySwapSkills(AICHAR *pl, AICHAR *per);
void he_GypsyCurse(AICHAR *pl, AICHAR *per);
void he_GypsySlowdown(AICHAR *pl, AICHAR *per);
void he_GypsyFee(AICHAR *pl, int a);
void he_AllocGypsyCurse(struct AIJOB *ev);
void he_RunGypsyCurse(struct AIJOB *ev);
void he_AllocGypsySlowdown(struct AIJOB *ev);
void he_RunGypsySlowdown(struct AIJOB *ev);
int he_HasEvent9f(AICHAR *a);
void he_AllocTrialScene(struct AIJOB *ev);
void he_RunTrialScene(struct AIJOB *ev);
void he_AllocMeeting4(struct AIJOB *ev);
void he_RunCircusShow(struct AIJOB *ev);
void he_CircusShowIncome(struct AIJOB *ev, int n);
void he_AllocPettyLoss(struct AIJOB *ev);
void he_RunPettyLoss(struct AIJOB *ev);
void he_AllocEventGood(struct AIJOB *ev);
void he_RunEventGood(struct AIJOB *ev);
void he_GiveDomizilGood(AICHAR *per);
void he_EventGoodMoney(AICHAR *per);
void he_EventGoodRefund(AICHAR *per);
/* dcp unit split: the declarations that moved to he_b (copies: drop what he does not use) */
float gm_MeanLiking(int c, int n, int *ids);
void sv_CountGroupMembers(struct AIJOB *g);
int he_HasEvent9f(AICHAR *a);
void init_HookObject(struct D3OBJECT *o, void *p, int kind);
struct D3OBJECT *
ai_FindNearestObject(float *ref, struct D3OBJECT **list); /* 0x58fe10 (lc.c) */
void sv_CreateBanners(struct AIBLD *b);
void snd_PlayFavourComment(void);
void ai_DomizilMessage(struct AICHAR *to, struct AICHAR *c, struct AIOBJ *obj,
                       int level);
void ai_DomizilMessageResearchKind(struct AICHAR *param_1,
                                   struct AICHAR *param_2,
                                   struct AIOBJ *param_3, int param_4);
void ai_DomizilMessageResearch(struct AICHAR *param_1, struct AICHAR *param_2,
                               struct AIOBJ *param_3, int param_4);
void ai_DomizilMessageTask(struct AICHAR *to, struct AICHAR *c,
                           struct AIBLD *bld, struct AIOBJ *obj);
void ai_DomizilMessage04(struct AICHAR *to, struct AICHAR *c,
                         struct AIBLD *bld);
void ai_DomizilMessageAge(struct AICHAR *param_1, struct AICHAR *param_2,
                          struct AIBLD *param_3);
void ai_DomizilMessagePlace(struct AICHAR *to, struct AICHAR *c,
                            struct AIBLD *bld, int placeId);
/* clang-format off */
int ai_PickActionBuilding(struct AICHAR *p, int a, __int64 mask, int lo, float hi, int *out);   /* 0x4a63f0, @original: lo an int, as this unit declares it above */
/* clang-format on */
void he_FreeEventNow(AIJOB *r);                   /* 0x56f040 */
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
void ai_HauntingText(struct AICHAR *param_1, struct AICHAR *param_2,
                     struct AITIME *param_3);         /* 0x5a9910 */
void ai_TellGraveWorkSuccess(struct AICHAR *param_1); /* 0x5a9990 */
void ai_TellGraveWorkFailure(struct AICHAR *param_1); /* 0x5a99e0 */
void ai_GraveyardMessage(struct AICHAR *to, struct AICHAR *worker,
                         struct AICHAR *other, int detail); /* 0x5a9a30 */
void ai_GraveyardMessagePlain(struct AICHAR *param_1, struct AICHAR *param_2,
                              struct AICHAR *param_3); /* 0x5a9af0 */
int ai_PickActionBuildings(struct AICHAR *p, int a, __int64 mask, float lo,
                           float hi, unsigned char n, int *out); /* 0x4a6570 */
int ai_PickPartnerRandomWalk(struct AICHAR *p, unsigned int fl, int n,
                             unsigned short *ids, float lo, float hi,
                             unsigned short *id); /* 0x4a5d30 */
void he_PlunderTakePrice(int *a, AICHAR *c);      /* 0x570bf0 */
void he_PlunderFailNews(int *a, AICHAR *c);       /* 0x570c70 */
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
void ai_ShowGraveOrderExtended(struct AICHAR *param_1, struct AICHAR *param_2,
                               int param_3, int param_4, int param_5,
                               int param_6); /* 0x5a97e0 */
void ai_ShowGraveOrderCancelled(struct AICHAR *param_1, struct AICHAR *param_2,
                                int param_3, int param_4); /* 0x5a9880 */
int gv_OrderExtendGrave(struct AICHAR *c, struct AIBLD *o, int v, int b,
                        short s, int x);       /* 0x4f0700 */
void he_AnswerGraveLease(struct AIJOB *ev);    /* 0x5728d0 */
void he_ExamCancelled(struct AIJOB *ev);       /* 0x5729c0 */
void ai_EndCharExtra(struct AICHAR *o, int f); /* 0x587c40 */
int ls_GetLanguage();                          /* 0x5190a0 */
void he_AllocCouncil(struct AIJOB *ev);        /* 0x573280 */
void he_RunCouncil(struct AIJOB *ev);          /* 0x5732d0 */
void hmt_Update();                             /* 0x4ace40, hmt_Update */
void hmt_Begin();                              /* 0x4ad0a0, hmt_Begin */
void hmt_Election();                           /* 0x4ad1c0, hmt_Election */
void hmt_ClearOffices(void);                   /* 0x4ad510 */
void hmt_DecideElection();                     /* 0x4ad580 */
void he_AllocGypsyApproach(struct AIJOB *ev);  /* 0x5734b0 */
void he_RunGypsyApproach(struct AIJOB *ev);    /* 0x573580 */
void he_AllocGypsyCurse(struct AIJOB *ev);     /* 0x573f20 */
void he_RunGypsyCurse(struct AIJOB *ev);       /* 0x573fb0 */
void he_AllocGypsySlowdown(struct AIJOB *ev);  /* 0x574060 */
void he_RunGypsySlowdown(struct AIJOB *ev);    /* 0x5740d0 */
void he_AllocTrialScene(struct AIJOB *ev);     /* 0x574120 */
void he_RunTrialScene(struct AIJOB *ev);       /* 0x5743c0 */
void he_AllocMeeting4(struct AIJOB *ev);       /* 0x574550 */
void he_RunCircusShow(struct AIJOB *ev);       /* 0x5748d0 */
void he_AllocPettyLoss(struct AIJOB *ev);      /* 0x575150 */
void he_RunPettyLoss(struct AIJOB *ev);        /* 0x5751e0 */
void he_AllocEventGood(struct AIJOB *ev);      /* 0x575320 */
void he_RunEventGood(struct AIJOB *ev);        /* 0x5753a0 */
void he_GypsyApproach(struct AICHAR *pl, struct AICHAR *per,
                      int a);                      /* 0x5736d0 */
void he_GypsyFee(AICHAR *pl, int a);               /* 0x573e30 */
void he_GypsyDisease(AICHAR *pl, AICHAR *per);     /* 0x573760 */
void he_GypsyRumour(AICHAR *pl, AICHAR *per);      /* 0x573820 */
void he_GypsyWorkerQuits(AICHAR *pl, AICHAR *per); /* 0x573970 */
void he_GypsySwapSkills(AICHAR *pl, AICHAR *per);  /* 0x573ae0 */
void he_GypsyCurse(AICHAR *pl, AICHAR *per);       /* 0x573c20 */
void he_GypsySlowdown(AICHAR *pl, AICHAR *per);    /* 0x573d30 */
void sv_MoveToGroup(struct AIBLD *o, struct AIOBJ *it, int c,
                    struct AIJOB *g); /* 0x524260, the group register */
void he_CircusShowIncome(struct AIJOB *ev, int n); /* 0x575030 */
unsigned short
ai_RandomDomizilGoodNotIn(int param_1, unsigned short *param_2); /* 0x5a9e90 */
void he_GiveDomizilGood(AICHAR *per);                            /* 0x575430 */
void he_EventGoodMoney(AICHAR *per);                             /* 0x575540 */
void he_EventGoodRefund(AICHAR *per);                            /* 0x575570 */
/* unlinked: the empty alloc / run handler of the event types without one; LINK folds it (/OPT:ICF) into
   d3io_NoopCallback, 0x44ee40, where the original's registrations (he_SetEventHandlers) point */
void he_NoHandler(AIJOB *ev) {}
