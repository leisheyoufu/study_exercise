/*

Populating Next Right Pointers in Each Node II

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

Note:

You may only use constant extra space.
For example,
Given the following binary tree,
         1
       /  \
      2    3
     / \    \
    4   5    7
After calling your function, the tree should look like:
         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution
{
public:
    void connect(TreeLinkNode *root)
    {
        if(root == NULL)
            return;

        if(root->left && root->right) {
            root->left->next = root->right;
        }
        TreeLinkNode *child = root->left;
        if (root->right) {
            child = root->right;
        }
        if(child) {
            TreeLinkNode *i = root->next;
            while(i && i->left == NULL && i->right == NULL) {
                i= i->next;
            }
            if(i && i->left) {
                child->next = i ->left;
            } else if(i && i->right) {
                child ->next = i->right;
            }
        }
        connect(root->right);
        connect(root->left);
    }
};

int main()
{
    Solution sln;

    getch();
    return 0;
}
