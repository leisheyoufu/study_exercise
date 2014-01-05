#include "usb_downloader.h"

#define USB_DOWNLOADER_MAJOR	102
#define USB_DOWNLOADER_MINOR	0
#define DRIVER_NAME	"usb_downloader"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("leisheyoufu");
MODULE_DESCRIPTION("hello world rootkit world");

struct usb_downloader_dev
{
    struct usb_device *udev;
    struct mutex io_mutex;
    char*	bulkout_buffer;
    __u8	bulk_out_endpointAddr;
};

static struct usb_driver usb_downloader_driver;

static int usb_downloader_open(struct inode *node, struct file *file)
{
    struct usb_interface *interface;
	struct usb_downloader_dev *dev;

	interface = usb_find_interface(&usb_downloader_driver, iminor(node));
	if(!interface)
		return -ENODEV;

	dev = usb_get_intfdata(interface);
	dev->bulkout_buffer = kzalloc(BULKOUT_BUFFER_SIZE, GFP_KERNEL);
	if(!(dev->bulkout_buffer))
		return -ENOMEM;
	if(!mutex_trylock(&dev->io_mutex))
		return -EBUSY;
	file->private_data = dev;
	return 0;
}
static int usb_downloader_release(struct inode *node, struct file *file)
{
    struct usb_downloader_dev *dev;
	dev = (struct usb_downloader_dev*)(file->private_data);
	kfree(dev->bulkout_buffer);
	mutex_unlock(&dev->io_mutex);
	return 0;
}
static ssize_t usb_downloader_read(struct file *file, char __user *buf, size_t len, loff_t *loff)
{
    return -EPERM;
}
static ssize_t usb_downloader_write(struct file *file, const char __user *buf, size_t len, loff_t *loff)
{
    size_t to_write;
	struct usb_downloader_dev *dev = file->private_data;
	int ret;
	int actual_length;
	size_t total_writed;

	total_writed = 0;
	while(len > 0)
	{
		to_write = min(len, BULKOUT_BUFFER_SIZE);

		if(copy_from_user(dev->bulkout_buffer, buf+total_writed, to_write))
		{
			printk(KERN_ERR "secbulk:copy_from_user failed!\n");
			return -EFAULT;
		}

		ret = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, dev->bulk_out_endpointAddr),
				dev->bulkout_buffer,
				to_write,
				&actual_length,
				3*HZ);
		if(ret || actual_length!=to_write)
		{
			CL_DBG_PRINT("send bulk buffer failed\n");
			return -EFAULT;
		}
		len -= to_write;
		total_writed += to_write;
	}
	return total_writed;
}


static struct file_operations usb_downloader_fops = {
	.owner 	=	THIS_MODULE,
	.read 	=	usb_downloader_read,
	.write	=	usb_downloader_write,
	.open   =	usb_downloader_open,
	.release=	usb_downloader_release,
};

static struct usb_class_driver usb_downloader_class = {
	.name = 	"usb-downloader%d",
	.fops =		&usb_downloader_fops,
	.minor_base=	100,
};


static struct usb_device_id usb_downloader_table[]= {
	{ USB_DEVICE(0x5345, 0x1234)},
	{ }
};
static int usb_downloader_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    int ret;
    struct usb_downloader_dev *dev;
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;
    int i;

    CL_INFO_PRINT("secbulk:secbulk probing...\n");

    dev = kzalloc(sizeof(*dev), GFP_KERNEL);
    if(PTR_ERR(dev))
    {
        ret = -ENOMEM;
        goto err;
    }

    iface_desc = interface->cur_altsetting;
    for(i=0; i < iface_desc->desc.bNumEndpoints; i++)
    {
        endpoint = &(iface_desc->endpoint[i].desc);
        if(!dev->bulk_out_endpointAddr
        && usb_endpoint_is_bulk_out(endpoint))
        {
            CL_INFO_PRINT("bulk endpoint found\n");
            dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
            break;
        }
    }

    if(!(dev->bulk_out_endpointAddr))
    {
        ret = -EBUSY;
        goto err;
    }

    ret = usb_register_dev(interface, &usb_downloader_class);
    if(ret)
    {
        CL_INFO_PRINT("usb register failed\n");
        return ret;
    }
    dev->udev = usb_get_dev(interface_to_usbdev(interface));

    usb_set_intfdata(interface, dev);

    mutex_init(&dev->io_mutex);
    return 0;
err:
    if(!dev)
        kfree(dev);
    return ret;
}

static void usb_downloader_disconnect(struct usb_interface *interface)
{
    struct usb_download_dev *dev = NULL;
	CL_INFO_PRINT("usb_downloader_disconnect:usb_downloader_disconnect disconnected!\n");
	dev = usb_get_intfdata(interface);
	if( dev != NULL )
		kfree(dev);
	usb_deregister_dev(interface, &usb_downloader_class);
	return;
}

static struct usb_driver usb_downloader_driver= {
	.name=		"usb-downloader",
	.probe=		usb_downloader_probe,
	.disconnect=	usb_downloader_disconnect,
	.id_table=	usb_downloader_table,
	.supports_autosuspend=0,
};

static int __init usb_downloader_init(void)
{
    int ret;
    printk("usb-downloader init\n");
    ret = usb_register(&usb_downloader_driver);
	if(ret)
	{
	    CL_DBG_PRINT("usb_downloader_driver register failed\n");
		return ret;
	}
	return 0;
}
static void __exit usb_downloader_exit(void)
{
    printk("usb-downloader exit\n");
    usb_deregister(&usb_downloader_driver);

}

module_init(usb_downloader_init);
module_exit(usb_downloader_exit);


