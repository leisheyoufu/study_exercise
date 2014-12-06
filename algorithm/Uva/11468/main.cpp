#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define PATTERN_LEN 25
#define SIGMASIZE 256
#define MAXNODE 5632
int charactor[111];
double prob[111];

int len,c_sz;
int vis[MAXNODE][111];
double d[MAXNODE][111];

struct AhoCorsickAutomata {
    int sz;
    int ch[MAXNODE][SIGMASIZE];
    int f[MAXNODE];
    int val[MAXNODE];

    void init () {
        sz = 1;
		val[0] =0;
        memset(ch[0],0,sizeof(ch[0]));
    }


    void insert(char *s, int v) {
        int u=0,n=strlen(s);
        for(int i=0; i<n; i++) {
            int c=s[i];
            if(!ch[u][c]) {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = 1;   // 该pattern 完全匹配后置位
    }

    void getFail() {
        queue<int> q;
        f[0] =0;
        for(int c=0; c<SIGMASIZE; c++) {
            int u=ch[0][c]; // 从trie 树根节点开始找
            if(u) {
                f[u]=0;
                q.push(u);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(int c=0; c<SIGMASIZE; c++) {
                int v=ch[u][c];
                if(!v) {
                    ch[u][c] = ch[f[u]][c];
                    continue;
                }
                q.push(v);
                int j=f[u];
                while( j && !ch[j][c]) {
                    j=f[j];
                }
                f[v]= ch[j][c];
                val[v] |=val[f[v]];
            }
        }
    }

    double get_prob(int u,int l) {
        if(!l) {
            return 1;
        }
        if(vis[u][l]) {
            return d[u][l];
        }
        vis[u][l] =1;
        double &ans = d[u][l];
        ans = 0;
        for( int i=0; i<c_sz; i++) {
            if(!val[ch[u][charactor[i]]]) {
                ans += prob[i]*get_prob(ch[u][charactor[i]],l-1);
            }
        }
        return ans;
    }
};

AhoCorsickAutomata ac;


int main()
{
    char str[PATTERN_LEN];
    //freopen("test.txt","r",stdin);
    int T;
    scanf("%d",&T);
    int k=0,p;;  // case, patterm. charactor
    for(int k=1; k<=T; k++) {
        ac.init();
        scanf("%d",&p);
        for(int i=0; i<p; i++) {
            scanf("%s",str);
            ac.insert(str,i);
        }
        scanf("%d",&c_sz);
		char s[2];
        for(int i=0; i<c_sz; i++) {            
            scanf("%s %lf",s,&prob[i]);
            charactor[i]=s[0];
        }

        scanf("%d",&len);
        ac.getFail();
        memset(vis,0,sizeof(vis));
        printf("Case #%d: %.6f\n", k,ac.get_prob(0,len));
    }
	
    return 0;
}
