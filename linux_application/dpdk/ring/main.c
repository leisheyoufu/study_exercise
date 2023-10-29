#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <rte_eal.h>
#include <rte_common.h>
#include <rte_malloc.h>
#include <rte_lcore.h>
#include <rte_log.h>
#include <rte_spinlock.h>
#include <rte_memory.h>
#include <rte_memzone.h>
#include <rte_ring.h>

#define RING_SIZE 1024
#define RING_NAME "my_ring"

int main(int argc, char **argv)
{
    int ret;
    struct rte_ring *ring;
    uint32_t i, j;
    void *data;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 创建ring
    ring = rte_ring_create(RING_NAME, RING_SIZE, rte_socket_id(), RING_F_SP_ENQ | RING_F_SC_DEQ);
    if (ring == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create ring: %s\n", rte_strerror(rte_errno));
    }

    // 向ring中添加元素
    for (i = 0; i < RING_SIZE; i++) {
        data = rte_malloc(NULL, sizeof(uint32_t), 0);
        *(uint32_t *)data = i;
        ret = rte_ring_enqueue(ring, data);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot enqueue element: %s\n", rte_strerror(rte_errno));
        }
    }

    // 从ring中获取元素并释放
    for (i = 0; i < RING_SIZE; i++) {
        ret = rte_ring_dequeue(ring, &data);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot dequeue element: %s\n", rte_strerror(rte_errno));
        }
        printf("Element %d: %d\n", i, *(uint32_t *)data);
        rte_free(data);
    }

    // 删除ring
    rte_ring_free(ring);

    return 0;
}