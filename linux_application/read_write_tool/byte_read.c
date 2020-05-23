#include <stdio.h>

#define BUF_LEN 16
#define FILE_PATH "/dev/vir_cdev1"
#define FILENAME_LEN 256
int main(int argc,char *argv[])
{
    char filepath[FILENAME_LEN];
    FILE *fd;
    char c;
    int count;
    strcpy(filepath,FILE_PATH);
    if(argc == 2) {
        strcpy(filepath,argv[1]);
    }
    fd = fopen(filepath,"r");
    //fd = fopen("block_read.c","r");
    if(fd !=NULL) {
        while( (c = getc(fd))!= EOF) {
            printf("%c",c);

        }

        fclose(fd);
    } else {
        printf("open device file error!\n");
    }

    return 0;
}
