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
        ListNode *fast = head, *slow=head;
        while(fast && fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
            if(slow == fast) {
                break;
            }
        }
        if(!fast || !fast->next || !fast->next->next) {
            return NULL;
        }
        fast = head;
        while(fast != slow) {
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
    n1.next=&n2;
    n2.next=&n3;
    n3.next=&n4;
    n4.next=&n1;
    cout << sln.detectCycle(&n1)->val<< endl; // 1
    system("pause");
    return 0;
}
