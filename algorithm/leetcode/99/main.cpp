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

class Solution {
public:
    TreeNode *mistake1, *mistake2;;
    TreeNode *pre;
    
    void recursive_traversal(TreeNode *root) {
        if(root==NULL) {
            return;
        }
        if(root->left!=NULL) {
            recursive_traversal(root->left);
        }
        if(pre!=NULL&&root->val<pre->val) {
            if(mistake1==NULL) {
                mistake1 = pre;
                mistake2 = root;
            } else {
                mistake2 = root;
            }
        }
        pre = root;
        if(root->right!=NULL) {
            recursive_traversal(root->right);
        }
    }
    void recoverTree(TreeNode *root) {        
        recursive_traversal(root);
        if(mistake1!=NULL&&mistake2!=NULL) {
            int tmp = mistake1->val;
            mistake1->val = mistake2->val;
            mistake2->val = tmp;
        }
    }
};

int main()
{
    Solution sln;
	string s1 = "db";
	string s2 = "b";
	string s3="cbb";

    printf("%d\n",sln.isInterleave(s1,s2,s3));
    getch();
    return 0;
}
