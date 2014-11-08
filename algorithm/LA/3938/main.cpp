#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>


using namespace std;
#define MAXN 500010
#define MAXTREENODE 1000010

long long prefix[MAXN];
int ql,qr;
typedef pair<int,int> Interval;

long long sum(int a, int b)
{
    return prefix[b]-prefix[a-1];
}

Interval more(Interval a, Interval b)
{
    long long v1,v2;
    v1 = sum(a.first,a.second);
    v2 = sum(b.first,b.second);
    if(v1 ==v2) {
        return a<b? a:b;
    }
    return v1>v2? a:b;
}



struct IntervalTree {
    int max_prefix[MAXTREENODE];
    int max_suffix[MAXTREENODE];
    Interval max_sub[MAXTREENODE];

    void build(int o,int l, int r) {
        if(l==r) {
            max_prefix[o] = max_suffix[o]= l;
            max_sub[o]=make_pair(l,l);
        } else {
            int m = (l+r)/2;
            int lc = o*2;
            int rc = o*2+1;
            build(lc,l,m);
            build(rc,m+1,r);
            // prefix
            long long v1=sum(l,max_prefix[lc]);
            long long v2=sum(l,max_prefix[rc]);
            if(v1==v2) {
                max_prefix[o] = min(max_prefix[lc],max_prefix[rc]);
            } else {
                max_prefix[o] = v1>v2?max_prefix[lc]:max_prefix[rc];
            }
            // suffix
            v1 = sum(max_suffix[lc],r);
            v2 = sum(max_suffix[rc],r);
            if(v1 == v2) {
                max_suffix[o] = min(max_suffix[lc],max_suffix[rc]);
            } else {
                max_suffix[o] = v1>v2?max_suffix[lc]:max_suffix[rc];
            }
            // sub
            max_sub[o] = more(max_sub[lc],max_sub[rc]);
            max_sub[o] = more(max_sub[o],make_pair(max_suffix[lc],max_prefix[rc]));  // 左子树后缀靠左，右子树前缀和靠右，取中间部分最大
        }
    }
    Interval query_prefix(int o,int l, int r) { // 前缀是左边序号不变
        if(max_prefix[o]<=qr) { // 最大前缀序号小于被查询右端
            return make_pair(l,max_prefix[o]);
        }
        int m = (l+r)/2;
        int lc = o*2;
        int rc = o*2+1;
        if(qr <= m) { // 被查询序号仅在左边
            return query_prefix(lc,l,m);
        }
        Interval temp = query_prefix(rc,m+1,r); // 找到右子树的右端
        temp.first = l;
        return more(temp,make_pair(l,max_prefix[lc]));  // 和仅在左子树比较
    }
    Interval query_suffix(int o,int l,int r) {
        if(max_suffix[o]>= ql) {
            return make_pair(max_suffix[o],r);
        }
        int m = (l+r)/2;
        int lc = o*2;
        int rc = o*2+1;
        if( ql > m) {
            return query_suffix(rc,m+1,r);
        }
        Interval temp = query_suffix(lc,l,m);
        temp.second = r;
        return more(temp,make_pair(max_suffix[rc],r));
    }

    Interval query(int o, int l,int r) {
        if(ql <=l && qr >=r) {
            return max_sub[o];
        }
        int m = (l+r)/2;
        int lc = o*2;
        int rc = o*2+1;
        if(qr <=m) {
            return query(lc,l,m);
        }
        if( ql > m) {
            return query(rc,m+1,r);
        }
        Interval t1 = query_prefix(rc,m+1,r);  // 右子树前缀
        Interval t2 = query_suffix(lc,l,m); // 左子树后缀
        Interval t3 = more(query(lc,l,m),query(rc,m+1,r));  // 选左子树或右子树的结果范围
        return more(make_pair(t2.first,t1.second),t3);   // 比较公共部分和前面的t3 结果
    }
};
IntervalTree tree;
int main()
{
    int n,m;
    int k=0;
    //freopen("test.txt","r",stdin);
    while( scanf("%d%d",&n,&m) == 2) {
        int i;
        int val;
        prefix[0] = 0;
        Interval answer;
        for(i=1; i<=n; i++) {
            scanf("%d",&val);
            prefix[i] = prefix[i-1]+val;
        }
        tree.build(1,1,n);
        printf("Case %d:\n",++k);
        for(i=1; i<=m; i++) {
            scanf("%d%d",&ql,&qr);
            answer = tree.query(1,1,n);
            printf("%d %d\n",answer.first,answer.second);
        }

    }
    return 0;
}
