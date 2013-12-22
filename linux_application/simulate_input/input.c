#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static unsigned long long index = 0;

void simulate_key(int fd,int kval)
{
    struct input_event event;

    event.type = EV_KEY;
    event.value = 1;
    event.code = kval;
    gettimeofday(&event.time,0);
    write(fd,&event,sizeof(event)) ;

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(fd, &event, sizeof(event));

    memset(&event, 0, sizeof(event));
    gettimeofday(&event.time, NULL);
    event.type = EV_KEY;
    event.code = kval;
    event.value = 0;
    write(fd, &event, sizeof(event));

    event.type = EV_SYN;
    event.code = SYN_REPORT;
    event.value = 0;
    write(fd, &event, sizeof(event));
}

static void show_event(struct input_event* event)
{
    printf("index = %u type=%d code=%d value=%d\n", index++, event->type, event->code, event->value);
    return;
}

int main(int argc, char* argv[])
{
    struct input_event event = {{0}, 0};
    const char* file_name = argc == 2 ? argv[1] : "/dev/input/event1";

    int fd = open(file_name, O_RDWR);
    int count = 0;
    if(fd > 0)
    {
        while(1)
        {
            /*
            int ret = read(fd, &event, sizeof(event));
            if(ret == sizeof(event))
            {
                show_event(&event);
            }
            else
            {
                break;
            }
            */
            if(count %2 == 0)
            {
                simulate_key(fd,KEY_CAPSLOCK);
                printf("caps lock enter\n");
            }
            else
            {
                simulate_key(fd,KEY_NUMLOCK);
                printf("caps lock enter\n");
            }
            sleep(1);
            count++;

        }
        close(fd);
    }

    return 0;
}
