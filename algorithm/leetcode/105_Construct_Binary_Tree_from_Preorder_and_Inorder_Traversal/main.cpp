/*

Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        if(preorder.empty()) {
            return NULL;
        }
        return build(preorder, 0,preorder.size()-1, inorder,0, inorder.size()-1);
    }
    TreeNode *build(vector<int>& pre, int prestart, int preend, vector<int>& inorder, int instart, int inend)
    {
        if(prestart > preend) {
            return NULL;
        }
        int rootVal = pre[prestart];
        int i;
        for(i=instart; i<=inend; i++) {
            if(inorder[i] == rootVal) {
                break;
            }
        }
        int leftlen = i - instart;
        TreeNode * root = new TreeNode(rootVal);
        root->left = build(pre,prestart+1,prestart+leftlen, inorder, instart, i-1);
        root->right = build(pre, prestart+leftlen+1, preend, inorder, i+1, inend);
        return root;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
