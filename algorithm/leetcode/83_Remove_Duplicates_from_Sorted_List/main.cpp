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
        ListNode **runner = &head;
        if (!head || !head->next) {
            return head;
        }
        while(*runner) {
            ListNode *curr = *runner;
            while(curr->next && curr->val == curr->next->val) {
                curr = curr->next;
            }
            *runner = curr;
            runner = &(curr->next);
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
