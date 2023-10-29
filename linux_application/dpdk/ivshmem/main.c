#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
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
#include <rte_ethdev.h>
#include <rte_ether.h>
#include <rte_ip.h>
#include <rte_udp.h>
#include <rte_cycles.h>
#include <rte_errno.h>
#include <rte_arp.h>
#include <rte_string_fns.h>
#include <rte_byteorder.h>
#include <rte_flow.h>
#include <rte_bus_vdev.h>
#include <rte_kvargs.h>
#include <rte_vhost.h>
#include <rte_vdpa.h>
#include <rte_devargs.h>
#include <rte_pci.h>
#include <rte_bus_pci.h>
#include <rte_rawdev.h>
#include <rte_bus_vmbus.h>
#include <rte_bus_vmbus.h>
#include <rte_vmbus.h>
#include <rte_ivshmem.h>

#define IVSHMEM_SOCKET "/tmp/ivshmem_socket"
#define IVSHMEM_SIZE (1024 * 1024 * 1024)

int main(int argc, char **argv)
{
    int ret;
    struct rte_ivshmem_info ivshmem_info;
    void *ivshmem_addr;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 创建共享内存区域
    ret = rte_ivshmem_create(IVSHMEM_SOCKET, IVSHMEM_SIZE);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot create ivshmem: %s\n", rte_strerror(rte_errno));
    }

    // 获取共享内存信息
    ret = rte_ivshmem_get_mem_info(IVSHMEM_SOCKET, &ivshmem_info);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot get ivshmem info: %s\n", rte_strerror(rte_errno));
    }

    // 映射共享内存到本地地址空间
    ivshmem_addr = mmap(NULL, ivshmem_info.len, PROT_READ | PROT_WRITE, MAP_SHARED, ivshmem_info.fd, 0);
    if (ivshmem_addr == MAP_FAILED) {
        rte_exit(EXIT_FAILURE, "Cannot mmap ivshmem: %s\n", rte_strerror(rte_errno));
    }

    // 等待客户端连接
    printf("Waiting for client connection...\n");
    while (1) {
        ret = rte_ivshmem_check_attach(IVSHMEM_SOCKET);
        if (ret == 0) {
            break;
        }
        usleep(1000);
    }

    printf("Client connected.\n");

    // 在共享内存中写入一些数据
    memset(ivshmem_addr, 0x42, ivshmem_info.len);

    // 等待客户端断开连接
    printf("Waiting for client disconnection...\n");
    while (1) {
        ret = rte_ivshmem_check_detach(IVSHMEM_SOCKET);
        if (ret == 0) {
            break;
        }
        usleep(1000);
    }

    printf("Client disconnected.\n");

    // 解除共享内存映射
    munmap(ivshmem_addr, ivshmem_info.len);

    // 删除共享内存区域
    rte_ivshmem_destroy(IVSHMEM_SOCKET);

    return 0;
}