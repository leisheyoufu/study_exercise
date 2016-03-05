#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

long long A[1000003], C[1000003];
int N;
long long M;

long long get_min()
{
    C[0]  = 0;
    for(int i=1; i<N; i++) {
        C[i] = C[i-1] + A[i] -M;
    }
    sort(C,C+N);
    long long x = C[N/2];
    long long ans = 0;
    for(int i=0; i<N; i++) {
        ans += abs(x-C[i]);
    }
    return ans;
}

int main()
{
    //freopen("test.txt","r",stdin);
    int T =1;
    while( scanf("%d",&N) != EOF) {
        long long sum = 0;
        for(int i=1; i<=N; i++) {
            scanf("%lld",&A[i]);
            sum+= A[i];
        }
        M = sum / N;
        long long ans = get_min();
        printf("%lld\n", ans);
    }

    return 0;
}
