/*

53. Maximum Subarray

Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int max_sub = nums[0];
        int max_ret = nums[0];
        for(int i=1; i<n; i++) {
            if(max_sub <0) {
                max_sub = nums[i];
            } else {
                max_sub += nums[i];
            }
            if(max_sub > max_ret) {
                max_ret = max_sub;
            }
        }
        return max_ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {-2,1,-3,4,-1,2,1,-5,4};
    int size = sizeof(a)/sizeof(int);
    vector<int> v(a,a+size);
    cout << sln.maxSubArray(v) << endl;
    system("pause");
    return 0;
}
