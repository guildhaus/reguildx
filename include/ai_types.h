/* ai.h's records other units need without the rest of ai.h: the game time (mission_types.h's G13MIS)
   and the offer row (f3gm.c's gm_Offers), the goods list AIRECIPE f3gm.c fills: types only. ai.h includes it. */
#ifndef AI_TYPES_H
#define AI_TYPES_H
#include "d3_types.h"                /* D3VECTOR */
#pragma pack(push, 2)
typedef struct AITIME {                 /* 14 bytes: the game clock ai_Time, the AI's last-run time ai_Update.last,
                                           the times of the events and messages (f3gm.c's clock functions) */
    int year;                           /* 0x0, the year (0x578 + it is the calendar year; % 4 the season) */
    unsigned short hour;                /* 0x4, the hour */
    int min;                            /* 0x6, the minute */
    int sec;                            /* 0xa, the second */
} AITIME;
#pragma pack(push, 1)
typedef struct AIOFFERAT {              /* 15 bytes at AIJOB + 0xc4 of the offer event 0x2c (AIJOB.offerAt): the clock
                                           follows the kind byte unaligned, at 0xc5 (the original's pack(1) words) */
    signed char kind;                   /* +0x0, the offer kind compared between the pending offers */
    AITIME clock;                       /* +0x1, the offer's clock: now + 0x18 units, its hour 0xa and minute 0 (the
                                           wedding's day, ai_FillWeddingTab) */
} AIOFFERAT;
#pragma pack(pop)
#pragma pack(pop)

typedef struct G14MSG {                 /* an AI message, the argument of rmsg.c's callbacks (ai_RunMessage) */
    int id;                             /* 0x00, a character id */
    unsigned short type;                /* 0x04, 0..0x44, the table index; text 0x12e7 + type */
} G14MSG;

typedef struct AISTORE {                /* 24 bytes, a stock list per building, gm_Offers[] */
    struct AIBLD *bld;                  /* 0x00 */
    int market;                         /* 0x04, the market / stall object holding the goods (f3gm.c gm_CollectOffers) */
    int goodsObj;                       /* 0x08, the goods object of the offer (the f3gm.c note of 0x7e4b20) */
    int count;                          /* 0x0c, the supply: the stall's amount less a quarter of its stock times the goods' +0x1c, not below 0 */
    float price;                        /* 0x10, the goods price times the building's price factor; gm_CollectOffers sorts by it, highest first */
    int stored;                         /* 0x14, 1 when the building's store object (0xff) holds the goods */
} AISTORE;

