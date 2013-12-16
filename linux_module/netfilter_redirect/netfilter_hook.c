#include <linux/list.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/types.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_ether.h>
#include <uapi/linux/if_packet.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <net/sock.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <net/net_namespace.h>
#include <linux/inet.h>
#include <linux/tcp.h>
#include <linux/list.h>


#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)

#define    ETH    "eth1"
#define    SIP     "192.168.1.104"
#define    DIP     "192.168.65.50"
#define    RIP     "192.168.1.111"

struct skb_priv
{
    struct list_head list;
    struct sk_buffer *skb;
};
static int build_and_xmit_udp(char * eth, u_char * smac, u_char * dmac,
							 u_char * pkt, int pkt_len,u_long sip, u_long dip,
							 u_short sport, u_short dport)
{
    CL_PRINT("eth = %s\n",eth);
	struct sk_buff * skb = NULL;
	struct net_device * dev = NULL;
	struct ethhdr * ethdr = NULL;
	struct iphdr * iph = NULL;
	struct udphdr * udph = NULL;
	u_char * pdata = NULL;

	if(NULL == smac || NULL == dmac)
		goto out;

	if(NULL == (dev= dev_get_by_name(&init_net,eth)))
		goto out;

	skb = alloc_skb(pkt_len + sizeof(struct iphdr) + sizeof(struct udphdr) + LL_RESERVED_SPACE(dev), GFP_ATOMIC);

	if(NULL == skb)
		goto out;

	skb_reserve(skb, LL_RESERVED_SPACE(dev)+sizeof(struct udphdr)+sizeof(struct iphdr));

	skb->dev = dev;
	skb->pkt_type = PACKET_OTHERHOST;
	skb->protocol = __constant_htons(ETH_P_IP);
	skb->ip_summed = CHECKSUM_NONE;
	skb->priority = 0;

    pdata = skb_put(skb, pkt_len);
	{
		if(NULL != pkt)
			memcpy(pdata, pkt, pkt_len);
	}

	skb_push(skb,sizeof(struct udphdr));
	skb_reset_transport_header(skb);
	udph = (struct udphdr *)skb_transport_header(skb);

	skb_push(skb,sizeof(struct iphdr));
	skb_reset_network_header(skb);
	iph = (struct iphdr *)skb_network_header(skb);


	memset(udph, 0, sizeof(struct udphdr));
	udph->source = sport;
	udph->dest = dport;
	skb->csum = 0;
	udph->len = htons(sizeof(struct udphdr)+pkt_len);
	udph->check = 0;

	iph->version = 4;
	iph->ihl = sizeof(struct iphdr)>>2;
	iph->frag_off = 0;
	iph->protocol = IPPROTO_UDP;
	iph->tos = 0;
	iph->daddr = dip;
	iph->saddr = sip;
	iph->ttl = 0x40;
	iph->tot_len = __constant_htons(skb->len);
	iph->check = 0;
	iph->check = ip_fast_csum((unsigned char *)iph,iph->ihl);

	skb->csum = skb_checksum(skb, iph->ihl*4, skb->len - iph->ihl * 4, 0);
	udph->check = csum_tcpudp_magic(sip, dip, skb->len - iph->ihl * 4, IPPROTO_UDP, skb->csum);

	skb_push(skb, 14);
	skb_reset_mac_header(skb);
	ethdr = (struct ethhdr *)skb_mac_header(skb);
	memcpy(ethdr->h_dest, dmac, ETH_ALEN);
	memcpy(ethdr->h_source, smac, ETH_ALEN);
	ethdr->h_proto = __constant_htons(ETH_P_IP);
	skb->ip_summed = CHECKSUM_NONE;

    if(dev_queue_xmit(skb))
    {
        CL_PRINT("dev queue xmit error\n");
    }
out:
    CL_PRINT(" NF ACCEPT\n");
	return(NF_ACCEPT);
}
static struct sk_buff *clone_and_xmit_tcp(struct sk_buff *skb)
{
    __wsum tcp_hdr_csum;
    unsigned short  tcp_len;
    struct sk_buff * new_skb = NULL;
    struct net_device * dev = NULL;
    struct ethhdr * ethdr = NULL;
    struct iphdr * iph = NULL;
    struct tcphdr * tcph = NULL;
    new_skb = skb_copy(skb,GFP_ATOMIC);
    unsigned char  local_mac[ETH_ALEN];
    unsigned char  remote_mac[ETH_ALEN];
    __be32 temp;
    struct ethhdr *nethdr = (struct ethhdr *)skb_mac_header(new_skb);
    memcpy(local_mac, nethdr->h_dest, ETH_ALEN);
    memcpy(remote_mac, nethdr->h_source, ETH_ALEN);

