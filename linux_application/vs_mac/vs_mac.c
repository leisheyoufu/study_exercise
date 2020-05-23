#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>

#include <linux/if_packet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include "util_mac.h"
#define BUFFER_MAX 1024
#define ETH_ALEN 6
#define MASK(n) (((1ULL<<n))-1)

#define REDIRECT 1
#define OK 0
#define VSTRONG_PROTOCOL 0x0807
#define IF_NAME "eth0"


#define DEST_IP "192.168.1.13"
#define LOCAL_MAC "00:0c:29:55Ld2:87"
#define DEST_MAC "e0:b9:a5:af:8a:94"



typedef struct iphdr { //定义IP首部
    unsigned char h_verlen; //4位首部长度+4位IP版本号
    unsigned char tos; //8位服务类型TOS
    unsigned short total_len; //16位总长度（字节）
    unsigned short ident; //16位标识
    unsigned short frag_and_flags; //3位标志位
    unsigned char ttl; //8位生存时间 TTL
    unsigned char proto; //8位协议 (TCP, UDP 或其他)
    unsigned short checksum; //16位IP首部校验和
    unsigned int source_ip; //32位源IP地址
    unsigned int dest_ip; //32位目的IP地址
} __attribute__((packed));

typedef struct udphdr { //定义UDP首部
    unsigned short uh_sport;    //16位源端口
    unsigned short uh_dport;    //16位目的端口
    unsigned int uh_len;//16位UDP包长度
    unsigned int uh_sum;//16位校验和
} __attribute__((packed));

typedef struct tcphdr { //定义TCP首部
    unsigned short th_sport; //16位源端口
    unsigned short th_dport; //16位目的端口
    unsigned int th_seq; //32位序列号
    unsigned int th_ack; //32位确认号
    unsigned char th_lenres;//4位首部长度/6位保留字
    unsigned char th_flag; //6位标志位
    unsigned short th_win; //16位窗口大小
    unsigned short th_sum; //16位校验和
    unsigned short th_urp; //16位紧急数据偏移量
} __attribute__((packed));


typedef struct icmphdr {
    unsigned char  icmp_type;
    unsigned char icmp_code; /* type sub code */
    unsigned short icmp_cksum;
    unsigned short icmp_id;
    unsigned short icmp_seq;
    /* This is not the std header, but we reserve space for time */
    unsigned short icmp_timestamp;
} __attribute__((packed));


struct eth_hdr {
    unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
    unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
    __be16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));


int analyse_eth(struct eth_hdr *eth)
{
    char *p;
    p = (char *)eth;
    int n = MASK(8);
    printf("MAC: %.2X:%02X:%02X:%02X:%02X:%02X==>"
           "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X  proto_id = %u\n",
           p[6]&n, p[7]&n, p[8]&n, p[9]&n, p[10]&n, p[11]&n,
           p[0]&n, p[1]&n, p[2]&n, p[3]&n, p[4]&n, p[5]&n,
           eth->h_proto);
    // change dest mac when the packet is mime
    if(mac_compare(eth->h_dest,LOCAL_MAC)== 0 ) {
        printf("Now change the mac \n");
        COPY_STR2MAC(eth->h_dest,DEST_MAC);
        return REDIRECT;
    }
    return OK;
}

void analyse_tcp(struct tcphdr* tcp)
{
    printf("TCP -------------\n");
    printf("port :%u  ====>  %u \n",ntohs(tcp->th_sport),
           ntohs(tcp->th_dport));
}

void analyse_udp(struct udphdr* udp)
{
    printf("UDP -------------\n");
    printf("port :%u  ====>  %u \n",ntohs(udp->uh_sport),
           ntohs(udp->uh_dport));
}

void analyse_icmp(struct icmphdr *icmp)
{
    printf("ICMP -------------\n");
    printf("type :%u \n",icmp->icmp_type);
    printf("sub code : %u\n",icmp->icmp_code);
}


