#ifndef _DAEMON_H
#define _DAEMON_H

#include "epoll.h"



void child_thread(int);
void init_thread();
void main_thread();
void daemonize();
int select_tfd(struct d_thread* fds);


#endif