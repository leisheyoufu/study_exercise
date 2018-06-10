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
        if(m==n) {
            return head;
        }
        ListNode *dummy = new ListNode(-1);
        dummy->next = head;
        ListNode *pre = dummy, *curr = head, *next = head->next, *oldPre;
        int index = 0;
        while(curr) {
            index ++;
            next = curr->next;
            if (index == m) {
                oldPre = pre;
            } else if(index>m && index <n) {
                curr->next = pre;
            } else if(index ==n) {
                curr->next = pre;
                ListNode *temp = oldPre->next;
                oldPre->next = curr;
                temp->next = next;
                break;
            }
            pre = curr;
            curr = next;
        }
        return dummy->next;
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
