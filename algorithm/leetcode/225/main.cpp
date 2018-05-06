/*
225. Implement Stack using Queues

mplement the following operations of a stack using queues.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
empty() -- Return whether the stack is empty.
Notes:
You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue.
You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
*/
#include<iostream>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

class MyStack
{
private:
    queue<int> q1;
    queue<int> q2;
    int t;
public:
    /** Initialize your data structure here. */
    MyStack()
    {

    }

    /** Push element x onto stack. */
    void push(int x)
    {
        if(q1.size() > 0) {
            q1.push(x);
        } else {
            q2.push(x);
        }
        t = x;
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        queue<int> *outQ, *inQ;
        if(q1.size() > 0) {
            outQ = &q1;
            inQ = &q2;
        } else if(q2.size()>0) {
            outQ = &q2;
            inQ = &q1;
        } else {
            return 0;
        }
        while(outQ->size() > 1) {
            int val = outQ->front();
            outQ->pop();
            inQ->push(val);
            t = val;
        }
        int val = outQ->front();
        outQ->pop();
        return val;
    }

    /** Get the top element. */
    int top()
    {
        return t;
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        return q1.size() ==0 && q2.size() == 0;
    }
};

int main()
{
    system("pause");
    return 0;
}
