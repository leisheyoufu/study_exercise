/*
Remove Nth Node From End of List

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
    /*
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (n==0) {
            return head;
        }
        ListNode *fast = head, *slow = head;
        int i =0;
        while(i<n) {
            fast = fast ->next;
            i++;
            if (fast == NULL) {
                break;
            }
        }
        if(fast == NULL) {
            head = head->next;
            return head;
        }
        while(fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *temp = slow->next->next;
        slow->next = temp;
        return head;
    }
    */
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (n <=0) {
            return head;
        }
        ListNode *slow = head, *fast = head;
        ListNode dummy(0);
        dummy.next = head;
        ListNode *prev = &dummy;
        int k = 0;
        while(fast && k<n) {
            fast = fast->next;
            k++;
        }
        if (k<n) {
            return head->next;
        }
        while(fast) {
            fast = fast->next;
            slow = slow->next;
            prev = prev->next;
        }
        if (prev->next == head) {
            return head->next;
        }
        prev->next = slow->next;
        return head;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
