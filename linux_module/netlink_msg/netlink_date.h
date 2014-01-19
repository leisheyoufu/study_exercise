#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/percpu.h>
#include <linux/proc_fs.h>
#include <net/sock.h>
#include <net/netlink.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <linux/timer.h>
#include <linux/time.h>
#include <linux/types.h>
#include <linux/list.h>

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

#define NETLINK_TEST 25
#define MAX_MSG_LEN 128

