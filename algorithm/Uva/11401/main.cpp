#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

unsigned long long f[1000005];
int main()
{
    unsigned long long n;
    f[3] = 0;
    for(long long i=4; i<=1000000; i++) {
        // x-y<z<x
        f[i]=f[i-1] + ((i-1)*(i-2)/2-(i-1)/2)/2;
    }
    //freopen("test.txt","r",stdin);
    while( scanf("%lld",&n) && n >=3 ) {
        printf("%lld\n",f[n]);
    }

    return 0;
}
