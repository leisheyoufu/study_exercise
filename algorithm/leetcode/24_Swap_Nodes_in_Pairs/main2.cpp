/*
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

For example,
Given 1->2->3->4, you should return the list as 2->1->4->3.

Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed.
*/
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
// CL: last solution is better
class Solution
{
public:
    ListNode* swapPairs(ListNode* head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode *newHead = head->next;
        ListNode *temp = newHead->next;
        newHead->next = head;
        head->next = swapPairs(temp);
        return newHead;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
