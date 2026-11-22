/* Declarations of ls.c, the save game unit from 0x519010 (load / save, the network game transfer):
   its functions and data as the definitions spell them. Names are ours except the ls_* ones the
   strings leak. */
#ifndef LS_H
#define LS_H
struct VFSFILE;

#include "ls_types.h"                     /* NETHDR, LSSAVE */

struct CHACTION;

int ls_LanguageOf(char *s);                                             /* 0x519010 */
int ls_GetLanguage(void);                                               /* 0x5190a0 */
int ls_SaveGame(char *name, char *path, unsigned flags);                  /* 0x5190b0 */
int ls_WriteSaveHeader(struct VFSFILE *f, unsigned flags);                          /* 0x5194c0 */
void ls_RefsToIds(void);                                               /* 0x519a00 */
void ls_IdsToRefs(void);                                               /* 0x519aa0 */
int ls_RelinkScene(struct VFSFILE *f);                                               /* 0x519b50 */
int ls_WriteObjects(struct VFSFILE *f);                                             /* 0x519bf0 */
int ls_WriteBuildings(struct VFSFILE *f);                                               /* 0x519d20 */
int ls_WritePlayerRecords(struct VFSFILE *f);                                               /* 0x51a1a0 */
int ls_WriteCharacters(struct VFSFILE *f);                                               /* 0x51a4b0 */
unsigned ls_ActionIndex(struct CHACTION *p);                            /* 0x51ad30 */
struct CHACTION *ls_ActionAt(int n);                                    /* 0x51ad60 */
int ls_WriteSceneCharacter(struct CHARACTER *c, int owner, struct VFSFILE *f);  /* 0x51ad80, writes one scene character record */
int ls_WriteSceneRecords(struct VFSFILE *f);                                               /* 0x51aff0 */
int ls_WritePlayerSlots(struct VFSFILE *f);                                               /* 0x51b340 */
int ls_WriteRelations(struct VFSFILE *f);                                           /* 0x51b890 */
int ls_WriteStatistics(struct VFSFILE *f);                                               /* 0x51b910 */
int ls_WriteAvatars(void *f);                                           /* 0x51bdb0 */
int ls_WriteEventTables(struct VFSFILE *f);                                               /* 0x51bdc0 */
int ls_WriteParties(struct VFSFILE *f);                                               /* 0x51c2f0 */
int ls_WriteHistory(struct VFSFILE *f);                                             /* 0x51c450 */
int ls_WriteMessageQueues(struct VFSFILE *f);                                               /* 0x51c560 */
int ls_WriteEnvironment(struct VFSFILE *f);                                               /* 0x51c870 */
int ls_Read(void *buf, int size, int count, struct VFSFILE *f);                     /* 0x51c920 */
int ls_LoadGame(char *name, int kind);                                  /* 0x51c950, kind is not read (main passes 1 / 2, f3init 5) */
int ls_ReadSaveHeader(struct VFSFILE *f, LSHDR *h);                                   /* 0x51cee0 */
int ls_LoadScene(struct VFSFILE *f);                                               /* 0x51d2d0 */
int ls_ReadObjects(struct VFSFILE *f);                                              /* 0x51d3d0 */
char ls_HookBuildingCB(struct D3OBJECT *o);                                  /* 0x51d4f0 */
char ls_ClearObjectFlag(struct D3OBJECT *o);                                       /* 0x51d530 */
int ls_ReadBuildings(struct VFSFILE *f);                                            /* 0x51d550 */
int ls_ReadPlayerRecords(struct VFSFILE *f);                                        /* 0x51db00 */
int ls_ReadCharacters(struct VFSFILE *f);                                           /* 0x51de70 */
struct CHARACTER *ls_ReadCharacter(struct VFSFILE *f);                                         /* 0x51e750 */
int ls_ReadSceneRecords(struct VFSFILE *f);                                               /* 0x51e900 */
int ls_ReadPlayerSlots(struct VFSFILE *f);                                               /* 0x51f080 */
int ls_ReadRelations(struct VFSFILE *f);                                            /* 0x51f650 */
int ls_ReadStatistics(struct VFSFILE *f);                                               /* 0x51f720 */
int ls_ReadAvatars(void *f);                                            /* 0x51fb80 */
int ls_ReadEventTables(struct VFSFILE *f);                                               /* 0x51fb90 */
int ls_ReadParties(struct VFSFILE *f);                                               /* 0x520000 */
int ls_ReadHistory(struct VFSFILE *f);                                               /* 0x520200 */
int ls_ReadMessageQueues(struct VFSFILE *f);                                               /* 0x520310 */
int ls_ReadEnvironment(struct VFSFILE *f);                                               /* 0x5205f0 */
int ls_FixupAfterLoad(void);                                            /* 0x5206b0 */
int ls_SendGame(char *name);                                            /* 0x520a30 */
int ls_ReceiveGame(void);                                               /* 0x520b80 */

#ifndef DATA_VIEWS_H
#endif
extern LSSAVE ls_SavePath;                                  /* 0x75e640 */
extern unsigned short ai_ScreenImage[19200];                /* 0x766320 */
extern LSHDR ls_LoadedHeader;                            /* 0x76f920, the header of the loaded save game (ls_LoadGame) */
extern int ai_NextPartyId;                                    /* 0x61a658 */
extern int ls_Language;                                     /* 0x62364c */
extern int ls_Version;                                      /* 0x623650 */
extern const char ls_LanguageNames[][0x40];                 /* 0x5ee978 */
extern void *d3_Terrain;                                    /* 0x633738, d3_fl.c: the current terrain map */
extern int ai_NextCrimeId;                                    /* 0x6f1b88 */
extern int ls_SpareInt;                                    /* 0x6f1bcc */
extern unsigned char ls_SaveSlot;                           /* 0x6f1c38 */
extern int ai_NextEventId;                                    /* 0x6f2618 */
extern int he_EventTop;                                      /* 0x6f261c, the highest used index of he_Events */
extern int he_QuickTop;                                    /* 0x6f2620 */
extern int he_EventCount;                                    /* 0x7585e4 */
#ifndef DATA_VIEWS_H
#endif
extern unsigned cm_LoadSize;                               /* 0xa68d28 */
extern int cm_LastSeq;                                    /* 0xf81168 */
extern unsigned cm_LoadReceived;                               /* 0xf81220 */

#endif
