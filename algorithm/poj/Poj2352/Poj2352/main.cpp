
#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
int n;

int C[32002];

int lowbit(int x)
{
    return x&(-x);
}

int sum(int x)
{
    int ret =0;
    while(x>0) {
        ret+=C[x];
        x-=lowbit(x);
    }
    return ret;
}

void add(int x,int d)
{
    while(x<=32001) {
        C[x]+=d;
        x+=lowbit(x);
    }
}

int main()
{
//	freopen("test.txt","r+",stdin);
    scanf("%d",&n);
    int *level = (int *)malloc(n*sizeof(int));
    for(int i=0; i<n; i++) {
        level[i]=0;
    }

    for(int i=0; i<n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        level[sum(x+1)]++;
        add((x+1),1);
    }

    for(int i=0; i<n; i++) {
        printf("%d\n",level[i]);
    }
    free(level);
    //getch();
    return 0;
}

