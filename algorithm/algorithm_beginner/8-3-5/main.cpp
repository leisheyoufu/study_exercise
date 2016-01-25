#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
#include <queue>
using namespace std;

int a[100];
int max_num;
int sum(int n)
{
    int sum = 0;
    for(int i=0; i<n; i++) {
        sum +=a[i];
    }
    return sum;
}

bool split(int max_num,int n, int m)
{
    int num =0;
    int t=0;
    for(int i=0; i<n; i++) {
        if(num + a[i] > max_num) {
            num=a[i];
            if( num > max_num)
                return false;
            t++;
            if (t>m) {
                return false;
            }
        }
    }
    return true;
}



int binary_part(int n, int m)
{
    int right,left,mid;
    right = sum(n);
    left =0;
    while(left<right) {
        mid = (left+right)/2;
        if( !split(mid,n,m)) {
            left = mid+1;
        } else {
            right = mid;
        }
    }
    return mid;
}



int main()
{
    int m,n;
    freopen("test.txt","r",stdin);
    scanf("%d", &n,&m);
    for(int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    int part_num = binary_part(n,m);
    printf("%d\n", part_num);

    return 0;
}
