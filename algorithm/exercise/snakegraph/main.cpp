#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;


void draw(int n)
{
    int **a;
    a = (int**)malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++) {
        a[i] = (int*)malloc(sizeof(int)*n);
        memset(a[i], 0, sizeof(int)*n);
    }

    //memset(a,0,sizeof(n*n));
    int i =1;
    int r=0, c=n-1;
    //a[r][c] = 1;
    while(i <= n*n) {
        // down
        while(r<=n-1 && a[r][c] == 0) {
            a[r++][c] = i++;
        }
        r-=1;
        c-=1;
        // left
        while(c>=0 && a[r][c] == 0) {
            a[r][c--] = i++;
        }
        // up
        c+=1;
        r-=1;
        while(r>=0 && a[r][c] == 0) {
            a[r--][c] = i++;
        }
        r+=1;
        c+=1;
        //right
        while(c<=n-1 && a[r][c] == 0) {
            a[r][c++] = i++;
        }
        c-=1;
        r+=1;
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    draw(5);
    getch();
    return 0;
}
