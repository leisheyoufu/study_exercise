/*
236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: ��The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).��

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.


*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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
    TreeNode *traverse(TreeNode *root, TreeNode *p, TreeNode* q, TreeNode **ret)
    {
        if(!root) {
            return NULL;
        }
        if(*ret) {
            return NULL;
        }
        TreeNode *left = traverse(root->left, p, q, ret);
        TreeNode *right = traverse(root->right, p, q, ret);
        TreeNode *temp;
        if((left ==p || left == q) && (right == p || right == q))  {
            if(! *ret) {
                *ret = root;
            }
        }
        if((left ==p || left == q || right == p || right == q) && (root == p || root == q)) {
            if(! *ret) {
                *ret = root;
            }
        }
        if(left == p || right == p || root == p) {
            return p;
        }
        if(left == q || right == q || root == q) {
            return q;
        }
        return NULL;
    }

    TreeNode* lowestCommonAncestorTemp(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if(!root) {
            return NULL;
        }
        TreeNode *ret = NULL;
        traverse(root, p, q, &ret);
        return ret;
    }

    // CL the best way
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if (!root || root == p || root == q)
            return root;
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        if (left && right)
            return root;
        if (!left)
            return right;
        if (!right)
            return left;

    }
};

int main()
{
    Solution sln;
    TreeNode n1 (1);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    TreeNode *ret = sln.lowestCommonAncestor(&n1, &n3,&n4);
    cout << ret->val;
    system("pause");
    return 0;
}
