#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define MAXNODE 20000
#define SIGMASIZE 26
#define TEXTSIZE 1000010

#define PATTERNSIZE 75
#define PATTERNNUM 155


map<string,int> ms;
struct AhoCorsickAutomata {
    int cnt[PATTERNNUM];
    int sz;
    int ch[MAXNODE][SIGMASIZE];
    int f[MAXNODE];
    int val[MAXNODE];
    int last[MAXNODE];

    void init ()
    {
        sz = 1;
        memset(ch,0,sizeof(ch));
        memset(cnt,0,sizeof(cnt));
        ms.clear();
    }

    int idx(char c)
    {
        return c-'a';
    }

    void insert(char *s, int v)
    {
        int u=0,n=strlen(s);
        for(int i=0; i<n; i++) {
            int c=idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;   // 该pattern 完全匹配后置位
        ms[string(s)] =v;
    }

    void print(int j)
    {
        if(j) {
            cnt[val[j]]++;
            print(last[j]);
        }
    }

    void find(char *T)
    {
        int n = strlen(T);
        int j=0;
        for(int i=0; i<n; i++) {
            int c =idx(T[i]);
            while(j && !ch[j][c]) {
                j = f[j];
            }
            j = ch[j][c];
            if(val[j]) {
                print(j);
            } else if(last[j]) {
                print(last[j]);
            }
        }
    }

    void getFail()
    {
        queue<int> q;
        f[0] =0;
        for(int c=0; c<SIGMASIZE; c++) {
            int u=ch[0][c]; // 从trie 树根节点开始找
            if(u) {
                f[u]=0;
                q.push(u);
                last[u] =0;
            }
        }
        while(!q.empty()) {
            int item = q.front();
            q.pop();
            for(int c=0; c<SIGMASIZE; c++) {
                int u=ch[item][c];
                if(!u) {
                    continue;
                }
                q.push(u);
                int v=f[item];
                while( v && !ch[v][c]) {
                    v=f[v];
                }
                f[u]= ch[v][c];
                last[u] =val[f[u]]?f[u]:last[f[u]];
            }
        }
    }
};

AhoCorsickAutomata ac;
char str[TEXTSIZE],p[PATTERNNUM][PATTERNSIZE];

int main()
{
    int n,i;
    int k=0,q=0;

    //freopen("test.txt","r",stdin);
    while( scanf("%d",&n) ==1 && n) {
        ac.init();
        for( i=1; i<=n; i++) {
            scanf("%s",p[i]);
            ac.insert(p[i],i);
        }
        scanf("%s",str);
        ac.getFail();
        ac.find(str);
        int temp = -1;
        for(i=1; i<=n; i++) {
            if(ac.cnt[i]>temp) {
                temp=ac.cnt[i];
            }
        }
        printf("%d\n",temp);
        for(i =1; i<=n; i++) {
            if(ac.cnt[ms[string(p[i])]] == temp) {
                printf("%s\n",p[i]);
            }
        }
    }
    return 0;
}
