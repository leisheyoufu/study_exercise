/*

515. Find Largest Value in Each Tree Row

You need to find the largest value in each row of a binary tree.

Example:

Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]
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
    vector<int> largestValues(TreeNode* root)
    {
        vector<int> ret;
        if(!root) {
            return ret;
        }
        queue<pair<TreeNode*, int>> q;
        q.push(make_pair(root, 1));
        int level = 1;
        int maxVal = root->val;
        while(!q.empty()) {
            int currLevel = q.front().second;
            TreeNode *currNode = q.front().first;
            if(level != currLevel) {
                ret.push_back(maxVal);
                maxVal = currNode->val;
                level = currLevel;
            } else {
                maxVal = max(maxVal, currNode->val);
            }
            if(currNode->left) {
                q.push(make_pair(currNode->left, currLevel + 1));
            }
            if(currNode->right) {
                q.push(make_pair(currNode->right, currLevel + 1));
            }
            q.pop();
        }
        ret.push_back(maxVal);
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
