#include "pthread.h"


// return 1  success
int remove_fd(struct d_thread * t,int fd)
{
    int i,j;
    printf("remove fd\n");
    pthread_mutex_lock(&t->wait_mutex);
    for(i=0; i<t->size; i++) {
        if(t->fds[i] == fd) {
            t->fds[i] = 0;
            for(j=i; j<t->size-1; j++) {
                t->fds[j] = t->fds[j+1];
            }
            t->size--;
            pthread_mutex_unlock(&t->wait_mutex);
            return 1;
        }
    }
    pthread_mutex_unlock(&t->wait_mutex);
    return 0;
}
// return 1 success
int insert_fd(struct d_thread *t,int fd)
{
    pthread_mutex_lock(&t->wait_mutex);
    if(t->size < ARRAY_SIZE) {
        t->fds[t->size] = fd;
        (t->size)++;
        pthread_mutex_unlock(&t->wait_mutex);
        return 1;
    }
    pthread_mutex_unlock(&t->wait_mutex);
    return 0;
}
/*
int insert_waitfd(struct d_thread *t,int fd)
{
	printf("insert_waitfd \n");
	pthread_mutex_lock(&t->wait_mutex); // 给互斥体变量加锁
	if(t->wait_size < ARRAY_SIZE)
	{
		t->waitfds[t->wait_size] = fd;
		(t->wait_size)++;
		pthread_mutex_unlock(&t->wait_mutex); // 给互斥体变量解除锁
		return 1;
	}
	pthread_mutex_unlock(&t->wait_mutex); // 给互斥体变量解除锁
	return 0;
}

int batch_insert_fd(struct d_thread *t)
{
	int i;
	printf("batch insert fd\n");
	pthread_mutex_lock(&t->wait_mutex); // 给互斥体变量加锁
	for(i=0;i<t->wait_size;i++)
	{
		insert_fd(t,t->waitfds[i]);
	}
	t->wait_size =0;
	pthread_mutex_unlock(&t->wait_mutex); // 给互斥体变量解除锁
}
*/