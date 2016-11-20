#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<algorithm>

int d[100][100];

int dis(char *s1, char* s2)
{
    int l1=strlen(s1);
    int l2=strlen(s2);
    for(int i=0; i<l1; i++) {
        d[i][0] = i;
    }
    for(int j=0; j<l2; j++) {
        d[j][0] = j;
    }

    for(int i=1; i<=l1; i++) {
        for(int j=1; j<=l2; j++) {
            if(s1[i-1] == s2[j-1]) {
                d[i][j] = d[i-1][j-1];
            } else if(d[i-1][j-1] < d[i-1][j] && d[i-1][j-1] < d[i][j-1]) {
                d[i][j] = d[i-1][j-1] + 1;
            } else if(d[i][j-1]<d[i-1][j]) {
                d[i][j] = d[i][j-1] +1;
            } else {
                d[i][j] = d[i-1][j] +1;
            }
        }
    }
    return d[l1][l2];
}

int main()
{
    char *str1 = "sailn";
    char *str2 = "failing";
    printf("%d\n", dis(str1,str2));
    getch();
    return 0;
}
