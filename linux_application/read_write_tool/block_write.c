#include <stdio.h>
#include <string.h>

#define BUF_LEN 16
#define FILENAME_LEN 256
#define FILE_PATH "/dev/vir_cdev1"
int main(int argc,char *argv[])
{
	FILE *fd;
	char buf[] = "block write";
	char filepath[FILENAME_LEN];
	int count;
	strcpy(filepath,FILE_PATH);
	if(argc == 2)
	{
		strcpy(filepath,argv[1]);		
	}
	fd = fopen(filepath,"w");
	
	if(fd !=NULL)
	{
		count = fwrite(buf,BUF_LEN,1,fd);
		printf("vir_cdev buf is %s\n",buf);
		printf("read count = %d\n",count);
	fclose(fd);
	}
	else
	{
		printf("open device file error!\n");
	}

	return 0;
}
