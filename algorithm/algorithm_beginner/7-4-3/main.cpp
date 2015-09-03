#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;



int N,L;
int a[80];

void print()
{
    for(int i=0; i<N; i++) {
        printf("%c", a[i]+'A');
    }
    printf("\n");
}

void backtrack(int cur)
{
    if(cur+1 == N) {
        print();
    }
    for(int i=0; i<L; i++) {
        a[cur] = i;

        int ok=1, equal = 1;
        for(int j=1; 2*j<=cur+1; j++) {
            equal = 1;
            for(int k=0; k<j; k++) {
                if( a[cur-k] != a[cur-k-j]) {
                    equal = 0;
                    break;
                }
            }
            if(equal) {
                ok = 0;
                break;
            }
        }
        if(ok) {
            backtrack(cur+1);
        }
    }
}


int main()
{
    int n,i;
    freopen("test.txt","r",stdin);
    while( scanf("%d %d",&N,&L) !=EOF) {
        backtrack(0);
    }

    return 0;
}
