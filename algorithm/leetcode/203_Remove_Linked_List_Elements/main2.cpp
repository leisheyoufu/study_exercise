/*
203. Remove Linked List Elements

Remove all elements from a linked list of integers that have value val.

Example
Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6, val = 6
Return: 1 --> 2 --> 3 --> 4 --> 5
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        for(ListNode **curr = &head; *curr;) {
            ListNode *entry = *curr;
            if(entry->val == val) {
                *curr = (*curr) ->next;
            } else {
                curr = &(entry->next);
            }
        }
        return head;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
