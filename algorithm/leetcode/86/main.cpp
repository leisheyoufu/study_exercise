/*
86. Partition List

Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

You should preserve the original relative order of the nodes in each of the two partitions.

For example,
Given 1->4->3->2->5->2 and x = 3,
return 1->2->2->4->3->5.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    ListNode* partition(ListNode* head, int x)
    {
        ListNode *left, **right, *left_head = NULL;
        right = &head;
        if( !head || !head->next) {
            return head;
        }
        while(*right) {
            ListNode *curr = *right;
            while( curr && curr->val < x) {
                if(!left_head) {
                    left_head = curr;
                    left = curr;
                } else {
                    left->next = curr;
                    left = curr;
                }
                curr = curr->next;
            }
            *right = curr;
            if(curr) {
                right = &(curr->next);
            }
        }
        if (left_head) {
            left->next = head;
            return left_head;
        }
        return head;
    }
};

int main()
{
    Solution sln;
    ListNode n1(1);
    ListNode n2(4);
    ListNode n3(3);
    ListNode n4(2);
    ListNode n5(5);
    ListNode n6(2);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    sln.partition(&n1, 3);
    system("pause");
    return 0;
}
