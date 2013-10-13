#include "cdev_message.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("vir_cdev");
MODULE_VERSION("1.0.0");

static struct vir_device *vir_devices;
	static struct class *vir_cdev_class;


static ssize_t cdev_write (struct file *filp, const char __user *buf,
                            size_t count, loff_t *pos);

static int cdev_open (struct inode *inode, struct file *filp)
{
	struct vir_device *dev;
	dev = container_of(inode->i_cdev,struct vir_device,cdev);
	CL_PRINT("dev = %p\n",dev);
	filp->private_data = dev;
    return 0;  /* success */
}

static int cdev_release (struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t cdev_read (struct file *filp, char __user *buf,
                           size_t count, loff_t *pos)
{	
	ssize_t size;	
	ssize_t retval;
	if(count ==(size_t)0 )
	{
		CL_PRINT("read start pos = %d, count = %d\n",*pos,count);
		size = 0;
		goto out;
	}	
	struct vir_message *priv,*tmp;
	struct vir_device *dev = filp->private_data;
	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if(list_empty(&dev->head) && *pos == dev->len)
	{	
		if (filp->f_flags & O_NONBLOCK)
			retval = -EAGAIN;		
			goto out;
	}
	if(*pos < dev->len)
	{
		CL_PRINT("dev len = %d\n",dev->len);
		size = *pos + count >dev->len?dev->len-*pos:count;
		if( copy_to_user(buf,dev->buf+*pos,size))
		{
			retval= -ENOMEM;
			goto out;
		}
	}
	else
	{
		if(list_empty(&dev->head))
		{
			size = 0;
			goto out;
		}	
		spin_lock(&dev->priv_lock);  // only test the spin lock
		list_for_each_entry_safe(priv,tmp,&dev->head,list)
		{			
			list_del(&priv->list);
			break;
		}
		spin_unlock(&dev->priv_lock);
		*pos = 0;		
		strcpy(dev->buf,priv->buf);
		kfree(priv);
		dev->len = strlen(dev->buf);
		size = count >dev->len?dev->len:count;
		if (copy_to_user(buf, dev->buf, size))
		{
		   retval=-ENOMEM;
		   goto out;
		}
	}
	CL_PRINT("cdev read return size = %d\n",size);
	dev->len -=size;
	retval = size;
out:	
	up(&dev->sem);	
	CL_PRINT("out size = %d count = %d\n",size,count);
    return retval;
}
static ssize_t cdev_write (struct file *filp, const char __user *buf,
                            size_t count, loff_t *pos)
{
	if(count <=0)
		return -EINVAL;

    int size = count < BUF_LEN ? count :BUF_LEN;
	struct vir_device *dev = filp->private_data;
	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	struct vir_message *priv;
	priv = kzalloc(sizeof(*priv),GFP_KERNEL);
	if(priv == NULL)
	{
		return -ENOMEM;
	}
    if (copy_from_user(priv->buf, buf, size))
        return -ENOMEM;
	priv->buf[BUF_LEN-1] = '\0';	
	CL_PRINT("%s\n",priv->buf);
	spin_lock(&dev->priv_lock);
	list_add_tail(&priv->list,&dev->head);
	spin_unlock(&dev->priv_lock);
	up(&dev->sem);
    return size;
}

static struct file_operations cdev_fops = {
        .read = cdev_read,
        .write = cdev_write,
        .open = cdev_open,
        .release = cdev_release,
};

static int cdev_setup(struct vir_device *vir_device,dev_t dev,char *node_name)
{
	int ret = 0;
	
	cdev_init(&vir_device->cdev,dev);
	vir_device->cdev.ops=&cdev_fops;
    vir_device->cdev.owner = THIS_MODULE;
    ret = cdev_add(&vir_device->cdev, dev, 1);
    if (ret)
    {
        CL_ERR("cdev: cdev_add failed!\n");
        cdev_del(&vir_device->cdev);
        return ret;
    }
	INIT_LIST_HEAD(&vir_device->head);
	sema_init(&vir_device->sem,1);
	spin_lock_init(&vir_device->priv_lock);
	dev = device_create(vir_cdev_class,NULL,dev,NULL,node_name);

}
static int cdev_cleanup(struct vir_device *vir_device)
{
	struct vir_message *priv,*tmp;

	cdev_del(&vir_device->cdev);
	
	list_for_each_entry_safe(priv,tmp,&vir_device->head,list)
		{
			list_del(&priv->list);
			kfree(priv);
		}


}

static int __init cdev_vir_init(void)
{
	int ret=0;
	dev_t dev;
	int i;
	char node_name[NAME_LEN];
	printk(KERN_ERR "cdev message world!\n");
	ret = alloc_chrdev_region(&dev, 0, DEV_NUM, device_name);
    if (ret)
    {
		CL_ERR("cdev: alloc_chardev_region failed!\n");
        return ret;
    }

	vir_cdev_class = class_create(THIS_MODULE,device_name);
	if(IS_ERR(vir_cdev_class)) {
        CL_ERR(" failed in creating class.\n");
        return -1;
    }
	CL_PRINT("class_create\n");

	vir_devices = kzalloc(sizeof(struct vir_device)*DEV_NUM,GFP_KERNEL);
	if(vir_devices == NULL)
	{
		CL_ERR("kmalloc vir_device \n");
	}
	for(i=0;i<DEV_NUM;i++)
	{
		sprintf(node_name,"%s%d",device_name,i);		
		cdev_setup(&vir_devices[i],dev+i,node_name);	
	}

		/*
	*/


 return 0;
}
static void __exit cdev_vir_exit(void)
{
	int i;
	for(i=0;i<DEV_NUM;i++)
	{		
		cdev_cleanup(&vir_devices[i]);
		device_destroy(vir_cdev_class,vir_devices[i].cdev.dev);
	}
    unregister_chrdev_region(vir_devices[0].cdev.dev, DEV_NUM);
	class_destroy(vir_cdev_class);
	kfree(vir_devices);
}

module_init(cdev_vir_init);
module_exit(cdev_vir_exit);


