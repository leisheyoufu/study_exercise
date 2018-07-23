/*

257. Binary Tree Paths

Given a binary tree, return all root-to-leaf paths.

Note: A leaf is a node with no children.

Example:

Input:

   1
 /   \
2     3
 \
  5

Output: ["1->2->5", "1->3"]

Explanation: All root-to-leaf paths are: 1->2->5, 1->3
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
    void dfs(TreeNode *curr, vector<string> &ret, vector<int> path)
    {
        path.push_back(curr->val);
        if(!curr->left && !curr->right) {
            string s = to_string(path[0]);
            for(int i=1; i<path.size(); i++) {
                s += "->" + to_string(path[i]);
            }
            ret.push_back(s);
            return;
        }
        if(curr->left) {
            dfs(curr->left, ret, path);
        }
        if(curr->right) {
            dfs(curr->right, ret, path);
        }
    }
    vector<string> binaryTreePaths(TreeNode* root)
    {
        if(!root) {
            return vector<string>();
        }
        vector<string> ret;
        vector<int> path;
        dfs(root, ret, path);
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
