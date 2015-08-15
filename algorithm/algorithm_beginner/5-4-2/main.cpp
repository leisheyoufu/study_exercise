#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int prim[100];

int init_prim(int num)
{
    int j=0;
    for(int i=2; i<=num; i++) {
        if(is_prime(i) ) {
            prim[j++] = i;
        }
    }
    return j;
}

int count_array[100];

int main()
{
    int number,index, index_sum;
    freopen("test.txt","r",stdin);
    while( scanf("%d", &number) != EOF) {
        int prime_count = init_prim(number);
        memset(count_array,0,sizeof(count_array));
        for(int i=2; i<=number; i++) {
            int num = i;
            for(int j =0; j<prime_count; j++) {
                while(num>= prim[j] && num % prim[j] == 0) {
                    num /= prim[j];
                    count_array[j]++;
                }
            }
        }
        for(int i=0; i<prime_count; i++) {
            printf("%d ",count_array[i]);
        }
        printf("\n");
    }
    return 0;
}
