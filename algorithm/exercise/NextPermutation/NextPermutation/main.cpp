#include <iostream>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <stack>

using namespace std;


struct CharFrequency
{
	char ch;
	int count;
};
void statistcs(char *str,struct CharFrequency *maparray,int n);
bool inArray(struct CharFrequency *maparray,int n,char ch);
int getMaxPermutation(struct CharFrequency *maparray,int n);
int getMinPermutation(struct CharFrequency *maparray,int n);

void printAllPermutation( int number,struct CharFrequency *maparray,int n);


int main()
{
	char *str = "aarmy";
	CharFrequency maparray[5];
	statistcs(str,maparray,5);
	for(int i=0;i<5;i++)
	{
		printf("%c , %d \n",maparray[i].ch,maparray[i].count);
	}
	int max = getMaxPermutation(maparray,5);
	int min = getMinPermutation(maparray,5);

	for(int number = min;number <=max;number++)
	{
		printAllPermutation(number,maparray,5);
		printf("\n");
	}

	//printAllPermutation(414,maparray,5);
	//printf("Max = %d \n",max);
	//printf("Min = %d \n",min);

	
	getch();
	return 0;
}

void statistcs(char *str,struct CharFrequency *maparray,int n)
{
	int len = strlen(str);
	char ch = 127;
	int count =0;
	for(int k=0;k<len;k++)
	{
		for(int i=0;i<len;i++)
		{
			if(!inArray(maparray,n, *(str+i)) && *(str+i)<ch )
			{
				ch = *(str+i);
				count = 1;
			}
			else if(ch == *(str+i))
			{
				count++;
			}
		}
		maparray[k].count = count;
		maparray[k].ch = ch;
		count = 0;
		ch = 127;

	}
	

}

bool inArray( struct CharFrequency *maparray,int n,char ch)
{
	for(int i=0;i<n;i++)
	{
		if(maparray[i].ch == ch )
			return true;
	}
	return false;
}

int getMaxPermutation(struct CharFrequency *maparray,int n)
{	
	int max = 0;
	int k = n;
	while(n>0)
	{
		int count = maparray[n-1].count;
		while(count >0)
		{
			count--;
			max+=n-1;
			max*=k;
			k--;
		}
		n--;
	}
	return max;

}

int getMinPermutation(struct CharFrequency *maparray,int n)
{
	int k=0;
	int min = 0;
	int m = n;
	while(m>0)
	{
		int count = maparray[k].count;
		while( count >0)
		{
			count--;
			min+=k;
			min*=m;
			m--;
		}
		k++;

	}
	return min;

}

void printAllPermutation( int number,struct CharFrequency *maparray,int n)
{	
	int m = 0;
	for(int i=2;i<=n+1;i++)
	{
		m = number%i;
	
		
		if(maparray[m].count >=1)
		{
			printf("%c",maparray[m].ch);
		//	maparray[m].count--;

		}
		
			
		number/=i;

	}
}
