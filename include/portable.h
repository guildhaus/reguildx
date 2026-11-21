/* portable.h -- pointer-sized integers for the values the original passes as "a small id or a pointer" in one
   parameter (io_PrintText's text id or string, sv_MessageBox, txt_Format, cm_MessageBox ..) and for address
   arithmetic that must stay integral. VC6 has no <stdint.h>: its intptr_t / uintptr_t are int / unsigned int,
   byte-identical to the int the original used; any other compiler takes the standard header. */
#ifndef PORTABLE_H
#define PORTABLE_H

#if defined(_MSC_VER) && _MSC_VER < 1600
#ifndef _INTPTR_T_DEFINED
typedef int intptr_t;
#define _INTPTR_T_DEFINED
#endif
#ifndef _UINTPTR_T_DEFINED
typedef unsigned int uintptr_t;
#define _UINTPTR_T_DEFINED
#endif
#else
#include <stdint.h>
#endif

#endif
