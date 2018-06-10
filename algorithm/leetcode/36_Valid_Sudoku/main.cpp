/*
36. Valid Sudoku

Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.

The Sudoku board could be partially filled, where empty cells are filled with the character '.'.


A partially filled sudoku which is valid.

Note:
A valid Sudoku board (partially filled) is not necessarily solvable. Only the filled cells need to be validated.
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<cstdlib>
using namespace std;


class Solution
{
public:
    bool isValidSudoku(vector<vector<char>>& board)
    {
        // column
        unordered_map<char,bool> map;
        for(int i=0; i<9; i++) {
            map.clear();
            for(int j=0; j<9; j++) {
                if(board[i][j] != '.') {
                    char val = board[i][j];
                    if(map[val] == true) {
                        return false;
                    }
                    map[val] = true;
                }
            }
        }
        // row
        for(int i=0; i<9; i++) {
            map.clear();
            for(int j=0; j<9; j++) {
                if(board[j][i] != '.') {
                    char val = board[j][i];
                    if(map[val] == true) {
                        return false;
                    }
                    map[val] = true;
                }
            }
        }
        //
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                map.clear();
                for(int m=0; m<3; m++) {
                    for(int n=0; n<3; n++) {
                        if(board[i*3+m][j*3+n] != '.') {
                            char val = board[i*3+m][j*3+n];
                            if(map[val] == true) {
                                return false;
                            }
                            map[val] = true;
                        }
                    }
                }
            }
        }
        return true;
    }
};
int main()
{
    string s[9] = {".........","4........","......6..","...38....",".5...6..1","8......6.",".........","..7.9....","...6....."};
    vector<vector<char>> board(9, vector<char>(9,0));
    for(int i=0; i<9; i++) {
        for(int j=0; j<9; j++) {
            board[i][j] = s[i][j];
        }
    }
    Solution sln;
    cout << sln.isValidSudoku(board);
    system("pause");
    return 0;
}
