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
#include <rte_pci.h>

#define PCI_DRIVER_NAME "vfio-pci"

int main(int argc, char **argv)
{
    int ret;
    struct rte_pci_device *pci_dev;
    struct rte_pci_driver *pci_driver;
    struct rte_pci_device_list pci_dev_list;
    uint32_t i, j;

    // 初始化EAL
    ret = rte_eal_init(argc, argv);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot init EAL: %s\n", rte_strerror(rte_errno));
    }

    // 列出系统中的PCI设备
    memset(&pci_dev_list, 0, sizeof(pci_dev_list));
    ret = rte_pci_scan(&pci_dev_list);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "Cannot scan PCI devices: %s\n", rte_strerror(rte_errno));
    }
    printf("PCI devices found: %d\n", pci_dev_list.count);
    for (i = 0; i < pci_dev_list.count; i++) {
        pci_dev = &pci_dev_list.devices[i];
        printf("PCI device %d: %04x:%04x:%04x.%d\n", i, pci_dev->addr.domain, pci_dev->addr.bus, pci_dev->addr.devid, pci_dev->addr.function);
    }

    // 绑定PCI设备的驱动程序
    for (i = 0; i < pci_dev_list.count; i++) {
        pci_dev = &pci_dev_list.devices[i];
        pci_driver = rte_pci_find_driver(pci_dev->driver->name);
        if (pci_driver && strcmp(pci_driver->driver.name, PCI_DRIVER_NAME) == 0) {
            ret = rte_pci_probe_one(pci_dev);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "Cannot bind driver to PCI device: %s\n", rte_strerror(rte_errno));
            }
            printf("PCI device %d: driver bound\n", i);
        }
    }

    // 解绑PCI设备的驱动程序
    for (i = 0; i < pci_dev_list.count; i++) {
        pci_dev = &pci_dev_list.devices[i];
        pci_driver = rte_pci_find_driver(pci_dev->driver->name);
        if (pci_driver && strcmp(pci_driver->driver.name, PCI_DRIVER_NAME) == 0) {
            ret = rte_pci_detach(pci_dev);
            if (ret < 0) {
                rte_exit(EXIT_FAILURE, "Cannot unbind driver from PCI device: %s\n", rte_strerror(rte_errno));
            }
            printf("PCI device %d: driver unbound\n", i);
        }
    }

    return 0;
}