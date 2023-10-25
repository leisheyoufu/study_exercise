#include <stdio.h>
#include <stdlib.h>
#include <numa.h>
#include <sched.h>

void numa_thread_func(void *arg)
{
    int cpu, node;
    cpu = (int)arg;
    node = numa_node_of_cpu(cpu);

    printf("Thread running on CPU %d, NUMA node %d\n", cpu, node);

    // 设置线程的CPU亲和力
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (sched_setaffinity(0, sizeof(cpuset), &cpuset) == -1) {
        perror("sched_setaffinity");
        exit(1);
    }

    // 在特定的CPU核心上执行一些计算任务
    int i, sum = 0;
    for (i = 0; i < 100000000; i++) {
        sum += i;
    }
    printf("Thread finished. Sum = %d\n", sum);
}

int main()
{
    int num_cpus = numa_num_configured_cpus();
    int i;

    // 在每个NUMA节点上启动一个线程
    for (i = 0; i < num_cpus; i++) {
        numa_run_on_node(i % numa_max_node());
        pthread_t tid;
        pthread_create(&tid, NULL, &numa_thread_func, (void *)i);
        pthread_join(tid, NULL);
    }

    return 0;
}