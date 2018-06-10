/*
235. Lowest Common Ancestor of a Binary Search Tree

Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given nodes in the BST.

According to the definition of LCA on Wikipedia: ¡°The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).¡±

        _______6______
       /              \
    ___2__          ___8__
   /      \        /      \
   0      _4       7       9
         /  \
         3   5
For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.


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
        if(!root) {
            return NULL;
        }
        if(p==q) {
            return p;
        }
        int min_val = p->val;
        if(min_val > q->val) {
            min_val = q->val;
        }
        while(root) {
            if(root->val == p->val || root->val == q->val) {
                return root;
            } else if(root->val <q->val && root->val > p->val || root->val > q->val && root->val < p->val) {
                return root;
            } else if(root->val < min_val) {
                root =root->right;
            } else if(root->val > min_val) {
                root = root->left;
            }
        }
        return NULL;
    }
};

int main()
{
    Solution sln;
    TreeNode n1 (3);
    TreeNode n2(1);
    TreeNode n3(4);
    TreeNode n4(2);
    n1.left = &n2;
    n1.right = &n3;
    n2.right = &n4;
    TreeNode *ret = sln.lowestCommonAncestor(&n1, &n2,&n4);
    cout << ret->val;
    system("pause");
    return 0;
}
