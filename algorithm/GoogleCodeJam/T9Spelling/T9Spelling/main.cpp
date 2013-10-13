#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


char *charactor[27] = {"2","22","222","3","33","333"  //abccedf
						,"4","44","444","5","55","555","6","66","666"  //ghijklmno
						,"7","77","777","7777","8","88","888","9","99","999","9999","0"};//pqrstuvwxyz ¿Õ¸ñ
FILE *infp,*outfp;
int N;

char ch;


int main()
{
	infp = fopen("C-large-practice.in","r");
	outfp = fopen("out.txt","w");
	fscanf(infp,"%d",&N);
	fgetc(infp);
	
	
//	char temp[10];
	//fscanf(infp,"%s",temp);
	//fscanf(infp,"%s",temp);
//	fscanf(infp,"%s",str);
	
	for(int i=0;i<N;i++)
	{
		int index = 0;
		char str[2048];
		while(ch = fgetc(infp),ch!='\n' && ch!=EOF)
		{
			str[index++]=ch;
		}
		str[index] = '\0';
		printf("%s",str);
		fprintf(outfp,"Case #%d: ",i+1);
		for(int j=0;j<index;j++)
		{
			if(str[j] ==' ')
			{
				if(j>0 && str[j-1] == ' ')
				{
					fprintf(outfp," ");
				}
				fprintf(outfp,"0");
			}
			else
			{
				if(j>0 && str[j-1]>='a')
				{
					int len = strlen(charactor[str[j-1]-'a']);
					if( charactor[str[j-1]-'a'][len-1] == charactor[str[j]-'a'][0])
					{
						fprintf(outfp," ");
					}

				}
				fprintf(outfp,"%s",charactor[str[j]-'a']);
				//str[j]
			}
			
		}
		fprintf(outfp,"\n");

	}
	fclose(infp);
	fclose(outfp);
	getch();

}