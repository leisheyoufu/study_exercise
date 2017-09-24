/*

104. Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
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
    int maxDepth(TreeNode* root)
    {
        if(!root) {
            return 0;
        }
        int depth = 0;
        if (!root->left && !root->right) {
            return 1;
        }
        if( root->left) {
            depth = maxDepth(root->left) + 1;
        }
        if (root->right) {
            depth = max(depth, maxDepth(root->right) +1);
        }
        return depth;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
