/*
124. Binary Tree Maximum Path Sum
Given a binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

For example:
Given the below binary tree,

       1
      / \
     2   3
Return 6.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

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
    int maxPath(TreeNode *root, int &maxNum)
    {
        int left_num = 0, right_num = 0;
        if(root->left) {
            left_num = maxPath(root->left, maxNum);
        }
        if(root->right) {
            right_num = maxPath(root->right, maxNum);
        }
        int ret = root->val;
        if(left_num > 0) {
            ret += left_num;
        }
        if(right_num > 0) {
            ret += right_num;
        }
        maxNum = max(maxNum, ret);
        int temp = max(left_num, right_num);
        if(temp > 0) {
            return root->val + temp;
        }
        return root->val;
    }
    int maxPathSum(TreeNode* root)
    {
        if(!root) {
            return INT_MIN;
        }
        int maxNum = root->val;
        maxPath(root, maxNum);
        return maxNum;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
