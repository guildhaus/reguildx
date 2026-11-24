/* cmfight.c -- the fight of a raid / brawl scene (0x4cd9d0..0x4d8b50): weapons and their records, bombs and
   grenades, the portraits and character info windows, the orders and the fight AI, the actions (hit, bombs, death),
   the loot and the fight dialogs, the fight loop. Split from cm (data layout s12): its own .data block
   ai_WeaponRecords 0x60c7c0 .. cm_FightButton 0x60cb68 after cm's last string ("%s %s" of cm_LobbyAddChat), then its
   string run (first user ai_FindWeaponRecord); its .bss 0x6f0ce0..0x6f0d68; its common group 0x930380..0x935da0
   (cm_PointList .. cm_CharInfoWins, read only by these functions) between the scene's group and cm's. The sync
   values sent by address are block locals (cm_AddFieldValues in cm stays unknown here; byte both ways).
   Open: summary: the leaf ai_LedSelectBits counts as writing ai_PickedObject in the original (cm_UpdatePointer
   reloads it after each call), which its text does not give; it holds a dead `if (0) ai_PickedObject = 0;` with
   an @original comment (cm_UpdatePointer 142 -> 36 ins and its padded size, size queue s19); the original's own
   form of that write is not known (an external copy gave only 49, a write of another global nothing). The other
   such case, cm_RunCutOrders reloading x->scene->obj after cm_CharObjDistXZ, was a unit boundary: cmorders.
   unit 0x004cd9d0..0x004d76a0; boundaries in decl/text.dcl */
#include "d2_types.h"
#include "txt_views.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <d3d.h>
#include "net.h"
#include "cm.h"
#include "cmfight.h"
#include "d2.h"
#include "d3.h"
struct D3SKYLAYER;
struct D3SKY;
struct D3SKYLAYER *d3sky_CreateLayer(struct D3SKY *s, int first, char *tex,
                                     D3TEXFLAGS flags, float scale,
                                     float offset, float vscale,
                                     float voffset); /* 0x45d880 */
#include "d3_tools.h"
#include "d3_quad.h"
#include "d3_light.h"
#include "di_input.h"
#include "evt.h"
#include "data_views.h"
#include "menu_types.h"
#define GAPDATA __declspec(align(1)) unsigned char

/* full rebuild: the symbols whose original addresses the code above spells literally */
extern GAPDATA full_data_602568[];

/* the block at 0x936420 is 0x24 bytes: the count then the eight player states at +4 (one object, so the
   0x24-byte memset / memcpy in 0x4cd580 and 0x4cdxx cannot run over a neighbour that LINK placed there) */

#include "f3init.h"
#include "sv.h"
#include "ahm.h"
#include "ai.h"
#include "ch.h"
#include "d3_anim.h"
#include "d3_engine.h"
#include "d3_fl.h"
#include "d3_int_io.h"
#include "d3_interface.h"
#include "d3_io_a.h"
#include "d3_io_t.h"
#include "d3_sky.h"
#include "d3_sm.h"
#include "d3_vec.h"
#include "err.h"
#include "f3snd.h"
#include "io_text.h"
#include "ls.h"
#include "main.h"
#include "mem.h"
#include "msx.h"
#include "rd.h"
#include "sblib.h"
#include "tb.h"
#include "tr.h"
#include "d3_pose.h"
#include "sv_t.h"
#include "lc.h"
#include "shp.h"
#include "f3gm_types.h"
#include "f3gm.h"
#include "he.h"
#include "amt.h"
#include "am_types.h"
#include "mission.h"
#include "gv.h"
#include "poker.h"
#include "gfx.h"
/* clang-format off */
unsigned short util_Random(unsigned short n);  /* 0x42ec00, @original: tr.c defines it returning int; this unit's callers read the 16-bit result (mov si,ax / movzx): the original's units saw a 16-bit declaration */
#define d3sm_PickK ((int (*)(D3SM *, int, int, int *, int *))d3sm_Pick)  /* 0x45f2b0 (d3_sm.c: char d3sm_Pick(D3SM *, int, int, int *, int *)): @original this unit's callers read an int result (byte-matched cm_UpdatePointer 0x4cf73a: and eax, 0xff after the call) */
/* clang-format on */
#define CM_KEEPER_FLAG                                                                               \
  0x800000 /* flags1c8 bit 23 (he.c HE_LOVER_FLAG: has a keeper; f3gm.c ORD_F1C8_ANEW): message 0x19 \
              may not set it on a character that has it */
typedef struct
    CMCUTTYPEMSG { /* 0x7c bytes, the data of the system message 0x11 cm_RunSceneParty sends (cm_SendExSysMessage) */
  int party;       /* 0x00, the party's id (G28REC.id) */
  char text[0x78]; /* 0x04, "cut_type:%i" with the scene kind */
} CMCUTTYPEMSG;
typedef struct
    CMFIELD { /* the head of one field of a field block (G17FIELDS.buf); its values follow at 0x04 */
  signed char size;      /* 0x00, a value's size: 1, 2 or 4 bytes */
  signed char n;         /* 0x01, the values */
  unsigned short offset; /* 0x02, the field's offset in the record */
  int values[1];         /* 0x04, the values */
} CMFIELD;
typedef struct
    CMGRENADE {  /* 0x10 bytes, one of the 32 thrown bombs of cm_Grenades */
  D3OBJECT *obj; /* the object "ob_BOMBE", 0 = a free slot */
  D3PATH *anim;  /* 0x04, its flight path (d3anim_CreatePath) */
  int x, y;      /* 0x08, the target cell */
} CMGRENADE;

/* dcp unit split: the declarations of cm before the moved functions */

/* clang-format off */
AIWEAPON ai_WeaponRecords[10] = {  /* 0x60c7c0, the ten records ai_FindWeaponRecord searches; the last has id 0, the fallback */
    { 0x154, 120, 5, 20, 0, 1, 4, 1, 0, 80.0f, 2, "kampf/stich", 0x1163, 0 },
    { 0x156, 95, 10, 15, 0, 1, 4, 1, 0, 80.0f, 5, "kampf/streich", 0x1164, 0 },
    { 0x158, 80, 20, 40, 0, 1, 4, 1, 0, 80.0f, 10, "kampf/hieb", 0x1165, 0 },
    { 0x172, 110, 5, 10, 0, 1, 5, 0, 0, 80.0f, 10, "kampf/stich", 0x1166, 0 },
    { 0x16e, 100, 5, 10, 0, 1, 5, 0, 0, 80.0f, 10, "kampf/stich", 0x1167, 0 },
    { 0x174, 100, 0, 30, 1, 2, 6, 0, 0, 200.0f, 2, "kampf/werfen", 0x1168, 2 },
    { 0x176, 90, 0, 30, 1, 1, 6, 0, 0, 200.0f, 2, "kampf/werfen", 0x1169, 2 },
    { 0x15e, 60, 5, 20, 1, 1, 3, 0, 0, 400.0f, 5, "kampf/schiessen_pistole", 0x116a, 1 },
    { 0x160, 70, 10, 30, 1, 1, 3, 0, 0, 600.0f, 5, "kampf/schiessen_armbrust", 0x116b, 1 },
    { 0x0, 150, 2, 8, 0, 1, 5, 1, 0, 80.0f, 2, "kampf/schlagen1", 0x1163, 0 }
};
/* clang-format on */
float cm_DefenseFactor = 1.0f;     /* 0x60cb58 */
int cm_FightOwner = -1;            /* 0x60cb5c */
int cm_FightView = -1;             /* 0x60cb60 */
int cm_FightTimeBar = -1;          /* 0x60cb64 */
int cm_FightButton = -1;           /* 0x60cb68 */
struct D3OBJECT *cm_PointList[32]; /* 0x930380 */
CMPORTRAIT cm_Portraits[6];        /* 0x930400 */
G18POP cm_DamagePops[16];          /* 0x9304c0 */
AICHAR cm_Fighters
    [32]; /* 0x930600, the fight copies of the characters in the fight */
char cm_FightScratch
    [0x1000]; /* 0x934980, cleared by the fight setup (cm_SetupFightScene); no other reader known */
struct D3OBJECT *cm_FlagObjects[32]; /* 0x935980 */
CMGRENADE cm_Grenades[32];           /* 0x935a00, the thrown bombs */
CMBOMB cm_Bombs[32];          /* 0x935c00, the 32 bomb records (object, time) */
float cm_FightCellScale;      /* 0x935d00 */
int cm_CharInfoWins[32];      /* 0x935d20 */
D3OBJECT *cm_HoverObject = 0; /* 0x6f0ce0 */
int cm_FightPaused = 0;       /* 0x6f0ce4, fight paused */
AICHAR *cm_FightDefender = 0; /* 0x6f0ce8, the defending side's leader */
AICHAR *cm_FightAttacker = 0; /* 0x6f0cec, the attacking side's leader */
D3OBJECT *cm_PickMarker = 0;  /* 0x6f0cf0 */
AICHAR *cm_FightWinner = 0;   /* 0x6f0cf4 */
int cm_FightSettled = 0;      /* 0x6f0cf8 */
int cm_FightLootValue = 0;    /* 0x6f0cfc */
int cm_UnreadBss =
    0; /* 0x6f0d00, no surviving instruction or pointer refers to it: data of functions /OPT:REF removed; size from the neighbours' addresses */
G28REC *cm_FightRecord = 0;                 /* 0x6f0d04 */
int cm_SelectedCount = 0;                   /* 0x6f0d08 */
struct SBBANK *cm_FightSounds = 0;          /* 0x6f0d0c */
struct SBBANK *cm_CrossbowSounds = 0;       /* 0x6f0d10 */
struct SBBANK *cm_BombSounds = 0;           /* 0x6f0d14 */
struct SBBANK *cm_DaggerSounds = 0;         /* 0x6f0d18 */
struct SBBANK *cm_PistolSounds = 0;         /* 0x6f0d1c */
struct SBBANK *cm_SwordSounds = 0;          /* 0x6f0d20 */
struct SBBANK *cm_AttackerClickVoices = 0;  /* 0x6f0d24 */
struct SBBANK *cm_DefenderClickVoices = 0;  /* 0x6f0d28 */
struct SBBANK *cm_AttackerAttackVoices = 0; /* 0x6f0d2c */
struct SBBANK *cm_DefenderAttackVoices = 0; /* 0x6f0d30 */
struct SBBANK *cm_AttackerOrderVoices = 0;  /* 0x6f0d34 */
struct SBBANK *cm_DefenderOrderVoices = 0;  /* 0x6f0d38 */
struct SBBANK *cm_AttackerTauntVoices = 0;  /* 0x6f0d3c */
struct SBBANK *cm_DefenderTauntVoices = 0;  /* 0x6f0d40 */
struct SBBANK *cm_AttackerPainVoices = 0;   /* 0x6f0d44 */
struct SBBANK *cm_DefenderPainVoices = 0;   /* 0x6f0d48 */
struct MSXTRACK *cm_FightAmbient = 0;       /* 0x6f0d4c */
int cm_AttackerRole = 0;                    /* 0x6f0d50 */
int cm_DefenderRole = 0;                    /* 0x6f0d54 */
int cm_FlagObjectCount = 0;                 /* 0x6f0d58 */
struct D3BGF *cm_BootsObject = 0;           /* 0x6f0d5c */
int cm_PointCount = 0;                      /* 0x6f0d60 */
int cm_FightForm = 0;                       /* 0x6f0d64 */

/* 0x4cd9d0, the weapon record (AIWEAPON) of the ten at ai_WeaponRecords with the goods item id id, 0: none */

AIWEAPON *ai_FindWeaponRecord(int id) {
  int i = 0;
  AIWEAPON *p;

  for (p = ai_WeaponRecords; (intptr_t)p < (intptr_t)(ai_WeaponRecords + 10);
       p++) {
    if (p->id == id)
      return ai_WeaponRecords + i;
    i++;
  }
  return 0;
}
/* 0x4cda00, the first weapon record (ai_FindWeaponRecord) of the kind 5 items of the character c's inventory */

AIWEAPON *cm_CharWeaponAny(AICHAR *c) {
  AIOBJ *q;
  AIWEAPON *r;

  for (q = gm_Query(c->inventory, 1, 5); q != 0; q = gm_QueryNext()) {
    r = ai_FindWeaponRecord(q->id);
    if (r != 0)
      return r;
  }
  return ai_FindWeaponRecord(0);
}
/* 0x4cda50, as cm_CharWeaponAny; a record of kind 1 / 2 whose item has nothing left (AIOBJ.usesLeft) is not taken */

AIWEAPON *cm_CharWeapon(AICHAR *c) {
  AIOBJ *q;
  AIWEAPON *r;

  for (q = gm_Query(c->inventory, 1, 5); q != 0; q = gm_QueryNext()) {
    r = ai_FindWeaponRecord(q->id);
    if (r != 0) {
      if ((r->kind == 1 || r->kind == 2) && q->usesLeft <= 0)
        return ai_FindWeaponRecord(0);
      return r;
    }
  }
  return ai_FindWeaponRecord(0);
}
/* 0x4cdac0, the inventory entry (AIOBJ, not its weapon record) of the search cm_CharWeapon does, 0: none */

AIOBJ *cm_CharWeaponItem(AICHAR *c) {
  AIOBJ *q;
  AIWEAPON *r;

  for (q = gm_Query(c->inventory, 1, 5); q != 0; q = gm_QueryNext()) {
    r = ai_FindWeaponRecord(q->id);
    if (r != 0) {
      if ((r->kind == 1 || r->kind == 2) && q->usesLeft <= 0)
        return 0;
      return q;
    }
  }
  return 0;
}
/* 0x4cdb20, gives up every weapon item of the character c's inventory: sends each as sold to nobody (cm_SendExSellObject, buyer -1) */

void cm_DiscardWeapons(AICHAR *c) {
  AICHAR *ch = c;
  AIOBJ *q;
  int id;

  for (q = gm_Query(ch->inventory, 1, 5); q != 0; q = gm_QueryNext()) {
    id = q->id;
    if (ai_FindWeaponRecord(id) != 0)
      cm_SendExSellObject(-1, ch->netId, id, q->count, ai_OwnPlayer, 0);
  }
}
/* 0x4cdb80, after a fight, of a character c with the flag 0x20000000: with the chance c->b1c5 in 10 its weapons are
   taken (cm_DiscardWeapons), b1c5 is negated and the owner of its building (a character of kind 6 / 7) gets the news
   0x1bca naming the weapon; returns 1. Else b1c5 becomes 1, the flag is cleared; returns 0 */

char cm_FightWeaponLoss(AICHAR *ch) {
  char buf[0x800];
  char v = 1; /* the value sent for b1c5: 1, or the negated chance */
  char neg;
  AICHAR *c = ch;
  AICHAR *owner;
  AIWEAPON *w;

  if (c != 0 && (c->flags1c8 & 0x20000000) != 0) {
    neg = c->b1c5;
    if (util_Random(10) < (unsigned char)neg) {
      v = -neg;
      cm_DiscardWeapons(c);
      cm_BeginFieldBlock(c, c->netId);
      cm_AddFieldValues(1, 1, (char *)&c->b1c5 - cm_FieldObject, &v);
      cm_SendFieldDeltas();
      if (c->bld != 0 && c->bld->owner != 0xffff) {
        owner = &ai_Chars[c->bld->owner];
        if (owner->kind == 6 || owner->kind == 7) {
          w = cm_CharWeapon(c);
          if (w->id != 0) {
            txt_Format(buf, 0x1bca, w->id * 2 + 0x9a8, c->id, c->bld);
            he_ShowNews(owner->netId, -1, buf, 0, 0x5f2, 0);
          }
        }
      }
      return 1;
    }
    cm_BeginFieldBlock(c, c->netId);
    cm_AddFieldValues(1, 1, (char *)&c->b1c5 - cm_FieldObject, &v);
    cm_SendFieldDeltas();
    cm_SendSetField(c->netId, 0x1c8, 4, 0, 0x20000000);
  }
  return 0;
}
/* 0x4cdcf0, the fighting strength of the character c: its health ratio times its skill 3 times a factor of the
   weapon it carries (cm_CharWeapon's item: 0x158 1.0, 0x154 0.5, 0x156 / 0x16e / 0x172 0.8, 0x174 / 0x176 0.9,
   0x15e / 0x160 0.7, another 0.3; none 0.5) */

float cm_FightStrength(AICHAR *c) {
  float f = 0.5f;
  float skill;
  AIWEAPON *w;

  skill = gm_GetSkill(c, 3);
  w = cm_CharWeapon(c);
  if (w != 0) {
    switch (w->id) {
    case 0x158:
      f = 1.0f;
      break;
    case 0x154:
      f = 0.5f;
      break;
    case 0x156:
    case 0x16e:
    case 0x172:
      f = 0.8f;
      break;
    case 0x174:
    case 0x176:
      f = 0.9f;
      break;
    case 0x15e:
    case 0x160:
      f = 0.7f;
      break;
    default:
      f = 0.3f;
    }
  }
  return gm_HealthRatio(c) * skill * f;
}
/* 0x4cde20, puts the weapon the character c carries (cm_CharWeapon) into its scene character's right hand as the
   model "ob_<GOOD NAME>" (unless it holds that already); without a weapon the hand is emptied */

void cm_UpdateHandObject(AICHAR *ch) {
  char buf[0x80];
  AICHAR *c = ch;
  AIWEAPON *w;
  AIGOOD *g;

  w = cm_CharWeapon(ch);
  if (w != 0 && w->id != 0) {
    g = &ai_Goods[w->id];
    if (c->scene == 0)
      return;
    sprintf(buf, "ob_%s", strupr(g->name));
    if (c->scene->rightHand != 0 &&
        strcmpi(c->scene->rightHand->name, buf) == 0)
      return;
    if (c->scene->rightHand != 0)
      ch_SetHandObject(c->scene, 2, 0);
    ch_SetHandObject(c->scene, 2, buf);
    return;
  }
  if (c->scene != 0 && c->scene->rightHand != 0)
    ch_SetHandObject(c->scene, 2, 0);
}
/* 0x4cdf00, the record of the character c in the 16 records (0x2c bytes, id at +0) of rec + 0x94, else a free one
   (id -1), 0: none */

CMCUTENTRY *cm_CutEntrySlot(CMCUTINFO *rec, AICHAR *c) {
  CMCUTINFO *r = rec;
  int id = c->netId;
  int i;

  for (i = 0; i < 16; i++) {
    if (r->entries[i].charId == id)
      return &r->entries[i];
  }
  for (i = 0; i < 16; i++) {
    if (r->entries[i].charId == -1) {
      memset(&r->entries[i], 0, sizeof(CMCUTENTRY));
      r->entries[i].charId = c->netId;
      r->entries[i].state = 0;
      return &r->entries[i];
    }
  }
  return 0;
}
/* 0x4cdf80, the entry (CMCUTENTRY) of the character c in the first cm_FightRecord[0x30] cutscene records
   (cm_CutInfos), 0: none */

CMCUTENTRY *cm_FightCutEntry(AICHAR *c) {
  int n = cm_FightRecord->used;
  CMCUTINFO *r;
  int i, j;

  for (i = 0; i < n; i++) {
    r = &cm_CutInfos[i];
    for (j = 0; j < 16; j++) {
      if (r->entries[j].charId == c->netId)
        return &r->entries[j];
    }
  }
  return 0;
}
/* 0x4cdfe0, 1 when the cell (x, y) of the height map d3_DefaultScene->hmap is inside and passable */

int cm_CellUsable(int x, int y) {
  D3SM *g = d3_DefaultScene->hmap;
  int w = g->size;
  int type;

  if (x > w || x < 0 || y < 0 || y > w || x >= w || y >= w)
    return 0;
  type = g->entries[w * y + x].type;
  if (type == 0 || type == 0xd)
    return 0;
  return 1;
}
/* 0x4ce040, the nearest usable cell (cm_CellUsable) of the current scene's height map around the cell (a, b), in
   diamonds of the distance d = 0 .. 0x3f, rows top to bottom: *ox, *oy, returns 1; 0: none */

int cm_FindNearCell(int a, int b, int *ox, int *oy) {
  D3SM *hmap = d3_DefaultScene->hmap;
  int d, y, x, k, ylo, yhi, xlo, xhi;

  for (d = 0; d < 0x40; d++) {
    yhi = hmap->size - 1 < b + d ? hmap->size - 1 : b + d;
    ylo = b - d < 0 ? 0 : b - d;
    for (y = ylo; y <= yhi; y++) {
      k = d - abs(b - y);
      xhi = hmap->size - 1 < k + a ? hmap->size - 1 : k + a;
      xlo = a - k < 0 ? 0 : a - k;
      for (x = xlo; x <= xhi; x++) {
        if (cm_CellUsable(x, y) != 0) {
          *ox = x;
          *oy = y;
          return 1;
        }
      }
    }
  }
  return 0;
}
/* 0x4ce130, the fighter (an AICHAR, 0x21c bytes) with the netId id among the 32 of cm_Fighters, 0 when none */

struct AICHAR *cm_FindFighter(int id) {
  int i = 0;
  AICHAR *p;

  for (p = cm_Fighters; (intptr_t)&p->netId < (intptr_t)&cm_Fighters[32].netId;
       p++) {
    if (p->id != 0xffff && p->netId == id)
      return &cm_Fighters[i];
    i++;
  }
  return 0;
}
/* 0x4ce170, the select bits of the fighter c: 0x800 when its side leader (bld in a fight) is the character idx,
   or when gm_AllowAll is set */

int ai_LedSelectBits(int idx, AICHAR *c) {
  int r = 0;

  if (c->side == &ai_Chars[idx])
    r = 0x800;
  if (gm_AllowAll != 0)
    r = 0x800;
  if (0)
    /* clang-format off */
    ai_PickedObject = 0;   /* @original dead code: VC6 counts this leaf as writing ai_PickedObject (cm_UpdatePointer reloads it after each call); no code */
  /* clang-format on */
  return r;
}
/* 0x4ce1b0, the distance of the character c's model to the object o (x / z) */

float cm_CharObjDistXZ(AICHAR *c, D3OBJECT *o) {
  D3VECTOR4 v, d;

  v.x = o->pos.x;
  v.z = o->pos.z;
  d.x = c->scene->obj->pos.x;
  d.z = c->scene->obj->pos.z;
  d.x = v.x - d.x;
  d.z = v.z - d.z;
  return (float)sqrt(d.z * d.z + d.x * d.x);
}
/* 0x4ce200, the distance in the x / z plane of the character c's body to the vertex of cell (x, y) (the frame holds two 16-byte vectors) */

float cm_CharCellDistXZ(AICHAR *c, int x, int y) {
  D3VECTOR4 v, d;
  D3VECTOR b;

  d3sm_GetVertex(d3_DefaultScene->hmap, x, y, &v.v);
  v.y = 0;
  b.x = c->scene->obj->pos.x;
  b.z = c->scene->obj->pos.z;
  d.x = v.x - b.x;
  d.z = v.z - b.z;
  return (float)sqrt(d.z * d.z + d.x * d.x);
}
/* 0x4ce270, 1 when the two characters are not in the same building (+0x16c) */

int cm_OtherBuilding(AICHAR *a, AICHAR *b) { return a->bld != b->bld; }
/* 0x4ce290, a bomb object "ob_BOMBE" at the position p in a free slot of the 32 (object, time) of cm_Bombs */

CMBOMB *cm_LayBomb(D3VECTOR *p) {
  D3VECTOR rot;
  int i;
  CMBOMB *b;

  rot.x = 0;
  rot.y = 0;
  rot.z = 0;
  for (i = 0; i < 32; i++) {
    if (cm_Bombs[i].obj == 0) {
      b = &cm_Bombs[i];
      b->obj = d3_CreateObject(0, p, &rot, "ob_BOMBE");
      cm_Bombs[i].time = d3_Time;
      return b;
    }
  }
  return 0;
}
/* 0x4ce300, updates the bombs of cm_Bombs: a bomb older than 0x15e ms explodes (the sound "Explosion_s", smoke, earth
   and explosion effects at its position) and hurts every scene character within 170.0 by a random weapon damage (0x174)
   scaled by its life value and the distance; returns the number of used slots */

