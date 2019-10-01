#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;
#define MAXN	3000
int f[1001][MAXN];

void init_factorial(int n)
{
    memset(f,0,sizeof(f));
    f[0][0] =1;
    f[1][0] =1;
    for(int i=2; i<=n; i++) {
        for(int k=0; k<MAXN; k++) {
            f[i][k] += f[i-1][k]*i; // һ����+=, ��Ϊf[i][k] ������k-1��ʱ��ֵ
            if(f[i][k]>9) {
                f[i][k+1] = f[i][k]/10;  // �ѽ�λ�Ž�k+1, ���ܽ�����һλ����k+1 ѭ����ʱ���ٴ���
                f[i][k] = f[i][k]%10;
            }
        }
    }
}

int main()
{
    int n;
    init_factorial(1000);
    //freopen("test.txt","r",stdin);
    while(scanf("%d",&n) !=EOF) {
        printf("%d!\n",n);
        int flag = 0;
        for(int i=MAXN-1; i>=0; i--) {
            if(!flag&& f[n][i]!=0) {
                flag =1;
            }
            if(flag) {
                printf("%d",f[n][i]);
            }
        }
        printf("\n");
    }

    return 0;
}
