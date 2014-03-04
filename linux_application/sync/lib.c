#include "header.h"
uint32 adler32(char *buf,int len)
{
    int i;
    uint32 s1, s2;

    s1 = s2 = 0;
    for (i = 0; i < len; i++) {
        s1 += buf[i];
        s2 += s1;
    }
    return (s1 & 0xffff) + (s2 << 16);
}
