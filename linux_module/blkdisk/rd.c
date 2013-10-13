
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/vmalloc.h>
#include <linux/hdreg.h>
#include <linux/blkdev.h>
#include <linux/blkpg.h>
#include <asm/uaccess.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("CL");
MODULE_DESCRIPTION("vir_blkdev");
MODULE_VERSION("1.0.0");
#define CL_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)

#define BLK_RD_DEV_NAME "cl_rd" //dev name
#define BLK_RD_DEV_MAJOR 220  //major 
#define BLK_RD_MAX_DEVICE 2    // max dev num
#define BLK_BLOCKSIZE  1024
#define BLK_RD_SECTOR_SIZE 512   // sector size
#define BLK_RD_SIZE (40*1024*1024)  // total disk size 
#define BLK_RD_SECTOR_TOTAL (BLK_RD_SIZE/BLK_RD_SECTOR_SIZE)  // sector num

typedef struct
{
	unsigned char *data;
	struct request_queue *queue;
	struct gendisk *gd;
}blk_rd_device;

static char *vdisk[BLK_RD_MAX_DEVICE];

static blk_rd_device device[BLK_RD_MAX_DEVICE];


static int blk_rd_make_request(struct request_queue *q, struct bio *bio)/*制造请求函数*/
{
	blk_rd_device *rd_device;    
	char *ptr;
	char *buffer;
	struct bio_vec *bvec;
	int i;


	if(((bio->bi_sector*BLK_RD_SECTOR_SIZE) + bio-> bi_size) > BLK_RD_SIZE)
	{
		bio_io_error(bio);  // bio->bi_size
		return 0;
	}
	else
	{

		rd_device = (blk_rd_device *) bio->bi_bdev->bd_disk-> private_data;   
		ptr = rd_device->data + (bio-> bi_sector*BLK_RD_SECTOR_SIZE);  

		bio_for_each_segment(bvec, bio, i)/*循环遍历的宏*/
		{

			buffer = kmap(bvec->bv_page) + bvec-> bv_offset;//kmap()函数？？？

			switch(bio_data_dir(bio))//??????????????????????????????
			{
				case READA :    
				case READ : memcpy(buffer, ptr, bvec-> bv_len);
							break;
				case WRITE : memcpy(ptr, buffer, bvec-> bv_len);
							 break;
				default : kunmap(bvec->bv_page);
						  bio_io_error(bio);
						  return 0;            
			}

			kunmap(bvec->bv_page);
			ptr += bvec->bv_len;
		}
		
		bio_endio(bio,0);
		return 0;
	}    
}

int blk_rd_open(struct inode *inode, struct file *filp)
{
	return 0;
}

int blk_rd_release (struct inode *inode, struct file *filp)
{
	return 0;
}

int blk_rd_ioctl(struct inode *inode, struct file *filp, unsigned int cmd,unsigned long arg)
{
	//return -ENOTTY;
	int error;
	struct block_device *bdev = inode->i_bdev;
	if(cmd!= BLKFLSBUF)
	{
		return -ENOTTY;//不适当的I/O控制操作（没有tty终端）
	}
	error = -EBUSY;//资源正忙
	// down(&bdev->bd_mount_sem);
	if(bdev->bd_openers <= 2)
	{
		truncate_inode_pages(bdev->bd_inode->i_mapping,0);
		error = 0;
	}
	//  up(&bdev->bd_mount_sem);
	return error;
}
//block_device_operations 结构体是对块设备操作的集合
static struct block_device_operations vrd_fops =
{
	.owner = THIS_MODULE,
	.open = blk_rd_open,
	.release = blk_rd_release,
	.ioctl = blk_rd_ioctl,
};
int blk_rd_init(void)
{
	int i;    
	int err = -ENOMEM;
	for(i=0; i < BLK_RD_MAX_DEVICE; i++)
	{
		vdisk[i] = vmalloc(BLK_RD_SIZE);  // alloc buffer for the disk
	}    	/*注册vrd设备驱动程序*/
	if(register_blkdev(BLK_RD_DEV_MAJOR, BLK_RD_DEV_NAME))// registe blk dev
	{
		err = -EIO;
		goto out;
	}
	/**/
	for(i = 0; i < BLK_RD_MAX_DEVICE; i++)
	{
		device[i].data = vdisk[i]; // assign vdisk mem buffer to blk_rd_device   
	
		device[i].gd = alloc_disk(1);  // alloc disk node  1 is the minor

		if (!device[i].gd)
			goto out;

		device[i].queue = blk_alloc_queue(GFP_KERNEL);  // request queue
		if (!device[i].queue)
		{
			put_disk(device[i].gd);
			goto out;
		}

		blk_queue_make_request(device[i].queue, &blk_rd_make_request);  // make_request_fn: blk_re_make_request
	
		blk_queue_max_hw_sectors(device[i].queue,BLK_BLOCKSIZE);

		device[i].gd->major = BLK_RD_DEV_MAJOR;
		device[i].gd->first_minor = i;
		device[i].gd->fops = &vrd_fops;
		device[i].gd->queue = device[i].queue;
		device[i].gd->private_data = &device[i];  // gendisk store the rd_device 
		sprintf(device[i].gd->disk_name, "blk_rd%c" , 'a'+i);//
		set_capacity(device[i].gd,BLK_RD_SECTOR_TOTAL);

		add_disk(device[i].gd);
	}
	CL_PRINT("RAMDISK driver initialized!");
	return 0;
out:
	while (i--) {
		put_disk(device[i].gd);
		blk_cleanup_queue(device[i].queue);
	}
	return err;
}

void blk_rd_exit(void)
{
	int i;    
	for(i = 0; i < BLK_RD_MAX_DEVICE; i++)
	{
		del_gendisk(device[i].gd);//删除gendisk结构体    
		put_disk(device[i].gd);//减少gendisk结构体的引用计数
		blk_cleanup_queue(device[i].queue);
	}
	unregister_blkdev(BLK_RD_DEV_MAJOR, BLK_RD_DEV_NAME);
	for(i=0;i < BLK_RD_MAX_DEVICE; i++)
	{
		vfree(vdisk[i]);
	}
}
module_init(blk_rd_init);
module_exit(blk_rd_exit);


