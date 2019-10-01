#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>

using namespace std;

#define STR_NUM 105
#define STR_LEN 1005
#define MAXN 200000

int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN];
int n, len;
int s[MAXN];
char str[STR_NUM][STR_LEN];
int h[MAXN];  // h[i]表示后缀i的首字符所属的字符串编号
int flag[STR_NUM];  //  组flag[i]表示编号为i的字符串在该分组中是否出现过
int r[MAXN],height[MAXN];

void build_sa(int * s, int n, int m)
{
    int i, * x = t, * y = t2;
    for(i = 0; i < m; ++i) c[i] = 0;
    for(i = 0; i < n; ++i) c[x[i] = s[i]]++;
    for(i = 1; i < m; ++i) c[i] += c[i - 1];
    for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
    for(int k = 1; k <= n; k <<= 1) {
        int p = 0;
        for(i = n - k; i < n; ++i) y[p++] = i;
        for(i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i] - k;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[y[i]]]++;
        for(i = 1; i < m; ++i) c[i] += c[i - 1];
        for(i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for(i = 1; i < n; ++i)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? p - 1: p++;
        if(p >= n) break;
        m = p;
    }
}

void get_height(int * s, int n)
{
    int i, j, k = 0;
    for(i = 1; i <= n; i++) {
        r[sa[i]] = i;
    }
    for(i = 0; i < n; i++) {
        if(k) {
            k--;
        }
        j = sa[r[i] - 1];
        while(s[i + k] == s[j + k]) k++;
        height[r[i]] = k;
    }
}

bool scan( int p,bool f)
{
    int i=2;
    while(i<=len) {
        int j=i;
        while(j<=len && height[j]>=p) { // height[j] 后缀j 的最大公共字串长度大于 p
            flag[h[sa[j-1]]]=1;
            flag[h[sa[j]]]=1;   // h[sa[j]] 表示后缀j 所在的字符串
            j++;
        }
        int num=0;
        for(int k=0; k<n; k++) {
            if(flag[k]) {
                num++;   // 计算最大公共长度大于 p 的字串数量
            }
        }
        memset(flag,0,sizeof(flag));
        if(num > n/2) {
            if(!f) {
                return true;  // 有答案， 在后面二分答案
            }
            for( int k=sa[j-1],q=0; q<p; k++,q++) {
                printf("%c",s[k]+'a'-1);
            }
            printf("\n");
        }
        i=j+1;
    }
    return false;
}

int main()
{
    bool ss=false;
    // freopen("test.txt","r",stdin);
    while( scanf("%d",&n)==1 &&n) {
        if(ss)
            printf("\n");
        else
            ss= true;
        len =0;
        int i;
        int la=1, ra=0;  // ra 右边界
        for(i=0; i<n; i++) {
            scanf("%s",str[i]);
            int j=0;
            while(true) {
                if(str[i][j] == '\0') {
                    s[len] = 27+i;
                    h[len++] = i;
                    ra = (j>ra)?j:ra;
                    break;
                }
                s[len] = str[i][j] - 'a' +1;
                h[len++] = i;
                j++;
            }
        }

        if(n==1) {
            printf("%s\n",str[0]);
            continue;
        }
        s[len]='\0';
        build_sa(s,len+1,27+n);
        get_height(s,len);
        if( !scan(1,false)) {
            printf("?\n");
            continue;
        }
        while(la < ra) {
            int mid=(la+ra)/2+1;
            if(scan(mid,false)) {
                la = mid;
            } else {
                ra = mid-1;
            }
        }
        scan(la,true);
    }
    return 0;
}
