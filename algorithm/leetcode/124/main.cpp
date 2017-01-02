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
    int maxNum(TreeNode *node, int &cur_max)
    {
        int num = node->val;
        int left = num, right = num;
        if(node->left) {
            int val = maxNum(node->left, cur_max);
            if(val + num > num) {
                num = val + num;
                left+=val;
            }
        }
        if(node->right) {
            int val = maxNum(node->right, cur_max);
            if(val + num > num) {
                num = val + num;
                right +=val;
            }
        }
        cur_max = max(cur_max, num);
        return max(left, right);
    }
    int maxPathSum(TreeNode* root)
    {
        if(!root) {
            return INT_MIN;
        }
        int cur_max = root->val;
        maxNum(root, cur_max);
        return cur_max;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}