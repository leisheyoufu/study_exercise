/*
209. Minimum Size Subarray Sum

Given an array of n positive integers and a positive integer s, find the minimal length of a contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

For example, given the array [2,3,1,2,4,3] and s = 7,
the subarray [4,3] has the minimal length under the problem constraint.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int s, vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) {
            return 0;
        }
        int minL = INT_MAX;
        int left = 0;
        int sum = 0;
        for(int i=0; i<n; i++) {
            sum += nums[i];
            while(sum >= s) {
                minL = min(minL, i-left + 1);
                sum -= nums[left++];
            }
        }
        if(minL == INT_MAX) {
            return 0;
        }
        return minL;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
