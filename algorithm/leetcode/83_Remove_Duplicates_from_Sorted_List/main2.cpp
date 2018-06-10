/*
83. Remove Duplicates from Sorted List

Given a sorted linked list, delete all duplicates such that each element appear only once.

For example,
Given 1->1->2, return 1->2.
Given 1->1->2->3->3, return 1->2->3.
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
        int val = head->val;
        ListNode **entry = &head->next;
        while(*entry) {
            ListNode *curr = *entry;
            if(curr->val == val) {
                *entry = curr->next;
            } else {
                entry = &curr->next;
                val = curr->val;
            }
        }
        return head;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
