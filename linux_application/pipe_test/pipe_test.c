#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BUFFER_LEN 128
#define INPUT 0
#define OUTPUT 1


int main()
{
	int pipe_fd[2];
	pid_t pid;
	char buf[BUFFER_LEN];
	int count;
	pipe(pipe_fd);
	if ((pid = fork()) == - 1)
	{
		printf("Error in fork\n");
		exit(1);
	}
	if (pid == 0)
	{
		FILE *fp;
		char child_buf[BUFFER_LEN];
		int popen_count;
		printf("in the (child) process...\n");
		// close the input pipe
		close(pipe_fd[INPUT]);
		//popen open a new child process
		fp = popen("cat /etc/passwd","r");
		popen_count = fread(child_buf,BUFFER_LEN-1,1,fp);
		buf[BUFFER_LEN-1] = '\0';
		write(pipe_fd[OUTPUT], child_buf,BUFFER_LEN);
		exit(0);
	}
	else
	{
		printf("in the (parent) process...\n");
		// father close the output pipe
		close(pipe_fd[OUTPUT]);
		// father get data from input pipe
		count = read(pipe_fd[INPUT], buf, sizeof(buf));
		printf("%d bytes of data received from child process form pipe is: %s\n",
				count, buf);
		return 0;
	}
}


