#include <cstdio>
//#include <conio.h>
#include <vector>
#include <string>
using namespace std;

#define INF 999999
struct item {
	
	int p;
	int dis;

};

int map[105][105];
vector<struct item> result;

void find_min_dis(int n)
{
	struct item t;
	t.dis = INF;
	t.p = 0;
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<n;i++)
		{	
			for(int j=0;j<n;j++)
			{
				if(map[i][j]> map[i][k]+map[k][j])
				{
					map[i][j] =  map[i][k]+map[k][j];
				}
			}
		}
	}
	
	
	for(int i=0;i<n;i++)
	{
		int max = -1;			
		for(int j=0;j<n;j++)
		{			
			if(map[i][j]>max)
			{
				max = map[i][j];
			}			
		}
		if( max < t.dis)
		{
			t.dis = max;
			t.p = i+1;
		}
	}
	result.push_back(t);

}

int main()
{
	//freopen("test.txt","r+",stdin);

	int n;
	int index=0;
	while(scanf("%d",&n) == 1 &&n)
	{
		memset(map,INF,sizeof(map));
		for(int i=0;i<n;i++)
		{
			int num;
			scanf("%d",&num);
			for(int j=0;j<num;j++)
			{
				int temp;
				int dis;
				scanf("%d %d",&temp,&dis);
				map[i][temp-1]=dis;
			}
		}
		for(int i=0;i<n;i++)
		{
			map[i][i] =0;
		}

		find_min_dis(n);
		index++;
	}

	for(int i=0;i<index;i++)
	{
		if( result[i].dis>=INF )
		{
			printf("disjoint\n");
		}
		else
		{
			printf("%d %d\n",result[i].p,result[i].dis);
		}
	}


	//getch();
	return 0;
}