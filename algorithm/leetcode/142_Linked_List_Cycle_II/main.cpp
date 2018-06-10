/*

142. Linked List Cycle II

Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Follow up:
Can you solve it without using extra space?


*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
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
    ListNode *detectCycle(ListNode *head)
    {
        if(!head) {
            return NULL;
        }
        ListNode *one = head->next;
        if(!one) {
            return NULL;
        }
        ListNode *two = one->next;
        while(two) {
            two = two->next;
            if(two) {
                two = two->next;
            } else {
                return NULL;
            }
            one = one->next;
            if(one == two) {
                break;
            }
        }
        if(!two) {
            return NULL;
        }
        one = head;
        while(one!=two) {
            one = one->next;
            two = two->next;
        }
        return one;
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
    n1.next=&n2;
    n2.next=&n3;
    n3.next=&n4;
    n4.next=&n1;
    cout << sln.detectCycle(&n1)->val<< endl;
    system("pause");
    return 0;
}
