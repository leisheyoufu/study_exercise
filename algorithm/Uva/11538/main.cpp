#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int main()
{
    unsigned long long m,n;
    //freopen("test.txt","r",stdin);
    while( scanf("%lld%lld",&m,&n) && n && m) {
        if(n>m) {
            swap(n,m);  //n 行数， m 列数
        }
        long long ans = m*(m-1)*n + n*(n-1)*m +2*n*(n-1)*(3*m-n-1)/3;  // 行 ， 列 ， 对角线全排列
        printf("%lld\n",ans);
    }
    return 0;
}
