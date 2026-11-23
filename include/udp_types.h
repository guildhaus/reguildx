/* udp_types.h -- the records of udp.c's LAN server scan (udp.h), types only: cm_types.h declares the network game
   cm_NetGame with them. */
#ifndef UDP_TYPES_H
#define UDP_TYPES_H

#include "ls_types.h"                     /* NETHDR */

#pragma pack(push, 8)                     /* natural layout (UDPSERVER.flags at 0x7c) wherever it is included */
typedef struct UDPINFO1 {           /* 0x2a bytes, server answer version 1 */
    short type;                     /* 1 */
    short version;                  /* 1 */
    short magic;                    /* 0x6a */
    char data[0x24];
} UDPINFO1;

typedef struct UDPINFO4 {           /* 0x6a bytes, server answer version 4 */
    short type;
    short version;                  /* 4 */
    short magic;
    char data[0x64];
} UDPINFO4;

typedef union UDPPACKET {           /* 0x100 bytes, receive buffer */
    struct {
        short type;
        short version;
        short magic;
    };
    UDPINFO1 v1;
    UDPINFO4 v4;
    char raw[0x100];
} UDPPACKET;

typedef struct UDPSERVER {          /* 0x80 bytes, a server of the LAN scan (udp_FindServers); cm_NetGame, the network game
                                       hosted or joined, is one (main_SearchNetworkGame copies the picked entry over it,
                                       main_HostNetworkGame writes info.game) */
    char ip[16];
    union {
        UDPINFO1 v1;
        UDPINFO4 v4;
        NETHDR game;                /* v4 is the host's network game record (main_SearchNetworkGame reads its
                                       name, players, save name and party table) */
    } info;                         /* 0x10 */
    int flags;                      /* 0x7c, 0x3f (version 1) or 0x7f (version 4); of cm_NetGame: 0x3f a new game,
                                       0x7f a saved one (was ai_ModeMask) */
} UDPSERVER;

#pragma pack(pop)

#endif
