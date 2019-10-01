#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

#define MOD	1000007
#define MAXK	500

int C[MAXK+1][MAXK+1];   // ����������

// ��ϵ��ƹ�ʽ
void init(int k)
{
    //memset(C,0,sizeof(C));
    for(int i=0; i<=k; i++) {
        C[i][0] = 1;
        C[i][i]=1;
        for(int j=1; j<i; j++) {
            C[i][j] = (C[i-1][j-1]+C[i-1][j])%MOD;
        }
    }
}

int main()
{
    int T,m,n,k,t=1;
    init(MAXK);
    //freopen("test.txt","r",stdin);
    scanf("%d",&T);
    while(t<=T) {
        int sum = 0;
        scanf("%d %d %d",&m,&n,&k);
        // ʹ���ݳⶨ�����ӻ��
        for(int S=0; S<16; S++) {
            int hit =0, r=m,c=n;
            if(S&1) {
                r--;    // ��һ�в���ʯͷ
                hit++;
            }
            if(S&2) {
                r--;
                hit++;
            }
            if(S&4) {
                c--;
                hit++;
            }
            if(S&8) {
                c--;
                hit++;
            }
            if(hit&1) {
                sum = (sum +MOD -C[r*c][k]) %MOD;
            } else {
                sum = (sum +C[r*c][k] +MOD) %MOD;
            }
        }
        printf("Case %d: %d\n",t,sum);
        t++;
    }

    return 0;
}
