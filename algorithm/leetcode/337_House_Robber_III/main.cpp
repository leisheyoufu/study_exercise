/*
337. House Robber III
Medium

The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:

Input: [3,2,3,null,3,null,1]

     3
    / \
   2   3
    \   \
     3   1

Output: 7
Explanation: Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.

Example 2:

Input: [3,4,5,1,3,null,1]

     3
    / \
   4   5
  / \   \
 1   3   1

Output: 9
Explanation: Maximum amount of money the thief can rob = 4 + 5 = 9.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution
{
    int rob(TreeNode *root)
    {
        vector<int> ret = dfs(root);
        return max(ret[0], ret[1]);
    }
    vector<int> dfs(TreeNode *root)
    {
        vector<int> ret(2, 0);
        if(!root) {
            return ret;
        }
        vector<int> left = dfs(root->left);
        vector<int> right = dfs(root->right);
        ret[0] = max(left[0], left[1]) + max(right[0], right[1]);
        ret[1] = root->val + left[0] + right[0];
        return ret;
    }
};

int main()
{
    system("pause");
    return 0;
}
