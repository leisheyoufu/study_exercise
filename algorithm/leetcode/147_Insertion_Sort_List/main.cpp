/*
147. Insertion Sort List

Sort a linked list using insertion sort.
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<cstdlib>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:

    ListNode* insertionSortList(ListNode* head)
    {
        if(!head) {
            return NULL;
        }
        ListNode dummy(-1);
        dummy.next = head;
        for(ListNode *i = dummy.next; i->next;) {
            bool b = false;
            for(ListNode *j = &dummy; j!=i; j=j->next) {
                if (i->next->val < j->next->val) {
                    ListNode *jtemp = j->next;
                    ListNode *itemp = i->next->next;
                    j->next = i->next;
                    j->next->next = jtemp;
                    i->next = itemp;
                    // i is alreay point to the next one, do not get next in current iteration.
                    b = true;
                    break;
                }
            }
            if (!b) {
                i = i->next;
            }
        }
        return dummy.next;
    }

};
int main()
{
    Solution sln;
    ListNode l1(3);
    ListNode l2(1);
    ListNode l3(2);
    l1.next = &l2;
    l2.next = &l3;
    ListNode *l4 = sln.insertionSortList(&l1);
    system("pause");
    return 0;
}
