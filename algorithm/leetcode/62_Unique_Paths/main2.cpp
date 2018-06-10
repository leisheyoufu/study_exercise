/*
Unique Paths

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?


Above is a 3 x 7 grid. How many possible unique paths are there?

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
    /*
    int uniquePaths(int m, int n)
    {
    	if(m <=0 || n <= 0) {
    		return 0;
    	}
        if(m == 1 && n == 1) {
    		return 1;
    	} else if(m==1) {
    		return uniquePaths(1, n-1);
    	} else if(n==1) {
    		return uniquePaths(m-1, 1);
    	}
    	return uniquePaths(m-1, n) + uniquePaths(m, n-1);
    }
    */
    int uniquePaths(int m, int n)
    {
        if(m <=0 || n <= 0) {
            return 0;
        }
        //vector<vector<int>> dp(m, vector<int>(n, 0));
        int dp[101][101]; // much faster
        for(int i=0; i<m; i++) {
            dp[i][0] = 1;
        }
        for(int j=1; j<n; j++) {
            dp[0][j] = 1;
        }
        for(int i = 1; i<m; i++) {
            for(int j=1; j<n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};
int main()
{
    Solution sln;
    cout << sln.uniquePaths(2,3) << endl; // 3
    cout << sln.uniquePaths(2,1) << endl; // 1
    cout << sln.uniquePaths(1,1) << endl; // 1
    system("pause");
    return 0;
}
