#ifndef _PTHREAD_H
#define _PTHREAD_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


#define ARRAY_SIZE 100
#define THREAD_NUM 10

struct d_thread {
    int id;
    int fds[ARRAY_SIZE];
    int size;
    int epfd;
//	int waitfds[ARRAY_SIZE];
//	int wait_size;
    pthread_mutex_t wait_mutex;

};


// return 1  success
int remove_fd(struct d_thread * t,int fd);
int insert_fd(struct d_thread *t,int fd);
//int insert_waitfd(struct d_thread *t,int fd);
//int batch_insert_fd(struct d_thread *t);



#endif
