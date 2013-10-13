#include "EightDigital.h"


EightDigital::EightDigital(void)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			array[i][j] = -1;
		}
	}
	h=0;
	g=-1;
	f = h+g;
	for(int i=0;i<4;i++)
	{
		child[i] = NULL;
	}
	father = NULL;
}

EightDigital::EightDigital(int a[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			array[i][j] = a[i][j];
		}
	}
	initZeroPosition();
}


EightDigital::EightDigital(int a[3][3],EightDigital *goal)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			array[i][j] = a[i][j];
		}
	}
	calh(goal);
	g = 0;
	f = g+h;
	initZeroPosition();
}

EightDigital::EightDigital(EightDigital *copy)
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			array[i][j] = copy->array[i][j];
		}
	}
	g = copy->g +1;
	
}



EightDigital::~EightDigital(void)
{
}

void EightDigital::calh(EightDigital *goal)
{
	h= 0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(array[i][j] != goal->array[i][j])
			{
				h++;
			}
		}
	}
	
}

void EightDigital::calf(EightDigital *goal)
{
	calh(goal);
	f= g+h;
	
}


void EightDigital::initZeroPosition()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(array[i][j] == 0)
			{
				x = i;
				y = j;
				break;
			}
		}
	}
}

bool EightDigital::swapZeroUp()
{
	if(x==0)
	{
		return false;
	}
	else
	{
		int temp = array[x-1][y];
		array[x-1][y] = 0;
		array[x][y]=temp;
	}
	return true;
}

bool EightDigital::swapZeroDown()
{
	if( x ==2 )
	{
		return false;
	}
	else
	{
		int temp = array[x+1][y];
		array[x+1][y] = 0;
		array[x][y] =temp;
	}
	return true;
}

bool EightDigital::swapZeroLeft()
{
	if(y==0)
	{
		return false;
	}
	else
	{
		int temp = array[x][y-1];
		array[x][y-1] = 0;
		array[x][y] =temp;
	}
	return true;
}

bool EightDigital::swapZeroRight()
{
	if(y==2)
	{
		return false;
	}
	else
	{
		int temp = array[x][y+1];
		array[x][y+1]=0;
		array[x][y] = temp;
	}
	return true;
}

void EightDigital::initChild(EightDigital *goal)
{
	int i=0;	
	EightDigital *temp =  new EightDigital(this);
	temp->initZeroPosition();
	
	if(temp->swapZeroUp())
	{
		child[i] = temp;
		child[i]->father = this;
			i++;
	}
	else
	{
		free(temp);
	}

	temp =  new EightDigital(this);
	temp->initZeroPosition();
	if(temp->swapZeroDown())
	{
		child[i] = temp;
		child[i]->father = this;
			i++;
	}
	else
	{
		free(temp);
	}

	temp =  new EightDigital(this);
	temp->initZeroPosition();
	if(temp->swapZeroLeft())
	{
		child[i] = temp;
		child[i]->father = this;
			i++;
	}
	else
	{
		free(temp);
	}

		temp =  new EightDigital(this);
		temp->initZeroPosition();
	if(temp->swapZeroRight())
	{
		child[i] = temp;
		child[i]->father = this;
			i++;
	}
	else
	{
		free(temp);
	}
	childNum = i;
	


}

void EightDigital::print()
{
	printf("Êý¾Ý\n");
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			printf("%d ",array[i][j]);
		}
		printf("\n");
	}
	printf("h= %d, g= %d, f= %d \n",h,g,f);
}