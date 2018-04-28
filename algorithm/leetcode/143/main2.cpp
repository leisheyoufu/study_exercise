/*
143. Reorder List

Given a singly linked list L: L0��L1������Ln-1��Ln,
reorder it to: L0��Ln��L1��Ln-1��L2��Ln-2����

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    void reorderList(ListNode* head)
    {
        if(!head) {
            return;
        }
        stack<ListNode*> s;
        ListNode *curr = head;
        while(curr) {
            s.push(curr);
            curr = curr->next;
        }
        curr = head;
        ListNode *tail = s.top();
        s.pop();
        while(curr != tail) {
            ListNode *temp = curr->next;
            curr->next = tail;
            tail->next = temp;
            curr = temp;
            if(curr == tail) {
                break;
            }
            tail = s.top();
            s.pop();
        }
        tail->next = NULL;
    }
};
int main()
{
    Solution sln;
    ListNode t1(1);
    ListNode t2(2);
    ListNode t3(3);
    ListNode t4(4);
    t1.next = &t2;
    t2.next = &t3;
    t3.next = &t4;
    sln.reorderList(&t1);
    system("pause");
    return 0;
}
