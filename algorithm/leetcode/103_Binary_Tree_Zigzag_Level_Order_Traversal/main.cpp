/*
Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
  [15,7]
]
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        vector<vector<int>> ret;
        if(!root) {
            return ret;
        }
        queue<TreeNode*> queue;
        queue.push(root);
        int last = 1;
        int curr = 0;
        int level = 1;
        vector<int> line;
        stack<int> stack;
        while(!queue.empty()) {
            TreeNode *node = queue.front();
            queue.pop();
            if(node->left) {
                queue.push(node->left);
                curr++;
            }
            if(node->right) {
                queue.push(node->right);
                curr++;
            }
            if(level %2 == 1) {
                line.push_back(node->val);
            } else {
                stack.push(node->val);
            }
            last --;
            if(!last) {
                if(level %2 == 1) {
                    ret.push_back(line);
                    line.clear();
                } else {
                    vector<int> temp;
                    while(!stack.empty()) {
                        int val = stack.top();
                        temp.push_back(val);
                        stack.pop();
                    }
                    ret.push_back(temp);
                }
                last = curr;
                curr = 0;
                level++;
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
