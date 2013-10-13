#include <stdio.h>
#include <conio.h>
#include <algorithm>

using namespace std;
	int a[5][5]={{1},{3,2},{4,10,1},{4,3,2,20}};
	int d[5][5];
int dp(int n)
{
	d[0][0]= a[0][0];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<=i+1;j++)
		{
			if(j!=i+1)
			{
				d[i][j] = max(d[i-1][j-1],d[i-1][j])+a[i][j];
			}
			else
			{
				d[i][j] = d[i-1][j-1]+a[i][j];
			}
		}
	}

	for(int i=0;i<n;i++)
	{
		printf("%d ",d[3][i]);
	}
	return 0;
}

int dp2(int n)
{
	for(int i=0;i<n;i++)
	{
		d[n-1][i] = a[n-1][i];
	}
	for(int i=n-1;i>0;i--)
	{		
		for(int j=1;j<=i;j++)
		{
			d[i-1][j-1] = max(d[i][j],d[i][j-1])+a[i-1][j-1];
		}
	}

	printf("%d",d[0][0]);
	return 0;
}


int main()
{

	dp2(4);



	getch();
	return 0;
}