/*

581. Shortest Unsorted Continuous Subarray
Given an integer array, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order, too.

You need to find the shortest such subarray and output its length.

Example 1:
Input: [2, 6, 4, 8, 10, 9, 15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
Note:
Then length of the input array is in range [1, 10,000].
The input array may contain duplicates, so ascending order here means <=.
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
    int findUnsortedSubarray(vector<int>& nums)
    {
        int n = nums.size();
        if(n==0 || n == 1) {
            return 0;
        }
        int i =0, left, right;
        while(i<n-1) {
            if(nums[i] <= nums[i+1]) {
                i++;
            } else {
                left = i;
                break;
            }
        }
        if (i == n-1) {
            return 0;
        }
        i = n-1;
        while(i>0) {
            if(nums[i] >= nums[i-1]) {
                i--;
            } else {
                right = i;
                break;
            }
        }
        i = left;
        int min_val = nums[i], max_val = nums[i];
        while(i<=right) {
            min_val = min(min_val, nums[i]);
            max_val = max(max_val, nums[i]);
            i++;
        }
        for(int i=0; i<left; i++) {
            if(nums[i] > min_val) {
                left = i;
                break;
            }
        }
        for(int i=n-1; i>right; i--) {
            if(nums[i] < max_val) {
                right = i;
                break;
            }
        }
        return right - left + 1;
    }
};

int main()
{
    Solution sln;
    vector<int> nums = {1,2,3,4};
    cout << sln.findUnsortedSubarray(nums) << endl;
    system("pause");
    return 0;
}
