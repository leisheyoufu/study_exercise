/*
368. Largest Divisible Subset

Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies:

Si % Sj = 0 or Sj % Si = 0.

If there are multiple solutions, return any subset is fine.

Example 1:

Input: [1,2,3]
Output: [1,2] (of course, [1,3] will also be ok)

Example 2:

Input: [1,2,4,8]
Output: [1,2,4,8]
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
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0) {
            return vector<int>();
        }
        sort(nums.begin(), nums.end());
        vector<int> dp(n,0);
        vector<int> p(n, -1);
        for(int i=0; i<n; i++) {
            dp[i] = 1;
            for(int j=i-1; j>=0; j--) {
                if(nums[i] % nums[j] == 0) {
                    if(dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        p[i] = j;
                    }
                }
            }
        }
        int largest = 0, end = 0;
        for(int i=0; i<n; i++) {
            if(dp[i] > largest) {
                largest = dp[i];
                end = i;
            }
        }
        vector<int> ret;
        while(end != -1) {
            ret.push_back(nums[end]);
            end = p[end];
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {3,4,6,8,12,16,32}; // [4,8,16,32]
    vector<int> ret = sln.largestDivisibleSubset(nums);
    for(auto r : ret) {
        cout << r << " ";
    }
    system("pause");
    return 0;
}