void analyse_ip(struct iphdr *iph)
{
    unsigned char *src = (unsigned char *)&iph->source_ip;
    unsigned char *des = (unsigned char *)&iph->dest_ip;
    int m = MASK(8);
    char *p = (char*) iph;
    p+=sizeof(struct iphdr);
    printf("ip  %u.%u.%u.%u ===> %u.%u.%u.%u\n",
           src[0]&m,src[1]&m,src[2]&m,src[3]&m,
           des[0]&m,des[1]&m,des[2]&m,des[3]&m);
    printf("Protocol: ");
    switch(iph->proto) {
    case IPPROTO_ICMP:
        analyse_icmp((struct icmphdr*)p);
        break;

    case IPPROTO_IGMP:
        printf("IGMP\n");
        break;
    case IPPROTO_IPIP:
        printf("IPIP\n");
        break;
    case IPPROTO_TCP :
        analyse_tcp((struct tcphdr *)p);
        break;
    case IPPROTO_UDP :
        analyse_udp((struct udphdr *)p);
        break;
    case IPPROTO_RAW :
        printf("RAW\n");
        break;
    default:
        printf("Unkown, please query in include/linux/in.h\n");
    }

}

void capture(int sock, struct sockaddr_ll *st_eth_addr)
{
    int i;
    int n_read,proto;
    char buffer[BUFFER_MAX];
    char *p;
    int ret;


    //	char *ethhead, *iphead, *tcphead, *udphead, *icmphead, *p;

    while(1) {
        n_read = recvfrom(sock, buffer, BUFFER_MAX, 0, NULL, NULL);
        /*
           14   6(dest)+6(source)+2(type or length)
           +
           20   ip header
           +
           8   icmp,tcp or udp header
           = 42
           */
        if(n_read < 42) {
            fprintf(stdout, "Incomplete header, packet corrupt\n");
            continue;
        }
        p = buffer;
        ret = analyse_eth((struct eth_hdr*)p);

        if(ret == REDIRECT) {
            unsigned short eth_len = n_read;
            char *eth_msg = buffer;
            p+=sizeof(struct eth_hdr);

            printf("nread %u \n",n_read);
            // printf("eth_len = %u\n", ntohs(ip_hdr->total_len)+sizeof(struct eth_hdr));  // eaqual
            unsigned long dest_ip;
            inet_pton(AF_INET, DEST_IP, &dest_ip);
            //  ip_hdr->dest_ip = dest_ip;
            analyse_ip((struct iphdr*)p);
            if(sendto(sock,eth_msg,eth_len,0x0,(struct sockaddr *)st_eth_addr,
                      sizeof(*st_eth_addr)) != eth_len) {
                printf("buffer len = %u\n",eth_len);
                perror("sendto");
                free(eth_msg);
                exit(1);
            }
        }
        // analyse_ip((struct iphdr*)p);
    }

}

int get_eth_index(char *eth_name)
{
    struct ifreq req;
    int sockfd;
    int ret;
    int index;
    sockfd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_IP));//这个sd就是用来获取eth0的index，完了就关闭 d = socket(PF_INET,SOCK_DGRAM,0) AF_INET,SOCK_DGRAM,0 SOCK_PACKET

    if(sockfd < 0) {
        perror("create sd ");
        exit(0);
    }
    strncpy(req.ifr_name,IF_NAME,sizeof(IF_NAME));
    ret=ioctl(sockfd,SIOCGIFINDEX,&req);
    if(ret < 0) {
        perror("SIOCGIFINDEX ");
    }
    printf("%s index = %u\n",IF_NAME,req.ifr_ifindex);
    close(sockfd);
    index = req.ifr_ifindex;
    return index;
}

void init_tag_addr(struct sockaddr_ll *st_eth_addr,int index)
{
    memset(st_eth_addr, 0, sizeof(*st_eth_addr));
    st_eth_addr->sll_family = PF_PACKET;
    st_eth_addr->sll_protocol = htons(VSTRONG_PROTOCOL);
    st_eth_addr->sll_ifindex = index;// eth index
    st_eth_addr->sll_pkttype = PACKET_OUTGOING; // out packet
    st_eth_addr->sll_halen = 6; // MAC len
}

int main(int argc, char *argv[])
{
    int sock, n_read, proto;
    char buffer[BUFFER_MAX];
    struct sockaddr_ll st_eth_addr;
    char *ethhead, *iphead, *tcphead, *udphead, *icmphead, *p;
    int ret,index;

    index = get_eth_index(IF_NAME);
    init_tag_addr(&st_eth_addr,index);

    if((sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_IP))) < 0) {
        printf("create socket error\n");
        exit(0);
    }
    capture(sock,&st_eth_addr);
    close(sock);

}
