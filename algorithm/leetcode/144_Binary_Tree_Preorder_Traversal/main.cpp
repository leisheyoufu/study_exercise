/*

144. Binary Tree Preorder Traversal

Given a binary tree, return the preorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [1,2,3].
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<unordered_set>

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

    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        stack<TreeNode*> stk;
        if(!root) {
            return ret;
        }
        stk.push(root);
        while(!stk.empty()) {
            TreeNode *node = stk.top();
            ret.push_back(node->val);
            stk.pop();
            if (node->right) {
                stk.push(node->right);
            }
            if(node->left) {
                stk.push(node->left);
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    sln.preorderTraversal(NULL);
    system("pause");
    return 0;
}
