
#include "s3c24xx.h"


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




