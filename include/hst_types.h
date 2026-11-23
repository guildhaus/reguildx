/* The list record of hst's table hst_Lists, for the units that declare the table without the rest of hst.h
   (hst.h includes am.h): types only. hst.h includes it. */
#ifndef HST_TYPES_H
#define HST_TYPES_H

typedef struct
    G12ROW { /* 0x44 bytes, hst_Lists[4] (one list of text entries) */
  int inUse; /* 0x00, 1 while the list holds entries (0x4b1ee0 clears it, a [_SET_ / [_USE_ command needs it) */
  struct {
    int id; /* a character id (net id) */
    int token; /* the replacement token (hst_TokenNames index) the slot took with "_NEWn" */
  } e[8]; /* 0x04, the slots; the text commands and replacement tokens take the row and
             a slot index (hst_ParseContext tests and clears inUse as the valid flag) */
} G12ROW;

#endif
