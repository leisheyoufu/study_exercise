/*

112. Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*/
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
    bool dfs(TreeNode *root, int num, int sum)
    {
        if(!root) {
            return false;
        }
        if(!root->left && !root->right) {
            if(num + root->val == sum) {
                return true;
            }
            return false;
        }
        bool left = dfs(root->left, num + root->val, sum);
        bool right = dfs(root->right, num + root->val, sum);
        return left || right;
    }
    bool hasPathSum(TreeNode* root, int sum)
    {
        return dfs(root, 0, sum);
    }
};

int main()
{
    Solution sln;
    TreeNode t1 (1);
    TreeNode t2(2);
    t1.left = &t2;
    cout << sln.hasPathSum(&t1, 3);
    system("pause");
    return 0;
}
