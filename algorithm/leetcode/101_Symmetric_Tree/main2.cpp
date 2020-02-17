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
        bool flag = true;
        int n = 1;
        vector<TreeNode*> v1(n, NULL);
        v1[0] = root;
        while(flag) {
            flag = false;
            vector<TreeNode*> v2(n*2, NULL);
            for(int i=0; i<n; i++) {
                if(!v1[i]) {
                    continue;
                }
                v2[2*i] = v1[i]->left;
                v2[2*i+1] = v1[i]->right;
                flag = v2[2*i] || v2[2*i+1];
            }
            for(int i=0; i<n; i++) {
                if(!v2[i] && !v2[2*n-i-1]) {
                    continue;
                }
                if((v2[i] == NULL ^ v2[2*n-i-1] == NULL) != NULL) {
                    return false;
                }
                if(v2[i]->val != v2[2*n-i-1]->val) {
                    return false;
                }
            }
            v1 = v2;
            n = n*2;
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
