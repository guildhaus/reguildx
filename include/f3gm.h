/* Declarations of f3gm.c (0x4f9e30 .. 0x50d0b0): the game data part (clock, building / object tables and
   queries, character helpers, prices). The unit still declares most of its own functions in the .c; these are
   the ones other units call. Names are ours. */
#ifndef F3GM_H
#define F3GM_H

#include "f3gm_types.h"

struct AIBLD; struct AICHAR;

struct AIBLD *gm_BuildNext(void);              /* 0x501030, the next building of the query */
struct AIBLD *gm_BuildQuery(int n, ...);       /* 0x501190, n (kind, value) filters; 6 takes no value */
struct AIOBJ *gm_BuildingMainObject(struct AIBLD *bld);  /* 0x501b50, the main object of the building by its class (an AIOBJ, ai.c +0x2 objId) */
struct AICHAR *gm_FindChar(int id);                     /* 0x505df0, the character with the id, 0 when none */
int gm_FindById(struct AIBLD **bld, struct AIOBJ **obj, struct AICHAR **chr, int id);  /* 0x4fea50, what has the id: 1 building, 2 object, 3 character */
int gm_FindObjectProto(char *name);             /* 0x4fe900, the number of the object prototype with the given name (case-insensitive), 0 when none */
struct AIOBJ *gm_FindObjectInst(int id);                  /* 0x4fe980, the object instance with the id (int +2) */
struct AIBLD *gm_FindBuildingById(int id);              /* 0x502020, the building with the id (+1) */
void gm_ResetStock(void);                       /* 0x50cc60, the stock of the type 0x1e buildings' stalls to 2 */
int gm_TitleNumber(int group, int rank);        /* 0x5043d0, the title number of the rank in the group */
int gm_TitleGroup(int n);                       /* 0x504ad0, the title group of the title n */
int gm_TitleJobGroup(int n);                    /* 0x504c00, the job group of a job-pair number n */
int gm_TitleJob(int i, int p);       /* 0x5044b0, the job byte of the character i in the title group p, 0 when none */
int gm_IsType10(struct AIBLD *b);              /* 0x5024f0, 1 for the town market */
int gm_IsHomeType(struct AIBLD *b);            /* 0x502520, 1 for a home type */
struct AICHAR *gm_FindCharacterByMaster(struct AIBLD *m);          /* 0x50a810, the first kind 6 / 7 / 1 / 2 character with a job whose master (+0x16c) is m */
void gm_ShowSlotObjects(struct AIBLD *unused, struct AIOBJ *scene, int c);  /* 0x502a60, the scene objects of the character's five slots on */
void gm_ShowBuildingObjects(struct AIBLD *b);  /* 0x502e30, for a building of the type 2: gm_ShowSlotObjects for every object of the kind 2 in its list (up to 32) */
void gm_AssignBuilding(struct AIBLD *b, unsigned master, unsigned own);  /* 0x502b60 */

void gm_ClearBuildings(void);                   /* 0x4fe7f0, clears the 0x100 records of ai_Blds */
float gm_Mix2(float u, float v);                /* 0x504e80 */
void gm_ClearObjects(void);                     /* 0x4fe830, returns the instances of live owners and clears the 0x5008-record table */

int gm_LoadTables(char *root);                                       /* 0x4fe570 */
void unk_LoadIconNames(void);                                         /* 0x4fde90 */
void gm_ResetCharacters(void);                                        /* 0x503e80 */
void gm_FreeIconNames(void);                                          /* 0x4fdfb0 */
void gm_Free(void);                                                   /* 0x4fe9c0 */
int gm_TitlesLeft(int n);                                             /* 0x504ce0 */
int gm_CollectCarried(int id, int *out);                                   /* 0x50af00 */
int gm_IsBankrupt(struct AICHAR *p, int n);                                  /* 0x50a6c0, p: an AICHAR */

