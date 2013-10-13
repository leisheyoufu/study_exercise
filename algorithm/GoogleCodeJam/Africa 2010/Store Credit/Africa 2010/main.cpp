#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int N;
int C;
int I;
int P[65536];

int choose1;
int choose2;

FILE *infp;
	FILE *outfp;

void select(int index)
{
	for(int i=0;i<I;i++)
	{
		for(int j=i+1;j<I;j++)
		{
			if(P[i] + P[j] == C)
			{
				fprintf(outfp,"Case #%d: %d %d\n",index,i+1,j+1);

			}

		}
	}

}


int main()
{
	

	infp=fopen("A-large-practice.in","r");
	outfp=fopen("out.txt","w");
	
	fscanf(infp,"%d",&N);
	for(int i=0;i<N;i++)
	{
		fscanf(infp,"%d",&C);
		fscanf(infp,"%d",&I);
		for(int j=0;j<I;j++)
		{
			fscanf(infp,"%d",&P[j]);
		}

		select(i+1);



	}
	
	fclose(infp);
	fclose(outfp);
	getch();
	return 0;
}