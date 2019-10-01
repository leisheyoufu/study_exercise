#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <vector>

using namespace std;

int L,D,N;
FILE *infp,*outfp;
char word[5000][16];
char pattern[5000];
int length;
bool state = false;
char pk[15][50];
int pk_size[15];
bool mark[5000];
char str[16];
int count =0;
int mattrix[5000][15];


bool isRightRow(int line,int end)
{
    for(int i=0; i<end; i++) {
        if(mattrix[line][i] == 0)
            return false;
    }
    return true;

}

bool compare(char *str,int n)  //比较前n个字符
{

    for(int i=0; i<D; i++) {
        int j=0;
        for(j=0; j<n; j++) {
            if(*(str+j)!=word[i][j]) {
                break;
            }

        }
        if( j==n) {
            return true;
        }
    }
    return false;
}

int comparebyte(char ch,int k)
{
    int num = 0;
    for(int i=0; i<D; i++) {
        if( k==0 &&ch == word[i][k]) {
            mattrix[i][k] = 1;
            num++;
        } else if( mattrix[i][k-1]== 1 &&ch == word[i][k]) {
            mattrix[i][k] = 1;
            num++;
        }

    }
    return num;
}
/*
void backtrack(int k)
{
	if(k==L)
	{
		if(compare(str,k))
		{
			count++;
		}
	}
	else
	{
		for(int i=0;i<pk_size[k];i++)
		{
			str[k] = pk[k][i];
			if( compare(str,k))
			{
				backtrack(k+1);
			}
			str[k] = '\0';
		}
	}

}
*/

/*
void backtrack(int k)
{
	if(k==L)
	{
		if(comparebyte(str,k))
		{
			count++;
		}
	}
	else
	{
		for(int i=0;i<pk_size[k];i++)  //第K列
		{
			str[k] = pk[k][i];
			comparebyte(str,k);
			if( isRightRow(str,k))
			{
				backtrack(k+1);
			}
			str[k] = '\0';
		}
	}}
*/

void traversal()
{
    for(int i=0; i<L; i++) {
        count = 0;
        for(int j=0; j<pk_size[i]; j++) {
            count+=comparebyte(pk[i][j],i);
        }
        if(count == 0)
            break;
    }
}

int main()
{
    infp=fopen("A-large-practice.in","r");
    //infp=fopen("example.txt","r");
    outfp=fopen("out.txt","w");

    fscanf(infp,"%d%d%d\n",&L,&D,&N);
    for(int i=0; i<D; i++) {
        for(int j=0; j<L; j++) {
            fscanf(infp,"%c\n",&word[i][j]);
        }

    }
    for(int i=0; i<N; i++) {

        fscanf( infp,"%s",pattern);
        length = strlen(pattern);
        memset(pk,0,sizeof(pk));
        memset(pk_size,0,sizeof(pk_size));
        memset(mattrix,0,sizeof(mattrix));

        int j=0;
        int k=0;
        while(j<length) {
            int num=0;
            if(!state) {
                if(pattern[j] =='(') {
                    state = true;
                } else {
                    pk[k][pk_size[k]++] = pattern[j];
                    k++;
                }
                j++;

            } else {

                if(pattern[j] == ')') {
                    state = false;
                    k++;
                } else {
                    pk[k][pk_size[k]++] = pattern[j];
                }
                j++;
            }
        }
        count = 0;
        //backtrack(0);
        //	printf("Case #%d: %d\n",i+1,count);
        //	fprintf(outfp,"Case #%d: %d\n",i+1,count);
        traversal();
        //	printf("Case #%d: %d\n",i+1,count);
        fprintf(outfp,"Case #%d: %d\n",i+1,count);
    }
    fclose(infp);
    fclose(outfp);
    printf("complete");
    getch();

    return 0;
}