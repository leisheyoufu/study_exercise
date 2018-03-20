/*
61. Rotate List

Given a list, rotate the list to the right by k places, where k is non-negative.

For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

Subscribe to see which companies asked this question.
*/
#include<iostream>
#include<string>
#include<vector>
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
    ListNode* rotateRight(ListNode* head, int k)
    {
        if(!head) {
            return NULL;
        }
        ListNode *fast = head;
        ListNode *slow = head;
        int i=0;
        while(i<k) {
            if (!fast->next) {
                fast = head;
                i ++;
                k %= i;
                i = 0;
                continue;
            }
            fast = fast->next;
            i++;
        }
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        fast->next = head;
        head = slow->next;
        slow->next = NULL;
        return head;
    }
};
int main()
{
    Solution sln;
    ListNode n1(1);
    ListNode n2(2);
    n1.next = &n2;
    sln.rotateRight(&n1,1);
    // [1,2,3,4,5]
    // 14
    system("pause");
    return 0;
}