    memcpy(nethdr->h_dest,remote_mac, ETH_ALEN);
    memcpy(nethdr->h_source,local_mac, ETH_ALEN);


    new_skb->csum = 0;

    iph = (struct iphdr *)skb_network_header(new_skb);
    CL_PRINT("source skb ->saddr = %x\n",iph->saddr);
    CL_PRINT("source skb ->daddr = %x\n",iph->daddr);
    temp = iph->saddr;
    iph->saddr = iph->daddr;
    iph->daddr = temp;

    iph->ihl = sizeof(struct iphdr)>>2;

    iph->protocol = 6;
    iph->ttl = 0x40;
    iph->version  = 4;

    iph->check = 0;
    iph->check    = ip_fast_csum( ( unsigned char * )iph, iph->ihl );

    tcp_len = iph->tot_len- sizeof(*iph) ;
    new_skb->csum = 0;

    tcph = tcp_hdr(new_skb);
    tcp_hdr_csum = csum_partial( tcph, tcp_len, 0 );

    tcph->check = csum_tcpudp_magic(  iph->saddr,
                                      iph->daddr,
                                      tcp_len, IPPROTO_TCP,
                                      tcp_hdr_csum );
    new_skb->csum=tcp_hdr_csum;


    dev= dev_get_by_name(&init_net,ETH);
    new_skb->dev = dev;
    new_skb->ip_summed =  CHECKSUM_NONE;
    skb_push(new_skb, 14);
    return new_skb;
}

static unsigned int netfilter_hook_func(unsigned int hooknum,
                                        struct sk_buff *skb,
                                        const struct net_device *in,
                                        const struct net_device *out,
                                        int (*okfn)(struct sk_buff *))
{
    struct iphdr *iph = (struct iphdr *)skb_network_header(skb);
    int ret = NF_ACCEPT;
    struct net_device * dev = NULL;
    struct sk_buff *new_skb;
    struct skb_priv *priv;
    unsigned long flags;
    __be32 temp;
    CL_PRINT("netfilter hook \n");
    if(iph->protocol == IPPROTO_TCP && iph->daddr ==in_aton(RIP) )
    {
        iph = (struct iphdr *)skb_network_header(new_skb);
        temp = iph->saddr;
        new_skb = clone_and_xmit_tcp(skb);
        iph = (struct iphdr *)skb_network_header(new_skb);
        iph->daddr = temp;

        if( dev_queue_xmit(new_skb))
        {
            CL_PRINT("dev queue xmit error\n");
        }
        return NF_DROP;
    }
    return ret;
}

static struct nf_hook_ops redirect_hook_ops[]=
{
    {
        .hook           = netfilter_hook_func,
        .owner          = THIS_MODULE,
        .pf             = PF_INET,
        .hooknum        = NF_INET_PRE_ROUTING,
        .priority       = NF_IP_PRI_LAST,
    }
};

int netfilter_hook_init(void)
{
    printk("netfilter_hook_init\n");
    int ret;
    ret = nf_register_hooks(redirect_hook_ops, ARRAY_SIZE(redirect_hook_ops));

}

static void netfilter_hook_exit(void)
{
    printk("netfilter_hook_exit\n");
    nf_unregister_hooks(redirect_hook_ops, ARRAY_SIZE(redirect_hook_ops));
}

module_init(netfilter_hook_init);
module_exit(netfilter_hook_exit);

MODULE_AUTHOR("leisheyoufu");
MODULE_LICENSE("GPL");




