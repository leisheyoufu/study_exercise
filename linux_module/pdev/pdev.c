#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/platform_device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("pdev");
MODULE_VERSION("1.0.0");

#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#define BUF_SIZE 64
#define CONTENT_ITEM 4
static char device_name[]="vir_pdev";
struct pdev_content{
	char buf[64];
};
static struct kmem_cache *vir_dev_cachep;
static struct pdev_content *content[CONTENT_ITEM];

static void the_pdev_release(struct device *dev);

static struct platform_device the_pdev = {
	/* should be the same name as driver_name */
	.name = (char *) device_name,
	.id = -1,
	.dev = {
		.release = the_pdev_release,
	},
};

int valid_args(int index,char *buf)
{
	if(index >=0 && index < CONTENT_ITEM)
		return 1;
	return -EINVAL;
}



static ssize_t pdev_content_show(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	int i;
	char *s = buf;
	for(i=0;i<CONTENT_ITEM;i++)
	{
		buf+=sprintf(buf,"%d %s\n",i,content[i]->buf);
	}
	return buf-s;
}

static ssize_t pdev_content_store(struct device *dev,
					  struct device_attribute *attr,char *buf,ssize_t count)
{
	int index;
	char temp[BUF_SIZE];
	if(count >66)
		return -EINVAL;
	CL_PRINT("buf is %s\n",buf);
	sscanf(buf,"%d %s", &index,temp);
	CL_PRINT("index = %d,temp = %s\n",index,temp);
	if(valid_args(index,buf) < 0)
		return -EINVAL;
	strcpy(content[index]->buf,temp);
	
	return count;
}

static const DEVICE_ATTR(content, S_IRUGO|S_IWUSR,
			 pdev_content_show,
			 pdev_content_store);

static const struct attribute *pdev_events_attrs[] = {
	&dev_attr_content,
	NULL,
};

const struct attribute_group dev_attr_group = {
	.attrs = pdev_events_attrs,
};


static int pdev_remove(struct platform_device *pdev)
{
	int i;
	for( i=0;i<CONTENT_ITEM;i++)
	{
		if(content[i] !=NULL)
		{
			kmem_cache_free(vir_dev_cachep,content[i]);
		}
	}
	sysfs_remove_group(&the_pdev.dev.kobj, &dev_attr_group);
	CL_PRINT("pdev device remove \n");
	return 0;

}

static int pdev_probe(struct platform_device *pdev)
{
	int i;
	int err = 0;
	for( i=0;i<CONTENT_ITEM;i++)
	{
		content[i] = kmem_cache_zalloc(vir_dev_cachep, GFP_KERNEL);
		if(content[i] == NULL)
		{
			CL_PRINT("mem_cacahe alloc failed\n");
			return -1;
		}
	}
	err = sysfs_create_group(&the_pdev.dev.kobj, &dev_attr_group);
	if (err) {
		pr_err("create sysfs files\n");
		return err;
	}
	CL_PRINT("pdev device detected, pdev_driver will bind\n");
	return 0;
}



static struct platform_driver pdev_driver = {
	.probe	= pdev_probe,
	.remove	= pdev_remove,
	.driver	= {
		.name = (char *) device_name,
		.owner = THIS_MODULE,
	},
};



static void the_pdev_release(struct device *dev)
{
	return;
}

static int __init pdev_init(void)
{
	int ret=0;
	printk(KERN_ERR "pdev world!\n");

	vir_dev_cachep = kmem_cache_create("vir_pdev",
	sizeof(struct pdev_content), 0, 0, NULL);
	if(!vir_dev_cachep)
		goto err_kmem_create;


	ret = platform_device_register(&the_pdev);
	if (ret < 0)
		goto err_platform_device_register;
	ret = platform_driver_register(&pdev_driver);
	if(ret < 0)
		goto err_platform_driver_register;
	return ret;

err_platform_driver_register:
	platform_device_unregister(&the_pdev);
	CL_PRINT("pdev driver register fault\n");
err_platform_device_register:
	kmem_cache_destroy(vir_dev_cachep);
	CL_PRINT("pdev device register fault\n");
err_kmem_create:
	CL_PRINT("kmem_cache_create err\n");
	return ret;
	
 return 0;
}
static void __exit pdev_exit(void)
{
	platform_device_unregister(&the_pdev);
	platform_driver_unregister(&pdev_driver);
	kmem_cache_destroy(vir_dev_cachep);
	printk(KERN_EMERG "pdev exit!\n");
}

module_init(pdev_init);
module_exit(pdev_exit);


