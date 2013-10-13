#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define NUM 1000
int T;
int N;

__int64 a[NUM];
__int64 b[NUM];
__int64 c[NUM];
int mark[NUM];
FILE *infp;
FILE *outfp;

__int64 scalar;
__int64 min;

void cal_scalar()
{
	scalar = 0;
	for(int i=0;i<N;i++)
	{
		
		scalar+=a[i]*b[i];
	}
}

void select_min(int k)
{
	__int64 s_min = 9223372036854775808;
	for(int i=k;i<N;i++)
	{
		if(s_min>a[i])
		{
			__int64 temp = a[i];
			a[i] = a[k];
			a[k] = temp;
			s_min = temp;
		}
	}
}

void select_max(int k)
{
	__int64 s_max = -9223372036854775808;
	for(int i=k;i<N;i++)
	{
		if(s_max<b[i])
		{
			__int64 temp = b[i];
			b[i] = b[k];
			b[k] = temp;
			s_max = temp;
		}
	}
}

void cal_scalar2()
{
	for(int i=0;i<N;i++)
	{
		select_min(i);
		select_max(i);
	}
	scalar = 0;
	if(N%2==0)
	{
		for(int i=0;i<N/2;i++)
		{
		
			scalar+=a[i]*b[i];
		//	if(i!=N-i-1)
			scalar+=a[N-i-1]*b[N-i-1];
		}
	}
	else
	{
		for(int i=0;i<N/2+1;i++)
	{
		
		scalar+=a[i]*b[i];
		if(i!=N-i-1)
		scalar+=a[N-i-1]*b[N-i-1];
	}
	}
	
	min =scalar;
}


void permutation(int k)
{
	if(k == N)
	{
		cal_scalar();
		//printf("%d ",scalar);
		if(min >scalar)
		{
			min = scalar;
		}
		//printf("%d",min);

	}
	else
	{
		for(int i=0;i<N;i++)
		{
			if(mark[i]==0)
			{
				a[k] = c[i];
				mark[i] =1;
				permutation(k+1);
				mark[i] = 0;
			}
		}
	}
	

}



int main()
{
	infp=fopen("A-large-practice.in","r");
	outfp = fopen("out3.txt","w");
	fscanf(infp,"%d",&T);
	for(int i=0;i<T;i++)
	{
		fscanf(infp,"%d",&N);
		for(int j=0;j<N;j++)
		{
			fscanf(infp,"%d",&b[j]);
		}
		for(int j=0;j<N;j++)
		{
			fscanf(infp,"%d",&a[j]); //permu 方法改为c
		}
		min = 99999999999999;
	//	permutation(0);
		cal_scalar2();
		
		fprintf(outfp,"Case #%d: %lld\n",i+1,min);
	}
	fclose(infp);
	fclose(outfp);
	getch();
	return 0;
}
		