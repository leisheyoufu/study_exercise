/*

Path Sum II

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
    vector<vector<int>> pathSum(TreeNode* root, int sum)
    {
        vector<vector<int>> vv;
        vector<int> v;
        if(root == NULL) {
            return vv;
        }
        traverse(root, sum, v, vv);
        return vv;
    }
    bool traverse(TreeNode* root, int sum, vector<int> v, vector<vector<int>> &vv)
    {
        if(root == NULL && sum ==0) {
            return true;
        }
        if(root != NULL) {
            vector<int> r(v);
            r.push_back(root->val);
            bool left = traverse(root->left, sum - root->val,r, vv);
            bool right = traverse(root->right, sum - root->val, r, vv);
            if(!root->left && !root->right) {
                if(left || right) {
                    vv.push_back(r);
                    return true;
                }
            }
            if(root->right && right) {
                return true;
            }
            if(root->left && left) {
                return true;
            }
        }
        return false;
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
