/*
327. Count of Range Sum

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:

Input: nums = [-2,5,-1], lower = -2, upper = 2,
Output: 3
Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include <functional>
#include<queue>

using namespace std;

class Solution
{
public:
    int countRangeSum(vector<int>& nums, int lower, int upper)
    {
        int n = nums.size();
        if (n <= 0) {
            return 0;
        }
        vector<long long> sums(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sums[i+1] = sums[i] + nums[i];
        }
        return merge(sums, 0, n, lower, upper);
    }

    int merge(vector<long long>& sums, int start, int end, int lower, int upper)
    {
        if (start >= end) {
            return 0;
        }
        int mid = start + (end - start) / 2;
        int count = merge(sums, start, mid, lower, upper) + merge(sums, mid + 1, end, lower, upper);
        vector<long long> tmp(end - start + 1, 0);
        int j = mid + 1, k = mid + 1, t = mid + 1, i = start, r = 0;
        for (; i <= mid; ++i, ++r) {
            while (j <= end && sums[j] - sums[i] <= upper) ++j;
            while (k <= end && sums[k] - sums[i] < lower) ++k;
            count += j - k;
            while (t <= end && sums[t] <= sums[i]) tmp[r++] = sums[t++];
            tmp[r] = sums[i];
        }
        for (int i = 0; i < r; ++i) {
            sums[start + i] = tmp[i];
        }
        return count;
    }
};
int main()
{
    Solution sln;
    //vector<int> nums = {-2, 5, 1,3,-5,6,-2};
    vector<int> nums = {2147483647,-2147483648,-1,0};
    cout << sln.countRangeSum(nums, -1, 0) << endl;
    system("pause");
    return 0;
}
