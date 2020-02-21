/*
120. Triangle

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).

Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int minimumTotal(vector<vector<int>>& triangle)
    {
        int n = triangle.size();
        if(n == 0) {
            return 0;
        }
        vector<int> dp(n, 0);
        dp[0] = triangle[0][0];
        for(int i=1; i<n; i++) {
            dp[i] = dp[i-1] + triangle[i][i];
            for(int j=i-1; j>0; j--) {
                dp[j] = min(dp[j], dp[j-1]) + triangle[i][j];
            }
            dp[0] = dp[0] + triangle[i][0];
        }
        int ret = dp[0];
        for(int i = 1; i<n; i++) {
            ret = min(ret, dp[i]);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int a[] = {-1};
    int b[] = {2,3};
    int c[] = {1,-1,-1};
    vector<vector<int>> v;
    vector<int> v1(a,a+1);
    vector<int> v2(b,b+2);
    vector<int> v3(c,c+3);

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    cout << sln.minimumTotal(v) << endl;
    system("pause");
    return 0;
}
