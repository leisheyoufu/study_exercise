#include "timer.h"

extern timer_func cur_timer_func;

/* delay is ms  <1000*/
void enqueue_timer(struct timer_queue *q,int delay,timer_func f)
{
	int i=-1;
	delay = delay * TIMER_CLK  >> 3;
	
	if(q->size == TIMER_SIZE )
		return ;
	for(i=q->size-1;i>=0;i--)
	{
		if(q->queue[i].delay >delay )
		{
			q->queue[i+1].delay = q->queue[i].delay;
			q->queue[i+1].f = q->queue[i].f;
		}
		else
		{
			break;
		}
	}
	q->queue[i+1].delay = delay;
	q->queue[i+1].f = f;	
	q->size++;
	}
			
	

void init_timer_queue(struct timer_queue *q)
{
	q->size = 0;
}

void idle_func()
{
	putc('i');
	putc('d');
	putc('l');
	putc('e');
	putc('\r');
	putc('\n');
}
int dequeue_timer(struct timer_queue *q)
{	
	int i;
	if(q->size == 0 )
	{
		cur_timer_func = idle_func;
		return -1;
	}
	int t = q->queue[0].delay;
	cur_timer_func = q->queue[0].f;
	q->size--;
	for( i=0;i<q->size;i++)
	{
		q->queue[i].delay = q->queue[i+1].delay -t;
		q->queue[i].f = q->queue[i+1].f;
	}
	
	return t;
}
		
	
	