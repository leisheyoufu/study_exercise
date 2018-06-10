/*
92. Reverse Linked List II

Reverse a linked list from position m to n. Do it in-place and in one-pass.

For example:
Given 1->2->3->4->5->NULL, m = 2 and n = 4,

return 1->4->3->2->5->NULL.

Note:
Given m, n satisfy the following condition:
1 ? m ? n ? length of list.
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* reverseBetween(ListNode* head, int m, int n)
    {
        ListNode dummy(-1);
        dummy.next = head;
        int i = 1;
        ListNode *split_tail = &dummy;
        while(split_tail && i<m) {
            split_tail = split_tail->next;
            i++;
        }
        ListNode *prev = split_tail->next;
        ListNode *tail = prev;
        ListNode *curr = prev->next;
        tail->next = NULL;
        i = 0;
        while(i++<n-m && curr) {
            ListNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        split_tail->next =prev;
        tail->next = curr;
        return dummy.next;
    }
};

int main()
{
    Solution sln;
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(4);
    ListNode n5(5);
    ListNode n6(6);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    cout << sln.reverseBetween(&n1, 2,4);
    system("pause");
    return 0;
}
