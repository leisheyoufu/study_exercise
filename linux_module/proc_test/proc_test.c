#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("proc_test");
MODULE_VERSION("1.0.0");

#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define BUF_LEN 128
static char proc_name[]="proc_test_mem";
static char reply[] = "This is simply for proc test";

int proc_test_read(char *buf,char **start,off_t offset,
		int count,int *eof,void *data)
{
	sprintf(buf,"CL The buf in the kernel is %s\n",reply);
	count = strlen(buf);
	return count;


}

static void test_create_proc()
{
	struct proc_dir_entry *entry;
	create_proc_read_entry(proc_name,0,
			NULL,proc_test_read,
			NULL);
}



static int __init proc_test_init(void)
{
	test_create_proc();
	CL_PRINT("create proc \n");


 return 0;
}
static void __exit proc_test_exit(void)
{
	remove_proc_entry(proc_name,NULL);
}

module_init(proc_test_init);
module_exit(proc_test_exit);


