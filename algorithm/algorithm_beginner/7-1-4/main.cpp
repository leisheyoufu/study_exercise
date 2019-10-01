#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

int isright(int a)
{
    int f=0;
    for(int num=2; num<=10; num++) {
        char str[29];
        itoa(a,str,num);
        int cont=strlen(str);
        for(int i=0; i<cont/2; i++) {
            if(str[i]!=str[cont-i-1]) {
                f--;
                break;
            }
        }
        f++;
    }
    if(f>=2)
        return 1;
    else
        return 0;
}

int main()
{
    int n,i;
    freopen("test.txt","r",stdin);
    int num;
    while(scanf("%d", &num) != EOF) {
        for(int i=num;; i++) {
            if(isright(i)) {
                printf("%d\n",i);
                break;
            }
        }
    }
    return 0;
}
