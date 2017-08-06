/*

200. Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:

    void dfs(vector<vector<char>> &grid, vector<vector<int>> &groups, int level, int &count, int i, int j)
    {
        int m = grid.size();
        int n = grid[0].size();
        if (i<0 || i>m-1 || j<0 || j>n-1) {
            return;
        }
        if(groups[i][j] != 0) {
            return;
        }
        if(grid[i][j] == '0') {
            return;
        }
        if(level == 1) {
            groups[i][j] = ++count;
        } else {
            groups[i][j] = count;
        }
        dfs(grid, groups, level+1, count, i+1, j);
        dfs(grid, groups, level+1, count, i-1, j);
        dfs(grid, groups, level+1, count, i, j+1);
        dfs(grid, groups, level+1, count, i, j-1);
    }

    int numIslands(vector<vector<char>>& grid)
    {
        if(grid.empty()) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        vector<vector<int>> groups(m, vector<int>(n, 0));
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                dfs(grid, groups, 1, count, i, j);
            }
        }
        return count;
    }
};

int main()
{
    Solution sln;
    vector<vector<char>> v;
    cout << sln.numIslands(v);
    system("pause");
    return 0;
}
