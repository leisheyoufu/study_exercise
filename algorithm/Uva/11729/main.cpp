#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
//#include <conio.h>
using namespace std;

struct task {
    int B;
    int J;
};

struct task job[10001];

int N;

bool compare (struct task j1, struct task j2)
{
    if (j1.J > j2.J)
        return true;
    return false;
}
int command(int N, struct task *job)
{
    int t = 0, temp, prev=0;
    sort(job, job+N, compare);

    for(int i=0; i<N; i++) {
        temp = job[i].B+job[i].J + prev;
        if(temp > t) {
            t = temp;
        }
        prev +=job[i].B;
    }
    return t;
}

int main()
{
    //freopen("test.txt","r",stdin);
    int T =1;
    while( scanf("%d",&N) && N!=0) {
        for(int i=0; i<N; i++) {
            scanf("%d %d",&job[i].B,&job[i].J);

        }
        int time = command(N,job);
        printf("Case %d: %d\n", T++, time);
    }
    // getch();
    return 0;
}
