/* f3gm.c's carried-goods records (0x100 of 0xa4 bytes at 0x74e1e0) for the units that
   use them (f3gm.c, he.c, main.c defines them). */
#ifndef F3GM_CARRY_H
#define F3GM_CARRY_H
struct AIJOB;
#pragma pack(push, 1)
/* the 0xe-byte goods description a carried-goods record holds and gm_CollectCarried copies whole (ls.c saves it
   as one block of 0xe bytes) */
typedef struct GMCARRYSPEC {
  int v[3];
  short w;
} GMCARRYSPEC;

/* one of the 0x100 carried-goods records at 0x74e1e0 (0xa4 bytes; he.c counts +4 down, ls.c saves the fields
   +4 / +8 / +0xc / +0x10 / +0x14 (0xe bytes) / +0x22 (0x80 bytes) of each used one) */
typedef struct GMCARRYREC {
  union {
    struct AIJOB
        *ref;  /* 0x00, the event the goods belong to, 0: the record is free */
    int refId; /* 0x00, its AIJOB.id while saved (ls_ReadEventTables reads it, ls_FixupAfterLoad
                  turns it back into the event) */
  };
  unsigned char
      ttl; /* 0x04, counted down by he.c 0x53eea0, the record expires at 0 */
  char pad05[3];
  int hasValue;     /* 0x08, nonzero: value counts */
  int owner;        /* 0x0c, the id of the person who carries it */
  int value;        /* 0x10 */
  GMCARRYSPEC spec; /* 0x14 */
  char data[0x80];  /* 0x22 */
  char padA2[2];
} GMCARRYREC;
#pragma pack(pop)
typedef char gm_AssertGMCARRYREC[sizeof(GMCARRYREC) == 0xa4 ? 1 : -1];
#pragma pack(push, 1)
/* an entry of gm_CollectCarried's list (0x1e bytes) */
typedef struct GMCARRYENTRY {
  struct AIJOB *ref; /* 0x00, the record's event */
  GMCARRYREC *rec;   /* 0x04, the record */
  char *data;        /* 0x08, the record's data */
  int value;         /* 0x0c, the record's value when it has one */
  GMCARRYSPEC spec;  /* 0x10 */
} GMCARRYENTRY;

/* what gm_CollectCarried collects for a person (0x21d bytes; main.c's round change reads the goods and the capacity) */
typedef struct GMCARRY {
  int units; /* 0x000, the 0xe-byte units */
  struct {
    unsigned char
        good; /* a good (its name is the text 0x253 + good), 0 ends the list */
    int amount;
  } goods
      [9]; /* 0x004, what the round change lists on the balance page (main.c 0x5384e0) */
  int capacity;             /* 0x031, the free capacity (unaligned) */
  GMCARRYENTRY entries[16]; /* 0x035 */
  int valueSum; /* 0x215, minus the values of the records with one */
  int count;    /* 0x219, the entries used */
} GMCARRY;
#pragma pack(pop)
typedef char gm_AssertGMCARRY[sizeof(GMCARRY) == 0x21d ? 1 : -1];
extern GMCARRYREC
    gm_CarryRecs[0x100]; /* 0x74e1e0, the 0x100 carried-goods records */
#endif
