/*
Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.
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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode *head = NULL, *temp = NULL;
        if(l1 && l2) {
            if(l1->val < l2->val) {
                head = l1;
                l1 = l1->next;
            } else {
                head = l2;
                l2 = l2->next;
            }
        } else if(!l1) {
            return l2;
        } else if(!l2) {
            return l1;
        }
        temp = head;
        while(l1!=NULL || l2!=NULL) {
            if(!l1) {
                temp->next = l2;
                return head;
            }
            if(!l2) {
                temp->next = l1;
                return head;
            }
            if(l1->val <l2->val) {
                temp->next = l1;
                l1 = l1->next;
            } else {
                temp->next = l2;
                l2 = l2->next;
            }
            temp = temp->next;
        }
        return head;
    }
};
