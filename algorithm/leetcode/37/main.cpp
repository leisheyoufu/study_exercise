#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
	bool is_valid(vector<vector<char>>& board, int i, int j, char val)
	{
		for(int k=0;k<9;k++) {
			if(k != j && board[i][k] == val) { // check i th row
				return false;
			}
			if(k != i && board[k][j] == val) { // check i th column
				return false;
			}
		}
		int i_mul = i/3;
		int j_mul = j/3;
		for(int x=i_mul*3; x<i_mul*3+3; x++) {		
			for(int y=j_mul*3; y<j_mul*3+3;y++) {
				if(x!= i && y != j && board[x][y] == val) {
					return false;
				}
			}
		}
		return true;
	}


	bool dfs(vector<vector<char>>& board, int i, int j, int n)
	{
		if(i==n) {
			return true;
		} else if(j==n) {
			return dfs(board, i+1, 0, n);
		} else if(board[i][j] != '.') {
			return dfs(board, i, j+1, n);
		} else {
			for(int k=1; k<=9; k++) {
				char val = k+'0';
				if(is_valid(board, i, j, val)) {
					board[i][j] = val;
					if( dfs(board, i, j+1, n)) {
						return true;
					}
					board[i][j] = '.';
				}
			}
		}
		return false;
	}
    void solveSudoku(vector<vector<char>>& board) {
		if (board.size() == 0 || board[0].size() == 0) 
			return;
        dfs(board,0,0,9);
    }
};
int main()
{
    system("pause");
    return 0;
}