/* declared in other units' headers before (moved to the owner) */
struct AICHAR; int gm_CatchDisease(struct AICHAR *c, int *kind, float *health);  /* 0x505230, the character catches a disease: *kind its kind, *health the new health (either may be 0); 1 when it caught one */
struct AICHAR; int gm_CatchUpperDisease(struct AICHAR *c);  /* 0x5056a0, the character catches one of the upper diseases 5 .. 8; the kind or 0 */
struct AICHAR; int gm_CureDisease(struct AICHAR *c);  /* 0x505840, cures one disease of the character; the kind or 0 */
struct AICHAR; int gm_CureMinorDisease(struct AICHAR *c);  /* 0x5059d0, cures one of the minor diseases 2 .. 5 of the character; the kind or 0 */
struct AICHAR; int gm_CureUpperDisease(struct AICHAR *c);  /* 0x505ad0, cures one of the diseases 6, 7, 8, 3 of the character; the kind or 0 */
int gm_CurseTargetCount(struct AIBLD *b);  /* 0x50d0b0 */
int gm_Season(char *d);  /* 0x4fe330 */
struct AICHAR; int gm_CatchMinorDisease(struct AICHAR *c);  /* 0x5054f0, the character catches one of the minor diseases 2 .. 5; the kind or 0 */
int gm_HeadIconNumber(char *name);  /* 0x4fb770 */
int gm_FindRichest(short *id, int *rate);  /* 0x4fad60 */
void gm_Shuffle(unsigned n, int *out);  /* 0x505d30 */
int gm_SexForJob(int x);  /* 0x503f30 */
extern GMPLAYERSLOT ai_PlayerSlots[4];        /* 0x7e3f40, the player slots (the town each player plays in) */
extern GMBLOCK gm_StockBlocks[];             /* 0x7d6a60, the five stock blocks (one per player slot) */
extern unsigned short gm_KindObjCount;  /* 0x76fdc4 */
extern unsigned gm_KindObjs[732];  /* 0x889400 */
int gm_BuildKindObjects(struct AIBLD *b);  /* 0x500b90 */
int gm_BathObjectCount(struct AIBLD *b);  /* 0x50cf60 */
int gm_CurseObjectCount(struct AIBLD *b);  /* 0x50cfd0 */
struct AIBLD *gm_ObjectBuilding(struct AIOBJ *o);  /* 0x50a0f0 */
int gm_TakeableCount(struct AICHAR *c, int proto, int n);  /* 0x50ad70 */
float gm_HealthFactor(int c);  /* 0x508a20 */
int gm_FreeStallCapacity(struct AIOBJ *l, int id, int n);  /* 0x50acf0, how many of the goods the stall object l can still take, at most n */
void gm_ChangeBuildingState(struct AIBLD *b, int d);  /* 0x50cad0 */
int gm_ListWorkers(struct AIBLD *b, int *out);  /* 0x502eb0, the worker lists of the building b (out[1 ..], out[0x19 ..]); returns their number */
int gm_TitleNumberGroup(int n);  /* 0x504350, the group of the title number n */
int gm_HasBuilding(int p);  /* 0x5049c0 */
void gm_EndDayIncomes(unsigned flags);  /* 0x4fabe0, the end of the day for the income histories */
void gm_DailyCharacters(void);  /* 0x4fc920, the daily step of all characters */
void gm_UpdatePlayers(void);  /* 0x4feb30 */
void gm_CharacterUpkeep(void);  /* 0x4fa580, the daily upkeep of the characters */
void gm_PayAllCharacterWages(void);  /* 0x4fa9b0 */
void gm_UpdateWorthMood(void);  /* 0x4faa00 */
float gm_JobWage(struct AICHAR *c, int k, int a, int b);  /* 0x508740, the wage of a job (a) or title (b) of the building kind k for the character c */
int gm_BuildingBalance(struct AIBLD *b, unsigned id, int *out);  /* 0x508d80, the income / cost summary of the building b for the owner id */
struct GMHEAD *gm_NameRecord(int kind, int id);  /* 0x4fb330, the name record (0x44 bytes, the name at +4) with the id in the table of the sex kind (0 / 1), or the first free one */
struct GMHEAD *gm_CharNameRecord(int id);  /* 0x4fb390 */
struct CHARACTER *gm_CreateCharModel(struct AICHAR *c, int scene, struct D3VECTOR *p, struct D3VECTOR *ori, struct D3OBJECT *obj, char *dummy);  /* 0x4fbb80 */
float gm_HealthRatio(struct AICHAR *c);  /* 0x4fc8e0 */
struct AIBLD; struct AIBLD *gm_FindHome(int unused, struct AIBLD *o);  /* 0x4fd820, a home with room for the building o (the nearest or least full) */
void gm_MoveIntoHome(struct AICHAR *c, struct AIBLD *b);  /* 0x4fda10 */
int gm_AddToTreasury(int a);  /* 0x50c4e0, gives the amount a to the town treasury */
struct AICHAR; struct AIBLD; struct AICHAR *gm_FindApplicant(struct AIBLD *o, unsigned title, unsigned job);  /* 0x4fda70 */
struct AIOBJ *gm_HomeObject(struct AIBLD *b);  /* 0x4fdc10 */
short *gm_SpawnCharacter(unsigned char flags, int p2, int p3, unsigned char p4, unsigned char p5, struct AIBLD *p6);  /* 0x4fddb0 */
void gm_CountCharacters(void);  /* 0x4fdfd0 */
unsigned short *gm_AllocRaum(struct AIBLD *b, unsigned n);  /* 0x5031b0 */
int gm_BuildingGoodsList17(struct AIBLD *b, struct AIRECIPE *out, int kind);  /* 0x5099e0 */
extern GMCHARSTATS gm_CharacterStatistics;  /* 0x91b500 */
int gm_CharacterWages(unsigned short id, int flag, unsigned char *out);  /* 0x4fa700 */
int gm_TakeObjekt(int id, int proto, int n);  /* 0x500a40 */
unsigned short *gm_CreateObject(int id, int proto, int n);  /* 0x500190, the new object instance of the prototype proto with the amount n in the holder's list (gm_FindById); 0 on failure */
void gm_FreeObject(struct AIOBJ *obj);  /* 0x5034b0 */
int gm_SkillPoints(struct AICHAR *c, int skill);  /* 0x504e00 */
int gm_HasAdultRelative(struct AICHAR *c, int *n);  /* 0x506480 */
unsigned gm_TakeOverCharacter(int a, int b);  /* 0x5064d0 */
struct AICHAR; void gm_InheritEstate(struct AICHAR *dead, struct AICHAR *heir);  /* 0x506890, the heir inherits the dead character's estate */
struct AICHAR; void gm_ForfeitEstate(struct AICHAR *c, char *out, int flag);  /* 0x506e70, the character c forfeits its estate after a lost fight; the announcement into out */
struct AIBLD; unsigned short gm_CreateCharacter(int type, int a2, int a3, unsigned short a4, struct AIBLD *a5, unsigned a6, int a7, int a8);  /* 0x507690 */
struct AICHAR *gm_ObjectBuildingOwner(struct AIOBJ *o);  /* 0x50a050 */
int gm_ListObjectsAfter(struct AIBLD *b, struct AIOBJ *proto, int *out);  /* 0x508cc0, counts (and with out lists) the objects b lists after proto */
int gm_RemoveOwned(struct AIOBJ **list, int id);  /* 0x5000c0 */
void gm_SelectModelVariant(struct AICHAR *o);  /* 0x4fb5a0 */
void gm_SetJob(int i, unsigned n);  /* 0x504790 */
void gm_ShuffledBytes(unsigned char n, unsigned char *out);  /* 0x505be0 */
int gm_FreeBuilding(struct AIBLD *b);  /* 0x5012e0 */
int gm_RemoveObjectFromBuilding(struct AIBLD *b, int id);  /* 0x503480 */
unsigned char *gm_CreateBuilding(unsigned char k, unsigned short own);  /* 0x501580 */
void gm_StockBuildingObjects(struct AIBLD *p);  /* 0x501400, stocks a new building p with the objects its building kind needs */
void gm_SetCapacities(struct AIBLD *p);  /* 0x5014b0, sets the capacities of the objects of building p from its kind record */
extern int gm_AllowAll;  /* 0x6f2448 */
float gm_AddHealth(unsigned short id, int d);  /* 0x4fca40 */
int gm_AddNegative(int id, int proto, int n);  /* 0x500ae0 */
float gm_CharacterHealth(struct AICHAR *c);  /* 0x4fc820 */
float gm_GoodsValue(int p, unsigned id);  /* 0x4ffbf0 */
void gm_Shuffled(unsigned char n, int *out);  /* 0x505ca0 */
int gm_BuildingKindCost(struct AICHAR *c, int kind);  /* 0x509dc0 */
int gm_SumListAmounts(void *list, unsigned char p);  /* 0x509e30 */
int gm_CharCurrency(struct AICHAR *c, signed char p);  /* 0x509ee0 */
struct AICHAR *gm_ObjectOwnerChar(struct AIOBJ *o);  /* 0x509ff0 */
struct ORDCREDIT; int gm_GetCreditOffers(struct AIBLD *b, struct AICHAR *p, unsigned cnt, struct ORDCREDIT *out);  /* 0x50a250 */
int gm_ExpectedDeathAge(struct AICHAR *c);  /* 0x4fc7a0 */
int gm_MayTakeJob(int k, int c);  /* 0x5020e0 */
void gm_SellBuilding(int a, int b, int c, struct AIJOB *d, int e);  /* 0x502fd0 */
struct AIOBJ *gm_PlayerSeat(int p);  /* 0x504a80 */
void gm_SendMoneyDelta(int a, int b);  /* 0x50cc50 */
int gm_JobBuildingType(int x);  /* 0x504050 */
float gm_MapDistance(int a, int b, int c, int d);  /* 0x4ffc90 */
float gm_Mix(struct AICHAR *a, struct AICHAR *b, int c);  /* 0x504e20 */
int gm_PlayerFactor(int a, unsigned char k);  /* 0x5085f0 */
struct AIBLD *gm_FirstBuilding(int n);  /* 0x50b010 */
int gm_FirstTitleNumber(int x);  /* 0x504290 */
float gm_GetSkill(struct AICHAR *c, int skill);  /* 0x504ec0 */
int gm_GetWorth(unsigned short id);  /* 0x50a640 */
int gm_BuildingKindValue(int kind);  /* 0x509d30 */
int gm_ConvertMoney(int a, unsigned char k);  /* 0x5085b0 */
int gm_BuildingJob(int t);  /* 0x5048e0 */
int gm_StallGoodsList(struct AIOBJ *c, struct AIRECIPE *out);  /* 0x50aa00 */
int gm_SumSlotAmounts(void *list, unsigned char p);  /* 0x508660 */
int gm_CharLevel(unsigned short id, int again);  /* 0x505e60, the level of the character id (its job's kind level + 1, raised to the parent's) */
int gm_CharPrevLevel(unsigned short id, int again);  /* 0x505f30, gm_CharLevel for the previous office (+0x167) */
struct AICHAR; struct GMDATE; void gm_BirthDate(struct AICHAR *c, struct GMDATE *out);  /* 0x506000, the birthday of the character c (its birth year, a month and day from its first name) */
struct AICHAR; struct GMDATE; int gm_DeathDate(struct AICHAR *c, struct GMDATE *out);  /* 0x5060d0, the day of death of the character c; 0 for a living one */
struct GMRANK; void gm_RankPlayers(int *count, struct GMRANK *out);  /* 0x506180, the ranking of the up to 8 players into out, *count of them */
float gm_JobCost(struct AICHAR *c, int k, int a, int b);  /* 0x50cd40 */
struct AIOBJ *gm_QueryNext(void);  /* 0x4ffcc0 */
int gm_OwnerWorth(struct AIBLD *b, int flag);  /* 0x509c80 */
struct AIFIN *gm_PlayerRecord(struct AICHAR *c);  /* 0x506430 */
int gm_Opinion(int a, int b);  /* 0x50c520 */
extern int gm_NOffers;  /* 0x7e3f3c */
float gm_ObjectValue(int n);  /* 0x5086b0 */
int gm_ListStock(struct AIOBJ *l, int id);  /* 0x50ab50 */
int gm_ListAmountById(struct AIOBJ *l, int id);  /* 0x50ab20 */
int gm_BuildingClass(int kind);  /* 0x501d80 */
int gm_BuildingGoodsList(struct AIBLD *b, struct AIRECIPE *out, int kind);  /* 0x5098a0 */
int gm_BuildingLevel(struct AIBLD *b);  /* 0x508d70 */
int gm_BuildingRank(struct AIBLD *b);  /* 0x5090b0 */
int gm_BuildingSkill(struct AIBLD *b, unsigned k, int flag);  /* 0x5092e0 */
int gm_BuildingKindSkill(int kind, unsigned k);  /* 0x5093a0, the level the building kind reaches in skill k (gm_BuildingSkill without the instance) */
float gm_StockPrice(int p, int n);  /* 0x4ffa10, the price of the goods n of the player p */
float gm_CharAge(unsigned short id);  /* 0x505e30, the age (+0x0a) of the character id */
float gm_StaffFactor(struct AIBLD *b, int n, int *ids);  /* 0x50cdc0, the staff factor of the building b with the persons ids[0 .. n - 1] */
int gm_CollectOffers(int goods);  /* 0x500c20 */
int gm_EquipmentValue(struct AIBLD *b, int level);  /* 0x509b10 */
struct GMSTOCK *gm_FindGoods(int p, unsigned id);  /* 0x4ffc40 */
struct AIOBJ *gm_FindMarketObject(int id);  /* 0x500ec0 */
int gm_FreeCapacity(struct AIOBJ *l, int id, int n);  /* 0x50ab80 */
struct AIOBJ *gm_GetGebaeudeHauptraum(struct AIBLD *b);  /* 0x501ce0 */
int gm_GetGoodsValue(struct AICHAR *c);  /* 0x509e60 */
float gm_GoodsPrice(unsigned id, unsigned char p);  /* 0x5089c0 */
float gm_ItemPrice(int item, unsigned char n);  /* 0x5087f0 */
float gm_Liking(unsigned a, unsigned b, int c);  /* 0x50c550 */
int gm_ListAmount(struct AIOBJ *l, struct AIOBJ *o);  /* 0x50aaf0 */
extern struct AIOBJ *ai_Objects;  /* 0x7e3f34 */
extern int ai_GameFlags;  /* 0x6f23f8 */
extern struct AIGOOD *ai_Goods;  /* 0x91aaf0 */
int gm_RemoveObject(struct AIOBJ **list, unsigned id);  /* 0x4ffff0 */
void gm_KillSpieler(int c, int mode);  /* 0x503c60 */
extern struct AIBLD *ai_Blds;  /* 0x889f74 */
extern int ai_Difficulty;  /* 0x6f23fc */
extern int ai_CharCount;  /* 0x6f1bc0 */
extern int ai_NextObjectId;  /* 0x61a654 */
int gm_AddObjekt(int id, int proto, int n);  /* 0x500970 */
void gm_ChooseHeadIcon(struct AICHAR *c);  /* 0x4fb890 */
struct CHARACTER *gm_PlaceOnStage(int id, int a, int b, struct D3VECTOR *p, struct D3VECTOR *ori);  /* 0x4fbd10 */
struct AIOBJ *gm_Query(void *list, int n, ...);  /* 0x4ffe90 */
void gm_RefreshGoodsLists(unsigned p);  /* 0x4ff190 */
JOBTALENTS gm_GetJobTalents(int job);  /* 0x503ee0, the record of the job (0x5f and above: the first) */
struct AITIME; void gm_AddTime(struct AITIME *c, int hours, int mins, int secs);  /* 0x4fe140 */
struct AITIME; int gm_CompareTime(struct AITIME *a, struct AITIME *b);  /* 0x4fe210 */
struct AITIME; int gm_MinutesBetween(struct AITIME *a, struct AITIME *b);  /* 0x4fe280, the minutes from clock a to clock b */
struct AITIME; int gm_ClockSeason(struct AITIME *c);  /* 0x4fe350 */
struct AITIME; void gm_AddTime2(struct AITIME *c, int unused, int hours, int mins, int secs);  /* 0x4fe310 */
struct AITIME; int gm_WorkMinutesBetween(struct AITIME *a, struct AITIME *b, struct AIBLD *bld);  /* 0x509400 */
struct AITIME; int gm_FixedWorkMinutesBetween(struct AITIME *a, struct AITIME *b);  /* 0x5096a0 */
int gm_BuildingValues(struct AIBLD *b, int *out);  /* 0x5091a0 */
struct AICHAR; float gm_CatchPlague(struct AICHAR *c);  /* 0x505440 */
void gm_ChangeObjektZustand(int id, int d);  /* 0x50ca50 */
float gm_CharacterBaseHealth(struct AICHAR *c);  /* 0x4fc890 */
struct AIBLD *gm_CharacterHome(struct AICHAR *c, int *out2, int *out3);  /* 0x4fdcb0 */
struct AICHAR; int gm_DropRank(struct AICHAR *c);  /* 0x504840 */
struct AIBLD *gm_FindPlayerBuilding(int p);  /* 0x501000 */
struct GMDISEASE; int gm_GetDisease(int n, struct GMDISEASE *out);  /* 0x5051d0 */
struct AIBLD; int gm_HandOutMoney(struct AIBLD *b, int *out);  /* 0x4fae50 */
int gm_JobSlots(int job, int *a, int *b);  /* 0x504100 */
int gm_LikingChance(int a, int b, int c, int d);  /* 0x50b290 */
struct AICHAR; int gm_MayRemoveChar(struct AICHAR *c);  /* 0x5075c0 */
int gm_TrialBuildingKind(struct AIBLD *b);  /* 0x50d060 */
void gm_StatisticsScreen(void);  /* 0x4f9e30, the city statistics screen */
struct AITIME; void gm_ClockToDate(struct AITIME *c, unsigned char *out);  /* 0x4fe2c0, the calendar record of a clock */
char *gm_ClassTreasury(struct AIBLD *b);  /* 0x5049e0, the treasury text of a building */
int gm_CurrencyFactor(int a, int i);  /* 0x508620 */
int gm_CurrencyDivide(int a, int i);  /* 0x508640 */
int gm_BuildingCarts(struct AIBLD *b, struct AIOBJ **out);  /* 0x509060 */
int gm_BuildingRankGate(struct AIBLD *b, struct AIBLD *c);  /* 0x509120 */
int gm_CharMoney(int c);  /* 0x509f20 */
int gm_GoodPicture(struct AIOBJ *o);  /* 0x502570, the string-table number (0x60e + n) of the good's picture, -1 when none */
int gm_ResearchClass(int k, int *out);  /* 0x50b090 */
int gm_DonationRank(int c, int d);  /* 0x50b170 */
struct HELOAN; int gm_CreditEvents(int c, struct AIBLD *bld, struct HELOAN **out);  /* 0x50a150 */
int gm_BuildingEvents(unsigned owner, struct AIBLD *b, int c, struct HELOAN **out);  /* 0x50a1c0 */
void gm_UpdateTechTree(struct AIBLD *bld, struct AIOBJ *item);  /* 0x50b9f0 */
int gm_TechTreeWindow(char *form, struct AIBLD *bld, struct AIOBJ *item);  /* 0x50c340 */
int gm_Homeless(struct AICHAR *c);  /* 0x50ccd0 */

#endif
