#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


bool isTree(struct Edge *edge,int edgenum);
bool exist(struct Edge *edge,int m,int a,int b);


#define MAX 100000
struct Edge{
	int start;
	int end;
};

struct Edge edge[MAX];
int child[MAX];
int node[MAX];
int headnode[MAX];
int result[MAX];
int index = 0;

void print();
int main()
{
	int a,b;
	int m=0;
	
	
	while( scanf("%d%d",&a,&b)!=EOF )
	{
		if(a==0 && b==0)
		{			
			result[index] = isTree(edge,m);
			index++;
			m=0;
		}
		else if(a == -1 && b==-1 )
		{
			break;
		}
		else if( !exist(edge,m,a,b))
		{
			edge[m].start = a;
			edge[m].end = b;
			m++;
		}
		
		/*
			edge[m].start = a;
			edge[m].end = b;
			m++;
		*/

	}
	print();

	getch();
	return 0;
}

void print()
{
	for(int i=0;i<index;i++)
	{
		if(result[i] == 1)
		{
			printf("Case %d is a tree.\n",i+1);
		}
		else if(result[i]==0)
		{
			printf("Case %d is not a tree.\n",i+1);
		}
	}
}

bool isTree(struct Edge *edge,int edgenum)
{
	if(edgenum == 0 )
		return true;
	int inputnode = 0;
	
	memset(child,0,sizeof(child));
	memset(node,0,sizeof(node));
	memset(headnode,-1,sizeof(headnode));
	for(int i=0;i<edgenum;i++)
	{		
		if(edge[i].end == edge[i].start) //self circle
		{
			return false;
		}
		// 判断是否入度为1
		if(child[ edge[i].end % MAX]== 0)
		{
			child[ edge[i].end % MAX] =1;
		}
		else
		{
			return false;
		}

		if(node[ edge[i].end % MAX ]==0)
		{
			node[ edge[i].end % MAX ]++;
			inputnode++;
		}
	
		if(node[ edge[i].start % MAX ]==0)
		{
			node[ edge[i].start % MAX ]++;
			inputnode++;
		}

		if(headnode[ edge[i].start%MAX] == -1)
		{
			headnode[ edge[i].start%MAX] = 0;  // node exsit
		}
		if (headnode[ edge[i].end%MAX] == -1 || headnode[ edge[i].end%MAX]==0 )
		{
			headnode[ edge[i].end%MAX] = 1;  // has pointer to it
		}
		
	
	}
	if(inputnode != edgenum+1)
	{
		return false;
	}
	int head = 0;
	for(int i=0;i<MAX;i++)
	{
		if(headnode[i] == 0 && head == 0)
		{
			head =1;
		}
		else if( headnode[i] == 0 && head == 1)
		{
			return false;
		}
	}
	if(head == 0 )
	{
		return false;
	}
	return true;
}

bool exist(struct Edge *edge,int m,int a,int b)
{
	for(int i=0;i<m;i++)
	{
		if( edge[i].start == a &&  edge[i].end == b)
		{
			return true;
		}		
	}
	return false;
}