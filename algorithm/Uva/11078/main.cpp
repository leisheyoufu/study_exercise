#include<cstdio>
#include<algorithm>

using namespace std;

int A[100000];

int get_max(int N)
{
    int maxa = A[0];
    int ans = A[0] - A[1];
    for(int i=1; i<N; i++) {
        ans = max(ans, maxa - A[i]);
        maxa = max(A[i], maxa);
    }
    return ans;
}
int main()
{
    freopen("test.txt","r",stdin);
    int T,N;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        for(int i=0; i<N; i++) {
            scanf("%d", &A[i]);
        }
        printf("%d\n", get_max(N));
    }

    return 0;
}
