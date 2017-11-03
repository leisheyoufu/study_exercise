/*

160. Intersection of Two Linked Lists
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.


*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (!headA || !headB) {
            return NULL;
        }
        ListNode *tail = headA;
        while (tail->next) {
            tail = tail->next;
        }
        tail->next = headB;
        ListNode *ret = getCircleStart(headA);
        tail->next = NULL;
        return ret;
    }

    ListNode *getCircleStart(ListNode *head)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                fast = fast->next;
            }
            slow = slow->next;
            if (slow == fast) {
                break;
            }
        }
        if (!fast) {
            return NULL;
        }
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
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
    ListNode n7(7);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n5.next = &n6;
    n6.next = &n7;
    n7.next = &n2;
    cout << sln.getIntersectionNode(&n1, &n5)->val << endl;
    system("pause");
    return 0;
}
