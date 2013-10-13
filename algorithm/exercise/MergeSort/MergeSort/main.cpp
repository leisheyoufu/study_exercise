#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void MergeSort(int a[],int temp[],int left,int right);

int main()
{
	int a[] = {31,42,25,78,64,3,100};
	int len = sizeof(a)/sizeof(int);
	int *b = (int*)malloc(sizeof(int)*len);
	MergeSort(a,b,0,len-1);
	free(b);

	for(int i=0;i<len;i++)
	{
		printf("%d ",a[i]);
	}
	getch();
	return 0;
}

void MergeSort(int a[],int temp[],int left,int right)
{
	for(int i=left;i<=right;i++)
	{
		temp[i] = a[i];
			printf("%d ",a[i]);
	}
	printf("\n");
	int mid = (left+right)/2;
	if(left == mid && right == mid)
	{
		return ;
	}
	MergeSort(a,temp,left,mid);
	MergeSort(a,temp,mid+1,right);

	int cur = left;
	int l = left;
	int r = mid+1;

	while(cur<=right)
	{	
		if(l>mid)
		{
			a[cur++] = temp[r++];
		}
		else if(r>right)
		{
			a[cur++] = temp[l++];
		}
		else if(temp[l]<=temp[r])
		{
			a[cur++] = temp[l++];
		}
		else if(temp[l]>temp[r])
		{
			a[cur++] = temp[r++];
		}		
	}
	printf("after sort\n");
	for(int i=left;i<=right;i++)
	{
		temp[i] = a[i];
		printf("%d ",a[i]);
	}
	printf("\n");
}