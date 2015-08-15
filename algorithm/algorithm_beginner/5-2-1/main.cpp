#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;
int main()
{
    freopen("test.txt","r",stdin);
    int a=0, b=0;
    while (scanf("%d %d",&a,&b) ==2) {
        if ( a == 0 && b==0)
            return 0;
        int c=0, ans =0;
        for(int i=9; i>=0; i--) {
            c = a%10+b%10+c >9 ?1:0;
            ans +=c;
            a/=10, b/=10;
        }
        printf("%d",ans);
    }
    return 0;
}
