#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define BUF_MAX 128
#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000

void conn(char *ip_addr)
{
	int  sockfd;
	char recvline[BUF_MAX + 1];
	struct sockaddr_in  servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error\n");
		exit(1);

	}
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(SERV_PORT);   
	if (inet_pton(AF_INET, ip_addr, &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error\n");
		exit(1);
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
	{
		printf("connect error\n");
		exit(1);
	}
	char input[100];
	sprintf(input,"client %d send",getpid());
	sleep(5);
	write(sockfd, input, strlen(input));
	memset(recvline,0,sizeof(recvline));

	int n = 0;
	int count = 0;
	while (1)
	{
		n = read(sockfd, recvline + count, BUF_MAX);

		if (n == BUF_MAX)
		{
			break;
		}
		else
		{
			count +=n;
		}
	}
	printf("%s\n", recvline);

	close(sockfd);
	exit(0);

}

int main(int argc, char **argv)
{
	pid_t pid;
	if (argc != 2)
	{
		printf("no ip address\n");
		exit(1);
	}
	while(1)
	{
		if((pid = fork()) == 0)
		{
			conn(argv[1]);
		}
		else
		{
			sleep(1);

		}
	}
	return 0;
}
