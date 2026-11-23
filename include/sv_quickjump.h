/* The info panel's quick jump record (sv_QuickJump, sv.h declares it). Its body is in its own header, included
   only by the units that read its fields (sv.c, lc.c, lcamt.c, lcdom.c, lcmap.c, and for panelFlag cmscene.c,
   f3init.c, main.c, svcannon.c, svtip.c, sv_t.c, which read it through sv.h's `sv_PanelFlag` view before). */
#ifndef SV_QUICKJUMP_H
#define SV_QUICKJUMP_H

struct
    SVQUICKJUMP { /* 0x60 bytes at 0x75e8c0, sv_QuickJump: the info panel's flag and pending quick jump
                     (sv_HandleObjects: "QuickJump.ContactName"). One object: sv_SelectPanelObject's
                     inline strcpy into contactName makes the original reload record (VC6 forgets what it
                     knew of the object the bytes are stored into); the 0x5c bytes from object on sit at
                     0x75e8c4, off the 32-byte alignment of a common that size: the object starts with
                     the panel flag (panelFlag) */
  int panelFlag;  /* 0x00, 1 while the info panel is up */
  struct AIBLD *
      object; /* 0x04, the building the info panel shows (sv_SelectPanelObject) */
  struct AIOBJ *
      record; /* 0x08, its room object (gm_Query; its type is the scene record) */
  int unk0c; /* 0x0c, no access found */
  int unk10; /* 0x10, no access found */
  char contactName
      [76]; /* 0x14, the panel text: the contact name a quick jump looks up */
};

#endif
