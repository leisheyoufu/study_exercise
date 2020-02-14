/*
19. Remove Nth Node From End of List

Given a linked list, remove the nth node from the end of list and return its head.

For example,

   Given linked list: 1->2->3->4->5, and n = 2.

   After removing the second node from the end, the linked list becomes 1->2->3->5.
Note:
Given n will always be valid.
Try to do this in one pass.
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<cstdlib>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if(n<=0 || !head) {
            return head;
        }
        int slow =0, fast = 0;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *temp = head;
        while(fast <n && temp) {
            temp = temp->next;
            fast++;
        }
        if(fast < n) {
            return head;
        }
        ListNode *curr = head, *prev = &dummy;
        while(temp) {
            temp = temp->next;
            curr = curr->next;
            prev = prev->next;
        }
        prev->next = prev->next->next;
        curr->next = NULL;
        return dummy.next;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
