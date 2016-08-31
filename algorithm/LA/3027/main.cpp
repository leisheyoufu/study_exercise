#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

#define N 200010
int d[N], p[N];

int findset(int x)
{
    if(x != p[x]) {
        int root = findset(p[x]);
        d[x] += d[p[x]];
        p[x] = root;
        return root;
    } else
        return x;
}



int main()
{
    int T;
    char cmd;
    // freopen("test.txt","r",stdin);
    scanf("%d", &T);
    for(int i=0; i< T; i++) {
        for(int k=0; k<N; k++) {
            p[k] = k;
            d[k] = 0;
        }
        while(scanf("%c", &cmd)) {
            if( cmd =='O') {
                break;
            }
            int u,v;
            if (cmd == 'I') {
                scanf("%d %d", &u, &v);
                p[u] =v;
                d[u] = abs(u-v)%1000;
            } else if(cmd =='E') {
                scanf("%d", &u);
                findset(u);
                printf("%d\n", d[u]);
            }
        }
    }
    return 0;
}