int cm_UpdateBombs() {
  int cnt;
  AIWEAPON *w;
  CMBOMB *rec;
  AICHAR *c;
  CHARACTER *ch;
  D3OBJECT *bo;
  /* clang-format off */
  struct { union { struct { float x, y, z; }; D3VECTOR v; }; int w; } a, b;   /* @original the pad word is an int: its 0 stores use the cached zero register */
  /* clang-format on */
  D3COLOR col;
  float dist;
  int i, j, t, amt;

  cnt = 0;
  w = ai_FindWeaponRecord(0x174);
  for (i = 0; i < 32; i++) {
    rec = &cm_Bombs[i];
    if (rec->obj == 0)
      continue;
    cnt++;
    if (d3_Time <= rec->time + 0x15e)
      continue;
    a.x = -243.0f;
    a.y = -90.0f;
    a.z = 190.0f;
    a.w = 0;
    b.x = -50.0f;
    b.y = 0.0f;
    b.z = 38.0f;
    b.w = 0;
    sb_PlaySample(cm_BombSounds, "Explosion_s", 1, 0x3f, 0x7f, 0, 0);
    col.r = 0xc0;
    col.g = 0xc0;
    col.b = 0xc0;
    col.a = 0x3f;
    a.x = rec->obj->pos.x;
    a.y = rec->obj->pos.y;
    a.z = rec->obj->pos.z;
    d3t_CreateSmoke(0, &a.v, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f, 140.0f, 35.0f,
                    &b.v, 0x190, 6, col);
    d3t_CreateEarth(0, &a.v, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f, 4.0f, 7.0f,
                    8.0f, col);
    d3t_CreateExplosion(0, &a.v, 0x1e, 120.0f, 80.0f, 20.0f, 60.0f, 0x3c);
    for (j = 0; j < 32; j++) {
      if (ai_SceneChars[j] == 0)
        continue;
      ch = ai_SceneChars[j]->scene;
      c = ai_SceneChars[j];
      if (c->health == 0)
        continue;
      bo = rec->obj;
      a.x = bo->pos.x - ch->obj->pos.x;
      a.y = bo->pos.y - ch->obj->pos.y;
      a.z = bo->pos.z - ch->obj->pos.z;
      dist = (float)sqrt(a.z * a.z + a.y * a.y + a.x * a.x);
      if (dist < 170.0f) {
        t = (int)((cm_Random(w->dmgMax - w->dmgMin) + w->dmgMin) *
                  (c->f01c * 0.01));
        amt = (int)(t * (1.0 - dist * 0.0058823530562222f));
        ai_SceneChars[j]->v024 -= amt;
        if (ai_SceneChars[j]->side == cm_FightAttacker)
          cm_ShowDamage(ai_SceneChars[j], amt, 1);
        else
          cm_ShowDamage(ai_SceneChars[j], amt, 2);
        if (cm_CheckDeath(c) == 0)
          ch_QueueAnim(ch, "kampf/bauch_greifen", 1);
      }
    }
    d3if_Delete(rec->obj);
    rec->obj = 0;
  }
  return cnt;
}
/* 0x4ce5d0, throws a bomb: the first free slot of cm_Grenades gets the object "ob_BOMBE" at p (60.0 higher) and a
   4-key path animation (up to half way + 50.0, then down) to the vertex of the cell (x, y); 0 when all 32 are used */

CMGRENADE *cm_ThrowGrenade(D3VECTOR *p, int x, int y) {
  D3ANIMKEY keys[4];
  D3VECTOR4 mid;
  D3VECTOR4 pos;
  D3VECTOR rot;
  D3ANIMFLAGS af;
  D3VECTOR4 d;
  struct D3SM *g;
  int i;

  rot.x = 0;
  rot.y = 0;
  rot.z = 0;
  g = d3_DefaultScene->hmap;
  for (i = 0; i < 32; i++) {
    if (cm_Grenades[i].obj != 0)
      continue;
    pos.x = p->x;
    pos.y = p->y + 60.0;
    pos.z = p->z;
    cm_Grenades[i].obj = d3_CreateObject(0, &pos.v, &rot, "ob_BOMBE");
    cm_Grenades[i].obj->objectFlags |= 4;
    d3sm_GetVertex(g, x, y, &d.v);
    d.x -= p->x;
    d.y -= p->y;
    d.z -= p->z;
    memset(keys, 0, sizeof(keys));
    mid.x = d.x * 0.5;
    mid.y = d.y * 0.5;
    mid.z = d.z * 0.5;
    mid.y += 50.0;
    D3_ZERO(&af, sizeof(af));
    af.b[1] |= 0x14;
    af.b[8] |= 2;
    af.b[1] |= 8;
    keys[1].pos.x = mid.x;
    keys[1].pos.y = mid.y;
    keys[1].pos.z = mid.z;
    keys[1].rot.x = 3.1415927f;
    keys[1].rot.y = 3.1415927f;
    keys[1].rot.z = 3.1415927f;
    d.y -= 60.0;
    keys[2].pos.x = d.x;
    keys[2].pos.y = d.y;
    keys[2].pos.z = d.z;
    keys[2].rot.x = 3.1415927f;
    keys[2].rot.y = 3.1415927f;
    keys[2].rot.z = 3.1415927f;
    keys[3].pos.x = d.x;
    keys[3].pos.y = d.y;
    keys[3].pos.z = d.z;
    keys[3].rot.x = 3.1415927f;
    keys[3].rot.y = 3.1415927f;
    keys[3].rot.z = 3.1415927f;
    keys[0].time = 0x12;
    keys[1].time = 0x12;
    keys[2].time = 1;
    cm_Grenades[i].anim = d3anim_CreatePath(cm_Grenades[i].obj, af, 4, keys);
    cm_Grenades[i].x = x;
    cm_Grenades[i].y = y;
    return &cm_Grenades[i];
  }
  return 0;
}
/* 0x4ce830, updates the thrown bombs of cm_Grenades: one whose path has ended (flag 0x20 of D3PATH.flags.b[1]) explodes
   (smoke, earth and explosion effects at its position), lowers the terrain at its cell by 5 and clears the cell's
   type there (the map rebuilt), sounds "Explosion_s" and hurts every scene character within 100.0 of the cell's
   vertex by a random weapon damage (0x176) scaled by its life value and the distance; returns the number of used
   slots */

int cm_UpdateGrenades() {
  int cnt;
  AIWEAPON *w;
  struct D3SM *g;
  CMGRENADE *rec;
  AICHAR *c;
  CHARACTER *ch;
  /* clang-format off */
  struct { union { struct { float x, y, z; }; D3VECTOR v; }; int w; } a, b;   /* @original the pad word is an int: its 0 stores use the cached zero register */
  /* clang-format on */
  D3COLOR col;
  float dist;
  int i, j, t, amt;

  g = d3_DefaultScene->hmap;
  cnt = 0;
  w = ai_FindWeaponRecord(0x176);
  for (i = 0; i < 32; i++) {
    rec = &cm_Grenades[i];
    if (rec->obj == 0)
      continue;
    cnt++;
    if (!(rec->anim->flags.b[1] & 0x20))
      continue;
    a.x = -243.0f;
    a.y = -90.0f;
    a.z = 190.0f;
    a.w = 0;
    b.x = -50.0f;
    b.y = 0.0f;
    b.z = 38.0f;
    b.w = 0;
    col.r = 0xc0;
    col.g = 0xc0;
    col.b = 0xc0;
    col.a = 0x3f;
    a.x = rec->obj->pos.x;
    a.y = rec->obj->pos.y;
    a.z = rec->obj->pos.z;
    d3t_CreateSmoke(0, &a.v, 0x1e, 15.0f, 50.0f, 100.0f, 150.0f, 140.0f, 35.0f,
                    &b.v, 0x190, 6, col);
    d3t_CreateEarth(0, &a.v, 0x1e, 5.0f, 2.5f, 1.0f, 3.0f, -3.0f, 4.0f, 7.0f,
                    8.0f, col);
    d3t_CreateExplosion(0, &a.v, 0x1e, 70.0f, 50.0f, 20.0f, 60.0f, 0x3c);
    /* @original the cell index reads x through the table and y through rec: written this way VC6 keeps the
       index as one value for both arrays */
    if (d3_Terrain->types[cm_Grenades[i].x + rec->y * d3_Terrain->size] != 0) {
      d3_Terrain->height[cm_Grenades[i].x + rec->y * d3_Terrain->size] -= 5;
      d3_Terrain->types[rec->x + rec->y * d3_Terrain->size] = 0;
      d3fl_MakeDivide(d3_Terrain);
      d3fl_MakeLight(d3_Terrain);
    }
    sb_PlaySample(cm_BombSounds, "Explosion_s", 1, 0x3f, 0x7f, 0, 0);
    for (j = 0; j < 32; j++) {
      if (ai_SceneChars[j] == 0)
        continue;
      ch = ai_SceneChars[j]->scene;
      c = ai_SceneChars[j];
      if (c->health == 0)
        continue;
      d3sm_GetVertex(g, rec->x, rec->y, &a.v);
      a.x -= ch->obj->pos.x;
      a.y -= ch->obj->pos.y;
      a.z -= ch->obj->pos.z;
      dist = (float)sqrt(a.z * a.z + a.y * a.y + a.x * a.x);
      if (dist < 100.0f) {
        t = (int)((cm_Random(w->dmgMax - w->dmgMin) + w->dmgMin) *
                  (c->f01c * 0.01));
        amt = (int)(t * (1.0 - dist * 0.01f));
        ai_SceneChars[j]->v024 -= amt;
        if (ai_SceneChars[j]->side == cm_FightAttacker)
          cm_ShowDamage(ai_SceneChars[j], amt, 1);
        else
          cm_ShowDamage(ai_SceneChars[j], amt, 2);
        if (cm_CheckDeath(c) == 0)
          ch_QueueAnim(ch, "kampf/arm_greifen", 1);
      }
    }
    d3if_Delete(rec->obj);
    rec->obj = 0;
  }
  return cnt;
}
/* 0x4ceb70, the game record the object c stands for (its owner) */

void *cm_ObjectOwner(D3OBJECT *c) { return c->owner; }
/* 0x4ceb80, waits for the event id to end, then stops it */

void cm_WaitEventStop(int id) {
  EVTSCRIPT *e;

  if (cm_SkipEvents != 0)
    return;
  if (sv_RunFrame(0, 0x7d6c6) != 0) {
    do {
      if (dm_L.rup != 0 || kb_Last != 0)
        break;
      if (evt_FindById(id) == 0)
        return;
    } while (sv_RunFrame(0, 0x7d6c6) != 0);
  }
  e = evt_FindById(id);
  if (e != 0)
    evt_Stop(e);
  di_ClearButtons();
}
/* 0x4cec00, closes the 32 windows of cm_CharInfoWins */

void cm_CloseCharInfoWins() {
  int *p;

  for (p = cm_CharInfoWins; (int)p < (int)(cm_CharInfoWins + 0x20); p++) {
    if (*p != -1) {
      d2_RemoveWindow(*p);
      *p = -1;
    }
  }
}
/* 0x4cec30, the info window of the character c: a window 16 pixels around the screen box of its body (at least 110
   wide; pictures 0x7b0 / 0x7b1 in its corners) with the value bar of skill 3 and the health slider (0..100), in a free
   slot of cm_CharInfoWins; first the record of c in a (cm_CutEntrySlot) is looked up or taken */

void cm_OpenCharInfoWin(CMCUTINFO *a, AICHAR *c) {
  D3RECT r;
  int x0, y0, w, h, i, hp, bar;

  if (d3if_ScreenBox(c->scene->obj, &r) == 0)
    return;
  x0 = r.left - 0x10;
  y0 = r.top - 0x10;
  w = r.right - r.left + 0x20;
  if (w <= 0x6e)
    w = 0x6e;
  h = r.bottom - r.top + 0x20;
  for (i = 0; i < 0x20; i++) {
    if (cm_CharInfoWins[i] != -1)
      continue;
    cm_CutEntrySlot(a, c);
    cm_CharInfoWins[i] = d2_CreateWindow(x0, y0, w, h, 0x10);
    d2_WinOpenPic(0, 0, 0x7b0, d2_LastWindow);
    d2_WinOpenPic(w - 0x18, 0, 0x7b1, d2_LastWindow);
    d2_Wins[d2_LastWindow].font = 0x54;
    sv_ValueBar(4, 4, gm_SkillPoints(c, 3), 0x4df);
    hp = (int)(gm_HealthRatio(c) * 100.0);
    bar = d2_WinOpenSlider(0, 0xe, 0x40, 0, 0x64, 0x75, 0x442, d2_LastWindow);
    d2_SetObjValue(bar, 0, 0x64, hp);
    return;
  }
}
/* 0x4ced80, refreshes the character info windows: closes them, then opens one for every selected fighter (a: the
   fight record the cut entries go to) */

void cm_UpdateCharInfoWins(CMCUTINFO *a) {
  AICHAR *p;

  cm_CloseCharInfoWins();
  for (p = cm_Fighters; (intptr_t)p < (intptr_t)&cm_Fighters[32]; p++) {
    if (p->selected != 0)
      cm_OpenCharInfoWin(a, p);
  }
}
/* 0x4cedc0, shows the damage v over the character c as a floating number (v relative to its life value f01c, in
   percent) in a free slot of the 16 of cm_DamagePops (kind 1 / 2 drawn with signs, else plain) */

void cm_ShowDamage(AICHAR *c, int v, int kind) {
  int i;

  for (i = 0; i < 16; i++) {
    if (cm_DamagePops[i].v != 0)
      continue;
    cm_DamagePops[i].v = (int)((double)v / (c->f01c * 0.01));
    cm_DamagePops[i].c = c;
    cm_DamagePops[i].t = 64.0f;
    cm_DamagePops[i].kind = kind;
    return;
  }
}
/* 0x4cee20, shows / moves the damage numbers of cm_ShowDamage over their characters (created on first show, kind 1 /
   2 between sign glyphs); each rises half a pixel a step and is removed after 128 steps; a character off screen hides
   its number and ends the pass */

void cm_UpdateDamagePops(void) {
  char buf[0x40];
  D3RECT box;
  int i, x, y0;
  AICHAR *c;

  for (i = 0; i < 16; i++) {
    if (cm_DamagePops[i].v == 0)
      continue;
    c = cm_DamagePops[i].c;
    if (d3if_ScreenBox(c->scene->obj, &box) == 0) {
      if (cm_DamagePops[i].h != -1)
        d2_EnableObject(cm_DamagePops[i].h, 0);
      return;
    }
    x = box.left + 0x10;
    y0 = box.top - 0x30;
    if (cm_DamagePops[i].h == -1) {
      if (cm_DamagePops[i].kind == 1)
        sprintf(buf, "%c-%i%c", 0x5c, cm_DamagePops[i].v, 0x5d);
      else if (cm_DamagePops[i].kind == 2)
        sprintf(buf, "%c-%i%c", 0x5e, cm_DamagePops[i].v, 0x5f);
      else
        sprintf(buf, "-%i", cm_DamagePops[i].v);
      cm_DamagePops[i].h =
          d2_CreateScreenText(x, (int)(y0 + cm_DamagePops[i].t), buf);
    } else
      d2_MoveObj(x, (int)(y0 + cm_DamagePops[i].t), cm_DamagePops[i].h);
    if (cm_DamagePops[i].h != -1)
      d2_EnableObject(cm_DamagePops[i].h, 1);
    cm_DamagePops[i].t = (float)(cm_DamagePops[i].t - 0.5);
    if (cm_DamagePops[i].t <= 0.0f) {
      d2_RemoveObj(cm_DamagePops[i].h);
      cm_DamagePops[i].v = 0;
      cm_DamagePops[i].h = -1;
      cm_DamagePops[i].c = 0;
    }
  }
}
/* 0x4cef80, clears the 16 damage numbers of cm_DamagePops (no screen text, no value, no character) */

void cm_InitDamagePops(void) {
  int i;

  for (i = 0; i < 16; i++) {
    cm_DamagePops[i].h = -1;
    cm_DamagePops[i].v = 0;
    cm_DamagePops[i].c = 0;
  }
}
/* 0x4cefa0, removes all damage numbers of cm_DamagePops (their screen texts too) */

void cm_ClearDamagePops(void) {
  int i;

  for (i = 0; i < 16; i++) {
    if (cm_DamagePops[i].h != -1)
      d2_RemoveObj(cm_DamagePops[i].h);
    cm_DamagePops[i].h = -1;
    cm_DamagePops[i].v = 0;
    cm_DamagePops[i].c = 0;
  }
}
/* 0x4cefe0, closes the fight view (cm_FightView) and marks it closed (-1) */

void cm_CloseFightView() {
  if (cm_FightView != -1) {
    d2_CloseView(cm_FightView);
    cm_FightView = -1;
  }
}
/* 0x4cf000, the per-tick update of the scene characters (ai_SceneChars): on the fight owner's machine, every 0x15e
   ticks, a character whose health is 2..4 loses one point and the damage of weapon 0x16e (the poison, reasoned) is
   sent for it (health 1 is reset to 100); a character holding weapon 0x172 is shown to the others only near them
   (faded by the distance to the nearest one in another building, rest 255) or half-transparent when cm_CutChar
   sees it (0x800); a fighter in cutscene state 2 turns towards its partner; ends with the damage numbers */

void cm_UpdateSceneChars() {
  AICHAR *c, *d, *o;
  AIWEAPON *w;
  CMCUTENTRY *e;
  CHARACTER *g;
  D3OBJECT *body;
  D3TEXFLAGS col;
  int i, j, fl, found, dmg;
  unsigned int n;
  float best, dist, ang;
  unsigned char b;

  if (cm_CutChar->netId == cm_FightOwner && d3_Time % 0x15e == 0) {
    for (i = 0; i < 32; i++) {
      c = ai_SceneChars[i];
      if (c == 0)
        continue;
      b = c->health;
      if (b > 4 || b <= 0)
        continue;
      b--;
      c->health = b;
      if (b == 1)
        c->health = 100;
      else {
        w = ai_FindWeaponRecord(0x16e);
        n = cm_Random(w->dmgMax - w->dmgMin) + w->dmgMin;
        dmg = (int)(n * c->f01c * 0.01);
      }
      if (b != 1)
        cm_SendDamage(c->netId, dmg, c->health);
    }
  }
  for (i = 0; i < 32; i++) {
    c = ai_SceneChars[i];
    if (c == 0)
      continue;
    w = cm_CharWeapon(c);
    if (w != 0 && w->id == 0x172) {
      fl = 0;
      if (cm_CutChar != 0)
        fl = ai_LedSelectBits(cm_CutChar->id, c);
      if (fl & 0x800) {
        col.all = 0;
        col.b[2] = 0;
        col.b[0] = 0x80;
        d3if_ShowTree(c->scene->obj, 1);
        c->scene->obj->stateFlags &= 0xfd;
        d3_SetObjectAlpha(c->scene->obj, c->scene->obj->info, col);
        c->scene->obj->stateFlags |= 2;
      } else {
        best = 999999.0f;
        found = 0;
        for (j = 0; j < 32; j++) {
          d = ai_SceneChars[j];
          if (d != 0 && cm_OtherBuilding(c, d) != 0 && d->health != 0) {
            dist = cm_CharObjDistXZ(c, d->scene->obj);
            if (dist < 100.0f) {
              found = 1;
              if (dist < best)
                best = dist;
            }
          }
        }
        d3if_ShowTree(c->scene->obj, found);
        if (found != 0) {
          col.all = 0;
          col.b[2] = 0;
          col.b[0] = (unsigned char)(int)(255.0f - 255.0f * (best * 0.01f));
          c->scene->obj->stateFlags &= 0xfd;
          d3_SetObjectAlpha(c->scene->obj, c->scene->obj->info, col);
          c->scene->obj->stateFlags |= 2;
        }
      }
    }
    e = cm_FightCutEntry(c);
    if (e != 0 && e->state == 2 && e->turn != 0) {
      o = cm_FindFighter(e->stateArg);
      if (o != 0) {
        if (d3_VecEqual(&c->scene->obj->pos, &o->scene->obj->pos, 10.0f) == 0) {
          ang = d3_YawTo(c->scene->obj, &o->scene->obj->pos);
          g = c->scene;
          if (g->actions == 0 ||
              (g->actions->type != 0x2d && g->actions->type != 0x3a)) {
            if (fabs(ang) > 0.08) {
              ang *= 0.25;
              body = g->obj;
              d3_SetObjectRotXYZ(body, body->rotation.x, body->rotation.y + ang,
                                 body->rotation.z);
            }
          }
        }
      }
    }
  }
  cm_UpdateDamagePops();
}
/* 0x4cf370, draws the scroll arrows (sprite ids 0 .. 7 of the sheet d2_GetPic(0x52c)): the mouse hit tests and
   whether the camera's preset views d3_Camera->views[1] .. [4] are set (their position not d3_Origin) pick the
   pressed (2) or the free (1) look; the top and bottom arrows sit 75 screen units in from the edge (the top one's
   sprite 30 units tall) */

void cm_DrawScrollArrows(void) {
  int up = 0, e = 0, a = 0, b = 0;
  void *t;

  t = d2_GetPic(0x52c);
  if (sv_BorderViewX == -1) {
    up = 1;
    if (d3_VecEqual(&d3_Camera->views[4].pos, &d3_Origin.v, 0.2f) == 0)
      up = 2;
  } else if (sv_BorderViewX == 1) {
    e = 1;
    if (d3_VecEqual(&d3_Camera->views[3].pos, &d3_Origin.v, 0.2f) == 0)
      e = 2;
  } else if (sv_BorderViewX == 0) {
    if (d3_VecEqual(&d3_Camera->views[3].pos, &d3_Origin.v, 0.2f) == 0)
      e = 1;
    if (d3_VecEqual(&d3_Camera->views[4].pos, &d3_Origin.v, 0.2f) == 0)
      up = 1;
  }
  if (sv_BorderViewY == -1) {
    a = 1;
    if (d3_VecEqual(&d3_Camera->views[1].pos, &d3_Origin.v, 0.2f) == 0)
      a = 2;
  } else if (sv_BorderViewY == 1) {
    b = 1;
    if (d3_VecEqual(&d3_Camera->views[2].pos, &d3_Origin.v, 0.2f) == 0)
      b = 2;
  } else if (sv_BorderViewY == 0) {
    if (d3_VecEqual(&d3_Camera->views[1].pos, &d3_Origin.v, 0.2f) == 0)
      a = 1;
    if (d3_VecEqual(&d3_Camera->views[2].pos, &d3_Origin.v, 0.2f) == 0)
      b = 1;
  }
  d2_SetClipRect(0, 0, d2_ScreenSurf->w, d2_ScreenSurf->h);
  if (a == 2)
    d2_DrawShape(d2_ScreenW / 2 - 0x14, (int)(d2_ScreenScale * 525.0f - 30.0f),
                 d2_ScreenSurf, t, 0);
  else if (a == 1)
    d2_DrawShape(d2_ScreenW / 2 - 0x14, (int)(d2_ScreenScale * 525.0f - 30.0f),
                 d2_ScreenSurf, t, a);
  if (e == 2)
    d2_DrawShape(8, d2_ScreenH / 2 + 0x14, d2_ScreenSurf, t, e);
  else if (e == 1)
    d2_DrawShape(8, d2_ScreenH / 2 + 0x14, d2_ScreenSurf, t, 3);
  if (up == 2)
    d2_DrawShape(d2_ScreenW - 0x28, d2_ScreenH / 2 + 0x14, d2_ScreenSurf, t, 4);
  else if (up == 1)
    d2_DrawShape(d2_ScreenW - 0x28, d2_ScreenH / 2 + 0x14, d2_ScreenSurf, t, 5);
  if (b == 2)
    d2_DrawShape(d2_ScreenW / 2 - 0x14, (int)(d2_ScreenScale * 75.0f),
                 d2_ScreenSurf, t, 6);
  else if (b == 1)
    d2_DrawShape(d2_ScreenW / 2 - 0x14, (int)(d2_ScreenScale * 75.0f),
                 d2_ScreenSurf, t, 7);
}
/* 0x4cf670, the mouse pick: the object under the cursor (ai_PickedObject; with characters selected and nothing picked,
   the ground cell under the cursor is looked up, else the pick marker is hidden) and the cursor look d2_PointerLook:
   by the weapon of the selected characters cm_CutChar sees (0x160 -> 0x18 .. 0x176 -> 0x25; more than one: 0x23) over
   a character it does not see (or with key 0x36 down), "sp_ESCAPE" 0x1c, "sp_CONQUER" 0x1b, "WARE" 0xe;
   cm_HoverObject keeps the object the look was decided for */

void cm_UpdatePointer() {
  int i, n = 0, cur = 0x23;
  AICHAR *c;
  AIWEAPON *w;
  struct D3SM *map;
  int z, x;
  D3VECTOR4 v;

  map = d3_DefaultScene->hmap;
  ai_PickedObject = 0;
  d2_PointerLook = 0;
  if (dm_L.x > 0 && dm_L.x < d2_ScreenW && dm_L.y > 0 && dm_L.y < d2_ScreenH &&
      d2_PointerObj == -1) {
    ai_PickedObject = d3if_Pick((float)dm_L.x, (float)dm_L.y, 0x40, 1);
    if (ai_PickedObject == 0 && cm_SelectedCount != 0) {
      if ((d3sm_PickK(map, dm_L.x + 0x1a, dm_L.y + 0x1a, &x, &z) & 0xff) !=
          -1) {
        d3sm_GetVertex(map, x, z, &v.v);
        v.y += 10.0f;
        d2_PointerLook = 0;
      }
    } else if (cm_PickMarker != 0) {
      d3if_Show(cm_PickMarker, 0);
    }
  }
  if (ai_PickedObject == 0) {
    cm_HoverObject = 0;
    ai_PickedChar = 0;
    return;
  }
  for (i = 0; i < 31; i++) {
    c = ai_SceneChars[i];
    if (c != 0 && c->selected != 0) {
      if (ai_LedSelectBits(cm_CutChar->id, c) & 0x800) {
        if (kb_Down[0x36] == 0) {
          w = cm_CharWeapon(c);
          if (w != 0) {
            if (w->id == 0x160)
              cur = 0x18;
            else if (w->id == 0x174)
              cur = 0x19;
            else if (w->id == 0x16e)
              cur = 0x1e;
            else if (w->id == 0x154)
              cur = 0x1a;
            else if (w->id == 0x158)
              cur = 0x1f;
            else if (w->id == 0x15e)
              cur = 0x21;
            else if (w->id == 0x156)
              cur = 0x23;
            else if (w->id == 0x176)
              cur = 0x25;
          }
          n++;
        }
      }
    }
  }
  if (n > 1)
    cur = 0x23;
  if (ai_PickedObject != 0 && d2_PointerObj == -1) {
    if (strcmp(ai_PickedObject->name, "sp_ESCAPE") == 0 && n != 0)
      d2_PointerLook = 0x1c;
    else if (strncmp(ai_PickedObject->name, "sp_CONQUER", 10) == 0 && n != 0)
      d2_PointerLook = 0x1b;
    else if (strncmp(ai_PickedObject->name, "WARE", 4) == 0 && n != 0)
      d2_PointerLook = 0xe;
    else if (ai_PickedObject->kind == 2 && n != 0) {
      if (!(ai_LedSelectBits(cm_CutChar->id, ai_PickedObject->owner) & 0x800) ||
          kb_Down[0x36] != 0)
        d2_PointerLook = cur;
    } else
      d2_PointerLook = 0;
    cm_HoverObject = ai_PickedObject;
    return;
  }
  d2_PointerLook = 0;
}

