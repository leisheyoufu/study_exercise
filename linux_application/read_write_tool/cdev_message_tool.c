#include <stdio.h>

#define BUF_LEN 128
int main()
{
    FILE *fd;
    char buf[BUF_LEN];
    int count;
    fd = fopen("/dev/vir_cdev1","r");

    if(fd !=NULL) {
        count = fread(buf,BUF_LEN,1,fd);
        printf("vir_cdev buf is %s\n",buf);
        fclose(fd);
    } else {
        printf("open device file error!\m");
    }

    return 0;
}
