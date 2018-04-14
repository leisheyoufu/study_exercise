/*
198. House Robber

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

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
        for(int num : nums) {
            int temp = curr_max;
            curr_max = max(curr_max, pre_max + num);
            pre_max = temp;
        }
        return curr_max;
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
