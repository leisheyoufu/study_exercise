#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>


#define MIN(A,B) ((A)>(B)?(B):(A))
#define MAX(A,B) ((A)<(B)?(B):(A))

int Gcd(int a,int b);
void calculate(int index);

int n=100;
int m=6;
int p = n-m;

int N[100];
int M[100];
int P[100];
int C[1000];
int A[1000];
int B[1000];
int index =0;

int main()
{


    for(int i=0; i<1000; i++) {
        C[i] =1;
    }
    while ( scanf("%d%d",&n,&m)!=EOF) {
        if(n==0 && m==0) {
            break;
        }
        p = n-m;
        A[index]=n;
        B[index]=m;
        calculate(index++);
    }

    for(int i=0; i<index; i++) {
        printf("%d things taken %d at a time is %d exactly.\n",A[i],B[i],C[i]);

    }









//	getch();
    return 0;
}
void calculate(int index)
{
    for(int i=1; i<=n; i++) {
        N[i-1] = i;
    }
    for(int i=1; i<=m; i++) {
        M[i-1] = i;
    }
    for(int i=1; i<=p; i++) {
        P[i-1] = i;
    }

    for( int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            int temp = Gcd(N[i],M[j]);
            N[i]/=temp;
            M[j]/=temp;
        }
    }

    for( int i=0; i<n; i++) {
        for(int j=0; j<p; j++) {
            int temp = Gcd(N[i],P[j]);

            N[i]/=temp;
            P[j]/=temp;

        }
    }

    for(int i=0; i<n; i++) {
        C[index]*=N[i];
    }

    for(int i=0; i<m; i++) {
        C[index]/=N[i];
    }

    for(int i=0; i<p; i++) {
        C[index]/=P[i];
    }

}
int Gcd(int a,int b)
{
    int max = MAX(a,b);
    int min = MIN(a,b);
    while(max %min !=0) {
        int temp = min;
        min=max%min;
        max = temp;
    }
    return min;
}