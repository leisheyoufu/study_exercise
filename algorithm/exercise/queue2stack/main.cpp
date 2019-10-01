#include<algorithm>
#include<stdlib.h>
#include <conio.h>
#include<queue>

using namespace std;

struct Stack {
    queue<int> q1;
    queue<int> q2;

    void push(int val)
    {
        queue<int> *temp;
        if(q1.size() == 0 && !q2.empty()) {
            temp = &q2;
        } else if (!q1.empty() && q2.empty()) {
            temp = &q1;
        } else {
            temp = &q1;
        }
        temp->push(val);
    }

    int pop()
    {
        queue<int> *temp, *empty;
        if(q1.size() == 0 && q2.size() !=0) {
            empty = &q1;
            temp = &q2;
        } else if(q2.size() ==0 && q1.size() !=0) {
            empty = &q2;
            temp= &q1;
        } else {
            return NULL;
        }
        int val = temp->front();
        temp->pop();
        while(temp->size()!=0) {
            empty->push(val);
            val = temp->front();
            temp->pop();
        }
        return val;
    }
};

int main()
{
    int data[] = { 1,2, 3,4,5,6,7,8,100,300};
    struct Stack s;
    for(int i=0; i<sizeof(data)/sizeof(int); i++) {
        s.push(data[i]);
    }
    int val = s.pop();
    while(val !=NULL) {
        printf("%d ", val);
        val = s.pop();
    }
    printf("\n");

    getch();
    return 0;
}
