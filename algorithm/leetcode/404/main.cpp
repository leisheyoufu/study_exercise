/*
404. Sum of Left Leaves

Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.


*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
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
    int sumOfLeftLeaves(TreeNode* root)
    {
        if(!root) {
            return 0;
        }
        pair<TreeNode*, bool> p(root, false);
        stack< pair<TreeNode*, bool>> s;
        s.push(p);
        int val = 0;
        while(!s.empty()) {
            pair<TreeNode*, bool> temp = s.top();
            s.pop();
            TreeNode *t = temp.first;
            if(temp.second == true && !t->left && !t->right) {
                val += t->val;
            } else {
                if(t->right) {
                    pair<TreeNode*, bool> r(t->right, false);
                    s.push(r);
                }
                if(t->left) {
                    pair<TreeNode*, bool> l(t->left, true);
                    s.push(l);
                }
            }
        }
        return val;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
