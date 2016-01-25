#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
#include <queue>
using namespace std;

const int INF = 1<<30;
struct node {
    int k;
    int x;
    int y;
};

struct node a[100];
struct node o;
int cmp(struct node n1, struct node n2)
{
    int x1,y1,x2,y2;
    double k1,k2;
    y1 = n1.y - o.y;
    y2 = n2.y - o.y;
    x1 = n1.x - o.x;
    x2 = n2.x- o.x;
    if (x1==0) {
        k1 = INF;
    } else {
        k1 = 1.0*y1/x1;
    }
    if(x2==0) {
        k2=INF;
    } else {
        k2 = 1.0*y2/x2;
    }
    if( k1*k2<0)
        return k1>k2;
    else
        return k1<k2;
}


void dfs(int s, int e)
{
    int n = e-s;
    if(n==2) {
        printf("%s(%d,%d) match %s(%d,%d)\n", a[s].k==0?"¾ÞÈË":"¹í", a[s].x, a[s].y,
               a[s+1].k==0?"¾ÞÈË":"¹í", a[s+1].x, a[s+1].y);
        return;
    }
    int m=s;
    for(int i=s+1; i<e; i++) {
        if((a[i].y < a[m].y) || ( a[i].y == a[m].y && a[i].x < a[m].x)) {
            m = i;
        }
    }
    swap(a[m], a[e-1]);
    o = a[e-1];
    sort(a+s,a+e-1,cmp);
    if( o.k != a[s].k) {
        swap(a[s],a[e-2]);
        dfs(e-2,e);
        dfs(s,e-2);
    } else {
        int c[2]= {0};

        for(int i= s; i<e; i++) {
            c[a[i].k]++;
            if(c[0] == c[1])
                break;
        }
        dfs(s,s+c[0]*2);
        dfs(s+c[0]*2,e);
    }
}

int main()
{
    int T,n;
    freopen("test.txt","r",stdin);
    scanf("%d", &T);
    for(int i=0; i<T; i++) {
        scanf("%d",&n);
        for(int j=0; j<n; j++) {
            scanf("%d",&a[j].k);
            scanf("%d",&a[j].x);
            scanf("%d",&a[j].y);
        }
        printf("Case %d:\n", T);
        dfs(0,n);
        printf("\n");
    }
    return 0;
}
