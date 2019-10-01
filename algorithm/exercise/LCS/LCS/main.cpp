#include <stdio.h>
#include <conio.h>
#include <string.h>



int len[15][15];

#define MAX(A,B) ((A)>(B))?(A):(B)

int get_lcs(char *s1,int l1, char *s2, int l2)  // 这个最大公共子序列不一定连续  最大修改次数
{

    for(int i=0; i<l1; i++) {
        len[i][0]=0;
    }
    for(int j=0; j<l2; j++) {
        len[0][j]=0;

    }

    for(int i=1; i<l1; i++) {
        for(int j=1; j<l2; j++) {
            if(s1[i-1]==s2[j-1]) {
                len[i][j]=len[i-1][j-1]+1;
            } else {
                len[i][j]=MAX(len[i-1][j],len[i][j-1]);
            }
        }
    }
    return len[l1-1][l2-1];
}

int common_len(char *a1,char *a2)
{
    int i=0;
    while(*(a1+i)!='\0' || *(a2+i)!='\0') {
        if( *(a1+i)==*(a2+i)) {
            i++;
            continue;
        }
        break;
    }
    return i;
}

int get_common_str(char *a1,char *a2)
{

    int l1=strlen(a1);
    int l2=strlen(a2);
    int max_common=0;
    int start=0;
    for(int i=0; i<l1; i++) {
        for(int j=0; j<l2; j++) {
            int len=common_len(a1+i,a2+j);
            if(len>max_common) {
                start = i;
                max_common=len;
            }
        }
    }
    printf("common str = %s \n",a1+start);
    return max_common;
}


int main()
{
    char *s1="abccade";
    char *s2="dgcadde";
    int l1=strlen(s1);
    int l2=strlen(s2);
    //int len = get_lcs(s1,l1,s2,l2);

    int len= get_common_str(s1,s2);

    printf("len = %d",len);

    getch();
    return 0;
}