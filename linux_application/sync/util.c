#include "header.h"

extern int verbose;

int readfd(int fd,char *buffer,int N)
{
    int  ret;
    int total=0;

    while (total < N) {
        ret = read(fd,buffer + total,N - total);

        if (ret <= 0)
            return total;
        total += ret;
    }
    return total;
}
void read_buf(int f,char *buf,int len)
{
    if (readfd(f,buf,len) != len) {
        if (verbose > 1)
            fprintf(stderr,"Error reading %d bytes : %s\n",len,strerror(errno));
        exit(1);
    }

}

char *map_file(int fd,off_t len)
{
    char *ret = (char *)mmap(NULL,len,PROT_READ,MAP_SHARED,fd,0);
    return ret;
}

void unmap_file(char *buf,off_t len)
{
    if (len > 0)
        munmap(buf,len);
}
void write_buf(int f,char *buf,int len)
{
    if (write(f,buf,len) != len) {
        fprintf(stderr,"write_buf failed : %s\n",strerror(errno));
        exit(1);
    }
}


/*
md5

  unsigned char *data = "123";
    unsigned char md[16];
    int i;
    char tmp[3]= {'\0'},buf[33]= {'\0'};
    MD5(data,strlen(data),md);
    for (i = 0; i < 16; i++) {
        sprintf(tmp,"%2.2x",md[i]);
        strcat(buf,tmp);
    }
    printf("%s\n",buf);
*/
