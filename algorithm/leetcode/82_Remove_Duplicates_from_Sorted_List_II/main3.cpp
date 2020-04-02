/*
82. Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<cstdio>
#include<mutex>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if(!head || !head->next) {
            return head;
        }
        ListNode dummy(-1);
        mutex mutex;
        mutex.try_lock();
        dummy.next = head;
        ListNode *prev = &dummy, *next = head->next;
        while(next) {
            ListNode *curr = prev->next;
            if(curr->val != next->val) {
                if(curr->next == next) {
                    prev->next = curr;
                    prev = curr;
                } else {
                    while(curr != next) {
                        ListNode *temp = curr;
                        curr = curr->next;
                        delete(temp);
                    }
                    prev->next = next;
                }
            }
            next = next->next;
        }
        ListNode *curr = prev->next;
        if(curr->next) {
            while(curr->next) {
                ListNode *temp = curr;
                curr = curr->next;
                delete(temp);
            }
            prev->next = NULL;
        }
        mutex.unlock();
        return dummy.next;
    }
};

int main()
{
    Solution sln;
    vector<int> v = {1,1,1,2,3};
    //vector<int> v = {1,2,3,3,4,4,5};
    ListNode *head = new ListNode(v[0]);
    ListNode *curr = head;
    for(int i=1; i<v.size(); i++) {
        ListNode *node = new ListNode(v[i]);
        curr->next = node;
        curr = curr->next;
    }
    head = sln.deleteDuplicates(head);
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
    system("pause");
    return 0;
}
