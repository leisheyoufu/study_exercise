#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

#define BUFFER_SIZE 4096
#define FILE1 "linux-3.10.1.tar.xz"
#define FILE2 "output1"
#define FILE3 "output2"

void old_copy(char *infile,char *outfile)
{
	int from_fd,to_fd;
	int bytes_read,bytes_write;
	char buffer[BUFFER_SIZE];
	char *ptr;
	if( (from_fd = open(infile,O_RDONLY)) == -1)
	{
		return;
	}
	if( (to_fd = open(outfile,O_RDWR|O_CREAT)) == -1)
	{
		return;
	}

	while(bytes_read=read(from_fd,buffer,BUFFER_SIZE))
	{
		/* 一个致命的错误发生了 */
		if((bytes_read==-1)&&(errno!=EINTR)) 
			break;
		else if(bytes_read>0)
		{
			ptr=buffer;
			while(bytes_write=write(to_fd,ptr,bytes_read))
			{
				/* 一个致命错误发生了 */
				if((bytes_write==-1)&&(errno!=EINTR))
					break;
				/* 写完了所有读的字节 */
				else if(bytes_write==bytes_read) 
					break;
				/* 只写了一部分,继续写 */
				else if(bytes_write>0)
				{
					ptr+=bytes_write;
					bytes_read-=bytes_write;
				}
			}
			/* 写的时候发生的致命错误 */
			if(bytes_write==-1)
				break;
		}
	}
	close(from_fd);
	close(to_fd);
}

void zero_copy(char *infile,char* outfile)
{
	int infd,outfd;
	struct stat filestat;
	off_t offset = 0;
	stat(infile,&filestat);
	//printf("file size = %d\n",filestat.st_size);
	if ((infd = open(infile,O_RDWR)) == -1)
	{
		return ;
	}
	if( (outfd = open(outfile,O_RDWR|O_CREAT)) == -1)
	{
		return ;
	}
	sendfile(outfd,infd,&offset,filestat.st_size) ;

	//	printf ("file size = %d\n",filestat.st_size);
	close(infd);
	close(outfd);

}
int main()
{

	struct timeval tpstart,tpend;
	float timeuse;

	gettimeofday(&tpstart,NULL);

	old_copy(FILE1,FILE2);
	gettimeofday(&tpend,NULL);

	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
		tpend.tv_usec-tpstart.tv_usec;
	timeuse/=1000000;
	printf("old copy %f\n",timeuse);
	gettimeofday(&tpstart,NULL);
	zero_copy(FILE1,FILE3);
	gettimeofday(&tpend,NULL);
	timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
		tpend.tv_usec-tpstart.tv_usec;
	timeuse/=1000000;
	printf("zero copy %f\n",timeuse);
	return 0;
}

