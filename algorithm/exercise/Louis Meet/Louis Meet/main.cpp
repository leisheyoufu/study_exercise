#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

int A[][4] = {{2,1,1,0},{0,2,1,1},{0,0,2,0},{1,0,1,2}};
int meet[4][4];
int N=4,M=4;

void dump_meet(int num)
{
	for(int i=0;i<num;i++)
	{		
		for(int j=0;j<num;j++)
		{
			printf("%d ",meet[i][j]);
		}
		printf("\n");
	}

}

void find_meet(int num)
{
	memset(meet,-1,16*sizeof(int));
	dump_meet(4);

	for(int i=0;i<num;i++)
	{
		int k=0;
		int j;
		while(k<num-1)
		{
			j=(k+i+1)%num;
			
			

		}
		
	}

}


int main()
{
	find_meet();
	getch();
	return 0;
}