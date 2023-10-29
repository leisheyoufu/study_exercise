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
#include <rte_hash.h>

#define HASH_TABLE_SIZE 1024
#define HASH_TABLE_NAME "my_hash_table"

int main(int argc, char **argv)
{
    int ret;
    struct rte_hash *hash_table;
    struct rte_hash_parameters hash_params;
    uint32_t i, j;
    uint32_t key, value, *lookup_value;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 设置hash表参数
    memset(&hash_params, 0, sizeof(hash_params));
    hash_params.name = HASH_TABLE_NAME;
    hash_params.entries = HASH_TABLE_SIZE;
    hash_params.key_len = sizeof(uint32_t);
    hash_params.hash_func = rte_hash_crc;
    hash_params.socket_id = rte_socket_id();

    // 创建hash表
    hash_table = rte_hash_create(&hash_params);
    if (hash_table == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create hash table: %s\n", rte_strerror(rte_errno));
    }

    // 向hash表中添加元素
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        key = i;
        value = i * 2;
        ret = rte_hash_add_key_data(hash_table, &key, &value);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot add key-value pair: %s\n", rte_strerror(rte_errno));
        }
    }

    // 从hash表中获取元素并释放
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        key = i;
        ret = rte_hash_lookup_data(hash_table, &key, (void **)&lookup_value);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot lookup key: %s\n", rte_strerror(rte_errno));
        }
        printf("Element %d: %d\n", i, *lookup_value);
    }

    // 删除hash表
    rte_hash_free(hash_table);

    return 0;
}