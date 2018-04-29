/*

230. Kth Smallest Element in a BST

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note:
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently? How would you optimize the kthSmallest routine?

Credits:
Special thanks to @ts for adding this problem and creating all test cases.
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
    void traverse(TreeNode* root, int k, int &curr, int &val)
    {
        if(root->left) {
            traverse(root->left, k, curr, val);
        }
        curr++;
        if(curr == k) {
            val =root->val;
            return;
        }
        if(root->right) {
            traverse(root->right, k, curr, val);
        }
    }
    int kthSmallest(TreeNode* root, int k)
    {
        if(!root) {
            return -1;
        }
        int curr = 0, val = -1;
        traverse(root, k, curr, val);
        return val;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
