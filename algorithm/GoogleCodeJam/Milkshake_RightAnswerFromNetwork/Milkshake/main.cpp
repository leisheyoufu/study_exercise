
#include <string>   
#include <cmath>   
#include <queue>   
#include <algorithm>   
#include <iostream>   
#define PI 3.14159265358979323846264338327950288   
#define _clr(a,b) memset(a,b,sizeof(a))   
template<class T> T _abs(T a)  
{if(a<0) a=-a;return a;}  
template<class T> void Get_Min(T& a,T b)  
{ if(a>b) a=b;}  
template<class T> void Get_Max(T& a,T b)  
{ if(a<b) a=b;}  
using namespace std;  
int cnt[2005];  
struct node  
{  
    int n,malted;  
}flavor[2005][2005];  
bool malted[2005];  
int main()  
{  
    freopen("B-small-practice.in","r",stdin);  
    freopen("out.txt","w",stdout);  
    int T,num_customer,num_milk;  
    scanf("%d",&T);  
    for(int t=1;t<=T;t++)  
    {  
        scanf("%d%d",&num_milk,&num_customer);  
        _clr(flavor,-1);  
        _clr(malted,false);  
        for(int i=0;i<num_customer;i++)  
        {  
            scanf("%d",&cnt[i]);  
            int temp;  
            for(int j=0;j<cnt[i];j++)  
            {  
                scanf("%d%d",&flavor[i][j].n,&flavor[i][j].malted);  
                flavor[i][j].n--;  
            }  
        }  
        bool finished=false;  
        bool satisfy=true;  
        while(!finished)  
        {  
            finished=true;  
            for(int i=0;i<num_customer;i++)  
            {  
                int k=-1;  
                int j;  
                for(j=0;j<cnt[i];j++)  
                {  
                    if(flavor[i][j].malted==1)   
              
					{  
                        if(malted[flavor[i][j].n]==true) break;  
                        k=flavor[i][j].n;  
                    }  
                    else  
                    {  
                        if(malted[flavor[i][j].n]==false) break;  
                    }  
                }  
                if(j==cnt[i])  
                {  
                    if(k<0)  
                    {  
                        finished=true;  
                        satisfy=false;  
                        break;  
                    }  
                    else  
                    {  
                        malted[k]=true;  
                        finished=false;  
                    }  
                }  
            }  
        }  
        printf("Case #%d: ",t);  
        if(satisfy==true)  
        {  
            if(malted[0]) printf("%d",1);  
            else printf("%d",0);  
            for(int i=1;i<num_milk;i++)  
            {  
                if(malted[i]) printf(" %d",1);  
                else printf(" %d",0);  
            }  
            printf("\n");  
        }  
        else printf("IMPOSSIBLE\n");  
    }  
    return 0;  
}  
