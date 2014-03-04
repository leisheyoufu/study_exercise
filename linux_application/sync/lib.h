#ifndef _LIB_H_
#define _LIB_H_
#include "header.h"

#define ADLER_SUM_LEN 4
#define MD5_SUM_LEN 16
#define CHUNK_SIZE 32

uint32 adler32(char *buf,int len);

#endif // _LIB_H_
