#include <stdio.h>
#include <conio.h>


int a1[]={1,2,10};
int a2[]={1,2,5,7};


int center_search(int a[],int n1,int b[],int n2)
{
	int l1=0,r1=n1-1,l2=0,r2=n2-1;
	int n = n1+n2;
	int c= 0;
	while(l1!=r1 && l2!=r2)
	{
		int c1=(l1+r1)/2;
		int c2=(l2+r2)/2;
		if(a[c1]<b[c2])
		{		
			l1=c1+1;
			r2=c2;
		}
		else
		{
		
			r1=c1;
			l2=c2+1;
		}
		
	}
	if(l2==r2)
	{
		return a[(l1+r1)/2]>b[l2]?b[l2]:a[(l1+r1)/2];
	}
	else
	{
		return b[(l2+r2)/2]>a[l1]?a[l1]:b[(l2+r2)/2];
	}
}

int main()
{
	int len1=sizeof(a1)/sizeof(int);
	int len2=sizeof(a2)/sizeof(int);
	int r =center_search(a1,len1,a2,len2);
	printf("%d\n",r);
	getch();

	return 0;
}