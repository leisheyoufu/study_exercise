#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN	3000
int f[MAXN];

int main()
{
    int n;
    //freopen("test.txt","r",stdin);
    while(scanf("%d",&n) !=EOF) {
        printf("%d!\n",n);
        memset(f,0,sizeof(f));
        f[0]=1;
        for(int i=2; i<=n; i++) {
            int c=0,flag=1;
            for(int k=0; k<MAXN; k++) {
                int t = (f[k])*i+c;
                if(f[k] == 0) {
                    flag=0;
                }
                f[k] = t%10;
                c = t/10;
            }
        }
        int flag = 0;
        for(int i=MAXN-1; i>=0; i--) {
            if(!flag&& f[i]!=0) {
                flag =1;
            }
            if(flag) {
                printf("%d",f[i]);
            }
        }
        printf("\n");
    }
    return 0;
}
