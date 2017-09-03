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
        if(head==NULL) {
            return head;
        }
        unordered_map<RandomListNode*, RandomListNode*> maps;
        RandomListNode* ret = (RandomListNode*)malloc(sizeof(RandomListNode));
        maps[head] = ret;
        ret->label = head->label;
        while(head) {
            RandomListNode *copy = maps[head];
            if(head->next) {
                RandomListNode *next;
                if(maps.find(head->next) == maps.end()) {
                    next = (RandomListNode *)malloc(sizeof(RandomListNode));
                    next->label = head->next->label;
                    maps[head->next] = next;

                } else {
                    next = maps[head->next];
                }
                copy->next = next;
            } else {
                copy->next = NULL;
            }
            if(head->random) {
                RandomListNode *random;
                if(maps.find(head->random) == maps.end()) {
                    random = (RandomListNode *)malloc(sizeof(RandomListNode));
                    random->label = head->random->label;
                    maps[head->random] = random;

                } else {
                    random = maps[head->random];
                }
                copy->random = random;
            } else {
                copy->random = NULL;
            }
            head = head->next;
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
