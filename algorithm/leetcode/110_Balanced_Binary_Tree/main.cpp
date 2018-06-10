/*

110. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
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
    bool isBalanced(TreeNode* root)
    {
        if(!root) {
            return true;
        }
        bool balanced = true;
        height(root, balanced);
        return balanced;
    }
    int height(TreeNode *root, bool &balanced)
    {
        if(!root) {
            return 0;
        }
        int left_height = 1, right_height = 1;
        if(root->left) {
            left_height = height(root->left, balanced) + 1;
        }
        if(root->right) {
            right_height = height(root->right, balanced) + 1;
        }
        if(abs(left_height - right_height) > 1) {
            balanced = false;
        }
        return max(left_height, right_height);
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
