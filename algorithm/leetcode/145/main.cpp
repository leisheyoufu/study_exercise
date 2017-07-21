/*

145. Binary Tree Postorder Traversal

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
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
    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> ret;
        stack<TreeNode*> stk;
        unordered_set<TreeNode*> vis;
        if(!root) {
            return ret;
        }
        stk.push(root);
        while(!stk.empty()) {
            TreeNode *node = stk.top();
            if(vis.find(node) == vis.end()) {
                if(node->right) {
                    stk.push(node->right);
                }
                if(node->left) {
                    stk.push(node->left);
                }
                vis.insert(node);
            } else {
                ret.push_back(node->val);
                stk.pop();
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    sln.postorderTraversal(NULL);
    system("pause");
    return 0;
}
