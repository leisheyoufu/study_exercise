#pragma once

#include "ANode.h"
#include <stdlib.h>
#include <string.h>
#include "SortList.cpp"
class AStar
{
public:
	AStar(int **grid,int row,int column);
	~AStar(void);

	SortList<ANode> *OpenList;
	SortList<ANode> *CloseList;

	ANode* algorithm(int startX,int startY,int endX,int endY);
	void createChild(ANode node,ANode end_p,ANode *child_array[]);
	int **grid;
	int row;
	int column;

};

