#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void signal_handler1(int sig)
{
	printf("receive a %d signal!\n",sig);
	exit(0);
	//sigaction(SIGINT,SIG_DFL,NULL);
}

void signal_handler2(int sig)
{
	printf("child receive a %d signal!\n",sig);
	printf("child exit\n");
	exit(0);
}

void alarm_handler()
{
	printf("received alarm signal\n");
}

int main()
{
	pid_t pid;
	struct sigaction sac1,sac2;
	sac1.sa_handler = signal_handler1;
	sac2.sa_handler = signal_handler2;

	if((pid = fork()) == -1)
	{
		printf("Error in fork\n");
		exit(1);
	}
	if(pid == 0)
	{
		printf("child process created\n");
		sigaction(SIGINT,&sac2,NULL);
		while(1)
		{
		}
	}
	else
	{	
		sigaction(SIGINT,&sac1,NULL);
		signal(SIGALRM,alarm_handler);
		alarm(3);
		sleep(5);
		kill( pid,SIGINT);
		while(1)
		{
			sleep(1);
		}
	}
	return 0;
}
