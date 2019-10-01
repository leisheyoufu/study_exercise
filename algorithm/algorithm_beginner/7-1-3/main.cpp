#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

void print_x(int num)
{
    float x;
    for(int y=1; y<=2*num; y++) {
        x = (float)num *y/(y-num);
        int t=x;
        if(t==x &&t>0) {
            printf("1/%d=1/%d+1/%d\n",num,y,t);
        }
    }
}
int main()
{
    int n,i;
    freopen("test.txt","r",stdin);
    int num;
    while(scanf("%d", &num) != EOF) {
        printf("%d\n",num);
        print_x(num);
    }

    return 0;
}
