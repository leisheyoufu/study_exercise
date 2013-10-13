#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Point{
	double x;
	double y;
};
struct Rect{
	struct Point p1;
	struct Point p2;
	int num;
	Rect()
	{
		num=0;
	}
	
};

int GetChildRect(int width,int height,Rect rect,vector<Rect> &child)
{

	int num = 0;
	if( rect.p1.y>0.5)
	{
		struct Rect upRect;
		upRect.p1.x = 0;
		upRect.p1.y = 0;
		upRect.p2.x = width;
		upRect.p2.y = rect.p1.y-0.5;
		upRect.num = rect.num;

		child.push_back(upRect);
		num ++;
	}
	if(rect.p1.x>0.5)
	{
		struct Rect leftRect;
		leftRect.p1.x=0;
		leftRect.p1.y=0;
		leftRect.p2.x = rect.p1.x-0.5;
		leftRect.p2.y = height;
		leftRect.num = rect.num;
		child.push_back(leftRect);
		num ++;
	}
	if(width - rect.p2.x >0.5)
	{
		struct Rect rightRect;
		rightRect.p1.x=rect.p2.x+0.5;
		rightRect.p1.y=0;
		rightRect.p2.x = width;
		rightRect.p2.y = height;
		rightRect.num = rect.num;
		child.push_back(rightRect);
		num ++;
	}
	if(height - rect.p2.y>0.5)
	{
		struct Rect downRect;
		downRect.p1.x=0;
		downRect.p1.y=rect.p2.y+0.5;
		downRect.p2.x = width;
		downRect.p2.y = height;
		downRect.num = rect.num;
		child.push_back(downRect);
		num ++;
	}

	return num;

}

bool InRect(Rect rect,int x,int y)
{
	if(x>=rect.p1.x && x<=rect.p2.x && y>=rect.p1.y && y<=rect.p2.y)
		return true;
	return false;
}

int TreesInRect(Rect &rect,Point point[],int n)
{
	int num = rect.num;
	for(int i=0;i<n;i++)
	{
		if(InRect(rect,point[i].x,point[i].y))
			num++;
	}
	rect.num = num;
	return num;
}

int TressInAll(Rect rect,Point point[],int n,Rect &rect2)
{
	int min = 255;
	for(double x = rect.p1.x; x<=rect.p2.x;x+=0.5)
	{
		for(double y = rect.p1.y;y<=rect.p2.y;y+=0.5)
		{
			if(InRect(rect,x+28,y+15))
			{
				int number = 255;
				struct Rect temp;
				temp.p1.x=x;
				temp.p1.y=y;
				temp.p2.x=x+28;
				temp.p2.y=y+15;
				temp.num = rect.num;
				//cout << "Rect2: "<< "(" <<temp.p1.x << "," << temp.p1.y <<") (" << temp.p2.x << "," <<temp.p2.y << ")" << endl; 
				number = TreesInRect(temp,point,n);
				if(number <min)
				{
					min = number;
					rect2.p1.x=x;
					rect2.p1.y= y;
					rect2.p2.x=x+28;
					rect2.p2.y=y+15;
				}
			}
			
			if(InRect(rect,x+15,y+28))
			{
				int number = 255;
				struct Rect temp;
				temp.p1.x=x;
				temp.p1.y=y;
				temp.p2.x=x+15;
				temp.p2.y=y+28;
				temp.num = rect.num;
				number = TreesInRect(temp,point,n);
				if(number <min)
				{
					min = number;
					rect2.p1.x=x;
					rect2.p1.y= y;
					rect2.p2.x=x+28;
					rect2.p2.y=y+15;
				}
			}
			
		}
	}
	return min;
}

int main()
{
	int width=50,height=40;
	vector<Rect> v;
	Point point[] = {{11,17},{24,26},{36,20}};
	for(double x=0;x<=width;x+=0.5)
	{
		for(double y=0;y<=height;y+=0.5)
		{
			if(x+28<=width && y+15<=height)
			{
				struct Rect rect;
				rect.p1.x = x;
				rect.p1.y = y;
				rect.p2.x = x+28;
				rect.p2.y = y+15;
			
				rect.num = 0;
				TreesInRect(rect,point,3);
				GetChildRect(width,height,rect,v);
			
			}

			if(x+15<=width && y+28<=height)
			{
				struct Rect rect;
				rect.p1.x = x;
				rect.p1.y = y;
				rect.p2.x = x+15;
				rect.p2.y = y+28;
				rect.num = 0;
				TreesInRect(rect,point,3);
				GetChildRect(width,height,rect,v);
			}
		}
	}
	int min =255;
		vector<Rect>::iterator iter;
		Rect rect2;
	for(iter = v.begin();iter!=v.end();iter++)
	{
		if(TressInAll((*iter),point,3,rect2) < min)
		{
			min = TressInAll((*iter),point,3,rect2);
			if(min == 0)
			{
				cout << "Rect2" << endl;
				cout <<"("<<(*iter).p1.x << ","<<(*iter).p1.y <<")  (" <<(*iter).p2.x <<"," <<(*iter).p2.y << ")" << endl;
				cout << "Rect2: "<< "(" <<rect2.p1.x << "," << rect2.p1.y <<") (" << rect2.p2.x << "," <<rect2.p2.y << ")" << endl; 
			}
		}
	}

	cout << min;
	/*
	vector<Rect>::iterator iter;
	for(iter = v.begin();iter!=v.end();iter++)
	{
		cout <<"("<<(*iter).p1.x << ","<<(*iter).p1.y <<")  (" <<(*iter).p2.x <<"," <<(*iter).p2.y << ")" << endl;
	}*/
	getch();
	return 0;
}

