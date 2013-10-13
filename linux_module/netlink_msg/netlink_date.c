
#include <linux/list.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/types.h>
#include <net/sock.h>
#include <net/netlink.h> 
#include <linux/timex.h>
#include <linux/rtc.h>

#define NETLINK_TEST 25

#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define MAX_MSG_LEN 128
struct sock *nl_sk = NULL;
struct nl_msg{
	int type;  // len include the length of str and the nl_msg header
	int len;
	char str[MAX_MSG_LEN];
};
static enum TYPE
{
	HELLO=1,
	JIFFIES,
	DATE
};
static int g_pid;
static char reply[MAX_MSG_LEN];

static void sendnlmsg(struct nl_msg *snd_nlmsg)
{
	struct sk_buff *skb;
	struct nlmsghdr *nlh;
	int len = NLMSG_SPACE(snd_nlmsg->len+ offsetof(struct nl_msg,str));

	skb = alloc_skb(len,GFP_KERNEL);
	if(!skb)
	{
		CL_PRINT("alloc skb error\n");
	}
	nlh = nlmsg_put(skb,0,0,0,len-NLMSG_HDRLEN,0);
	memcpy(NLMSG_DATA(nlh),snd_nlmsg,snd_nlmsg->len);
	netlink_unicast(nl_sk,skb,g_pid,MSG_DONTWAIT);
}


void sendmsg(char *message,int type)
{
	struct nl_msg snd_nlmsg;

	if(!message || !nl_sk)
	{
		return ;
	}

	int msglen = strlen(message)+1;
	memcpy(snd_nlmsg.str,message,msglen);
	snd_nlmsg.len= msglen+offsetof(struct nl_msg,str); 
	CL_PRINT("snd_nlmsg -> len = %d\n",snd_nlmsg.len);
	snd_nlmsg.type = type;
	sendnlmsg(&snd_nlmsg);
}

static void send_date()
{
	struct timex txc;
	struct rtc_time tm;
	char message[64];
	do_gettimeofday(&(txc.time));
	rtc_time_to_tm(txc.time.tv_sec,&tm);
	sprintf(message,"UTC time : %d-%d-%d %d:%d:%d \n",
			tm.tm_year+1900,tm.tm_mon,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
	sendmsg(message,DATE);
}

static void recv_handler(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	static struct nl_msg rcv_nlmsg;
	u32 rcv_len;
	CL_PRINT("recv in kernel\n");
	while(skb->len>= NLMSG_SPACE(0))
	{
		memset(&rcv_nlmsg,0,sizeof(rcv_nlmsg));
		nlh = nlmsg_hdr(skb);
		rcv_len = NLMSG_ALIGN(nlh->nlmsg_len);
		if(rcv_len > skb->len)
			rcv_len = skb->len;
		memcpy(&rcv_nlmsg,NLMSG_DATA(nlh),rcv_len);
		CL_PRINT("receive data = %s\n",rcv_nlmsg.str);
		g_pid = nlh->nlmsg_pid;
		skb_pull(skb,rcv_len);
	}
	if(rcv_nlmsg.type==HELLO)
	{
		char *reply = "I have received!";
		sendmsg(reply,1);
	}
	
	if(rcv_nlmsg.type==JIFFIES)
	{
		char reply[12];
		sprintf(reply,"%ld\n",jiffies);
		sendmsg(reply,2);
	}

	if(rcv_nlmsg.type==DATE)
	{
		send_date();
	}

}

int netlink_init(void)
{
	printk("netlink init\n");

	struct netlink_kernel_cfg cfg = {	
		.input	= recv_handler,	
		.groups	= 1,	};
	
	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST, &cfg
									);
	
	if(!nl_sk){
		   printk(KERN_ERR " %s my_net_link: create netlink socket error.\n",__func__);
		   return 1;
	   }
	
	

    return 0;
}

static void netlink_exit(void)
{
    if(nl_sk != NULL){
        sock_release(nl_sk->sk_socket);
    }

    printk("my_net_link: self module exited\n");
	

}




module_init(netlink_init);
module_exit(netlink_exit);

MODULE_AUTHOR("ChengLong");
MODULE_LICENSE("GPL");




