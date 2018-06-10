/*
221. Maximal Square

Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;



class Solution
{
public:
    int maximalSquare(vector<vector<char>>& matrix)
    {
        int m = matrix.size();
        if(m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        if(n == 0) {
            return 0;
        }
        int ret = 0;
        vector<vector<int> > dp(m, vector<int>(n, 0));
        for(int i=0; i<m; i++) {
            dp[i][0] = matrix[i][0] - '0';
            ret = max(dp[i][0], ret);
        }
        for(int j=0; j<n; j++) {
            dp[0][j] = matrix[0][j] - '0';
            ret = max(dp[0][j], ret);
        }
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                if(matrix[i][j] == '1') {
                    dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
                    ret = max(dp[i][j], ret);
                }
            }
        }
        return ret * ret;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
