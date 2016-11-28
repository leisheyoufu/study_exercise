#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<conio.h>

using namespace std;
struct ListNode {
	int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	int getSize(ListNode *l1) {
		int sz = 0;
		while(l1!=NULL) {
			sz++;
			l1 = l1->next;
		}
		return sz;
	}

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int s1 = getSize(l1);
		int s2 = getSize(l2);
		int len, remain;
		ListNode *node, *head = NULL, *curr;
		
		
		int c=0;
		while(l1 !=NULL || l2!=NULL) {
			int v1, v2;
			if(l1==NULL) {
				v1=0;
			} else {
				v1 = l1->val;
				l1 = l1->next;
			}
			if(l2==NULL) {
				v2 = 0;
			} else {
				v2= l2->val;
				l2 = l2->next;
			}
			int val = v1+v2+c;
			c = val /10;
			val %=10;
			if(head == NULL) {
				head = new ListNode(val);
				curr = head;
			} else {
				node = new ListNode(val);
				curr->next = node;
				curr = node;
			}
		}
		if (c>0 ) {
			node = new ListNode(c);
			curr->next = node;
		}
		return head;
    }
};


int main()
{
	ListNode *a1 = new ListNode(2);
	ListNode *a2 = new ListNode(4);
	ListNode *a3 = new ListNode(3);
	a1->next = a2;
	a2->next = a3;
	ListNode *b1 = new ListNode(5);
	ListNode *b2 = new ListNode(6);
	ListNode *b3 = new ListNode(4);
	b1->next = b2;
	b2->next = b3;
	Solution s;
	ListNode *result = s.addTwoNumbers(a1,b1);
	while(result!=NULL) {
		printf("%d ", result->val);
		result = result->next;
	}
	getch();
	return 0;
}
