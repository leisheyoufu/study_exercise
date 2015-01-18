#include<iostream>
#include<cstdio>
#include<cstring>
#include <algorithm>

using namespace std;

#define MAXN	300
#define MOD	1000000000

char str[MAXN+1];
int d[MAXN][MAXN];

int dp(int l, int r)
{
    if(l==r) {
        return 1;
    }
    if(str[l] != str[r]) {
        return 0;
    }
    int &ans = d[l][r];
    if(ans >=0)
        return ans;
    ans = 0;
    for(int k=l+2; k<=r; k++) {
        if(str[l] == str[k]) {
            ans = (ans+(long long)dp(l+1,k-1)*(long long)dp(k,r)) % MOD;
        }
    }
    return ans;
}

int main()
{
    //freopen("test.txt","r",stdin);
    while(scanf("%s",str) == 1) {
        memset(d,-1,sizeof(d));
        printf("%d\n",dp(0,strlen(str)-1));
    }

    return 0;
}
