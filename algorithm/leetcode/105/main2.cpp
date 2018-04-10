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
    TreeNode *generate(vector<int>& preorder, vector<int>& inorder, int p_start, int i_start, int i_end)
    {
        if(i_start > i_end) {
            return NULL;
        }
        int val = preorder[p_start];
        TreeNode *root = new TreeNode(val);
        int i;
        for(i=i_start; i<i_end; i++) {
            if(val == inorder[i]) {
                break;
            }
        }
        root->left = generate(preorder, inorder, p_start+1, i_start, i-1);
        root->right = generate(preorder, inorder, p_start + i - i_start +1, i+1, i_end);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        int n1= preorder.size();
        int n2 = inorder.size();
        if(n1 != n2 || n1 == 0 ) {
            return NULL;
        }
        return generate(preorder, inorder, 0, 0, n2-1);
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
