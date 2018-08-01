/*
289. Game of Life

According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):

Any live cell with fewer than two live neighbors dies, as if caused by under-population.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by over-population..
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
Write a function to compute the next state (after one update) of the board given its current state. The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously.

Example:

Input:
[
  [0,1,0],
  [0,0,1],
  [1,1,1],
  [0,0,0]
]
Output:
[
  [0,0,0],
  [1,0,1],
  [0,1,1],
  [0,1,0]
]
Follow up:

Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.
In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    // < 2 , 1->0
    // 2,3 ,  1->0
    // > 3 ,  1 ->0
    // ==3 ,  0->1

    int getNeighbors(int x, int y, vector<vector<int>> &board, int m, int n)
    {
        int last[] = {0, 1, 0, 1, 1};
        int dx[] = {-1,0, 1, -1, 1, -1, 0, 1};
        int dy[] = {-1,-1,-1, 0, 0, 1, 1, 1};
        int count = 0;
        for(int i=0; i<8; i++) {
            int tx = dx[i] + x;
            int ty = dy[i] + y;
            if(tx >=0 && tx <n && ty>=0 && ty <m) {
                count += last[board[ty][tx]];
            }
        }
        return count;
    }
    void gameOfLife(vector<vector<int>>& board)
    {
        int m = board.size();
        if(m ==0) {
            return;
        }
        int n = board[0].size();
        if(n == 0) {
            return;
        }
        int curr[] = {0, 1, 1, 0, 1};
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                int count = getNeighbors(j, i, board, m, n);
                if(board[i][j] == 1) {
                    if(count < 2) {
                        board[i][j] = 3;
                    } else if(count == 2 || count ==3) {
                        board[i][j] = 4;
                    } else if(count > 3) {
                        board[i][j] = 3;
                    }
                } else if(board[i][j] == 0) {
                    if(count == 3) {
                        board[i][j] = 2;
                    }
                }
            }
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                board[i][j] = curr[board[i][j]];
            }
        }
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
