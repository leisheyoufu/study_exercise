#include "dma_copy.h"
#define DRIVER_NAME	"dma_copy"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("leisheyoufu");
MODULE_DESCRIPTION("hello world dma_copy world");

#define DEV_NUM 1
#define BUF_SZ 512*1024
#define NO_DMA 0
#define USE_DMA 1

#define DMA0_BASE_ADDR 0x4B000000
#define DMA1_BASE_ADDR 0x4B000040
#define DMA2_BASE_ADDR 0x4B000080
#define DMA3_BASE_ADDR 0x4B0000C0

#define INT_DMA3 IRQ_DMA3

static char device_name[]="dma_copy_device";
static char class_name[]="dma_copy_class";
static int major;
static struct class *dma_copy_class;
static struct dma_copy_device dma_copy_dev;
static struct dma_buffer dma_buf;
static int ev_dma = 0;

static int dma_ioctl (struct file *file, unsigned int cmd,
			   unsigned long arg)
{
	int i;
	CL_DBG_PRINT("dma ioctl cmd = %u\n",cmd);
    memset(dma_buf.src, 1, BUF_SZ);
    memset(dma_buf.dst, 0, BUF_SZ);
    switch (cmd) {
    case NO_DMA: {
        for(i=0; i<BUF_SZ; i++)
            dma_buf.dst[i] = dma_buf.src[i];
        if (0 == memcmp(dma_buf.src, dma_buf.dst, BUF_SZ))
            CL_INFO_PRINT("(NO_DMA)Success to memcpy from source to destination\n");
        else
            CL_INFO_PRINT("(NO_DMA)Failed to memcpy from source to destination\n");
    }
    break;
    case USE_DMA: {
    	ev_dma = 1;

        dma_copy_dev.hw.dma_regs->didst = dma_buf.dst_phys;
        dma_copy_dev.hw.dma_regs->disrcc = (0<<1)|(0<<0);
        dma_copy_dev.hw.dma_regs->didstc = (0<<2)|(0<<1)|(0<<0);
        dma_copy_dev.hw.dma_regs->dcon = (0<<31)|(1<<30)|(1<<29)|(0<<28)|(1<<27)|(0<<24)|
                         (0<<23)|(0<<22)|(0<<20)|(BUF_SZ<<0);

        dma_copy_dev.hw.dma_regs->dmasktrig = (1<<1)|(1<<0); // start transfer
        wait_event_interruptible(dma_copy_dev.dma_waitq, ev_dma);
        if (0 == memcmp(dma_buf.src, dma_buf.dst, BUF_SZ))
            CL_INFO_PRINT("(USE_DMA)Success to memcpy from source to destination\n");
        else
            CL_INFO_PRINT("(USE_DMA)Failed to memcpy from source to destination\n");
    }
    break;
    }
    return 0;
}
static int cdev_open (struct inode *inode, struct file *filp)
{
	CL_INFO_PRINT("cdev_open\n");
    return 0;  /* success */
}

static int cdev_release (struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t cdev_read (struct file *filp, char __user *buf,
                           size_t count, loff_t *pos)
{
    return 0;
}
static ssize_t cdev_write (struct file *filp, const char __user *buf,
                            size_t count, loff_t *pos)
{
    return 0;
}

static struct file_operations dma_copy_fops = {
    .unlocked_ioctl = dma_ioctl,
    .read = cdev_read,
	.write = cdev_write,
	.open = cdev_open,
	.release = cdev_release,
};


static irqreturn_t dma_copy_irq(int irq, void *dat)
{
	ev_dma = 1;
	wake_up_interruptible(&dma_copy_dev.dma_waitq);
    return IRQ_HANDLED;
}

static int __init dma_copy_init(void)
{
    int ret;
    dev_t devt;
    printk("dma_copy init\n");
    dma_buf.src = dma_alloc_writecombine(NULL, BUF_SZ, &dma_buf.src_phys,GFP_KERNEL);
    if (!dma_buf.src ) {
        CL_DBG_PRINT("src-dma alloc failed\n");
        ret = -ENOMEM;
		goto err_alloc_dma_src;
    }

    dma_buf.dst = dma_alloc_writecombine(NULL, BUF_SZ, &dma_buf.dst_phys, GFP_KERNEL);
    if (!dma_buf.dst) {
        CL_DBG_PRINT("dst-dma alloc failed\n");
        ret = -ENOMEM;
        goto err_alloc_dma_dst;
    }

    ret = alloc_chrdev_region(&devt, 0, DEV_NUM, device_name);
    if (ret) {
        CL_DBG_PRINT("dma_copy: alloc_chardev_region failed!\n");
        goto err_alloc_chrdev_region;
    }

    major = MAJOR(devt);
    cdev_init(&dma_copy_dev.cdev, &dma_copy_fops);
    dma_copy_dev.cdev.ops=&dma_copy_fops;
    dma_copy_dev.cdev.owner = THIS_MODULE;

    ret = cdev_add(&dma_copy_dev.cdev, devt, DEV_NUM);
    if (ret) {
        goto err_cdev_add;
    }

    dma_copy_class = class_create(THIS_MODULE,class_name);
    if(IS_ERR(dma_copy_class)) {
        CL_DBG_PRINT(" failed in creating class.\n");
        ret = PTR_ERR(dma_copy_class);
        goto err_class_create;
    }

    if(IS_ERR(device_create(dma_copy_class,NULL,devt,NULL,device_name))) {
        CL_DBG_PRINT("device_create failed\n");
        goto err_device_create;
    }

    dma_copy_dev.hw.dma_regs = ioremap(DMA3_BASE_ADDR, sizeof(struct dma_regs));
    if (!dma_copy_dev.hw.dma_regs ) {
        CL_DBG_PRINT(" dma ioremap failed.\n");
        ret = -ENOMEM;
        goto err_ioremap;

    }
    init_waitqueue_head(&dma_copy_dev.dma_waitq);
    ret = request_irq(INT_DMA3, dma_copy_irq, IRQF_SHARED, "dma3", &dma_copy_dev);
    if(ret) {
        CL_DBG_PRINT("dma3 busy\n");
        goto err_req_irq;
    }
    return ret;

err_req_irq:
    iounmap(dma_copy_dev.hw.dma_regs);
err_ioremap:
    device_destroy(dma_copy_class, MKDEV(major, 0));
err_device_create:
    class_destroy(dma_copy_class);
err_class_create:
    cdev_del(&dma_copy_dev.cdev);
err_cdev_add:
    unregister_chrdev_region(MKDEV(major, 0), DEV_NUM);
err_alloc_chrdev_region:
	dma_free_writecombine(NULL, BUF_SZ, dma_buf.dst, dma_buf.dst_phys);
err_alloc_dma_dst:
	dma_free_writecombine(NULL, BUF_SZ, dma_buf.src, dma_buf.src_phys);
err_alloc_dma_src:
    return ret;
}
static void __exit dma_copy_exit(void)
{
    printk("dma_copy exit\n");
    dma_free_writecombine(NULL, BUF_SZ, dma_buf.src, dma_buf.src_phys);
    dma_free_writecombine(NULL, BUF_SZ, dma_buf.dst, dma_buf.dst_phys);
    free_irq(INT_DMA3, &dma_copy_dev);
    iounmap(dma_copy_dev.hw.dma_regs);
    device_destroy(dma_copy_class, MKDEV(major, 0));
    class_destroy(dma_copy_class);
    cdev_del(&dma_copy_dev.cdev);
    unregister_chrdev_region(MKDEV(major, 0), 1);
}

module_init(dma_copy_init);
module_exit(dma_copy_exit);


