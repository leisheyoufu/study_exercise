#include "raw_socket.h"

unsigned short in_cksum(unsigned short *addr,int len)
{
    register int sum = 0;
    unsigned short answer = 0;
    register unsigned short *w = addr;
    register int nleft = len;

    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }

    //  mop up an odd byte, if necessary
    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)w ;
        sum += answer;
    }
    // add back carry outs from top 16 bits to low 16 bits //
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return answer;
}


void ip_gen(char *packet,unsigned char protocol,struct in_addr saddr,
            struct in_addr daddr,unsigned short length)
{
    struct iphdr *iphdr;
    iphdr = (struct iphdr *)packet;
    memset((char *)iphdr,'\0',sizeof(struct iphdr));
    iphdr->ihl = 5;
    iphdr->version = IPVERSION;
    iphdr->tot_len = htons(length);
    iphdr->id = htons(getpid());
    iphdr->ttl = DEFAULT_TTL;
    iphdr->protocol = protocol;

    iphdr->saddr = saddr.s_addr;
    iphdr->daddr = daddr.s_addr;

    iphdr->check = (unsigned short)in_cksum((unsigned short *)iphdr,
                                            sizeof(struct iphdr));
}
