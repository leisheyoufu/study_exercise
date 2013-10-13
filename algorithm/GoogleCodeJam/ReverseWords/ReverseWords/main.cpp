#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


FILE *infp, *outfp;

char *letter[1000];
	int line = 0;
	int word = 0;
	int N;

void read()
{
		char ch;
		word = 0;
		line = 0;
//	ch=	fgetc(infp);
//	ch = fgetc(infp);
	letter[0] = (char*)malloc(1000*sizeof(char));
	while( (ch = fgetc(infp)) !='\n')
	{		
		if(ch == ' ')
		{
			letter[line++][word] = '\0';
			letter[line] = (char*)malloc(1000*sizeof(char));
			word = 0;
		}
		else
		{
			letter[line][word++] = ch;
		}
	}
	letter[line][word] = '\0';

}

void process()
{
	int mid = word/2;

	int l = 0;
	int r = line;
	while(l<r)
	{
		char *p = letter[l];
		letter[l] = letter[r];
		letter[r] = p;
		l++;
		r--;
	}
	
}

void write(int N)
{
	fprintf(outfp,"Case #%d: ",N);
	for(int i=0;i<=line;i++)
	{
		fprintf(outfp,"%s ",letter[i]);
	}
	fprintf(outfp,"\n");
	for(int i=0;i<line;i++)
	{
		free(letter[i]);
	}
	
}


int main()
{
	infp = fopen("B-large-practice.in","r");	
	outfp=fopen("out.txt","w");
	fscanf(infp,"%d",&N);
	fgetc(infp);
	for(int i=0;i<N;i++)
	{
		read();
		process();
		write(i+1);
	}

	fclose(infp);
	fclose(outfp);

	

	getch();
	return 0;
}