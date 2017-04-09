/*
64. Minimum Path Sum

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
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
    int minPathSum(vector<vector<int>>& grid)
    {
        if (grid.empty()) {
            return 0;
        }
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> B(m+1, vector<int>(n+1));
        for(int i=2; i<m+1; i++) {
            B[i][0] = INT_MAX;
        }
        for(int i=2; i<n+1; i++) {
            B[0][i] = INT_MAX;
        }
        B[0][0] = 0;
        for(int i=1; i<m+1; i++) {
            for(int j=1; j<n+1; j++) {
                B[i][j] = grid[i-1][j-1] + min(B[i-1][j], B[i][j-1]);
            }
        }
        return B[m][n];
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
