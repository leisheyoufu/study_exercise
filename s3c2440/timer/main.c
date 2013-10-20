#include "serial.h"
#include "timer.h"

extern struct timer_queue global_timer_queue;
extern timer_func cur_timer_func;

void uart_message1()
{
	
	putc('i');
	putc('n');
	putc('t');
	putc('1');
	putc('\r');
	putc('\n');
}

void uart_message2()
{
	
	putc('i');
	putc('n');
	putc('t');
	putc('2');
	putc('\r');
	putc('\n');
}

void uart_message3()
{
	
	putc('i');
	putc('n');
	putc('t');
	putc('3');
	putc('\r');
	putc('\n');
}


int main()
{
    unsigned char c;
    uart0_init();  
	cur_timer_func = idle_func;
	init_timer_queue(&global_timer_queue);
	enqueue_timer(&global_timer_queue,1000,uart_message1);
	enqueue_timer(&global_timer_queue,300,uart_message2);
	enqueue_timer(&global_timer_queue,400,uart_message3);
  
	putc('T');
	putc('e');
	putc('s');
	putc('t');
	putc(':');
	putc('\n');
	putc('\r');
	putstr("str_test");
	putint(987649);
	
    while(1)
    {
        
        c = getc();
     		putc(c);
    }

    return 0;
}
