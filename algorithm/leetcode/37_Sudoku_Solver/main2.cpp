/*
Sudoku Solver

Write a program to solve a Sudoku puzzle by filling the empty cells.

Empty cells are indicated by the character '.'.

You may assume that there will be only one unique solution.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
    bool is_valid(vector<vector<char>>& board, int m, int n, char val)
    {
        for(int i=0; i<9; i++) {
            if(board[m][i] == val) {
                return false;
            }
            if(board[i][n] == val) {
                return false;
            }
        }
        int p = m/3;
        int q = n/3;
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                if(board[p*3+i][q*3+j] == val) {
                    return false;
                }
            }
        }
        return true;
    }
    bool dfs(vector<vector<char>>& board, int s)
    {
        if(s == 81) {
            return true;
        }
        int m = s/9;
        int n = s%9;
        if(board[m][n] != '.') {
            return dfs(board, s+1);
        }
        for(int i=1; i<=9; i++) {
            if(!is_valid(board, m, n, i+'0')) {
                continue;
            }
            board[m][n] = i + '0';
            if(dfs(board,s+1)) {
                return true;
            }
            board[m][n] = '.';
        }
        return false;
    }
    void solveSudoku(vector<vector<char>>& board)
    {
        dfs(board, 0);
    }
};
int main()
{
    system("pause");
    return 0;
}
