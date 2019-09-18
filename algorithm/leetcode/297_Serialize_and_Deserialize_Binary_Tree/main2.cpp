/*

297. Serialize and Deserialize Binary Tree

Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.

Example:

You may serialize the following tree:

    1
   / \
  2   3
     / \
    4   5

as "[1,2,3,null,null,4,5]"
Clarification: The above format is the same as how LeetCode serializes a binary tree. You do not necessarily need to follow this format, so please be creative and come up with different approaches yourself.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<unordered_map>

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
    string parse(TreeNode* root)
    {
        if(!root) {
            return "*";
        }
        string ret = to_string(root->val);
        ret += " " + parse(root->left);
        ret += " " + parse(root->right);
        return ret;
    }

    string join(vector<string> s)
    {
        int n = s.size();
        if(n==0) {
            return "";
        }
        if(n==1) {
            return s[0];
        }
        string ret = s[0];
        for(int i=1; i<n; i++) {
            ret+=" " + s[i];
        }
        return ret;
    }

    string serialize(TreeNode* root)
    {
        return parse(root);
    }

    vector<string> split(string data)
    {
        if(data.length() == 0) {
            return vector<string>();
        }
        vector<string> ret;
        string s;
        for(int i=0; i<data.length(); i++) {
            if(data[i] != ' ') {
                s += data[i];
            } else {
                ret.push_back(s);
                s = "";
            }
        }
        return ret;
    }
    TreeNode* buildTree(vector<string> &s, int &i)
    {
        int n = s.size();
        if(i >= n) {
            return NULL;
        }
        string val = s[i++];
        if(val == "*") {
            return NULL;
        }
        TreeNode *root = new TreeNode(stoi(val));
        root->left = buildTree(s, i);
        root->right = buildTree(s, i);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        vector<string> s = split(data);
        int index = 0;
        return buildTree(s, index);
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
