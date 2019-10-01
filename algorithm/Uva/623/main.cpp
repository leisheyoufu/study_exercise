#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
#define MAXN	3000
int f[1001][MAXN];

void init_factorial(int n)
{
    memset(f,0,sizeof(f));
    f[0][0] =1;
    f[1][0] =1;
    for(int i=2; i<=n; i++) {
        for(int k=0; k<MAXN; k++) {
            f[i][k] += f[i-1][k]*i; // 一定是+=, 因为f[i][k] 可能在k-1的时候赋值
            if(f[i][k]>9) {
                f[i][k+1] = f[i][k]/10;  // 把进位放进k+1, 可能进多余一位，在k+1 循环的时候再处理
                f[i][k] = f[i][k]%10;
            }
        }
    }
}

int main()
{
    int n;
    init_factorial(1000);
    //freopen("test.txt","r",stdin);
    while(scanf("%d",&n) !=EOF) {
        printf("%d!\n",n);
        int flag = 0;
        for(int i=MAXN-1; i>=0; i--) {
            if(!flag&& f[n][i]!=0) {
                flag =1;
            }
            if(flag) {
                printf("%d",f[n][i]);
            }
        }
        printf("\n");
    }

    return 0;
}
