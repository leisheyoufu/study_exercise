#include <stdio.h>
//#include <conio.h>

int t,M,N;
int K;
void backtrack(int M,int N,int last)
{
    if(N== 1) {
        if(M<=last) {
            K++;
        }
        return ;
    }

    for(int i=M; i>=M/N; i--) {
        if(i<=last) {
            backtrack(M-i,N-1,i);
        }
    }
}



int main()
{
//	freopen("test.txt","r+",stdin);
    scanf("%d",&t);

    for(int i=0; i<t; i++) {
        scanf("%d %d\n",&M,&N);
        K=0;
        backtrack(M,N,M);
        printf("%d\n",K);

    }

//	getch();
    return 0;
}