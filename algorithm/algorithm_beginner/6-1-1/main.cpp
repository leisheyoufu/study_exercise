#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

#define DEFAULT_SIZE	50

class Queue
{
    int *a;
    int size;
    int rear, front;
public:
    Queue(int size);
    ~Queue();
    bool Queue::enqueue(int val);
    bool Queue::dequeue(int &val);
};

Queue::Queue(int sz= DEFAULT_SIZE)
{
    front = 1;
    rear = 0;
    size = sz;
    a = new int[size];
}
Queue::~Queue()
{
    delete []a;
}
bool Queue::enqueue(int val)
{
    if( (rear + size +2) %size ==front)
        return false;
    rear = (rear +1 +size) % size;
    a[rear] = val;
    return true;
}
bool Queue::dequeue(int &val)
{
    if (( front - 1 + size ) %size == rear)
        return false;
    val = a[front];
    front = (front +1 +size) % size;
    return true;
}
int main()
{
    int num;
    freopen("test.txt","r",stdin);
    scanf("%d", &num);
    Queue *q = new Queue();
    for(int i=1; i<=num; i++) {
        q->enqueue(i);
    }
    int val;
    while(q->dequeue(val)) {
        printf("%d ",val);
        if (!q->dequeue(val))
            break;
        q->enqueue(val);
    }
    delete q;
    return 0;
}
