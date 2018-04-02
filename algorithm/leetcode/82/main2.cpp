/*
82. Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode dummy(-1);
        ListNode *prev = &dummy;
        dummy.next = NULL;
        int val = head->val;
        while(head) {
            if(head->next && head->next->val == val) {
                head = head->next->next;
                while(head) {
                    if (head->val != val) {
                        val = head->val;
                        break;
                    }
                    head = head->next;
                }
            } else {
                prev->next = head;
                head = head->next;
                if(head) {
                    val = head->val;
                }
                prev =prev->next;
            }
        }
        if(!head) {
            prev->next = NULL;
        }
        return dummy.next;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
