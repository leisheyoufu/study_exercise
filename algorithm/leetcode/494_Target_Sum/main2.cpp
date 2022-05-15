/*
494. Target Sum

You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

    For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".

Return the number of different expressions that you can build, which evaluates to target.



Example 1:

Input: nums = [1,1,1,1,1], target = 3
Output: 5
Explanation: There are 5 ways to assign symbols to make the sum of nums be target 3.
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3

Example 2:

Input: nums = [1], target = 1
Output: 1



Constraints:

    1 <= nums.length <= 20
    0 <= nums[i] <= 1000
    0 <= sum(nums[i]) <= 1000
    -1000 <= target <= 1000
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>
#include<cmath>

using namespace std;

class Solution
{
public:
    int solve(int target,vector<int>&nums)
    {
        vector<int> dp = vector<int>(target+10, 0);
        dp[0] = 1;
        for(int i=0; i<nums.size(); ++i) {
            for(int j=target; j>=nums[i]; --j) {
                //这里从大到小，是因为每个数只能使用一次，这里相当于利用得上一层的结果
                dp[j] += dp[j-nums[i]];
            }
        }
        return dp[target];
    }
    int findTargetSumWays(vector<int>& nums, int S)
    {
        int sum = 0;
        S = abs(S);
        for(int i=0; i<nums.size(); ++i)
            sum += nums[i];
        if(sum < S || (sum+S) % 2 !=0)  return 0;
        int target = (sum+S)/2;
        return solve(target,nums);
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,1,1,1,1};
    cout << sln.findTargetSumWays(nums, 3) << endl; // 5
    nums = {1};
    cout << sln.findTargetSumWays(nums, 1) << endl; // 1
    nums = {100};
    cout << sln.findTargetSumWays(nums, -200) << endl; // 0

    system("pause");
    return 0;
}
