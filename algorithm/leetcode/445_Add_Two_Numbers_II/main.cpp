/*
445. Add Two Numbers II

You are given two non-empty linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
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
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        stack<int> s1, s2;
        while(l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while(l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        int c = 0;
        ListNode *last = NULL, *temp = NULL;
        while(!s1.empty() || !s2.empty()) {
            int a = 0, b = 0;
            if (!s1.empty()) {
                a = s1.top();
                s1.pop();
            }
            if (!s2.empty()) {
                b = s2.top();
                s2.pop();
            }
            int val = a + b + c;
            if (val >= 10) {
                val -=10;
                c = 1;
            } else {
                c = 0;
            }
            temp = new ListNode(val, last);
            last = temp;
        }
        if (c > 0) {
            temp = new ListNode(c, last);
        }
        return temp;
    }
};

ListNode* genList(vector<int> v)
{
    ListNode* temp = NULL, *last = NULL;
    for(int i=v.size()-1; i>=0; i--) {
        temp = new ListNode(v[i], last);
        last = temp;
    }
    return temp;
}

void PrintList(ListNode *l)
{
    while(l) {
        cout << l->val << "->";
        l = l->next;
    }
    cout << endl;
}

int main()
{
    Solution sln;
    ListNode *l1 = genList({7,2,4,3});
    ListNode *l2 = genList({5,6,4});
    ListNode *l3 = sln.addTwoNumbers(l1,l2);
    PrintList(l3); // 7 -> 8 -> 0 -> 7
    system("pause");
    return 0;
}
