/*

108. Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>

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
    TreeNode *build(vector<int>& nums, int start, int end)
    {
        if(start > end) {
            return NULL;
        }
        int mid = start + (end-start)/2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = build(nums, start, mid-1);
        root->right = build(nums, mid+1, end);
        return root;
    }
    TreeNode* sortedArrayToBST(vector<int>& nums)
    {
        int n = nums.size();
        return build(nums, 0, n-1);
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