/* 0x4cf9c0, refreshes the portrait boxes cm_Portraits: after a click a portrait's checked state becomes its
   character's selection; each box of a character whose body is of type 1 hides its window and frame, the others
   show the selection, the name with the health in percent ("%1N1 %i%"), the picture of the weapon (replaced when the
   weapon changed) and, for a kind 1 / 2 weapon, the count left; cm_SelectedCount counts the selected ones */

void cm_UpdatePortraits() {
  char buf[0x100];
  int i;
  AICHAR *c;
  AIWEAPON *w;
  AIOBJ *item;

  if (d2_ClickedId != -1) {
    for (i = 0; i < 6; i++) {
      if (cm_Portraits[i].win != -1 &&
          d2_PointerObj == cm_Portraits[i].portrait) {
        if (d2_Objs[cm_Portraits[i].portrait].checked != 0)
          cm_Portraits[i].c->selected = 1;
        else
          cm_Portraits[i].c->selected = 0;
      }
    }
  }
  d2_ClearPointerItems();
  cm_SelectedCount = 0;
  for (i = 0; i < 6; i++) {
    if (cm_Portraits[i].win == -1)
      continue;
    c = cm_Portraits[i].c;
    if (c->scene->obj->type == 1) {
      d2_EnableObject(d2_Wins[cm_Portraits[i].win].parent, 0);
      d2_EnableObject(d2_Wins[cm_Portraits[i].frame].parent, 0);
      continue;
    }
    if (c->selected != 0) {
      d2_AddPointerItem(c->picture, 1);
      d2_SetObjValue(cm_Portraits[i].portrait, 1);
      cm_SelectedCount++;
    } else
      d2_SetObjValue(cm_Portraits[i].portrait, 0);
    txt_Format(buf, (intptr_t)"%1N1 %i%", cm_Portraits[i].c->id,
               (int)(gm_HealthRatio(cm_Portraits[i].c) * 100.0));
    d2_SetObjText(cm_Portraits[i].text, buf);
    w = cm_CharWeaponAny(cm_Portraits[i].c);
    if (w == 0 || w->id == 0)
      continue;
    if (cm_Portraits[i].weaponPic == -1 ||
        d2_Objs[cm_Portraits[i].weaponPic].pic != w->id + 0xdf) {
      if (cm_Portraits[i].weaponPic != -1)
        d2_RemoveObj(cm_Portraits[i].weaponPic);
      d2_LastWindow = cm_Portraits[i].win;
      cm_Portraits[i].weaponPic =
          d2_WinOpenPic(0x54, 0xf, w->id + 0xdf, d2_LastWindow);
      d2_ScaleObject(cm_Portraits[i].weaponPic, -2);
    }
    if (cm_Portraits[i].countText != -1 && (w->kind == 1 || w->kind == 2)) {
      item = cm_CharWeaponItem(cm_Portraits[i].c);
      if (item != 0) {
        sprintf(buf, "%i", item->usesLeft);
        d2_SetObjText(cm_Portraits[i].countText, buf);
      } else if (cm_Portraits[i].countText != -1)
        d2_SetObjText(cm_Portraits[i].countText, ch_EmptyName);
    } else if (cm_Portraits[i].countText != -1)
      d2_SetObjText(cm_Portraits[i].countText, ch_EmptyName);
  }
}

/* 0x4cfc10, builds the portrait boxes cm_Portraits (at most 6, 0x80 pixels apart) for the characters of
   ai_SceneChars that cm_CutChar sees (0x800): a frame picture, a window with the weapon picture and its uses left text
   (when the character has a weapon), the portrait (checkable), the name text and the value bar of skill 3; then
   cm_UpdatePortraits fills them */

void cm_BuildPortraits() {
  AICHAR *c;
  AIWEAPON *w;
  int i, n, x;
  float t;

  for (i = 0; i < 6; i++) {
    cm_Portraits[i].win = -1;
    cm_Portraits[i].portrait = -1;
    cm_Portraits[i].unused0c = -1;
    cm_Portraits[i].text = -1;
    cm_Portraits[i].countText = -1;
    cm_Portraits[i].weaponPic = -1;
  }
  x = 0;
  for (i = 0, n = 0; i < 31 && n < 6; i++) {
    c = ai_SceneChars[i];
    if (c == 0)
      continue;
    if (!(ai_LedSelectBits(cm_CutChar->id, c) & 0x800))
      continue;
    cm_Portraits[n].frame = d2_CreatePicObj(x + 0x18, 0xf, 0x5da);
    cm_Portraits[n].win = d2_CreateWindow(x, 0, 0x80, 0x4b, 0x110);
    w = cm_CharWeapon(c);
    if (w != 0 && w->id != 0) {
      cm_Portraits[n].weaponPic =
          d2_WinOpenPic(0x54, 0xf, w->id + 0xdf, d2_LastWindow);
      d2_ScaleObject(cm_Portraits[n].weaponPic, -2);
      cm_Portraits[n].countText =
          d2_CreateWinText(0x54, 0x26, ch_EmptyName, d2_LastWindow);
      d2_Objs[cm_Portraits[n].countText].font = 0x54;
      d2_Objs[cm_Portraits[n].countText].w = 0x18;
      d2_Objs[cm_Portraits[n].countText].centred = 1;
    }
    cm_Portraits[n].c = c;
    d2_Wins[cm_Portraits[n].win].mt = 0;
    d2_Wins[cm_Portraits[n].win].font = 0x54;
    cm_Portraits[n].portrait =
        d2_WinOpenPic(0x28, 0x11, c->picture, d2_LastWindow);
    d2_Objs[cm_Portraits[n].portrait].checkable = 1;
    cm_Portraits[n].text = d2_CreateWinText(0, 0, ch_EmptyName, d2_LastWindow);
    d2_Objs[cm_Portraits[n].text].font = 0x54;
    d2_Objs[cm_Portraits[n].text].w = 0x80;
    d2_Objs[cm_Portraits[n].text].centred = 1;
    t = gm_SkillPoints(c, 3);
    sv_ValueBar(0x24, 0x41, (int)t, 0x4df);
    x += 0x80;
    n++;
  }
  cm_UpdatePortraits();
}
/* 0x4cfe70, removes the portrait boxes cm_Portraits[6] again */

void cm_ClosePortraits() {
  int i;
  int t;

  for (i = 0; i < 6; i++) {
    if (cm_Portraits[i].win != -1) {
      d2_RemoveWindow(cm_Portraits[i].win);
      t = cm_Portraits[i].frame;
      cm_Portraits[i].win = -1;
      d2_RemoveObj(t);
    }
  }
}
/* 0x4cfeb0, the click on an own character object (ai_PickedObject, D3OBJECT.kind 2) while characters are selected: the first
   selected standing scene character is marked (AICHAR.selected) and gets the click comment "_ARBEITER_KOMMENTARE_KLICK" from
   the attacker's or the defender's voice bank (by its building); the picked object becomes ai_ClickedObject. */

