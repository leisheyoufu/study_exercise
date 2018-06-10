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
    ListNode *reverse(ListNode *head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode *curr, *temp;
        curr = head->next;
        head->next = NULL;
        while(curr) {
            temp = curr->next;
            curr->next = head;
            head = curr;
            curr = temp;
        }
        return head;
    }

    ListNode* reverseKGroup(ListNode* head, int k)
    {
        if(k==1) {
            return head;
        }
        ListNode *temp = NULL;
        ListNode *curr = head;
        ListNode *new_head = head;
        ListNode *last = NULL;
        ListNode *next_head = NULL;
        while(head) {
            int count = 1;
            while(count < k) {
                head = head->next;
                count++;
                if(!head) {
                    break;
                }
            }
            if(!head) {
                if(last) {
                    last->next = curr;
                }
                break;
            }
            next_head = head->next;
            head->next = NULL;
            temp = reverse(curr);
            if(new_head == curr) {
                new_head = temp;
            } else {
                last ->next = temp;
            }
            last = curr;
            head = next_head;
            curr = head;
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
