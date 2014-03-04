#ifndef _UTIL_H_
#define _UTIL_H_
#include "header.h"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>=(b)?(a):(b))

void read_buf(int f,char *buf,int len);
char *map_file(int fd,off_t len);
void unmap_file(char *buf,off_t len);
int readfd(int fd,char *buffer,int N);
void write_buf(int f,char *buf,int len);
#endif // _UTIL_H_
