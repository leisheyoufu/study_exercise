#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define LOOP_TIME 50
#define BUF_LEN 128

int cpu_nums;

int read_thread(char *path)
{
	FILE *fd;
	int count;
	char buf[BUF_LEN];
	pthread_t tid = pthread_self();
	for(;;)
	{

		if( (fd=fopen(path,"r")) !=NULL)
		{
			count = fread(buf,BUF_LEN,1,fd);
			if(buf[0]!='\0')
				printf("tid %u read buf is %s\n",tid,buf);
			else
				printf("tid read buf is NULL\n");
			memset(buf,0,sizeof(buf));

			fclose(fd);
		}
		sleep(2);
	}
	pthread_exit((void *)tid);
}

int write_thread(char *path)
{
	FILE *fd;
	int count;
	char *buf = "thread buf";
	pthread_t tid = pthread_self();
	int index = 0;
	for(;;)
	{

		if( (fd=fopen(path,"w")) !=NULL)
		{
			char temp[BUF_LEN];
			index++;
			sprintf(temp,"%s %d",buf,index);
			count = fwrite(temp,strlen(temp),1,fd);
			printf("tid %u write buf is %s \n",tid,temp);
			fclose(fd);

		}
		sleep(1);
	}
	pthread_exit((void *)tid);
}

int main()
{
	pthread_t tid[5];
	void *result;
	int i;
	cpu_nums = sysconf(_SC_NPROCESSORS_CONF);
	int thread_num = cpu_nums;
	if(thread_num == 1)
	{
		thread_num = 2;
	}
	
	printf("create thread\n");
	char *path = "/dev/vir_cdev1";
	if(pthread_create(&tid[0],NULL,(void *)write_thread,path))
	{
		printf("main :create write thread %u\n",tid[0]);
	}
	

	for(i=1;i< thread_num;i++)
	{
		if(pthread_create(&tid[i],NULL,(void*)read_thread,path))
		{
			printf("main: create read thread %u\n",tid[i]);
		}
	}
	
	
	if( pthread_join(tid[0],&result) ==0)
	{
		printf("thread %u return result=%u\n",tid,(int)result);
	}
	
	return 0;
}
			