typedef struct HEWALKSLOT {
    int chr;                            /* 0x0, the walking character's netId (gm_FindChar), -1 free */
    int target;                         /* 0x4, the building it walks to (gm_FindById's building) */
    unsigned char stage;                /* 0x8, the walk's stage counter */
    unsigned char state;                /* 0x9, flags: 1 counted, 4 done, 0x10 played, 0x20 a character with +0x1f0, 0x40 held */
    unsigned char step;                 /* 0xa, the step through ai_Blds (a random ai_RandomStrides entry) */
    unsigned char bldIndex;             /* 0xb, the ai_Blds index of the building */
    signed char holdHour;               /* 0xc, the hour the character was held at, 0xff none (@original: signed, so
                                           he_StepWalk's test of the sign-extended byte for 0xff never holds) */
    unsigned char pad[3];
} HEWALKSLOT;
typedef struct AIJOB {                  /* 0x14c bytes, a job / event record (he_Events, he_CreateEvent; he_FindEvent / he_NextEvent) */
    unsigned char kind;                 /* 0x00, the message type it was made from, 0: a free record (unsigned:
                                           sv_MoveToGroup / sv_CharStateIcons read it zero-extended, the kinds
                                           0x87 / 0x8c / 0x8f compare as bytes) */
    char pad01[3];
    int id;                             /* 0x04, the event id (ai_NextEventId at its creation) */
    unsigned short chr;                 /* 0x08, the index in ai_Chars of the character it is for (cm_ExAddCrime: of a
                                           kind 0x18 the witness told of the crime) */
    char pad0a[2];
    int netId;                          /* 0x0c, the netId of that character, -1: none (the message's 'to') */
    int from;                           /* 0x10, the message's fromId */
    union {
        int words14[12];                /* 0x14, the message's 12 words from +0x10 */
        struct {                        /* 0x14, of a group job 0x14 (AICHAR.job): its members counted by the title
                                           ranks of their building type (sv_CountGroupMembers) */
            int rank1Count;             /* 0x14, the members of the type's first rank */
            int rank2Count;             /* 0x18, those of its second rank */
        };
    };
    AITIME start;                       /* 0x44, the start time (sv_RefreshPanel measures the progress from it) */
    AITIME end;                         /* 0x52, the end time of the kinds whose length is fixed at the start (0x40, the building jobs 0x1e / 0x1f) */
    AITIME clock60;                     /* 0x60, of a running income event 3 its second clock (the alloc handler 0x568ae0
                                           sets it to the start clock with the due clock +0x52) */
    char pad6e[2];
    int stage;                          /* 0x70, the stage the job has reached (sv_RefreshPanel shows progress only from a kind's timed stage on) */
    struct HEEVSLOT *slot;              /* 0x74, of an event shown in the event bar its slot (he.h he_EventSlots), 0: none */
    unsigned char opts;                 /* 0x78, the event's options from its message: 2 posts it when due, 4 not started yet,
                                           8 shown in the event bar, 0x10 runs every frame (he.c) */
    char pad79[3];
    char *text;                         /* 0x7c, of a message box event 0x11 its text ("messagebox", cm.c), 0 at creation */
    int textSize;                       /* 0x80, the size of that text (ls.c's loader reads it) */
    int exSlot;                         /* 0x84, the cm slot cm_SendExSetHE gave the event (cm_GetSlotState asks it), -1: none */
    struct HEGFXINFO *gfx;              /* 0x88, the gfx info shown over its object (he.h, he_CreateGfxInfo), 0: none */
    union {
        int ids[8];                     /* 0x8c, the message's ids[] */
        int helpers[4];                 /* 0x8c, of a helper job 0x8c the characters on it, -1: a free place
                                           (ai_GypsyHelperWindow counts them) */
        int groupMembers[8];            /* 0x8c, of a group job (AICHAR.job: sv_AddGroupMember, sv_CountGroupMembers)
                                           the members' netIds, -1: a free slot */
    };
    union {                             /* 0xac..0x14b: the message's words from +0x58, or a kind's own record over them
                                           (he.c's event handlers, the lc units' windows) */
        struct {
            union {                             /* 0xac..0xeb: the three unions, or a kind's own words over them */
                struct {
                    union {
                        int cart;                       /* 0xac, of the trade event 0xb the objId of the trading cart (he.c AIJOB.cart;
                                                           ai_CalcMeisterFernhaendler skips the carts a trade event runs with) */
                        int targetBld;                  /* 0xac, of the spy / break-in / attack events 0x40 / 0x3f / 0x49 the
                                                           building spied on, broken into or attacked (the message's arg[0];
                                                           ai_CalcAngriff, ai_CalcMeisterDiebe) */
                        int bldId;                      /* 0xac, of the building events (0x1b, 0x1c, 0x1e, 0x1f, 0x40) their building's id
                                                           (he_AddEventGfxInfo shows their gfx info over it) */
                        int partner1;                   /* 0xac, of a pair event (kinds 0x41 / 0x6f / 0x45, he_EndPersonEvents; the
                                                           domicile event 0x9b, he_NoEvent9bFor) the first partner's netId */
                        int ownerCh;                    /* 0xac, of an event 0x24 / 0x32 the netId of the character it is for (ai_DecideChangeProfession
                                                           skips a character that has one; the promotion handlers find it with gm_FindChar) */
                        union {
                            int id;                     /* 0xac */
                            struct {
                                unsigned short lo;      /* 0xac */
                                unsigned short hi;      /* 0xae */
                            } w;
                        } u;
                        unsigned short orderGood;       /* 0xac, of an order (event kind 2): the goods it makes (gm_UpdateTechTree) */
                        unsigned char thiefClass;       /* 0xac, of the thief event 0x16 (AIMSG.thiefClass, 0x54 further on): 2 / 3,
                                                           the two thief rows of lc.c ai_TrainingWindow */
                    };
                    union {
                        int unkb0;                      /* 0xb0 */
                        unsigned short upgradeGood;     /* 0xb0, of the room upgrade event 0x1f the good being built in
                                                           (AIMSG.roomUpgrade.good; lc.c ai_RoomUpgradeWindow) */
                        int salePrice;                  /* 0xb0, of a building sale event 0x1b the asking price (ai_BuyBuildingWindow
                                                           shows it, the buyer's money must cover it) */
                        int graveSize;                  /* 0xb0, of the graveyard order events 0x92 / 0x93 (the master exam at
                                                           a graveyard): the size of the grave the order names, an index into
                                                           ai_GraveNames (he.c 0x5729c0 passes it as the order's size) */
                        int partner2;                   /* 0xb0, of a pair event the second partner's netId */
                        int orderObj;                   /* 0xb0, of an order (event kind 2): the AIOBJ.objId of the workshop it is for */
                        int id2;                        /* 0xb0, a second id: a building (kind 100) or a character (kind 0x89) as
                                                           sv_SpeakPicked looks them up */
                        struct D3PARTSYS *effectObj;    /* 0xb0, of an effect event 0x76 the effect's particle system, 0: none yet
                                                           (its alloc handler 0x54fb50 clears it; ls.c clears it on load) */
                        int dropSlot;                   /* 0xb0, of a promotion event 0x32 the cm slot handle gm_DropRank leaves, -1: none
                                                           (its alloc handler 0x55dd70 sets -1) */
                        int slotOrder1c;                /* 0xb0, of a kind 0x12 slot order event (the type 0x12 message
                                                           ai_BuySlots posts): the number of first-kind slots it adds, added
                                                           to AIOBJ.lvl1c and checked against AIBTYPE.min0 */
                        int capacityOrder;              /* 0xb0, of a kind 0x13 store capacity order (the type 0x13 message
                                                           ai_StorageWindow posts): the capacity levels it adds to AIOBJ.count */
                        int thief;                      /* 0xb0, of the thief event 0x16 the netId of the thief (AIMSG.arg[1];
                                                           lc.c ai_TrainingWindow selects it) */
                        unsigned char payer;            /* 0xb0, of the payment event 0x27 the paying player's slot (AIMSG.payment.player;
                                                           he.c AIJOB.payer, lc.c ai_MoneyExchangeWindow names it) */
                    };
                    union {                             /* 0xb4..0xe7: the words, or the kind-specific times sv_RefreshPanel measures the progress to / from */
                        struct {
                            union {
                                int unkb4;                      /* 0xb4 */
                                int slotOrder1d;                /* 0xb4, of a kind 0x12 slot order event: the number of
                                                                   second-kind slots it adds, added to AIOBJ.lvl1d and checked
                                                                   against AIBTYPE.min1 (ai_BuySlots) */
                            };
                            int unkb8;                          /* 0xb8, a job-kind specific payload word: of a harvest job (0x28) the
                                                                   plant it works (veg_FindPlantId, ai_SendJobOrders), else a counter / an
                                                                   id / a news id (he.c per kind); no single role name */
                            char padbc[8];
                            int workTotal;                      /* 0xc4, of a building job 0xd the total that argc8 counts up to (sv_RefreshPanel: progress argc8 / workTotal) */
                            int argc8;                          /* 0xc8, a job-kind specific word (he.c: a random table entry, a task, an
                                                                   object); a workshop's chimney smokes only while its job has none
                                                                   (sv.c 0x528490) */
                            int wordcc;                         /* 0xcc, a job-kind specific word; of a kind 0x78 cleared with argc8
                                                                   after a load (ls_FixupAfterLoad) */
                            unsigned short in[3];               /* 0xd0, the workshop kinds */
                            unsigned short out[3];              /* 0xd6 */
                            int amount[3];                      /* 0xdc */
                        };
                        AITIME end6c;                   /* 0xb4, of a job kind 0x6c: the end time */
                        int research;                   /* 0xb4, of a research job (event kind 0xc): the goods researched (gm_UpdateTechTree) */
                        int cartBld;                    /* 0xb4, of the job a cart runs (AIOBJ.job24): the building (sv_RefreshPanel prints its kind) */
                        int id3;                        /* 0xb4, a third id: of a kind 0x1a the character sv_SpeakPicked looks up */
                        struct { char padid4[0x10]; int id4; };       /* 0xc4, of a kind 0x18: the character sv_SpeakPicked looks up */
                        struct { char padst18[0x14]; AITIME stopped18; }; /* 0xc8, of an espionage event 0x18: the time the AI's
                                                                      counter-espionage ended it (ai_CounterEspionage) */
                        struct { char padt8f[4]; AITIME end8f; };     /* 0xb8, of the kinds 0x8f / 0x16 and the building job 0x1c: the end time */
                        struct { char padt61[0x10]; AITIME start61; }; /* 0xc4, of a job kind 0x61: the start of its eight hours */
                        struct { char padt48[0x18]; AITIME end48; };  /* 0xcc, of a job kind 0x48 (stage 1): the end time */
                        struct { char padeff[0xe]; unsigned short effectGood; };  /* 0xc2, of an effect event 0x76 the Domizil table id
                                                                      (ai_FindUsableGood) whose duration sets its end time end6c */
                        struct { char padidbc[8]; int idbc; };      /* 0xbc, a kind-specific id: of a kind 4 a building (shown with an exclamation mark
                                                                       while argc8 is set), of a pamphlet event 0x35 the netId of the character it is about (he_NoEvent35Pair) */
                        struct { char padalwin[8]; void *alwin; };  /* 0xbc, of the kind 0xc event: the 0x58-byte "f3_alwin_t:d"
                                                                       record ls_ReadEventTables allocates at it */
                        struct { char padpamph[0xd]; unsigned char pamphletVariant; };  /* 0xc1, of a pamphlet event 0x35 the text
                                                                      variant the notice board shows (0x1916 + it; ai_NoticeBoardWindow) */
                        struct { char padbldd0[0x1c]; int bldd0; };  /* 0xd0, of a kind 0x1a the building id the blows are shown over (he.c 0x53e8b0) */
                        struct { char padgc4[0x10]; int members[4]; };  /* 0xc4, of a group job 'C' (0x43): the netIds of its up to four
                                                                          members, -1 = free (sv_SendSelectedToBuilding) */
                        unsigned char graveEntry;       /* 0xb4, of the graveyard order events 0x92 / 0x93 (the master exam at a
                                                           graveyard): the grave entry the order names (gv_OrderSetGraveHolder's
                                                           entry, a byte) */
                    };
                    char pade8[4];
                };
                struct {                        /* 0xac, of the reaper event ("Sensenmann"; alloc handler 0x5509f0, run handler 0x550b60:
                                                   its object flies from building to building) */
                    int reaperHome;             /* 0xac, the id of the building it flies back to when reaperLeft has run out (the
                                                   run handler 0x550b60) */
                    int reaperFrom;             /* 0xb0, the id of the building the reaper starts from */
                    int reaperTo;               /* 0xb4, the id of the building it flies to */
                    int reaperNext;             /* 0xb8, the ai_Blds index the search for the next target starts at */
                    int reaperStep;             /* 0xbc, the step of that search (mod 0x100) */
                    int reaperLeft;             /* 0xc0, the targets left to visit (reasoned: the run handler goes on while it is > 0) */
                    int reaperPlaced;           /* 0xc4, 1 once the object was created: reaperPos / reaperRot hold where */
                    struct D3OBJECT *reaper;    /* 0xc8, the reaper object, 0: none */
                    char padreapercc[4];
                    D3VECTOR reaperPos;         /* 0xd0, the object's position (D3OBJECT.pos) */
                    char padreaperdc[4];
                    D3VECTOR reaperRot;         /* 0xe0, its rotation angles (D3OBJECT.rotation) */
                };
                struct {                        /* 0xac, of the kind 6 sales-tour event (its run handler 0x554320, the
                                                   single-ware variant 0x554860); the personnel book posts 6 / 7 as its
                                                   hire requests (AIMSG.hireTitle / hireRows, ai_PersonnelBook) */
                    unsigned char hireTitle;    /* 0xac, the message's hireTitle: the title rank hired (of the hire event 7 the
                                                   same byte is hireJob) */
                    char padad[3];
                    int tourCounters[12];       /* 0xb0 .. 0xdc, the twelve ware counters it hands over one by one;
                                                   ai_UpdateStaff counts the nonzero ones as staff already busy */
                };
                struct { int grpMode; union { int groups[6]; AITIME homeUntil; }; };  /* 0xb0, of a six-group event 0x7d its six figure groups (its alloc
                                                           handler 0x551d00: gm_Shuffled, each + 1); homeUntil over them: of
                                                           the send-home event 0x77 the time it ends (its init 0x54fe80: now
                                                           + the duration of the goods 0x178); grpMode (0xac): the six-group
                                                           event's variant 0 / 1 (its texts 0x10bc / 0x10bd or 0x10be / 0x10bf;
                                                           1 also lets the officials of level 6 / 9 send office messages) */
                struct {                        /* 0xac, of a running income event 3 (its alloc handler 0x568ae0) */
                    unsigned short incomeGood;  /* 0xac, the goods (an ai_Goods index) */
                    char padinc[2];
                    int incomeAmount;           /* 0xb0, the stock amount the run handler pays out: the goods' work time */
                    float incomeAmountF;        /* 0xb4, the same as a float */
                    int incomeBld;              /* 0xb8, the building whose group its workers join */
                    int incomeFrom;             /* 0xbc, the object whose list the next batch of the goods is taken from (its run
                                                   handler: gm_Query on its list, cm_SendExSellObject's source) */
                    int incomeTo;               /* 0xc0, the object that batch goes to (cm_SendExSellObject's target) */
                    float incomeRate;           /* 0xc4, (gm_MeanLiking - 0.5) * 0.25 */
                    unsigned char incomeCounter; /* 0xc8, 0 at the start */
                };
                struct {                        /* 0xac, of the bard event 0x6b (he.c's AIJOB.bard*; ai_BardWindow sells its song) */
                    unsigned short bardRec;     /* 0xac, the hmt record the song is about (hmt_GetRecord) */
                    unsigned short bardTextOff; /* 0xae, its text offset (hmt_RecordTextId) */
                };
                struct {                        /* 0xac, of a production job 4 (lc.c ai_UpdateProdColumns shows its progress) */
                    unsigned short prodGood;    /* 0xac, the goods it makes (an ai_Goods index) */
                    char padprod[6];
                    float prodLeft;             /* 0xb4, the work still to do (the progress shown is 1 - prodLeft / prodWork) */
                    float prodWork;             /* 0xb8, the work of the whole run */
                };
                struct {                        /* 0xac, of the harvest event (its alloc handler 0x55d490, run handler 0x55d5c0) */
                    int harvestBld;             /* 0xac, the id of the building whose vegetation map (AIBLD.plants) holds the plant */
                    int harvestWorker;          /* 0xb0, the worker's netId (gm_FindChar), the spot "sp_%i" of its cutscene */
                    int harvestScript;          /* 0xb4, the id of the running cutscene script, -1: none */
                    int harvestPlant;           /* 0xb8, the plant's id (veg_FindPlantId; unkb8) */
                    unsigned short harvestType; /* 0xbc, the plant's type (G15PLANT.type) when the alloc handler took it */
                    char padharvbe[2];
                    int harvestSlot;            /* 0xc0, the cm send slot of the plant message (cm_SetPlant (.., 1) of the alloc
                                                   handler); the run handler waits on it (cm_GetSlotState), -1: dropped */
                };
                struct {                        /* 0xac, of the feast event (its run handler 0x5437c0), read when its
                                                   building has no feast table object (AIOBJ.festGuests) */
                    int festGuests[4];          /* 0xac, the guests' character ids */
                    unsigned char festEssen;    /* 0xbc, the menu pick (AIGRP.essen) */
                    unsigned char festMusik;    /* 0xbd, the musician pick (AIGRP.musik) */
                    char padfestbe[2];
                    int inviteGuests;           /* 0xc0, 1: the alloc handler 0x5436a0 sends the guests the invitation
                                                   message 0x36 (reasoned: its only read) */
                };
                struct {                        /* 0xac, of the master exam at a feast, kind 0x36 (its run handler 0x543ac0) */
                    char examText[0x10];        /* 0xac, a text the news 0x1770 / 0x1771 print (reasoned: io_PrintText gets its
                                                   address among the characters' ids) */
                    int examAt;                 /* 0xbc, where: 0 the feast table object of the building e->from (its owner
                                                   examines), 1 the feast event examFeast (its host examines) */
                    int examFeast;              /* 0xc0, the id of that feast event (kind 0x37, he_FindEvent) */
                };
                struct {                        /* 0xac, of the courtship event 0x41 (partner1 / partner2, of different sex; its
                                                   alloc handler 0x544630, run handler 0x544840, the picks drawn by 0x544550) */
                    char padpair[0xc];
                    signed char pairRound;      /* 0xb8, the rounds held, 0 at the start (the run handler counts it up) */
                    signed char pairRounds;     /* 0xb9, the rounds it takes (0x5c6620 of the two partners; the news 0x1cf4
                                                   tells pairRounds - pairRound) */
                    unsigned char pairDrawn;    /* 0xba, 1 once a round drew new picks (the run handler), 0 at the start */
                    unsigned char pairDone;     /* 0xbb, 1 once the partners are each other's relatives[0] and the party
                                                   message is posted (the run handler), 0 at the start */
                    unsigned char pairPick[3];  /* 0xbc, three of twelve shuffled values from half the first partner's
                                                   level (gm_CharLevel) on */
                    char padpairbf;
                    int pairPrice[3];           /* 0xc0, per pick (pick + 1) * the partners' worths (gm_GetWorth, each at
                                                   least 32000) / 640 */
                };
                struct {                        /* 0xac, of the patrol event 0x43 ("STREIFE_INIT"; alloc handler 0x545670, run
                                                   handler 0x545840) */
                    int patrolTarget;           /* 0xac, the id of the target building */
                    int patrolStart;            /* 0xb0, the id of the building it starts from */
                    int patrolWay[4];           /* 0xb4, up to four buildings of kind 6 within 950 of the target, in a random
                                                   order, -1: none */
                    int patrolGuards[4];        /* 0xc4, its guards (the run handler) */
                    int patrolWait;             /* 0xd4, -1 at the start; the run handler waits while it is set */
                    int patrolStep;             /* 0xd8, the index into patrolWay of the next way point, 0 at the start */
                    unsigned char patrolRound;  /* 0xdc, the rounds walked, 0 at the start */
                };
                struct {                        /* 0xac, of the raid event 0x44 ("Razzia"; alloc handler 0x546100, run handler
                                                   0x5461c0; the raiders are ids[]) */
                    int raidTarget;             /* 0xac, the id of the building raided */
                    int raidStart;              /* 0xb0, the id of the building the raiders start from and go back to */
                    int raidSlot;               /* 0xb4, the cm send slot of the raid's fight party (cm_SendNewParty) */
                    int raidParty;              /* 0xb8, the id of that party (cm_GetSlotValue of the slot; cm_PartyById) */
                };
                struct {                        /* 0xac, of the tribute event 0x35 (alloc handler 0x544070, run handler 0x544330;
                                                   the collector's netId is idbc) */
                    AITIME tributeEnd;          /* 0xac, the end of the collection: a day after its start */
                    char padtrib[0xa];
                    int tributeNext;            /* 0xc4, the ai_Chars index the next round starts at, random at the start */
                    int tributeStride;          /* 0xc8, the step from one character to the next (mod 0x300), a random
                                                   ai_CharWalkSteps entry */
                    int tributeLeft;            /* 0xcc, the characters left to visit, 0x300 at the start */
                    float tributeSkill;         /* 0xd0, the event character's skill 4 (gm_GetSkill), mixed with each visited
                                                   character's to the relation change */
                };
                struct {                        /* 0xac, of the loan event 0x23 (he.c he_AllocKredit / he_RunKredit, lc.c ai_RepayLoan;
                                                   its building is bldId) */
                    int padloan;
                    int loanPartner;            /* 0xb0, the netId of the other party (gm_FindChar; the loan's money moves between
                                                   it and the event character, cm_SendMoveGoodsUnchecked) */
                    int loanAmount;             /* 0xb4, the sum (reasoned: the news 0x18d7 names it before the interest) */
                    int loanDays;               /* 0xb8, the term in days (the payback date is days * 24 hours ahead) */
                    int loanDaysLeft;           /* 0xbc, days at the start */
                    int loanInterest;           /* 0xc0, the interest (the value gv_Accuse checks against the law 0xe) */
                    AITIME loanDue;             /* 0xc4, the payback date, at 8:00 */
                };
                struct {                        /* 0xac, of the ransom event 0x3d (he.c he_AllocRansom / he_RunRansom; he_RunKidnap's
                                                   ransom message 0x3d posts it) */
                    int ransomVictim;           /* 0xac, the netId of the kidnapped character (gm_FindChar) */
                    int ransomGuild;            /* 0xb0, the id of the thieves' guild that holds it (gm_BuildQuery(1, 1, id)) */
                    AITIME ransomSince;         /* 0xb4, the time of the kidnap (he_AllocRansom: now), shown by the news 0x19c2 */
                };
                G14MSG msg;                     /* 0xac, of the random-message event 0x42: the message it runs (he_RunRandomMessage) */
            };
            unsigned long reaperClock;          /* 0xec, of the reaper event: d3_Time when its object was placed / last moved */
            unsigned char modes;                /* 0xf0, of a kind 0x11 bit 0x40: the game pauses while its event window is active (he_PickActiveEvent) */
            signed char flags;                  /* 0xf1, a flags byte (nonzero defers the trade message posting; the bits are unknown) */
            char padf2[0x5a];                   /* up to 0x14c: the rest of the message's words from +0x58 (0xac..0x14c) */
        };
        struct {                        /* of the walk event 0x7a: its ten slots (its alloc handler
                                           he_StartWalk clears them, its run handler steps them) */
            HEWALKSLOT walkSlots[10];       /* 0xac, the walking characters */
        };
        struct {                        /* of the master exam question 0x7e (from AIMSG.exam) */
            int examBoxChr;                 /* 0xac, the netId of the character asked */
            int examBoxExamId;              /* 0xb0, the id of the exam offer event 0x7f that asks (AIJOB.examOffer*) */
        };
        struct {                        /* of the exam offer event 0x7f (he_RunExamOffer) */
            int examOfferChr;               /* 0xac, the netId of the character it is for */
            int examOfferAccepted;          /* 0xb0, 0 at the start (he_StartExamOffer), 1 when the player said yes (he_RunExamQuestion) */
        };
        struct {                        /* of the conversion event 0x81 (he_RunConversion) */
            int convertLeft;                /* 0xac, the characters still to turn */
            int convertRounds;              /* 0xb0, the rounds (days) left */
            int convertFrom;                /* 0xb4, the AICHAR.faith kind turned (0 / 1) into the other */
        };
        struct {                        /* of the delay event 0x80 (he_StartDue starts it,
                                           he_RunDelay counts the days down) */
            int delayDays;                  /* 0xac, the days still to wait, one counted off per day, 0 frees the event */
        };
        struct {                        /* of the skill-bonus event 0x82 (he_StartSkillBonus
                                           starts it, 0x552820 runs it; AIMSG.skillBonus's words): gm_GetSkill adds the
                                           bonuses of a character's events for the two skills */
            unsigned char skillBonusSkill1; /* 0xac, the first skill number (0 .. 4) */
            unsigned char skillBonusSkill2; /* 0xad, the second skill number */
            char skillBonusPadae[2];
            float skillBonusAdd1;           /* 0xb0, the bonus added for skill1 (negative: a malus) */
            float skillBonusAdd2;           /* 0xb4, the bonus added for skill2 */
            int skillBonusHours;            /* 0xb8, the hours the bonus lasts (its due clock) */
        };
        struct {                        /* of the applicants event 0x86 (he_RunApplicants) */
            int applicantsOffice;           /* 0xac, the office kind applied for (amt_GetOpenOffice), 0 none */
            int applicantsMaxKind;          /* 0xb0, the highest office kind looked at (0x1b at a restart) */
            int applicantsApplicant[2];     /* 0xb4, the handles of the two created characters (amt_CreateApplicant), -1 none */
        };
        struct {                        /* of the imperial office award event 0xa5 (he_StartOfficeAward /
                                           he_RunOfficeAward) */
            AITIME awardWhen;               /* 0xac, the clock of the award (now, he_StartOfficeAward), shown in the news */
            char awardPadba[2];
            int awardCh;                    /* 0xbc, the netId of the character who gets the office (gm_FindChar) */
            int awardOffice;                /* 0xc0, the office kind 0x23 .. 0x25 (the voice and news by it) */
        };
        struct {                        /* of the sale event 2 (he_AllocSale / he_RunSale); the
                                           building is AIJOB.from */
            char salePadac[2];              /* 0xac: AIJOB.orderGood */
            char salePadae[2];
            int saleObj;                    /* 0xb0, the object sold (its objId: gm_Query key 1 in the building's list) */
            int saleSlot;                   /* 0xb4, the send slot of the sale (cm_SendExSellObject), asked in stage 2 */
            int saleNotify;                 /* 0xb8, nonzero: a master's kind 1 character with flags1b4 bit 0 makes the news
                                           0x60b (reasoned: who sets it is not read yet) */
        };
        struct {                        /* of the building purchase event 0x21 (he_AllocBuyBuilding /
                                           he_RunBuyBuilding); the building is AIJOB.bldId */
            char buyPadac[0x4];
            int buyPrice;                   /* 0xb0, the price offered (paid with cm_SendMoveGoodsUnchecked) */
            int buyBuyer;                   /* 0xb4, the buyer's netId (gm_FindChar) */
        };
        struct {                        /* of the event 0x24 (he_AllocDueIsStart / he_RunEvent24); the
                                           character is AIJOB.ownerCh */
            char ev24Padac[0xc];
            int ev24DaysLeft;               /* 0xb8, the runs left: counted down once per run, below 0 the event ends */
        };
        struct {                        /* of the dismissal event 0x31 (he_AllocDueInOne /
                                           he_RunDismissal) */
            int dismissWorker;              /* 0xac, the netId of the worker dismissed (gm_FindChar) */
        };
        struct {                        /* of the kidnap event 0x3c (he_AllocEvent3c / he_RunKidnap) */
            int kidnapVictim;               /* 0xac, the netId of the victim (gm_FindChar) */
            int kidnapTarget;               /* 0xb0, the id of the building the gang goes to for the victim */
            int kidnapGuild;                /* 0xb4, the thieves' guild's id (gm_BuildQuery(1, 1, id)) */
        };
        struct {                        /* of the event 0x39 (he_AllocEvent39_3e / he_RunEvent39) */
            int bailHeld;                   /* 0xac, the netId of the held character (AICHAR.heldRounds) the payment frees */
            int bailPayer;                  /* 0xb0, the netId of the character asked to pay; kind 6 / 7 (a player) answers in
                                           the message box, any other decides by gm_LikingChance */
            int bailAmount;                 /* 0xb4, the sum asked for */
        };
        struct {                        /* of the event 0x38 (he_AllocEvent38 / he_RunEvent38); the
                                           building is AIJOB.from */
            int ev38Amount;                 /* 0xac, divided by gm_PlayerFactor (1000) and times 20: the relation change */
        };
        struct {                        /* of the payment event 0x27 (he_AllocEvent27 /
                                           he_RunEvent27); the building is AIJOB.bldId */
            char ev27Padac[0x4];
            char ev27Padb0[1];              /* 0xb0: AIJOB.payer */
            char ev27Padb1[3];
            int ev27Amount;                 /* 0xb4, the amount paid */
        };
        struct {                        /* of the passed master exam event 0x26 (he_AllocMasterExamPass /
                                           he_RunMasterExamPassed); the character is AIJOB.ownerCh */
            char examPassPadac[0x4];
            unsigned char examPassJob;      /* 0xb0, the character's job (AICHAR.jobId) when the event first ran */
            unsigned char examPassNewJob;   /* 0xb1, the job it gets (cm_SendSetJob): job - 1; 0 until the first run sets both */
        };
        struct {                        /* of the customers event 6 (he_AllocCustomersHire / he_RunCustomers);
                                           the building is AIJOB.from */
            char customersPadac[1];         /* 0xac: AIJOB.hireTitle */
            char customersPadad[3];
            char customersPadb0[48];        /* 0xb0: AIJOB.tourCounters */
            int customersTarget;            /* 0xe0, the objId the customer walks to, -1: the building's main object */
            int customersSlot;              /* 0xe4, the spawn's send slot, -1 none */
            int customersPerson;            /* 0xe8, the netId of the spawned customer */
        };
        struct {                        /* of the offer event 0x2c (the wedding offer: he_AllocOffer / he_RunWeddingOffer,
                                           ai_FillWeddingTab) and the master exam event 0x2f (he_RunMasterExam keeps its
                                           three characters in offerWho) */
            int offerWho[6];                /* 0xac, the netIds of the wedding: the suitor, the partner, then four guests, the
                                           last -1 for none (reasoned from the news: 0x1bc0 to the partner names the
                                           suitor, 0x1bbf the other way); ai_EvalLeastLikedOfEvent weighs the first three
                                           guests for the partner */
            AIOFFERAT offerAt;              /* 0xc4, the offer kind and the offer clock (0xc5) */
            char offerPadd3;
            int offerHandle;                /* 0xd4, the offer handle cm_SendHandOverCrimes gave (cm_GetSlotState asks it) */
        };
        struct {                        /* of the hire event 7 (he_AllocCustomersHire / he_RunHire); the building
                                           is AIJOB.from */
            unsigned char hireJob;          /* 0xac, the index of the job in the building type's jobs[] (the message's
                                           hireTitle), 0: the master (ai_PersonnelBook and the master windows look for
                                           the running master hire by it) */
            char hirePadad[3];
            int hireCount[1];               /* 0xb0, the hires left (he_RunCustomers' loops over one count) */
            int hireTarget;                 /* 0xb4, the objId the hired character walks to; 0: the building's main room, -1: its 0xfd object */
            int hireSlot;                   /* 0xb8, the spawn's send slot */
            int hirePerson;                 /* 0xbc, the netId of the hired character */
        };
        struct {                        /* of the research event 0xc (its alloc 0x56b380, run handler
                                           he_RunResearch): a building orders the good it researches and hooks the object
                                           the order made */
            int researchBuyer;              /* 0xac, the id of the building the good is ordered to (the message's buyer) */
            char researchPadb0[4];
            int researchGood;               /* 0xb4, the goods prototype researched (AIJOB.research) */
            int researchObjId;              /* 0xb8, the objId of the object the order made (the reply's AIOBJ.objId) */
            int researchWbc;                /* 0xbc, 0 at the allocation (no reader known) */
            int researchLimit;              /* 0xc0, the rounds waited for that object (0x20) */
            int researchRounds;             /* 0xc4, the rounds since the order (one per minute) */
            int researchSlot;               /* 0xc8, the send slot of the order (cm_SendExSellObject) */
        };
        struct {                        /* of the building event 0xd (he_AllocGebaeudeBauen and
                                           its run handler he_RunConstruction): the building type it builds and the position it
                                           searches the plot around */
            char buildPadac[0x4];
            int buildBldType;               /* 0xb0, the building kind id (ai_BuildingName's id) */
            char buildPadb4[0x1c];
            unsigned char buildCount;       /* 0xd0, the placements left (the object callback counts it down; reasoned) */
            char buildPadd1[3];
            float buildPos[3];              /* 0xd4, the position ai_FindNearestObject measures the plots from */
        };
        struct {                        /* of the transport event 15 (he_AllocTransport / he_RunTransport):
                                           a cart driven from one building to another */
            int transportCart;              /* 0xac, the cart's objId (gm_FindById) */
            int transportStart;             /* 0xb0, the id of the start building */
            int transportGoal;              /* 0xb4, the id of the goal building (a kind 0xa goal of an escorted cart: the
                                           nearest one) */
            int transportTravel;            /* 0xb8, the two buildings' AIBLD.travel30 summed */
            char transportPadbc[4];
            float transportSpeed;           /* 0xc0, the cart's walk speed (its CHARACTER.walkSpeed after the driver's skill) */
            int transportAt;                /* 0xc4, the id of the building the cart is at (the start) */
            int transportMode;              /* 0xc8, by gm_IsHomeType of start / goal: 3 neither, 2 the start, 1 the goal, 4 both */
            int transportEscorts;           /* 0xcc, the escort kind 0 .. 2 (the goods' value / 16000 + random 0 .. 1) */
            unsigned char transportStarted; /* 0xd0, 1 once the leg's first round sent the cart off, 0 at the start */
            char transportPadd1[3];
            int transportRounds;            /* 0xd4, the rounds the cart has been under way (a leg ends after 6 at the latest) */
            D3VECTOR transportLastPos;      /* 0xd8, the cart body's position at the last round (arrived: it did not move) */
            char transportPade4[4];
            int transportSlotE8;            /* 0xe8, -1 at the start (its run handler's slot) */
            int transportRoute;             /* 0xec, the send slot of the cart's route (cm_SendCartRoute), -1 at the start */
            unsigned char transportAmbushed;/* 0xf0, 1 once an ambush (he_RunAmbush) picked the transport, 0 at the start */
            unsigned char transportWeatherStage;/* 0xf1, 2: the cart slowed once more (he_SetCartSpeed) */
            unsigned char transportQuiet;   /* 0xf2, nonzero: no arrival news */
            char transportPadf3;
            int transportOrder;             /* 0xf4, the id of the event that ordered the transport, 0 / -1 none */
        };
        struct {                        /* of the event 16 (he_AllocCartRepair / he_RunCartRepair); reasoned: a
                                           cart repair */
            int cartRepairCart;             /* 0xac, the cart's objId (gm_FindById) */
            int cartRepairPoints;           /* 0xb0, the points the cart's byte +0x12 rises by */
            int cartRepairTarget;           /* 0xb4, that byte after the work, 100 at most */
            int cartRepairPer;              /* 0xb8, the minutes per point */
            char cartRepairPadbc[4];
            AITIME cartRepairDone;          /* 0xc0, the start + per * points minutes */
            char cartRepairPadce[0xa];
            int cartRepairNotify;           /* 0xd8, nonzero: the news 0x1c49 when done (he_RunCartRepair) */
        };
        struct {                        /* of the message box event 17 (he_AllocMessageBox / he_RunMessageBox); the
                                           text is AIJOB.text (after its NUL the text to speak) */
            int msgBoxPic;                  /* 0xac, the picture of the window (he_OpenEventSlot) */
            int msgBoxBld;                  /* 0xb0, the quick jump's building id, -1: none */
            int msgBoxObj;                  /* 0xb4, the quick jump's object in it (sv_SelectPanelObject), -1: the building */
            int msgBoxParty;                /* 0xb8, of a cutscene box: the party it shows (cm_PartyById) */
            char msgBoxSel;                 /* 0xbc, sv_SelectPanelObject's third argument (written by it) */
            char msgBoxPadbd[0x2f];
            struct SBSAMPLE *msgBoxVoice;   /* 0xec, the spoken text's sample (snd_QueueVoice), 0: none */
            unsigned char msgBoxFlags;      /* 0xf0, 1 big, 2 quick jump, 4 cutscene, 8 activate, 0x10 speak, 0x20 history, 0x40 help */
        };
        struct {                        /* of the slot order event 18 (he_AllocSlotOrderStore / he_RunSlotOrder; AIJOB's
                                           slotOrder1c / slotOrder1d) */
            int slotOrderObj;               /* 0xac, the objId of the workshop object (gm_FindById) */
            char slotOrderPadb0[4];         /* 0xb0: AIJOB.slotOrder1c */
            char slotOrderPadb4[4];         /* 0xb4: AIJOB.slotOrder1d */
        };
        struct {                        /* of the store extension event 19 (he_AllocSlotOrderStore /
                                           he_RunStoreExtension) */
            int storeExtObj;                /* 0xac, the objId of the store object (gm_FindById) */
            int storeExtRounds;             /* 0xb0, the extension rounds still to run, one capacity unit each */
        };
        struct {                        /* of the herb gathering event 20 (he_AllocHerbGathering /
                                           he_RunHerbGathering); the gatherers' netIds are AIJOB.ids[] */
            unsigned char herbsN;           /* 0xac, the gatherers in AIJOB.ids[] */
            char herbsPadad;
            unsigned short herbsGood;       /* 0xae, the good gathered (gm_FreeCapacity; its name is the text 0x9a8 + 2 * good), 0: none */
            int herbsRoom;                  /* 0xb0, the object (room) of the event's building the gatherers come back to
                                           (cm_SendChrGotoBuilding's objId, the news' quick jump) */
            int herbsField;                 /* 0xb4, the id of the nearest building of type 0xb they gather at */
        };
        struct {                        /* of the animal hunt event 21 (he_AllocAnimalHunt /
                                           he_RunAnimalHunt); the hunters' netIds are AIJOB.ids[] */
            unsigned char huntN;            /* 0xac, the hunters in AIJOB.ids[] */
            char huntPadad;
            unsigned short huntGood;        /* 0xae, the good caught (cm_SendExSellObject; its name is the text 0x9a8 + 2 * good) */
            char huntPadb0[4];
            int huntRoom;                   /* 0xb4, the object (room) of each hunter's building (AICHAR.bld) it goes to */
        };
        struct {                        /* of the study event 22 (he_AllocStudy / he_RunStudy;
                                           reasoned: a stay at a building that raises one skill of the character) */
            unsigned char studySkill;       /* 0xac, the skill raised: the character's byte 0x80 + skill, up to 252 */
            char studyPadad[3];
            int studyChr;                   /* 0xb0, the netId of the character (gm_FindChar) */
            int studyRoom;                  /* 0xb4, the objId of its room in the building (an object of type 1), -1: none */
            AITIME studyUntil;              /* 0xb8, the latest end: 6 units after the first due clock */
        };
        struct {                        /* of the event type 0x17 (he_AllocEvent17 / he_RunEvent17) */
            char ev17Padac[0x8];
            AITIME ev17Due;                 /* 0xb4, the due clock the allocation handler copies to AIJOB.end */
        };
        struct {                        /* of the sabotage event 25 (he_AllocSabotage / he_RunSabotage);
                                           AIJOB.from is the building the saboteur is hired at and goes back to */
            int sabotageTarget;             /* 0xac, the id of the building attacked */
            char sabotagePadb0[0x12];
            unsigned char sabotageBlasts;   /* 0xc2, the explosions set off so far (stage 5) */
            char sabotagePadc3;
            int sabotageSaboteur;           /* 0xc4, the netId of the saboteur (the character the spawn request made), -1: none */
            int sabotageSlot;               /* 0xc8, the cm slot of the pending request (the spawn, the walk, the accusation), -1: none */
            int sabotageWatch;              /* 0xcc, the id of the watch event that caught the saboteur (HEDETECT.found, AIJOB.patrolGuards / patrolWait) */
            int sabotageFee;                /* 0xd0, the money the event's character pays for it */
        };
        struct {                        /* of the spying event 24 (he_AllocSpying / 0x55a030) */
            int spyingTarget;               /* 0xac, the id of the building spied on (gm_FindById; none: ai_PickActionBuilding
                                           picks one of the gypsyFilter kinds) */
            char spyingPadb0[4];
            int spyingAt;                   /* 0xb4, the id of the building the walk is at, -1 at the start */
            int spyingB8;                   /* 0xb8, 0 at the start (reasoned: a counter of the run handler) */
            int spyingCursor;               /* 0xbc, the walk over the 0x100 buildings: the index it is at, random */
            int spyingStep;                 /* 0xc0, the walk's step, a random ai_RandomStrides entry */
            int spyingVictim;               /* 0xc4, the netId of the character spied on */
            AITIME spyingUntil;             /* 0xc8, the end: 3 days (4 when order 0x26 answers 2) + AIJOB.spyingDays from now */
            char spyingPadd6[2];
            int spyingSpy;                  /* 0xd8, the cm slot of the spy's creation, then its netId; -1: none */
            char spyingPaddc[8];
            int spyingFee;                  /* 0xe4, the money the event's character pays for the spy */
            int spyingDays;                 /* 0xe8, the days of spying asked for */
        };
        struct {                        /* of the brawl event 26 (he_AllocBrawl / he_RunBrawl);
                                           AIJOB.from is the building the thug is hired at and goes back to */
            int brawlPlace;                 /* 0xac, a building id from the event's message: the place the accusations name
                                           (gv_Accuse), which must still exist when the watch's proof is sent */
            char brawlPadb0[4];
            int brawlVictim;                /* 0xb4, the netId of the character beaten up (gm_FindChar; the run handler's
                                           money moves and accusation name it) */
            char brawlPadb8[0x10];
            int brawlThug;                  /* 0xc8, the netId of the thug (the run handler takes it from the spawn slot), -1: none */
            int brawlSlot;                  /* 0xcc, the cm slot of the pending request (the spawn, the walk) */
            int brawlMeet;                  /* 0xd0, the id of the building the thug goes to: the victim's home, else one of
                                           its buildings, else one of the gypsyFilter kinds near it */
            int brawlWatch;                 /* 0xd4, the id of the watch event that caught the thug (HEDETECT.found, AIJOB.patrolGuards / patrolWait) */
            int brawlFee;                   /* 0xd8, the money the event's character pays for it */
        };
        struct {                        /* of the theft event 27 (he_AllocTheft / he_RunTheft) */
            int theftBld;                   /* 0xac, the id of the building robbed */
            int theftLoot;                  /* 0xb0, the value taken (the news 0x17f4 prints it; reasoned: the run handler's
                                           chance of a second round is it over the building's equipment value) */
            char theftPadb4[4];
            int theftRounds;                /* 0xb8, 0 at the start (the run handler acts from 2 on) */
        };
        struct {                        /* of the repair event 28 (he_AllocRepair / he_RunRepair):
                                           the run handler raises the building's state (gm_ChangeBuildingState) by the
                                           minutes passed since AIJOB.clock60 */
            int repairBld;                  /* 0xac, the id of the building repaired */
            int repairPoints;               /* 0xb0, the state points still to repair (the run handler counts them down) */
            char repairPadb4[4];
            AITIME repairUntil;             /* 0xb8, the planned end: 10 minutes per point, less for a higher ranked character */
        };
        struct {                        /* of the inn meeting event 0x2a (AIJOB has no name at
                                           +0xb0: a field there flips d3_CloneObject's bytes, the unit's lead comment) */
            int innInnId;                   /* 0xac, the inn building's id (gm_FindById) */
            AITIME innMeeting;              /* 0xb0, when the meeting is held: the hour set to a random 0x13 .. 0x16 */
            char innPadbe[2];
            int innState;                   /* 0xc0, 1 after the start, counted down by the run handler 0x542100 */
        };
        struct {                        /* of the duel challenge (he_RunDuelChallenge): the challenge
                                           event 0x46 names the duel event, the duel event keeps two values for its news */
            int duelDuelId;                 /* 0xac, of the challenge 0x46: the id of the duel event (he_FindEvent(1, 1, id)) */
            char duelPadb0[4];
            unsigned short duelNewsArg1;    /* 0xb4, of the duel event: the first value of the challenge's news 0x1d6b */
            unsigned short duelNewsArg2;    /* 0xb6, of the duel event: the third value of that news (both not read further) */
        };
        struct {                        /* of the "RndGeselle" (a random journeyman) event (event 0x4a:
                                           its init 0x547ee0, run handler he_RunGeselle) */
            int geselleChrId;               /* 0xac, the character the news goes to (gm_FindById's character) */
            int geselleBldId;               /* 0xb0, the building the journeyman is sent to (gm_FindById's building) */
            int geselleBldArg;              /* 0xb4, cm_SendChrGotoBuilding's third value with that building, also the
                                           news box's jump target's second word */
            unsigned short geselleNewsId;   /* 0xb8, the text id of the news */
            char gesellePadba[2];
            int geselleSlot;                /* 0xbc, the cm slot of the journeyman's creation (cm_SendMessage3d); its value
                                           is the new character */
        };
        struct {                        /* of the master exam payment event (he_RunMasterExamPay) */
            char examPayPadac[0x4];
            int examPayFee;                 /* 0xb0, the fee the message box names (5% of the character's worth), paid on yes */
        };
        struct {                        /* of the payment event 0x56 (its init 0x5482c0, run handler he_RunPayment) */
            unsigned char paymentWait;      /* 0xac, the runs left before it pays, counted down */
            char paymentPadad[3];
            unsigned int paymentAmount;     /* 0xb0, the base amount: twice it or half of it is paid */
        };
        struct {                        /* of the countdown event 0x51 (its init he_AllocNextDay, run
                                           handler he_RunCountdown): counted down once per run, 0 frees the event */
            unsigned char countdownRuns;    /* 0xac, the runs left (the message's first word) */
        };
        struct {                        /* of the history comment event 0x52 (the KOMMENTARE text
                                           command ai_CommandComments posts message 0x52; its init he_AllocComment, run
                                           handler 0x548380) */
            int commentEntry;               /* 0xac, the index into the history list (AIMSG.car) */
            int commentNext;                /* 0xb0, the next index (entry + 1) */
        };
        struct {                        /* of the festival payouts event 0x53 (the FEST text command
                                           posts message 0x53; its init he_AllocCharPayouts, run handler he_RunCharPayouts) */
            char festPayoutPadac[0x4];
            int festPayoutBld;              /* 0xb0, -1 at the init (reasoned: no building; the run handler picks one per
                                           character and keeps no event-level word, so nothing reads it back) */
        };
        struct {                        /* of the offspring event (its run handler he_RunOffspring) */
            float offspringChance;          /* 0xac, stage 0: the chance built up run by run; stage 1: the runs waited (to 3) */
        };
        struct {                        /* of the trial event 0x5e (its alloc handler he_StartTrialEvent,
                                           run handler he_RunTrialEvent) */
            int trialTeacher;               /* 0xac, the netId of the character the trial is held with (gm_FindChar); the
                                           rounds' cost goes to its AP events, the news 0x1a9c to it */
            unsigned char trialJob;         /* 0xb0, the job the character gets at the end (cm_SendSetJob; its title
                                           group picks the two abilities raised, the job title text 0x130 + it) */
            char trialPadb1[3];
            int trialCost;                  /* 0xb4, the cost of a round (he_AddApEvent's cost, negated) */
            unsigned char trialRounds;      /* 0xb8, the round counter (he_StartTrialEvent clears it; 1 at the first
                                           round, the third one moves the event to the state 1) */
        };
        struct {                        /* of the next trial step event 0x5f (its alloc handler
                                           he_StartNextTrialStep, run handler he_RunTrialSteps) */
            int trialStepTeacher;           /* 0xac, the netId of the teaching character (gm_FindChar) */
            char trialStepPadb0[4];
            int trialStepCost;              /* 0xb4, the cost of a step (he_AddApEvent's cost, negated) */
            unsigned char trialStepSkill[2];/* 0xb8, the two skills each step raises (ai_ApplyTrialStep's index 0 .. 4) */
            unsigned char trialSteps;       /* 0xba, the steps taken (he_StartNextTrialStep clears it; 5 end it) */
        };
        struct {                        /* of the training event 0x60 (its alloc handler
                                           he_StartTraining, run handler 0x549aa0) */
            unsigned char trainBase;        /* 0xac, the most the skill rises: 0x15 */
            unsigned char trainRange;       /* 0xad, the random amount taken off it (util_Random), 2 * (2 + skill / 42 + 1) */
            unsigned char trainSkill;       /* 0xae, the skill trained (AICHAR.skills index; AIMSG.training.talent, the talent
                                           lcdom.c ai_TalentWindow names) */
        };
        struct {                        /* of the skill level-up event 0x6a's words: AIMSG.skillLevel's words as the
                                           event takes them over (+0x58 -> +0xac; its init he_StartSkillUp, run handler
                                           he_RunSkillUp) */
            unsigned char skillUpSkill;     /* 0xac, the skill (AICHAR.skills index) */
            char skillUpPadad[3];
            int skillUpLevel;               /* 0xb0, its new level: below 6 the news 0x16e6 + level, else the skill's master news */
            int skillUpVariant;             /* 0xb4, one of six texts per skill (random(6), its init) */
        };
        struct {                        /* of the bard event (its init he_StartBard, run handler
                                           he_RunBard) */
            char bardPadac[2];              /* 0xac: AIJOB.bardRec */
            char bardPadae[2];              /* 0xae: AIJOB.bardTextOff */
            char bardPadb0[4];
            int bardScript;                 /* 0xb4, the id of the bard's script (barde_create.esc), -1: none */
        };
        struct {                        /* of the population event 0x6d (its init he_StartPopulation,
                                           run handler he_RunPopulation) */
            int populationCount;            /* 0xac, the newcomers and the dead of this round */
            float populationChance;         /* 0xb0, the chance of the next newcomer (or death) */
            float populationStep;           /* 0xb4, what each failed draw takes off chance */
            int populationSlot;             /* 0xb8, the cm slot of the newcomer being created, -1: none */
        };
        struct {                        /* of the lover event 0x6f ("Geliebte"; its init he_StartLover,
                                           run handler he_RunLover) */
            int loverKeeper;                /* 0xac, the netId of the character who keeps the lover (and pays) */
            int loverLover;                 /* 0xb0, the netId of the lover (flagged HE_LOVER_FLAG while it lasts) */
            int loverRounds;                /* 0xb4, the days paid, 0 at the start */
            int loverPay;                   /* 0xb8, what the keeper pays a day, 2 at the start */
        };
        struct {                        /* of the "Dunkle Ecke" robbery event 0x74 (its init
                                           he_StartDarkCorner, run handler 0x54f160) */
            int darkCornerCarrier;          /* 0xac, the cm slot of the carrier figure, then its id; -1: none */
            int darkCornerVictim;           /* 0xb0, the id of the victim building */
            int darkCornerAmount;           /* 0xb4, the amount */
            int darkCornerTarget;           /* 0xb8, the next target building, -1 at the start */
            int darkCornerSteps;            /* 0xbc, the robbery steps left, 5 + random(4) at the start */
            int darkCornerLoot;             /* 0xc0, the loot level 0 .. 3, 0 at the start */
            int darkCornerCursor;           /* 0xc4, the walk over the 0x100 buildings: the index it is at, random */
            int darkCornerStep;             /* 0xc8, the walk's step, a random ai_RandomStrides entry */
        };
        struct {                        /* of the plague event 0x59 (he_BeginPlague, its run handler 0x54a020) */
            int plagueLeft;                 /* 0xac, counted down by the run handler at every infected target */
            int plagueWalk;                 /* 0xb0, the walk over the 0x100 buildings: the index it is at, random at the start */
            int plagueStep;                 /* 0xb4, the walk's step, a random ai_RandomStrides entry */
            char plaguePadb8[4];
            int plagueCarriers[4];          /* 0xbc, the four carriers: the cm slots of their creation, then their ids */
            int plagueTarget;               /* 0xcc, the id of the building the carriers are sent to */
            int plagueHome;                 /* 0xd0, the id of the start building, where they go back after each target */
        };
        struct {                        /* of the pickpocket gang event 0x61 (its alloc handler
                                           he_StartGang, run handler 0x54a7b0; the gang is AIJOB.ids[0..5]) */
            int gangTargets[6];             /* 0xac, the buildings the members are sent to, -1 at the start */
            AITIME gangStart;               /* 0xc4, the start (AIJOB.start61): after 0x1e0 minutes the gang is collected */
            unsigned char gangNext;         /* 0xd2, the member the run handler handles next */
            char gangPadd3;
            int gangLeader;                 /* 0xd4, the netId of the gang's leader */
            unsigned char gangMembers;      /* 0xd8, the members the gang has (ids[] not -1) */
        };
        struct {                        /* of the protection money event 0x62 (its run handler
                                           0x54b1e0; the question event 0x63 he_RunProtectionAsk answers it); the
                                           collector is AIJOB.chr */
            int protectionCollector;        /* 0xac, the collector figure's netId */
            int protectionVictim;           /* 0xb0, the victim building's id (its owner pays) */
            int protectionAmount;           /* 0xb4, the protection money */
            int protectionAnswer;           /* 0xb8, -1 open, 0 refused, 1 paid, 2 asked a player (the event 0x63) */
            int protectionHome;             /* 0xbc, the collector's building, which counts the money, -1: none */
            int protectionHomeRoom;         /* 0xc0, the room object there the collector goes back to */
        };
        struct {                        /* of the audit event 0x64 (he_StartAudit / he_RunAudit);
                                           the one who ordered it is AIJOB.chr */
            int auditInspector;             /* 0xac, the inspector figure's netId */
            int auditBld;                   /* 0xb0, the audited building's id */
            int auditHome;                  /* 0xb4, the building the inspector goes back to */
            int auditHomeRoom;              /* 0xb8, the room object there */
        };
        struct {                        /* of the patrol gathering event 0x65 (he_StartGathering /
                                           he_RunGathering; its figures are AIJOB.ids[0..5]) */
            char gatheringPlace[0x20];      /* 0xac, the name of the scene object the figures gather at; an event 0x48 of
                                           another character at the same place is its opponent */
            int gatheringHome;              /* 0xcc, the building the figures go back to (the fight party's fight.attackerBld) */
            int gatheringHomeRoom;          /* 0xd0, the room object there */
            int gatheringParty;             /* 0xd4, the id of the fight party (cm_GetSlotValue), -1 at the start */
            int gatheringPartySlot;         /* 0xd8, the cm send slot of the fight party (cm_SendNewParty) */
            unsigned char gatheringDc;      /* 0xdc, 0 at the start (no reader known) */
        };
        struct {                        /* of the tutorial hint event 0x83 (its alloc handler
                                           0x5679b0, run handler 0x567a80) */
            int hintEntry;                  /* 0xac, the index into he_Hints the run handler is at */
        };
        struct {                        /* of the trade event 0xb (he_AllocTrade / he_RunTrade) */
            char tradePadac[4];             /* 0xac: AIJOB.cart */
            int tradeBld;                   /* 0xb0, the id of the building it trades at, then the next one it goes to */
            int tradeChr;                   /* 0xb4, the trading character (its budget pays the buys) */
            int tradeSellBld[3];            /* 0xb8, per sell slot the building that buys its goods, -1: done */
            int tradeBuyBld[3];             /* 0xc4, per buy slot the building to buy at, -1: done */
            unsigned short tradeSell[3];    /* 0xd0, per sell slot the good, 0: none */
            unsigned short tradeBuy[3];     /* 0xd6, per buy slot the good, 0: none */
            int tradeBuyAmount[3];          /* 0xdc, per buy slot the amount wanted */
            int tradeMoveSlot;              /* 0xe8, the cm send slot of the last goods move (cm_SendExSellObject), -1: none */
            int tradeMsgSlot;               /* 0xec, the cm send slot of the move-on message 0xf, -1: none */
            unsigned char tradeTries;       /* 0xf0, AIJOB.modes: the half-hour retries left for a buy that found nothing
                                           (4 from the alloc handler when the character exists) */
            char tradeDeferred;             /* 0xf1, AIJOB.flags: nonzero defers the move-on message (and the cart check) */
        };
        struct {                        /* of the production event (he_AllocProduktion 0x5690c0,
                                           he_RunProduktion) */
            unsigned short productionGood;  /* 0xac, the good produced (an ai_Goods index) */
            char productionPadg[2];
            char productionPadb0[4];
            float productionAmount;         /* 0xb4, the work left on the current unit: starts at the good's work time
                                           (AIGOOD.workTime), worn down by the work minutes, one unit made per work time */
            float productionAmount2;        /* 0xb8, the same, set when a unit starts */
            int productionBld;              /* 0xbc, the producing building's id */
            int productionStore;            /* 0xc0, the id of the object the goods are made in (kind 0x2a / 0x116: its list
                                           holds the inputs, cm_SendMakeGoods' target) */
            int productionSlot;             /* 0xc4, the cm send slot of the last make / order message (cm_GetSlotState), -1: none */
            int productionLacking;          /* 0xc8, 1 once a shortage was reported (its news box event 0x11 is freed when the work resumes) */
            float productionRate;           /* 0xcc, (the owner's mean liking - 0.5) * 0.25 */
            unsigned char productionCounter;/* 0xd0, the work minutes since the workers were last rated (every 60) */
            char productionPadd1[3];
            float productionStaff;          /* 0xd4, the workers' mean factor (health, skill, place), 1.0 at the allocation */
        };
        struct {                        /* of the search event 8 (he_AllocSearchEvent / he_RunSearchEvent) */
            unsigned short searchGood;      /* 0xac, the good searched for (an ai_Goods index) */
            char searchPadg[2];
            int searchBld;                  /* 0xb0, the id of the building the workers belong to */
            int searchStore;                /* 0xb4, the id of the object the found goods go to */
        };
        struct {                        /* of the search event 9 (he_AllocSearch9 / he_RunSearch9) */
            int search9Bld;                 /* 0xac, the id of the building the workers belong to */
            int search9Source;              /* 0xb0, the id of the object searched (its list holds the kind 0x17 goods) */
            int search9Store;               /* 0xb4, the id of the object the found goods go to */
        };
        struct {                        /* of the new-occurrence debug event 0xa (its run handler
                                           he_RunNewOccurrenceMsg) */
            int occurrenceGood;             /* 0xac, the goods index the bug text names (0x9a8 + 2 * good) */
        };
        struct {                        /* of the building construction event 0xd (its run handler
                                           he_RunConstruction, he_ShowConstruction) */
            int constructPayer;             /* 0xac, the netId of the character paying for the building */
            int constructBldType;           /* 0xb0, the building kind id (AIJOB.buildBldType), sent with the message 10 */
            int constructCarry;             /* 0xb4, the price paid in stage 0; from stage 6 on the work minutes carried over
                                           to the next stage */
            int constructBld;               /* 0xb8, the id of the building under construction (he_ShowConstruction) */
            int constructScript;            /* 0xbc, the id of the event script playing (evt_FindById), -1: none */
            int constructMinutes;           /* 0xc0, the work minutes per construction stage */
            int constructStages;            /* 0xc4, the last construction stage (AIJOB.workTotal) */
            int constructStage;             /* 0xc8, the stage reached, -1: not started (AIJOB.argc8) */
            int constructSlot;              /* 0xcc, the cm slot of the payment / the building message (cm_GetSlotState) */
            unsigned char constructPlacing; /* 0xd0, the "vg_" objects still being placed (AIJOB.buildCount) */
            char constructPadd1[3];
            D3VECTOR constructPos;          /* 0xd4, where the building stands (AIJOB.buildPos) */
            char constructPade0[4];
            D3VECTOR constructRot;          /* 0xe4, its rotation */
            char constructModel[0x40];      /* 0xf0, the building's group model file (the length reasoned: what fits in AIJOB) */
        };
        struct {                        /* of the mission check event 0x4c (he_AllocMissionCheck / he_RunMissionCheck) */
            int missionCheckSlot;           /* 0xac, the cm slot of the system message 8 that tells the mission's owner, -1: none */
        };
        struct {                        /* of the research event 0x95 (he_AllocRecipeResearch / he_RunRecipeResearch) */
            int recipeAlchemist;            /* 0xac, the netId of the researching character */
            int recipeRecipe;               /* 0xb0, the recipe's id (the first word of ahm_RandomRecipe's record) */
            int recipeLeft;                 /* 0xb4, the research minutes left (ahm_ResearchMinutes at the start) */
            int recipeTotal;                /* 0xb8, the research minutes at the start */
            AITIME recipeWorked;            /* 0xbc, the clock the minutes worked are counted from */
        };
        struct {                        /* of the alchemist's daily laboratory event 0x98 (he_AllocAlchemistDay /
                                           he_RunAlchemistDay) */
            int ahmDayBonus;                /* 0xac, nonzero: the next run adds a bonus to the alchemist record's value
                                           instead of the roll (0 at the start; he_LabIncident sets it to the mishap it ran) */
            int ahmDayPayloadB0;            /* 0xb0, a kind-specific payload word the alloc clears to -1 (none); no handler of
                                           event 0x98 reads it, cm_SendExSetHE sends it in the event's data block */
            int ahmDayPayloadB4;            /* 0xb4, the second such word, -1: none */
        };
        struct {                        /* of the graveyard owner's haunting event 0x88 (the message's
                                           arg[0 .. 3]: am.c ai_ExecGraveyardOwner0, sv_t.c; he_AllocHaunting / he_RunHaunting) */
            int hauntHome;                  /* 0xac, the id of the victim's building the haunter goes to */
            int hauntVictim;                /* 0xb0, the netId of the character haunted */
            int hauntHaunter;               /* 0xb4, the netId of the character who haunts (the one selected), -1: none */
            int hauntPaid;                  /* 0xb8, the money paid for it (the slider's amount) */
            int hauntWalkSlot;              /* 0xbc, the cm slot of the haunter's walk, -1: none */
        };
        struct {                        /* of the graveyard owner's "breath of decay" event 0x89 (the
                                           message's arg[0 .. 3]: am.c ai_ExecGraveyardOwner2, sv_t.c; he_AllocDecay / he_RunDecay) */
            int decayHome;                  /* 0xac, the id of the victim's building the agent goes to */
            int decayVictim;                /* 0xb0, the netId of the character it is against */
            int decayAgent;                 /* 0xb4, the netId of the character who goes (the one selected) */
            int decayPaid;                  /* 0xb8, the price (sv_t.c: 4) */
            int decayAged;                  /* 0xbc, 1 when the victim aged, 0 when it failed */
        };
        struct {                        /* of the secret room event 0x99 (am.c ai_ExecSecretRoom0 .. 3
                                           post it; he_AllocSecretRoom / he_RunSecretRoom) */
            int secretRoomTarget;           /* 0xac, the id of the building the agent goes to (of the way 3: the spied
                                           building of the spy hunted, or one ai_PickActionBuilding picks) */
            int secretRoomHome;             /* 0xb0, the id of the secret room's building: the agent is spawned there and
                                           goes back to it */
            int secretRoomVictim;           /* 0xb4, the netId of the character the deed is against */
            int secretRoomAgent;            /* 0xb8, the netId of the agent ("ASSASSIN", spawned by he_AllocSecretRoom) */
            int secretRoomWay;              /* 0xbc, 1 an attack, 2 an accusation, 3 a spy hunt ("Spy Killer"), 4 the domicile
                                           event (am.c's ways 1, 2, 3, 0) */
            int secretRoomStrength;         /* 0xc0, of an attack the strength (he_SecretRoomAttack; the news 0x4007 + it) */
            int secretRoomSpyEvent;         /* 0xc4, of a spy hunt the id of the spying event followed, -1: none */
            int secretRoomHunting;          /* 0xc8, of a spy hunt 1 while it follows a spy, 0 while it searches */
            int secretRoomWalkSlot;         /* 0xcc, the cm slot of the agent's spawn, then of its walk; -1: none */
        };
        struct {                        /* of the tips event 0x84 (its alloc handler 0x567b80,
                                           run handler 0x567c00) */
            int tipEntry;                   /* 0xac, the index into he_TipOrder the run handler is at */
        };
        struct {                        /* of the new-worker event 0x6e (its alloc handler 0x565850,
                                           run handler 0x565940) */
            int newWorkerSlot;              /* 0xac, the cm send slot of the hire message (cm_GetSlotState / cm_GetSlotValue) */
            char newWorkerPadb0[4];
            int newWorkerBld;               /* 0xb4, the id of the building that gets the worker (gm_FindBuildingById) */
            char newWorkerPadb8[4];
            int newWorkerShare;             /* 0xbc, the share of the reward paid to the building's owner, 0: none */
        };
        struct {                        /* of the daily routine event 0x3a (he_PostEvent3a posts
                                           it at the start of the day; its run handler he_RunRoutine walks ai_Chars) */
            int routineChrIdx;              /* 0xac, the ai_Chars index of the last character sent (he_RunRoutine stores its loop
                                           index here and clears it for the next stage), 0 at the allocation */
            int routineStep;                /* 0xb0, 3 at the allocation (reasoned: the unit's note calls it the routine step;
                                           he_RunRoutine never reads it) */
        };
        struct {                        /* of the auction event 0x67 (he_StartAuctionEvent /
                                           he_RunAuctionEvent) */
            int auctionBld;                 /* 0xac, the id of the building auctioned */
            int auctionPrice;               /* 0xb0, the start price; a bidder must be worth at least as much */
        };
        struct {                        /* of the title ceremony event 0x69 (he_StartTitleCeremony /
                                           he_RunTitleCeremony; the player is AIJOB.chr) */
            unsigned char titleTitle;       /* 0xac, the title given: 2 the citizenship, 7 .. 9 the highest ones */
            char titlePadad[3];
            int titleCh;                    /* 0xb0, the netId of the character who gets it */
            int titleSent;                  /* 0xb4, 1 once the title was sent as the character's field 0xd, 0 at the start */
        };
        struct {                        /* of the alchemist research event 0x96 (he_AllocResearchRecipe
                                           and its run handler he_RunResearchRecipe) and the training event 0x97; ahm_ResearchState reads
                                           Start / Amount, the event 0x95's words at 0xb4 / 0xb8 are recipeLeft / recipeTotal */
            int ahmResearchChr;             /* 0xac, the id of the character researching (gm_FindChar) */
            int ahmResearchId;              /* 0xb0, the recipe / share researched (ahm_FindRecipe) */
            float ahmResearchProgress;      /* 0xb4, the progress of this round (ahm_ResearchProgress; the run handler adds it to the share) */
            int ahmResearchAmount;          /* 0xb8, the amount left (the run handler counts it down by the elapsed minutes) */
            int ahmResearchStart;           /* 0xbc, the amount the research started with (the minutes the progress is measured in) */
            AITIME ahmResearchClock;        /* 0xc0, the clock the elapsed minutes are measured from (ai_Time) */
        };
        struct {                        /* of the plunder event 0x8a (its alloc he_AllocPlunder and run
                                           handler 0x5707a0): the buildings the character plunders one after the other */
            int plunderAgent;               /* 0xac, the netId of the character who walks the round (the run handler finds it
                                           with gm_FindChar, sends it to the buildings and names it in the message 0x8b) */
            int plunderAt;                  /* 0xb0, the index of the building being plundered */
            int plunderBld[5];              /* 0xb4, the ids of the buildings to plunder (ai_PickActionBuildings' out) */
            unsigned short plunderVictims[5];/* 0xc8, the character picked at each building (ai_PickPartnerRandomWalk's
                                           exclusion list: the run handler passes it with n = 4) */
        };
        struct {                        /* of the plunder offer 0x8b (the message's arg[0..3] from
                                           he_RunPlunder; its run handler 0x570cc0) */
            int plunderDealDeal[4];         /* 0xac, the deal he_PlunderTakePrice / he_PlunderFailNews take: [0] the client's
                                           netId (the plunder event's character), [1] the agent's, [2] the victim's,
                                           [3] the price */
        };
        struct {                        /* of the a master's production job 0x8c (its alloc handler
                                           0x570ef0 and run handler 0x571000; the workers are ids[0..3], the building from) */
            unsigned short masterworkGood;  /* 0xac, the goods produced (an ai_Goods index; its name is the text 0x9a8 + 2 * good) */
            char masterworkPadae[2];
            float masterworkMade;           /* 0xb0, the units made so far, 0 at the start */
            int masterworkLeft;             /* 0xb4, the working minutes left, 0x168 at the start */
            AITIME masterworkSince;         /* 0xb8, the time the last production step counted up to */
        };
        struct {                        /* of the grave care job 0x8d (the message's graveWork words
                                           from ai_GraveCare; its alloc handler 0x571550, run handler 0x571640; the worker is ids[0]) */
            float graveCareCare;            /* 0xac, the care done so far, 0 at the start (handed to gv_OrderAdjustEntry at the end) */
            int graveCareSize;              /* 0xb0, the grave's size: the list of the building's graveyard (gv_ListEntry's i) */
            unsigned char graveCareEntry;   /* 0xb4, the entry in that list */
            char graveCarePadb5[3];
            int graveCareLeft;              /* 0xb8, the working minutes left, 0x1fe at the start */
            AITIME graveCareSince;          /* 0xbc, the time the last care step counted up to */
        };
        struct {                        /* of the event 0x8e (its alloc handler 0x571990, run handler 0x5719e0) */
            int deathDuePrice;              /* 0xac, the amount the character pays when it can (cm_SendMoveGoods) */
        };
        struct {                        /* of the graveyard worker's theft 0x94 (the message's
                                           arg[0] from he_RunGraveyardWorkers; run handler 0x572fd0) */
            int graveTheftWorker;           /* 0xac, the netId of the worker */
        };
        struct {                        /* of the training job 0x8f (the message's arg[0..2] from
                                           ai_SendFreeSpies; its alloc handler 0x571ac0, run handler 0x571c30) */
            int graveTrainingTrainee;       /* 0xac, the netId of the character trained */
            int graveTrainingSkill;         /* 0xb0, the index of the skill trained (AICHAR.skills: 1, 2 or 4) */
            int graveTrainingObjId;         /* 0xb4, the id of the building's object it trains at (0x211), -1: none */
            AITIME graveTrainingUntil;      /* 0xb8, the time the training ends: 3 hours after the first due time */
        };
        struct {                        /* of the meeting event 0x90 (its alloc he_AllocMeeting and
                                           run handler 0x5725b0) */
            int meetingBld;                 /* 0xac, the id of the building the meeting is held in */
            int meetingRadius;              /* 0xb0, the radius kind of the meeting search (0x572310's b), capped at 2 */
            int meetingKind;                /* 0xb4, the kind of the meeting (0x572310's c), capped at 2 */
            int meetingRounds;              /* 0xb8, the rounds held (the run handler holds up to 4) */
        };
        struct {                        /* of the meeting scene object event 0x91 (its alloc
                                           handler he_AllocMeetingScene and run handler 0x5726b0) */
            int meetScenePartner;           /* 0xac, the id of the partner event 0x90 the scene is shown for */
            int meetSceneObj;               /* 0xb0, the handle of the scene object the event keeps, -1: none */
            int meetSceneKind;              /* 0xb4, the meeting kind: 2 / 1 / other loads the big / middle / small script */
        };
        struct {                        /* of the grave lease offer event 0x92 (the message
                                           0x92 lease gv_GraveyardTurn posts; its run handler 0x572a50 and the answer
                                           0x5728d0) */
            int graveLeaseBld;              /* 0xac, the graveyard building's id */
            char graveLeasePadb0[4];        /* 0xb0: AIJOB.graveSize */
            char graveLeasePadb4[1];        /* 0xb4: AIJOB.graveEntry */
            char graveLeasePadb5[3];
            int graveLeasePrice;            /* 0xb8, the lease price (gv_LeasePrice) */
            unsigned short graveLeaseYears; /* 0xbc, the years the lease is extended by (10) */
        };
        struct {                        /* of the gypsy event 0x9d (its alloc he_AllocGypsyApproach,
                                           run he_RunGypsyApproach; he_GypsyApproach dispatches the approach) */
            int gypsyApproach;              /* 0xac, the approach he_GypsyApproach dispatches (0 disease .. 5+ slowdown) */
            int gypsyFigure;                /* 0xb0, the netId of the gypsy character (gm_FindChar) */
        };
        struct {                        /* of the gypsy curse event 0x9e (the message 0x9e
                                           he_GypsyCurse posts: arg[0] at 0xac, arg[1] at 0xb0; its alloc
                                           he_AllocGypsyCurse, run he_RunGypsyCurse) */
            int curseGypsy;                 /* 0xac, the netId of the gypsy character the curse pays, -1: the cursed
                                           character is the gypsy himself (he_GypsyCurse sends -1 then) */
            int curseCursed;                /* 0xb0, the netId of the cursed character (he_GypsyCurse's arg[1]) */
        };
        struct {                        /* of the trial event 0xa0 (its alloc he_AllocTrialScene,
                                           run he_RunTrialScene and the trial he_TrialPayment) */
            unsigned int trialCaseLevel;    /* 0xac, the trial's level (below 4 / 7 raises the payment's bar; compared unsigned);
                                           the message's arg[0], the strength ai_CurseTargetWindow sends, which shows
                                           the text 0x41fb + it while the event runs */
        };
        struct {                        /* of the circus show event 0xa1 (its alloc he_AllocMeeting4, run
                                           he_RunCircusShow and the room query he_FindMeetingRoom); the four figures are AIJOB.ids */
            int circusIncome;               /* 0xac, the income of the meeting (he_CircusShowIncome adds to it) */
            int circusRoom;                 /* 0xb0, the show's time left (0xf0, 0x78 less per round); > 0: the room is looked up (he_FindMeetingRoom) */
            int circusStop;                 /* 0xb4, cm_SendChrStop's argument */
            char circusPadb8[4];
            int circusStart;                /* 0xbc, the index into circusClasses the room query starts at (he_AllocMeeting4:
                                           0, one more per round) */
            union {
                struct {
                    unsigned short circusClasses[4];/* 0xc0, the building classes the room query hands to gm_BuildQuery
                                                   (key 5), picked by he_AllocMeeting4 from 7 / 0x16 / 0xf / 0xa */
                    unsigned short circusObjs[4];   /* 0xc8, the meeting object ids (he_CircusShowIncome fills the first free one) */
                };
                unsigned short circusRoomKeys[5];   /* 0xc0, the classes as he_FindMeetingRoom reads them: its index (circusStart,
                                                   then n % 4 + 1) reaches 4, the word after the classes, circusObjs[0]
                                                   (@original: the bytes of the original's off-by-one) */
            };
            int circusBld;                  /* 0xd0, the id of the building the show is at (he_RunCircusShow), -1 at the allocation */
        };
        struct {                        /* of the ransom demand event 0x3e (he_RunRansom's message 0x3e) */
            int ransomDemandVictim;         /* 0xac, the netId of the kidnapped character (gm_FindChar), who is asked to pay */
            int ransomDemandMaster;         /* 0xb0, the netId of the guild's master (gm_FindChar), who is paid */
            int ransomDemandRansom;         /* 0xb4, the ransom */
        };
        struct {                        /* of the burglary event 0x3f (he_AllocBurglary / he_RunBurglary);
                                           the gang is AIJOB.ids */
            char burglaryPadac[4];          /* 0xac: AIJOB.targetBld */
            int burglaryGuild;              /* 0xb0, the id of the thieves' guild the gang comes from */
            int burglarySlot;               /* 0xb4, the cm slot of the accusation (gv_Accuse) when the watch saw it, -1: none */
            int burglaryWatch;              /* 0xb8, the id of the patrol event 0x43 that saw it (HEDETECT.found) */
            int burglaryGuardBld;           /* 0xbc, that patrol's start building (patrolStart), which counts the reward */
        };
        struct {                        /* of the building spying event 0x40 (he_AllocDueInOne /
                                           he_RunBuildingSpying); the spies are AIJOB.ids */
            char bldSpyPadac[4];            /* 0xac: AIJOB.targetBld */
            int bldSpyHome;                 /* 0xb0, the id of the spies' building (its owner is told), where the report goes */
        };
        struct {                        /* of the ambush event 0x48 (he_AllocAmbush / he_RunAmbush): the
                                           gang (AIJOB.ids) lies in wait at a scene object for passing transports */
            char ambushPlace[0x20];         /* 0xac, the name of the scene object the gang waits at (a name with "STADT":
                                           the fight's variant flag 8) */
            AITIME ambushUntil;             /* 0xcc, the time it gives up (the alloc handler: 48 hours ahead) */
            char ambushPadda[2];
            int ambushPartySlot;            /* 0xdc, the cm send slot of the fight party (cm_SendNewParty) */
            int ambushParty;                /* 0xe0, the id of that party (cm_GetSlotValue; cm_PartyById) */
            unsigned int ambushSkill;       /* 0xe4, the gang's mean skills[2] */
        };
        struct {                        /* of the fire event 0x4e (he_AllocFire / the run handler
                                           0x5644e0), laid out as the storm event's (AIJOB.stormBlds) */
            int fireBlds[16];               /* 0xac, [0] the burning building's id (the message's, else a random pick),
                                           [1 ..] the buildings within radius of it, -1: none */
            int fireCenter;                 /* 0xec, the id of the building of blds[0] */
            int fireRadius;                 /* 0xf0, the distance a neighbour building must be within (the message's value) */
        };
        struct {                        /* of the storm (WIRBELSTURM) event 0x50 (he_AllocStorm / he_RunStormEvent) */
            int stormBlds[16];              /* 0xac, the ids of the 16 buildings its alloc handler collected, [0] the target,
                                           -1: none */
            unsigned char stormDue;         /* 0xec, nonzero: the run handler damages the buildings once, then clears it */
            char stormPaded[3];
            int stormRadius;                /* 0xf0, the distance a follower building must be within (the message's value,
                                           1000: AIMSG.word9c of the WIRBELSTURM command) */
            char stormPadf4[0xc];
            int stormW100;                  /* 0x100, 0 at the allocation (no reader known) */
            int stormW104;                  /* 0x104, 0 at the allocation (no reader known) */
        };
        struct {                        /* of the burning event 0x4f (its alloc handler he_AllocBurn,
                                           its run handler 0x5649b0) */
            int burnBld;                    /* 0xac, the id of the burning building (the message's arg[0]) */
            int burnDuration;               /* 0xb0, the burning time (the message's arg[1]), scaled by the alloc handler */
            unsigned char burnState;        /* 0xb4, the run handler's state, 0 at the start */
            char burnPadb5[3];
            int burnHelpers[16];            /* 0xb8, the netIds of the characters the run handler sends to fetch water
                                           (cm_SendChrGotoBuilding "Brand"), -1: none */
            int burnFire;                   /* 0xf8, the id of the fire event 0x4e whose message 0x4f started it (AIMSG.srcEvent) */
            unsigned burnVoiceAt;           /* 0xfc, the tb_Calls tick of the last "Brand_Zerstoert" voice */
            char burnPad100[4];
            unsigned char burnNews;         /* 0x104, nonzero: the owner gets the message box (the message's extraFlag) */
        };
        struct {                        /* of the healing event 0x6c (he_AllocHealing / he_RunHealing) */
            int healCharId;                 /* 0xac, the netId of the character healed (gm_FindChar) */
            unsigned healAmount;            /* 0xb0, the health left to heal, 200 at the allocation (the run's step takes it down) */
            AITIME healEnd;                 /* 0xb4, the next run (AIJOB.end6c) */
            char healPadc2[2];
            int healRoom;                   /* 0xc4, the room object the character is sent to (gm_FindObjectInst), -1: none */
        };
        struct {                        /* of the kill-player event 0x72 (its alloc handler 0x565d10,
                                           run handler he_RunKillPlayer) */
            int killChr;                    /* 0xac, the netId of the character to die (gm_FindChar) */
            int killParty;                  /* 0xb0, the id of its funeral party (cm_PartyById), -1: none */
            int killSlot;                   /* 0xb4, the cm send slot of the party (cm_SendNewParty), -1: none */
        };
        struct {                        /* of the night watchman event 0x73 (its alloc handler
                                           he_AllocNightWatch, run handler he_RunNightWatch) */
            int nightWatchSpeaker;          /* 0xac, the voice source of the announcements (snd_QueueVoice's first argument) */
        };
        struct {                        /* of the robbery event 0x75 (he_AllocDueInOne / he_RunRobbery),
                                           laid out as the burglary's AIJOB.burglary*; the gang is AIJOB.ids */
            int robberyTarget;              /* 0xac, the id of the building raided */
            int robberyHome;                /* 0xb0, the id of the gang's building, where it goes back to */
            int robberySlot;                /* 0xb4, the cm slot of the accusation (gv_Accuse) when the watch saw it, -1: none */
            int robberyWatch;               /* 0xb8, the id of the patrol event 0x43 that saw it (HEDETECT.found) */
            int robberyGuardBld;            /* 0xbc, that patrol's start building (patrolStart), which counts the reward */
        };
        struct {                        /* of the search events 0x14 / 0x15 (the two trade search windows count them) */
            unsigned char groupSize;        /* 0xac, how many characters search: rank1Count + rank2Count (ls_FixupAfterLoad
                                           recounts it after a load) */
            char groupPadad;
            unsigned short groupGood;       /* 0xae, the good searched for */
        };
        struct {                        /* of the trial-punishment events 0x5b (the fine, he_RunFinePayment) and 0x5c (the
                                           pillory, he_RunPilloryPunishment; their alloc handler he_AllocPunishment) */
            int punishAmount;               /* 0xac, the amount of each payment (the message's first argument): taken from
                                           the character by the fine, the negated income of the pillory's AP event */
            int punishDays;                 /* 0xb0, the payments left (the message's second argument), counted down */
        };
        struct {                        /* of the simulation events 0x66 (he_RunAccidentSim), 0x68 (the inn) and 0x70 (the
                                           disease twin of 0x66); their alloc handlers clear them */
            int simCursor;                  /* 0xac, the ai_Chars index the next run starts at */
            int simStep;                    /* 0xb0, the stride through ai_Chars, one of 16 numbers prime to 0x300; 0: not
                                           started (the next run picks one and a random cursor) */
            int simDone;                    /* 0xb4, the characters visited this round */
        };
        struct {                        /* of an event that orders a transport (AIJOB.transportOrder): the building ids it
                                           names, which he_AllocTransport moves to a replaced goal */
            char orderPadac[4];
            int orderBld;                   /* 0xb0 */
            char orderPadb4[4];
            int orderStopsB8[3];            /* 0xb8 */
            int orderStopsC4[3];            /* 0xc4 */
        };
        char tail[0xa0];                /* 0xac..0x14b whole: the message's words from +0x58 as the event takes them
                                           (he_CreateEvent) and message 0x1d sends and takes them (cm_SendExSetHE / cm_ExSetHE),
                                           as the save writes them (ls.c) */
    };
} AIJOB;