void cm_ClickSceneChar() {
  AICHAR *t = cm_CutChar;
  AICHAR *c, *o, **pp;
  D3OBJECT *sel;

  ai_ClickedObject = 0;
  for (pp = ai_SceneChars; (int)pp < (int)(ai_SceneChars + 32); pp++) {
    c = *pp;
    if (c != 0 && c->selected != 0 && (ai_LedSelectBits(t->id, c) & 0x800) &&
        c->scene != 0 && c->health != 0)
      break;
  }
  if (dm_L.lup != 0 && d2_PointerObj == -1) {
    sel = ai_PickedObject;
    if (sel != 0 && sel->kind == 2) {
      o = sel->owner;
      if ((ai_LedSelectBits(t->id, o) & 0x800) && kb_Down[0x36] == 0 &&
          (c == 0 || cm_OtherBuilding(c, o) == 0)) {
        cm_ClearMarks();
        o->selected = 1;
        if (o->side == cm_FightAttacker)
          snd_QueueVoice(o->id, cm_AttackerClickVoices,
                         "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
        else
          snd_QueueVoice(o->id, cm_DefenderClickVoices,
                         "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
        sel = ai_PickedObject;
      }
    }
    ai_ClickedObject = sel;
  }
}
/* 0x4cffd0, orders the character c of the cutscene record rec (CMCUTINFO) to attack: its entry (cm_CutEntrySlot, b0c and
   held cleared there) is copied with state 2 and tgt's netId, for the weapon kinds 0x15e / 0x160 also the cell (x, z) of
   tgt's body, for 0x174 / 0x176 that cell alone, and sent as message 0x50 (cm_SendCutEntry); held is set for the
   formation types 1 .. 3. A weapon of those kinds with no uses left shows its txt_WeaponEmpty text instead. -1 when c,
   tgt, its body or the entry is missing; else the original returns nothing (eax as the last call left it) */

int cm_OrderAttack(CMCUTINFO *rec, AICHAR *c, AICHAR *tgt, int x, int z) {
  D3SM *hmap = d3_DefaultScene->hmap;
  AICHAR *ch = c;
  AICHAR *t = tgt;
  AIWEAPON *w;
  AIOBJ *item;
  CMCUTENTRY *e;
  CMCUTENTRY order;
  float y;

  if (ch == 0)
    return -1;
  w = cm_CharWeapon(c);
  if (t == 0 || t->scene->obj == 0)
    return -1;
  if (d3_GetHeightAt(hmap, &t->scene->obj->pos, &x, &z, &y) == 0)
    return -1;
  e = cm_CutEntrySlot(rec, c);
  if (e == 0)
    return -1;
  e->held = 0;
  e->b0c = 0;
  memcpy(&order, e, sizeof(order));
  if (w == 0 || w->id == 0x154 || w->id == 0x156 || w->id == 0x158 ||
      w->id == 0x16e || w->id == 0x172 || w->id == 0) {
    order.charId = ch->netId;
    order.stateArg = t->netId;
    order.state = 2;
  } else if (w->id == 0x15e || w->id == 0x160) {
    item = cm_CharWeaponItem(c);
    if (item != 0 && item->usesLeft <= 0) {
      sv_SetStatusText(txt_Ptrs[TXT_WEAPON_EMPTY_15E]);
      return -1;
    }
    order.charId = ch->netId;
    order.stateArg = t->netId;
    order.x = x;
    order.z = z;
    order.state = 2;
  } else if (w->id == 0x174) {
    item = cm_CharWeaponItem(c);
    if (item != 0 && item->usesLeft <= 0) {
      sv_SetStatusText(txt_Ptrs[TXT_WEAPON_EMPTY_174]);
      return -1;
    }
    order.charId = ch->netId;
    order.stateArg = 0;
    order.x = x;
    order.z = z;
    order.state = 2;
  } else if (w->id == 0x176) {
    item = cm_CharWeaponItem(c);
    if (item != 0 && item->usesLeft <= 0) {
      sv_SetStatusText(txt_Ptrs[TXT_WEAPON_EMPTY_176]);
      return -1;
    }
    order.stateArg = 0;
    order.charId = ch->netId;
    order.x = x;
    order.z = z;
    order.state = 2;
  }
  if (ch->formation == 1 || ch->formation == 2 || ch->formation == 3)
    order.held = 1;
  cm_SendCutEntry(rec->playerId, &order);
}
/* 0x4d0200, orders the character c of the cutscene record rec (CMCUTINFO) to flee to the escape object tgt
   ("sp_ESCAPE"): its entry (cm_CutEntrySlot, b0c cleared there) is copied with state 3 and the ground cell of tgt's
   world position in stateArg / x, and sent as message 0x50 (cm_SendCutEntry). -1 when tgt, c or rec is missing or the
   position has no cell; else the original returns nothing (VC6 keeps x, z, y in the dead parameters' slots) */

int cm_OrderEscape(CMCUTINFO *rec, AICHAR *c, D3OBJECT *tgt) {
  D3SM *hmap = d3_DefaultScene->hmap;
  CMCUTENTRY *e;
  CMCUTENTRY order;
  D3VECTOR4 v; /* d3_PointToWorld writes the point and the angle after it */
  int x, z;
  float y;

  if (tgt == 0 || c == 0 || rec == 0)
    return -1;
  d3_PointToWorld(tgt, &tgt->pos, &v.v);
  if (d3_GetHeightAt(hmap, &v.v, &x, &z, &y) == 0)
    return -1;
  e = cm_CutEntrySlot(rec, c);
  if (e == 0)
    return -1;
  e->b0c = 0;
  memcpy(&order, e, sizeof(order));
  order.charId = c->netId;
  order.stateArg = x;
  order.state = 3;
  order.x = z;
  cm_SendCutEntry(rec->playerId, &order);
}
/* 0x4d02d0, an order kind 4 (the walk to a named dummy) for the character c with the name of the object tgt
   (CMCUTENTRY.dummy) and its ground cell (cellX, cellZ); returns 1, 0 when the point is not on the ground. */

int cm_OrderConquer(CMCUTINFO *rec, AICHAR *c, D3OBJECT *tgt) {
  D3SM *sc = d3_DefaultScene->hmap;
  CMCUTENTRY *q;
  D3VECTOR4 v;
  int x, z;
  float h;

  cm_CharWeapon(c);
  d3_PointToWorld(tgt, &tgt->pos, &v.v);
  if ((char)d3_GetHeightAt(sc, &v.v, &x, &z, &h) == 0)
    return 0;
  q = cm_CutEntrySlot(rec, c);
  q->b0c = 0;
  strcpy(q->dummy, tgt->name);
  q->charId = c->netId;
  q->state = 4;
  q->cellX = x;
  q->cellZ = z;
  return 1;
}
/* 0x4d0380, an order kind 6 (walk to the goods store) for the character c: its entry (cm_CutEntrySlot, b0c cleared
   there) is copied with state 6, the name of the object tgt (dummy), the ground cell of tgt's point (d3_GetHeightAt's x / z)
   as storeX / storeZ, and sent as message 0x50 (cm_SendCutEntry, whose result it returns). -1 when the point is not on
   the ground or the character c is in a job (AICHAR.v1ac). */

int cm_OrderWare(CMCUTINFO *rec, AICHAR *c, D3OBJECT *tgt) {
  D3SM *hmap = d3_DefaultScene->hmap;
  CMCUTENTRY *q;
  CMCUTENTRY order;
  D3VECTOR4 v;
  int x, z;
  float y;

  cm_CharWeapon(c);
  d3_PointToWorld(tgt, &tgt->pos, &v.v);
  if (d3_GetHeightAt(hmap, &v.v, &x, &z, &y) == 0 || c->v1ac != 0)
    return -1;
  q = cm_CutEntrySlot(rec, c);
  q->b0c = 0;
  memcpy(&order, q, sizeof(order));
  order.charId = c->netId;
  order.state = 6;
  strcpy(order.dummy, tgt->name);
  order.storeX = (unsigned char)x;
  order.storeZ = (unsigned char)z;
  return cm_SendCutEntry(rec->playerId, &order);
}
/* 0x4d0460, orders the character c of the cutscene record rec (CMCUTINFO) to the best ground cell within 8 rings of
   its own (cm_BestCellNear, formation type 4): its entry (cm_CutEntrySlot, b0c cleared there) is copied with state 7 and
   that cell in stateArg / x, and sent as message 0x50 (cm_SendCutEntry). -1 when c's body is not on the ground or no
   cell is found; else cm_SendCutEntry's result (VC6 keeps x in c's dead parameter slot) */

int cm_OrderToBestCell(CMCUTINFO *rec, AICHAR *c) {
  D3SM *hmap = d3_DefaultScene->hmap;
  AICHAR *ch = c;
  CMCUTENTRY *e;
  CMCUTENTRY order;
  int x, z;
  float y;

  if (d3_GetHeightAt(hmap, &ch->scene->obj->pos, &x, &z, &y) != 0 &&
      cm_BestCellNear(c, x, z, 8, &x, &z) != 0) {
    e = cm_CutEntrySlot(rec, c);
    e->b0c = 0;
    memcpy(&order, e, sizeof(order));
    order.charId = ch->netId;
    order.stateArg = x;
    order.state = 7;
    order.x = z;
    return cm_SendCutEntry(rec->playerId, &order);
  }
  return -1;
}
/* 0x4d0520, the formation type 3's order for the character c: its entry (cm_CutEntrySlot, b0c cleared there) is copied
   with state 8 and no target and sent as message 0x50 (cm_SendCutEntry); case 8 of cm_RunCutOrders then sends fight
   command 6 once the previous order slot is done (the character waits). */

void cm_OrderWait(CMCUTINFO *rec, AICHAR *c) {
  CMCUTENTRY *q;
  CMCUTENTRY order;

  q = cm_CutEntrySlot(rec, c);
  q->b0c = 0;
  memcpy(&order, q, sizeof(order));
  order.charId = c->netId;
  order.state = 8;
  cm_SendCutEntry(rec->playerId, &order);
}

/* 0x4d0570, the order of a mouse click (dm_L.lup) for the character c of the cutscene record rec (CMCUTINFO): on a
   character's body (D3OBJECT.kind 2) an attack (cm_OrderAttack) when it is not in c's building or shift is down; on
   "sp_ESCAPE" cm_OrderEscape, on "sp_CONQUER.." cm_OrderConquer, on "WARE.." cm_OrderWare; with nothing picked the ground
   cell under the pointer (d3sm_Pick) is sent in state 1 (stateArg / x), else TXT_CLICK_NO_GROUND is shown. Returns 1 when
   an order was given */
char cm_OrderClick(CMCUTINFO *rec, AICHAR *c) {
  char ret = 0;
  D3OBJECT *sel;
  AICHAR *o;
  CMCUTENTRY *e;
  CMCUTENTRY order;
  int x, z;
  D3SM *map;

  if (dm_L.lup != 0) {
    sel = ai_ClickedObject;
    if (sel != 0) {
      if (sel->kind == 2) {
        o = sel->owner;
        if (cm_OtherBuilding(c, o) != 0 || kb_Down[DIK_RSHIFT] != 0) {
          if (cm_OrderAttack(rec, c, o, 0, 0) != -1)
            ret = 1;
        }
      } else if (strcmp(sel->name, "sp_ESCAPE") == 0) {
        cm_OrderEscape(rec, c, sel);
        ret = 1;
      } else if (strncmp(sel->name, "sp_CONQUER", 10) == 0) {
        cm_OrderConquer(rec, c, ai_ClickedObject);
        ret = 1;
      } else if (strncmp(ai_ClickedObject->name, "WARE", 4) == 0) {
        cm_OrderWare(rec, c, ai_ClickedObject);
        ret = 1;
      }
    } else {
      map = d3_DefaultScene->hmap;
      if (d3sm_Pick(map, dm_L.x + 0x1a, dm_L.y + 0x1a, &x, &z)) {
        e = cm_CutEntrySlot(rec, c);
        e->b0c = 0;
        memcpy(&order, e, sizeof(order));
        order.charId = c->netId;
        order.stateArg = x;
        order.state = 1;
        order.x = z;
        cm_SendCutEntry(rec->playerId, &order);
        ret = 1;
      } else
        sv_SetStatusText(txt_Ptrs[TXT_CLICK_NO_GROUND]);
    }
  }
  return ret;
}
/* 0x4d0740, the per-tick mouse handling of the fight for the cutscene record rec: the left button held starts the
   rubber band (sv_StartBand, the marks cleared first), its release ends it; a click gives every marked scene character
   (AICHAR.selected) that cm_CutChar may command (ai_LedSelectBits 0x800) and that is alive its order (cm_OrderClick),
   answered with the voice "_K_C2C_BEFEHL_ERHALTEN" of its side, and drops the mark. Then the marked characters' bodies
   are greyed (d3t_SetGrey, D3OBJECT.stateFlags bit 2) and the unmarked ones restored, unless the body is fading; a
   right click clears every mark (cm_ClearMarks) */

void cm_FightMouse(CMCUTINFO *rec) {
  AICHAR **pp;
  AICHAR *c;

  if (dm_L.lhold == 0 && sv_BandActive != 0)
    sv_EndBand();
  if (dm_L.lhold != 0 && dm_L.rdown == 0) {
    if (sv_BandActive == 0 && di_Absolute != 0 && d2_PointerObj == -1) {
      cm_ClearMarks();
      sv_StartBand();
    }
  } else if (dm_L.lup != 0) {
    for (pp = ai_SceneChars; (int)pp < (int)(ai_SceneChars + 32); pp++) {
      c = *pp;
      if (c != 0 && c->selected != 0 &&
          (ai_LedSelectBits(cm_CutChar->id, c) & 0x800) && c->scene != 0 &&
          c->health != 0) {
        if (cm_OrderClick(rec, c)) {
          if (cm_CutChar == cm_FightAttacker)
            snd_PlayVoice(c->id, cm_AttackerOrderVoices,
                          "_K_C2C_BEFEHL_ERHALTEN", -1);
          else
            snd_PlayVoice(c->id, cm_DefenderOrderVoices,
                          "_K_C2C_BEFEHL_ERHALTEN", -1);
          c->selected = 0;
        }
      }
    }
  }
  for (pp = ai_SceneChars; (int)pp < (int)(ai_SceneChars + 32); pp++) {
    c = *pp;
    if (c != 0 && !(c->scene->flags.bytes.lo & 0x40)) {
      if (c->selected) {
        if (!(c->scene->obj->stateFlags & 2))
          d3t_SetGrey(c->scene->obj, 1);
      } else if ((c->scene->obj->stateFlags & 2) == 2)
        d3t_SetGrey(c->scene->obj, 0);
    }
  }
  if (dm_L.rup != 0)
    cm_ClearMarks();
}
/* 0x4d08c0, clears the marks (AICHAR.selected) of the 32 cm_Fighters and the grey highlight of their bodies
   (D3OBJECT.stateFlags bit 2: d3t_SetColor black), then the pointer items, the character info windows and the fight
   view */

void cm_ClearMarks(void) {
  AICHAR *r;
  D3OBJECT *body;

  for (r = cm_Fighters; (intptr_t)&r->scene < (intptr_t)&cm_Fighters[32].scene;
       r++) {
    if (r->selected != 0)
      r->selected = 0;
    if (r->scene != 0) {
      body = r->scene->obj;
      if ((body->stateFlags & 2) == 2)
        d3t_SetColor(body, 0, 0, 0);
    }
  }
  d2_ClearPointerItems();
  cm_CloseCharInfoWins();
  cm_CloseFightView();
}
/* 0x4d0920, the fight copy of the character with the netId id: the first free record of cm_Fighters (id 0xffff; 0 when
   all 32 are taken) gets a copy of the AICHAR, without its object v1ac and scene character, and a new scene character
   (gm_CreateCharModel at the dummy object, path type 4, flag 0x8000) with its hand object, the speed of its weapon
   (AIWEAPON.speed * 2/7) and "cmb_<netId>" as its body's name; the weapon item's uses are reset to 6 (kind 2) or 15 */

struct AICHAR *cm_AddFighter(int id, char *dummy) {
  AICHAR *c;
  AIWEAPON *w;
  AIOBJ *item;
  int i;

  c = gm_FindChar(id);
  for (i = 0; i < 32; i++) {
    if (cm_Fighters[i].id == 0xffff) {
      memcpy(&cm_Fighters[i], c, sizeof(AICHAR));
      cm_Fighters[i].fightWare = 0;
      cm_Fighters[i].scene = 0;
      gm_CreateCharModel(&cm_Fighters[i], d3_CurrentScene, 0, 0, 0, dummy);
      cm_Fighters[i].scene->pathType = 4;
      cm_Fighters[i].scene->flags.bytes.hi |= 0x80;
      cm_UpdateHandObject(&cm_Fighters[i]);
      w = cm_CharWeapon(c);
      cm_Fighters[i].scene->walkSpeed = w->speed * 0.2857142857142857;
      sprintf(cm_Fighters[i].scene->obj->name, "cmb_%i", cm_Fighters[i].netId);
      item = cm_CharWeaponItem(c);
      if (item != 0) {
        if (w->kind == 2)
          item->usesLeft = 6;
        else
          item->usesLeft = 0xf;
      }
      return &cm_Fighters[i];
    }
  }
  return 0;
}
/* 0x4d0a30, fills ai_SceneChars (32 pointers, cleared first) with the cm_Fighters whose scene character is in the scene
   d3_DefaultScene, in record order; at most 31 are taken */

void cm_CollectSceneChars(void) {
  AICHAR **p;
  AICHAR *r;

  memset(ai_SceneChars, 0, sizeof(ai_SceneChars));
  p = ai_SceneChars;
  for (r = cm_Fighters; (intptr_t)&r->scene < (intptr_t)&cm_Fighters[32].scene;
       r++) {
    if ((intptr_t)p >= (intptr_t)&ai_SceneChars[31])
      break;
    if (r->scene != 0 && r->scene->scene == d3_DefaultScene)
      *p++ = r;
  }
}
/* 0x4d0a80, the object walk's callback for the flag dummies: "dummy_sp_ESCAPE" gets a flag object "ub_FLUCHTFLAGGE"
   (named "sp_ESCAPE", the animation "anim_FLUCHTFLAGGE.baf"), "dummy_CONQUER" one "ub_CONQUER" (named
   "sp_CONQUER_<n>"), both kind 4 with mask 1 and kept in cm_FlagObjects[cm_FlagObjectCount++]; returns 1. */

char cm_CreateDummyFlag(D3OBJECT *obj, void *ctx) {
  D3OBJECT *r;
  D3VECTOR4 pos;
  D3VECTOR rot;

  if (strstr(obj->name, "dummy_sp_ESCAPE") != 0) {
    rot.x = 0;
    rot.y = 0;
    rot.z = 0;
    d3_PointToWorld(obj, &obj->pos, &pos.v);
    r = d3_CreateObject(0, &pos.v, &rot, "ub_FLUCHTFLAGGE");
    cm_FlagObjects[cm_FlagObjectCount] = r;
    strcpy(r->name, "sp_ESCAPE");
    cm_FlagObjects[cm_FlagObjectCount]->kind = 4;
    cm_FlagObjects[cm_FlagObjectCount]->mask = 1;
    cm_FlagObjects[cm_FlagObjectCount]->stateFlags =
        (cm_FlagObjects[cm_FlagObjectCount]->stateFlags & 0xf7) | 4;
    cm_FlagObjects[cm_FlagObjectCount]->stateFlags |= 0x40;
    d3t_PlayAnim(cm_FlagObjects[cm_FlagObjectCount],
                 "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
    cm_FlagObjectCount++;
    return 1;
  }
  if (strstr(obj->name, "dummy_CONQUER") != 0) {
    rot.x = 0;
    rot.y = 0;
    rot.z = 0;
    d3_PointToWorld(obj, &obj->pos, &pos.v);
    r = d3_CreateObject(0, &pos.v, &rot, "ub_CONQUER");
    cm_FlagObjects[cm_FlagObjectCount] = r;
    d3if_SelectTextureSet(r, r->info, 1, 1);
    sprintf(cm_FlagObjects[cm_FlagObjectCount]->name, "sp_CONQUER_%i",
            cm_FlagObjectCount);
    cm_FlagObjects[cm_FlagObjectCount]->owner = 0;
    cm_FlagObjects[cm_FlagObjectCount]->kind = 4;
    cm_FlagObjects[cm_FlagObjectCount]->mask = 1;
    cm_FlagObjects[cm_FlagObjectCount]->stateFlags =
        (cm_FlagObjects[cm_FlagObjectCount]->stateFlags & 0xf7) | 4;
    cm_FlagObjectCount++;
  }
  return 1;
}
/* 0x4d0ca0, walks the objects of the scene with the callback 0x4d0a80 (the flag dummies) */

void cm_PlaceFlagObjects() {
  cm_FlagObjectCount = 0;
  d3_ForEachObject(d3_DefaultScene, 0, 0x100, cm_CreateDummyFlag, 0);
}
/* 0x4d0cd0, the first free (-1) netId slot of the 16 of a fight party's defenders (G28REC.fight), else -1 */

int cm_FreeNetIdSlot(int *a) {
  int i;

  for (i = 0; i < 16; i++) {
    if (a[i] == -1)
      return i;
  }
  return -1;
}

/* arms the next guard: takes the first free slot i of rec, the character ai_KindBChars[i] gives up its weapons and
   gets the item ITEM, loses its v024 health and its skill sk83 is set to SKILL (a field delta of the character).
   The original repeats this code inline (the four copies of 0x4d0cf0 reload ai_KindBChars[i] each time) */
#define CM_ARM_GUARD(ITEM, SKILL)                                              \
  i = cm_FreeNetIdSlot(rec->fight.defenders);                                  \
  rec->fight.defenders[i] = ai_KindBChars[i]->netId;                           \
  cm_DiscardWeapons(ai_KindBChars[i]);                                         \
  cm_SendExSellObject(ai_KindBChars[i]->netId, -1, ITEM, 1, ai_OwnPlayer, 0);  \
  gm_AddHealth(ai_KindBChars[i]->id, -ai_KindBChars[i]->v024);                 \
  skill = SKILL;                                                               \
  cm_BeginFieldBlock(ai_KindBChars[i], ai_KindBChars[i]->netId);               \
  cm_AddFieldDelta(                                                            \
      1, 1,                                                                    \
      (unsigned short)((char *)&ai_KindBChars[i]->sk83 - cm_FieldObject),      \
      &skill);                                                                 \
  cm_SendFieldDeltas()

/* 0x4d0cf0, arms the guards of the town gate event: kind 1 two guards with the item 0x156 (sk83 = 0xa8), kinds 2 / 3
   one with 0x158 and one with 0x160 (sk83 = 0xd2); a nonzero kind is kept in rec->fight.escort (the fight party of the ambush,
   he_RunAmbush; reasoned: the items replace
   the weapons cm_DiscardWeapons sends away, the characters are the kind 0xb ones of ai_KindBChars) */
void ai_ArmGateGuards(G28REC *rec, unsigned char kind) {
  unsigned char skill;
  int i;

  if (kind != 0)
    rec->fight.escort = kind;
  if (kind == 1) {
    CM_ARM_GUARD(0x156, 0xa8);
    CM_ARM_GUARD(0x156, 0xa8);
  } else if (kind == 2 || kind == 3) {
    CM_ARM_GUARD(0x158, 0xd2);
    CM_ARM_GUARD(0x160, 0xd2);
  }
}
/* 0x4d0f80, the object walk's callback: an object of kind 3 gets its mask (D3OBJECT.mask) cleared; returns 1 */

char cm_ClearKind3MaskCB(D3OBJECT *o) {
  if (o->kind == 3)
    o->mask = 0;
  return 1;
}

/* the voice banks of a fight side: KIND is the role's suffix (DIEBE thieves, RAEUBER robbers, SOELDNER mercenaries) */
#define CM_LOAD_VOICES(SIDE, KIND)                                             \
  cm_##SIDE##ClickVoices =                                                     \
      snd_LoadVoiceBank("ARBEITER_KOMMENTARE_KLICK_" KIND ".sbf", 0);          \
  cm_##SIDE##AttackVoices =                                                    \
      snd_LoadVoiceBank("K_C2C_ANGRIFF_" KIND ".sbf", 0);                      \
  cm_##SIDE##OrderVoices =                                                     \
      snd_LoadVoiceBank("K_C2C_BEFEHL_ERHALTEN_" KIND ".sbf", 0);              \
  cm_##SIDE##TauntVoices = snd_LoadVoiceBank("K_C2C_HOHN_" KIND ".sbf", 0);    \
  cm_##SIDE##PainVoices = snd_LoadVoiceBank("K_C2C_SCHMERZ_" KIND ".sbf", 0)

/* 0x4d0fa0, sets up the fight scene for the fight record rec: the scenario "Kampfszenario_<place>.ed3" by the flags or
   the type of the defender's building (cm_LoadEventScene; a robbers' camp gets a 15 cells wide border), the fight
   tables cleared, the weapon sounds (kampf\*.sbf), the voices of both sides by their roles (cm_FightRole), the boots
   object, the attackers placed at "dummy_OFFENSE_ENTRY" and the defenders (walking 1.2 times as fast) at
   "dummy_DEFENSE_ENTRY", the scene characters collected, the carts "ob_KARREN_<size>_KAMPF.ogr" put at their
   dummies "dummy_KARREN_0<n>" with up to three of their goods shown as "WARE_0<n>" (shuffled), the border cells of the
   height map set to the ground type 0xd and cm_DefenseFactor from the defender's building */
void cm_SetupFightScene(G28REC *rec) {
  char name[0x100];
  D3VECTOR4 pos;
  signed char order[9];
  AIOBJ *goods[3];
  int k, n, border, i;
  int *cart;
  AIBLD *b;
  AIOBJ *obj, *load, *w;
  D3OBJECT *o;
  AICHAR *r;
  D3SM *sc;
  AIBTYPE *t;
  signed char *p;

  border = 10;
  if (rec->fight.flags & 1) {
    if (rec->fight.flags & 8)
      cm_LoadEventScene("Kampfszenario_STADT.ed3");
    else
      cm_LoadEventScene("Kampfszenario_BERGPASS.ed3");
  } else if (rec->fight.flags & 4) {
    cm_LoadEventScene("Kampfszenario_BERGPASS.ed3");
  } else {
    b = gm_BuildQuery(1, 1, rec->thing);
    if (gm_IsHomeType(b) != 0) {
      t = &ai_BTypes[b->type];
      if (t->kind == 0x10) {
        cm_LoadEventScene("Kampfszenario_RAEUBERLAGER.ed3");
        border = 15;
      } else if (t->kind == 0xc)
        cm_LoadEventScene("Kampfszenario_STEINBRUCH.ed3");
      else if (t->kind == 0xb)
        cm_LoadEventScene("Kampfszenario_WALDSTUECK.ed3");
      else if (t->kind == 0xd)
        cm_LoadEventScene("Kampfszenario_MINE.ed3");
    } else if (ai_BTypes[b->type].kind == 4) {
      if (ai_BTypes[b->type].level == 1)
        cm_LoadEventScene("Kampfszenario_SCHMUGGLERLOCH.ed3");
      else if (ai_BTypes[b->type].level == 2)
        cm_LoadEventScene("Kampfszenario_UNTERSCHLUPF.ed3");
      else if (ai_BTypes[b->type].level == 3)
        cm_LoadEventScene("Kampfszenario_DIEBESGILDE.ed3");
    } else if (ai_BTypes[b->type].kind == 0x13) {
      if (ai_BTypes[b->type].level == 1)
        cm_LoadEventScene("Kampfszenario_STADTWACHE_KLEIN.ed3");
      else if (ai_BTypes[b->type].level == 2)
        cm_LoadEventScene("Kampfszenario_STADTWACHE_MITTEL.ed3");
      else if (ai_BTypes[b->type].level == 3)
        cm_LoadEventScene("Kampfszenario_STADTWACHE_GROSS.ed3");
    }
  }
  sc = d3_DefaultScene->hmap;
  cm_ApplySeason();
  if (d3_Terrain != 0) {
    d3_Scenes[d3_CurrentScene].sky = d3_Scenes[0].sky;
    d3_Sky = d3_Scenes[0].sky;
    sv_UpdateWeather();
    d3sky_Init(d3_Sky, 1);
  }
  memset(cm_CharInfoWins, -1, 32 * sizeof(int));
  for (i = 0; i < 16; i++) {
    cm_DamagePops[i].h = -1;
    cm_DamagePops[i].v = 0;
    cm_DamagePops[i].c = 0;
  }
  memset(cm_FightScratch, 0, sizeof(cm_FightScratch));
  memset(cm_Bombs, 0, sizeof(cm_Bombs));
  memset(cm_Grenades, 0, sizeof(cm_Grenades));
  memset(cm_Fighters, 0, sizeof(cm_Fighters));
  for (i = 0; i < 32; i++)
    cm_Fighters[i].id = 0xffff;
  for (i = 0; i < 6; i++)
    cm_Portraits[i].win = -1;
  cm_FightSounds = sb_LoadSampleBank("kampf.sbf", 1);
  cm_CrossbowSounds = sb_LoadSampleBank("kampf\\armbrust.sbf", 1);
  cm_BombSounds = sb_LoadSampleBank("kampf\\bombeundtopf.sbf", 1);
  cm_DaggerSounds = sb_LoadSampleBank("kampf\\dolche.sbf", 1);
  cm_PistolSounds = sb_LoadSampleBank("kampf\\pistole.sbf", 1);
  cm_SwordSounds = sb_LoadSampleBank("kampf\\schwerter.sbf", 1);
  b = gm_BuildQuery(1, 1, rec->fight.attackerBld);
  if (b != 0)
    cm_AttackerRole = cm_FightRole(b);
  if (cm_AttackerRole == 2) {
    CM_LOAD_VOICES(Attacker, "DIEBE");
  } else if (cm_AttackerRole == 1) {
    CM_LOAD_VOICES(Attacker, "RAEUBER");
  } else if (cm_AttackerRole == 0) {
    CM_LOAD_VOICES(Attacker, "SOELDNER");
  }
  b = gm_BuildQuery(1, 1, rec->thing);
  if (b != 0)
    cm_DefenderRole = cm_FightRole(b);
  if (cm_DefenderRole != cm_AttackerRole) {
    if (cm_DefenderRole == 2) {
      CM_LOAD_VOICES(Defender, "DIEBE");
    } else if (cm_DefenderRole == 1) {
      CM_LOAD_VOICES(Defender, "RAEUBER");
    } else if (cm_DefenderRole == 0) {
      CM_LOAD_VOICES(Defender, "SOELDNER");
    }
  } else {
    cm_DefenderClickVoices = cm_AttackerClickVoices;
    cm_DefenderAttackVoices = cm_AttackerAttackVoices;
    cm_DefenderOrderVoices = cm_AttackerOrderVoices;
    cm_DefenderTauntVoices = cm_AttackerTauntVoices;
    cm_DefenderPainVoices = cm_AttackerPainVoices;
  }
  cm_BootsObject = d3io_LoadObjectRef("ub_STIEFEL", "ub_STIEFEL");
  if (sc == 0) {
    d3_DefaultScene->hmap =
        d3sm_Create(d3_Terrain, d3_DefaultScene->mapSize, 2);
    sc = d3_DefaultScene->hmap;
  }
  cm_FightCellScale = sc->cell.x * 1.1;
  sv_ScrollSpeed = 0.15f;
  sv_CameraEaseOn = 0;
  cm_FightRecord = rec;
  cm_PlaceFlagObjects();
  cm_FightAttacker = gm_FindChar(rec->members[0]);
  cm_FightDefender = gm_FindChar(rec->members[1]);
  if (ai_Chars[ai_PlayerId].netId == cm_FightOwner && (rec->fight.flags & 1)) {
    cm_BeginSendGroup();
    for (i = 0; i < 3; i++) {
      if (rec->fight.carts[i] != -1)
        cm_SendExSellObject(-2, -1, 0x154, 1, ai_OwnPlayer, 0);
    }
    cm_EndSendGroup();
    if (cm_SendGroupState() == 0) {
      do
        sv_PumpNet();
      while (cm_SendGroupState() == 0);
    }
  }
  for (i = 0; i < 16; i++) {
    if (rec->fight.attackers[i] != -1) {
      r = cm_AddFighter(rec->fight.attackers[i], "dummy_OFFENSE_ENTRY");
      r->side = cm_FightAttacker; /* in a fight: the side's leader */
      if (r->scene != 0)
        d3if_SelectTextureSet(r->scene->obj, r->scene->obj->info, 5, 1);
    }
  }
  for (i = 0; i < 16; i++) {
    if (rec->fight.defenders[i] != -1) {
      r = cm_AddFighter(rec->fight.defenders[i], "dummy_DEFENSE_ENTRY");
      r->side = cm_FightDefender;
      r->scene->walkSpeed *= 1.2;
      if (r->scene != 0)
        d3if_SelectTextureSet(r->scene->obj, r->scene->obj->info, 4, 1);
    }
  }
  d3_ForEachObject2(d3_DefaultScene, 0, 0xc0,
                    (void (*)(D3OBJECT *))cm_ClearKind3MaskCB);
  memset(ai_SceneChars, 0, sizeof(ai_SceneChars));
  n = 0;
  for (i = 0; i < 32; i++) {
    if (cm_Fighters[i].id != 0xffff && cm_Fighters[i].scene != 0 &&
        cm_Fighters[i].scene->scene == d3_DefaultScene)
      ai_SceneChars[n++] = &cm_Fighters[i];
  }
  for (i = 0; i < 9; i++) {
    sprintf(name, "WARE_0%i", i + 1);
    o = d3_FindObject(0, 0x40, 0, name);
    if (o != 0)
      d3if_Show(o, 0);
  }
  for (i = 0, cart = rec->fight.carts; i < 3; i++, cart++) {
    goods[0] = 0;
    goods[1] = 0;
    goods[2] = 0;
    gm_ShuffledBytes(9, (unsigned char *)order);
    sprintf(name, "dummy_KARREN_0%i", i + 1);
    o = d3_FindObject(0, 0x100, 0, name);
    if (o != 0) {
      if (*cart != -1) {
        obj = gm_Query(0, 2, 7, 1, *cart);
        if (obj == 0) {
          gm_FindObjectInst(*cart);
          *cart = -1;
          continue;
        }
        load = gm_Query(obj->list, 1, 0, 0x1dd);
        n = 0;
        for (w = gm_Query(load->list, 1, 5); n < 3 && w != 0;
             w = gm_QueryNext())
          goods[n++] = w;
        d3_PointToWorld(o, &o->pos, &pos.v);
        if (obj->type == 0x134)
          sprintf(name, "%s*ob_KARREN_KLEIN_KAMPF.ogr", ai_DataPath);
        else if (obj->type == 0x135)
          sprintf(name, "%s*ob_KARREN_MITTEL_KAMPF.ogr", ai_DataPath);
        else if (obj->type == 0x136)
          sprintf(name, "%s*ob_KARREN_GROSS_KAMPF.ogr", ai_DataPath);
        o = d3_LoadGroup(name, 0, 0);
        d3_SetObjectPos(o, &pos.v);
        o->owner = obj;
        for (k = 0, p = order; k < 3; k++) {
          sprintf(name, "WARE_0%i", *p++ + 1); /* the shuffled goods places */
          o = d3_FindObject(0, 0xc0, 0, name);
          if (o != 0) {
            if (k > n - 1)
              d3if_Show(o, 0);
            else {
              o->owner = goods[k];
              d3if_Show(o, 1);
              o->mask = 1;
            }
          }
        }
      } else
        d3if_ShowTree(o, 0);
    }
  }
  d3sm_Build(d3_DefaultScene->hmap, d3_Terrain);
  for (i = 0; i < border; i++) {
    for (k = i; k < sc->size; k++) {
      sc->entries[(sc->size - 1) * i + k].type = 0xd;
      sc->entries[(sc->size - i - 1) * sc->size + k].type = 0xd;
      sc->entries[sc->size * k + i].type = 0xd;
      sc->entries[sc->size * (k + 1) - i - 1].type = 0xd;
    }
  }
  if (b != 0)
    cm_DefenseFactor = (float)gm_BuildingSkill(b, 6, 1) + 1.4f;
  else
    cm_DefenseFactor = 1.0f;
}
/* 0x4d1a10, ends the fight scene of the fight record rec (the counterpart of cm_SetupFightScene): fades to black, unloads
   the sound banks and voices (the defender's only when its role differs), deletes the flag objects cm_FlagObjects and
   the boots object; every fighter with a scene character carries the health lost in the fight back to its character
   (gm_AddHealth, not for the kind 0xb ones; only in the own fight or without a network connection) and loses the scene
   character; then the scroll speed, the sky, the scene and the caption are put back */

void cm_EndFightScene(G28REC *rec) {
  AICHAR *k;
  int i;

  cm_FadeToBlack();
  if (cm_PickMarker != 0) {
    d3if_Delete(cm_PickMarker);
    cm_PickMarker = 0;
  }
  sb_UnloadSampleBank(cm_FightSounds);
  sb_UnloadSampleBank(cm_CrossbowSounds);
  sb_UnloadSampleBank(cm_BombSounds);
  sb_UnloadSampleBank(cm_DaggerSounds);
  sb_UnloadSampleBank(cm_PistolSounds);
  sb_UnloadSampleBank(cm_SwordSounds);
  sb_UnloadSampleBank(cm_AttackerClickVoices);
  sb_UnloadSampleBank(cm_AttackerAttackVoices);
  sb_UnloadSampleBank(cm_AttackerOrderVoices);
  sb_UnloadSampleBank(cm_AttackerTauntVoices);
  sb_UnloadSampleBank(cm_AttackerPainVoices);
  if (cm_AttackerRole != cm_DefenderRole) {
    sb_UnloadSampleBank(cm_DefenderClickVoices);
    sb_UnloadSampleBank(cm_DefenderAttackVoices);
    sb_UnloadSampleBank(cm_DefenderOrderVoices);
    sb_UnloadSampleBank(cm_DefenderTauntVoices);
    sb_UnloadSampleBank(cm_DefenderPainVoices);
  }
  for (i = 0; i < cm_FlagObjectCount; i++)
    d3if_Delete(cm_FlagObjects[i]);
  if (cm_BootsObject != 0) {
    d3io_ReleaseObject(cm_BootsObject);
    cm_BootsObject = 0;
  }
  for (i = 0; i < 32; i++) {
    if (cm_Fighters[i].id != 0xffff && cm_Fighters[i].scene != 0) {
      if (rec->host == ai_Chars[ai_PlayerId].netId ||
          net_Conn.s == INVALID_SOCKET) {
        k = gm_FindChar(cm_Fighters[i].netId);
        if (k->kind != 0xb)
          gm_AddHealth(k->id, cm_Fighters[i].v024 - k->v024);
      }
      ch_Delete(cm_Fighters[i].scene);
      cm_Fighters[i].scene = 0;
    }
  }
  sv_ScrollSpeed = 1.0f;
  if (d3_Terrain != 0) {
    d3_Sky = 0;
    d3_Scenes[d3_CurrentScene].sky = 0;
  }
  cm_LeaveEventScene();
  snd_EndSpecialTrack();
  sv_CameraEaseOn = 1;
  d2_CopyCaption(ch_EmptyName);
}
/* 0x4d1c20, places the fighters ids[16] (-1 = none) of one side of the fight (side "OFF" / "DEF") on the ground of the
   scene: a fighter with a ranged weapon (the goods 0x174 0x176 0x15e 0x160) at the next dummy "dummy_<side>_FERN_%02i",
   the others at "dummy_<side>_NAHK_%02i", each on the free cell nearest the dummy's height map cell (ch_FindFreeCell),
   turned the way the dummy faces; stops when a dummy lies off the height map */
void cm_PlaceFighters(int *ids, char *side) {
  int melee, ranged, i;
  int z, cz, cx, x;
  float h;
  D3VECTOR4 pos; /* d3_PointToWorld writes past the vector */
  D3VECTOR dir;
  char name[0x100];
  D3SM *sc;
  AICHAR *c;
  AIWEAPON *weapon;
  D3OBJECT *o;

  ranged = 1;
  melee = 1;
  sc = d3_DefaultScene->hmap;
  for (i = 0; i < 16; i++) {
    if (ids[i] == -1)
      continue;
    c = cm_FindFighter(ids[i]);
    if (c == 0)
      continue;
    weapon = cm_CharWeapon(c);
    if (weapon != 0 && (weapon->id == 0x174 || weapon->id == 0x176 ||
                        weapon->id == 0x15e || weapon->id == 0x160))
      sprintf(name, "dummy_%s_FERN_%02i", side, ranged++);
    else
      sprintf(name, "dummy_%s_NAHK_%02i", side, melee++);
    o = d3_FindObject(0, 0x100, 0, name);
    if (o == 0)
      continue;
    d3_PointToWorld(o, &o->pos, &pos.v);
    if (d3_GetHeightAt(sc, &pos.v, &x, &z, &h) == 0)
      return;
    ch_FindFreeCell(sc, &c->scene->obj->pos, &c->scene->obj->pos, x, z, &cx,
                    &cz, 2, 0);
    d3sm_GetVertex(sc, cx, cz, &pos.v);
    ch_SetPos(c->scene, &pos.v, 1);
    {
      D3VECTOR rot;

      rot.x = 0;
      rot.y = 0;
      rot.z = 0;
      d3_DirToWorld(o, &d3_ZAxis.v, &dir);
      rot.y = d3_VecAngle(&d3_ZAxis.v, &dir);
      d3_SetObjectRot(c->scene->obj, &rot);
    }
  }
}
/* 0x4d1e00, the intro of the fight: a random fight track (when the music is on) and the cutscene "Kampf_Intro_Fluege" */

void cm_FightIntro(char *a) {
  int r;
  EVTSCRIPT *s;

  d2_CutsceneActive = 1;
  if (snd_MusicEnabled != 0) {
    r = util_Random(100);
    if (r < 0x14)
      snd_PlaySpecialTrack("cd2\\Krieg.mp3");
    else if (r < 0x28)
      snd_PlaySpecialTrack("cd1\\RuestetEuch.mp3");
    else if (r < 0x3c)
      snd_PlaySpecialTrack("cd1\\Flucht.mp3");
    else if (r < 0x50)
      snd_PlaySpecialTrack("cd2\\DerSeuchenzug.mp3");
    else
      snd_PlaySpecialTrack("cd2\\AmKuehlenGrabe.mp3");
  }
  sv_FrameMask = 0x7d6c6;
  sv_UpdateWeather();
  sv_UpdateSkyPhase(&ai_Time);
  s = evt_Load("cutscenes\\kampf\\Kampf_Intro_Fluege.esc");
  if (s != 0) {
    evt_RunScript(s);
    cm_WaitEventStop(s->id);
  }
  d2_CutsceneActive = 0;
}
/* 0x4d1eb0, the outro: stops the stream cm_FightAmbient and runs the cutscene "Kampf_outro_flug" */

void cm_FightOutro(char *a) {
  EVTSCRIPT *s;

  if (cm_FightAmbient != 0)
    msx_StopAmbient(cm_FightAmbient);
  sv_FrameMask = 0x7d6c6;
  d2_CutsceneActive = 1;
  s = evt_Load("cutscenes\\kampf\\Kampf_outro_flug.esc");
  if (s != 0) {
    evt_RunScript(s);
    cm_WaitEventStop(s->id);
  }
  d2_CutsceneActive = 0;
}
/* 0x4d1f10, the enemy of the fighter c to go for: among the scene characters ai_SceneChars of another side
   (cm_OtherBuilding) still alive, the one whose distance to c weighted by its health ratio (gm_HealthRatio) is less
   than the plain distance of the one found before (from 1e6 on); 0 when none. The loops for a weapon of kind 2 and
   for the others are the same */

AICHAR *cm_NearestEnemy(AICHAR *c) {
  float best;
  AICHAR *res;
  int i;
  float d;

  best = 1000000.0f;
  res = 0;
  if (cm_CharWeapon(c)->kind != 2) {
    for (i = 0; i < 32; i++) {
      if (ai_SceneChars[i] != 0 && cm_OtherBuilding(c, ai_SceneChars[i]) != 0 &&
          ai_SceneChars[i]->health != 0) {
        d = cm_CharObjDistXZ(c, ai_SceneChars[i]->scene->obj);
        if (gm_HealthRatio(ai_SceneChars[i]) * d < best) {
          res = ai_SceneChars[i];
          best = d;
        }
      }
    }
  } else {
    for (i = 0; i < 32; i++) {
      if (ai_SceneChars[i] != 0 && cm_OtherBuilding(c, ai_SceneChars[i]) != 0 &&
          ai_SceneChars[i]->health != 0) {
        d = cm_CharObjDistXZ(c, ai_SceneChars[i]->scene->obj);
        if (gm_HealthRatio(ai_SceneChars[i]) * d < best) {
          res = ai_SceneChars[i];
          best = d;
        }
      }
    }
  }
  return res;
}
/* 0x4d2010, the threat at the height map vertex (a, b) for the fighter c: every living enemy within limit of it adds
   70 / its distance, every other living fighter of c's own side takes it off (the sides are the attackers / defenders
   of the fight record cm_FightRecord) */

float cm_ThreatAt(AICHAR *c, int a, int b, float limit) {
  float threat;
  D3VECTOR4 v;
  D3SM *sc;
  int *own, *enemies;
  AICHAR *o;
  float d, dx, dy, dz;
  int i;

  sc = d3_DefaultScene->hmap;
  threat = 0.0f;
  if (c->side == cm_FightAttacker) { /* in a fight: the side's leader */
    own = cm_FightRecord->fight.attackers;
    enemies = cm_FightRecord->fight.defenders;
  } else {
    own = cm_FightRecord->fight.defenders;
    enemies = cm_FightRecord->fight.attackers;
  }
  d3sm_GetVertex(sc, a, b, &v.v);
  for (i = 0; i < 16; i++) {
    if (enemies[i] != -1) {
      o = cm_FindFighter(enemies[i]);
      if (o != 0 && o->health > 0) {
        dx = v.x - o->scene->obj->pos.x;
        dy = v.y - o->scene->obj->pos.y;
        dz = v.z - o->scene->obj->pos.z;
        d = sqrt(dx * dx + dy * dy + dz * dz);
        if (d <= limit)
          threat += 70.0f / d;
      }
    }
  }
  for (i = 0; i < 16; i++) {
    if (own[i] != -1) {
      o = cm_FindFighter(own[i]);
      if (o != 0 && o->health > 0 && o != c) {
        dx = v.x - o->scene->obj->pos.x;
        dy = v.y - o->scene->obj->pos.y;
        dz = v.z - o->scene->obj->pos.z;
        d = sqrt(dx * dx + dy * dy + dz * dz);
        if (d <= limit)
          threat -= 70.0f / d;
      }
    }
  }
  return threat;
}
/* 0x4d2170, the safest cell around (cx, cy) for the fighter c: walks the diamond rings 0 .. r - 1 around it inside the
   height map, rates every cell whose ground type is not 0 / 0xd (the border) with cm_ThreatAt (limit r cells: r * the
   cell size * 2) and puts the least rated one into (*ox, *oy); returns 0 when no cell was rated */

int cm_BestCellNear(AICHAR *c, int cx, int cy, int r, int *ox, int *oy) {
  D3SM *sc;
  float best;
  float f;
  int k, row, col, hi, hic, m, type;

  sc = d3_DefaultScene->hmap;
  k = 0;
  best = 1000000000.0f;
  for (; k < r; k++) {
    hi = sc->size - 1 < cy + k ? sc->size - 1 : cy + k;
    for (row = cy - k < 0 ? 0 : cy - k; row <= hi; row++) {
      m = k - abs(cy - row);
      hic = sc->size - 1 < cx + m ? sc->size - 1 : cx + m;
      for (col = cx - m < 0 ? 0 : cx - m; col <= hic; col++) {
        type = sc->entries[sc->size * row + col].type;
        if (type != 0 && type != 0xd) {
          f = cm_ThreatAt(c, col, row, r * sc->cell.x * 2.0);
          if (f < best) {
            best = f;
            *ox = col;
            *oy = row;
          }
        }
      }
    }
  }
  return best != 1000000000.0f;
}
/* 0x4d22d0, the most threatened cell around (cx, cy) for the fighter c: the rings of cm_BestCellNear, the cell with the
   greatest cm_ThreatAt rating goes into (*ox, *oy); returns 1 when that rating is above 5 (0 too when no cell rated
   above 0) */

int cm_MostThreatenedCellNear(AICHAR *c, int cx, int cy, int r, int *ox,
                              int *oy) {
  D3SM *sc;
  float best;
  float f;
  int k, row, col, hi, hic, m, type;

  sc = d3_DefaultScene->hmap;
  k = 0;
  best = 0.0f;
  for (; k < r; k++) {
    hi = sc->size - 1 < cy + k ? sc->size - 1 : cy + k;
    for (row = cy - k < 0 ? 0 : cy - k; row <= hi; row++) {
      m = k - abs(cy - row);
      hic = sc->size - 1 < cx + m ? sc->size - 1 : cx + m;
      for (col = cx - m < 0 ? 0 : cx - m; col <= hic; col++) {
        type = sc->entries[sc->size * row + col].type;
        if (type != 0 && type != 0xd) {
          f = cm_ThreatAt(c, col, row, r * sc->cell.x * 2.0);
          if (f > best) {
            best = f;
            *ox = col;
            *oy = row;
          }
        }
      }
    }
  }
  if (best != 0.0f && best > 5.0f)
    return 1;
  return 0;
}
/* 0x4d2450, a callback of the object walk: collects the objects named "sp_ESCAPE" into list[cm_PointCount++] */

char cm_CollectEscapeObject(D3OBJECT *o, void *ctx) {
  D3OBJECT **list = ctx;

  if (stricmp(o->name, "sp_ESCAPE") == 0) {
    list[cm_PointCount] = o;
    cm_PointCount++;
  }
  return 1;
}
/* 0x4d2490, the closest "sp_ESCAPE" object (0x4d2450) to the character c, or 0 (limit 1e6) */

D3OBJECT *cm_NearestEscapeObject(AICHAR *c) {
  D3OBJECT *list[0x20];
  D3VECTOR4 v;
  float best = 1000000.0f;
  float d, dx, dy, dz;
  D3OBJECT *res = 0;
  D3OBJECT *m, *o;
  int i;

  cm_PointCount = 0;
  d3_ForEachObject(d3_DefaultScene, 0, 0xc0, cm_CollectEscapeObject, list);
  m = c->scene->obj;
  d3_PointToWorld(m, &m->pos, &v.v);
  for (i = 0; i < cm_PointCount; i++) {
    o = list[i];
    dx = v.x - o->pos.x;
    dy = v.y - o->pos.y;
    dz = v.z - o->pos.z;
    d = (float)sqrt(dx * dx + dy * dy + dz * dz);
    if (d < best) {
      best = d;
      res = o;
    }
  }
  return res;
}
/* 0x4d2550, a callback: collects the objects "WARE_" whose owner (+0x200, a record with the side in +0xa) is not the side
   of the character c into cm_PointList[cm_PointCount++] */

char cm_CollectWareObject(D3OBJECT *o, void *ctx) {
  AICHAR *c = ctx;
  AICHAR *side = c->side;

  if (strncmp(o->name, "WARE_", 5) == 0 &&
      ((AIOBJ *)o->owner)->fightSide != side->id)
    cm_PointList[cm_PointCount++] = o;
  return 1;
}
/* 0x4d25a0, the closest object of 0x4d2550 to the character c, or 0 */

D3OBJECT *cm_NearestWareObject(AICHAR *c) {
  D3VECTOR4 v;
  float best = 1000000.0f;
  float d, dx, dy, dz;
  D3OBJECT *res = 0;
  D3OBJECT *m, *o;
  int i, n;

  cm_PointCount = 0;
  d3_ForEachObject(d3_DefaultScene, 0, 0x40, cm_CollectWareObject, c);
  m = c->scene->obj;
  d3_PointToWorld(m, &m->pos, &v.v);
  n = cm_PointCount;
  for (i = 0; i < n; i++) {
    o = cm_PointList[i];
    dx = v.x - o->pos.x;
    dy = v.y - o->pos.y;
    dz = v.z - o->pos.z;
    d = (float)sqrt(dx * dx + dy * dy + dz * dz);
    if (d < best) {
      best = d;
      res = o;
    }
  }
  return res;
}
/* 0x4d2650, a callback: collects the objects "sp_CONQUER*" into cm_PointList[cm_PointCount++] */

char cm_CollectConquerPoint(D3OBJECT *o, void *ctx) {
  if (strncmp(o->name, "sp_CONQUER", 10) == 0)
    cm_PointList[cm_PointCount++] = o;
  return 1;
}
/* 0x4d2680, the conquer point (an "sp_CONQUER" object, cm_CollectConquerPoint) to go for: the least distance to the
   fighter c's body, weighted by the point's owner (10 for an owner of another side (cm_OtherBuilding), 15 for an
   owner of c's own side other than c, 25 for c itself); 0 when the point chosen is c's own */

D3OBJECT *cm_NearestConquerPoint(AICHAR *c) {
  D3VECTOR4 v;
  float best;
  D3OBJECT *res;
  D3OBJECT *body, *o;
  void *owner;
  float d, dx, dy, dz;
  int i;

  best = 1000000.0f;
  res = 0;
  cm_PointCount = 0;
  d3_ForEachObject(d3_DefaultScene, 0, 0x40, cm_CollectConquerPoint, c);
  body = c->scene->obj;
  d3_PointToWorld(body, &body->pos, &v.v);
  for (i = 0; i < cm_PointCount; i++) {
    o = cm_PointList[i];
    dx = v.x - o->pos.x;
    dy = v.y - o->pos.y;
    dz = v.z - o->pos.z;
    d = (float)sqrt(dx * dx + dy * dy + dz * dz);
    if (o->owner != 0 && cm_OtherBuilding(c, o->owner) != 0)
      d = (float)(d * 10.0);
    else if (o->owner != 0 && cm_OtherBuilding(c, o->owner) == 0 &&
             o->owner != c)
      d = (float)(d * 15.0);
    else if (o->owner != 0)
      d = (float)(d * 25.0);
    if (d < best) {
      best = d;
      res = o;
    }
  }
  if (res->owner == c)
    res = 0;
  return res;
}
/* 0x4d27a0, builds the fight AI's order chances cm_OrderChances[6 kinds][5 strength levels][6 orders]: the
   percentages stored one by one, then each row made cumulative (v[k] = v[k] * 0.01 + v[k - 1]), and in each row
   a value equal to an earlier one cleared (an order that adds no chance is never drawn) */

void cm_InitOrderChances(void) {
  int k, b, i, j;

  memset(cm_OrderChances, 0, 0x2d0);
  cm_OrderChances[0x0] = 10.0f;
  cm_OrderChances[0x1] = 10.0f;
  cm_OrderChances[0x4] = 30.0f;
  cm_OrderChances[0x5] = 50.0f;
  cm_OrderChances[0x6] = 40.0f;
  cm_OrderChances[0x7] = 20.0f;
  cm_OrderChances[0xa] = 20.0f;
  cm_OrderChances[0xb] = 20.0f;
  cm_OrderChances[0xc] = 80.0f;
  cm_OrderChances[0xd] = 20.0f;
  cm_OrderChances[0x10] = 0;
  cm_OrderChances[0x11] = 0;
  cm_OrderChances[0x12] = 70.0f;
  cm_OrderChances[0x13] = 30.0f;
  cm_OrderChances[0x16] = 0;
  cm_OrderChances[0x17] = 0;
  cm_OrderChances[0x18] = 50.0f;
  cm_OrderChances[0x19] = 50.0f;
  cm_OrderChances[0x1c] = 0;
  cm_OrderChances[0x1d] = 0;
  cm_OrderChances[0x1e] = 10.0f;
  cm_OrderChances[0x1f] = 10.0f;
  cm_OrderChances[0x22] = 30.0f;
  cm_OrderChances[0x23] = 50.0f;
  cm_OrderChances[0x24] = 80.0f;
  cm_OrderChances[0x25] = 20.0f;
  cm_OrderChances[0x28] = 0;
  cm_OrderChances[0x29] = 0;
  cm_OrderChances[0x2a] = 80.0f;
  cm_OrderChances[0x2b] = 20.0f;
  cm_OrderChances[0x2e] = 0;
  cm_OrderChances[0x2f] = 0;
  cm_OrderChances[0x30] = 60.0f;
  cm_OrderChances[0x31] = 40.0f;
  cm_OrderChances[0x34] = 0;
  cm_OrderChances[0x35] = 0;
  cm_OrderChances[0x36] = 50.0f;
  cm_OrderChances[0x37] = 50.0f;
  cm_OrderChances[0x3a] = 0;
  cm_OrderChances[0x3b] = 0;
  cm_OrderChances[0x3c] = 5.0f;
  cm_OrderChances[0x3e] = 5.0f;
  cm_OrderChances[0x40] = 20.0f;
  cm_OrderChances[0x41] = 70.0f;
  cm_OrderChances[0x42] = 50.0f;
  cm_OrderChances[0x44] = 10.0f;
  cm_OrderChances[0x46] = 20.0f;
  cm_OrderChances[0x47] = 20.0f;
  cm_OrderChances[0x48] = 80.0f;
  cm_OrderChances[0x4a] = 20.0f;
  cm_OrderChances[0x4c] = 0;
  cm_OrderChances[0x4d] = 0;
  cm_OrderChances[0x4e] = 70.0f;
  cm_OrderChances[0x50] = 30.0f;
  cm_OrderChances[0x52] = 0;
  cm_OrderChances[0x53] = 0;
  cm_OrderChances[0x54] = 50.0f;
  cm_OrderChances[0x56] = 50.0f;
  cm_OrderChances[0x58] = 0;
  cm_OrderChances[0x59] = 0;
  cm_OrderChances[0x5a] = 20.0f;
  cm_OrderChances[0x5c] = 80.0f;
  cm_OrderChances[0x5e] = 0;
  cm_OrderChances[0x5f] = 0;
  cm_OrderChances[0x60] = 30.0f;
  cm_OrderChances[0x62] = 70.0f;
  cm_OrderChances[0x64] = 0;
  cm_OrderChances[0x65] = 0;
  cm_OrderChances[0x66] = 40.0f;
  cm_OrderChances[0x68] = 60.0f;
  cm_OrderChances[0x6a] = 0;
  cm_OrderChances[0x6b] = 0;
  cm_OrderChances[0x6c] = 60.0f;
  cm_OrderChances[0x70] = 0;
  cm_OrderChances[0x71] = 0;
  cm_OrderChances[0x76] = 0;
  cm_OrderChances[0x77] = 0;
  cm_OrderChances[0x7a] = 0;
  cm_OrderChances[0x80] = 0;
  cm_OrderChances[0x86] = 0;
  cm_OrderChances[0x88] = 0;
  cm_OrderChances[0x89] = 0;
  cm_OrderChances[0x8c] = 0;
  cm_OrderChances[0x8e] = 0;
  cm_OrderChances[0x8f] = 0;
  cm_OrderChances[0x92] = 0;
  cm_OrderChances[0x94] = 0;
  cm_OrderChances[0x95] = 0;
  cm_OrderChances[0x98] = 0;
  cm_OrderChances[0x9e] = 0;
  cm_OrderChances[0xa4] = 0;
  cm_OrderChances[0xa6] = 0;
  cm_OrderChances[0xa7] = 0;
  cm_OrderChances[0xaa] = 0;
  cm_OrderChances[0xac] = 0;
  cm_OrderChances[0xad] = 0;
  cm_OrderChances[0xb0] = 0;
  cm_OrderChances[0xb2] = 0;
  cm_OrderChances[0xb3] = 0;
  cm_OrderChances[0x6e] = 40.0f;
  cm_OrderChances[0x72] = 70.0f;
  cm_OrderChances[0x74] = 30.0f;
  cm_OrderChances[0x78] = 20.0f;
  cm_OrderChances[0x7c] = 10.0f;
  cm_OrderChances[0x7d] = 70.0f;
  cm_OrderChances[0x7e] = 30.0f;
  cm_OrderChances[0x82] = 20.0f;
  cm_OrderChances[0x83] = 50.0f;
  cm_OrderChances[0x84] = 100.0f;
  cm_OrderChances[0x8a] = 100.0f;
  cm_OrderChances[0x90] = 100.0f;
  cm_OrderChances[0x96] = 20.0f;
  cm_OrderChances[0x9a] = 10.0f;
  cm_OrderChances[0x9b] = 70.0f;
  cm_OrderChances[0x9c] = 30.0f;
  cm_OrderChances[0xa0] = 20.0f;
  cm_OrderChances[0xa1] = 50.0f;
  cm_OrderChances[0xa2] = 100.0f;
  cm_OrderChances[0xa8] = 100.0f;
  cm_OrderChances[0xae] = 100.0f;
  for (b = 0; b < 6 * 5; b += 5) {
    for (i = 0; i < 5; i++) {
      for (k = 0; k < 6; k++) {
        cm_OrderChances[(b + i) * 6 + k] *= 0.01;
        if (k != 0)
          cm_OrderChances[(b + i) * 6 + k] +=
              cm_OrderChances[(b + i) * 6 + k - 1];
      }
    }
  }
  for (b = 0; b < 6; b++) {
    for (i = 0; i < 5; i++) {
      for (j = 0; j < 6; j++) {
        for (k = j + 1; k < 6; k++) {
          if (cm_OrderChances[(b * 5 + i) * 6 + k] ==
              cm_OrderChances[(b * 5 + i) * 6 + j])
            cm_OrderChances[(b * 5 + i) * 6 + k] = 0;
        }
      }
    }
  }
}
/* 0x4d2c00, the row of cm_OrderChances the fight AI draws the orders of side from: the kind by the fight flags (bit 0 /
   1 / 2, then side being the attacker cm_FightAttacker or the defender cm_FightDefender; 6 for neither), the level
   0 .. 4 by the ratio of the side's own strength to the enemy's (the sums of cm_FightStrength over the fighters still
   standing, health neither 0 nor 4) against 1.75 / 1.25 / 0.75 / 0.5; the defender holding against the attacker's
   "sp_CONQUER" flags gets level 1 for one taken, 0 for two or three */

float *cm_OrderChancesFor(AICHAR *side) {
  int kind;
  float def, att, r;
  D3VECTOR4 v;
  AICHAR *o;
  int i, cnt, lvl;

  kind = 6;
  if ((cm_FightRecord->fight.flags & 1) && cm_FightAttacker == side)
    kind = 0;
  else if ((cm_FightRecord->fight.flags & 1) && cm_FightDefender == side)
    kind = 1;
  else if ((cm_FightRecord->fight.flags & 2) && cm_FightAttacker == side)
    kind = 2;
  else if ((cm_FightRecord->fight.flags & 2) && cm_FightDefender == side)
    kind = 3;
  else if ((cm_FightRecord->fight.flags & 4) && cm_FightAttacker == side)
    kind = 4;
  else if ((cm_FightRecord->fight.flags & 4) && cm_FightDefender == side)
    kind = 5;
  def = 0.0f;
  for (i = 0; i < 16; i++) {
    if (cm_FightRecord->fight.defenders[i] != -1) {
      o = cm_FindFighter(cm_FightRecord->fight.defenders[i]);
      if (o->health != 0 && o->health != 4)
        def = cm_FightStrength(o) + def;
    }
  }
  att = 0.0f;
  for (i = 0; i < 16; i++) {
    if (cm_FightRecord->fight.attackers[i] != -1) {
      o = cm_FindFighter(cm_FightRecord->fight.attackers[i]);
      if (o->health != 0 && o->health != 4)
        att = cm_FightStrength(o) + att;
    }
  }
  cnt = 0;
  for (i = 0; i < cm_FlagObjectCount; i++) {
    if (strstr(cm_FlagObjects[i]->name, "sp_CONQUER") != 0) {
      d3_PointToWorld(cm_FlagObjects[i], &cm_FlagObjects[i]->pos, &v.v);
      o = cm_FlagObjects[i]->owner;
      if (o != 0 && o->side == cm_FightAttacker)
        cnt++;
    }
  }
  if (side == cm_FightAttacker)
    r = att / def;
  else
    r = def / att;
  if (r >= 1.75f)
    lvl = 4;
  else if (r >= 1.25f)
    lvl = 3;
  else if (r >= 0.75f)
    lvl = 2;
  else if (r >= 0.5f)
    lvl = 1;
  else
    lvl = 0;
  if (side == cm_FightDefender) {
    if (cnt == 1)
      lvl = cnt;
    else if (cnt == 2 || cnt == 3)
      lvl = 0;
  }
  return &cm_OrderChances[(kind * 5 + lvl) * 6];
}
/* 0x4d2e30, how well the fighter c suits the order 0 .. 5 (the fight AI gives each order drawn to the fighter rated
   highest): 0 (attack) its strength (cm_FightStrength) times 1, 0.5 when it has an order already, 0.2 with a used-up
   weapon; 1 the inverse (1 / strength times 0.4, 0.5 with another order, 1 while on order 1 or with a used-up weapon);
   2 1 on order 2, else 0.5; 3 1; 4 / 5 0.2 on order 2, else 1 / its health ratio (gm_HealthRatio); 0 for others */

float cm_OrderRating(AICHAR *c, int order) {
  float r;
  float f;
  int kind;
  unsigned char cur;

  r = 0.0f;
  switch (order) {
  case 0:
    if (c->formation == 0)
      f = 1.0f;
    else
      f = 0.5f;
    kind = cm_CharWeapon(c)->kind;
    if ((kind == 1 || kind == 2) && cm_CharWeaponItem(c)->usesLeft <= 0)
      f = 0.2f;
    r = cm_FightStrength(c) * f;
    break;
  case 1:
    cur = c->formation;
    if (cur == 1)
      f = 1.0f;
    else {
      f = 0.4f;
      if (cur != 0)
        f = 0.5f;
    }
    kind = cm_CharWeapon(c)->kind;
    if ((kind == 1 || kind == 2) && cm_CharWeaponItem(c)->usesLeft <= 0)
      f = 1.0f;
    r = f / cm_FightStrength(c);
    break;
  case 2:
    if (c->formation != 2)
      r = 0.5f;
    else
      r = 1.0f;
    break;
  case 4:
  case 5:
    if (c->formation == 2)
      r = 0.2f;
    else
      r = 1.0f / gm_HealthRatio(c);
    break;
  case 3:
    r = 1.0f;
    break;
  }
  return r;
}
/* 0x4d2f80, gives the fighters of the leading character side (cm_FightAttacker: the attackers, else the defenders of
   the fight record) their orders: once per fighter an order 0 .. 5 is drawn (util_RandomF against
   cm_OrderChancesFor) and given (AICHAR.formation) to the fighter still without a new order rated best for it
   (cm_OrderRating), a fighter holding an order already only on a second roll above 0.25; then each fighter carries
   out its order (cm_CarryOutOrder, with the leader's cutscene record cm_CutInfos) */

void cm_GiveFightOrders(AICHAR *side) {
  AICHAR *c[16];
  int *ids;
  float *row;
  CMCUTINFO *cut;
  AICHAR *sel;
  float r, best, w;
  int i, j, order, n, left, selidx;

  n = 0;
  selidx = 0;
  order = 0;
  cut = 0;
  row = cm_OrderChancesFor(side);
  for (i = 0; i < cm_FightRecord->used; i++) {
    if (cm_FightRecord->members[i] == side->netId) {
      cut = &cm_CutInfos[i];
      break;
    }
  }
  if (side == cm_FightAttacker)
    ids = cm_FightRecord->fight.attackers;
  else
    ids = cm_FightRecord->fight.defenders;
  for (i = 0; i < 16; i++) {
    if (ids[i] != -1) {
      c[i] = cm_FindFighter(ids[i]);
      n++;
    } else
      c[i] = 0;
  }
  for (left = n; left > 0; left--) {
    r = util_RandomF();
    for (j = 0; j < 6; j++) {
      if (r <= row[j]) {
        order = j;
        break;
      }
    }
    best = -1.0f;
    for (i = 0; i < 16; i++) {
      if (c[i] != 0) {
        w = cm_OrderRating(c[i], order);
        if (w > best) {
          best = w;
          selidx = i;
        }
      }
    }
    sel = c[selidx];
    if (sel->formation == 0 || cm_RandomFloat() > 0.25) {
      sel->formation = (unsigned char)order;
      c[selidx] = 0;
    }
  }
  for (i = 0; i < 16; i++) {
    if (ids[i] != -1)
      cm_CarryOutOrder(cut, cm_FindFighter(ids[i]));
  }
}
/* 0x4d3120, the formation order for the character c of the fight record rec by its formation type (AICHAR.formation):
   0 the best free cell near the character for a kind 2 weapon (cm_MostThreatenedCellNear), else the closest selected
   enemy (cm_NearestEnemy), then cm_OrderAttack; 1 the closest "WARE_" object (cm_NearestWareObject) -> cm_OrderWare3;
   2 the closest "sp_CONQUER" point (cm_NearestConquerPoint) -> cm_OrderConquer; 3 cm_OrderWait; 4 cm_OrderToBestCell;
   5 the closest "sp_ESCAPE" object (cm_NearestEscapeObject) -> cm_OrderEscape */

void cm_CarryOutOrder(CMCUTINFO *rec, AICHAR *c) {
  D3SM *sc;
  AIWEAPON *k;
  AICHAR *e;
  D3OBJECT *o;
  int x, y;
  float h;
  float v[4];

  if (c != 0 && c->scene != 0) {
    if (c->health == 0)
      return;
    if (c->scene->obj->type == 1)
      return;
  }
  switch (c->formation) {
  case 0:
    k = cm_CharWeapon(c);
    if ((k->kind == 1 || k->kind == 2) && cm_CharWeaponItem(c)->usesLeft <= 0)
      return;
    if (k->kind == 2) {
      sc = d3_DefaultScene->hmap;
      if ((char)d3_GetHeightAt(sc, &c->scene->obj->pos, &x, &y, &h) == 0)
        return;
      if (cm_MostThreatenedCellNear(c, x, y, (int)(500.0f / sc->cell.x), &x,
                                    &y) == 0)
        return;
      cm_OrderAttack(rec, c, 0, x, y);
      return;
    }
    e = cm_NearestEnemy(c);
    if (e == 0)
      return;
    cm_OrderAttack(rec, c, e, 0, 0);
    return;
  case 5:
    o = cm_NearestEscapeObject(c);
    if (o == 0)
      return;
    cm_OrderEscape(rec, c, o);
    return;
  case 1:
    o = cm_NearestWareObject(c);
    if (o == 0)
      return;
    cm_OrderWare(rec, c, o);
    return;
  case 2:
    o = cm_NearestConquerPoint(c);
    if (o == 0)
      return;
    cm_OrderConquer(rec, c, o);
    return;
  case 4:
    cm_OrderToBestCell(rec, c);
    return;
  case 3:
    cm_OrderWait(rec, c);
    return;
  }
}
/* 0x4d3300, a character falls: the sound "Koerperfaellt" and a blood puddle "ub_Blutlache" (random turn) at its place */

void cm_FallDownAction(CHACTION *a) {
  D3VECTOR rot;
  D3OBJECT *b;

  rot.x = 0;
  rot.y = 0;
  rot.z = 0;
  rot.y = (float)(cm_Random(0x168) * 3.14159274f * 0.005555555555555556);
  sb_PlaySample(0, "Koerperfaellt", 1, 0x3f, 0x7f, 0, 0);
  b = d3_CreateObject(0, &a->ch->obj->pos, &rot, "ub_Blutlache");
  d3t_PlayAnim(b, "sonstiges\\ub_Blutlache.baf", 0x12);
}
/* 0x4d3390, the death of the fighter c once its health ratio (gm_HealthRatio) is below 0.05: blood spray at the body
   (d3t_CreateBlood), its actions stopped and the fall queued (cm_FallDownAction with the sound "kampf/todumfallen"),
   health 0, the body's kind cleared, the cry "Schmerzschrei", v024 set below zero (-life - 20 with a chance of a half,
   text 0x1181, else 10 - life, text 0x1182) and the text shown; a ware it carried (v1ac) is put at the body, shown and
   handed to the defender. Returns 1, 0 while it lives */

int cm_CheckDeath(AICHAR *c) {
  char buf[0x100];
  CHACTION *a;
  D3OBJECT *ware;

  cm_CharWeapon(c);
  if (gm_HealthRatio(c) < 0.05) {
    d3t_CreateBlood(c->scene->obj, 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
    ch_StopActions(c->scene);
    a = ch_AddActionCB(c->scene, cm_FallDownAction, 0x14, 0x36, 1);
    strcpy(a->u.name, "kampf/todumfallen");
    c->health = 0;
    c->scene->obj->kind = 0;
    sb_PlaySample(0, "Schmerzschrei", 1, 0x3f, 0x7f, 0, 0);
    if (cm_Random(100) > 50) {
      c->v024 = (int)(-(int)c->f01c - 20.0);
      txt_Format(buf, 0x1181, c->id);
    } else {
      c->v024 = (int)(10.0 - (int)c->f01c);
      txt_Format(buf, 0x1182, c->id);
    }
    ware = c->fightWare;
    if (ware != 0) {
      d3_SetWorldPosRot(ware, &c->scene->obj->pos, &c->scene->obj->matrix);
      d3if_Show(ware, 1);
      c->fightWare = 0;
      ((AIOBJ *)cm_ObjectOwner(ware))->fightSide = cm_FightDefender->id;
    }
    sv_SetStatusText(buf);
    return 1;
  }
  return 0;
}

#define G19_FIGHTER_SYNC(ch)                                                   \
  r = cm_CharWeaponItem(ch);                                                   \
  if (r != 0) {                                                                \
    int vv = -1;                                                               \
    cm_BeginFieldBlock(r, r->objId);                                           \
    cm_AddFieldValues(                                                         \
        4, 1, (unsigned short)((char *)&r->usesLeft - cm_FieldObject), &vv);   \
    cm_SendFieldDeltas();                                                      \
  }

/* 0x4d3550, the hit action of the fight (queued on the hitter, a's hit record): a hit counts only while the victim's
   body is within the range of the hitter's weapon; a used-up weapon item of the player's fight is synced (its uses
   field -1); a damage shows (cm_ShowDamage) with the pain voice "_K_C2C_SCHMERZ" of the victim's side (3 in 10) or
   the cry "Schmerzschrei" (3 in 10); while both stand, the sound of the hitter's weapon ("Treffer" for a hit, else
   "Daneben_s" of the sword / dagger bank, "schuss_s" for the pistol), then, unless the victim dies (cm_CheckDeath),
   blood and a random flinch "kampf/arm_greifen" / "kampf/bauch_greifen" for a hit (the weapon 0x16e stuns: health 4,
   text 0x1188), "kampf/ausweichen_seite" (pistol, 0x160) or "kampf/stich_abwehr" for a miss, when the victim is idle */

void cm_HitAction(CHACTION *a) {
  int damage, ok;
  AIWEAPON *hw, *vw;
  char anims[2][0x20] = {"kampf/arm_greifen", "kampf/bauch_greifen"};
  char buf[0x100];
  AICHAR *victim, *hitter;
  AIOBJ *item;
  int rnd;

  hitter = a->hit.hitter;
  ok = 1;
  victim = a->hit.victim;
  damage = a->hit.damage;
  vw = cm_CharWeapon(victim);
  hw = cm_CharWeapon(hitter);
  ch_GetHMap(victim->scene);
  if (hw == 0 || cm_CharObjDistXZ(hitter, victim->scene->obj) > hw->range) {
    damage = 0;
    ok = 0;
  }
  if (cm_CutChar->netId == cm_FightOwner && (hw->kind == 1 || hw->kind == 2)) {
    item = cm_CharWeaponItem(hitter);
    if (item != 0) {
      int v = -1;
      cm_BeginFieldBlock(item, item->objId);
      cm_AddFieldValues(
          4, 1, (unsigned short)((char *)&item->usesLeft - cm_FieldObject), &v);
      cm_SendFieldDeltas();
    }
  }
  if (damage != 0) {
    rnd = cm_Random(10);
    if (victim->side == cm_FightAttacker)
      cm_ShowDamage(victim, damage, 1);
    else
      cm_ShowDamage(victim, damage, 2);
    if (rnd > 8) {
      if (a->hit.sideId != cm_FightAttacker->netId)
        snd_QueueVoice(victim->id, cm_AttackerPainVoices, "_K_C2C_SCHMERZ", -1,
                       500);
      else
        snd_QueueVoice(victim->id, cm_DefenderPainVoices, "_K_C2C_SCHMERZ", -1,
                       500);
    } else if (rnd > 5)
      sb_PlaySample(0, "Schmerzschrei", 1, 0x3f, 0x7f, 0, 0);
  }
  if (victim->health != 0 && hitter->health != 0 && ok != 0) {
    if (hw->id == 0x156 || hw->id == 0x158) {
      if (damage != 0)
        sb_PlaySample(0, "Treffer", 1, 0x3f, 0x7f, 0, 0);
      else
        sb_PlaySample(cm_SwordSounds, "Daneben_s", 1, 0x3f, 0x7f, 0, 0);
    } else if (hw->id == 0x154 || hw->id == 0x16e || hw->id == 0x172) {
      if (damage != 0)
        sb_PlaySample(0, "Treffer", 1, 0x3f, 0x7f, 0, 0);
      else
        sb_PlaySample(cm_DaggerSounds, "Daneben_s", 1, 0x3f, 0x7f, 0, 0);
    } else if (hw->id == 0x15e)
      sb_PlaySample(cm_PistolSounds, "schuss_s", 1, 0x3f, 0x7f, 0, 0);
    else if (hw->id == 0x160) {
      if (damage != 0)
        sb_PlaySample(0, "Treffer", 1, 0x3f, 0x7f, 0, 0);
    } else if (hw->id == 0)
      sb_PlaySample(0, "Treffer", 1, 0x3f, 0x7f, 0, 0);
    if (cm_CheckDeath(victim) == 0) {
      if (damage != 0) {
        d3t_CreateBlood(victim->scene->obj, 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
        if (victim->scene->actions == 0 ||
            victim->scene->actions->type == 0x3b) {
          ch_StopActions(victim->scene);
          ch_QueueAnimSpeed(victim->scene, anims[cm_Random(2)], 1, 1.4f);
        }
        if (hw->id == 0x16e) {
          victim->health = 4;
          txt_Format(buf, 0x1188, vw->text054, victim->id);
          sv_SetStatusText(buf);
        }
      } else if (victim->scene->actions == 0 ||
                 victim->scene->actions->type == 0x3b) {
        ch_StopActions(victim->scene);
        if (hw->id == 0x15e || hw->id == 0x160)
          ch_QueueAnimSpeed(victim->scene, "kampf/ausweichen_seite", 1, 1.4f);
        else
          ch_QueueAnimSpeed(victim->scene, "kampf/stich_abwehr", 1, 1.4f);
      }
    }
  }
}
/* 0x4d3980, an explosion event: the fuse sound "ZuendschnurBrennt_l_01", the attacker's worker count synced, 0x4ce290 */

void cm_LayBombAction(CHACTION *ev) {
  AICHAR *att = ev->pot.thrower;
  AIWEAPON *k;
  AIOBJ *r;

  k = cm_CharWeapon(att);
  cm_LayBomb(&att->scene->obj->pos);
  sb_PlaySample(cm_BombSounds, "ZuendschnurBrennt_l_01", 3, 0x3f, 0x7f, 0, 0);
  if (cm_CutChar->netId == cm_FightOwner && (k->kind == 1 || k->kind == 2)) {
    G19_FIGHTER_SYNC(att);
  }
}
/* 0x4d3a30, a bomb event: for the player's side the thrower's used weapon item is synced (its uses field -1),
   then a grenade (cm_ThrowGrenade, 0x4ce5d0) is thrown from the thrower's body to the cell aimed at */

void cm_ThrowBombAction(CHACTION *ev) {
  CHACTION *b = ev;
  AICHAR *att = b->bomb.thrower;
  AIOBJ *r;

  if (cm_CutChar->netId == cm_FightOwner) {
    G19_FIGHTER_SYNC(att);
  }
  cm_ThrowGrenade(&att->scene->obj->pos, b->bomb.x, b->bomb.y);
}
/* 0x4d3ac0, a fighter's cheer (fight command 1, cm_FightSlotCheer with "gestik/jubeln"): the cheering character's
   model is hidden (ch_SetVisible, 0x402480) */

void cm_CheerAction(CHACTION *ev) {
  CHACTION *b = ev;

  ch_SetVisible(b->cheer.fighter->scene, 0);
}
/* 0x4d3ae0, the end of a pick-up (fight command 4, cm_FightSlotPickUp): the object picked up gets the fight's
   attacker side as its owner (AIOBJ.fightSide), is carried by the fighter (AICHAR.v1ac) and hidden on the ground */

void cm_PickUpAction(CHACTION *ev) {
  CHACTION *b = ev;
  AICHAR *att = b->pickUp.fighter;
  D3OBJECT *o = b->pickUp.object;
  AIOBJ *p;

  p = cm_ObjectOwner(o);
  if (p != 0) {
    p->fightSide = cm_FightAttacker->id;
    att->fightWare = o;
  }
  d3if_ShowTree(o, 0);
}
/* 0x4d3b30, decides the fight of rec: the winner known already (cm_FightWinner), else the attacker cm_FightAttacker
   when no attacker of rec stands any more (health neither 0 nor 4, the body not hidden: type 1), the defender
   cm_FightDefender when no defender does, and the defender too when the attacker's side owns every "sp_CONQUER" flag;
   the winner's cutscene entry (cm_CutEntrySlot, the record of the first leader of cm_FightRecord) is sent with state 5
   (cm_SendCutEntry). Returns the winner, 0 while the fight goes on */

AICHAR *cm_CheckFightWinner(G28REC *rec) {
  AICHAR *winner;
  int flags, owned;
  int nDef, nAtt;
  D3VECTOR4 v;
  CMCUTENTRY entry;
  AICHAR *c;
  CMCUTENTRY *slot;
  int i, n;

  winner = 0;
  owned = 0;
  flags = 0;
  if (cm_FightWinner != 0)
    return cm_FightWinner;
  nDef = 0;
  for (i = 0; i < 16; i++) {
    if (rec->fight.defenders[i] != -1) {
      c = cm_FindFighter(rec->fight.defenders[i]);
      if (c->health != 0 && c->health != 4 && c->scene->obj->type != 1)
        nDef++;
    }
  }
  nAtt = 0;
  for (i = 0; i < 16; i++) {
    if (rec->fight.attackers[i] != -1) {
      c = cm_FindFighter(rec->fight.attackers[i]);
      if (c->health != 0 && c->health != 4 && c->scene->obj->type != 1)
        nAtt++;
    }
  }
  if (nAtt <= 0)
    winner = cm_FightAttacker;
  else if (nDef <= 0)
    winner = cm_FightDefender;
  for (i = 0; i < cm_FlagObjectCount; i++) {
    if (strstr(cm_FlagObjects[i]->name, "sp_CONQUER") != 0) {
      d3_PointToWorld(cm_FlagObjects[i], &cm_FlagObjects[i]->pos, &v.v);
      flags++;
      c = cm_FlagObjects[i]->owner;
      if (c != 0 && c->side == cm_FightAttacker)
        owned++;
    }
  }
  if (flags != 0 && owned == flags)
    winner = cm_FightDefender;
  if (winner != 0) {
    n = cm_FightRecord->used;
    for (i = 0; i < n && cm_FightRecord->members[i] == -1; i++)
      ;
    slot = cm_CutEntrySlot(&cm_CutInfos[i], winner);
    entry = *slot;
    entry.charId = winner->netId;
    entry.state = 5;
    cm_SendCutEntry(cm_CutInfos[i].playerId, &entry);
  }
  return winner;
}

/* 0x4d3d10, loot of a won fight: a random share (0.07 + 0.001 * 0 .. 49 of the loser's goods value 0x509e60, at
   most 0x9c400) is moved from the loser's record to the winner's (money message 0x4c47e0), then each object of the
   loser's stock (0x4ffe90 list 1) is moved to the winner (0x4c4880, 80 .. 99 % of its count) and its price added; the
   value goes to the winner's record (0x506430, AIFIN.lootTakings) */
int cm_LootStock(AIBLD *a, AIBLD *b, AICHAR *d, AICHAR *t) {
  AIOBJ *oa, *ob, *q;
  AIFIN *fin;
  int cnt, v;

  oa = gm_Query(b->objList, 2, 6, 0, 0x116);
  ob = gm_Query(a->objList, 2, 6, 0, 0x2a);
  v = gm_GetGoodsValue(t);
  v = v < 0 ? 0 : v;
  v = v < 0x9c400 ? v : 0x9c400;
  v = (int)(((double)(unsigned int)cm_Random(0x32) * 0.001 + 0.07) * v);
  cm_SendMoveGoods(d->netId, t->netId, ai_OwnPlayer, v);
  if (ob != 0 && oa != 0) {
    for (q = gm_Query(ob->list, 1, 5); q != 0; q = gm_QueryNext()) {
      cnt = (int)(((double)(unsigned int)(cm_Random(0x14) + 0x50) * 0.01) *
                  (double)q->count);
      if (cnt < 1)
        cnt = 1;
      cm_SendExSellObject(oa->objId, ob->objId, q->id, cnt, ai_OwnPlayer, 0);
      v = (int)(gm_GoodsPrice(q->id, ai_OwnPlayer) * cnt + v);
    }
  }
  fin = gm_PlayerRecord(d);
  if (fin != 0)
    fin->lootTakings += v;
  return v;
}
/* 0x4d3ea0, the loot of the carts of a won fight: for each of the 3 cart ids (G28REC.carts), the goods of the
   cart (0x4ffe90 chains) go to the winner (0x4c4880, at least 1, f of the count; a free pick-up with b == 0) and their
   price is added; with no winner record half of the value goes to the money message 0x4c47e0; the value goes to the
   record of the attacker side (0x506430, AIFIN.lootTakings) */
int cm_LootCarts(G28REC *a, AIBLD *b, AICHAR *d, AICHAR *t, float f) {
  AIOBJ *ob, *q, *p;
  AIFIN *fin;
  int cnt, i;
  int dmg = 0;
  float x;

  if (cm_FightAttacker == 0 || cm_FightDefender == 0)
    return 0;
  {
    ob = gm_Query(b->objList, 2, 6, 0, 0x116);
    for (i = 0; i < 3; i++) {
      if (a->fight.carts[i] != -1) {
        p = gm_Query(0, 2, 7, 1, a->fight.carts[i]);
        p = gm_Query(p->list, 1, 0, 0x1dd);
        for (q = gm_Query(p->list, 1, 5); q != 0; q = gm_QueryNext()) {
          gm_ObjectBuildingOwner(q);
          x = (float)q->count * f;
          if (1.0f > x)
            x = 1.0f;
          cnt = (int)x;
          if (ob != 0)
            cm_SendExSellObject(ob->objId, q->ownerId, q->id, cnt, ai_OwnPlayer,
                                0);
          else
            cm_SendExSellObject(-1, q->ownerId, q->id, cnt, ai_OwnPlayer, 0);
          dmg = (int)(gm_GoodsPrice(q->id, ai_OwnPlayer) * cnt + dmg);
        }
        if (ob == 0) {
          dmg = (int)(dmg * 0.5);
          cm_SendMoveGoods(d->netId, -1, ai_OwnPlayer, dmg);
        }
        fin = gm_PlayerRecord(cm_FightAttacker);
        if (fin != 0)
          fin->lootTakings += dmg;
      }
    }
  }
  return dmg;
}
/* 0x4d4050, the fight role of a building kind (first byte of its 0x24d-byte record): 0x13 -> 0, 0x10 -> 1, 4 -> 2, else 0 */

int cm_FightRole(AIBLD *b) {
  AIBTYPE *t = &ai_BTypes[b->type];

  if (t->kind == 0x13)
    return 0;
  if (t->kind == 0x10)
    return 1;
  return t->kind == 4 ? 2 : 0;
}
/* 0x4d4090, the loot list of a won fight: for each of the 3 cart ids at +0x100 of cm_FightRecord the goods (mode 0 all,
   1 only those of the player, 2 only the others) get a cell of 5 per row (120 x 96 pixels from x, y): their picture
   (0x525 frame, 0xdf + id), the count "%i " plus a suffix, the value "%T"; returns the sum of the values */

int cm_LootList(int x, int y, int mode) {
  int i;
  int j = 0;
  int total = 0;
  int px, py;
  int t, t2;
  AIOBJ *q;
  char buf[0x100];

  for (i = 0; i < 3; i++) {
    if (cm_FightRecord->fight.carts[i] == -1)
      continue;
    q = gm_Query(0, 2, 7, 1, cm_FightRecord->fight.carts[i]);
    q = gm_Query(q->list, 1, 0, 0x1dd);
    for (q = gm_Query(q->list, 1, 5); q != 0; q = gm_QueryNext()) {
      if (mode != 0 && !(mode == 1 && q->fightSide == ai_PlayerId) &&
          !(mode == 2 && q->fightSide != ai_PlayerId))
        continue;
      px = x + (j % 5) * 120;
      py = y + (j / 5) * 96;
      d2_WinOpenPic(px, py, 0x525, d2_LastWindow);
      d2_WinOpenPic(px, py, q->id + 0xdf, d2_LastWindow);
      t = d2_CreateWinText(px - 0x10, py - 0xf, ch_EmptyName, d2_LastWindow);
      d2_Objs[t].font = 0x56;
      d2_Objs[t].w = 0x50;
      d2_Objs[t].centred = 1;
      sprintf(buf, "%i ", q->count);
      strcat(buf, txt_Ptrs[TXT_AMOUNT_UNIT]);
      d2_SetObjText(t, buf);
      t2 = d2_CreateWinText(px - 0x10, py + 0x34, ch_EmptyName, d2_LastWindow);
      d2_Objs[t2].font = 0x56;
      d2_Objs[t2].w = 0x50;
      d2_Objs[t2].centred = 1;
      txt_Format(buf, (intptr_t)"%T",
                 (int)gm_GoodsPrice(q->id, ai_OwnPlayer) * q->count);
      d2_SetObjText(t2, buf);
      total = (int)(gm_GoodsPrice(q->id, ai_OwnPlayer) * q->count + total);
      j++;
    }
  }
  return total;
}
/* 0x4d4340, the portrait row of the fight: for each of the 16 ids (-1 = none) a column (width = (0x6ed980 + 8 - 0x30) /
   (count + 1), 6 per row, rows of 100 pixels from x, y) with the frame 0x5da, the portrait, the health bar (0x504e00),
   the name and health text ("%1N1 %i%"), the building icon and the state icon (0x3b / 0x37) of the character */

void cm_FightPortraits(int *ids, int x, int y) {
  int i, n = 0;
  int w, px, py, v, t, f, ic;
  AICHAR *c;
  AIWEAPON *o;
  char buf[0x100];

  for (i = 0; i < 16; i++) {
    if (ids[i] != -1)
      n++;
  }
  w = (d2_LastWindowPtr->w - 0x30) / (n + 1);
  for (i = 0; i < 16; i++) {
    if (ids[i] == -1)
      continue;
    c = cm_FindFighter(ids[i]);
    px = (i % 6 + 1) * w + x;
    py = y + i / 6 * 100;
    d2_WinOpenPic(px - 0x10, py, 0x5da, d2_LastWindow);
    d2_WinOpenPic(px - 4, py, c->picture, d2_LastWindow);
    v = gm_SkillPoints(c, 3);
    sv_ValueBar(px, py + 0x3c, (int)(double)(float)v, 0x4eb);
    t = d2_CreateWinText(px - 0x24, py - 0x11, ch_EmptyName, d2_LastWindow);
    d2_Objs[t].w = 0x78;
    d2_Objs[t].centred = 1;
    d2_Objs[t].font = 0x56;
    txt_Format(buf, (intptr_t)"%1N1 %i%", c->id,
               (int)(gm_HealthRatio(c) * 100.0));
    d2_SetObjText(t, buf);
    o = cm_CharWeapon(c);
    if (o != 0 && o->id != 0) {
      ic = d2_WinOpenPic(px + 0x28, py + 0xf, o->id + 0xdf, d2_LastWindow);
      d2_ScaleObject(ic, -2);
    }
    if (c->health == 0) {
      f = (int)-c->f01c;
      if ((double)c->v024 == (double)f - 20.0)
        d2_WinOpenPic(px, py + 6, 0x3b, d2_LastWindow);
      else
        d2_WinOpenPic(px, py + 6, 0x37, d2_LastWindow);
    }
  }
}
/* 0x4d4540, the dialog "cutscenes\combat_start" that ends a fight (a: the fight record; its flags bits 2 / 1 / 4 pick the
   text): when the attacker is a player's character, the line of the winner (texts 0x1138 .. 0x113c, 0x1125 + role),
   the portrait row (cm_FightPortraits) and two buttons (1: settle); then, for a raid in the open (flags bit 0) not
   settled yet: a player defender sees the carts' loot (cm_LootList, their value at 10 / 50 / 80 per cent) and picks the
   share 10 / 50 / 90 (taken when random 10 .. 99 is at most it, else refused), or the AI side picks one at random when
   it fights no defenders or its random 0 .. 4 is above the escort. The loot goes through cm_LootCarts into
   cm_FightLootValue (-1: refused), cm_FightSettled = 1 when it was taken. Returns 1 when the fight goes on. */

int cm_FightStartDialog(G28REC *a) {
  int res = 1;
  int st = 0;
  int line = 0;
  int win, role, i, n, r, v, sel, k, total;
  int b1, b2, b3, b4;
  AIBLD *place, *home;
  float fv;
  AIJOB *job;
  void *bld;
  char tb[0x400];
  char tc[0x400];

  win = d2_OpenForm(0, 0, "cutscenes\\combat_start");
  d2_PlaceMainWindow(win, 3);
  cm_FightSettled = 0;
  place = gm_BuildQuery(1, 1, a->thing);
  home = gm_BuildQuery(1, 1, a->fight.attackerBld);
  role = cm_FightRole(home);
  d2_SetForm(win, 1);
  if (cm_FightAttacker->kind == 6) {
    if (a->fight.flags & 2) {
      io_PrintText(0x1138, role + 0x1125, home, cm_FightDefender->id, place);
      d2_SetForm(win, 2);
      line = io_PrintText(0x113a, cm_FightDefender->id, place);
    } else if (a->fight.flags & 1) {
      for (i = 0; i < 3; i++) {
        if (a->fight.carts[i] != -1)
          st++;
      }
      fv = gm_GetSkill(cm_FightAttacker, 3);
      io_PrintText(0x112e, home, cm_FightDefender->id);
      d2_SetForm(win, 2);
      io_PrintText(0x112f, st, 0xc10);
      if (fv >= 0.5) {
        if (a->fight.escort != 0)
          io_PrintText(0x1134);
        else
          io_PrintText(0x1135);
      }
      if (fv >= 0.75) {
        v = gm_SkillPoints(cm_FightDefender, 3);
        r = (int)(v * 0.023809524f);
        if (r > 4)
          r = 4;
        r = r < 0 ? 0 : r;
        io_PrintText(0x1131, r + 0x1128);
      }
      if (cm_FightDefender->sex == 0)
        line = io_PrintText(0x1133, 0x1136);
      else
        line = io_PrintText(0x1133, 0x1137);
    } else if (a->fight.flags & 4) {
      io_PrintText(0x113b, home, cm_FightDefender->id);
      d2_SetForm(win, 2);
      line = io_PrintText(0x113c, cm_FightDefender->id, place);
    }
    d2_SetForm(win, 1);
    io_PrintText(0x1132);
    cm_FightPortraits(a->fight.attackers, 0, 0xb4);
    d2_GetWinObj(win, 2, line);
    line++;
    d2_GetWinObj(win, 2, line);
    while (sv_RunFrame(cm_FightStartDialog, 0x7d6c6)) {
      if (dm_L.rup != 0) {
        sv_PopRequest = 1;
        cm_FightSettled = 1;
        res = 0;
      }
      if (d2_ClickedId == 0) {
        res = 1;
        sv_PopRequest = 1;
      } else if (d2_ClickedId == 1) {
        cm_FightSettled = 1;
        res = 0;
        sv_PopRequest = 1;
      }
    }
  }
  if ((a->fight.flags & 1) && cm_FightDefender->kind == 6 &&
      cm_FightSettled == 0) {
    AIRECIPE rc = {0};

    total = 0;
    for (i = 0; i < 3; i++) {
      if (a->fight.carts[i] != -1)
        st++;
    }
    job = (gm_Query(0, 2, 7, 1, a->fight.carts[0]))
              ->job24; /* the job the first cart runs */
    d2_SetForm(win, 1);
    io_PrintText((intptr_t)"$C");
    if (job != 0) {
      bld = gm_FindBuildingById(job->cartBld);
      k = 0;
      for (i = 0; i < 16; i++) {
        if (a->fight.attackers[i] != -1)
          k++;
      }
      if (bld != 0)
        io_PrintText(0x113d, st, 0xc10, bld, cm_FightAttacker->id, k);
    }
    v = gm_SkillPoints(cm_FightDefender, 3);
    r = (int)(v * 0.023809524f);
    if (r > 4)
      r = 4;
    if (a->fight.escort != 0)
      io_PrintText(0x113e, (r < 0 ? 0 : r) + 0x1128);
    else
      io_PrintText(0x113f);
    cm_LootList(0x10, 0x96, 0);
    for (i = 0; i < 3; i++) {
      n = a->fight.carts[i];
      if (n != -1) {
        bld = gm_FindObjectInst(n);
        if (bld != 0) {
          gm_StallGoodsList(bld, &rc);
          for (k = 0; k < rc.count; k++)
            total =
                (int)(gm_GoodsPrice(rc.item[k], ai_OwnPlayer) * rc.amount[k] +
                      total);
        }
      }
    }
    d2_SetForm(win, 2);
    io_PrintText((intptr_t)"$C");
    k = io_PrintText(0x1141, (int)(total * 0.1), (int)(total * 0.5),
                     (int)(total * 0.8));
    b1 = d2_GetWinObj(win, 2, k);
    b2 = d2_GetWinObj(win, 2, k + 1);
    b3 = d2_GetWinObj(win, 2, k + 2);
    line = 0;
    for (i = 0; i < 16; i++) {
      if (a->fight.defenders[i] != -1)
        line++;
    }
    b4 = d2_GetWinObj(win, 2, k + 3);
    if (line == 0)
      d2_EnableObject(b4, 0);
    while (sv_RunFrame(cm_FightStartDialog, 0x7d6c6)) {
      if (dm_L.rup != 0) {
        sv_PopRequest = 1;
        res = 0;
      }
      if (d2_ClickedId == -1)
        continue;
      sel = d2_PointerObj;
      if (sel == b4) {
        sv_PopRequest = 1;
        res = 1;
      } else if (sel == b1 || sel == b2 || sel == b3) {
        st = 0;
        if (sel == b1)
          st = 10;
        else if (sel == b2)
          st = 50;
        else if (sel == b3)
          st = 90;
        if (util_Random(0x5a) + 10 <= st) {
          home = gm_BuildQuery(1, 1, a->fight.attackerBld);
          txt_Format(tb, 0x1142);
          cm_MessageBox((intptr_t)tb, 0);
          fv = (float)(st * 0.01);
          sv_PopRequest = 1;
          res = 0;
          cm_FightSettled = 1;
          cm_FightLootValue = cm_LootCarts(
              cm_FightRecord, home, cm_FightAttacker, cm_FightDefender, fv);
        } else {
          txt_Format(tc, 0x1143);
          cm_MessageBox((intptr_t)tc, 0);
          sv_PopRequest = 1;
          res = 1;
        }
      }
    }
  } else if ((a->fight.flags & 1) && cm_FightDefender->kind != 6 &&
             cm_FightSettled == 0) {
    n = 0;
    for (i = 0; i < 16; i++) {
      if (a->fight.defenders[i] != -1)
        n++;
    }
    if (n == 0 || util_Random(5) > a->fight.escort) {
      st = 0;
      r = util_Random(4);
      if (r == 0)
        st = 10;
      else if (r == 1)
        st = 90;
      else if (r >= 2)
        st = 50;
      if (util_Random(0x5a) + 10 <= st) {
        home = gm_BuildQuery(1, 1, a->fight.attackerBld);
        fv = (float)(st * 0.01);
        res = 0;
        cm_FightSettled = 1;
        cm_FightLootValue = cm_LootCarts(cm_FightRecord, home, cm_FightAttacker,
                                         cm_FightDefender, fv);
      } else {
        cm_FightLootValue = -1;
        res = 1;
      }
    }
  }
  if (win != -1)
    d2_CloseView(win);
  return res;
}

/* 0x4d4d70, the end of a fight (a: the fight record, its flags say how it was fought): the weapons the fighters lose
   (cm_FightWeaponLoss, by the fight's owner), the side picked (side: by cm_FightWinner, else the side with more
   fighters standing), the dialog "cutscenes\combat_end" with that side's text (0x1189 .. 0x118f), the portrait rows of
   both sides with their roles (0x1191, 0x1193, cm_FightPortraits), then by the kind of the fight: the loot of the
   carts (flags 1: cm_LootList, the goods moved to the attacker's building), the capture of the target building
   (flags 2, the player attacking: texts 0x119f .. 0x11a3 offer four outcomes: 1 the building is taken, 2 a share of
   money and goods is taken, 3 the attacker gains face, 0 the town guards are called, 0x11a4 .. 0x11a7), the bars of
   the defenders of a building of kind 0x13 (flags 4: their health, the money for the wounded) or the AI's capture
   (flags 2, the AI attacking: the same outcomes by random) */
void cm_FightEndDialog(G28REC *a) {
  char ba[0x800];
  char bb[0x400];
  char tc[0x400];
  char tmp[0x100];
  AIOBJ *obj, *ob, *q, *p;
  AICHAR *side, *c, *ch;
  AIBLD *b, *ca;
  AIBTYPE *bt;
  AIFIN *rec;
  int win, i, n, role, v, cnt, total, na, nb, id, k;
  int h, row, col, px, py;
  int wait = 0;

  obj = 0;
  role = 0;
  d2_CopyCaption(ch_EmptyName);
  sv_SetStatusText(ch_EmptyName);
  if (a->fight.attackerBld != -1) {
    b = gm_BuildQuery(1, 1, a->fight.attackerBld);
    obj = gm_Query(b->objList, 2, 6, 0, 0x116);
    if (obj == 0)
      obj = gm_Query(b->objList, 2, 6, 0, 0x2a);
  }
  if (cm_FightOwner == ai_Chars[ai_PlayerId].netId) {
    for (i = 0; i < 16; i++) {
      id = a->fight.defenders[i];
      if (id != -1 && (c = gm_FindChar(id)) != 0)
        cm_FightWeaponLoss(c);
    }
    for (i = 0; i < 16; i++) {
      id = a->fight.attackers[i];
      if (id != -1 && (c = gm_FindChar(id)) != 0)
        cm_FightWeaponLoss(c);
    }
  }
  if (cm_FightWinner == 0) {
    na = 0;
    for (i = 0; i < 16; i++) {
      id = a->fight.defenders[i];
      if (id != -1) {
        c = cm_FindFighter(id);
        if (c->health != 0 && c->health != 4 && c->scene->obj->type != 1)
          na++;
      }
    }
    nb = 0;
    for (i = 0; i < 16; i++) {
      id = a->fight.attackers[i];
      if (id != -1) {
        c = cm_FindFighter(id);
        if (c->health != 0 && c->health != 4 && c->scene->obj->type != 1)
          nb++;
      }
    }
  }
  side = cm_FightWinner == 0
             ? (nb > na ? cm_FightAttacker : cm_FightDefender)
             : (cm_FightWinner == cm_FightAttacker ? cm_FightDefender
                                                   : cm_FightAttacker);
  win = d2_OpenForm(0, 0, "cutscenes\\combat_end");
  d2_PlaceMainWindow(win, 3);
  d2_SetForm(win, 2);
  io_PrintText(0x7d);
  d2_SetForm(win, 1);
  if (ai_Chars[ai_PlayerId].netId == side->netId) {
    if (side == cm_FightDefender) {
      if (a->fight.flags & 1) {
        io_PrintText(0x1189, cm_FightDefender->id, cm_FightAttacker->id);
        io_PrintText(0x118a);
      } else
        io_PrintText(0x1189, cm_FightDefender->id, cm_FightAttacker->id);
    } else if (a->fight.flags & 1)
      /* @original the same text both ways: VC6 merges the arms, the flags load stays ahead of the defender
         test */
      io_PrintText(0x118e, cm_FightAttacker->id, cm_FightDefender->id);
    else
      io_PrintText(0x118e, cm_FightAttacker->id, cm_FightDefender->id);
  } else if (side == cm_FightAttacker) {
    io_PrintText(0x118c, cm_FightDefender->id, cm_FightAttacker->id);
    if (a->fight.flags & 1) {
      p = gm_Query(0, 2, 7, 1, a->fight.carts[0]);
      if (p->job24 != 0 && gm_FindBuildingById(p->job24->cartBld) != 0)
        io_PrintText(0x118d);
    }
  } else
    io_PrintText(0x118f, cm_FightAttacker->id, cm_FightDefender->id);
  while (sv_RunFrame(cm_FightEndDialog, 0x7d6c6)) {
    if (dm_L.rup != 0 || d2_ClickedId == 0)
      sv_PopRequest = 1;
  }
  d2_SetForm(win, 1);
  io_PrintText((intptr_t)"$C");
  io_PrintText(0x1191);
  b = gm_BuildQuery(1, 1, a->fight.attackerBld);
  bt = &ai_BTypes[b->type];
  if (bt->kind == 0x13)
    role = 0;
  else if (bt->kind == 0x10)
    role = 1;
  else if (bt->kind == 4)
    role = 2;
  io_PrintText(0x1193, cm_FightAttacker->id, role + 0x1125);
  cm_FightPortraits(a->fight.attackers, 0, 100);
  ca = gm_BuildQuery(1, 1, a->thing);
  if (ca != 0) {
    bt = &ai_BTypes[ca->type];
    if (bt->kind == 0x13)
      role = 0;
    else if (bt->kind == 0x10)
      role = 1;
    else if (bt->kind == 4)
      role = 2;
  } else
    role = 0;
  io_PrintText((intptr_t)"$7A");
  io_PrintText(0x1193, cm_FightDefender->id, role + 0x1125);
  cm_FightPortraits(a->fight.defenders, 0, 0x12c);
  while (sv_RunFrame(cm_FightEndDialog, 0x7d6c6)) {
    if (dm_L.rup != 0 || d2_ClickedId == 0)
      sv_PopRequest = 1;
  }
  d2_SetForm(win, 1);
  io_PrintText((intptr_t)"$C");
  io_PrintText(0x1197);
  if (a->fight.flags & 1) {
    /* the carts: the loot list, the goods moved to the attacker's building */
    if (ai_PlayerId == cm_FightDefender->id)
      cm_LootList(0x24, 0x32, 2);
    else if (ai_PlayerId == cm_FightAttacker->id) {
      if (side == cm_FightAttacker)
        v = cm_LootList(0x24, 0x32, 0);
      else
        v = cm_LootList(0x24, 0x32, 1);
      rec = gm_PlayerRecord(cm_FightAttacker);
      if (rec != 0)
        rec->lootTakings += v;
      if (a->fight.attackerBld != -1) {
        b = gm_BuildQuery(1, 1, a->fight.attackerBld);
        b->roundSums[0] += v;
      }
    }
    for (i = 0; i < 3; i++) {
      id = a->fight.carts[i];
      if (id == -1)
        continue;
      p = gm_Query(0, 2, 7, 1, id);
      p = gm_Query(p->list, 1, 0, 0x1dd);
      for (q = gm_Query(p->list, 1, 5); q != 0; q = gm_QueryNext()) {
        if (side == cm_FightAttacker)
          q->fightSide = cm_FightAttacker->id;
        if (q->fightSide == cm_FightAttacker->id) {
          if (obj != 0 && cm_FightOwner == ai_Chars[ai_PlayerId].netId) {
            gm_ObjectBuildingOwner(q);
            cm_SendExSellObject(obj->objId, q->ownerId, q->id, q->count,
                                ai_OwnPlayer, 0);
          }
          gm_GoodsPrice(q->id, ai_OwnPlayer);
        }
      }
    }
    wait = 1;
  } else if ((a->fight.flags & 2) && side == cm_FightAttacker &&
             side->id == ai_PlayerId) {
    /* the player took the building: four outcomes to choose */
    ca = gm_BuildQuery(1, 1, a->thing);
    txt_Format(ba, 0x119f, ca, cm_FightAttacker->id, ca);
    if (ca->type != 0x1e && ca->type != 0x20 && ca->type != 0x1f) {
      txt_Format(bb, 0x11a0, ca->type * 14 + 0x48e);
      strcat(ba, bb);
    }
    txt_Format(bb, 0x11a1);
    strcat(ba, bb);
    txt_Format(bb, 0x11a2);
    strcat(ba, bb);
    txt_Format(bb, 0x11a3);
    strcat(ba, bb);
    n = cm_MessageBox((intptr_t)ba, 0x11);
    if (ca->type == 0x1e || ca->type == 0x20 || ca->type == 0x1f)
      n++;
    if (n == 1) {
      /* the building is taken */
      bt = &ai_BTypes[ca->type];
      if (bt->kind == 4 || bt->kind == 0x10)
        ai_CountMissionEvent(cm_FightAttacker, 0x1c);
      cm_SendOwnership(ca->id, cm_FightAttacker->netId,
                       cm_FightAttacker->netId);
      txt_Format(ba, 0x11a4, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)ba, 0);
    } else if (n == 2) {
      /* a share of the defender's money (5 .. 7 %, at most 0x9c400) and of the goods of the building's store
         (80 .. 99 %) goes to the attacker */
      tc[0] = ch_EmptyName[0];
      memset(tc + 1, 0, 0x3ff);
      txt_Format(tc, 0x11a5, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)tc, 0);
      ob = gm_Query(ca->objList, 2, 6, 0, 0x2a);
      if (ob == 0)
        ob = gm_Query(ca->objList, 2, 6, 0, 0x116);
      v = gm_GetGoodsValue(cm_FightDefender);
      v = v < 0x9c400 ? v : 0x9c400;
      v = (int)((float)((double)cm_Random(0x32) * 0.001 + 0.07) *
                (v < 0 ? 0 : v));
      txt_Format(tc, (intptr_t)"$Z%T$A", v);
      cm_SendMoveGoods(cm_FightAttacker->netId, cm_FightDefender->netId,
                       ai_OwnPlayer, v);
      if (ob != 0 && obj != 0) {
        for (q = gm_Query(ob->list, 1, 5); q != 0; q = gm_QueryNext()) {
          cnt = (int)(((double)(cm_Random(0x14) + 0x50) * 0.01) * q->count);
          if (cnt < 1)
            cnt = 1;
          sprintf(tmp, "%i %s$A", cnt, txt_Ptrs[TXT_OBJECT_NAMES + 2 * q->id]);
          strcat(tc, tmp);
          if (ai_Chars[ai_PlayerId].netId == cm_FightOwner)
            cm_SendExSellObject(obj->objId, ob->objId, q->id, cnt, ai_OwnPlayer,
                                0);
          v = (int)(gm_GoodsPrice(q->id, ai_OwnPlayer) * cnt + v);
        }
      }
      d2_SetForm(win, 1);
      io_PrintText((intptr_t)tc);
      rec = gm_PlayerRecord(cm_FightAttacker);
      if (rec != 0)
        rec->lootTakings += v;
      if (a->fight.attackerBld != -1) {
        b = gm_BuildQuery(1, 1, a->fight.attackerBld);
        b->roundSums[0] += v;
      }
      wait = 1;
    } else if (n == 3) {
      tc[0] = ch_EmptyName[0];
      memset(tc + 1, 0, 0x3ff);
      txt_Format(tc, 0x11a6, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)tc, 0);
      if (ai_Chars[ai_PlayerId].netId == cm_FightOwner)
        gm_ChangeBuildingState(ca, 0x14 - cm_Random(0x14));
    } else if (n == 0) {
      /* the town guards are called: every guard (title groups 10 .. 12) turns against the attacker */
      txt_Format(ba, 0x11a7, cm_FightAttacker->id, cm_FightAttacker->id);
      cm_MessageBox((intptr_t)ba, 0);
      for (i = 0; i < 0x300; i++) {
        ch = &ai_Chars[i];
        if (ch->id != 0xffff && ch->health != 0 &&
            ((k = gm_TitleGroup(ch->jobId)) == 10 || k == 11 || k == 12))
          cm_SendRelations(cm_FightAttacker->netId, ch->netId, 6, 1);
      }
    }
  } else if (a->fight.flags & 4) {
    /* the defenders of a building of kind 0x13: their bars, the wounded paid for */
    b = gm_BuildQuery(1, 1, a->fight.attackerBld);
    if (ai_BTypes[b->type].kind == 0x13) {
      total = 0;
      for (v = 0; v < 16; v++) {
        id = a->fight.defenders[v];
        if (id != -1) {
          c = cm_FindFighter(id);
          col = v % 4;
          row = v / 4 + 1;
          px = col * 80 + 0x30;
          py = row * 100;
          d2_WinOpenPic(px, py, 0x5db, d2_LastWindow);
          d2_WinOpenPic(px + 2, py, c->picture, d2_LastWindow);
          sv_ValueBar(px, py + 0x3c, c->sk83, 0x4eb);
          h = 0;
          if (c->health == 0) {
            h = (int)(c->sk83 * 0.023809524f + 1.0f);
            d2_WinOpenPic(px + 6, py + 6, 0x3b, d2_LastWindow);
            h = gm_PlayerFactor(h * 40, ai_OwnPlayer);
          }
          if (side == cm_FightAttacker) {
            if (c->health > 0) {
              int z = 0;

              cm_BeginFieldBlock(c, c->netId);
              cm_AddFieldValue(4, 1, (char *)&c->bld - cm_FieldObject, &z);
              cm_SendFieldDeltas();
            }
            txt_Format(tmp, (intptr_t)"%T", h);
            if (h != 0)
              d2_CreateWinText(px, py + 0x50, tmp, d2_LastWindow);
            total += h;
          }
        }
      }
      if (total != 0)
        cm_SendMoveGoods(cm_FightAttacker->netId, -1, ai_OwnPlayer, total);
      else if (ai_PlayerId == cm_FightAttacker->id)
        io_PrintText(0x11b6);
      if (a->fight.attackerBld != -1) {
        b = gm_BuildQuery(1, 1, a->fight.attackerBld);
        b->roundSums[0] += total;
      }
      wait = 1;
    }
  } else if ((a->fight.flags & 2) && side == cm_FightAttacker &&
             cm_FightAttacker->kind != 6 && cm_FightAttacker->kind != 7) {
    /* the AI took the building: the outcome by random (a guard's or a job's building of its own always) */
    k = 0;
    if (!gm_TitleJob(cm_FightAttacker->id, gm_BuildingJob(bt->kind)) ||
        bt->kind == 0xd || bt->kind == 0xc || bt->kind == 0xb)
      k = util_Random(3) + 1;
    if (k == 0) {
      txt_Format(bb, 0x11a4, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)bb, 0);
    } else if (k == 2) {
      tc[0] = ch_EmptyName[0];
      memset(tc + 1, 0, 0x3ff);
      txt_Format(tc, 0x11a5, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)tc, 0);
      p = gm_Query(ca->objList, 2, 6, 0, 0x2a);
      if (p == 0)
        p = gm_Query(ca->objList, 2, 6, 0, 0x116);
      v = gm_GetGoodsValue(cm_FightDefender);
      v = v < 0x9c400 ? v : 0x9c400;
      v = (int)((float)((double)cm_Random(0x32) * 0.001 + 0.07) *
                (v < 0 ? 0 : v));
      txt_Format(tc, (intptr_t)"$Z%T$A", v);
      cm_SendMoveGoods(cm_FightAttacker->netId, cm_FightDefender->netId,
                       ai_OwnPlayer, v);
      if (p != 0 && obj != 0) {
        for (q = gm_Query(p->list, 1, 5); q != 0; q = gm_QueryNext()) {
          n = (int)(((double)(cm_Random(0x14) + 0x50) * 0.01) * q->count);
          if (n < 1)
            n = 1;
          sprintf(tmp, "%i %s$A", n, txt_Ptrs[TXT_OBJECT_NAMES + 2 * q->id]);
          strcat(tc, tmp);
          if (ai_Chars[ai_PlayerId].netId == cm_FightOwner)
            cm_SendExSellObject(obj->objId, p->objId, q->id, n, ai_OwnPlayer,
                                0);
          v = (int)(gm_GoodsPrice(q->id, ai_OwnPlayer) * n + v);
        }
      }
      d2_SetForm(win, 1);
      io_PrintText((intptr_t)tc);
      rec = gm_PlayerRecord(cm_FightAttacker);
      if (rec != 0)
        rec->lootTakings += v;
      if (a->fight.attackerBld != -1) {
        b = gm_BuildQuery(1, 1, a->fight.attackerBld);
        b->roundSums[0] += v;
      }
      wait = 1;
    } else if (k == 3) {
      tc[0] = ch_EmptyName[0];
      memset(tc + 1, 0, 0x3ff);
      txt_Format(tc, 0x11a6, cm_FightAttacker->id, ca);
      cm_MessageBox((intptr_t)tc, 0);
      if (ai_Chars[ai_PlayerId].netId == cm_FightOwner)
        gm_ChangeBuildingState(ca, 0x14 - cm_Random(0x14));
    } else if (k == 1) {
      txt_Format(bb, 0x11a7, cm_FightAttacker->id, cm_FightAttacker->id);
      cm_MessageBox((intptr_t)bb, 0);
      for (i = 0; i < 0x300; i++) {
        ch = &ai_Chars[i];
        if (ch->id != 0xffff && ch->health != 0 &&
            ((k = gm_TitleGroup(ch->jobId)) == 10 || k == 11 || k == 12))
          cm_SendRelations(cm_FightAttacker->netId, ch->netId, 6, 1);
      }
    }
  }
  while (wait && sv_RunFrame(cm_FightEndDialog, 0x7d6c6)) {
    if (dm_L.rup != 0 || d2_ClickedId == 0)
      sv_PopRequest = 1;
  }
  di_ClearEvents(0x10);
  d2_CloseView(win);
}
/* 0x4d60b0, the check of the fight scene (cm_InitScenes registers it for kind 3) and its opening lines (a: the fight
   record): 0 when a leader is missing or both are the same, a cart is gone or its goods are worth nothing
   (gm_StallGoodsList's value) or the attacker's building is gone; else for both leaders one party note each by the
   kind of the fight (flags 1: texts 0x11e0 / 0x11e1, 2: 0x11e3 / 0x11e4 with the role of the attacker's building and
   the target building, 4: 0x11e6 / 0x11e7), the kind's closing text (0x11e2 / 0x11e5 / 0x11e8) appended; 1 */
