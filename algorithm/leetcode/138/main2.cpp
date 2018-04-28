/*
138. Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};
class Solution
{
public:

    RandomListNode *copyRandomList(RandomListNode *head)
    {
        if (!head) {
            return NULL;
        }
        unordered_map<RandomListNode*, RandomListNode*> m;
        RandomListNode* ret = new RandomListNode(head->label);
        m[head] = ret;
        RandomListNode* copy, *copy_random, *temp = ret;
        while(head) {
            if(head->next) {
                if(m.find(head->next) == m.end()) {
                    copy = new RandomListNode(head->next->label);
                    m[head->next] = copy;
                } else {
                    copy = m[head->next];
                }
                temp->next = copy;
            }
            if (head->random) {
                if(m.find(head->random) == m.end()) {
                    copy_random = new RandomListNode(head->random->label);
                    m[head->random] = copy_random;
                } else {
                    copy_random = m[head->random];
                }
                temp->random = copy_random;
            }
            head = head->next;
            temp = temp->next;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    RandomListNode n1(1);
    RandomListNode n2(2);
    RandomListNode n3(3);
    RandomListNode n4(4);
    RandomListNode n5(5);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n1.random = &n5;
    RandomListNode *copy = sln.copyRandomList(&n1);
    while(copy) {
        cout << copy->label << " ";
        copy = copy->next;
    }
    system("pause");
    return 0;
}
