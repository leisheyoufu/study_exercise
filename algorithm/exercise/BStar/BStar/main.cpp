#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "AStar.h"
int main()
{
	const int row =2;
	const int column = 10;
	int **grid;
	grid = new int*[row];
	for(int i=0;i<row;i++)
	{
		grid[i]=new int[column];
	}

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<column;j++)
		{
			grid[i][j]=1;
		}
	}
	grid[1][0] = 2;
	grid[1][2] = 2;

	AStar atar(grid,row,column);
	ANode *node = atar.algorithm(0,0,1,9);
	printf("dd\n\n");

	while( node->father!=NULL)
	{
		printf("Node (%d,%d)",node->x,node->y);
		node = node->father;
	}

	getch();
	return 0;
}