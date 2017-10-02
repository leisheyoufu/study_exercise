/*
155. Min Stack
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
Example:
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
*/
#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};
/*

class MinStack
{
	stack<int> s;
	ListNode *head;
public:
    MinStack() {
       head = NULL;
    }

    void push(int x) {
        if(!head) {
			ListNode *temp = new ListNode(x);
			head = temp;
		} else if (head->val >= x) {
			ListNode *temp = new ListNode(x);
			temp->next = head;
			head = temp;
		}
		s.push(x);
    }

    void pop() {
		if (s.empty()) {
			return;
		}
		int val = s.top();
		if (val == head->val) {
			ListNode *temp = head;
			head = head->next;
			delete(temp);
		}
		s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
		return head->val;
    }
};
*/
class MinStack
{
public:
    stack<int> sm;
    stack<int> s;
    void push(int x)
    {
        s.push(x);
        if(sm.empty() || (!sm.empty() && sm.top() >= x)) sm.push(x);
    }

    void pop()
    {
        if(s.top() == sm.top()) sm.pop();
        s.pop();
    }

    int top()
    {
        return s.top();
    }

    int getMin()
    {
        return sm.top();
    }
};

int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin();
    minStack.pop();
    minStack.top();
    cout << minStack.getMin();
    system("pause");
    return 0;
}
