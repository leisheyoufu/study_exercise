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
    ListNode* sortList(ListNode* head)
    {
        if(head == NULL || head->next == NULL) {
            return head;
        }
        ListNode *s = head;
        ListNode *mid = middle(head);
        s = sortList(s);
        mid = sortList(mid);
        return merge(s,mid);
    }

    ListNode *merge(ListNode *s, ListNode *mid)
    {
        ListNode *r, *temp;
        if(s->val< mid->val) {
            r = s;
            s = s->next;
        } else {
            r = mid;
            mid = mid->next;
        }
        temp = r;
        while(s || mid) {
            if(s == NULL) {
                r->next = mid;
                break;
            } else if(mid == NULL) {
                r->next = s;
                break;
            } else if(s->val < mid->val) {
                r->next = s;
                s = s->next;
            } else {
                r->next = mid;
                mid = mid->next;
            }
            r= r->next;
        }
        return temp;
    }

    ListNode *middle(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        while(fast != NULL) {
            fast = fast->next;
            if(fast) {
                fast = fast->next;
            } else {
                break;
            }
            if(fast) { // very important
                slow = slow->next;
            }
        }
        ListNode *temp = slow->next;
        slow->next = NULL; // cut
        return temp;
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
