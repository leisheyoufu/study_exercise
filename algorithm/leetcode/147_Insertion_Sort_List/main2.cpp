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
        if(!head || !head->next) {
            return head;
        }
        ListNode dummy(-1);
        dummy.next = head;
        for(ListNode *inode = head; inode->next;) {
            bool flag = false;
            for(ListNode *pnode = &dummy; pnode != inode; pnode= pnode->next) {
                if(inode->next->val < pnode->next->val) {
                    ListNode *pnext = pnode->next;
                    ListNode *inext = inode->next;
                    ListNode *temp = inext->next;
                    pnode->next = inext;
                    inext->next = pnext;
                    inode->next =temp;
                    flag = true;
                    break;
                }
            }
            if(!flag) {
                inode = inode->next;
            }
        }
        return dummy.next;
    }
};
int main()
{
    Solution sln;
    ListNode l1(4);
    ListNode l2(2);
    ListNode l3(1);
    ListNode l4(3);
    l1.next = &l2;
    l2.next = &l3;
    l3.next = &l4;
    ListNode *l5 = sln.insertionSortList(&l1);
    system("pause");
    return 0;
}
