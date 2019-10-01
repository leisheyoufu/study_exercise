#include <stdio.h>
//#include <conio.h>
#include <queue>
#include <algorithm>

using namespace std;
#define SIZE 1000
int n1,n2,n3;
int T;

struct cmp {
    bool operator()(int x,int y)
    {
        return x>y;
    }
};
priority_queue<int,vector<int>,cmp> q[3];
void clear(priority_queue<int,vector<int>,cmp> *q)
{
    int size = q->size();
    for(int i=0; i<size; i++) {
        q->pop();
    }
}
void init(priority_queue<int,vector<int>,cmp> *q,int n)
{
    for(int i=0; i<n; i++) {
        q->push(7*60);
    }
}

bool push(priority_queue<int,vector<int>,cmp> *q,int time)
{
    if(q->top() - time >30) {
        return false;
    } else if(q->top()-time <=0) {
        q->pop();
        q->push(time+30);
        return true;
    } else {
        int dif = q->top() - time;
        q->pop();
        q->push(time + dif+30);
        return true;
    }
}

int enqueue(int time,int num)
{
    int ret=0;
    switch(num) {
    case 1:
    case 2:
        if(push(&q[0],time))
            ret+=num;
        break;
    case 3:
    case 4:
        if(push(&q[1],time))
            ret+=num;
        break;
    case 5:
    case 6:
        if(push(&q[2],time))
            ret+=num;
        break;
    }
    return ret;
}


int main()
{
//	freopen("test.txt","r",stdin);
    while (scanf("%d %d %d",&n1,&n2,&n3) && n1 &&n2 && n3) {
        clear(&q[0]);
        clear(&q[1]);
        clear(&q[2]);


        init(&q[0],n1);
        init(&q[1],n2);
        init(&q[2],n3);

        int h,m;
        int num;
        int count = 0;
        while (scanf("%d",&h)) {
            scanf(":%d %d\n",&m,&num);
            int time = h*60+m;
            count +=enqueue(time,num);

        }
        char temp;
        scanf("%c",&temp);
        printf("%d\n",count);
    }


//	getch();
    return 0;
}