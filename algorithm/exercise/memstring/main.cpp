#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int strcmp(char *s1, char* s2)
{
    while(*s1 || *s2) {
        if(*s1 != *s2) {
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return 0;
}

char *strcpy(char *dst, char *src)
{
    int i=0;
    while(*(src+i)) {
        *(dst+i) = *(src+i);
        i++;
    }
    *(dst+i) = '\0';
    return dst;
}

char *strncpy(char*dst, char *src, int n)
{
    int i=0;
    while(*(src + i) ) {
        *(dst +i) = *(src+i);
        if(++i == n) break;
    }
    *(dst+i) = '\0';
    return dst;
}

char *strncat(char *dst, char *src, int n)
{
    char *tmp = dst;
    while(*dst) {
        dst++;
    }
    int i=0;
    while(*(src+i)) {
        *(dst+i) = *(src+i);
        if(++i == n) break;
    }
    *(dst+i) = '\0';
    return tmp;
}

int main()
{
    /*
    int ret = strcmp("abc","abcd");
    printf("%d\n", ret);
    */
    char s1[100];
    char s2[] = "abcdefg";
    printf("%s\n",strncpy(s1,s2,7));
    printf("%s\n", strncat(s1,s2,3));
    getch();
    return 0;
}
