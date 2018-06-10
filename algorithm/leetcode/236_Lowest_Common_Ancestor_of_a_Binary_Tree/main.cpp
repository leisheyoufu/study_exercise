/*
236. Lowest Common Ancestor of a Binary Tree

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: ¡°The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).¡±

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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        if( p == q) {
            return q;
        }
        TreeNode *result = NULL;
        return traverse(root, p, q, &result);

    }
    TreeNode* traverse(TreeNode* root, TreeNode *p, TreeNode *q, TreeNode **result)
    {
        if(root && !(*result)) {
            TreeNode *left = traverse(root->left, p, q, result);
            TreeNode *right = traverse(root->right,p,q, result);
            if(*result) {
                return *result;
            }
            if(left && right) {
                *result = root;
                return root;
            }
            if(left) {
                if(root == p && left == q) {
                    *result = root;
                    return root;
                }
                if(root == q && left ==p) {
                    *result = root;
                    return root;
                }
            }
            if(right) {
                if(root == p && right == q) {
                    *result = root;
                    return root;
                }
                if(root == q && right ==p) {
                    *result = root;
                    return root;
                }
            }
            if(root == p) {
                return p;
            } else if(root == q) {
                return q;
            }
            if(left) {
                return left;
            }
            if(right) {
                return right;
            }
        }
        if(*result) {
            return *result;
        }
        return NULL;
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
