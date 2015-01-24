#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define MAXN	20001
int dragon[MAXN], knight[MAXN];

int main()
{
    int n,m;   // n¡˙£¨ m ∆Ô ø
    //freopen("test.txt","r",stdin);
    while(scanf("%d%d",&n,&m) && n!=0 && m!=0) {
        for(int i=0; i<n; i++) {
            scanf("%d",&dragon[i]);
        }
        for(int i=0; i<m; i++) {
            scanf("%d",&knight[i]);
        }
        sort(dragon,dragon+n);
        sort(knight,knight+m);
        int cur=0,s,cost=0;
        for(s=0; s<m; s++) {
            if(knight[s] >=dragon[cur]) {
                cost+=knight[s];
                cur++;
            }
            if(cur>=n)
                break;
        }
        if(cur <n) {
            printf("Loowater is doomed!\n");
        } else {
            printf("%d\n",cost);
        }
    }

    return 0;
}
