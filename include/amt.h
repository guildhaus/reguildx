struct AMTKIND;
struct VFSFILE;
struct AICHAR;
/* Declarations of amt.c (0x4e5cd0.., the offices; tags "amt_"). Names are ours. */
#ifndef AMT_H
#define AMT_H
#include "portable.h"                /* intptr_t: a text id or a string in one parameter */

/* copy of am.h's AI_ZERO (the headers do not compile together) */
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

#include "amt_types.h"               /* AMTREC, AMTKIND */
extern AMTREC amt_Table[42];            /* 0x925120 */
extern AMTKIND amt_Kinds[40];           /* 0x60ed58 */
extern const float amt_Pay[];                 /* 0x5edfbc */
extern float amt_Rates[];               /* 0x60ec90, 7 floats per row */
/* views of the records as amt_Rating reads them (type debt) */
typedef union AMTFLOATBITS { float f; int i; } AMTFLOATBITS;    /* a float read as its bit pattern */
#define AMT_BITS(p) (((AMTFLOATBITS *)(p))->i)
typedef struct AMTKINDF {               /* an AMTKIND's +0x14 dword read as a float */
    char pad014[0x14];
    float value;
} AMTKINDF;
int amt_FindOffice(struct AICHAR *c, struct AMTKIND *kind, struct AMTREC *office);  /* 0x4e6030 */
int amt_GetOfficeRate(struct AICHAR *c, int x, float *out);  /* 0x4e60b0 */

void amt_InitTable(void);               /* 0x4e5cd0 */
extern const float amt_TabA[];                /* 0x5edc90, 15 rows of 10 floats (id, 9 columns by the rank) */
extern const float amt_TabB[];                /* 0x5edef0, 5 rows of 10 */
float amt_Rating(struct AICHAR *a, struct AICHAR *b, int mode, int flag);  /* 0x4e5e50 */

typedef struct AMTRANGE {               /* 0x1c bytes, the ranges of 0x4e78f0 */
    short s0, s1;
    int i2, i3, i4, i5, i6, i7;
} AMTRANGE;
extern char ch_EmptyName[];             /* 0x631090 */
extern int d3_CurrentScene;                /* 0x633444 */
extern char ai_DataPath[];             /* 0x75dca0 */
#include "ai_types.h"                /* AITIME */
extern AITIME ai_Time;                   /* 0x770ae0, the game clock */
void err_Message(char *text);                     /* 0x4222b0 */
struct AIMSG; int cm_SendLongMessage(struct AIMSG *msg);                     /* 0x4c4b70 */
struct AIJOB *he_FindEvent(int n, ...);                     /* 0x53e400 */
int cm_SendSetField(int a, int b, int c, int d, int e);                     /* 0x4c4a60 */
void cm_SendMoneyDelta(int a, int b);                     /* 0x4c5f60 */
int sv_MessageBox(intptr_t text, unsigned flags); /* 0x521150, sv.c */
extern int amt_Flip;                    /* 0x60f118, 2 at the start */
#include "am_types.h"                /* G7GRP */
extern G7GRP gm_BuildingItemGroups[];            /* 0x61a348 */
#define AMT_CHARS_END (&ai_CharInts[0x300][0])  /* 0x7d5f84, the word past the last character record */
int cm_SendMoveGoodsUnchecked(int a, int b, unsigned char c, int d);  /* 0x4c4830 */
extern unsigned char ai_OwnPlayer;      /* 0x6f1bc5 */
void cm_BeginFieldBlock(void *o, int id);     /* 0x4c3ba0 */
int cm_AddFieldDelta(unsigned char size, unsigned char n, unsigned short field, void *v);  /* 0x4c3c00 */
int cm_SendFieldDeltas(void);                /* 0x4c49a0 */
int cm_SendRelations(int a, int b, int c, int d);                     /* 0x4c4b00 */
int cm_GetSlotState(int h);                     /* 0x4c3ae0 */
int amt_ApplyForOffice(struct AICHAR *c, unsigned int kind);  /* 0x4e6180 */
int amt_CheckApplication(struct AMTAPP *m);           /* 0x4e6360 */
int amt_AcceptApplication(AMTAPP *m);           /* 0x4e6430 */
int amt_SendOfficeFree(char a);              /* 0x4e65e0 */
int amt_SendOfficeCandidates(struct AICHAR *c, struct AICHAR *x);    /* 0x4e6600 */
int amt_SendOfficeOwner(char a, struct AICHAR *b, unsigned char c);  /* 0x4e6650 */
int amt_SendOfficeMessage(unsigned char a, struct AICHAR *b, struct AICHAR *c, int d, unsigned char e);  /* 0x4e6680 */
int amt_CheckOfficeMessage(struct AMTMSG *m);  /* 0x4e6710 */

