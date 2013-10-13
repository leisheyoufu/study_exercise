#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("usermode_helper");
MODULE_VERSION("1.0.0");

#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
static char* filename="usermode_helper_test.txt";
static char *pwd ="/home/cl/Project/linux_modules/usermode_helper/";

static int __init usermode_helper_init(void)
{
	char filepath[256];
	sprintf(filepath,"%s%s",pwd,filename);	
	int result = 0;
    char cmd_path[] = "/usr/bin/touch";
    char* cmd_argv[] = {cmd_path,filepath,NULL};
    char* cmd_envp[] = {pwd, "PATH=/sbin:/bin:/usr/bin", NULL};

    result = call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_WAIT_PROC);
	CL_PRINT("usermode_helper touch a new a file %s\n",filepath);
    return result;


}
static void __exit usermode_helper_exit(void)
{
	char filepath[256];
	sprintf(filepath,"%s%s",pwd,filename);	
   	int result = 0;
    char cmd_path[] = "/bin/rm";
    char* cmd_argv[] = {cmd_path,filepath,NULL};
    char* cmd_envp[] = {pwd, "PATH=/sbin:/bin:/usr/bin", NULL};

    result = call_usermodehelper(cmd_path, cmd_argv, cmd_envp, UMH_WAIT_PROC);
	CL_PRINT("usermode_helper rm a file\n");
}

module_init(usermode_helper_init);
module_exit(usermode_helper_exit);


