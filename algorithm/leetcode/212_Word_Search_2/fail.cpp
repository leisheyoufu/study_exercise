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

class Solution
{
public:
    bool dfs(vector<vector<char>>& board, string &word, vector < vector<bool>> vis, int index, int i, int j)
    {
        vis[i][j] = true;
        index++;
        if (index == word.size()) {
            return true;
        }
        if (i > 0 && !vis[i-1][j] && board[i - 1][j] == word[index]) {
            if (dfs(board, word, vis, index, i - 1, j)) {
                return true;
            }
        }
        if (j < board[0].size() - 1 && !vis[i][j+1] && board[i][j + 1] == word[index]) {
            if (dfs(board, word, vis, index, i, j+1)) {
                return true;
            }
        }
        if ( i<board.size()-1 && !vis[i+1][j] && board[i+1][j] == word[index]) {
            if (dfs(board, word, vis, index, i+1, j)) {
                return true;
            }
        }
        if (j >0 && !vis[i][j-1] && board[i][j-1] == word[index]) {
            if (dfs(board, word, vis, index, i, j - 1)) {
                return true;
            }
        }
        return false;
    }
    bool search(vector<vector<char>>& board, string &word)
    {
        vector < vector<bool>> vis(board.size(), vector<bool>(board[0].size(), false));
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]) {
                    if (dfs(board, word, vis, 0, i, j)) {
                        return true;
                    }
                }
            }
        }
        return false;
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
        sort(words.begin(), words.end());
        for (int i = 0; i < words.size(); i++) {
            if (i > 0 && words[i] == words[i - 1]) {
                continue;
            }
            if (search(board, words[i])) {
                ret.push_back(words[i]);
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
