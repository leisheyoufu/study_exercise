#ifndef SERIAL_H
#define SERIAL_H

#include "s3c24xx.h"

void uart0_init(void);
void putc(unsigned char c);
unsigned char getc(void);
void putstr(char *str);
void putint(unsigned int num);


#endif
