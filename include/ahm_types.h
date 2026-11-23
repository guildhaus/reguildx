/* The alchemist record of ahm.c and its places, and the alchemist messages 99 / 100 (G17MSG.ahmCreate / ahmOrder), for
   the units that read them without the rest of ahm.h: types only.
   ahm.h includes it. */
#ifndef AHM_TYPES_H
#define AHM_TYPES_H
#pragma pack(push, 8)                   /* natural layout wherever it is included (cm_types.h is read under pack(1)) */

typedef struct AHMSLOT {                /* 8 bytes, a place of the record at +0x65 of the object (6 from +0xc): a good and its value */
    int id;
    float v;
} AHMSLOT;

typedef struct AHMREC {                 /* 0x3c bytes, the record the alchemist object keeps at +0x65 ("ahm_AllocAhmInfo") */
    int id;                             /* +0x0, the alchemist character id (0x4eaa50) */
    float value;                        /* +0x4, 0 .. 1, added to by an order (0x4ecdb0) */
    unsigned char share[4];             /* +0x8, 0 .. 252, the four shares / 252 (0x4eab20) */
    AHMSLOT slots[6];                   /* +0xc, the places */
} AHMREC;

#pragma pack(push, 1)
typedef struct AHMORDER {               /* 0x18 bytes, the data of a type 100 message (cm.c's 0x4cd010): one of the commands below */
    int tag;                            /* +0x0, the four-letter command */
    int charId;                         /* +0x4, the id of the character it is for */
    int id;                             /* +0x8, the recipe / place id it is about */
    int unk0c;                          /* +0xc, not used */
    union { float f; int i; } value;    /* +0x10, the value ('SmSa': the bits of a float) */
    int nextObjectId;                   /* +0x14, the object id the receiver continues counting from (ahm_AddPlace 0x4ecb30 gives it to ai_NextObjectId in a network game); the senders here leave it 0 */
} AHMORDER;
#pragma pack(pop)

typedef union AHMGRID {                 /* 12 bytes, an entry of the shuffled tables 0x6f0e2c (players) / 0x6f0e34 (recipes) */
    int w[3];                           /* the three words (ahm_FillSteps copies them into a walk step) */
    struct {                            /* the player prototype (0x6f0e2c) */
        unsigned char attr[5];          /* +0x0, ATTR0 .. ATTR3 (0 .. 252) and ATTR4 (18 .. 30) */
        char pad05[3];
        int id;                         /* +0x8, ATTR5: the object id */
    } plr;
    struct {                            /* the recipe prototype (0x6f0e34) */
        int id;                         /* +0x0, RCPID: the object id */
        float a, b;                     /* +0x4 / +0x8, ATTR0 / ATTR1, 0 .. 1 */
    } rcp;
} AHMGRID;
typedef struct AHMCREATEMSG {           /* 0x24 bytes, the data of the type 99 message (0x4c6170; the handler 0x4ccf90 calls ahm_CreateAlchemist) */
    int seed;                           /* +0x0, the generator seed; the handler 0x4ccf90 writes its own rand() when 0x1460ae0 is -1, unwritten here */
    int charId;                         /* +0x4, the character id the handler 0x4ccf90 syncs ai_NextObjectId from, unwritten here */
    int building;                       /* +0x8, the id of the alchemist building (AIBLD.id) */
    AHMGRID proto;                      /* +0xc, the step's prototype entry (the player view: its attributes and its place id) */
    int x, y;                           /* +0x18 / +0x1c, the name indexes of the creation (0x144a7a8 / 0x144a80c) */
    float value;                        /* +0x20, the +8 of the recipe entry of the prototype's id (AHMGRID.rcp.b), the value of the first place */
} AHMCREATEMSG;

#pragma pack(pop)
#endif
