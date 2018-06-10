/*

100. Same Tree

Given two binary trees, write a function to check if they are equal or not.

Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

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
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        if(p == NULL && q == NULL) {
            return true;
        }
        if(p == NULL || q == NULL) {
            return false;
        }
        if(p->val != q->val) {
            return false;
        }
        if (isSameTree(p->left, q->left) == false) {
            return false;
        }
        if (isSameTree(p->right, q->right) == false) {
            return false;
        }
        return true;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
