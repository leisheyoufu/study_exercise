#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

#define SIZE 2000000
#define HEIGHT 21
struct node {
    int state;
};
struct node binary_tree[SIZE];

void init()
{
    memset(binary_tree,0,sizeof(binary_tree));
}

int fall(int h)
{
    int pos = 1;
    for(int i=1; i<h; i++) {
        if(binary_tree[pos].state ==0) {
            binary_tree[pos].state =1;
            pos = 2*pos;
        } else if(binary_tree[pos].state ==1) {
            binary_tree[pos].state =0;
            pos =2*pos+1;
        }
    }
    return pos;
}

int main()
{
    int D, I;
    freopen("test.txt","r",stdin);
    while(scanf("%d %d\n",&D,&I) !=EOF) {
        init();
        int r;
        for(int i=0; i<I; i++) {
            r = fall(D);
        }
        printf("%d\n",r);
    }
    return 0;
}

