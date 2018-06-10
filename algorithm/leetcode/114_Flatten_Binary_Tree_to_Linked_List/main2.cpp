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
        stack<TreeNode*> s;
        s.push(root);
        TreeNode *last = NULL;
        while(!s.empty()) {
            TreeNode *curr = s.top();
            if(curr->right) {
                s.push(curr->right);
                curr->right = NULL;
            }
            if(curr->left) {
                s.push(curr->left);
                curr->left = NULL;
            }
            if(last) {
                last->right = curr;
            }
            last = curr;
            s.pop();
        }
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
