#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define LOOP_TIME 50

int my_rand(void *cnt)
{
    int i;
    pthread_t pthread_id = pthread_self();
    srand((unsigned int)time(NULL));
    for( i=0; i<LOOP_TIME; i++) {
        int temp = rand()%100;
        printf("pthread_id = %u rand num is %d\n",pthread_id,temp);
        sleep(1);
    }
    pthread_exit((void*)pthread_id);
}

int main()
{
    pthread_t tid;
    void *result;

    if(pthread_create(&tid,NULL,(void *)my_rand,NULL)) {
        printf("main :create thread %u\n",tid);
    }
    if( pthread_join(tid,&result) ==0) {
        printf("thread %u return result=%u\n",tid,(int)result);
    }
    return 0;
}



