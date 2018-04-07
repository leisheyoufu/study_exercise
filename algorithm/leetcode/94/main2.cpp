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
#include<stack>
#include<vector>
#include<unordered_set>
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
    vector<int> inorderTraversal(TreeNode* root)
    {
        stack<TreeNode*> s;
        unordered_set<TreeNode*> vis;
        vector<int> ret;
        if(root) {
            s.push(root);
        }
        while(!s.empty()) {
            TreeNode *curr = s.top();
            s.pop();
            if(vis.find(curr) == vis.end()) {
                vis.insert(curr);
                if(curr->right) {
                    s.push(curr->right);
                }
                s.push(curr);
                if (curr->left) {
                    s.push(curr->left);
                }
            } else {
                ret.push_back(curr->val);
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    TreeNode root(1);
    TreeNode r(2);
    TreeNode l(3);
    root.right = &r;
    r.left = &l;
    sln.inorderTraversal(&root);
    system("pause");
    return 0;
}
