#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>


#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)

#define CL_ERR(fmt,args...) printk("CL err: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define BUF_LEN 128
#define NAME_LEN 256
#define DEV_NUM 5
static char device_name[]="vir_cdev";

struct vir_device {
	struct cdev cdev;
	struct semaphore sem;
	struct list_head head;
	spinlock_t priv_lock;
	char buf[BUF_LEN];
	size_t len;
};

struct vir_message{
	char buf[BUF_LEN];
	struct list_head list;
};

