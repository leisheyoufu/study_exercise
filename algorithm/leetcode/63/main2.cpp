/*
63. Unique Paths II

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
using namespace std;

class Solution
{
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
    {
        int m = obstacleGrid.size();
        if (m ==0) {
            return 0;
        }
        int n = obstacleGrid[0].size();
        if(obstacleGrid[0][0] == 1) {
            return 0;
        }
        vector<vector<int>> p(m, vector<int>(n, 0));
        p[0][0] = 1;
        for(int i=1; i<m; i++) {
            if(obstacleGrid[i][0] == 1) {
                p[i][0] = 0;
            } else {
                p[i][0] = p[i-1][0];
            }
        }
        for(int i=1; i<n; i++) {
            if(obstacleGrid[0][i] == 1) {
                p[0][i] = 0;
            } else {
                p[0][i] = p[0][i-1];
            }
        }
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(obstacleGrid[0][i] == 1) {
                    p[i][j] = 0;
                } else {
                    p[i][j] = p[i-1][j] + p[i][j-1];
                }
            }
        }
        return p[m-1][n-1];
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
