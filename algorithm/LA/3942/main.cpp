#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
using namespace std;

#define MAXNODE 500000
#define SIGMASIZE 26
#define mod 20071027

int dp[MAXNODE];
char str[MAXNODE];
char word[MAXNODE];

struct Trie {
    int ch[MAXNODE][SIGMASIZE];
    int val[MAXNODE];
    int sz;
    Trie():sz(1) {
        memset(ch[0],0,sizeof(ch[0]));
    }
    void reset() {
        memset(ch,0,sizeof(ch));
        memset(val,0,sizeof(val));
        sz =1;
    }

    int idx(char c) {
        return c-'a';
    }

    void insert(char *s,int v) {
        int u=0,i;
        for( i =0; i<strlen(s); i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] =0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] =v;
    }

    int find(char *s, int a) {
        int i,u=0,ret = 0;
        for(i=a; s[i]; i++) { // 从字符串的后缀开始查找,trie 字典中应包含这个后缀
            int c = idx(s[i]);
            if( !ch[u][c] ) {
                return ret;
            }
            u = ch[u][c];
            if( val[u]) { // 查询到填入字典的单词
                ret += dp[i+1];
                ret %= mod;
            }
        }
        return ret;
    }
};
struct Trie tree;

int main()
{
    int n,m,i;
    int k=0,q=0;

    //freopen("test.txt","r",stdin);
    while( scanf("%s",str) != EOF) {
        tree.reset();
        memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        for( i =0; i<n; i++) {
            scanf("%s",word);
            tree.insert(word,1);
        }
        dp[strlen(str)] = 1;
        for( i=strlen(str)-1; i>=0; i--) {
            dp[i] = tree.find(str,i);
        }
        printf("Case %d: %d\n",++q,dp[0]);

    }

    return 0;
}
