#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
#include <queue>
using namespace std;

int a[100][100];

void make_match(int k)
{
    int t,i,j;
    for(t=1; t<k; t*=2) {
        for( i=0; i<t; i++) {
            for(int b=0; b<k/2; b+=t) {
                for(j=0; j<2*t; j++) {

                    a[t+i][j+2*b] = a[2*t-t-i-1][2*(t+b)-j-1];
                }
            }
        }
    }
}



int main()
{
    int n,i;
    freopen("test.txt","r",stdin);
    int k;
    scanf("%d", &k);

    for(int i=0; i<k; i++) {
        a[0][i] = i+1;
    }
    make_match(k);
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}
