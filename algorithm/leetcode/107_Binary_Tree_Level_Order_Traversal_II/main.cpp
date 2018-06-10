/*

107. Binary Tree Level Order Traversal II

Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

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
    vector<vector<int> > levelOrderBottom(TreeNode* root)
    {
        vector<vector<int> > ret(0, vector<int>());
        if(!root) {
            return ret;
        }
        queue<TreeNode*> q;
        q.push(root);
        int curr = 0;
        int total = 0;
        int last = 1;
        vector<int> line;
        while(!q.empty()) {
            TreeNode *temp = q.front();
            q.pop();
            line.push_back(temp->val);
            if(temp->left) {
                total ++;
                q.push(temp->left);
            }
            if(temp->right) {
                total++;
                q.push(temp->right);
            }
            curr ++;
            if(curr == last) {
                last = total;
                total = 0;
                curr = 0;
                ret.push_back(line);
                line.clear();
            }
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
