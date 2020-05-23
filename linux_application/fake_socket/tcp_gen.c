#include "raw_socket.h"

#define TH_OFFSET 5
#define TCP_WINDOW_SIZE 512
struct psuedohdr  {
    struct in_addr source_address;
    struct in_addr dest_address;
    unsigned char place_holder;
    unsigned char protocol;
    unsigned short length;
} psuedohdr;

unsigned short trans_check(unsigned char proto,
                           char *packet,
                           int length,
                           struct in_addr source_address,
                           struct in_addr dest_address)
{
    char *psuedo_packet;
    unsigned short answer;

    psuedohdr.protocol = proto;
    psuedohdr.length = htons(length);
    psuedohdr.place_holder = 0;

    psuedohdr.source_address = source_address;
    psuedohdr.dest_address = dest_address;

    if((psuedo_packet = malloc(sizeof(psuedohdr) + length)) == NULL)  {
        perror("malloc");
        exit(1);
    }

    memcpy(psuedo_packet,&psuedohdr,sizeof(psuedohdr));
    memcpy((psuedo_packet + sizeof(psuedohdr)),
           packet,length);

    answer = (unsigned short)in_cksum((unsigned short *)psuedo_packet,
                                      (length + sizeof(psuedohdr)));
    free(psuedo_packet);
    return answer;
}


void tcp_gen(char *packet,unsigned short sport,
             unsigned short dport,unsigned long seq,
             unsigned long ack)
{
    struct tcphdr *tcp;

    tcp = (struct tcphdr *)packet;
    memset((char *)tcp,'\0',sizeof(struct tcphdr));
    tcp->source = htons(sport);
    tcp->dest = htons(dport);

    tcp->seq = htonl(seq);
    tcp->ack_seq = htonl(ack);

    tcp->res1 = 0;
    tcp->doff = TH_OFFSET;

    tcp->window = htons(TCP_WINDOW_SIZE);
    tcp->fin = 0;
    tcp->syn = 1;
    return;
}
