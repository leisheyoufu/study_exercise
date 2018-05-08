/*
232. Implement Queue using Stacks

Implement the following operations of a queue using stacks.

push(x) -- Push element x to the back of queue.
pop() -- Removes the element from in front of queue.
peek() -- Get the front element.
empty() -- Return whether the queue is empty.
Notes:
You must use only standard operations of a stack -- which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, stack may not be supported natively. You may simulate a stack by using a list or deque (double-ended queue), as long as you use only standard operations of a stack.
You may assume that all operations are valid (for example, no pop or peek operations will be called on an empty queue).
*/
#include<iostream>
#include<string>
#include<stack>
#include<algorithm>

using namespace std;

class MyQueue
{
private:
    stack<int> inS;
    stack<int> outS;
public:
    /** Initialize your data structure here. */
    MyQueue()
    {

    }

    /** Push element x to the back of queue. */
    void push(int x)
    {
        inS.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop()
    {
        if(!outS.empty()) {
            int val = outS.top();
            outS.pop();
            return val;
        }
        while(!inS.empty()) {
            int val = inS.top();
            outS.push(val);
            inS.pop();
        }
        if(!outS.empty()) {
            int val = outS.top();
            outS.pop();
            return val;
        }
        return 0;
    }

    /** Get the front element. */
    int peek()
    {
        if(!outS.empty()) {
            return outS.top();
        }
        while(!inS.empty()) {
            int val = inS.top();
            outS.push(val);
            inS.pop();
        }
        if(!outS.empty()) {
            return outS.top();
        }
        return 0;
    }

    /** Returns whether the queue is empty. */
    bool empty()
    {
        return outS.empty() && inS.empty();
    }
};

int main()
{
    system("pause");
    return 0;
}
