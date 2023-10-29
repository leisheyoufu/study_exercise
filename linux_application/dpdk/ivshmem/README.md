下面是一个简单的DPDK IVSHMEM示例程序，演示如何在两个VM之间共享内存：

在VM1中运行以下命令：


```
sudo modprobe uio_pci_generic
sudo insmod $RTE_SDK/$RTE_TARGET/kmod/igb_uio.ko
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind=igb_uio 01:00.0

sudo $RTE_SDK/examples/ivshmem-client -s /tmp/ivshmem_socket -m 1024
```
在VM2中运行以下命令：

复制代码
```
sudo modprobe uio_pci_generic
sudo insmod $RTE_SDK/$RTE_TARGET/kmod/igb_uio.ko
sudo $RTE_SDK/usertools/dpdk-devbind.py --bind=igb_uio 01:00.0

sudo $RTE_SDK/examples/ivshmem-server -s /tmp/ivshmem_socket -m 1024
```
在VM1中运行的ivshmem-client程序将连接到在VM2中运行的ivshmem-server程序，并在两个VM之间共享一个大小为1024MB的内存区域。您可以在程序中使用共享内存进行高性能数据传输和共享。

请注意，上述命令假定您的系统中有一个PCI设备（01:00.0），可以使用igb_uio驱动程序进行绑定。如果您的系统中没有此类设备，则需要相应地更改命令。