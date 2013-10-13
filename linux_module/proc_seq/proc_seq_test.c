#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("proc_test");
MODULE_VERSION("1.0.0");

#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define BUF_LEN 128
#define ARRAY_SIZE 4
static char proc_name[]="proc_test_seq";

struct buf_array
{
	char buf[BUF_LEN];
};

static struct buf_array *b_array;

static void init_buf_array()
{
	int i;	
	for(i=0; i<ARRAY_SIZE;i++)
	{
		sprintf(b_array[i].buf,"	proc seq file test %d",i);
		CL_PRINT("%s\n",b_array[i].buf);
	}
	
}

static void *test_seq_proc_start(struct seq_file *s, loff_t *pos)
{
	if (*pos >= ARRAY_SIZE)
		return NULL;   /* No more to read */
	return  b_array+ *pos;
}

static void *test_seq_proc_next(struct seq_file *s, void *v, loff_t *pos)
{
	(*pos)++;
	if (*pos >= ARRAY_SIZE)
		return NULL;
	return b_array + *pos;
}

static void test_seq_proc_stop(struct seq_file *s, void *v)
{
	/* Actually, there's nothing to do here */
}



static int test_seq_proc_show(struct seq_file *s, void *v)
{
	struct buf_array *a = (struct buf_array *) v;
	seq_printf(s," test seq proc show %s\n",a->buf);
	return 0;
}

static struct seq_operations test_seq_proc_ops = {
	.start = test_seq_proc_start,
	.next  = test_seq_proc_next,
	.stop  = test_seq_proc_stop,
	.show  = test_seq_proc_show
};



static int test_seq_proc_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &test_seq_proc_ops);
}


static struct file_operations 
test_seq_proc_fops = {
	.owner   = THIS_MODULE,
	.open    = test_seq_proc_open,
	.read    = seq_read,
	.llseek  = seq_lseek,
	.release = seq_release
};
	

static void test_create_proc()
{
	struct proc_dir_entry *entry;
	entry = create_proc_entry(proc_name, 0, NULL);
	if(entry)
			entry->proc_fops = &test_seq_proc_fops;
	
	b_array = kmalloc(ARRAY_SIZE*sizeof(struct buf_array)
				,GFP_KERNEL);
	init_buf_array();

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
	kfree(b_array);
}

module_init(proc_test_init);
module_exit(proc_test_exit);


