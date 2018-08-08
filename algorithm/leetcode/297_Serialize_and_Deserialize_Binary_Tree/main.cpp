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
    string join(vector<string> v)
    {
        string ret;
        for(int i=0; i<v.size()-1; i++) {
            ret += v[i] + ",";
        }
        ret += v[v.size()-1];
        return ret;
    }
    vector<string> split(string s)
    {
        vector<string> ret;
        if(s.empty()) {
            return ret;
        }
        int i =0, start = 0;
        while(i<s.length()) {
            if(s[i] == ',') {
                ret.push_back(s.substr(start, i-start));
                i++;
                start = i;
                continue;
            }
            i++;
        }
        ret.push_back(s.substr(start, i-start + 1));
        return ret;
    }
    string serialize(TreeNode* root)
    {
        if(!root) {
            return "";
        }
        queue<TreeNode*> q;
        q.push(root);
        unordered_map<TreeNode*, string> m;
        m[root] = "1";
        vector<string> v;
        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();
            string index = m[node];
            v.push_back(index);
            v.push_back(to_string(node->val));
            if(node->left) {
                q.push(node->left);
                m[node->left] = index + "0";
            }
            if(node->right) {
                q.push(node->right);
                m[node->right] = index + "1";
            }
        }
        return join(v);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        vector<string> v = split(data);
        if(v.empty()) {
            return NULL;
        }
        int i=0;
        unordered_map<string, TreeNode*> m;
        TreeNode * root = new TreeNode(stoi(v[1]));
        m["1"] = root;
        i = 2;
        while(i<v.size()) {
            string index = v[i++];
            int val = stoi(v[i++]);
            TreeNode *node = new TreeNode(val);
            m[index] = node;
            if(index[index.size()-1] == '0') {
                m[index.substr(0, index.size()-1)]->left = node;
            } else {
                m[index.substr(0, index.size()-1)]->right = node;
            }
        }
        return root;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
