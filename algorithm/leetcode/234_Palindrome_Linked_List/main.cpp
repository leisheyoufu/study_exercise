/*
234. Palindrome Linked List

Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
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
    bool isPalindrome(ListNode* head)
    {
        if(!head || !head->next) {
            return true;
        }
        ListNode *fast = head, *slow = head;
        while(fast) {
            fast = fast->next;
            if(!fast) {
                break;
            }
            fast = fast->next;
            slow = slow->next;
        }
        ListNode *head2 = slow;
        ListNode *curr = head2->next, *prev = head2;
        prev->next = NULL;
        while(curr) {
            ListNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        head2 = prev;
        while(head != slow) {
            if(head->val != head2->val) {
                return false;
            }
            head = head->next;
            head2 = head2->next;
        }
        return true;
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
