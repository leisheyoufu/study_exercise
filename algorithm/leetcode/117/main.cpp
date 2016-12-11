#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 };

class Solution {
public:
	 void connect(TreeLinkNode *root) {
		 if(root == NULL)
			 return;

		 if(root->left && root->right) {
			 root->left->next = root->right;
		 }
		 TreeLinkNode *child = root->left;
		 if (root->right) {
			 child = root->right;
		 }
		 if(child) {
			 TreeLinkNode *i = root->next;
			 while(i && i->left == NULL && i->right == NULL) {
				 i= i->next;
			 }
			 if(i && i->left) {
				 child->next = i ->left;
			 } else if(i && i->right) {
				 child ->next = i->right;
			 }
		 }
		 connect(root->right);
		 connect(root->left);		 
    }
};

int main()
{
    Solution sln;
	
    getch();
    return 0;
}
