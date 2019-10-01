#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

#define SIZE 50005

int a[SIZE];

int find(int num)
{
    for(int i=0; i<num; i++) {
        if(a[i]== num)
            return i;
    }
    return -1;
}

// x ÒÆµ½ y×ó±ß
void left_shift(int x, int y, int n)
{
    int n1 = find(x);
    int n2 = find(y);
    if(n1>n2) {
        for(int i=n1; i<n; i++) {
            swap(a[i],a[i+1]);
        }
        swap(a[n-1],a[0]);
        for(int i=0; i<n2-1; i++) {
            swap(a[i],a[i+1]);
        }
    } else {
        for(int i=n1; i<n2-1; i++) {
            swap(a[i],a[i+1]);
        }
    }
}

void right_shift(int x,int y, int n)
{
    int n1 = find(x);
    int n2 = find(y);
    if(n1<n2) {
        for(int i=n1; i<n2; i++) {
            swap(a[i],a[i+1]);
        }
    } else {
        for(int i=n1; i>n2+1; i--) {
            swap(a[i],a[i-1]);
        }
    }
}

int main()
{
    int num;
    char type;
    int x,y;
    freopen("test.txt","r",stdin);
    int n,m;
    scanf("%d %d\n", &n,&m);
    for(int i=0; i< n; i++) {
        a[i] = i+1;
    }
    for(int i=0; i<m; i++) {
        scanf("%c %d %d\n",  &type,&x, &y);
        if( type =='A') {
            left_shift(x,y,n);
        }
        if( type =='B') {
            right_shift(x,y,n);
        }

    }
    for(int i=0; i<n; i++) {
        printf("%d ",a[i]);
    }
}
