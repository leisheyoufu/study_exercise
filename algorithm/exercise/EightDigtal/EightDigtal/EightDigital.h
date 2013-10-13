#pragma once

#include <stdlib.h>
#include <stdio.h>
class EightDigital
{
public:
	EightDigital(void);
	EightDigital(int a[3][3]);
	EightDigital(int a[3][3],EightDigital *goal);
	EightDigital(EightDigital *copy);
	void calh(EightDigital *goal);
	void calf(EightDigital *goal);
	~EightDigital(void);
	bool swapZeroUp();
	bool swapZeroDown();
	bool swapZeroLeft();
	bool swapZeroRight();
	void print();
	void initChild(EightDigital *goal);

	void initZeroPosition();
	int x;
	int y;
	int array[3][3];
	int h;
	int g;
	int f;
	EightDigital *child[4];
	int childNum;
	EightDigital *father;
};