typedef char ai_AssertAIJOB[sizeof(AIJOB) == 0x14c ? 1 : -1];

typedef struct AIFIN {                  /* what gm_PlayerRecord finds for a character */
    unsigned short w00;                 /* 0x00, the character's AICHAR.w050 (cm.c 0x4c6cd0 copies it) */
    char family[0x10];                  /* 0x02, the family name (cm.c 0x4c6cd0 sets it with the character's) */
    char pad12[2];                      /* 0x12 */
    int burglaryTakings;                /* 0x14, the money its character's burglaries took (he_RunBurglary adds it; the round
                                           report prints it with text 0x200d, then adds it with gangTakings to missionMoney[0]
                                           and clears it) */
    int gangTakings;                    /* 0x18, the money the pickpocket gangs brought its character (he_RunGang adds it;
                                           text 0x200c, rolled into missionMoney[0]) */
    int lootTakings;                    /* 0x1c, the loot value a won fight / raid took from the loser's goods
                                           (cm_LootStock and cm_LootCarts add it to the winner's record) */
    int ransomTakings;                  /* 0x20, the ransoms its character took as a thieves' guild master (he_RunRansomDemand
                                           adds them; text 0x2010, rolled into missionMoney[2]) */
    int madeValue;                      /* 0x24, the price value of the goods its workshops made (cm.c 0x4c78c0 adds it
                                           with the building's AIBLD.roundSums[0]) */
    int spyPaid;                        /* 0x28, the money the player paid to the cabinet's spies (ai_CabinetSpyWindow adds each payment) */
    int missionMoney[5];                /* 0x2c .. 0x3f, the money statistics: the round report (main_RoundReport) adds the
                                           round parts in ([0] burglaryTakings + gangTakings, [1] lootTakings, [2] ransomTakings, [3]
                                           madeValue, [4] the character's AICHAR.v1a4 + v1a0); read by the mission conditions, converted with
                                           gm_ConvertMoney: 0x38 by the types 1 / 6 / 14 / 22 / 32, 0x2c + 0x34 by
                                           20 / 25 / 36, 0x30 by 26 / 37, 0x3c by 27 */
    int upgradeSpent;                   /* 0x40, the money the record has paid for workshop upgrades (ai_BuyUpgrade) */
    int renovationSpent;                /* 0x44, the money it has paid for renovations (ai_BuyUpgrade, am.c 0x497ee0) */
    int loansRepaid;                    /* 0x48, the loan sums the character has paid back at a money lender (ai_RepayLoan adds each) */
    int customerPaid;                   /* 0x4c, the money its character's customers events cost (he_RunCustomers adds the
                                           cost; the round report prints it with text 0x201a as a cost and clears it) */
    int cartSpent;                      /* 0x50, the money the character has paid for new carts (lc.c ai_BuyCartWindow adds each price) */
    int buildPaid;                      /* 0x54, the money its character paid for new buildings (he_RunConstruction adds the
                                           price; text 0x2015, a cost cleared by the round report) */
    float duelBias;                     /* 0x58, the bias for who starts a dice duel (ai_DuelStart: below the random draw the
                                           player starts and it rises by 0.2 + 0..0.11, else it falls by the same); 0.5 at
                                           every round change (main.c 0x5384e0) */
    float tavernChance;                 /* 0x5c, the chance of being invited to the tavern dice game (ai_TavernDiceWindow);
                                           each visit takes it to * 0.66 - 0.1 (invited) or * 0.66 - 0.02 (not invited,
                                           after 11 o'clock); 1 at every round change */
    float pokerChance;                  /* 0x60, the chance of sitting down to the gypsy poker game (ai_PokerGame: above a random
                                           draw after 11 o'clock, then * 0.66 - 0.1); 1 at every round change and at a load
                                           before version 0x10018 */
    int taught;                         /* 0x64, the trial step courses its character finished as the teacher (he_RunTrialSteps
                                           counts it; the save game keeps it from version 0x10014) */
    int saved68;                        /* 0x68, an int the save game keeps (from version 0x10014); no other reader known */
    int officeSentences;                /* 0x6c, the sentences 4 / 6 / 8 its character passed as the judge of a trial on an
                                           office holder (cm.c 0x4db700) */
    int saved70;                        /* 0x70, an int the save game keeps (from version 0x10018); no other reader known */
    unsigned char jobByGroup[0x11];     /* 0x74, one job id per title group (gm_TitleGroup): 0 = none (gm_SetJob fills it; ai_DecideApprenticeship takes a free group) */
    char pad85[3];
    float camAngle;                     /* 0x88, the player's camera angle factor (sv_CameraAngleFactor; sv.c) */
    D3VECTOR4 camPos;                   /* 0x8c, the player's camera position, restored with the view (sv.c; the save game
                                           keeps all 16 bytes) */
    D3VECTOR camRot;                    /* 0x9c, its rotation (D3OBJECT.rotation; f3init restores .y) */
    int savedA8;                        /* 0xa8, an int the save game keeps; no other reader known */
} AIFIN;                                /* 0xac bytes, the 16 records of gm_PlayerRecords */

