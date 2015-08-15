#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

int ans[1000]= {1,0};


void f(int n)
{
    int c=0, temp,a;
    for(int t=1; t<=n; t++) {
        for(int i=0; i<1000; i++) {
            temp = t * ans[i] +c;
            c = temp/10;
            ans[i]= temp %10;
        }
    }
    int ok =0;
    for(int i=999; i>=0; i--) {

        if(ans[i] >0) {
            ok =1;
        }
        if(ok)
            printf("%d", ans[i]);
    }
}

int main()
{
    int n;
    freopen("test.txt","r",stdin);
    scanf("%d", &n);
    f(n);
    return 0;
}
