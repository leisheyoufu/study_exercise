#include <cstdio>
//#include <conio.h>

using namespace std;
#define NUM_MAX 10005
#define MAX(a,b) ((a)>(b)?(a):(b))
int M,N,K;

double data[NUM_MAX];

double B[NUM_MAX];

void cal()
{
    B[0] = 0;
    for(int i=1; i<=K; i++) {
        B[i]=B[i-1]+data[i-1];
    }
}

void advice()
{
    cal();
    int max = MAX(M,N);
    float pm,pn,pm_1,pn_1;
    for(int i=N; i<=K; i++) {
        pm = (B[i]-B[i-M])*N;
        pn = (B[i]-B[i-N])*M;
        if( i!=N) {
            pm_1 = (B[i-1]-B[i-M-1])*N;
            pn_1 = (B[i-1] - B[i-N-1])*M;
        }
        if(pm>pn && ( i == N ||pm_1<pn_1)) {
            printf("BUY ON DAY %d\n",i);
        } else if(pm<pn && (i == N ||pm_1>pn_1 )) {
            printf("SELL ON DAY %d\n",i);
        }
    }
}


int main()
{
    //freopen("test.txt","r+",stdin);
    scanf("%d %d %d",&M,&N,&K);

    for(int i=0; i<K; i++) {
        scanf("%lf",&data[i]);
    }

    advice();

//	getch();
    return 0;
}