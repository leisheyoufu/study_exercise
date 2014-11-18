#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>


using namespace std;
#define MAXN 1000010

char s[MAXN];
int f[MAXN];

void next_fail(int n)
{
    f[0] =0;
    f[1]=0;

    for(int i=1; i<n; i++) {
        int j = f[i];
        while( j && s[i] != s[j] ) {
            j = f[j];
        }
        f[i+1] = s[i] == s[j]? j+1:0;
    }
}



int main()
{
    int n,k=0;
    //freopen("test.txt","r",stdin);
    while( scanf("%d",&n) == 1 &&n) {
        scanf("%s",s);
        next_fail(n);
        printf("Test case #%d\n",++k);
        for( int i=2; i<=n; i++) {
            if( f[i]> 0 && i%(i-f[i]) ==0 ) {
                printf("%d %d\n", i, i/(i-f[i]));
            }
        }
        printf("\n");
    }
	
    return 0;
}
