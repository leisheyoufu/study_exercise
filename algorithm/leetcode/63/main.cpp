/*
Unique Paths II

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
The total number of unique paths is 2.

Note: m and n will be at most 100.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        int m = obstacleGrid.size();
        if(m==0) {
            return 0;
        }
        int n = obstacleGrid[0].size();
        if(n==0) {
            return 0;
        }
        if(obstacleGrid[0][0] == 1 || obstacleGrid[m-1][n-1]) {
            return 0;
        }
        vector<vector<int>> dp(m, vector<int>(n,0));
        dp[0][0] = 1;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(obstacleGrid[i][j]) {
                    dp[i][j] = 0;
                    continue;
                }
                if(i==0 && j>0) {
                    dp[i][j] = dp[i][j-1];
                } else if(j==0 && i>0) {
                    dp[i][j] = dp[i-1][j];
                } else if(j>0 && i>0) {
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }
            }
        }
        return dp[m-1][n-1];
    }

};
int main()
{
    Solution sln;
    cout << sln.uniquePaths(2,3);
    system("pause");
    return 0;
}
