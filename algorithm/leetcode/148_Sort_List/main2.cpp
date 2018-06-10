/*
148. Sort List

Sort a linked list in O(n log n) time using constant space complexity.

Example 1:

Input: 4->2->1->3
Output: 1->2->3->4
Example 2:

Input: -1->5->3->4->0
Output: -1->0->3->4->5
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
    ListNode* getMiddle(ListNode* head)
    {
        if(!head) {
            return NULL;
        }
        ListNode *fast = head, *slow = head, *prev;
        while(fast) {
            fast = fast->next;
            if(fast) {
                fast = fast->next;
            } else {
                break;
            }
            prev = slow;
            slow = slow->next;
        }
        prev->next = NULL;  // cut
        return slow;
    }

    ListNode* mergeList(ListNode* head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode *middle = getMiddle(head);
        ListNode *left = mergeList(head);
        ListNode *right = mergeList(middle);
        ListNode dummy(-1);
        head = &dummy;
        while(left || right) {
            if(!right) {
                head->next = left;
                left = left->next;
            } else if(!left) {
                head->next = right;
                right = right->next;
            } else if(left->val < right->val) {
                head->next = left;
                left = left->next;
            } else {
                head->next = right;
                right = right->next;
            }
            head= head->next;
        }
        return dummy.next;
    }
    ListNode* sortList(ListNode* head)
    {
        return mergeList(head);
    }
};
int main()
{
    Solution sln;
    ListNode l1(3);
    ListNode l2(1);
    ListNode l3(2);
    l1.next = &l2;
    l2.next = &l3;
    ListNode *l4 = sln.sortList(&l1);
    system("pause");
    return 0;
}
