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
    int minDepth(TreeNode* root)
    {
        if (!root) {
            return 0;
        }
        int depth = 1;
        queue<TreeNode*> q;
        q.push(root);
        int last = 1;
        int curr = 0;
        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            if(node->left) {
                q.push(node->left);
                curr++;
            }
            if(node->right) {
                q.push(node->right);
                curr++;
            }

            if(!node->left && !node->right) {
                return depth;
            }
            last --;
            if(!last) {
                depth++;
                last = curr;
                curr=0;
            }
        }
        return depth;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}