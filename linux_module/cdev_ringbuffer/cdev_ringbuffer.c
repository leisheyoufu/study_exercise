#include "cdev_ringbuffer.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("vir_cdev");
MODULE_VERSION("1.0.0");

static struct vir_device *vir_devices;
	static struct class *vir_cdev_class;

static int spacefree(struct vir_device *dev)
{
	if (dev->head == dev->tail)
		return dev->buf_len - 1;
	return ((dev->head + dev->buf_len - dev->tail) % dev->buf_len) - 1;
}

static ssize_t cdev_write (struct file *filp, const char __user *buf,
                            size_t count, loff_t *pos);

static int cdev_open (struct inode *inode, struct file *filp)
{
	struct vir_device *dev;
	dev = container_of(inode->i_cdev,struct vir_device,cdev);
	CL_PRINT("dev = %p\n",dev);
	filp->private_data = dev;
	
  return nonseekable_open(inode, filp);
}

static int cdev_release (struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t cdev_read (struct file *filp, char __user *buf,
                           size_t count, loff_t *pos)
{	
	ssize_t size;
	int space;
CL_PRINT("read  count = %d\n",count);
	if(count <=0 )
	{
		return -EINVAL;
	}	

	struct vir_device *dev = filp->private_data;
	if(down_interruptible(&dev->sem))
		return -ERESTARTSYS;
		CL_PRINT("read head %d   tail %d \n",dev->head,dev->tail );
	
	while( dev->tail == dev->head)
	{
		up(&dev->sem); /* release the lock */
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
			CL_PRINT("read head %d   tail %d \n",dev->head,dev->tail );
		if (wait_event_interruptible(dev->inq, (dev->tail != dev->head)))
			return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
		/* otherwise loop, but first reacquire the lock */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}
		CL_PRINT("read head %d   tail %d \n",dev->head,dev->tail );
	if( dev->tail > dev->head)
		space = dev->tail - dev->head;
	else
		space = dev->buf_len - (dev->head - dev->tail);
  size = count < space ? count :space;

  if (copy_to_user(buf, dev->buf+dev->head, size))
  	{
  		up (&dev->sem);
      return -EFAULT;
  }
 	dev->head = (dev->head+size) % dev->buf_len;
 	up (&dev->sem);
 	wake_up_interruptible(&dev->outq);
	CL_PRINT("read head %d   tail %d return size = %d\n",dev->head,dev->tail,size);
	return size;
}
static ssize_t cdev_write (struct file *filp, const char __user *buf,
                            size_t count, loff_t *pos)
{	
	size_t size;
	
	if(count <=0)
		return -EINVAL;
	
	struct vir_device *dev = filp->private_data;
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;
		CL_PRINT("head %d   tail %d buf_len %d \n",dev->head,dev->tail,dev->buf_len );
	int space = spacefree(dev);
	
	while(!space)
	{
	
		up(&dev->sem); /* release the lock */
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
	
		if (wait_event_interruptible(dev->outq, (space = spacefree(dev))!=0))
			return -ERESTARTSYS; /* signal: tell the fs layer to handle it */
		/* otherwise loop, but first reacquire the lock */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}
			
	if( dev->tail > dev->head)
		space = dev->buf_len - (dev->tail - dev->head) -1;		
	else
		space = dev->head - dev->tail -1;
	
  size = count < space ? count :space;

  if (copy_from_user(dev->buf+dev->tail, buf, size))
      return -EFAULT;
  up (&dev->sem);
 	dev->tail = (dev->tail+size) % dev->buf_len;
 	wake_up_interruptible(&dev->inq);

  return size;
}

static unsigned int cdev_poll(struct file *filp, poll_table *wait)
{
	struct vir_device *dev = filp->private_data;
	unsigned int mask = 0;

	down(&dev->sem);
	printk(" enter wait\n");
	poll_wait(filp, &dev->inq,  wait);
	poll_wait(filp, &dev->outq, wait);
	printk(" wake up\n");
	if (dev->head != dev->tail)
		mask |= POLLIN | POLLRDNORM;	/* readable */
	if (spacefree(dev))
		mask |= POLLOUT | POLLWRNORM;	/* writable */
	up(&dev->sem);
	return mask;
}

static int cdev_fasync(int fd, struct file *filp, int mode)
{
	struct vir_device *dev = filp->private_data;

	return fasync_helper(fd, filp, mode, &dev->async_queue);
}


static struct file_operations cdev_fops = {
        .read = cdev_read,
        .write = cdev_write,
        .open = cdev_open,
        .release = cdev_release,
        .fasync =	cdev_fasync,
        .poll =		cdev_poll,
};

static int cdev_setup(struct vir_device *vir_device,dev_t dev,char *node_name)
{
	int ret = 0;
	
	cdev_init(&vir_device->cdev,dev);
	vir_device->head = vir_device->tail = 0;
	vir_device->cdev.ops=&cdev_fops;
  vir_device->cdev.owner = THIS_MODULE;
  vir_device->buf_len = BUF_LEN;
  ret = cdev_add(&vir_device->cdev, dev, 1);
  if (ret)
  {
      CL_ERR("cdev: cdev_add failed!\n");
      cdev_del(&vir_device->cdev);
      return ret;
  }
  	CL_PRINT("head %d   tail %d buf_len %d \n",vir_device->head,vir_device->tail,vir_device->buf_len );
	sema_init(&vir_device->sem,1);
	init_waitqueue_head(&vir_device->inq);
	init_waitqueue_head(&vir_device->outq);
	dev = device_create(vir_cdev_class,NULL,dev,NULL,node_name);

}
static int cdev_cleanup(struct vir_device *vir_device)
{	
	cdev_del(&vir_device->cdev);
}

static int __init cdev_vir_init(void)
{
	int ret=0;
	dev_t dev;
	int i;
	char node_name[NAME_LEN];
	printk(KERN_ERR "cdev ringbuffer world!\n");
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


