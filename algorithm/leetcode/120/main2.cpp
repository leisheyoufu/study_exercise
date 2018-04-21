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
        int m = triangle.size();
        if(m == 0) {
            return 0;
        }
        vector<int> dp(m, 0);
        for(int j=0; j<m; j++) {
            dp[j] = triangle[m-1][j];
        }
        for(int i=m-2; i>=0; i--) {
            for(int j=0; j<=i; j++) {
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
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
