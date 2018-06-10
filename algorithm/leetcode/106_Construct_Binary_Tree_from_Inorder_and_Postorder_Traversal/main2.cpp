/*

Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

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
    TreeNode *generate(vector<int>& inorder, vector<int>& postorder, int in_start, int in_end, int post_start)
    {
        if(in_start > in_end) {
            return NULL;
        }
        int val = postorder[post_start];
        int i;
        for(i=in_start; i<=in_end; i++) {
            if(inorder[i] == val) {
                break;
            }
        }
        TreeNode *root = new TreeNode(val);
        root->left = generate(inorder, postorder, in_start, i-1, post_start - in_end+i-1);
        root->right = generate(inorder, postorder, i+1, in_end, post_start -1);
        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        int n1 = inorder.size();
        int n2 = postorder.size();
        if (n1 != n2 || n1 == 0) {
            return NULL;
        }
        return generate(inorder, postorder, 0, n1-1, n2-1);
    }
};

int main()
{
    int a1[] = {6,7,3};
    int a2[] = {6,3,7};

    vector<int> v1(a1, a1+ sizeof(a1)/sizeof(int));
    vector<int> v2(a2, a2+ sizeof(a2)/sizeof(int));
    Solution sln;
    TreeNode*  t = sln.buildTree(v1,v2);
    system("pause");
    return 0;
}
