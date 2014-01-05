#include "pci_scan.h"

int scan_pci_devices( struct pci_device_node *head)
{
    unsigned int bus, dev, fun;
    unsigned int addr, data;
    struct pci_device_node *node;

    for (bus = 0; bus <= PCI_MAX_BUS; bus++) {
        for (dev = 0; dev <= PCI_MAX_DEV; dev++) {
            for (fun = 0; fun <= PCI_MAX_FUN; fun++) {
                addr = 0x80000000L | (bus<<16) | (dev<<11) | (fun<<8);
                outl(addr, CONFIG_ADDRESS);
                data = inl(CONFIG_DATA);

                /* Identify vendor ID */
                if ((data != 0xFFFFFFFF) && (data != 0)) {
                    node = alloc_pci_device_node(1);
                    if(node == NULL)
                    {
                        DBG("error alloc node\n");
                        return -ENOMEM;
                    }
                    node->pci_dev.bus = bus;
                    node->pci_dev.dev = dev;
                    node->pci_dev.fun = fun;
                    node->pci_dev.device_id = data>>16;
                    node->pci_dev.vendor_id = data &0xFFFF; // Little-Endian
                    node->pci_dev.device_name = lookup_device_full(node->pci_dev.vendor_id, node->pci_dev.device_id);
                    if(node->pci_dev.device_name == NULL)
                    {
                        DBG("error lookup device\n");
                        return -ENOMEM;
                    }
                    /*
                    printf("%02X:%02X:%02X ", bus, dev, fun);
                    printf("%04X:%04X", data&0xFFFF, data>>16);
                    printf("%04X:%04X",node->pci_dev.vendor_id,node->pci_dev.device_id);
                    printf(" %s",node->pci_dev.device_name);
                    exit(1);
                    */
                    addr = 0x80000000L | (bus<<16) | (dev<<11) | (fun<<8) | PCICFG_REG_RID;  // 0x08 offset
                    outl(addr, CONFIG_ADDRESS);
                    data = inl(CONFIG_DATA);
                    if (data&0xFF) {
                        node->pci_dev.revision_id = data&0xFF;
                       // printf(" (rev %02X)\n", data&0xFF);
                    } else {
                        node->pci_dev.revision_id = 0;
                        //printf("\n");
                    }
                    head->next = node;
                    head = node;
                }
            }
        }
    }
    return 0;
}

struct pci_device_node* alloc_pci_device_node(int num)
{
    struct pci_device_node *head;
    head = malloc(sizeof(struct pci_device_node)*num);
    return head;
};

void cleanup(struct pci_device_node *head)
{
    struct pci_device_node *temp;
    while(head!=NULL)
    {
        temp = head->next;
        free(head->pci_dev.device_name);
        free(head);
        head = temp;
    }
}


void pci_devices_show(struct pci_device_node *head)
{
    while(head !=NULL)
    {
        printf("%02X:%02X:%02X ", head->pci_dev.bus, head->pci_dev.dev, head->pci_dev.fun);
        printf("%04X:%04X", head->pci_dev.vendor_id, head->pci_dev.device_id);
        printf(" %s",head->pci_dev.device_name);
        printf(" (rev %02X)\n", head->pci_dev.revision_id);
        head = head->next;
    }
}

int main()
{
    int ret;
    struct pci_device_node *head;

    /* Enable r/w permission of all 65536 ports */
    ret = iopl(3);
    if (ret < 0) {
        perror("iopl set error");
        return 1;
    }

    head = alloc_pci_device_node(1);
    if(head == NULL)
    {
        DBG("error alloc node\n");
        return -ENOMEM;
    }
    scan_pci_devices(head);

    pci_devices_show(head);

    /* Disable r/w permission of all 65536 ports */
    ret = iopl(0);
    if (ret < 0) {
        perror("iopl set error");
        return 1;
    }
    cleanup(head);

    return 0;
}
