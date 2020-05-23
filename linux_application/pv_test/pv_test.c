#include <stdio.h>
#include <pthread.h>
#include <error.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define FRUIT_NUM 2
sem_t apple_sem,pear_sem,empty_sem,full_sem;

int apple,pear,empty,full;

void father()
{
    int kind;
    pthread_t tid = pthread_self();
    while(1) {
        sem_wait(&empty_sem);
        srand((unsigned int)time(NULL));
        kind = rand()%FRUIT_NUM;
        sem_post(&full_sem);
        switch(kind) {
        case 0:
            printf("buy an apple \n");
            sem_post(&apple_sem);
            break;
        case 1:
            printf("buy a pear \n");
            sem_post(&pear_sem);
            break;
        }
        sleep(1);
    }
    pthread_exit((void*)tid);
}

void son()
{
    pthread_t tid = pthread_self();
    while(1) {
        sem_wait(&apple_sem);
        sem_wait(&full_sem);
        printf("son eat an apple\n");
        sem_post(&empty_sem);
        sleep(1);
    }
    pthread_exit((void*)tid);
}

int daughter()
{
    pthread_t tid = pthread_self();
    while(1) {
        sem_wait(&pear_sem);
        sem_wait(&full_sem);
        printf("daught eat a pear\n");
        sem_post(&empty_sem);
        sleep(1);
    }
    pthread_exit((void*)tid);
}



int init()
{
    int ret;
    ret = sem_init(&apple_sem,0,apple);
    if(ret!=0) {
        return ret;
    }
    ret = sem_init(&pear_sem,0,pear);
    if(ret !=0 ) {
        return ret;
    }
    ret = sem_init(&empty_sem,0,empty);
    if(ret !=0) {
        return ret;
    }
    ret = sem_init(&full_sem,0,full);
    return ret;
}

void destroy()
{
    sem_destroy(&empty_sem);
    sem_destroy(&pear_sem);
    sem_destroy(&apple_sem);
    sem_destroy(&full_sem);
}


int main()
{
    void *result;
    pthread_t t[FRUIT_NUM+1];
    apple =0;
    pear =1;
    empty = 0;
    full =1;
    int i;
    if(init() != 0) {
        return -1;
    }

    pthread_create(&t[0],NULL,(void*)father,NULL);
    pthread_create(&t[1],NULL,(void*)son,NULL);
    pthread_create(&t[2],NULL,(void*)daughter,NULL);

    for(i=0; i<FRUIT_NUM+1; i++) {
        if(pthread_join(t[i],&result) == 0) {
            printf("thread %u return result=%u\n",t[i],(int)result);
        }
    }
    destroy();

    return 0;
}



