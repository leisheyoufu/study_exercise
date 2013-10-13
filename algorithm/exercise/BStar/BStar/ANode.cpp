#include "ANode.h"


ANode::ANode(void)
{
}

ANode::ANode(int x,int y)
{
	this->x = x;
	this->y = y;
	
}

ANode::ANode(int x, int y,int endX,int endY,int g)
{
	this->x = x;
	this->y = y;
	calF(endX,endY,g);
	this->father=0;
}

ANode::~ANode(void)
{
}

void ANode::calF(int endX,int endY,int g)
{
	this->g = g;
	this->h= abs(endX-x)+abs(endY-y);
	this->f = this->g+this->h;
}

bool ANode::operator<(const ANode &right) const
{
	return this->f<right.f;
}

bool ANode::operator==(const ANode &right) const
{
	if(this->x==right.x && this->y == right.y)
		return true;
	return false;
}

void ANode::operator=(const ANode &right) 
{
	this->x = right.x;
	this->g = right.g;
	this->y = right.y;
	this->f = right.f;
	this->h = right.h;
	this->father = right.father;

}

bool ANode::equal(const ANode right) const
{
	if(this->x==right.x && this->y == right.y)
		return true;
	return false;
}

