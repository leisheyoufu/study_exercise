/*
25. Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

k is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.

You may not alter the values in the nodes, only nodes itself may be changed.

Only constant memory is allowed.

For example,
Given this linked list: 1->2->3->4->5

For k = 2, you should return: 2->1->4->3->5

For k = 3, you should return: 3->2->1->4->5
*/
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* reverse(ListNode *head)
    {
        if(!head) {
            return head;
        }
        ListNode *curr = head->next;
        head->next = NULL;
        while(curr) {
            ListNode *temp = curr->next;
            curr->next = head;
            head = curr;
            curr= temp;
        }
        return head;
    }

    ListNode* reverseKGroup(ListNode* head, int k)
    {
        int count = 1;
        int is_head = 0;
        ListNode *new_head = head;
        ListNode *prev_tail = NULL;
        ListNode *start = head;
        while(head) {
            ListNode *curr = head->next;
            ListNode *temp = NULL;
            count ++;
            if(count == k) {
                count = 1;
                if(curr) {
                    temp = curr->next;
                    curr->next = NULL;
                    ListNode *tail = start;
                    head = reverse(start);
                    if(prev_tail) {
                        prev_tail->next = head;
                    }
                    if(!is_head) {
                        is_head = 1;
                        new_head = head;
                    }
                    tail->next = temp;
                    curr = temp;
                    start = curr;
                    prev_tail = tail;
                }
            }
            head = curr;
        }
        return new_head;
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
    n1.next=&n2;
    n2.next=&n3;
    n3.next=&n4;
    n4.next=&n5;
    n5.next=&n6;
    sln.reverseKGroup(&n1,2);
    system("pause");
    return 0;
}
