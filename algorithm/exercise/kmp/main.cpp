#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<algorithm>

int f[100];
char *pattern ="abc";
char *str="uioooabc01ab";


void get_fail(char *P, int *f)
{
    int len=strlen(P);
    f[0]= 0;
    f[1] = 0;
    for(int i=1; i<len; i++) {
        int j = f[i];
        while(j &&  (P[i] != P[j])) {
            j=f[j];
        }
        f[i+1] = (P[i] == P[j])? j+1:0;
    }
}

int find(char *T, char* P, int *f)
{
    int n = strlen(T), m =strlen(P);
    get_fail(P, f);
    int j=0;
    for(int i=0; i<n; i++) {
        while(j && T[i] !=P[j]) {
            j=f[j];
        }
        if(T[i] == P[j]) {
            j++;
        }
        if(j== m) {
            return i-m+1;
        }
    }
    return -1;
}



int main()
{
    int pos = find(str, pattern,f);
    printf("%d\n", pos);
    getch();
    return 0;
}
