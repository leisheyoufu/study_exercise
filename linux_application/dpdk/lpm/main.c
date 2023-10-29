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
#include <rte_lpm.h>

#define LPM_TABLE_SIZE 1024
#define LPM_TABLE_NAME "my_lpm_table"

int main(int argc, char **argv)
{
    int ret;
    struct rte_lpm *lpm_table;
    struct rte_lpm_config lpm_config;
    uint32_t i, j;
    uint32_t ip, depth, next_hop;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 设置LPM表参数
    memset(&lpm_config, 0, sizeof(lpm_config));
    lpm_config.max_rules = LPM_TABLE_SIZE;
    lpm_config.number_tbl8s = LPM_TABLE_SIZE / RTE_LPM_TBL8_GROUP_SIZE;
    lpm_config.flags = 0;

    // 创建LPM表
    lpm_table = rte_lpm_create(LPM_TABLE_NAME, rte_socket_id(), &lpm_config);
    if (lpm_table == NULL) {
        rte_exit(EXIT_FAILURE, "Cannot create LPM table: %s\n", rte_strerror(rte_errno));
    }

    // 向LPM表中添加路由
    for (i = 0; i < LPM_TABLE_SIZE; i++) {
        ip = i << 24;
        depth = 24;
        next_hop = i;
        ret = rte_lpm_add(lpm_table, ip, depth, next_hop);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot add route: %s\n", rte_strerror(rte_errno));
        }
    }

    // 从LPM表中查找路由并释放
    for (i = 0; i < LPM_TABLE_SIZE; i++) {
        ip = i << 24;
        ret = rte_lpm_lookup(lpm_table, ip, &next_hop);
        if (ret < 0) {
            rte_exit(EXIT_FAILURE, "Cannot lookup route: %s\n", rte_strerror(rte_errno));
        }
        printf("Route %d: next hop %d\n", i, next_hop);
    }

    // 删除LPM表
    rte_lpm_delete_all(lpm_table);
    rte_lpm_free(lpm_table);

    return 0;
}