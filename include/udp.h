/* udp.c -- UDP broadcast and LAN server scan, original file name unknown.
   Extent in GildeGold.exe (inferred): 0x401d50..0x402140. Names are ours. */
#ifndef UNK_401D50_H
#define UNK_401D50_H

#include "udp_types.h" /* UDPINFO1 / UDPINFO4 / UDPPACKET / UDPSERVER */

void udp_Init(unsigned short port); /* 0x401d50 */
void udp_Exit(void);                /* 0x401e50 */
void udp_Send(char *buf, int len);  /* 0x401e70 */
int udp_FindServers(unsigned short port, unsigned long timeout,
                    struct UDPSERVER *list, int max); /* 0x401ea0 */

#endif
