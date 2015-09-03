#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

int is_prime(int num)
{
    for(int i=2; i*i<=num; i++) {
        if(num %i == 0)
            return false;
    }
    return true;
}

int a[18];
int vis[18];
int num;

void print(int num)
{
    for(int i=1; i<=num; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void backtrack(int cur)
{
    if(cur == num+1) {
        if( a[1] == 1)
            print(num);
        return;
    }
    for(int i=1; i<=num; i++) {
        if( !vis[i]) {
            if( (cur == num && is_prime(i+a[1])) || (cur > 1 && is_prime(i+a[cur-1])) || cur == 1) {
                a[cur] = i;
                vis[i] = 1;
                backtrack(cur+1);
                vis[i] = 0;
            }
        }
    }
}


int main()
{
    int n,i;
    freopen("test.txt","r",stdin);

    scanf("%d",&num);
    backtrack(1);
    return 0;
}
