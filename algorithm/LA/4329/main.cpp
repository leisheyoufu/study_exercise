#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#include<string.h>

#define NUM 21000
#define MAX 110000
long long T,N;
long long a[NUM];
long long bit[MAX];
long long c[NUM],d[NUM];

long long lowbit(long long x)
{
	return x&(-x);
}

void add(long long x, long long v)
{
	while( x<= MAX)
	{
		bit[x]+=v;
		x+=lowbit(x);
	}
}

int sum(long long x)
{
	int result = 0;
	while(x > 0)
	{
		result+=bit[x];
		x -=lowbit(x);
	}
	return result;
}

int main()
{  
	long long ans = 0;
	//freopen("test.txt","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld",&N);
		
		for(long long i=1;i<=N;i++)
		{
			scanf("%lld",&a[i]);
		}
		memset(bit,0,sizeof(bit));
		add(a[1],1);
		for(long long i=2;i<=N;i++)
		{
			c[i]=sum(a[i]);
			add(a[i],1);
		}
		memset(bit,0,sizeof(bit));
		add(a[N],1);
		for(long long i=N-1;i>=1;i--)
		{
			d[i] = (N-i) - sum(a[i]);
			add(a[i],1);
		}
		ans= 0;
		for(int i=1;i<=N;i++)
		{
			ans+=(i-1-c[i])*(N-i-d[i])+c[i]*d[i];
		}
		printf("%lld\n",ans);
	}	
	return 0;
}

