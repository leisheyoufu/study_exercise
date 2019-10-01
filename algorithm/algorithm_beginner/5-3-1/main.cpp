#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

int a[1001];
int c = 0;
int reverse(char *s)
{
    int rnum;
    int len = strlen(s);
    for(int i=0; i<len/2; i++) {
        char t = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = t;
    }
    sscanf(s,"%d",&rnum);
    return rnum;
}

int getnext(int num)
{
    char s[5];
    sprintf(s,"%d",num);
    int len = strlen(s);
    for(int i=len; i>0; i--)
        for(int j=0; j<i; j++) {
            if( s[j] < s[j-1] ) {
                swap(s[j], s[j-1]);
            }
        }
    sscanf(s,"%d",&num);
    int rnum = reverse(s);
    return rnum-num;
}

bool in_array(int num, int count)
{
    for(int i=0; i<c; i++) {
        if(a[i] == num)
            return true;
    }
    return false;
}

int main()
{
    int num;
    freopen("test.txt","r",stdin);
    scanf("%d", &num);
    printf("%d",num);
    a[0] = num;
    for(int i=0; i<=1000; i++) {
        c ++;
        int rnum = getnext(num);
        if( in_array(rnum,c)) {
            printf("->%d\n",rnum);
            break;
        }
        a[i+1] = rnum;
        printf("->%d",rnum);
        num = rnum;
    }

    return 0;
}
