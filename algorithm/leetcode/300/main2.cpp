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
    int binary_search(vector<int> &a, int r, int target)
    {
        int l = 0;
        while(l <= r) {
            int mid = (l + r)/2;
            if(a[mid] == target) {
                return mid;
            } else if(a[mid] < target) {
                l = mid+1;
            } else {
                r = mid -1;
            }
        }
        return l;
    }

    int lengthOfLIS(vector<int>& nums)
    {
        int n = nums.size();
        if (n<=1) {
            return n;
        }
        int len = 1;
        vector<int> d(n, 0);
        d[0] = nums[0];
        for(int i=1; i<n; i++) {
            int pos = binary_search(d, len -1, nums[i]);
            if(pos > len-1) {
                len = pos + 1;
            }
            d[pos] = nums[i];
        }
        return len;
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
