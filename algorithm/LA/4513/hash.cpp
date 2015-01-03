#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXN 40010
const int x = 127;

int m,n,pos;
char str[MAXN];
unsigned long long h[MAXN],xp[MAXN],Hash[MAXN];
int Rank[MAXN];

int cmp(const int &a,const int &b)
{
    return Hash[a]<Hash[b] || (Hash[a] ==Hash[b] && a<b);
}

int possible (int L)
{
    int c = 0;
    pos= -1;

    for(int i=0; i<n-L+1; i++) { //  从i 开始长为L 的字符串
        Rank[i] = i;
        Hash[i] = h[i]-h[i+L]*xp[L];  // 乘以hash 位的幂， 减去后就是右边剩下的hash 项
    }
    sort(Rank,Rank+n-L+1,cmp);  // 对Rank 按hash 进行排序, 值相近的就是共同后缀字符相同多的
    for(int i=0; i<n-L+1; i++) {
        if(i==0 ||Hash[Rank[i]] != Hash[Rank[i-1]]) {
            c = 0;
        }
        if(++c >=m) {
            pos = max(pos,Rank[i]);
        }
    }
    return pos >=0;
}

int main()
{
    int i;
    //freopen("test.txt","r",stdin);
    while( scanf("%d",&m) && m) {
        scanf("%s",str);
        n = strlen(str);
        h[n]=0;
        for( i=n-1; i>=0; i--) {
            h[i] = h[i+1]*x+str[i]-'a';   // h[] 前缀和
        }
        xp[0]=1;
        for(int i=1; i<=n; i++) {
            xp[i] = xp[i-1]*x;
        }
        if(!possible(1)) {
            printf("none\n");
        } else {
            int L=1,R=n+1;
            while(R-L >1) {
                int M=(L+R)/2;
                if(possible(M)) {
                    L=M;
                } else {
                    R=M;
                }
            }
            possible(L);
            printf("%d %d\n",L,pos);
        }
    }

    return 0;
}
