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
        int m = grid.size();
        if(m == 0) {
            return 0;
        }
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
        dp[0][0] = grid[0][0];
        for(int i=1; i<m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }
        for(int j=1; j<n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