typedef struct AIRECIPE {               /* 0xb8 bytes, a goods list: filled by gm_StallGoodsList / gm_BuildingGoodsList
                                           / gm_BuildingGoodsList17 (f3gm.c, which clear and fill it as 0x2e ints) */
    int n;                              /* 0x00, the capacity of the stall (its cap / lvl1c); ai.c walks the entries up to it */
    int count;                          /* 0x04, the number of entries filled */
    int max[16];                        /* 0x08, per entry its stock (gm_ListStock): ai.c takes max - amount as the room left */
    unsigned short item[16];            /* 0x48, per entry the goods id */
    int amount[16];                     /* 0x68, per entry its amount (gm_ListAmount; the object's count of a stall) */
    int stockSum;                       /* 0xa8, gm_StallGoodsList: the sum of the stocks */
    int amountSum;                      /* 0xac, gm_StallGoodsList: the sum of the amounts */
    int value;                          /* 0xb0, gm_StallGoodsList: the goods' value (gm_ItemPrice at 100 times the count) */
    struct AIOBJ *stall;                /* 0xb4, all three fillers: the stall object */
} AIRECIPE;

#pragma pack(push, 1)
typedef struct AISERMON {               /* 7 bytes, a church's sermon settings: its sermon object's +0x1c (AIOBJ.sermon),
                                           sent whole as a G17B7 (cm_SendObject1b5, ai_SermonWindow); a tavern's object
                                           0x1b5 holds its hired helper here (he_AllocTavern / he_RunTavern: priest = the
                                           helper, enabled = hired) */
    signed char text1;                  /* 0x00, the sermon's first text 0x1990 + it (0 .. 7), -1: none */
    signed char text2;                  /* 0x01, its second text 0x1998 + it (0 .. 7), -1: none */
    int priest;                         /* 0x02, the netId of the priest who preaches, -1: none */
    unsigned char enabled;              /* 0x06, nonzero once the owner paid for the sermons (reasoned name) */
} AISERMON;

