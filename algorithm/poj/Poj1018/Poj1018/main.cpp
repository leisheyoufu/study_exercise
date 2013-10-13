#include <stdio.h>
#include <stdlib.h>
#include <conio.h>



void print();
void backtrack(int index,int k);
void Trackback();



struct pair{
	int bandwidth;
	int cost;
};

struct device{
	int num;
	int a[100];
	struct pair node[100][100];
};

struct device dev[10];
int testcase;
int band = 32767;
int cost = 0;
float minbandcost = 0;

int min = 32767;

int main()
{
	
	scanf("%d",&testcase);
	for(int i=0;i<testcase;i++)
	{
		scanf("%d",&dev[i].num);
		
	}

	for(int i=0;i<testcase;i++)
	{
		for(int j=0;j<dev[i].num;j++)
		{
			scanf("%d",&dev[i].a[j]);
			
			for(int k=0;k<dev[i].a[j];k++)
			{
				scanf("%d",&dev[i].node[j][k].bandwidth);
				scanf("%d",&dev[i].node[j][k].cost);
			}
		}

	}
	for(int i=0;i<testcase;i++)
	{
		backtrack(i,0);
		printf("%.3f\n",minbandcost);
	}

	getch();
	return 0;
}

void print()
{
	for(int i=0;i<testcase;i++)
	{
		for(int j=0;j<dev[i].num;j++)
		{
			for(int k=0;k<dev[i].a[j];k++)
			{
				printf("%d  %d  ",dev[i].node[j][k].bandwidth,dev[i].node[j][k].cost);
			}
			printf("\n");
		}
	}

}

void backtrack(int index,int k)
{
	if(k>=dev[index].num)
	{		
	
		if(minbandcost < (float)min/cost)
		{
			minbandcost = (float)min/cost;
		}
	
		return ;
	}
	else
	{		
			for(int m=0;m<dev[index].a[k];m++)
			{
				cost+=dev[index].node[k][m].cost;
				int oldmin = min;
				if( k == 0)
				{
					min = dev[index].node[k][m].bandwidth;
				}
				else if(min > dev[index].node[k][m].bandwidth)
				{
					oldmin = min;
					min  = dev[index].node[k][m].bandwidth;
				}
				
				if( (float)min/cost > minbandcost)
				{
					backtrack(index,k+1);
			
				}
				min = oldmin;
				cost-=dev[index].node[k][m].cost;
				
			
				
			

			}
	}
}