int cm_CheckFight(G28REC *a) {
  char buf[0x400];
  AIRECIPE rc;
  int i, role;
  AIOBJ *cart;
  AICHAR *ca, *cb;
  char *place;

  ca = gm_FindChar(a->members[0]);
  cb = gm_FindChar(a->members[1]);
  if (ca == 0 || cb == 0 || ca == cb) {
    /* @original the failing guard tests ca == cb once more and returns 0 either way (no code left of it):
       only with that second test, one more reference of ca and cb, VC6 serves cb before the cart loop's
       pointer (cb esi, the pointer and place edi); the plain guard gives the two swapped */
    if (ca == cb)
      return 0;
    return 0;
  }
  if (a->fight.flags & 1) {
    for (i = 0; i < 3; i++) {
      if (a->fight.carts[i] != -1) {
        cart = gm_FindObjectInst(a->fight.carts[i]);
        if (cart == 0)
          return 0;
        gm_StallGoodsList(cart, &rc);
        if (rc.value <= 0)
          return 0;
      }
    }
  }
  place = (char *)gm_FindBuildingById(a->thing);
  if (gm_BuildQuery(1, 1, a->fight.attackerBld) == 0)
    return 0;
  if (a->fight.flags & 1) {
    txt_Format(buf, 0x11e0, cb->id);
    strcat(buf, txt_Ptrs[0x11e2]);
    cm_SendPartyNote(ca, a, buf, ch_EmptyName);
    txt_Format(buf, 0x11e1, ca->id);
    strcat(buf, txt_Ptrs[0x11e2]);
    cm_SendPartyNote(cb, a, buf, ch_EmptyName);
  } else if (a->fight.flags & 2) {
    role = cm_FightRole(gm_FindBuildingById(a->fight.attackerBld));
    txt_Format(buf, 0x11e3, role + 0x1125, cb->id, place);
    strcat(buf, txt_Ptrs[0x11e5]);
    cm_SendPartyNote(ca, a, buf, ch_EmptyName);
    txt_Format(buf, 0x11e4, ca->id, role + 0x1125, place);
    strcat(buf, txt_Ptrs[0x11e5]);
    cm_SendPartyNote(cb, a, buf, ch_EmptyName);
  } else if (a->fight.flags & 4) {
    txt_Format(buf, 0x11e6, cb->id);
    strcat(buf, txt_Ptrs[0x11e8]);
    cm_SendPartyNote(ca, a, buf, ch_EmptyName);
    txt_Format(buf, 0x11e7, ca->id);
    strcat(buf, txt_Ptrs[0x11e8]);
    cm_SendPartyNote(cb, a, buf, ch_EmptyName);
  }
  return 1;
}
/* 0x4d63e0, a fight starts (a: the fight record): characters that are gone are dropped from both id lists, a cart
   without goods or no defender ends it (bad = 2); with the player present (0x6f0d8c == 0) the fight scene is built and
   fought (cm_SetupFightScene .. cm_FightIntro, the party run by cm_RunSceneParty), cm_FightStartDialog settles the
   loot and cm_FightEndDialog shows the end, else (remote) it is decided at once by strength (sum of cm_FightStrength +
   random 30 per side, every fighter loses up to 20 * random 10 health) and the loot goes through cm_LootStock /
   cm_LootCarts. */

