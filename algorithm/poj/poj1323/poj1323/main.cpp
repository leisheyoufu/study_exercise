#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>
#include <queue>
using namespace std;
#define MAX_NUM 100000
int card[MAX_NUM];
int T, N,M;

bool exist(int num)
{
    for(int i=1; i<=M; i++) {
        if(card[i] == num)
            return true;
    }
    return false;
}



void stat(priority_queue<int> q)
{
    int count = 0;
    int num = N*M;
    for(int i=num; i>=1; i--) {
        if(q.size() ==0)
            break;
        if(q.top() >= i) { // ÿ��ȡ����һ����������������в������ľͲ���ʣ����ʱ�Ƴ��Լ���ǰ���ģ����������ٵ�����
            count ++;
            q.pop();
        }

        if(exist(i)) {
            continue;
        }

        q.pop();
    }
    printf("Case %d: %d\n",T,count);
}


int main()
{
//	freopen("test.txt","r+",stdin);
    while(scanf("%d %d",&N,&M) == 2 &&N &&M) {
        priority_queue<int> q;
        for(int i=1; i<=M; i++) {
            scanf("%d",&card[i]);
            q.push(card[i]);
        }
        T++;
        stat(q);
        scanf("\n");

    }
    //getch();
    return 0;
}
