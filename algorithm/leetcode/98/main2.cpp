/*

98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:
    2
   / \
  1   3
Binary tree [2,1,3], return true.
Example 2:
    1
   / \
  2   3
Binary tree [1,2,3], return false.
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
    bool validateHelper(TreeNode *root, int left_val, int right_val)
    {
        if(!root) {
            return true;
        }
        if(root->val <= left_val || root->val >= right_val) {
            return false;
        }
        return validateHelper(root->left, left_val, root->val) && validateHelper(root->right, root->val, right_val);
    }
    bool isValidBST(TreeNode* root)
    {
        if(!root) {
            return true;
        }
        return validateHelper(root->left, LONG_MIN, root->val) && validateHelper(root->right, root->val, LONG_MAX);
    }
};

int main()
{
    Solution sln;
    TreeNode node1 (1);
    TreeNode node2 (2);
    TreeNode node3 (3);
    node2.left = &node1;
    node2.right = &node3;
    cout << sln.isValidBST(&node2);
    system("pause");
    return 0;
}