int amt_ExecuteOfficeMessage(AMTMSG *p);           /* 0x4e67a0 */
void amt_SetEventOwner(int id);             /* 0x4e6b40 */
void amt_SetPersonOwner(int id);             /* 0x4e6b70 */
int amt_SendOfficeSwap(struct AICHAR *requester, struct AICHAR *b, struct AICHAR *c);  /* 0x4e6ba0 */
int amt_ExecuteSwapMessage(AMTTRADE *m);         /* 0x4e6c50 */
int amt_ClearOffices(struct AICHAR *c);             /* 0x4e6d80 */
void amt_ClearOfficesIfAll(struct AICHAR *c, int all);   /* 0x4e6e20 */
int amt_GetFirstOffice(unsigned int k, AMTREC *out);  /* 0x4e6ec0 */
int amt_KindColumn(int k);                /* 0x4e6f10 */
int amt_GetOffice(unsigned char i, AMTREC *out); /* 0x4e6f30, @original: cm.c 0x4dab50 passes its int index raw (push ebp, no zero-extension) where a caller compiled against this unsigned char parameter zero-extends; poker.c 0x4aad30 passes its unsigned char k as is */
int amt_GetKind(int k, struct AMTKIND *out);  /* 0x4e6f80 */
int amt_GetColumnOffices(int col, int max, AMTREC *out);  /* 0x4e6fc0 */

int amt_GetColumnOfficesOwned(int col, int max, struct AMTREC *out);  /* 0x4e7040 */
int amt_GetColumn7Offices(int all, int max, AMTREC *out);  /* 0x4e70f0 */
int amt_GetOfficeCandidates(struct AICHAR *c, int n, struct AMTCAND *out);   /* 0x4e7150 */
int amt_GetOfficeCandidatesFull(struct AICHAR *c, int n, AMTCAND *out, int *full);  /* 0x4e7320 */
struct AICHAR *amt_GetOfficeHolder(int k);       /* 0x4e7510 */
struct AICHAR *amt_GetSuperiorOfficeHolder(int k);             /* 0x4e7550 */
int amt_CanTakeOffice(struct AICHAR *c, int k);      /* 0x4e75c0 */
int amt_GetOfficeApplicants(int k, int n, struct AICHAR **out);  /* 0x4e76b0 */
int amt_GetEligibleOffices(struct AICHAR *c, int n, int *out);  /* 0x4e7770 */

int amt_GetOpenOffice(int k);           /* 0x4e78a0 */
int amt_GetCreateRanges(int k, AMTRANGE *r);  /* 0x4e78f0 */
int amt_CreateApplicant(int k);         /* 0x4e7aa0 */
int amt_InitApplicant(struct AICHAR *c, int k);      /* 0x4e7b60 */
int amt_GetKindLevel(int k);      /* 0x4e7c40, int not unsigned int: the original's callers use the result signed (f3init 0x50e5a0 divides it with sar, am.c 0x4a3af0 compares with jge) */
void amt_ElectOffices(int unused, int n, AMTREC *recs);  /* 0x4e7c60 */

int amt_CheckOfficeColumns(void);                /* 0x4e8160 */
int amt_IsColumnDecided(int col);       /* 0x4e83b0 */
int amt_HasDeposalVote(int col, AMTREC *r);  /* 0x4e8530 */
void amt_UpdateOffices(void);           /* 0x4e85d0 */
int amt_HasColumn7Holder(void);         /* 0x4e86e0 */
void amt_SendOfficeNews(unsigned short *p, int v);  /* 0x4e8730 */
void amt_SendOfficeLost(unsigned short *p, int v);  /* 0x4e87e0 */
void amt_ElectDeputies(void);            /* 0x4e88a0 */
void amt_ElectKind22(void);            /* 0x4e8c20 */

void amt_CalcZuenfte(unsigned int kind);  /* 0x4e8dc0 */
void amt_CheckOffices(void);               /* 0x4e9260 */
int amt_HasTownObject(int k);               /* 0x4e9400 */
int amt_MayorBonusStep(struct AICHAR *c);             /* 0x4e94a0 */
int amt_CanUseMayorPower2(struct AICHAR *c);             /* 0x4e94e0 */
int amt_CanUseMayorPower3(struct AICHAR *c);             /* 0x4e95a0 */

struct G8REQ;                                            /* am.h */
int amt_ExecutePriceMessage(struct AICHAR *c, struct G8REQ *m);     /* 0x4e9660 */
int amt_ExecuteShareMessage(struct AICHAR *c, struct G8REQ *m);    /* 0x4e9a00 */

int amt_ExecuteMayorPowerMessage(struct AICHAR *c, struct G8REQ *m);  /* 0x4e9ce0 */

void amt_ChangeDistrictOpinion(struct AICHAR *c, int d, int v);  /* 0x4ea550 */
float amt_GetDistrictLiking(struct AICHAR *c, int d);  /* 0x4ea5c0 */
int amt_SaveAemter(void *f);            /* 0x4ea690 */
int amt_LoadAemter(void *f, int version);  /* 0x4ea7a0 */
struct AICHAR;
void amt_TellOpenOffices(struct AICHAR *c);            /* 0x4ea8e0 */
void amt_AnnounceOfficeFree(unsigned int k);     /* 0x4eaa00 */

int amt_GetOwnedOfficePay(void);        /* 0x4ea990 */

#endif
