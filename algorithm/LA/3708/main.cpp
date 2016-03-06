#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

int n,m;
double pos;

int main()
{
    // freopen("test.txt","r",stdin);
    
    while( scanf("%d %d",&n,&m) ==2) {       
		double ans = 0.0;
		for(int i=1;i<n;i++) {
			pos = (double) i /n *(n+m);
			ans += fabs(pos- floor(pos+0.5)) / (n+m); 
		}
        printf("%.4lf\n", ans * 10000);
    }
    
    return 0;
}
