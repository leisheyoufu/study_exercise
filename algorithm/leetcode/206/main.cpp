/*
206. Reverse Linked List

Reverse a singly linked list.
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
    ListNode* reverseList(ListNode* head)
    {
        if(!head) {
            return head;
        }
        ListNode *prev = NULL, *curr = head, *next;
        while(curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
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
    ListNode n6(7);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    cout << sln.reverseList(&n1);
    system("pause");
    return 0;
}
