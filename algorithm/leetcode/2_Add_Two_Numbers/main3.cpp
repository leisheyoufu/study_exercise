/*
2. Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
*/
#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        if(!l1) {
            return l2;
        }
        if(!l2) {
            return l1;
        }
        ListNode *ret = new ListNode(0);
        ListNode *curr = ret;
        int c = 0, a = 0, b=0, val;
        while(l1 || l2 || c) {
            a = 0;
            b = 0;
            ListNode *temp = new ListNode(0);
            if(l1) {
                a = l1->val;
                l1 = l1->next;
            }
            if(l2) {
                b = l2->val;
                l2 = l2->next;
            }
            val = a + b + c;
            c = val / 10;
            temp->val = val % 10;
            curr->next = temp;
            curr = curr->next;
        }
        return ret->next;
    }
};

int main()
{
    ListNode *a1 = new ListNode(2);
    ListNode *a2 = new ListNode(4);
    ListNode *a3 = new ListNode(3);
    a1->next = a2;
    a2->next = a3;
    ListNode *b1 = new ListNode(5);
    ListNode *b2 = new ListNode(6);
    ListNode *b3 = new ListNode(4);
    b1->next = b2;
    b2->next = b3;
    Solution s;
    ListNode *result = s.addTwoNumbers(a1, b1);
    while (result != NULL) {
        printf("%d ", result->val);
        result = result->next;
    }
    system("pause");
    return 0;
}
