/*
 * init.c: 进行一些初始化
 */ 

#include "s3c24xx.h"

/*
 * LED1,LED2,LED4  -- GPB5、GPB6、GPB7、GPB8
 */
#define	GPB5_out	(1<<(5*2))
#define	GPB6_out	(1<<(6*2))
#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))

#define	GPB5_msk	(3<<(5*2))
#define	GPB6_msk	(3<<(6*2))
#define	GPB7_msk	(3<<(7*2))
#define	GPB8_msk	(3<<(8*2))

/*
 * K1,K2,K3,K4 -- GPF1、GPF4、GPF2、GPF0
 */
#define GPF0_int     (0x2<<(0*2))
#define GPF1_int     (0x2<<(1*2))
#define GPF2_int     (0x2<<(2*2))
#define GPF4_int     (0x2<<(4*2))

#define GPF0_msk    (3<<(0*2))
#define GPF1_msk    (3<<(1*2))
#define GPF2_msk    (3<<(2*2))
#define GPF4_msk    (3<<(4*2))


void disable_watch_dog(void)
{
    WTCON = 0;  
}

void init_led(void)
{	
	GPBCON &= ~(GPB5_msk | GPB6_msk | GPB7_msk | GPB8_msk);
	GPBCON |= GPB5_out | GPB6_out | GPB7_out | GPB8_out;
}


void init_irq( )
{
	
	GPFCON &= ~(GPF0_msk | GPF1_msk | GPF2_msk | GPF4_msk);
	GPFCON |= GPF0_int | GPF1_int | GPF2_int | GPF4_int;

    
    EINTMASK &= ~(1<<4);            
   
    PRIORITY = (PRIORITY & ((~0x01) | ~(0x3<<7)));

    // enable EINT0、EINT1、EINT2、EINT4_7
    INTMSK   &= (~(1<<0)) & (~(1<<1)) & (~(1<<2)) & (~(1<<4));
}




