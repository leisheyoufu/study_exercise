#include <stdio.h>
#include <algorithm>
//#include <conio.h>
#include <string.h>

using namespace std;

#define SIZE 50005

int T,N;
int a[SIZE],b[SIZE], num[SIZE];


int get_min1(int k)
{
    int max = -10000;
    for(int i=1; i<=k; i++) {
        if(num[i]>max) {
            max = num[i];
        }
    }
    return max;
}
int get_min2(int k)
{
    int max = -10000;
    for(int i=k; i<=N; i++) {
        if(num[i]>max) {
            max = num[i];
        }
    }
    return max;
}

int dp()
{
    int max = num[1];
    int maxi =0;
    for(int k=1; k<N; k++) {
        maxi+=num[k];
        if(maxi>max) {
            max = maxi;
        }
        if(maxi <0) {
            maxi=0;
        }
        a[k] = max;
        /*
        if(a[k] == 0 )
        {
        	a[k] = get_min1(k);
        }
        */
    }

    max=num[N];
    maxi=0;

    for(int k=N; k>1; k--) {
        maxi+=num[k];
        if(maxi>max) {
            max = maxi;
        }
        if(maxi <0) {
            maxi=0;
        }
        b[k] = max;
        /*
        if(b[k] == 0)
        {
        	b[k] = get_min2(k);
        }
        */
    }
    int mark2 = max;
    max=0;
    maxi=0;
    for(int k=1; k<N; k++) {
        int c;
        c=a[k] + b[k+1];
        if(c>max) {
            max = c;
        }
    }
    return max;
}

int main()
{
    //freopen("test.txt","r",stdin);
    scanf("%d",&T);

    for(int i=0; i<T; i++) {
        scanf("%d",&N);
        for(int j=1; j<=N; j++) {
            scanf("%d",&num[j]);
        }
        int c = dp();
        printf("%d\n",c);
    }

    //getch();
    return 0;
}