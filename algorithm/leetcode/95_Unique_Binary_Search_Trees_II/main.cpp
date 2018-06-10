/*

Unique Binary Search Trees II

iven an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

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
    vector<TreeNode*> generate(int left, int right)
    {
        vector<TreeNode* > ret;
        if(left>right) {
            ret.push_back(NULL);
        }
        for(int k=left; k<=right; k++) {
            vector<TreeNode*> leftTree = generate(left, k-1);
            vector<TreeNode*> rightTree = generate(k+1, right);
            for(int i=0; i<leftTree.size(); i++) {
                for(int j=0; j<rightTree.size(); j++) {
                    TreeNode *root = new TreeNode(k);
                    root->left = leftTree[i];
                    root->right = rightTree[j];
                    ret.push_back(root);
                }
            }
        }
        return ret;
    }

    vector<TreeNode*> generateTrees(int n)
    {
        if (n==0) {
            vector<TreeNode* > ret;
            return ret;
        }
        return generate(1,n);
    }
};

int main()
{
    system("pause");
    return 0;
}
