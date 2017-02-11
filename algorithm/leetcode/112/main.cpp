/*

Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
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
    bool hasPathSum(TreeNode* root, int sum)
    {
        if(root == NULL) {
            return false;
        }
        return traverse(root, sum);
    }
    bool traverse(TreeNode* root, int sum)
    {
        if(root == NULL && sum ==0) {
            return true;
        }
        if(root != NULL) {
            bool left = traverse(root->left, sum - root->val);
            bool right = traverse(root->right, sum - root->val);
            if(!root->left && !root->right) {
                return left || right;
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
    cout << sln.hasPathSum(&t1, 3);
    system("pause");
    return 0;
}
