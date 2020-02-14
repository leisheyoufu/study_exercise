/*
21. Merge Two Sorted Lists

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
        if(!l1 && !l2) {
            return NULL;
        }
        if(!l2) {
            return l1;
        }
        if(!l1) {
            return l2;
        }
        ListNode *ret = new ListNode(0);
        ListNode * curr = ret;
        while(l1 || l2) {
            if(!l2) {
                curr->next = l1;
                return ret->next;
            }
            if(!l1) {
                curr->next = l2;
                return ret->next;
            }
            if(l1->val < l2->val) {
                curr->next = l1;
                l1 = l1->next;
                curr = curr->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
                curr = curr->next;
            }
        }
        return ret->next;
    }
};
