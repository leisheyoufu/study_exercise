#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "raw_socket.h"

#define FROM_IP_ADDR "192.168.1.72"
#define TO_IP_ADDR "192.168.1.13"
#define FROM_PORT 5001
#define TO_PORT 5000

int init_sockfd(char * saddr,int sport, char * daddr, int dport,struct sockaddr_in * sock_saddr,struct sockaddr_in * sock_daddr)
{
    int sockfd;
    if( (sockfd = socket(AF_INET,SOCK_RAW,IPPROTO_RAW)) < 0) {
        perror("socket");
        exit(1);
    }

    sock_saddr->sin_family = AF_INET;
    sock_saddr->sin_port =  htons(sport);
    sock_saddr->sin_addr.s_addr = inet_addr(saddr); // 本机网口所绑定的IP地址
    bzero(&(sock_saddr->sin_zero),8);
    bind(sockfd, (struct sockaddr *)&sock_saddr, sizeof(struct sockaddr));
    bzero(&(sock_daddr->sin_zero),8);
    sock_daddr->sin_family=AF_INET;
    sock_daddr->sin_port=htons(dport);
    sock_daddr->sin_addr.s_addr = inet_addr(daddr); //真实可达的IP地址
    //  addr


    return sockfd;
}
int main()
{
    unsigned char packet[sizeof(struct iphdr) + sizeof(struct tcphdr)+20];
    unsigned char *msg;
    int count = 0;
    int bs = 1;
    unsigned short sport,dport;
    int sockfd;
    unsigned long seq, ack;
    struct sockaddr_in sock_saddr,sock_daddr;
    struct in_addr in_saddr,in_daddr;
    struct tcphdr *tcp;
    sport = FROM_PORT;
    dport = TO_PORT;

    sockfd = init_sockfd(FROM_IP_ADDR,sport,TO_IP_ADDR,dport,&sock_saddr,&sock_daddr);
    in_saddr = sock_saddr.sin_addr;
    in_daddr = sock_daddr.sin_addr;

    if( setsockopt(sockfd,IPPROTO_IP,IP_HDRINCL, (char *)&bs, sizeof(bs)) < 0) {
        perror("setsockopt");
        exit(1);
    }

    srand(getpid());

    seq = rand()%time(NULL);
    ack = rand()%time(NULL);
    ip_gen(packet,IPPROTO_TCP,in_saddr,in_daddr,sizeof(packet));

    tcp = (struct tcphdr *)(packet + sizeof(struct iphdr));
    tcp_gen((char *)tcp,sport,dport,seq,ack);
    /*
    tcp->check = trans_check(IPPROTO_TCP,(char *)tcp,
    		   sizeof(struct tcphdr),
    		   in_saddr,
    		   in_daddr);
    */
    printf("start send\n");
    msg =  (char*)(packet + sizeof(struct iphdr)+sizeof(struct tcphdr));
    strcpy(msg,"hello world");
    if(sendto(sockfd,packet,sizeof(packet),0x0,(struct sockaddr *)&sock_daddr,
              sizeof(sock_daddr)) != sizeof(packet)) {
        perror("sendto");
        exit(1);
    }

    /*

    	while( count < 50)
    	{
    		if (sendto(sock_fd,pkt_msg,msg_len,0,(struct sockaddr *)&to_addr,sizeof (struct sockaddr)) == -1)
    		{
    		perror("sendto ");
    		usleep(10);
    		}
    	}

    */
    close(sockfd);
    return 0;
}
