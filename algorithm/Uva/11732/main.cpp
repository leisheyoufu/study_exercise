#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>

using namespace std;
#define MAXN 4000010
#define MAXLEN 1010


long long answer;

struct Trie{
	int next[MAXN];
	int head[MAXN];
	char ch[MAXN];
	int val[MAXN];
	int flag[MAXN];
	int sz;

	void clear()
	{
		answer = 0;
		sz=1;
		val[0] = 0;
		flag[0] = head[0] = next[0] = 0;
	}

	void insert(char *s)
	{
		answer+=val[0];
		val[0]++;
		int i,u,v,n;
		n = strlen(s);
		u=0;
		for(i=0;i<n;i++)
		{
			bool found = false;
			for(v= head[u];v!='\0'; v = next[v])
			{
				if(ch[v] == s[i])
				{
					found = true;
					break;
				}
			}
			if(!found)
			{
				v = sz++;
				val[v] = 0;
				flag[v] = 0;
				ch[v] = s[i];
				next[v] = head[u];
				head[u] = v;  // u的子节点
				head[v] = 0;
			}
			u=v;
			answer+=val[u]*2;
			val[u]++;
		}
		if(flag[v])
		{
			answer+=flag[v];
		}
		flag[v]++;
	}
		

};

struct Trie tree;
char word[MAXLEN];
int main()
{
	int q = 0;
	int n;
    //freopen("test.txt","r",stdin);	
	while( scanf("%d",&n)==1 &&n){
		tree.clear();
		for(int i=0;i<n;i++)
		{
			scanf("%s",word);			
			tree.insert(word);
		}
		printf("Case %d: %lld\n",++q,answer);

	}
	
    return 0;
}