void cm_RunFight(G28REC *a) {
  char buf[0x800];
  AIRECIPE rc;
  int bad = 0, nb, seed, i, id, sa, sb, w, n, r;
  AIBLD *c;
  AIOBJ *p, *box;
  AICHAR *win;
  AIBLD *e1, *e2;
  AICHAR *ch;
  AIBLD *bld;
  int *e;

  seed = cut_GetRandSeed();
  nb = 0;
  for (i = 0; i < 16; i++) {
    id = a->fight.defenders[i];
    if (id != -1 && gm_FindChar(id) == 0) {
      bad = 1;
      a->fight.defenders[i] = -1;
    }
  }
  for (i = 0; i < 16; i++) {
    id = a->fight.attackers[i];
    if (id != -1) {
      if (gm_FindChar(id) == 0) {
        bad = 1;
        a->fight.attackers[i] = -1;
      } else
        nb++;
    }
  }
  if (a->fight.flags & 1) {
    for (i = 0; i < 3; i++) {
      id = a->fight.carts[i];
      if (id != -1) {
        p = gm_FindObjectInst(id);
        if (p != 0) {
          gm_StallGoodsList(p, &rc);
          if (rc.value > 0)
            continue;
        }
        bad = 2;
      }
    }
  }
  if (gm_BuildQuery(1, 1, a->fight.attackerBld) == 0 || bad == 2 || nb == 0)
    return;
  if (cm_SkipEvents == 0) {
    cm_SceneDuration = 200;
    cm_FightOwner = a->host;
    cm_SetupFightScene(a);
    cm_CollectSceneChars();
    cm_PlaceFighters(a->fight.attackers, "OFF");
    cm_PlaceFighters(a->fight.defenders, "DEF");
    cm_FightIntro((char *)a);
    if (cm_FightFixedLight != 0)
      d3_SetLightSet(2, 0, 1.0f, 1);
    else
      sv_UpdateSkyPhase(&ai_Time);
    cm_FightWinner = 0;
    cm_FightSettled = 0;
    cm_FightLootValue = 0;
    cm_FightStartDialog(a);
    cut_RandSeed(seed);
    cm_CollectSceneChars();
    cm_CollectSceneChars();
    cm_RunSceneParty(a, 0);
    if (cm_FightWinner == 0 && cm_FightSettled == 0)
      cm_RunSceneParty(a, 0);
    if (cm_FightSettled == 0) {
      for (i = 0; i < 16; i++) {
        if (cm_DamagePops[i].h != -1)
          d2_RemoveObj(cm_DamagePops[i].h);
        cm_DamagePops[i].h = -1;
        cm_DamagePops[i].v = 0;
        cm_DamagePops[i].c = 0;
      }
      cm_FightEndDialog(a);
      cm_FightOutro((char *)a);
    } else if (cm_FightLootValue != 0 && cm_FightAttacker->kind == 6) {
      box = 0;
      bld = gm_BuildQuery(1, 1, cm_FightRecord->fight.attackerBld);
      if (bld != 0)
        box = gm_Query(bld->objList, 2, 6, 0, 0x116);
      if (cm_FightLootValue > 0) {
        if (box == 0)
          txt_Format(buf, 0x1144, cm_FightLootValue);
        else
          txt_Format(buf, 0x1145, cm_FightLootValue);
      } else
        txt_Format(buf, 0x1146);
      cm_MessageBox((intptr_t)buf, 0x10);
    }
    cm_EndFightScene(a);
    return;
  }
  sa = 0;
  sb = 0;
  cm_FightAttacker = gm_FindChar(a->members[0]);
  cm_FightDefender = gm_FindChar(a->members[1]);
  for (i = 0; i < 16; i++) {
    id = a->fight.defenders[i];
    if (id != -1 && (ch = gm_FindChar(id)) != 0 && ch->health != 0 &&
        ch->health != 4) {
      sa = (int)(cm_FightStrength(ch) + sa);
      r = util_Random(10);
      gm_AddHealth(ch->id, -r * 20);
    }
  }
  for (i = 0; i < 16; i++) {
    id = a->fight.attackers[i];
    if (id != -1 && (ch = gm_FindChar(id)) != 0 && ch->health != 0 &&
        ch->health != 4) {
      sb = (int)(cm_FightStrength(ch) + sb);
      r = util_Random(10);
      gm_AddHealth(ch->id, -r * 20);
    }
  }
  if (util_Random(30) + sb > util_Random(30) + sa)
    win = cm_FightAttacker;
  else
    win = cm_FightDefender;
  for (i = 0; i < 16; i++) {
    id = a->fight.defenders[i];
    if (id != -1 && (ch = gm_FindChar(id)) != 0)
      cm_FightWeaponLoss(ch);
  }
  for (i = 0; i < 16; i++) {
    if (a->fight.attackers[i] != -1 &&
        (ch = gm_FindChar(a->fight.defenders[i])) != 0)
      cm_FightWeaponLoss(ch);
  }
  if (a->fight.flags & 2) {
    if (win == cm_FightAttacker) {
      e1 = gm_BuildQuery(1, 1, a->fight.attackerBld);
      e2 = gm_BuildQuery(1, 1, a->thing);
      cm_LootStock(e2, e1, cm_FightAttacker, cm_FightDefender);
    }
  } else if (!(a->fight.flags & 4) && (a->fight.flags & 1) &&
             win == cm_FightAttacker) {
    c = gm_BuildQuery(1, 1, a->fight.attackerBld);
    cm_LootCarts(a, c, cm_FightAttacker, cm_FightDefender, 100.0f);
  }
}
/* 0x4d6930, the result of the fight in the record r (+0x354 / +0x358): 0x6f0cf8 set -> 0 and the ransom 0x6f0cfc, else 1 */