typedef struct HESPYREPORT {            /* 0x1c bytes, the words 0x1c .. 0x37 of a spy report (AIOBJ kind 0xca, AIOBJ.report) that message
                                           0x5e (cm_SendSpyReport) sends for a building (he.c's report) */
    AITIME when;                        /* 0x00 (0x1c), the time of the report */
    int bld;                            /* 0x0e (0x2a, AIOBJ.reportBld), the building it reports on */
    int worth;                          /* 0x12 (0x2e), a tenth of the owner's worth (at most 1.6 million) */
    int goods;                          /* 0x16 (0x32), the price of the goods of the building's stall */
    unsigned char skill;                /* 0x1a (0x36), the building's skill 7 */
    unsigned char know;                 /* 0x1b (0x37, AIOBJ.reportKnow), how much it knows, 2 .. 100 percent */
} HESPYREPORT;
typedef struct AIOBJ {                  /* 0x43 bytes, an object (table behind ai_Objects): carts, stores, the
                                           goods in a store, a workshop's level object; what gm_Query finds */
    union {
        unsigned short id;              /* 0x00, index into ai_Goods */
        unsigned short type;            /* 0x00, 0x116: ... */
    };
    int objId;                          /* 0x02, the object's own id (0x500190 gives a new one; messages name the
                                           object by it, 0x4fea50 finds it by it) */
    int ownerId;                        /* 0x06, the id of the building / object / character holding it (gv.h AIOBJ.ownerId) */
    union {
        int holderId;                   /* 0x0a, set at creation (gm_CreateObject): the holder's building id, the holding
                                           object's holderId or the holding character's netId (a cart: its owner
                                           character's netId) */
        int fightSide;                  /* 0x0a, a good shown as a fight scene's "WARE_" object: the id (AICHAR.id) of the
                                           fight side's leader holding it (cm.c: cm_CheckDeath hands it to the defender) */
    };
    union {
        int unk0e;                      /* 0x0e */
        int count;                      /* 0x0e */
    };
    unsigned char fill;                 /* 0x12, how full the cart is in percent (msg.n = 100 - fill; below 0x21 a cart is free for a load, ai_MeisterTrade / ai_UnloadCarts) */
    signed char flags13;                /* 0x13, flags: 0x20 (the guard patrol 0xa6 skips such a cart), 0xa0 set on a sold object (he_RunSale) */
    union {
        int unk14;                      /* 0x14, the object list it holds */
        struct AIOBJ *list;             /* 0x14, the head of the objects it holds (AIOBJ.next chains them) */
        unsigned short *items;          /* 0x14, the same as the item ids it points to (ahm_CreateAlchemist removes the first until none is left) */
    };
    struct D3OBJECT *obj;               /* 0x18, the scene object that shows it (sv_DrawItemNames draws its name above it) */
    union {                             /* 0x1c..0x3a, per kind */
        struct {
            union {
                struct {
                    union {
                        int unk1c;                      /* 0x1c, a building id / a state / a count */
                        int reportStamp;                /* 0x1c, of a spy report: the start of the record its text 0x19fc shows (the
                                                           reports window passes its address; reasoned: when it was made) */
                        int bldId;                      /* 0x1c, of a cart (gm_Query kind 0x1d): the id of its building (main_EndRound looks it up with gm_BuildQuery(1, 1, id)) */
                        int cnt;                        /* 0x1c */
                        unsigned int reserve;           /* 0x1c, of goods in a store: the quarters of the store's stock (gm_ListStock)
                                                           kept from buyers other than its owner (cm.c 0x4c70b0); 4 when created
                                                           there for a character of kind 6 / 7 */
                        struct {
                            unsigned char lvl1c;        /* 0x1c, a workshop's levels, compared with AIENTRY need1c / need20 */
                            unsigned char lvl1d;        /* 0x1d */
                        };
                        unsigned char cap[2];           /* 0x1c, of the objects 0x2a / 0x116: two capacities from the building
                                                           kind (gm_SetCapacities) */
                        unsigned char kindData;         /* 0x1c, the first byte of the per-kind data 0x1c .. 0x3a that
                                                           gm_CreateObject clears (0x1f bytes) before it sets them by kind */
                        struct {
                            int pad1c20;
                            unsigned int flags20;       /* 0x20, of a cart (kind 0x1d): bit 1 (2) is cleared for the carts of the current building when the selection resets (sv_ResetSelection) */
                        };
                        struct {
                            int pad1c20w;
                            int usesLeft;               /* 0x20, of a weapon item (kind 5 in a character's inventory): the uses left of
                                                           a kind 1 / 2 weapon (cm_CharWeapon refuses it at 0; the portrait box shows it) */
                        };
                        struct {
                            int pad1c24[2];
                            struct AIJOB *job24;        /* 0x24, of a cart: a job whose cartBld names a building (sv_RefreshPanel prints that building's kind; reasoned: the job the cart runs) */
                        };
                        int recs[3];                    /* 0x1c..0x27, of a gm_Query kind 300 object in a shop: three record ids for gv_EvidencePrice (0x4ab080 tries them in turn) */
                        struct {                        /* of a room of a building (the objects of AIBLD.objList the enter-building driver walks) */
                            int locked;                 /* 0x1c, nonzero: the room's contacts open ai_UnlockRoomWindow, which clears it when paid */
                            int unlockPrice;            /* 0x20, the money ai_UnlockRoomWindow asks; cleared with locked */
                        };
                        struct {                        /* of an alchemist's laboratory device (kinds 0x24b / 0x256 / 0x266 in the
                                                           building's objList, he_LabIncident) */
                            int broken;                 /* 0x1c, 0 while it works; the laboratory incident adds 1 (reasoned name) */
                            int repair;                 /* 0x20, the incident adds 3 .. 6 (reasoned guess: the repair time) */
                        } lab;
                        AISERMON sermon;                /* 0x1c..0x22, of a church's sermon object (gm_Query kind 0x1b5 in its
                                                           objList; cm_SendObject1b5 makes it) */
                    };
                    signed char escort;                 /* 0x28, of a cart: its escort kind 0 .. 2 (he_AllocTransport picks it by the goods'
                                                           value, gm_LevelPayout prices it) */
                    char pad29;
                    int reportBld;                      /* 0x2a, of a spy report (gm_Query kind 0xca in a building): the id of the
                                                           building it reports on (ai.c 0x4817a0, he.c's raid 0x5461c0) */
                };
                struct {
                    char pad1c29[0xd];
                    struct RTPOINT *route;              /* 0x29, of a cart: its route, a list of rt.c's RTPOINT (rt_CopyPoints; message 0x68 sets it) */
                    int routeIdx;                       /* 0x2d, of a cart: the index of its current point in that route (rt_PointAt; he_RunTransport, rt.c) */
                };
                int seats[4];                   /* 0x1c..0x2b, of a table (kind 0x12d in a building): the ids of the characters at its
                                                   four seats, -1 free (message 0x54 'join' / 'leav' / 'cler', cm_SendTableRequest) */
                struct {                        /* of a dark corner (kind 300 in a tavern room; its recs[] are the three evidence offers) */
                    int pad1c28[3];
                    int cornerYear;             /* 0x28, the dark-corner menu offers its order 0x74 (0x18a7) only while this is below
                                                   ai_Time.year (ai_DarkCornerMenu; reasoned: the year of the last order) */
                };
                struct {                        /* of a feast table object (gm_Query kind 0x17 in a building, he.c 0x5437c0) */
                    int festGuests[4];          /* 0x1c..0x2b, the guests' netIds (gm_FindChar; ai_FeastWindow writes them), -1: none */
                    unsigned char festEssen;    /* 0x2c, the menu pick (AIGRP.essen) */
                    unsigned char festMusik;    /* 0x2d, the musician pick (AIGRP.musik) */
                };
            };
            unsigned char patrolLevel;          /* 0x31, of a guard cart: picks the steps it waits at its route's start, 12, 8, 4, 2, 0
                                                   for 0 .. 4 (he_PatrolStep; reasoned: a level) */
            unsigned char patrolWait;           /* 0x32, of a guard cart: the steps waited so far at its route's start (he_PatrolStep) */
            unsigned char patrolOn;             /* 0x33, of a guard cart: nonzero for the carts the patrol event 0xa6 steps (he_RunPatrolEvent) */
            char pad34[2];
            unsigned char reportGuard;          /* 0x36, of a spy report: (reasoned) the guard level it found: the AI burgles only
                                                   when reportKnow reaches util_Random(20) + twice it (ai.c 0x481ef0); the reports
                                                   window shows it after reportKnow (text 0x19fc) */
            unsigned char reportKnow;           /* 0x37, of a spy report: how much it knows, in percent (ai.c spies again below a
                                                   random 50 .. 99; the round settlement lowers it by twice the building's rank and
                                                   drops the report at 5 or less, main.c; the raid adds it to its chance) */
            char pad38[3];
        };
        struct {                        /* of a good held in a character's inventory (ai_InventoryHas, ai_BuildingHasItem,
                                           the inventory window, the Domizil goods' clock lc_UpdateGoodsReserves) */
            int minutesLeft;            /* 0x1c, of a Domizil good in use: the minutes its effect still runs
                                           (lc_UpdateGoodsReserves counts it down from G9DOMIZIL.minutes) */
            signed char inUse;          /* 0x20, of a Domizil good: set to 1 by ai_UseGood with minutesLeft (the name is
                                           a reasoned guess) */
            int active;                 /* 0x21, nonzero when the object counts as held, of a Domizil good while its
                                           effect runs (ai_InventoryHas tests it; lc_UpdateGoodsReserves clears it
                                           when minutesLeft runs out; the name is a reasoned guess) */
            int placeBldId;             /* 0x25, the id of the building the object stands in (reasoned guess:
                                           ai_BuildingHasItem compares it with AIBLD.id) */
            char pad29g[4];
            AITIME since;               /* 0x2d, of a Domizil good in use: when minutesLeft was last counted down */
        };
        HESPYREPORT report;             /* 0x1c..0x37, of a spy report (kind 0xca) its record as message 0x5e sends it (the
                                           cm_ExSpyReport handler writes it; reportBld / reportGuard / reportKnow above)
                                           name some of its words */
    };
    struct CHARACTER *sceneObj;         /* 0x3b, the scene character (ch.h CHARACTER) that shows a cart (gm_CreateObject
                                           creates the cart man or the horse, ch_Create) */
    struct AIOBJ *next;                 /* 0x3f, the next object of its list (an inventory, a store) */
} AIOBJ;
#pragma pack(pop)

