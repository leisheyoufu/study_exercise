#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

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
	void sum(TreeNode* node, int cur, int &r)
	{
		cur*=10;
		cur+= node->val;
		if(node->left) {
			sum(node->left, cur, r);
		}
		if(node->right) {
			sum(node->right, cur, r);
		}
		if(!node->left && !node->right) {
			r+=cur;
		}

	}
	int sumNumbers(TreeNode* root) {
		int cur = 0;
		if(!root) {
			return 0;
		}
		int r=0;
		sum(root, cur, r);
		return r;
    }
};

int main()
{	
	Solution sln;
    system("pause");
    return 0;
}