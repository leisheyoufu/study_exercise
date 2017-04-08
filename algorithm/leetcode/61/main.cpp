/*
61. Rotate List

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

Subscribe to see which companies asked this question.
*/
#include<iostream>
#include<string>
#include<vector>
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
    int length(ListNode *head)
    {
        int len = 0;
        while(head!=NULL) {
            head = head->next;
            len++;
        }
        return len;
    }
    ListNode* findKRight(ListNode *head, int k)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        int len = length(head);
        k = k % len;
        int count = k;
        while(fast!=NULL && count) {
            fast = fast->next;
            count --;
        }
        if(count> 0) {
            return NULL; // CL: can not reach
        }
        if(fast == NULL) {
            return NULL;
        }
        while(fast->next !=NULL) {
            slow = slow ->next;
            fast = fast ->next;
        }
        return slow;
    }


    ListNode* rotateRight(ListNode* head, int k)
    {
        if (head==NULL) {
            return head;
        }
        ListNode *curr;
        if( (curr= findKRight(head, k)) == NULL) {
            return head;
        }
        ListNode *temp =curr;
        while(temp->next) {
            temp= temp->next;
        }
        temp->next = head;
        ListNode *ret = curr->next;
        curr->next = NULL;
        return ret;
    }

};
int main()
{
    Solution sln;
    ListNode n1(1);
    ListNode n2(2);
    n1.next = &n2;
    sln.rotateRight(&n1, 3);
    system("pause");
    return 0;
}
