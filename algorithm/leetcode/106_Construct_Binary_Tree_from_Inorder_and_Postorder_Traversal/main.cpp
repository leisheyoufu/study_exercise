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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
    {
        if(postorder.empty()) {
            return NULL;
        }
        return build(inorder, 0,inorder.size()-1, postorder,0, postorder.size()-1);
    }
    TreeNode *build(vector<int>& in, int instart, int inend, vector<int>& post, int poststart, int postend)
    {
        if(poststart > postend) {
            return NULL;
        }
        int rootVal = post[postend];
        int i;
        for(i=instart; i<=inend; i++) {
            if(in[i] == rootVal) {
                break;
            }
        }
        int leftlen = i - instart;
        TreeNode * root = new TreeNode(rootVal);
        root->left = build(in,instart,i-1, post, poststart, poststart+leftlen-1);
        root->right = build(in, i+1, inend, post, poststart+leftlen, postend-1);
        return root;
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
