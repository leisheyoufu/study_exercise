/*
173. Binary Search Tree Iterator

Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class BSTIterator
{
    TreeNode *root;
    stack<TreeNode*> s;
public:
    BSTIterator(TreeNode *root)
    {
        this->root = root;
        while(root) {
            s.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext()
    {
        if(!s.empty()) {
            return true;
        }
        return false;
    }

    /** @return the next smallest number */
    int next()
    {
        TreeNode *curr = s.top();
        int ret = curr->val;
        s.pop();
        if(curr->right) {
            curr = curr->right;
            while(curr) {
                s.push(curr);
                curr = curr->left;
            }
        }
        return ret;
    }
};

int main()
{
    TreeNode root(0);
    BSTIterator bst(&root);
    system("pause");
    return 0;
}
