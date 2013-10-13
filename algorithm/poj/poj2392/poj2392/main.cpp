#include <stdio.h>
//#include <conio.h>
#include <algorithm>
#include <string.h>

using namespace std;

#define MAX_NODE 405
#define MAX_HEIGHT 40005
int K;
int sum[MAX_HEIGHT];
int mark[MAX_HEIGHT];
struct Node
{
	int h;
	int a;
	int c;
};

struct Node node[MAX_NODE];

int dp()
{
	int ans = 0;
	mark[0] =1;
	for(int i=0;i<K;i++)
	{
		memset(sum,0,sizeof(sum));
		for(int j=node[i].h;j<=node[i].a;j++)
		{
			if(!mark[j] && mark[j-node[i].h] && sum[j-node[i].h] <node[i].c)
			{
				mark[j] = 1;
				sum[j] = sum[j-node[i].h]+1;
				if (ans < j)
				{
					ans = j;
				}
			}
			
		}
	}
	return ans;
}

bool cmp(struct Node a,struct Node b)
{
	return a.a<b.a;
}

int main()
{
//	freopen("test.txt","r",stdin);
	scanf("%d",&K);

	for(int i=0;i<K;i++)
	{
		scanf("%d %d %d\n",&node[i].h,&node[i].a,&node[i].c);

	}
	sort(node,node+K,cmp);
	int ans = dp();
	printf("%d\n",ans);

//	getch();
	return 0;
}