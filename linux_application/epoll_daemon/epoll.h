#ifndef _EPOLL_H
#define _EPOLL_H

#include "pthread.h"

#define BUF_MAX 512
#define MAXLINE 5
#define OPEN_MAX 100
#define LISTENQ 20
#define SERV_PORT 5000
#define INFTIM 1000
#define EPOLL_EVENT_SIZE 100

void set_nonblock(int sock);
void close_disable(int sockid, struct epoll_event ee,struct d_thread *t);
int my_listen(int epfd,int portnumber);
int my_accept(int listenfd,int epfd);
void my_receive(struct epoll_event *events,char *buf,int epfd,struct d_thread *t);
void my_send(struct epoll_event *events,char *msg,int epfd,struct d_thread *t);
void epoll_add(int socdfd,int epfd);

#endif