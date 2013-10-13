#pragma once

#include <math.h>
class ANode
{
public:
	ANode(void);
	~ANode(void);
	ANode(int x, int y);
	ANode(int x, int y,int endX,int endY,int g);

	void calF(int endX,int endY,int g);
	int x;
	int y;
	ANode *father;
	int g;
	int h;
	int f;
	bool operator<(const ANode &) const;
	bool operator==(const ANode &) const;
	void operator=(const ANode &) ;
	bool equal(const ANode node) const;
};

