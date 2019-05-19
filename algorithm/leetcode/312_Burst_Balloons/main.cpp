/*
312. Burst Balloons

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:

You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100
Example:

Input: [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
             coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<queue>

using namespace std;

class Solution
{
public:

    int maxCoins(vector<int>& nums)
    {
        vector<int> attrs(nums.size()+2);
        int n = attrs.size();
        for(int i=1; i<n-1; i++) {
            attrs[i] = nums[i-1];
        }
        attrs[0] = attrs[n-1] = 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int k=2; k<n; k++) {
            for(int i=0; i<n-k; i++) {
                int j = i+k;
                for(int p = i+1; p<j; p++) {
                    dp[i][j] = max(dp[i][j], attrs[i] * attrs[p] * attrs[j] + dp[i][p] + dp[p][j]);
                }
            }
        }
        return dp[0][n-1];
    }
};
int main()
{
    Solution sln;
    vector<int> nums = {3,1,5,8};
    cout << sln.maxCoins(nums) << endl;
    system("pause");
    return 0;
}
