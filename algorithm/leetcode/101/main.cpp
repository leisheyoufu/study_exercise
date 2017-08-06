/*
101. Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
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
    bool isSymmetric(TreeNode* root)
    {
        if(!root) {
            return true;
        }
        vector<TreeNode *> v;
        v.push_back(root->left);
        v.push_back(root->right);
        while(!v.empty()) {
            int mid = v.size()/2;
            for(int i=0; i<mid; i++) {
                if(v[i] && v[v.size()-1-i] && v[i]->val == v[v.size()-1-i]->val || !v[i] && !v[v.size()-1-i]) {
                    continue;
                } else {
                    return false;
                }
            }
            vector<TreeNode *>tmp;
            for(int i=0; i<v.size(); i++) {
                if(v[i]) {
                    tmp.push_back(v[i]->left);
                    tmp.push_back(v[i]->right);
                }
            }
            v = tmp;
        }
        return true;
    }
};

int main()
{
    Solution sln;
    sln.isSymmetric(NULL);
    system("pause");
    return 0;
}
