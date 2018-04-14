/*
213. House Robber II

Note: This is an extension of House Robber.

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
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
    int rob(vector<int>& nums)
    {
        int pre_max = 0;
        int curr_max = 0;
        int n = nums.size();
        if(n == 1) {
            return nums[0];
        }
        for(int i=0; i<n-1; i++) {
            int temp = curr_max;
            curr_max = max(curr_max, pre_max+nums[i]);
            pre_max = temp;
        }
        int ret = curr_max;
        curr_max = 0;
        pre_max = 0;
        for(int i=1; i<n; i++) {
            int temp = curr_max;
            curr_max = max(curr_max, pre_max+nums[i]);
            pre_max = temp;
        }
        ret = max(ret, curr_max);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {10, 9, 2, 5, 3, 7, 101, 18};
    vector<int> v(a, a + sizeof(a)/sizeof(int));
    cout << sln.rob(v) << endl; // 116
    system("pause");
    return 0;
}
