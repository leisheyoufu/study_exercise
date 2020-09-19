/*
416. Partition Equal Subset Sum

Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Note:

Each of the array element will not exceed 100.
The array size will not exceed 200.


Example 1:

Input: [1, 5, 11, 5]

Output: true

Explanation: The array can be partitioned as [1, 5, 5] and [11].


Example 2:

Input: [1, 2, 3, 5]

Output: false

Explanation: The array cannot be partitioned into equal sum subsets.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    /*
    bool dfs(vector<int> &nums, int index, int curr, int total)
    {
        if(index >= nums.size()) {
            return false;
        }
        if(curr > total) {
            return false;
        }
        if (curr == total) {
            return true;
        }
        if (dfs(nums, index + 1, curr + nums[index], total)) {
            return true;
        }
        return dfs(nums, index +1, curr, total);
    }
    bool canPartition(vector<int>& nums)
    {
        int total = 0;
        for(int num: nums) {
            total += num;
        }
        if (total % 2 != 0) {
            return false;
        }
        total /= 2;
        return dfs(nums, 0, 0, total);
    }
    */
    bool canPartition(vector<int>& nums)
    {
        int total = 0;
        for(int num: nums) {
            total += num;
        }
        if (total % 2 != 0) {
            return false;
        }
        vector<bool> dp(total, false);
        dp[0] = true;
        for(int num: nums) {
            for(int i=total/2; i>=0; i--) {
                if(dp[i]) {
                    dp[i+num] =true;
                }
            }
            if(dp[total/2]) {
                return true;
            }
        }
        return false;
    }

};
int main()
{
    // [1,2147483646] 1
    Solution sln;
    vector<int> nums = {1, 5, 11, 5};
    cout << sln.canPartition(nums) << endl; // true
    nums = {1, 2, 3, 5};
    cout << sln.canPartition(nums) << endl; // false
    nums = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,100};
    cout << sln.canPartition(nums) << endl; // false
    system("pause");
    return 0;
}
