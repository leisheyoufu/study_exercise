#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

struct dict {
    char s[100];
    char d[100];
};

void insert_sort(char *src, char *dst)
{
    strcpy(dst,src);

    int len = strlen(dst);
    for(int i=0; i<len; i++) {
        for(int j=len-1; j>i; j--) {
            if(dst[j] < dst[j-1]) {
                swap(dst[j],dst[j-1]);
            }
        }
    }
}

bool find_s(struct dict *d, int n,char *str)
{
    bool find = false;
    for(int i=0; i<n; i++) {
        if(strcmp(d[i].d,str) ==0 ) {
            find = true;
            printf("%s ",d[i].s);
        }
    }
    return find;
}


int main()
{
    char word[100];
    struct dict d[100];
    freopen("test.txt","r",stdin);
    int i=0;
    while(scanf("%s",d[i].s) && strcmp(d[i].s,"******") !=0) {
        insert_sort(d[i].s,d[i].d);
        i++;
    }

    while(scanf("%s", word) != EOF) {
        char w[100];
        insert_sort(word,w);
        if(!find_s(d,i,w))
            printf(":)\n");
        else
            printf("\n");
    }

    return 0;
}