typedef struct AIMSG {                  /* 0xf8 bytes, given to cm_SendLongMessage */
    int unk00;
    unsigned char type;                 /* 0x04 */
    char pad05[3];
    int to;                             /* 0x08, the receiving player's netId (every sender
                                           writes the building owner's netId) */
    int fromId;                         /* 0x0c, the sending building's id */
    int nIds;                           /* 0x10, how many of ids[] are set (msg.ids[msg.nIds]++) */
    int reserved14;                     /* 0x14, only ever written 0 (hst.c: -1), no reader names it (f3init.c's view names it so) */
    char pad18[0x10];
    AITIME time;                        /* 0x28 */
    unsigned char flags;                /* 0x36, the message flags (1 / 2 / 9; he.md's message record) */
    char pad37;
    int ids[8];                         /* 0x38 */
    union {                             /* 0x58..0xf7: the kinds' words */
        AITIME inviteWhen;              /* 0x58, of the feast invitation 0x36 (he.c 0x5436a0): the time the feast
                                           starts, the event's end clock */
        struct {
            union {
                int arg[11];                    /* 0x58 */
                unsigned short itemId;          /* 0x58, the good a buy / move message is about (the 16-bit stores) */
                unsigned char thiefClass;       /* 0x58, of the thief message 0x16 (ai_SendFreeThieves): 3 when the
                                                   candidate's sk83 is below its sk82, else 2 */
                struct {                        /* the trade kinds */
                    int car;                    /* 0x58 */
                    int n;                      /* 0x5c */
                    int ch;                     /* 0x60 */
                    int dst[6];                 /* 0x64, 0..2 sold, 3..5 bought */
                    union {
                        unsigned short item[6]; /* 0x7c */
                        struct {
                            int pad7c[2];
                            int cost;           /* 0x84, the beat-up message 0x1a: the amount the decide callback
                                                   (ai_DecideBeatUp's worth estimate) puts on the brawl
                                                   (ai_ExecuteBeatUp); the trade messages set it 0 */
                        } s;
                    } u;
                };
                struct {                        /* the free-object message 0x4a of the AI message 0x2e (rmsg.c
                                                   ai_MsgFreeBuildingObjectType2e): the news text id of the message kind */
                    char pad58[0xc];
                    unsigned short textId;      /* 0x64, the news text (0x12e7 + the AI message type) */
                } freeBuilding;
                struct {                        /* the skill-bonus message 0x82 (its event's words AIJOB.skillBonus*, 0x54
                                                   further; he_StartSkillBonus) */
                    unsigned char skill1;       /* 0x58, the first skill number (AIJOB.skillBonusSkill1) */
                    unsigned char skill2;       /* 0x59, the second skill number */
                    char pad5a[2];
                    float bonus1;               /* 0x5c, the bonus for skill1 (negative: a malus) */
                    float bonus2;               /* 0x60, the bonus for skill2 */
                    int hours;                  /* 0x64, how long it lasts (AIJOB.skillBonusHours) */
                } skillBonus;
                struct {                        /* the effect message 0x76 of a Domizil good used on a target (the event
                                                   keeps these words 0x54 further: AIJOB.effectGood at 0xc2) and
                                                   the send-home message 0x77 of the good 0x178 (target only) */
                    int target;                 /* 0x58, the id of the target (a building) */
                    char pad5c[0x12];
                    unsigned short good;        /* 0x6e, the Domizil good (G9DOMIZIL.id) */
                } effect;
                struct {                        /* the AI message 0x42 (ai_PostRandomMessages): the record a G14MSG view points
                                                   at (id at 0x58, type at 0x5c) */
                    int car;                    /* 0x58, the character the message is for (G14MSG.id) */
                    unsigned short type;        /* 0x5c, the message type 0 .. 0x44 (G14MSG.type) */
                } aiMsg;
                struct {                        /* the goods orders 0x14 / 0x15 (ai_SendJobOrders); arg[1] / arg[2] carry
                                                   the workshop's object */
                    unsigned char count;        /* 0x58, how many workers the order names (its nIds) */
                    char pad59;
                    unsigned short item;        /* 0x5a, the good to make (AIENTRY.item) */
                } goodsOrder;
                struct {                        /* the rank message 0x69 (gv_CheckRankUp) */
                    unsigned char rank;         /* 0x58, the new rank (AICHAR.level) */
                    char pad59[3];
                    int ch;                     /* 0x5c, the netId of the character who rose */
                } rankUp;
                struct {                        /* the pamphlet message 0x35 (0x4aa940) */
                    AITIME when;                /* 0x58, the game time it was sent */
                    char pad66[2];
                    int about;                  /* 0x68, the netId of the character it is about */
                    char pad6c;
                    unsigned char variant;      /* 0x6d, a random text variant 0..0x1c */
                } pamphlet;
                struct {                        /* the tavern message 0x2b (he_PostEvent2b, one per tavern building) */
                    int pad58;
                    unsigned char mode;         /* 0x5c, posted 0; the event keeps it at +0xb0 (a reasoned guess: a mode byte, its
                                                   reader is not read yet) */
                } tavern;
                struct {                        /* the grave lease offer 0x92 to a player (gv_GraveyardTurn; he_AnswerGraveLease answers it with gv_OrderExtendGrave) */
                    int bld;                    /* 0x58, the graveyard building's id */
                    int size;                   /* 0x5c, the grave size */
                    unsigned char entry;        /* 0x60, the entry of that size */
                    char pad61[3];
                    int price;                  /* 0x64, the lease price (gv_LeasePrice) */
                    int years;                  /* 0x68, the years the lease is extended by (10) */
                } lease;
                struct {                        /* the graveyard work 0x8d on a grave (ai_GraveCare; he_HasGraveWork finds its event) */
                    int pad58;
                    int size;                   /* 0x5c, the grave's size (list) */
                    unsigned char index;        /* 0x60, its index in that list */
                } graveWork;
                struct {                        /* the payment message 0x27 (lc.c ai_MoneyMessengerWindow); the payment
                                                   event keeps its words 0x54 further on (he.c AIJOB.ev27*) */
                    int bld;                    /* 0x58, the bank the money goes out from (AIBLD.id) */
                    unsigned char player;       /* 0x5c, the slot of the player it goes to (ai_PlayerSlots) */
                    char pad5d[3];
                    int amount;                 /* 0x60, the amount paid out, the messenger's fee taken */
                } payment;
                struct {                        /* the apprenticeship message 0x5e (lc.c ai_ChooseProfessionWindow; am.c's
                                                   ai_ExecuteApprenticeship) */
                    int parent;                 /* 0x58, the netId of the parent who pays */
                    unsigned char bldClass;     /* 0x5c, the building class the child learns in (gm_TitleNumber) */
                    char pad5d[3];
                    int price;                  /* 0x60, the fee */
                } apprenticeship;
                struct {                        /* the study message 0x5f ("Studium", ai_ExecuteStudy) */
                    int ch;                     /* 0x58, the netId of the character who pays */
                    int pad5c;
                    int child;                  /* 0x60, the child's value from the decide callback (s1->arg2) */
                    unsigned char subject;      /* 0x64, the offer chosen (s2->ref) */
                    unsigned char level;        /* 0x65, the offer's second value (s2->arg2) */
                } study;
                struct {                        /* the talent training message 0x60 (lc.c ai_TalentWindow, am.c
                                                   ai_ExecuteTrainSkill / ai_ExecuteTrainJobSkill) */
                    char pad58[2];
                    unsigned char talent;       /* 0x5a, the talent (AICHAR.skills index) the training raises */
                } training;
                struct {                        /* the sabotage message 0x19 (lc.c ai_SabotageCallback) */
                    int bld;                    /* 0x58, the building sabotaged (AIBLD.id; the player's sabotage
                                                   event 0x19 keeps it at +0xac, AIJOB.bldId) */
                    char pad5c[0x20];
                    int price;                  /* 0x7c, the price paid for it */
                } sabotage;
                struct {                        /* the room upgrade message 0x1f (lc.c ai_RoomUpgradeWindow); the event
                                                   keeps the words 0x54 further on (AIJOB.bldId, upgradeGood) */
                    int bld;                    /* 0x58, the building upgraded (AIBLD.id) */
                    unsigned short good;        /* 0x5c, the upgrade good built in (ai_Goods type 2 or 6) */
                } roomUpgrade;
                struct {                        /* the blackmail contact's letter 0x47 (lc.c ai_BlackmailContactWindow,
                                                   ai_BlackmailContact) */
                    int from;                   /* 0x58, the netId of the sender */
                    int victim;                 /* 0x5c, the netId of the character it is sent to */
                    unsigned short text1;       /* 0x60, its first text, 0x1d6d + a roll 0 .. 8 */
                    unsigned short text2;       /* 0x62, its second text, 0x1d76 + a roll 0 .. 8 */
                } letter;
                struct {                        /* the master exam question 0x7e (he_RunExamOffer); the question event keeps
                                                   the words 0x54 further on (he.c AIJOB.examBox*) */
                    int chr;                    /* 0x58, the netId of the character asked */
                    int examId;                 /* 0x5c, the id of the exam offer event 0x7f that asks (he.c AIJOB.examOffer*) */
                    AITIME due;                 /* 0x60, the answer is due: now + 2 hours */
                } exam;
                struct {                        /* the AI message 0x56 of the master exam fee (he_RunMasterExamPay) */
                    unsigned char what;         /* 0x58, 4 (reasoned: the kind of payment, its reader is not read yet) */
                    char pad59[3];
                    int amount;                 /* 0x5c, the amount paid */
                } fee;
                struct {                        /* the AI message 0x6a he_RunTraining posts when a player's skill reaches a
                                                   new level; the event 0x6a takes the words over at +0xac (he.c AIJOB.skillUp*) */
                    unsigned char skill;        /* 0x58, the skill (AICHAR.skills index) */
                    char pad59[3];
                    int level;                  /* 0x5c, its new level: the value / 42 */
                } skillLevel;
                struct {                        /* the AI message 0x78 he_BeginPlague posts to every player character */
                    int bld;                    /* 0x58, the start building's id */
                    int target;                 /* 0x5c, the target building's id: the start building */
                    int next;                   /* 0x60, -1 */
                    int walk;                   /* 0x64, the event's walk index */
                    int step;                   /* 0x68, the event's walk step */
                    int left;                   /* 0x6c, the event's countdown */
                } plague;
                struct {                        /* the countdown message 0x51 (hst.c's FERNHANDEL_RAUBRITTER command,
                                                   ai_CommandRemoteTradeRaider); the event keeps the words 0x54 further on
                                                   (AIJOB.countdownRuns) */
                    unsigned char countdownRuns; /* 0x58, the runs the countdown event lasts */
                    char countdownDir;          /* 0x59, the command's direction letter N / S / O / W / A */
                };
                struct {                        /* the AI credit message 0x23 (a bank's offer, ai_ExecuteTakeCredit) */
                    int bld;                    /* 0x58, the bank building's id */
                    int from;                   /* 0x5c, the netId of the character who takes the credit */
                    int amount;                 /* 0x60, the sum lent (ORDCREDIT.amount) */
                    int term;                   /* 0x64, the term in rounds, 2 .. 7 (ORDCREDIT.term) */
                    int pad68;
                    int interest;               /* 0x6c, the rate (ORDCREDIT.interest) */
                } credit;
            };
            union {
                int amount[3];                  /* 0x88, of the bought goods */
                struct {
                    char pad88;
                    signed char patrolRoll;     /* 0x89, of the patrol message 0x43 a random 2 .. 5 (ai_CalcMeisterWache);
                                                   it lands at the event's +0xdd, after patrolRound; no reader known */
                };
            };
            char pad94[8];
            union {
                struct {
                    unsigned char textFlags;    /* 0x9c, of a note with a text (cm_SendPartyNote): 0xc, 0xe with the party's
                                                   building, | 0x10 when a second text follows the first */
                    unsigned char deferTrade;   /* 0x9d, 1 in the trade message 11 when the AI is over its work limit
                                                   (ai_WorkLoad > ai_WorkLimit); the event keeps it at +0xf1 (AIJOB.flags,
                                                   nonzero defers the posting) */
                    unsigned char flag9e;       /* 0x9e, 1 in the guard cart's message 0xf (he_PatrolStep); the meaning is
                                                   not known */
                    char pad9f;
                };
                int word9c;                     /* 0x9c, 1000 in the timed messages 0x4e / 0x50 (ord_UpdateMessageEvent, a
                                                   dword store; hst.c's BRAND / WIRBELSTURM commands); the event keeps it at
                                                   +0xf0 (AIJOB.modes / flags; the storm event's stormRadius) */
            };
            int jobId;                          /* 0xa0, of the move message 0xf the id of the event that posted it (the trade
                                                   event's, he_AllocTrade); -1 from the lost cart (ai_MeisterCollectTrans), 0 from
                                                   the patrol (he_PatrolStep) */
            int srcEvent;                       /* 0xa4, of the explosion message 0x4f from a fire (he_RunFire): the fire
                                                   event's id (the burning event 0x4f keeps it at +0xf8) */
            char pada8[8];
            unsigned char extraFlag;            /* 0xb0, 1 in the explosion message 0x4f (gv_ExplodeShot); the meaning is not known */
            char padb1[0x47];
        };
        struct {                        /* the hire requests of the personnel book (ai_PersonnelBook): 6 a worker for
                                           a row, 7 the building's master; the event keeps the words 0x54 further on
                                           (AIJOB.hireTitle, tourCounters) */
            unsigned char hireTitle;    /* 0x58, of 6 the title rank hired (AIBTYPE.title2), of 7 0 */
            unsigned char hireFlag;     /* 0x59, of 6: 1 */
            char padhire5a[2];
            union {
                struct {
                    int hireRows[12];   /* 0x5c, of 6: 1 for the row the worker is hired for */
                    int hireRoom;       /* 0x8c, of 6: the objId of the room the panel shows (sv_PanelShown), -1 at home */
                };
                struct {
                    int hireMaster;     /* 0x5c, of 7: 1 */
                    int hireMasterRoom; /* 0x60, of 7: as hireRoom */
                };
            };
        };
        struct {                        /* the build message 0xd (ai_ExecBuildBuilding 0x4a5320) */
            char padbuild58[0x28];
            D3VECTOR4 buildPos;         /* 0x80, the plot's world position (ai_ObjectPosition, a 0x10-byte vector) */
            float buildRot[3];          /* 0x90, the plot's angles (ai_ObjectAngle: [1] the turn) */
            char buildPath[0x5c];       /* 0x9c, the path of the building's model group ("...gebaeude/*gb_<NAME>.ogr");
                                           the size is reasoned: up to the record's end */
        };
        struct {                        /* the espionage message 0x18 (lc.c ai_EspionageAmountCB); the event keeps
                                           the words 0x54 further on (AIJOB.id4 is the target) */
            int bld;                    /* 0x58, the spying player's own building (AICHAR.bld2's id), -1: none */
            char pad5c[0x14];
            int target;                 /* 0x70, the netId of the character spied on */
            char pad74[0x1c];
            int price;                  /* 0x90, the price paid */
            int length;                 /* 0x94, the length picked on the slider, 0 .. 2 */
        } espionage;
    };
} AIMSG;

