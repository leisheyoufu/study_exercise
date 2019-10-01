#include<stdio.h>
#include<algorithm>

#define MAXN 100001

int p[MAXN];

int findset(int a)
{
    return a!=p[a]? findset(p[a]):a;
}

int main()
{
    int a,b;
//#freopen("test.txt","r",stdin);
    while( scanf("%d",&a) ==1 ) {
        int refuse_count=0;
        if( a != -1) {
            for( int i=0; i<MAXN; i++) {
                p[i] = i;
            }
        }
        while( a != -1 ) {
            scanf("%d",&b);
            a = findset(a);
            b= findset(b);
            if(a == b) {
                refuse_count++;
            } else {
                p[a] = b;
            }
            scanf("%d",&a);
        }
        printf("%d\n",refuse_count);

    }
    return 0;
}
