/*
300. Longest Increasing Subsequence

Given an unsorted array of integers, find the length of longest increasing subsequence.

For example,
Given [10, 9, 2, 5, 3, 7, 101, 18],
The longest increasing subsequence is [2, 3, 7, 101], therefore the length is 4. Note that there may be more than one LIS combination, it is only necessary for you to return the length.

Your algorithm should run in O(n2) complexity.

Follow up: Could you improve it to O(n log n) time complexity?

Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.


*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:

    int lengthOfLIS(vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) {
            return 0;
        }
        int max_len = 1;
        vector<int> dp(n, 1);
        for(int i=1; i<n; i++) {
            for(int j=i-1; j>=0; j--) {
                if(nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    max_len = max(dp[i], max_len);
                }
            }
        }
        return max_len;
    }
};
int main()
{
    Solution sln;
    int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    cout << sln.lengthOfLIS(v) << endl; // 4
    system("pause");
    return 0;
}
