#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>
#include <algorithm>
using namespace std;

#define NUM 256
char s[NUM];
int node[NUM];
void read_flag(char *s, char *d)
{
    int t=0;
    while(*(s+t) !=')') {
        d[t] = s[t];
        t++;
    }
    d[t] = '\0';
}

int get_index(char* f)
{
    int index =1;
    int i=0;
    while(f[i]) {
        switch(f[i++]) {
        case 'L':
            index <<= 1;
            break;
        case 'R':
            index = index <<1 |1;
            break;
        }
    }
    return index;
}

void add_node(int val, int index)
{
    node[index] = val;
}

void print()
{
    bool is_tree = true;
    for(int i=1; i<=NUM; i++) {
        if(node[i]) {
            if(i!=1 &&!node[i/2])
                is_tree= false;
        }
    }
    if( is_tree) {
        for(int i=1; i<=NUM; i++) {
            if(node[i]) {
                printf("%d ",node[i]);
            }
        }
    } else
        printf("%d",-1);
}

int main()
{
    int D, I;
    freopen("test.txt","r",stdin);
    while(1) {
        if( scanf("%s",s) !=1)
            break;
        if(!strcmp(s,"()")) {
            print();
            printf("\n");
            memset(node,0,sizeof(node));
            continue;
        }
        int val;
        sscanf(&s[1],"%d", &val);
        char *t = strchr(s,',');
        char f[100];
        read_flag(&t[1],f);
        int index = get_index(f);
        add_node(val, index);
    }
    return 0;
}

