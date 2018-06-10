/*

Path Sum III

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
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
    int count;
    int pathSum(TreeNode* root, int sum)
    {
        count = 0;
        path(root, sum);
        return count;
    }
    void path(TreeNode* root, int sum)
    {
        if(root == NULL) {
            return;
        }
        path(root->left, sum);
        path(root->right, sum);
        traverse(root, sum);
    }
    void traverse(TreeNode* root, int sum)
    {
        if(root == NULL) {
            return;
        }
        if(sum == root->val) {
            count++;
        }
        traverse(root->left,sum - root->val);
        traverse(root->right,sum - root->val);
    }
};

int main()
{
    Solution sln;
    TreeNode t1 (1);
    TreeNode t2(2);
    t1.left = &t2;
    sln.pathSum(&t1, 3);
    system("pause");
    return 0;
}
