#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>

#define AYYAY_SIZE 105

int N;
int a[AYYAY_SIZE][AYYAY_SIZE];
int column[AYYAY_SIZE];

int get_max()
{
    int max = 0;
    int result = column[0];
    for(int i=1; i<N; i++) {
        if(result< 0) {
            result = column[i];
        } else {
            result+=column[i];
        }
        if( result > max) {
            max = result;
        }
    }
    return max;
}


int main()
{
    int max = 0;
//	freopen("test.txt","r+",stdin);
    scanf("%d",&N);

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            scanf("%d",&a[i][j]);
        }
    }

    for(int i=0; i<N; i++) { //  i 起始行
        memset(column,0,sizeof(column));
        for(int j=i; j<N; j++) { // j 结束行
            for(int k=0; k<N; k++) { //  列
                column[k]+= a[j][k];
            }
            int temp = get_max();
            if( max < temp) {
                max = temp;
            }
        }
    }
    printf("%d\n",max);
//	getch();
    return 0;
}