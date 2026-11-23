/* Views into packed data objects (the source of truth; edit by hand, `dcp rename` renames).

   The original packs its data area: a name whose address lies inside a larger object is a
   view of that storage, not an object of its own.  Each line is one such name: the type, the
   container, the byte offset and the view's address.  dcp checks that the address is the
   container's plus the offset (L15).  The full link keeps the name inside its container, as
   the original does.  (First written by rea's tools/data_views.py, rea 8cef7d5b.) */
#ifndef DATA_VIEWS_H
#define DATA_VIEWS_H

/* d3_Scenes */
/* clang-format off */
#define ai_MapRefs               (d3_Scenes[0].map)  /* 0xfd7c4c, the town scene's terrain map */
/* clang-format on */

#endif
