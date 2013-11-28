#ifndef RAW_SOCKET_H_INCLUDED
#define RAW_SOCKET_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netinet/in_systm.h>
#include <netinet/ip.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/tcp.h>
#include <unistd.h>
#include <time.h>
#define IPVERSION 4
#define DEFAULT_TTL 60

void ip_gen(char *packet,unsigned char protocol,struct in_addr saddr,
            struct in_addr daddr,unsigned short length);
unsigned short in_cksum(unsigned short *addr,int len);  // addr is the buf address
unsigned short trans_check(unsigned char proto,
                           char *packet,
                           int length,
                           struct in_addr source_address,
                           struct in_addr dest_address);

#endif // RAW_SOCKET_H_INCLUDED
