#ifndef UTIL_MAC_H_INCLUDED
#define UTIL_MAC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

unsigned char a2x(const char c)
{
    switch(c) {
    case '0'...'9':
        return (unsigned char)atoi(&c);
    case 'a'...'f':
        return 0xa + (c-'a');
    case 'A'...'F':
        return 0xa + (c-'A');
    default:
        goto error;
    }
error:
    exit(0);
}

#define MAC_LEN_IN_BYTE 6
#define COPY_STR2MAC(mac,str)  \
    int j; \
    do { \
        for(j = 0; j < MAC_LEN_IN_BYTE; j++) {\
            mac[j] = (a2x(str[j*3]) << 4) + a2x(str[j*3 + 1]);\
        }\
    } while(0)



int mac_compare(char mac[6],char str[6])
{
    char mac_r[6];
    int i;
    COPY_STR2MAC(mac_r,str);
    for( i=0; i<6; i++) {
        if((unsigned char)mac[i] < (unsigned char )mac_r[i]) {
            return -1;
        } else if((unsigned char)mac[i] > (unsigned char )mac_r[i]) {
            return 1;
        }
    }
    printf("equal\n");
    return 0;
}


#endif // UTIL_MAC_H_INCLUDED
