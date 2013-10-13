#include <stdio.h>
#include <stdlib.h>

#include <math.h>


#define MAXNUMBER 1000000000
#define Min(A,B) (((A)>(B))?(B):(A))





int printqueue[1000];

int main()
{
	//printf("%d",Min(190,100));
	int a,b,k,min;
	int j=0;
	while(scanf("%d%d",&a,&b) !=EOF)
	{
		if(a>b)
		{
			k=a-b;
			min = b;
		}
		else
		{
			k=b-a;
			min = a;
		}
		 int data = floor(k*(1.0+sqrt(5.0))/2);
		 if(data == min)
		 {
			printqueue[j] = 0;
		 }
		 else
		 {
			printqueue[j] = 1;
		 }
		 j++;
	}

	for(int i=0;i<j;i++)
	{
		printf("%d\n",printqueue[i]);
	}



	
	return 0;
}
