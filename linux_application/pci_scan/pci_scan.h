/*
 * Enum all pci device via the PCI config register(CF8 and CFC).
 */

#ifndef _PCI_SCAN_H
#define _PCI_SCAN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <string.h>
#include <fcntl.h>
#include <linux/types.h>


#define PCI_MAX_BUS 255 /* 8 bits (0 ~ 255) */
#define PCI_MAX_DEV 31 /* 5 bits (0 ~ 31) */
#define PCI_MAX_FUN 7 /* 3 bits (0 ~ 7) */

#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

#define PCICFG_REG_VID 0x00 /* Vendor id, 2 bytes */
#define PCICFG_REG_DID 0x02 /* Device id, 2 bytes */
#define PCICFG_REG_CMD 0x04 /* Command register, 2 bytes */
#define PCICFG_REG_STAT 0x06 /* Status register, 2 bytes */
#define PCICFG_REG_RID 0x08 /* Revision id, 1 byte */

#define ENOMEM 5
#define DBG(fmt,args...)   fprintf(stderr, "CL: Error %s %d "fmt,__FILE__,__LINE__,##args)


#define ETC_PCI_IDS "pci.ids"

/* Types */

typedef __u8 byte;
typedef __u16 word;
typedef __u32 u32;


struct pci_device
{
    unsigned int bus;
    unsigned int dev;
    unsigned int fun;

    unsigned int vendor_id:16;
    unsigned int device_id:16;
    unsigned int revision_id:8;

    char *device_name;
};

struct pci_device_node{
    struct pci_device pci_dev;
    struct pci_device_node *next;
};
struct pci_device_node* alloc_pci_device_node(int num);
void cleanup(struct pci_device_node *head);

// names
char *lookup_device_full(word v, word i);

void pci_devices_show(struct pci_device_node *head);

#endif // _PCI_SCANH_H