typedef char ai_AssertAIMSG[sizeof(AIMSG) == 0xf8 ? 1 : -1];

#pragma pack(push, 1)
typedef struct AIGOOD {                 /* 0x41 bytes, ai_Goods[] */
    signed char type;                   /* 0x00 */
    union {
        char name[0x25];                /* 0x01 */
        struct {
            char padname[0x20];
            unsigned char cls;          /* 0x21, the goods class (gm_ClassBuilding's index) */
            unsigned int workTime;      /* 0x22, reasoned: the production time of one unit (the item tooltip shows it, in a building divided by the staff factor; ai_CalcEntryCost divides the margin by it) */
        };
    };
    unsigned short need[4];             /* 0x26 */
    unsigned short in[4];               /* 0x2e, the goods it is made of */
    unsigned short batch;               /* 0x36, the amount one production run makes (the store needs room for
                                           it and the market that much plus the stock; he.c 0x5690c0 hands it out) */
    int price;                          /* 0x38, the cached price of 100 pieces / 32 (gm_ItemPrice), 0: not computed yet */
    char pad3c[4];
    unsigned char noSale;               /* 0x40, nonzero: shown in the item tooltip instead of the price (text 0x21,
                                           ai_OpenItemTooltip; reasoned: not for sale, ai_DecideProduceGood never produces such a good) */
} AIGOOD;
#pragma pack(pop)

#endif
