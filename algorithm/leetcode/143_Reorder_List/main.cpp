/*
Reorder List

Given a singly linked list L: L0¡úL1¡ú¡­¡úLn-1¡úLn,
reorder it to: L0¡úLn¡úL1¡úLn-1¡úL2¡úLn-2¡ú¡­

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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
    ListNode *findHalf(ListNode *head)
    {
        int len = 0;
        ListNode *temp = head;
        while(temp!=NULL) {
            len++;
            temp = temp->next;
        }
        ListNode *half = head;
        int mid = (len+1)/2;
        while(mid) {
            mid--;
            half = half->next;
        }
        return half;
    }

    void put(ListNode *half, stack<ListNode *> &s)
    {
        while(half) {
            s.push(half);
            half=half->next;
        }
    }
    void reorderList(ListNode* head)
    {
        ListNode *half = findHalf(head);
        stack<ListNode *> s;
        put(half,s);
        ListNode *temp = head;
        while(!s.empty()) {
            if (temp->next == half) {
                half->next = NULL;
                break;
            }
            temp = head->next;
            ListNode *tail = s.top();
            s.pop();
            head->next = tail;
            tail->next = temp;
            head = temp;
        }
        if(s.empty()&& head) {
            head->next = NULL;
        }
    }
};
int main()
{
    Solution sln;
    ListNode t1(1);
    ListNode t2(2);
    ListNode t3(3);
    ListNode t4(4);
    t1.next = &t2;
    t2.next = &t3;
    //t3.next = &t4;
    sln.reorderList(&t1);
    system("pause");
    return 0;
}
