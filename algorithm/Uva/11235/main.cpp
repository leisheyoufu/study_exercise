#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>

using namespace std;
#define MAXN 100005
#define INF 65535

int seq[MAXN];
int count; // 数的个数，段数
int pre; //输入的前一个数
int l[MAXN], r[MAXN],m[MAXN],num[MAXN]; //  m记录位置位于哪一段， num记录当前段具有的数的个数
int maxnum[MAXN][30];
int MAX(int a,int b,int c );
void RMQ()
{
    for(int i=1; i<=count; i++) {
        maxnum[i][0] = num[i];
    }
    for(int j=1; (1<<j)<=count+1; j++) {
        for(int i=1; i+(1<<j)-1<=count; i++) {
            maxnum[i][j]=max(maxnum[i][j-1],maxnum[i+(1<<(j-1))][j-1]);
        }
    }
}

int MAX(int a,int b,int c)
{
    if(a<b) {
        a=b;
    }
    if(a<c) {
        a=c;
    }
    return a;
}

int main()
{
    int n,q,i;
    int s,e;
    //freopen("test.txt","r",stdin);
	
	while( ~scanf("%d",&n)&&n){
		scanf("%d %d",&q,&seq[1]) ;	
		count = 1;
		l[count] =1;
		m[1]=1;
		pre =seq[1];
		for(i=2; i<=n; i++) {
			scanf("%d",&seq[i]);
			if( seq[i] != pre) {
				r[count] = i-1;
				count ++;
				l[count] = i;
				num[count] =0;
			}
			m[i] = count;
			num[count]++;
			pre = seq[i];
		}
		r[count] =i-1;
		RMQ();
		for(i=1; i<=q; i++) {
			scanf("%d %d",&s,&e);
			if(m[s] == m[e]) {
				printf("%d\n",e-s+1);
			} else {
				int answer= 0;
				if(m[s]+1<=m[e]-1) {
					int k = (int)((log(m[e]-m[s]-1)/log(2.0)));
					answer=max(maxnum[m[s]+1][k],maxnum[m[e]-(1<<k)][k]); //中间段
				}
				answer = MAX(r[m[s]]-s+1,answer,e-l[m[e]]+1);
				printf("%d\n",answer);
			}
		}   
	}	
	
    return 0;
}
