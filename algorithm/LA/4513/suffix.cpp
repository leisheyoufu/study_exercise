#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<string>
#include <map>
#include <queue>
#include <algorithm>


using namespace std;

#define MAXN 40010

int m,n;
char str[MAXN];
int sa[MAXN];
int t[MAXN],t2[MAXN],c[MAXN],r[MAXN],height[MAXN];

void build_sa(int n,int m)
{
    int i,*x=t, *y=t2;

    for (i=0; i<m; i++) c[i]=0;
    for (i=0; i<n; i++) c[x[i]=str[i]]++;
    for (i=1; i<m; i++) c[i]+=c[i-1];
    for (i=n-1; i>=0; i--) sa[--c[x[i]]]=i;
    for (int k=1; k<=n; k<<=1) {
        int p=0;
        for (i=n-k; i<n; i++) y[p++]= i;
        for (i=0; i<n; i++) if (sa[i]>=k) y[p++]=sa[i]-k;
        for (i=0; i<m; i++) c[i]=0;
        for (i=0; i<n; i++) c[x[y[i]]]++;
        for (i=0; i<m; i++) c[i] += c[i-1];
        for (i=n-1; i>=0; i--) sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;
        x[sa[0]]=0;
        for (i=1; i<n; i++)
            x[sa[i]]= y[sa[i-1]]==y[sa[i]] && y[sa[i-1]+k]==y[sa[i]+k] ? p-1:p++;
        if (p>=n) break;
        m=p;
    }
}

void get_height(int n)
{
    int k = 0;
    for (int i=0; i<=n; i++) r[sa[i]]=i;
    for (int i=0; i<n; i++) {
        if (k) k--;
        int j=sa[r[i]-1];
        while (str[i+k]==str[j+k]) k++;
        height[r[i]]=k;
    }
}

bool valid(int ans,bool flag)
{
    int count=0,pre=0,suf=0;
    for(int i=1; i<=n; i++) {
        // ans 代表最长的pattern值
        if(height[i]>=ans) {
            if(!count) {
                count =1;
                pre = max(pre,sa[i-1]);
            }

            count++;
            pre=max(sa[i],pre);
        } else {
            if(count>=m) {
                if(!flag) {
                    return true;
                } else {
                    suf = max(pre,suf);
                }
            }
            count = pre =0;
        }
    }
    if(count >=m) {
        if(!flag) {
            return true;
        } else {
            suf = max(pre,suf);
        }
    }
    if(!flag)
        return false;
    else
        printf("%d %d\n",ans,suf);
    return 0;
}


int main()
{
    int i;
    //freopen("test.txt","r",stdin);
    while( scanf("%d",&m) && m) {
        scanf("%s",str);
        if(m==1) {
            printf("%d 0\n",strlen(str));
            continue;
        }
        for(i=0; str[i]; i++) {
            str[i] = str[i] -'a'+1;
        }
        n=i;
        str[n]='\0';
        build_sa(n+1,27);
        get_height(n);

        if(!valid(1,false)) {
            printf("none\n");
            continue;
        }

        int p=0,q=n+1,mid,ans=1;
        while(p<=q) {
            mid = (p+q)/2;
            if(valid(mid,false)) {
                ans = mid;
                p = mid+1;
            } else {
                q = mid-1;
            }
        }
        valid(ans,true);
    }

    return 0;
}
