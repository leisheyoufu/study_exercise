/*  Merge k Sorted Lists
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        if(!l1) {
            return l2;
        }
        if(!l2) {
            return l1;
        }
        ListNode *head = l1;
        if(l2->val < head->val) {
            head = l2;
            l2 = l2->next;
        } else {
            l1 = l1->next;
        }
        ListNode *temp = head;
        while(l1 || l2) {
            if(!l1) {
                temp->next = l2;
                return head;
            } else if(!l2) {
                temp->next = l1;
                return head;
            }
            if(l1->val < l2->val) {
                temp->next = l1;
                l1 = l1->next;
            } else {
                temp ->next = l2;
                l2 = l2->next;
            }
            temp = temp->next;
        }
        return head;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        if(lists.empty()) {
            return NULL;
        }
        while(lists.size() > 1) {
            vector<ListNode*> temp;
            int n = lists.size();
            for(int i=0; i<n/2; i++) {
                temp.push_back(mergeTwoLists(lists[i*2], lists[i*2+1]));
            }
            if(n & 0x1 == 1) {
                temp.push_back(lists[n-1]);
            }
            lists = temp;
        }
        return lists[0];
    }
};
int main()
{
    Solution sln;
    vector<ListNode*> lists;
    ListNode node(1);
    lists.push_back(NULL);
    lists.push_back(&node);
    sln.mergeKLists(lists);
    system("pause");
    return 0;
}
