/*
238. Product of Array Except Self

Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].

Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].

Follow up:
Could you solve it with constant space complexity? (Note: The output array does not count as extra space for the purpose of space complexity analysis.)

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

    vector<int> productExceptSelf(vector<int>& nums)
    {
        int n = nums.size();
        vector<int> ret(n, 1);
        for(int i=1; i<n; i++) {
            ret[i] = ret[i-1] * nums[i-1];
        }
        int right = 1;
        for(int i=n-1; i>=0; i--) {
            ret[i] = right * ret[i];
            right = right * nums[i];
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {1,2,3,4};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    sln.productExceptSelf(v);
    system("pause");
    return 0;
}
