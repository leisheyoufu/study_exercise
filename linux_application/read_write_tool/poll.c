#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <poll.h>


#define IN_FILES   3    /* 多路复用输入文件数目*/
//#define TIME_DELAY   6000    /* 超时时间秒数 */
#define TIME_DELAY   -1    /* 超时时间秒数 */
#define MAX(a, b)   ((a > b)?(a):(b))

#define BUF_LEN 16
#define FILE_PATH0 "/dev/vir_cdev0"
#define FILE_PATH1 "/dev/vir_cdev1"
#define FILENAME_LEN 256
int main(int argc,char *argv[])
{
    struct pollfd fds[IN_FILES];
    char buf[BUF_LEN];
    int i;
    fds[0].fd = 0;
    int real_read;
    if((fds[1].fd = open (FILE_PATH0, O_RDONLY|O_NONBLOCK)) < 0) {
        printf("Open FILE_PATH0 error\n");
        return 1;
    }
    if((fds[2].fd = open (FILE_PATH1, O_RDONLY|O_NONBLOCK)) < 0) {
        printf("Open FILE_PATH1 error\n");
        return 1;
    }

    /*取出两个文件描述符中的较大者*/
    for (i = 0; i < IN_FILES; i++) {
        fds[i].events = POLLIN;
    }

//	while(fds[0].events || fds[1].events || fds[2].events)
    while(1) {
        if (poll(fds, IN_FILES, TIME_DELAY) <= 0) {
            printf("poll error\n");
            return 1;
        }

        for (i = 0; i< IN_FILES; i++) {
            if (fds[i].revents) {
                memset(buf, 0, BUF_LEN);
                real_read = read(fds[i].fd, buf, BUF_LEN);

                if (real_read < 0) { //  < 0
                    if (errno != EAGAIN) {
                        return 1;
                    }
                } else if (!real_read) { // == 0
                    close(fds[i].fd);
                    fds[i].events = 0;
                } else { //>0   read data
                    if (i == 0) {
                        if ((buf[0] == 'q') || (buf[0] == 'Q')) {
                            return 1;
                        }
                    } else {
                        buf[real_read] = '\0';
                        printf("fd%d read %s", i,buf);
                    }
                } /* end of if real_read*/
            } /* end of if revents */
        } /* end of for */
    } /*end of while */
}
