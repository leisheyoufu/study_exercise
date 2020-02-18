/*

113. Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]
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
public:
    void dfs(TreeNode* root, vector<int> curr, vector<vector<int>> &ret, int num, int sum)
    {
        if(!root) {
            return;
        }
        if(!root->left && !root->right) {
            if(num + root->val == sum) {
                curr.push_back(root->val);
                ret.push_back(curr);
            }
            return;
        }
        curr.push_back(root->val);
        dfs(root->left, curr, ret, num+root->val, sum);
        dfs(root->right, curr, ret, num+root->val, sum);
    }
    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        vector<vector<int>> ret;
        vector<int> curr;
        dfs(root, curr, ret, 0, sum);
        return ret;
    }
};

int main()
{
    Solution sln;
    TreeNode t1 (1);
    TreeNode t2(2);
    t1.left = &t2;
    sln.pathSum(&t1, 3);
    system("pause");
    return 0;
}
