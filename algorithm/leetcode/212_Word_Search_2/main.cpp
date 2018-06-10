/*
212. Word Search II
Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

Example:

Input:
words = ["oath","pea","eat","rain"] and board =
[
['o','a','a','n'],
['e','t','a','e'],
['i','h','k','r'],
['i','f','l','v']
]

Output: ["eat","oath"]
Note:
You may assume that all inputs are consist of lowercase letters a-z.*/

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class TrieNode
{
public:
    TrieNode *next[26];
    bool mark;
    TrieNode()
    {
        mark = false;
        memset(next, 0, sizeof(next));
    }
    TrieNode* search(char ch, bool &found)
    {
        TrieNode *curr = next[ch - 'a'];
        if (!curr) {
            return NULL;
        }
        if (curr->mark) {
            found = true;
            curr->mark = false;  // no duplicate, del
        }
        return curr;
    }
};

class Trie
{
public:
    TrieNode * root;
    Trie()
    {
        root = new TrieNode();
    }
    void insert(string word)
    {
        TrieNode *curr = root;
        for (int i = 0; i < word.size(); i++) {
            char ch = word[i];
            if (!curr->next[ch - 'a']) {
                curr->next[ch - 'a'] = new TrieNode();
            }
            curr = curr->next[ch - 'a'];
        }
        curr->mark = true;
    }
};

class Solution
{
public:
    void dfs(vector<vector<char>>& board, TrieNode *curr, string str, vector < vector<bool>> &vis, vector<string> &ret, int i, int j)
    {
        bool found = false;
        TrieNode *temp = curr->search(board[i][j], found);
        if (!temp) {
            return;
        }
        str += board[i][j];
        if (found) {
            ret.push_back(str);
        }
        vis[i][j] = true;
        if (i > 0 && !vis[i-1][j]) {
            dfs(board, temp, str, vis, ret, i - 1, j);
        }
        if (j < board[0].size() - 1 && !vis[i][j+1]) {
            dfs(board, temp, str, vis, ret, i, j + 1);
        }
        if ( i<board.size()-1 && !vis[i+1][j]) {
            dfs(board, temp, str, vis, ret, i+1, j);
        }
        if (j >0 && !vis[i][j-1]) {
            dfs(board, temp, str, vis, ret, i, j-1);
        }
        vis[i][j] = false;
    }
    void search(vector<vector<char>>& board, Trie &tree, vector<string> &ret)
    {
        vector < vector<bool>> vis(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                dfs(board, tree.root, "", vis, ret, i, j);
            }
        }
    }
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
    {
        vector<string> ret;
        if (board.size() == 0) {
            return ret;
        }
        if (board[0].size() == 0) {
            return ret;
        }
        if (words.size() == 0) {
            return ret;
        }
        Trie tree;
        for (auto word : words) {
            tree.insert(word);
        }
        search(board, tree, ret);
        return ret;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
