#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#define NO_DMA 0
#define USE_DMA 1

int main(int argc, char *argv[])
{
    struct timeval tpstart,tpend;
    float timeuse;
    gettimeofday(&tpstart,NULL);
    int cmd, fd;
    if (argc != 2) {
        printf("%s <nodma | usedma>n", argv[0]);
        return -1;
    }
    fd = open("/dev/dma_copy_device", O_RDWR);
    if(fd < 0)
        printf("can not open /dev/dma_copy_device");

    if(0 == strcmp(argv[1], "nodma")) {
        cmd = NO_DMA;
    } else if(0 == strcmp(argv[1], "usedma")) {
        cmd = USE_DMA;
    } else {
        printf("%s <nodma | usedma>n", argv[0]);
        return -1;
    }
    while(3) {
        gettimeofday(&tpstart,NULL);
        ioctl(fd, cmd);
        gettimeofday(&tpend,NULL);
        timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+
                tpend.tv_usec-tpstart.tv_usec;
        timeuse/=1000000;
        if(cmd == USE_DMA) {
            printf("dma: timeuse%f\n",timeuse);
        } else if(cmd == NO_DMA) {
            printf("nodma: timeuse%f\n",timeuse);
        }

    }
    return 0;
}

