/*

94. Binary Tree Inorder Traversal

Given a binary tree, return the inorder traversal of its nodes' values.

For example:
Given binary tree [1,null,2,3],
   1
    \
     2
    /
   3
return [1,3,2].
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

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
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        helper(ret, root);
        return ret;
    }
    void helper(vector<int> &ret, TreeNode *root)
    {
        if(root) {
            helper(ret, root->left);
            ret.push_back(root->val);
            helper(ret, root->right);
        }
    }
};

int main()
{
    Solution sln;
    sln.inorderTraversal(NULL);
    system("pause");
    return 0;
}
