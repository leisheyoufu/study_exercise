#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <conio.h>
using namespace std;

struct ant {
    int id;
    int p;
    int d;
};

struct ant before[10005], after[10005];
int order[10005];

int L,T,n;
bool compare (struct ant a1, struct ant a2)
{
    if (a1.p< a2.p)
        return true;
    return false;
}

void run()
{
    sort(before, before+n, compare);
    for(int i=0; i<n; i++) {
        order[before[i].id] = i;
        after[i].d = before[i].d;
        after[i].p = before[i].p + before[i].d * T;
        if(after[i].p < 0 || after[i].p > L) {
            after[i].d = -2;
        }
    }
    sort(after,after+n,compare);
    for(int i=1; i<n; i++) {
        if(after[i].p == after[i-1].p ) {
            after[i].d = after[i-1].d;
            if(after[i].d != -2) {
                after[i].d = after[i-1].d = 0;
            }
        }
    }
}

int main()
{
    int N;
    freopen("test.txt","r",stdin);
    scanf("%d", &N);
    for(int i=0; i<N; i++) {
        scanf("%d %d %d", &L, &T, &n);
        for(int j=0; j<n; j++) {
            int p;
            char c;
            scanf("%d %c", &p,&c);
            before[j].id = j;
            before[j].p = p;
            if(c=='L') {
                before[j].d = -1;
            } else if(c=='R') {
                before[j].d = 1;
            }
        }
        run();
        printf("Case #%d:\n", i+1);
        for(int t=0; t<n; t++) {
            if(after[order[t]].d == -2) {
                printf("Fell off\n");
            } else if(after[order[t]].d ==0) {
                printf("%d %s\n",after[order[t]].p, "Turning");
            } else if(after[order[t]].d == -1) {
                printf("%d %s\n",after[order[t]].p, "L");
            } else if(after[order[t]].d == 1) {
                printf("%d %s\n",after[order[t]].p, "R");
            }
        }
        printf("\n");
    }
    getch();
    return 0;
}
