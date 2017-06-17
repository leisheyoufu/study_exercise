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
        if(!head) {
            return head;
        }
        ListNode *prev = head;
        head = head->next;
        if(!head || head->val != prev->val) {
            head = prev;
        } else {
            while(head) {
                if(prev->val != head->val) {
                    if(head->next && head->next->val != head->val) {
                        break;
                    } else if (!head->next) {
                        break;
                    }
                }
                if (prev->val == head->val && !head->next) {
                    return NULL;
                }
                prev = head;
                head = head->next;
            }
        }
        ListNode *new_head = head;
        prev = head;
        ListNode *curr = head;
        head = head->next;
        while(head) {
            if( prev->val !=head->val) {
                if( !head->next || head->next->val != head->val) {
                    curr->next = head;
                    curr = head;
                }
            }
            prev = head;
            head = head->next;
        }
        curr->next = NULL;
        return new_head;
    }
    // important solution with two pointer
    ListNode *deleteDuplicates2(ListNode *head)
    {
        ListNode **runner = &head;

        if(!head || !head->next)return head;

        while(*runner) {
            if((*runner)->next && (*runner)->next->val == (*runner)->val) {
                ListNode *temp = *runner;
                while(temp && (*runner)->val == temp->val)
                    temp = temp->next;

                *runner = temp;
            } else
                runner = &((*runner)->next);
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
