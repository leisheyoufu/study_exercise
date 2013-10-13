#include <stdio.h>
//#include <conio.h>
#include <string.h>

int f[1000005];
char p[1000005];


int get_fail()
{
	int l = strlen(p);
	f[0] =0;
	f[1] = 0;

	for(int i=1;i<l;i++)
	{
		int j =f[i];
		while( j && p[i]!=p[j])
		{
			j=f[j];
		}
		f[i+1] = p[i] ==p[j]?j+1:0;
	}
	if(l%(l-f[l])==0)
	{
		return l/(l-f[l]);
	}
	return l/l;
	/*
	for(int i=0;i<=l;i++)
	{
		printf("%d",f[i]);
	}
	printf("\n");
	*/
}
/*
int kmp_next()
{
	int i=0,j=-1;
	f[0] = -1;
	int len=strlen(p);
	while( i <len)
	{
		if(j==-1|| p[i]==p[j])
		{
			i++;
			j++;
			f[i] = j;
		}
		else
		{
			j=f[j];
		}
	}
	int x = i-f[i];
	if(len %x==0)
		return len/x;
	else
		return len/len;
}
*/


int main()
{
	//freopen("test.txt","r+",stdin);
	while (scanf("%s",p) !=EOF)
	{
		if(p[0] == '.')
			break;
		int r =get_fail();
		//int r =kmp_next();
		printf("%d\n",r);

	}
	//getch();
	return 0;
}