void cm_FightResult(CMCUTINFO *r) {
  if (cm_FightSettled != 0) {
    r->result = 0;
    r->lootValue = cm_FightLootValue;
  } else
    r->result = 1;
}
/* 0x4d6970, one frame of the fight UI (r: the fight record): the countdown bar cm_FightTimeBar sized to the fight area,
   the redraws 0x525ff0 .. 0x4ce830, and the click on the button cm_FightButton (while 0x6f0d88 / 0x6f0cf4 are clear) sends
   message 0x50 with the cut entry of the player's character (0x4cdf00) in state 5, else the dialog is closed (0x6f22a0) */

void cm_FightFrame(CMCUTINFO *r) {
  CMCUTENTRY sl;
  CMCUTENTRY *q;

  d2_SetObjValue(cm_FightTimeBar, 0, cm_SceneDuration,
                 cm_SceneDeadline - cm_SceneTicks + 1);
  sv_BorderCameraView();
  cm_UpdatePortraits();
  cm_UpdatePointer();
  cm_ClickSceneChar();
  cm_FightMouse(r);
  cm_UpdateSceneChars();
  cm_UpdateCharInfoWins(r);
  cm_UpdateBombs();
  cm_UpdateGrenades();
  if (cm_SceneTimedOut == 0 && cm_FightWinner == 0) {
    if (d2_ClickedId != -1 && d2_PointerObj == cm_FightButton) {
      q = cm_CutEntrySlot(r, cm_CutChar);
      memcpy(&sl, q, sizeof(CMCUTENTRY));
      sl.charId = cm_CutChar->netId;
      sl.state = 5;
      cm_SendCutEntry(r->playerId, &sl);
    }
  } else
    sv_PopRequest = 1;
}
/* 0x4d6a50, builds the fight UI: the form "cutscenes\combat" (cm_FightForm), the button cm_FightButton (text
   TXT_FIGHT_BUTTON) and the bar cm_FightTimeBar at the bottom, then the portrait boxes (0x4cfe70 / 0x4cfc10) */

