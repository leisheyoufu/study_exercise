/*
79. Word Search

Given a 2D board and a word, find if the word exists in the grid.

The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

For example,
Given board =

[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]
word = "ABCCED", -> returns true,
word = "SEE", -> returns true,
word = "ABCB", -> returns false.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    bool in(vector<vector<char> > &board, string &word, vector<vector<bool> > &vis, int i, int j, int k)
    {
        int m = board.size();
        int n = board[0].size();
        if (k == word.length()) {
            return true;
        }
        if(i>0 && !vis[i-1][j] && board[i-1][j] == word[k]) {
            vis[i-1][j] = true;
            if (in(board, word, vis, i-1, j, k+1)) {
                return true;
            }
            vis[i-1][j] = false;
        }
        if(i<m-1 && !vis[i+1][j] && board[i+1][j] == word[k]) {
            vis[i+1][j] = true;
            if(in(board, word, vis, i+1, j, k+1)) {
                return true;
            }
            vis[i+1][j] = false;
        }
        if(j>0 && !vis[i][j-1] && board[i][j-1] == word[k]) {
            vis[i][j-1] = true;
            if(in(board, word, vis, i, j-1, k+1)) {
                return true;
            }
            vis[i][j-1] = false;
        }
        if(j<n-1 && !vis[i][j+1] && board[i][j+1] == word[k]) {
            vis[i][j+1] = true;
            if(in(board, word, vis, i, j+1, k+1)) {
                return true;
            }
            vis[i][j+1] = false;
        }
        return false;
    }
    bool exist(vector<vector<char> >& board, string word)
    {
        int m = board.size();
        if (m ==0) {
            return false;
        }
        int n = board[0].size();
        if(n ==0) {
            return false;
        }
        if (word.empty()) {
            return true;
        }
        vector<vector<bool> > vis(m, vector<bool>(n, false));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(board[i][j] != word[0]) {
                    continue;
                }
                vis[i][j] = true;
                if (in(board, word, vis, i, j, 1)) {
                    return true;
                }
                vis[i][j] = false;
            }
        }
        return false;
    }
};

int main()
{
    Solution sln;
    vector<vector<char> > v;
    vector<char> vc;
    string s = "ABCE";
    vc.assign(s.begin(), s.end());
    v.push_back(vc);
    s = "SFES";
    vc.assign(s.begin(), s.end());
    v.push_back(vc);
    s = "ADEE";
    vc.assign(s.begin(), s.end());
    v.push_back(vc);
    cout << sln.exist(v, "SEE") << endl;
    system("pause");
    return 0;
}
