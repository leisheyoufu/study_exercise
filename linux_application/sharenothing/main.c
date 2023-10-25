#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10000000
#define NUM_THREADS 4

int *array;
int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg)
{
    int tid = (int)arg;
    int start = tid * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    int i, local_sum = 0;

    // 计算线程负责的部分的数组元素总和
    for (i = start; i < end; i++) {
        local_sum += array[i];
    }

    // 使用互斥锁将线程的计算结果添加到全局总和中
    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    int i;
    pthread_t threads[NUM_THREADS];

    // 分配并初始化数组
    array = malloc(ARRAY_SIZE * sizeof(int));
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1;
    }

    // 启动多个线程，每个线程计算数组的一部分
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, &thread_func, (void *)i);
    }

    // 等待所有线程完成
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // 输出数组元素总和
    printf("Sum of array elements: %d\n", sum);

    // 释放内存
    free(array);

    return 0;
}