/*
152. Maximum Product Subarray
Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        if (nums.empty()) {
            return 0;
        }
        int global_max = nums[0];
        int curr_max = nums[0];
        int curr_min = nums[0];
        for(int i=1; i<nums.size(); i++) {
            int temp = curr_max;
            curr_max = max(curr_max * nums[i], nums[i]);
            curr_max = max(curr_max, nums[i] * curr_min);
            curr_min = min(curr_min * nums[i], nums[i]);
            curr_min = min(curr_min, temp * nums[i]);
            global_max = max(global_max, curr_max);
        }
        return global_max;
    }
};

int main()
{
    Solution sln;
    int a[] = {0, 2,0,-3,3,-2,4};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.maxProduct(nums);
    system("pause");
    return 0;
}
