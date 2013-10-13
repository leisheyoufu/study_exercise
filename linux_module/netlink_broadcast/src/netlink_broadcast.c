#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <asm/types.h>
#include <linux/netlink.h>
#include <linux/socket.h>
#include <errno.h>


#include <strings.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifdef HAVE_LIBWRAP
#include <tcpd.h>
#endif

#define _GNU_SOURCE
#include <getopt.h>
#include <signal.h>




#define NETLINK_TEST 26
#define MAX_PAYLOAD 1024
#define CL_PRINT(fmt,args...) printf("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

static enum TYPE
{
	HELLO =1,
	JIFFIES,
	DATE
};

// this struct is the same as the kernel
struct nl_msg{
	int type;
	int len;
	char str[MAX_PAYLOAD];
};
struct msghdr msg;  // must exist when send


int sock_fd,retval;
struct sockaddr_nl src_addr,dest_addr;

void init_addr()
{
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid  = 0;
	src_addr.nl_groups = 1<<(5-1); // broadcast mask
	dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;
}

void send_nlmsg(char *pmsg,int type)
{
	struct nlmsghdr *nlh;
	struct nl_msg snd_msg;
	struct iovec iov;
	// the length of nlh is the nl length will be sent
	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
	nlh->nlmsg_len = NLMSG_SPACE(strlen(pmsg)+offsetof(struct nl_msg,str));
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;
	strncpy(snd_msg.str,pmsg,strlen(pmsg));
	snd_msg.type = type;
	snd_msg.len = strlen(pmsg);
	memcpy(NLMSG_DATA(nlh),&snd_msg,nlh->nlmsg_len);
	iov.iov_base = (void*)nlh;
	iov.iov_len = (nlh->nlmsg_len);
	msg.msg_name=(void*)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen =1;
	retval = sendmsg(sock_fd,&msg,0);
	free(nlh);
}

void recv_nlmsg(char *pmsg)
{
	struct nlmsghdr *nlh;
	struct iovec iov;
	struct nl_msg rcv_nlmsg;
	int msg_len;
	int i =0;
	iov.iov_len=NLMSG_SPACE(MAX_PAYLOAD);
	nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
	memset(nlh,0,NLMSG_SPACE(MAX_PAYLOAD));

	iov.iov_base = (void*)nlh;
	msg.msg_iov = &iov;
	msg.msg_iovlen =1;

	retval = recvmsg(sock_fd,&msg,0);
	char *temp = msg.msg_iov[0].iov_base;
	temp[retval] = '\0';
	printf("get message: %s",temp);
		
	if(retval >0)
	{
	
		memcpy(&rcv_nlmsg,NLMSG_DATA(nlh),128);
		printf("len = %d\n",rcv_nlmsg.len);
		
		rcv_nlmsg =* (struct nl_msg *)NLMSG_DATA(nlh);
	
		printf("Received len = %d\n",rcv_nlmsg.len);
		msg_len = rcv_nlmsg.len-offsetof(struct nl_msg,str);
		printf("Received type = %d\n",rcv_nlmsg.type);
		memcpy(pmsg,rcv_nlmsg.str,msg_len);
		printf("Received message :%s\n",pmsg);
		
		printf("cl\n");
	}
	free(nlh);


	
}



int main()
{
	char pmsg[1024];
	init_addr();

	
	printf("init data \n");
	sock_fd = socket(AF_NETLINK,SOCK_RAW,NETLINK_TEST);
	if(sock_fd== -1)
	{
		CL_PRINT("error getting socket: %s",strerror(errno));
		return -1;
	}
	retval = bind(sock_fd,(struct sockaddr*)&src_addr,sizeof(src_addr));
	
	if(retval < 0)
	{
		printf("bind_failed:%s",strerror(errno));
		close(sock_fd);
		return -1;
	}
	
	printf("waiting for...\n");
	recv_nlmsg(pmsg);
	printf("main %s\n",pmsg);
	close(sock_fd);

	return 0;
}
