#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/fcntl.h>
#include <linux/poll.h>
#include <linux/errno.h>	/* error codes */
#include <linux/wait.h>
#include <linux/sched.h>
#include  <linux/mm.h>  

//#define CL_DEBUG
#define CL_INFO

#ifdef CL_DEBUG
	#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_PRINT(fmt,args...) 
#endif

#ifdef CL_INFO
	#define CL_INFO(fmt,args...) printk("CL info: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_INFO(fmt,args...) 
#endif




#define CL_ERR(fmt,args...) printk("CL err: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define BUF_LEN PAGE_SIZE
#define NAME_LEN 256
#define DEV_NUM 2
static char device_name[]="vir_cdev";

struct vir_device {
	struct cdev cdev;
	struct semaphore sem;
	int head,tail;
	char *buf;
	int buf_len;
};
