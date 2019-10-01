#include<stdio.h>
//#include<conio.h>
#include<algorithm>

using namespace std;

#define MAX_WEEK 10005

int N,S;
int C[MAX_WEEK], Y[MAX_WEEK];
long long output = 0;
void init_c()
{
    for(int i=2; i<=N; i++) {
        C[i] = min(C[i-1]+S,C[i]);
    }
}

void cal_cost()
{

    for(int i=1; i<=N; i++) {
        output+=C[i]*Y[i];
    }

}

int main()
{
    //freopen("test.txt","r",stdin);

    scanf("%d %d\n",&N,&S);

    for(int i=1; i<=N; i++) {
        scanf("%d %d",&C[i],&Y[i]);
    }
    init_c();
    cal_cost();
    printf("%lld\n",output);


    //getch();
    return 0;
}