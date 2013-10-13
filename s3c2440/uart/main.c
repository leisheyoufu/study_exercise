#include "serial.h"

int main()
{
    unsigned char c;
    uart0_init();   
  
	putc('T');
	putc('e');
	putc('s');
	putc('t');
	putc(':');
	putc('\n');
	putc('\r');

    while(1)
    {
        
        c = getc();
     		putc(c);
    }

    return 0;
}
