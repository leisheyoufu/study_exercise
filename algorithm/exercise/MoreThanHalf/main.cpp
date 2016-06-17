#include<cstdio>
#include<cstdlib>
#include<string>

using namespace std;

int get_most(int a[], int size)
{
    int *b = (int*)malloc(sizeof(int)*size);
    memset(b,0,size*sizeof(int));
    int first, second, count = size;
    bool first_set = false, second_set = false;
    while(count > 1) {
        first_set =false;
        second_set =false;
        for(int i=0; i<size; i++) {
            if(b[i] == 0) {
                if(!first_set) {
                    first = a[i];
                    first_set = true;
                    b[i] = 1;
                    continue;
                } else if( a[i] != first) {
                    second = a[i];
                    second_set = true;
                    b[i] = 1;
                    count -=2;
                    break;
                }
            }
        }
    }
    int result;
    for(int i=0; i<size; i++) {
        if(b[i] == 0) {
            result = a[i];
        }
    }
    free(b);
    return result;
}
int main()
{
    int a[] = {545,578,900,578,578};
    int result = get_most(a, sizeof(a)/sizeof(int));
    printf("%d\n", result);
    return 0;
}
