/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        vector<vector<int>> ret;
        if(!root) {
            return ret;
        }
        queue<TreeNode*> queue;
        queue.push(root);
        int last = 1;
        int curr = 0;
        vector<int> line;
        while(!queue.empty()) {
            TreeNode *node = queue.front();
            queue.pop();
            if(node->left) {
                queue.push(node->left);
                curr++;
            }
            if(node->right) {
                queue.push(node->right);
                curr++;
            }
            line.push_back(node->val);
            last --;
            if(!last) {
                ret.push_back(line);
                line.clear();
                last = curr;
                curr = 0;
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
