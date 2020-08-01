/*
382. Linked List Random Node

Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?

Example:

// Init a singly linked list [1,2,3].
ListNode head = new ListNode(1);
head.next = new ListNode(2);
head.next.next = new ListNode(3);
Solution solution = new Solution(head);

// getRandom() should return either 1, 2, or 3 randomly. Each element should have equal probability of returning.
solution.getRandom();
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head)
    {
        this->head = head;
        srand( time(0) );
    }

    /** Returns a random node's value. */
    int getRandom()
    {
        int cnt = 0, ret = -1;
        ListNode *temp = this->head;
        while(temp) {
            cnt ++;
            if(rand()% cnt == 0) {
                ret = temp->val;
            }
            temp = temp->next;
        }
        return ret;
    }
private:
    ListNode *head;
};
int main()
{
    ListNode head(1);
    head.next = new ListNode(2);
    head.next->next = new ListNode(3);
    Solution* obj = new Solution(&head);
    int param_1 = obj->getRandom();
    cout << param_1 << endl;
    system("pause");
    return 0;
}
