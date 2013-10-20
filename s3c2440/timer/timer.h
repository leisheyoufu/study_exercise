#ifndef TIMER_H
#define TIMER_H

#include "s3c24xx.h"

#define TIMER_CLK  62500
#define TIMER_SIZE 5
typedef void (*timer_func)();

struct timer_struct
{
	int delay;
	timer_func f;	
};

struct timer_queue
{
	int size;
	struct timer_struct queue[TIMER_SIZE];
};

void init_timer_queue(struct timer_queue *q);	
void enqueue_timer(struct timer_queue *q,int delay,timer_func f);
int dequeue_timer(struct timer_queue *q);
void idle_func();

#endif
