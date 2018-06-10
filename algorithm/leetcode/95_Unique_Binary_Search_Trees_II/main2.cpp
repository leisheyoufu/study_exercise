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
    vector<TreeNode*> dfs(int start, int end)
    {
        vector<TreeNode*> ret;
        if(start > end) {
            ret.push_back(NULL);
            return ret;
        }
        for(int k=start; k<=end; k++) {
            vector<TreeNode*> left_list = dfs(start, k-1);
            vector<TreeNode*> right_list = dfs(k+1, end);
            for(int i=0; i<left_list.size(); i++) {
                for(int j=0; j<right_list.size(); j++) {
                    TreeNode *root = new TreeNode(k);
                    root->left = left_list[i];
                    root->right = right_list[j];
                    ret.push_back(root);
                }
            }
        }
        return ret;
    }
    vector<TreeNode*> generateTrees(int n)
    {
        if (n<=0) {
            return vector<TreeNode*>();
        }
        vector<TreeNode*> ret = dfs(1, n);
        return ret;
    }
};

int main()
{
    Solution sln;
    sln.generateTrees(3);
    system("pause");
    return 0;
}
