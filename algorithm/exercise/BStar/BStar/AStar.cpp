#include "AStar.h"


AStar::AStar(int **grid,int row,int column)
{
	this->row = row;
	this->column = column;
	this->OpenList = new SortList<ANode>(row*column);
	this->CloseList = new SortList<ANode>(row*column);
/*
	grid = new int*[row];
	for(int i=0;i<row;i++)
	{
		*(grid+i) = new int[column];
	}
	*/
	this->grid = grid;  // 1可通行 2 障碍 3终点
}


AStar::~AStar(void)
{
}

ANode* AStar::algorithm(int startX,int startY,int endX,int endY)
{
	ANode *start_p = new ANode(startX,startY,endX,endY,0);
	ANode *end_p = new ANode(endX, endY); 

	if(start_p->equal(*end_p))
	{
		return start_p;
	}
	
	OpenList->insert(start_p);
	while(!OpenList->isEmpty())
	{
		ANode *node = OpenList->pop();
		if((*node).equal(*end_p))
		{
			//break;
			return node;
		}
		ANode **child_array = new ANode*[4];
	//	memset(child_array,NULL,sizeof(child_array));
		createChild(*node,*end_p,child_array);

		for(int i=0;i<4;i++)
		{
			if(child_array[i]->x!=-1)
			{
				if(!OpenList->inList(*child_array[i])&& !CloseList->inList(*child_array[i]))
				{
					child_array[i]->father = node;
					OpenList->insert(child_array[i]);
				
				}

				else if(OpenList->inList(*child_array[i]))
				{
					int index = OpenList->getItem(*child_array[i]);
					if(OpenList->array[index]->f>child_array[i]->f)
					{
						OpenList->array[index]->f=child_array[i]->f;
						OpenList->array[index]->h=child_array[i]->h;
						OpenList->array[index]->g=child_array[i]->g;

						OpenList->array[index]->father = node;
					}
					
				}
				else if(CloseList->inList(*child_array[i]))
				{
					int index = CloseList->getItem(*child_array[i]);
					if(CloseList->array[index]->f>child_array[i]->f)
					{
						CloseList->array[index]->f=child_array[i]->f;
						CloseList->array[index]->h=child_array[i]->h;
						CloseList->array[index]->g=child_array[i]->g;
						CloseList->array[index]->father = node;
					}
					
				}

			}
			
		}//end of for
		CloseList->insert(node);


	}
}

void AStar::createChild(ANode node,ANode end_p,ANode *child_array[])
{
	ANode *up_node =NULL;	
	ANode *down_node = NULL;	
	ANode *left_node = NULL;	
	ANode *right_node = NULL;

	if(node.x+1<this->row &&grid[node.x+1][node.y]==1)
	{
		up_node = new ANode(node.x+1,node.y,end_p.x,end_p.y,node.g+1);
	}
	else
	{
		up_node = new ANode(-1,-1,0,0,0);
	}
	if(node.x-1>=0&&grid[node.x-1][node.y]==1)
	{
		down_node = new ANode(node.x-1,node.y,end_p.x,end_p.y,node.g+1);
	}
	else
	{
		down_node = new ANode(-1,-1,0,0,0);
	}
	if(node.y-1>=0&&grid[node.x][node.y-1]==1)
	{
		left_node = new ANode(node.x,node.y-1,end_p.x,end_p.y,node.g+1) ;
	}
	else
	{
		left_node = new ANode(-1,-1,0,0,0);
	}
	if(node.y+1<this->column&&grid[node.x][node.y+1]==1)
	{
		right_node = new ANode( node.x,node.y+1,end_p.x,end_p.y,node.g+1);
	}
	else
	{
		right_node = new ANode(-1,-1,0,0,0);
	}
	
	//if(up_node!=NULL)
	child_array[0]= up_node;
	//if(down_node!=NULL)
	child_array[1]= down_node;
	//if(left_node!=NULL)
	child_array[2]= left_node;
	//if(right_node!=NULL)
	child_array[3]= right_node;

}
