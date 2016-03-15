#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int a[18][18], b[18][18];

int N;
int count = 0;
int max_num = 1000000;

int check(int s);

int run()
{
    int cnt= max_num;
    for(int i=0; i< (1<<N); i++) {
        int temp = check(i);
        if(temp != -1) {
            cnt = min(temp, cnt);
        }
    }
    return cnt;
}

int check(int s)
{
    int cnt = 0;
    memset(b,0,sizeof(b));
    for(int i=0; i<N; i++) {
        if( (1 << i) & s) {
            b[0][i] = 1;
        }
        if( a[0][i] == 1 && b[0][i] == 0) {
            return -1;
        }
    }
    int sum = 0;
    for(int x= 1; x<N; x++) {
        for(int y=0; y<N; y++) {
            sum = 0;
            if( y+1 <N) {
                sum += b[x-1][y+1];
            }
            if(y>0) {
                sum +=b[x-1][y-1];
            }
            if(x>1) {
                sum +=b[x-2][y];
            }
            if(sum %2 !=0) {
                b[x][y] = 1;
            }
        }
    }

    /*	for(int y=0;y<N;y++) {
    		sum = 0;
    		sum = b[N-2][y];
    		if( y+1 <N) {
    			sum +=b[N-1][y+1];
    		}
    		if(y>0) {
    			sum +=b[N-1][y-1];
    		}
    		if(sum %2 != -1) {
    			return -1;
    		}
    	}
    	*/

    for(int x=0; x<N; x++) {
        for(int y=0; y<N; y++) {
            if(a[x][y] ==1&& b[x][y] == 0) {
                return -1;
            }
            if(a[x][y] == 0 && b[x][y] == 1) {
                cnt++;
            }
        }
    }
    return cnt;
}


int main()
{
    //freopen("test.txt","r",stdin);
    int T;
    scanf("%d",&T);
    for(int k=0; k<T; k++) {
        scanf("%d",&N);
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        int d = run();
        if(d == 1000000) {
            d= -1;
        }
        printf("Case %d: %d\n", k+1, d);
    }
    return 0;
}
