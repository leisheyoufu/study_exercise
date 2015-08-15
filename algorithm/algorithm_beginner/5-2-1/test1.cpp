#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

char num1[10],num2[10];


int add_time()
{
    int l1,l2,c,t=0,a,b;
    l1 = strlen(num1);
    l2 = strlen(num2);
    c = 0;
    int i=0;


    while(l1>=0 && l2 >=0) {
        a = num1[l1]-'0', b=num2[l2]-'0';
        if( a+b+c >9) {
            c=1;
            t++;
        } else {
            c =0;
        }
        l1--, l2--;
    }
    if(c>0 &&l2>=0) {
        if( num2[l2]-'0'+c >9)
            t++;
    } else if(c>0 &&l1>=0) {
        if( num1[l2]-'0' +c >9)
            t++;
    }
    return t;
}

int main()
{
    freopen("test.txt","r",stdin);
    while( scanf("%s %s",num1,num2) && strcmp(num1,"0") && strcmp(num2,"0")) {
        printf("%d\n",add_time());
    }

    return 0;
}
