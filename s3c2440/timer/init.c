

#include "serial.h"
#include "timer.h"

struct timer_queue global_timer_queue;
timer_func cur_timer_func = 0;
int counter = 0;


void disable_watch_dog(void)
{
    WTCON = 0;  
}

#define S3C2440_MPLL_200MHZ     ((0x5c<<12)|(0x01<<4)|(0x02))
#define	CLKDIVN		(*(volatile unsigned long *)0x4c000014)
#define	MPLLCON		(*(volatile unsigned long *)0x4c000004)
void clock_init(void)
{   
    CLKDIVN  = 0x03;            // FCLK:HCLK:PCLK=1:2:4, HDIVN=1,PDIVN=1

    //fast bus mode to asynchronous bus mode
__asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        
    "orr    r1, r1, #0xc0000000\n"          
    "mcr    p15, 0, r1, c1, c0, 0\n"       
    );
    MPLLCON = S3C2440_MPLL_200MHZ;  //FCLK=200MHz,HCLK=100MHz,PCLK=50MHz 
           
}

/*
Timer input clock Frequency = PCLK / {prescaler value+1} / {divider value}
50M /(99+1) / 16
*/
void timer0_init(void)
{
	TCFG0 = 99;
	TCFG1 = 0X03;
	TCNTB0 = 31250;   // 0.5 s
	//TCON &= ~(1<<1);  // manual update 0
	TCON |= (1<<1);  // manual update 0
	TCON = 0X01;
}

void init_irq(void)
{
	INTMSK &=(~(1<<10));
}

void Timer0_Handle(void)
{
	int t;

	if(INTOFFSET == 10)
	{
		counter++;
		
	
		putc('i');
		putc('r');
		putc('q');	
	//	putc(counter+'0');
		putc(':');
		putc('\r');
		putc('\n');
	
		cur_timer_func();
		
		putc('c');
		putc('u');
		putc('r');
		putc('\r');
		putc('\n');
		t = dequeue_timer(&global_timer_queue);		
		if(t == -1)
		{
			TCNTB0 = 0;
			TCON |= (1<<1);  // manual update 0
			TCON = 0X01;
		}
		else
		{
			TCON = 0X00;
			TCNTB0 = t;			
			TCON |= (1<<1);  // manual update 0
			TCON = 0X09;
		}
		putc('t');
		putc('\r');
		putc('\n');
		
	}
	
	SRCPND = 1<< INTOFFSET;
	INTPND = INTPND;
	
}

void memsetup(void)
{
    volatile unsigned long *p = (volatile unsigned long *)MEM_CTL_BASE;

   
    p[0] = 0x22011110;     //BWSCON
    p[1] = 0x00000700;     //BANKCON0
    p[2] = 0x00000700;     //BANKCON1
    p[3] = 0x00000700;     //BANKCON2
    p[4] = 0x00000700;     //BANKCON3  
    p[5] = 0x00000700;     //BANKCON4
    p[6] = 0x00000700;     //BANKCON5
    p[7] = 0x00018005;     //BANKCON6
    p[8] = 0x00018005;     //BANKCON7
    p[9]  = 0x008C04F4;
    p[10] = 0x000000B1;     //BANKSIZE
    p[11] = 0x00000030;     //MRSRB6
    p[12] = 0x00000030;     //MRSRB7
}

void copy_steppingstone_to_sdram(void)
{
    unsigned int *pdwSrc  = (unsigned int *)0;
    unsigned int *pdwDest = (unsigned int *)0x30000000;
    
    while (pdwSrc < (unsigned int *)4096)
    {
        *pdwDest = *pdwSrc;
        pdwDest++;
        pdwSrc++;
    }
}




