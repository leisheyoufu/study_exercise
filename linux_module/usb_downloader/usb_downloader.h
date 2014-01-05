#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/fs.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


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

#define BULKOUT_BUFFER_SIZE	512

