/*
114. Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example,
Given

         1
        / \
       2   5
      / \   \
     3   4   6
The flattened tree should look like:
   1
    \
     2
      \
       3
        \
         4
          \
           5
            \
             6
click to show hints.

Hints:
If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal.

*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
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
    void flatten(TreeNode* root)
    {
        if(!root) {
            return;
        }
        stack<TreeNode*> tree;
        queue<TreeNode*> ret;
        tree.push(root);
        while(!tree.empty()) {
            TreeNode *temp = tree.top();
            tree.pop();
            ret.push(temp);
            if(temp->right) {
                tree.push(temp->right);
            }
            if(temp->left) {
                tree.push(temp->left);
            }
            temp->left = NULL;
            temp->right = NULL;
        }
        ret.pop();
        TreeNode *temp = root;
        while(!ret.empty()) {
            temp->right = ret.front();
            ret.pop();
            temp = temp->right;
        }
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
