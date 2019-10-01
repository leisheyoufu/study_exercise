#include <stdio.h>
#include <vector>
//#include <conio.h>
#include <algorithm>

using namespace std;
#define INF 999999
#define MIN -1
#define PMAX_NUM 311
int v[PMAX_NUM];   // 所有点坐标
int V,P;

int dis[PMAX_NUM][PMAX_NUM];
int dp[PMAX_NUM][35];

void init_dis()
{
    for(int i=1; i<V; i++) {
        for(int j=i+1; j<=V; j++) {
            dis[i][j] = dis[i][j-1]+v[j] - v[(i+j)/2];  // i到j 点到中点的距离和
        }
    }
    for(int i = 1; i <= V; ++i) {
        dp[i][i] = 0; // 邮局和村庄数相等
        dp[i][1] = dis[1][i]; // 只1个邮局
    }
}
int main()
{
    //freopen("test.txt","r+",stdin);

    scanf("%d %d",&V,&P);
    for(int i=1; i<=V; i++) {
        scanf("%d",&v[i]);
    }
    init_dis();
    for(int j=2; j<=P; j++) {
        for(int i=j+1; i<=V; i++) { // j=1代表有两个邮局
            dp[i][j] = INF;
            for(int k=j-1; k<i; k++) {
                dp[i][j] = min(dp[i][j],dp[k][j-1]+dis[k+1][i]);
            }
        }
    }

    printf("%d\n",dp[V][P]);

    //getch();
    return 0;

}