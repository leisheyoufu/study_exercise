/*

141. Linked List Cycle

Given a linked list, determine if it has a cycle in it.

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
    bool hasCycle(ListNode *head)
    {
        if(!head || !head->next) {
            return false;
        }
        ListNode *fast = head, *slow = head;
        while(fast) {
            fast = fast->next;
            if(fast) {
                fast = fast->next;
            }
            slow = slow->next;
            if(slow == fast) {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    Solution sln;
    ListNode n1(1);
    ListNode n2(2);
    ListNode n3(3);
    ListNode n4(5);
    ListNode n5(5);
    n1.next=NULL;
    n2.next=&n3;
    n3.next=&n4;
    n4.next=&n4;
    cout << sln.hasCycle(&n1)<< endl;
    system("pause");
    return 0;
}
