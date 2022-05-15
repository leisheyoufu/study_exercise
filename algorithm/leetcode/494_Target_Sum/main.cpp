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
    int findTargetSumWays(vector<int>& nums, int target)
    {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int count = 0;
        dfs(nums, target, 0, 0, count);
        return count;

    }
    void dfs(vector<int>& nums, int target, int sum, int index, int &count)
    {
        if (index == nums.size()) {
            if (target == sum) {
                count++;
            }
            return;
        }
        dfs(nums, target, sum - nums[index], index+1, count);
        dfs(nums, target, sum + nums[index], index+1, count);
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,1,1,1,1};
    cout << sln.findTargetSumWays(nums, 3) << endl; // 5
    nums = {1};
    cout << sln.findTargetSumWays(nums, 1) << endl; // 1
    system("pause");
    return 0;
}
