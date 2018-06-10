/*
222. Count Complete Tree Nodes

Given a complete binary tree, count the number of nodes.

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
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
    int get_right_height(TreeNode *root)
    {
        int count = 0;
        while(root) {
            root = root->right;
            count ++;
        }
        return count;
    }

    int get_left_height(TreeNode *root)
    {
        int count = 0;
        while(root) {
            root = root ->left;
            count ++;
        }
        return count;
    }
    int countNodes(TreeNode* root)
    {
        if(!root) {
            return 0;
        }
        int left_height = get_left_height(root);
        int right_height = get_right_height(root);
        if(left_height == right_height) {
            return (1 << left_height) -1;
        }
        return countNodes(root->left) + countNodes(root->right) + 1;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
