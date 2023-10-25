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
#include <rte_mbuf.h>

#define MBUF_POOL_SIZE 1024
#define MBUF_POOL_CACHE_SIZE 32
#define MBUF_POOL_NAME "my_mbuf_pool"

int main(int argc, char **argv)
{
    int ret;
    struct rte_mempool *mbuf_pool;
    struct rte_mbuf *mbuf;
    uint32_t i, j;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 创建mbuf池
    mbuf_pool = rte_pktmbuf_pool_create(MBUF_POOL_NAME, MBUF_POOL_SIZE, MBUF_POOL_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
    if (mbuf_pool == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool: %s\n", rte_strerror(rte_errno));
    }

    // 创建mbuf
    mbuf = rte_pktmbuf_alloc(mbuf_pool);
    if (mbuf == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot allocate mbuf: %s\n", rte_strerror(rte_errno));
    }

    // 向mbuf中添加数据
    rte_pktmbuf_append(mbuf, sizeof(uint32_t));
    *(uint32_t *)rte_pktmbuf_mtod(mbuf, uint32_t *) = 42;

    // 从mbuf中获取数据并释放
    printf("Data: %d\n", *(uint32_t *)rte_pktmbuf_mtod(mbuf, uint32_t *));
    rte_pktmbuf_free(mbuf);

    // 删除mbuf池
    rte_mempool_free(mbuf_pool);

    return 0;
}