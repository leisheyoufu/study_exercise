/*

329. Longest Increasing Path in a Matrix
Given an integer matrix, find the length of the longest increasing path.

From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:

nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:

nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int dfs(vector<vector<int>>& matrix, vector<vector<int>> &vis, int val, int x, int y)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        int count = 0;
        if (matrix[y][x] <= val) {
            return count;
        }
        if( vis[y][x]) {
            return vis[y][x];
        }
        if( x<n-1) {
            count = max(count, dfs(matrix, vis, matrix[y][x], x+1,y));
        }

        if( x>0) {
            count = max(count, dfs(matrix, vis, matrix[y][x], x-1,y));
        }

        if( y<m-1) {
            count = max(count, dfs(matrix, vis, matrix[y][x], x,y+1));
        }

        if(y>0) {
            count = max(count, dfs(matrix, vis, matrix[y][x], x,y-1));
        }
        vis[y][x] = count +1;
        return count + 1;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix)
    {
        if (matrix.empty()) {
            return 0;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> vis(m, vector<int> (n, 0));
        int count = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                count = max(count, dfs(matrix, vis, INT_MIN, j, i));
            }
        }
        return count;
    }
};

int main()
{
    Solution sln;
    //int a[][3] = {{9,9,4},{6,6,8},{2,1,1}};
    int a[][2] = {{1,2}};
    vector<vector<int>> v(1, vector<int>(2,0));
    for(int i=0; i<1; i++) {
        for(int j=0; j<2; j++) {
            v[i][j] = a[i][j];
        }
    }
    cout << sln.longestIncreasingPath(v);
    system("pause");
    return 0;
}
