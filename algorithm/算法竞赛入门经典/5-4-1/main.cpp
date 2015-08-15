#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;


int get_index(int number, int &index)
{
    int index_sum=0;
    for(int i=1; i<number; i++) {
        index_sum+=i;
        if(index_sum>=number) {
            index = i;
            return index_sum;
        }
    }
    return index_sum;
}


int main()
{
    int number,index, index_sum;
    freopen("test.txt","r",stdin);
    while( scanf("%d", &number) != EOF) {
        index_sum= get_index(number, index);
        int a = index_sum - number +1;     // 均从右往左数分母
        int b = index - (index_sum - number );  // 均从右往左数分子
        if( index %2 ==0)
            printf("%d/%d\n", b,a);
        else
            printf("%d/%d\n", a,b);
    }
    return 0;
}
