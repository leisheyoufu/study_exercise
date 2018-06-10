/*
51. N-Queens

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.



Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

For example,
There exist two distinct solutions to the 4-queens puzzle:

[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
CL: the original method is better
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool valid(vector<vector<bool>> &m, int x, int y)
    {
        int n = m.size();
        // must no same row
        // check if same column exits
        for(int i=0; i<x; i++) {
            if(m[i][y]) {
                return false;
            }
        }
        for(int i=0; i<x; i++) {
            if (y-x +i >= 0 && y-x +i <n) {
                if(m[i][y-x+i]) {
                    return false;
                }
            }
            if (x-i+y >= 0 && x-i+y< n) {
                if (m[i][x-i+y]) {
                    return false;
                }
            }
        }
        return true;
    }
    void dfs(vector<vector<bool>> &m, vector<vector<string>> &ret, int x)
    {
        int n = m.size();
        if (x == n) {
            vector<string> v;
            for(int i=0; i<n; i++) {
                string s(n, '.');
                for(int j=0; j<n; j++) {
                    if(m[i][j]) {
                        s[j] = 'Q';
                    }
                }
                v.push_back(s);
            }
            ret.push_back(v);
        }
        for(int j=0; j<n; j++) {
            if(valid(m, x, j)) {
                m[x][j] = true;
                dfs(m, ret, x+1);
                m[x][j] = false;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ret;
        vector<vector<bool>> m(n, vector<bool>(n, false));
        dfs(m, ret, 0);
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<vector<string>> temp;
    temp = sln.solveNQueens(4);
    system("pause");
    return 0;
}
