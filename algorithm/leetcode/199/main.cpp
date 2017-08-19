/*

199. Binary Tree Right Side View
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

Credits:
Special thanks to @amrsaqr for adding this problem and creating all test cases.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    vector<int> rightSideView(TreeNode* root) 
	{
		vector<int> ret;
		if(!root) {
			return ret;
		}
		vector<TreeNode*> v1;
		vector<TreeNode*> v2;
		v1.push_back(root);
		while(!v1.empty()) {
			ret.push_back(v1[v1.size()-1]->val);
			for(int i=0; i<v1.size();i++) {
				if(v1[i]->left) {
					v2.push_back(v1[i]->left);
				}
				if(v1[i]->right) {
					v2.push_back(v1[i]->right);
				}	
			}
			v1.swap(v2);
			v2.clear();
		}
		return ret;        
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
