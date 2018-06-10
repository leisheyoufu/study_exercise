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
    /*
    ListNode* mergeKLists(vector<ListNode*>& lists) {
    	int n = lists.size();
    	if(n<=0) {
    		return NULL;
    	}
    	vector<int> vis(n,0);
    	vector<ListNode *> curr(n, NULL);
    	ListNode *head = NULL, *temp;
    	int k =INT_MAX, min_index = -1;
    	int count = 0;
    	for(int i=0;i<n;i++) {
    		if(lists[i] !=NULL) {
    			count++;
    			curr[i] = lists[i];
    			if(curr[i]->val <k) {
    				k = curr[i]->val;
    				min_index = i;
    			}
    		} else {
    			vis[i] = 1;
    		}
    	}
    	if(min_index != -1) {
    		head = lists[min_index];
    		temp = head;
    		curr[min_index] = curr[min_index]->next;
    	}
    	while(count >0) {
    		k = INT_MAX;
    		min_index = -1;
    		for(int i=0;i<n;i++) {
    			if(curr[i] == NULL) {
    				if(vis[i] != 1) {
    					vis[i] = 1;
    					count--;
    				}
    			}
    			if(!vis[i]) {
    				if(curr[i]->val <k) {
    					k = curr[i]->val;
    					min_index = i;
    				}
    			}
    		}
    		if(min_index !=-1) {
    			temp->next = curr[min_index];
    			curr[min_index] = curr[min_index]->next;
    			temp = temp->next;
    		}
    	}
    	return head;
    }
    */
    ListNode *merge(ListNode* list1, ListNode* list2)
    {
        ListNode *head = NULL, *temp;
        if(list1 !=NULL && list2!=NULL) {
            if(list1->val < list2->val) {
                head= list1;
                list1 = list1->next;
            } else {
                head = list2;
                list2 = list2->next;
            }
        } else if(list1) {
            head= list1;
        } else if (list2) {
            head = list2;
        }
        temp = head;
        while(list1 && list2) {
            if(list1->val < list2->val) {
                temp->next= list1;
                list1 = list1->next;
            } else {
                temp->next = list2;
                list2 = list2->next;
            }
            temp = temp->next;
        }
        if(list1) {
            temp->next = list1;
        } else if(list2) {
            temp->next = list2;
        }
        return head;
    }

    ListNode *mergeKlists(vector<ListNode*>& lists, int start, int end)
    {
        if(start == end) {
            return lists[start];
        }
        int mid = (start+end)/2;
        ListNode *left = mergeKlists(lists, start,mid);
        ListNode *right = mergeKlists(lists, mid+1, end);
        return merge(left, right);
    }

    ListNode* mergeKLists(vector<ListNode*>& lists)
    {
        int n =lists.size();
        if(n==0) {
            return NULL;
        }
        if(n==1) {
            return lists[0];
        }
        return mergeKlists(lists, 0, n-1);
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
