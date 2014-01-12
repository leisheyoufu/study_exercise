#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/fs.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <mach/irqs.h>
//#include <mach/irqs.h>

#define CL_DEBUG
#define CL_INFO

#ifdef CL_DEBUG
	#define CL_DBG_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_DBG_PRINT(fmt,args...)
#endif

#ifdef CL_INFO
	#define CL_INFO_PRINT(fmt,args...) printk("CL info: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_INFO_PRINT(fmt,args...)
#endif

struct dma_regs {
    unsigned long disrc;
    unsigned long disrcc;
    unsigned long didst;
    unsigned long didstc;
    unsigned long dcon;
    unsigned long dstat;
    unsigned long dcsrc;
    unsigned long dcdst;
    unsigned long dmasktrig;
};

struct dma_hw{
	volatile struct dma_regs *dma_regs;
};

struct dma_copy_device {
	struct cdev cdev;
	struct dma_hw hw;
	wait_queue_head_t dma_waitq;
};

struct dma_buffer{
	 dma_addr_t src_phys;
	 dma_addr_t dst_phys;
	 char *src;
	 char *dst;
};






