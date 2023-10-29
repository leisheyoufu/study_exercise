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
#include <rte_mempool.h>

#define MEMPOOL_SIZE 1024
#define MEMPOOL_CACHE_SIZE 32
#define MEMPOOL_NAME "my_mempool"

int main(int argc, char **argv)
{
    int ret;
    struct rte_mempool *mempool;
    uint32_t i, j;
    void *data;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 创建mempool
    mempool = rte_pktmbuf_pool_create(MEMPOOL_NAME, MEMPOOL_SIZE, MEMPOOL_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mempool == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create mempool: %s\n", rte_strerror(rte_errno));
    }

    // 向mempool中添加元素
    for (i = 0; i < MEMPOOL_SIZE; i++) {
        data = rte_pktmbuf_alloc(mempool);
        if (data == NULL) {
            rte_exit(EXIT_FAILURE, "Cannot allocate element: %s\n", rte_strerror(rte_errno));
        }
        *(uint32_t *)rte_pktmbuf_mtod(data, uint32_t *) = i;
        rte_pktmbuf_append(data, sizeof(uint32_t));
    }

    // 从mempool中获取元素并释放
    for (i = 0; i < MEMPOOL_SIZE; i++) {
        data = rte_pktmbuf_alloc(mempool);
        if (data == NULL) {
            rte_exit(EXIT_FAILURE, "Cannot allocate element: %s\n", rte_strerror(rte_errno));
        }
        printf("Element %d: %d\n", i, *(uint32_t *)rte_pktmbuf_mtod(data, uint32_t *));
        rte_pktmbuf_free(data);
    }

    // 删除mempool
    rte_mempool_free(mempool);

    return 0;
}