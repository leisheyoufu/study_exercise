#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;



int isright(int,int);
int main()
{
    int n,i;
    freopen("test.txt","r",stdin);
    while(scanf("%d",&n)!=EOF) {
        for(i=1234; i*n<=98765; i++)
            if(i<=9876&&i*n>=12345&&isright(i,i*n))
                printf("%d/0%d=%d\n",i*n,i,n);
        if(i>=10234&&i*n>=56789&&isright(i,i*n))
            printf("%d/%d=%d\n",i*n,i,n);
    }
    return 0;
}
int isright(int x,int y)
{
    int a[10]= {0};
    for(int i=0; i<5; i++) {
        a[x%10]++;
        x=x/10;
    }
    for(int i=0; i<5; i++) {
        a[y%10]++;
        y=y/10;
    }
    for(int i=0; i<10; i++) {
        if(a[i]!=1) return 0;
    }
    return 1;
}
