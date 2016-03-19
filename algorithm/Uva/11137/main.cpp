#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int a[22];
long long d[10005];

void init()
{
    for(int i=1; i<=21; i++) {
        a[i] = i*i*i;
    }
}

long long dp(int N)
{
    memset(d,0,sizeof(d));
    d[0] = 1;
    for(int i=1; i<=21; i++) {
        for(int j=a[i]; j<= N; j++) {
            d[j] += d[j - a[i]];
        }
    }
    return d[N];
}

int main()
{
    init();
    //freopen("test.txt","r",stdin);
    int N;
    while(scanf("%d", &N) != EOF) {
        printf("%lld\n",dp(N));
    }
    return 0;
}
