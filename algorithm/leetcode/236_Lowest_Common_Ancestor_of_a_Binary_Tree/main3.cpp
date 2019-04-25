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
    TreeNode * traverse(TreeNode *root, TreeNode* p, TreeNode* q, bool &found)
    {
        if(!root) {
            return NULL;
        }
        TreeNode *left = traverse(root->left, p, q, found);
        if(found) {
            return left;
        }
        TreeNode *right = traverse(root->right, p, q, found);
        if(found) {
            return right;
        }
        if(left == p && (right == q || root == q)) {
            found = true;
            return root;
        }
        if(left == q && (right == p || root == p)) {
            found = true;
            return root;
        }
        if(right == p && (left == q || root == q)) {
            found = true;
            return root;
        }
        if(right == q && (left == p || root == p)) {
            found = true;
            return root;
        }
        if(root == p || root == q) {
            return root;
        }
        if(left) {
            return left;
        }
        if(right) {
            return right;
        }
        return NULL;

    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        bool found = false;
        return traverse(root, p, q, found);
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
    cout << ret->val << endl;  // 1
    system("pause");
    return 0;
}
