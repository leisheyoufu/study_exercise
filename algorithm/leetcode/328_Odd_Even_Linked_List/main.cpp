/*
328. Odd Even Linked List

Given a singly linked list, group all odd nodes together followed by the even nodes. Please note here we are talking about the node number and not the value in the nodes.

You should try to do it in place. The program should run in O(1) space complexity and O(nodes) time complexity.

Example 1:

Input: 1->2->3->4->5->NULL
Output: 1->3->5->2->4->NULL

Example 2:

Input: 2->1->3->5->6->4->7->NULL
Output: 2->3->6->7->1->5->4->NULL

Note:

    The relative order inside both the even and odd groups should remain as it was in the input.
    The first node is considered odd, the second node even and so on ...
*/
#include<iostream>
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
    ListNode* oddEvenList(ListNode* head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode *odd = head;
        ListNode *even = head->next;
        head = head->next->next;
        bool isOdd = true;
        ListNode *currOdd = odd;
        ListNode *currEven = even;
        while(head) {
            if(isOdd) {
                currOdd->next = head;
                if(head) {
                    currOdd = head;
                }
                isOdd = false;
            } else {
                currEven->next = head;
                currEven = head;
                isOdd = true;
            }
            ListNode *tmpHead = head;
            head = head->next;
            tmpHead = NULL;
        }
        currEven->next = NULL; // cl: important
        currOdd->next = even;
        return odd;
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
    ListNode *oddEvenList = sln.oddEvenList(&n1);
    while(oddEvenList) {
        cout << oddEvenList->val << " ";
        oddEvenList = oddEvenList->next;
    }
    system("pause");
    return 0;
}
