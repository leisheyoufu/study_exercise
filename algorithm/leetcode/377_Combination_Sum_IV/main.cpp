/*
377. Combination Sum IV

Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.



Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

class Solution
{
public:
    int combinationSum4(vector<int>& nums, int target)
    {
        int n = nums.size();
        if(n==0 || target == 0) {
            return 0;
        }
        vector<unsigned long> dp(target+1, 0);
        dp[0] = 1;
        for(int i=1; i<=target; i++) {
            for(auto num : nums) {
                if(i -num >=0) {
                    dp[i] += dp[i-num];
                }
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,2,3};
    cout << sln.combinationSum4(nums, 4) << endl;  // 7
    nums = {3,33,333};
    cout << sln.combinationSum4(nums, 10000) << endl;

    system("pause");
    return 0;
}