void cm_BuildFightUI(CMCUTINFO *a) {
  int v, t;

  v = d2_OpenForm(0, 0, "cutscenes\\combat");
  cm_FightForm = v;
  d2_PlaceMainWindow(v, 3);
  d2_SetForm(v, 0);
  t = d2_WinCreateSlider(0x10, 0xc, 0xbf, txt_Ptrs[TXT_FIGHT_BUTTON],
                         d2_LastWindow);
  cm_FightButton = t;
  d2_Objs[t].centred = 1;
  d2_CenterObj(cm_FightButton);
  t = d2_WinOpenSlider((d2_LastWindowPtr->w - 0x190) / 2, 0x37, 0x190, 0,
                       cm_SceneDuration, 0x83, 0x42, d2_LastWindow);
  cm_FightTimeBar = t;
  d2_Objs[t].font = 0x54;
  d2_Objs[d2_Wins[d2_LastWindow].parent].interactive = 1;
  d2_SetForm(cm_TextBox, 0);
  io_PrintText((intptr_t)"$C");
  cm_ClosePortraits();
  cm_BuildPortraits();
}
/* 0x4d6b70, closes the fight UI: the form cm_FightForm, the marks (0x4d08c0), the portrait boxes */

void cm_CloseFightUI(void) {
  d2_CloseView(cm_FightForm);
  cm_FightForm = 0;
  cm_ClearMarks();
  cm_ClosePortraits();
}
/* 0x4d6ba0, the action of one fighter (f): the target's health is set; a blow (not with the pot 0x174 or the bomb
   0x176) by a fighter that is idle or walking / standing (action 0x2d / 0x3a) shouts the attack (1 in 10), takes the
   damage off the target when it lands and queues the strike: "kampf/schlagen1" without a weapon, else cm_HitAction
   with the weapon's animation (speed 1.4; a landing blow of the weapons 0x16e / 0x172 ends the action), then a pause.
   The pot queues cm_LayBombAction (the thrower's own fight places it at the free cell near him, cm_SendObjCell), the
   bomb cm_ThrowBombAction with the throw sound; both end the action. */

void cm_FighterAct(CMCUTENTRY *f) {
  struct D3SM *h = d3_DefaultScene->hmap;
  AICHAR *c, *tgt, *side;
  AIWEAPON *k;
  CHACTION *x, *ev;
  char *s, *d;
  int dmg, lands, ox, oy;
  float py;

  if (f->state == 0 || f->charId == -1)
    return;
  c = cm_FindFighter(f->charId);
  k = cm_CharWeapon(c);
  side = c->side; /* in a fight: the leader of the fighter's side */
  tgt = cm_FindFighter(f->stateArg);
  if (tgt != 0)
    tgt->v024 = f->health;
  if (!(k != 0 && (k->id == 0x174 || k->id == 0x176))) {
    if (f->turn != 0 &&
        ((x = c->scene->actions) == 0 || x->type == 0x2d || x->type == 0x3a)) {
      if (util_Random(10) > 8) {
        if (side->netId == cm_FightAttacker->netId)
          snd_QueueVoice(c->id, cm_AttackerAttackVoices, "_K_C2C_ANGRIFF", -1,
                         500);
        else
          snd_QueueVoice(c->id, cm_DefenderAttackVoices, "_K_C2C_ANGRIFF", -1,
                         500);
      }
      lands = f->kill;
      dmg = f->damage;
      if (lands != 0)
        tgt->v024 -= dmg;
      if (k == 0)
        ch_QueueAnim(c->scene, "kampf/schlagen1", 1);
      else {
        if (k->id == 0) {
          if (lands != 0)
            ev = ch_AddActionCB(c->scene, cm_HitAction, 8, 0x2e, 1);
          else
            ev = ch_AddActionCB(c->scene, cm_HitAction, 2, 0x2e, 1);
        } else if (lands != 0)
          ev = ch_AddActionCB(c->scene, cm_HitAction, 6, 0x2e, 1);
        else
          ev = ch_AddActionCB(c->scene, cm_HitAction, 2, 0x2e, 1);
        ev->hit.speed = 1.4f;
        ev->hit.victim = tgt;
        ev->hit.hitter = c;
        ev->hit.damage = dmg;
        ev->hit.sideId = side->netId;
        for (s = k->anim, d = ev->u.name; (*d++ = *s++) != 0;)
          ;
        if ((k->id == 0x16e || k->id == 0x172) && lands != 0) {
          f->charId = -1;
          f->state = 0;
        }
      }
      ch_AddAction(c->scene, 0x3b, cm_Random(0x1e) + 0x8c);
    }
  }
  if (k->id == 0x174 && f->kill != 0) {
    ev = ch_AddActionCB(c->scene, cm_LayBombAction, 6, 0x2e, 1);
    ev->pot.victim = tgt;
    ev->pot.thrower = c;
    ev->pot.x = f->x;
    ev->pot.y = f->z;
    strcpy(ev->u.name, "spezial/einhaendig_vom_boden_nehmen");
    if (cm_CutChar->netId == cm_FightOwner) {
      if (!d3_GetHeightAt(h, &c->scene->obj->pos, &cm_PickCellX, &cm_PickCellZ,
                          &py))
        return;
      cm_BestCellNear(c, cm_PickCellX, cm_PickCellZ, 8, &ox, &oy);
      cm_SendObjCell(c->scene->obj->name, ox, oy, 0);
      f->charId = -1;
      f->state = 0;
    }
  }
  if (k->id == 0x176 && f->turn != 0) {
    ev = ch_AddActionCB(c->scene, cm_ThrowBombAction, 5, 0x2e, 1);
    ev->bomb.thrower = c;
    ev->bomb.x = f->x;
    ev->bomb.y = f->z;
    ev->bomb.sideId = side->netId;
    for (s = k->anim, d = ev->u.name; (*d++ = *s++) != 0;)
      ;
    ch_AddAction(c->scene, 0x3b, cm_Random(0x1e) + 0x8c);
    sb_PlaySample(cm_BombSounds, "topfwerfen_s", 1, 0x3f, 0x7f, 0, 0);
    f->charId = -1;
    f->state = 0;
  }
}
/* 0x4d6f60, stops the actions of the fighter in the fight slot f (id, active): 0x405610 on its scene character */

void cm_FightSlotStop(CMCUTENTRY *f) {
  AICHAR *c;

  if (f->state != 0 && f->charId != -1) {
    c = cm_FindFighter(f->charId);
    if (c != 0)
      ch_StopActions(c->scene);
  }
}
/* 0x4d6f90, the cheer of the winner in the fight slot f: event 0x4d3ac0 with the animation "gestik/jubeln" */

void cm_FightSlotCheer(CMCUTENTRY *f) {
  AICHAR *c;
  CHACTION *ev;

  if (f->state != 0 && f->charId != -1) {
    c = cm_FindFighter(f->charId);
    ev = ch_AddActionCB(c->scene, cm_CheerAction, 5, 0x2e, 1);
    ev->cheer.fighter = c;
    strcpy(ev->u.name, "gestik/jubeln");
  }
}
/* 0x4d7000, the fighter slot f picks up the object lying at its place (dummy): the object (0x449690) is marked as
   owned by the character's side (AIOBJ.fightSide), event 0x4d3ae0 */

void cm_FightSlotPickUp(CMCUTENTRY *f) {
  AICHAR *c, *side;
  D3OBJECT *o;
  CHACTION *ev;

  if (f->state != 0 && f->charId != -1) {
    c = cm_FindFighter(f->charId);
    side = c->side;
    ch_StopActions(c->scene);
    o = d3_FindObject(0, 0x40, 0, f->dummy);
    if (o != 0) {
      ((AIOBJ *)o->owner)->fightSide = side->id;
      ev = ch_AddActionCB(c->scene, cm_PickUpAction, 5, 0x2e, 1);
      ev->pickUp.fighter = c;
      ev->pickUp.object = o;
      strcpy(ev->u.name, "spezial/einhaendig_vom_boden_nehmen");
    }
  }
}
/* 0x4d70a0, the fighter slot f puts down the object it carries (AICHAR.v1ac) at its place */

void cm_FightSlotPutDown(CMCUTENTRY *f) {
  AICHAR *c;
  D3OBJECT *o, *body;
  CHACTION *a;

  if (f->state != 0 && f->charId != -1) {
    c = cm_FindFighter(f->charId);
    ch_StopActions(c->scene);
    d3_FindObject(0, 0x40, 0, f->dummy);
    o = c->fightWare;
    if (o != 0) {
      body = c->scene->obj;
      d3_SetWorldPosRot(o, &body->pos, &body->matrix);
      d3if_Show(o, 1);
      c->fightWare = 0;
    }
    a = ch_AddAction(c->scene, 0x2e, 1);
    strcpy(a->u.name, "spezial/einhaendig_vom_boden_nehmen");
  }
}
/* 0x4d7150, the character in the fight slot f is the winner so far (cm_FightWinner): text 0x11b7 */

void cm_FightSlotWinner(CMCUTENTRY *f) {
  char buf[0x100];
  AICHAR *c;

  c = gm_FindChar(f->charId);
  cm_FightWinner = c;
  txt_Format(buf, 0x11b7, c->id);
  sv_SetStatusText(buf);
}
/* 0x4d7190, the escape flag of a fighter action f: the escape dummy named by f gets the fighter as its owner (the
   fighter marked fled, text 0x11b8); when the owner changes the old flag is deleted and a new "ub_FLUCHTFLAGGE" object
   (animated, the texture set 'g' + ref54 of the side leader of the kinds 5 .. 7, named "CONQUER_FLAG") is put at the
   dummy's place (the name of the fled bit is a reasoned guess from the flag). */

void cm_PlantEscapeFlag(CMCUTENTRY *f) {
  AICHAR *c = 0;
  D3OBJECT *o, *r;
  AICHAR *side;
  char buf[0x100];
  D3VECTOR4 pos;
  D3VECTOR rot;
  char k;

  if (f->state != 0) {
    o = d3_FindObject(0, 0x40, 0, f->dummy);
    if (f->charId != -1) {
      c = cm_FindFighter(f->charId);
      c->scene->flags.fled = 1;
      txt_Format(buf, 0x11b8, c->id);
      sv_SetStatusText(buf);
    }
    if (o->owner != c) {
      if (o->flagObj != 0) {
        d3if_Delete(o->flagObj);
        o->flagObj = 0;
      }
      if (c != 0) {
        rot.x = 0;
        rot.y = 0;
        rot.z = 0;
        d3_PointToWorld(o, &o->pos, &pos.v);
        r = d3_CreateObject(0, &pos.v, &rot, "ub_FLUCHTFLAGGE");
        cm_FlagObjects[cm_FlagObjectCount] =
            d3_CreateObject(0, &pos.v, &rot, ch_EmptyName);
        d3t_PlayAnim(r, "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
        side = c->side; /* in a fight: the leader of the fighter's side */
        if (side != 0 && side->ref54 != 0 &&
            (side->kind == 5 || side->kind == 6 || side->kind == 7))
          k = side->ref54 + 'g';
        else
          k = 0;
        if (k != 0)
          d3if_SelectTextureSet(r, r->info, k, 1);
        sprintf(r->name, "CONQUER_FLAG");
        r->owner = 0;
        r->kind = 4;
        r->mask = 1;
        r->stateFlags = (r->stateFlags & 0xf7) | 0x44;
        o->flagObj = r;
      } else
        o->flagObj = 0;
    }
    o->owner = c;
  }
}
/* 0x4d7360, the attack of the fighter c on the fighter g (rec: c's cutscene record): -1 when c cannot attack (a used-up
   weapon of the kinds 1 / 2, c's actions busy). In range (or with a weapon that is not one of the melee kinds) the hit
   is rolled (random 255 against the weapon's accuracy percent of c's skill sk83) with the damage (dmgMin .. dmgMax
   percent of g's life value, * 1.25 when c's side leader has the item 0x2b9); in the player's own fight a melee attack
   also orders the other side's AI to strike back (cm_OrderAttack, unless an order is pending); the fight command 2 goes
   out (cm_SendFightCommand). Out of range c walks to the free cell near g (cm_SendObjCell), unless c holds its place.
   Returns the send slot, -1 when nothing was sent. */

int cm_Attack(CMCUTINFO *rec, AICHAR *c, AICHAR *g) {
  struct D3SM *h = d3_DefaultScene->hmap;
  CMCUTENTRY s;
  AIWEAPON *k;
  AIOBJ *item;
  AICHAR *side;
  CMCUTINFO *other;
  CMCUTENTRY *e;
  int i, n, hit, state;
  int r;

  memset(&s, 0, sizeof(s));
  s.charId = c->netId;
  s.state = 2;
  s.stateArg = g->netId;
  if (c->formation == 1 || c->formation == 2 || c->formation == 3)
    s.held = 1;
  k = cm_CharWeapon(c);
  if (k->kind == 1 || k->kind == 2) {
    item = cm_CharWeaponItem(c);
    if (item != 0 && item->usesLeft <= 0)
      return -1;
  }
  if (!(k->id == 0x154 || k->id == 0x156 || k->id == 0x158 || k->id == 0x16e ||
        k->id == 0x172 || k->id == 0 || k->id == 0x176) ||
      !(cm_CharObjDistXZ(c, g->scene->obj) > k->range)) {
    if (c->scene->actions != 0)
      return -1;
    r = util_Random(0xff);
    side = c->side; /* in a fight: the leader of the fighter's side */
    if (r > 0xff - (int)((k->accuracy * 0.01) * c->sk83))
      hit = 1;
    else
      hit = 0;
    if (hit != 0)
      s.damage = (int)((double)(unsigned int)(cm_Random(k->dmgMax - k->dmgMin) +
                                              k->dmgMin) *
                       g->f01c * 0.01);
    else
      s.damage = 0;
    if (side != 0 && ai_InventoryHas(side, 0x2b9) != 0)
      s.damage = (int)(s.damage * 1.25f);
    s.turn = 1;
    s.kill = hit;
    if (cm_CutChar->netId == cm_FightOwner && k->kind == 0) {
      other = 0;
      n = cm_FightRecord->used;
      for (i = 0; i < n; i++) {
        if (cm_FightRecord->members[i] != -1 && rec != &cm_CutInfos[i]) {
          other = &cm_CutInfos[i];
          break;
        }
      }
      e = cm_CutEntrySlot(other, g);
      if (e->orderSlot == -1 || cm_GetSlotState(e->orderSlot) != 0) {
        state = e->state;
        e->orderSlot = -1;
        if (state == 0) {
          item = cm_CharWeaponItem(g);
          if (item != 0 && item->usesLeft > 0)
            e->orderSlot = cm_OrderAttack(other, g, c, 0, 0);
        }
      }
    }
    cm_SendSetField(c->netId, 0x1c8, 4, 0x20000000, 0);
    return cm_SendFightCommand(c, 2, &s);
  }
  {
    int ix, iz;
    float py;

    if (c->scene->actions != 0 || s.held != 0)
      return -1;
    if (!d3_GetHeightAt(h, &g->scene->obj->pos, &ix, &iz, &py))
      return -1;
    if (cm_FindNearCell(ix, iz, &ix, &iz) == 0)
      return -1;
    return cm_SendObjCell(c->scene->obj->name, ix, iz, 0);
  }
}
