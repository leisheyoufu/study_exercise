/*
136. Single Number
Given an array of integers, every element appears twice except for one. Find that single one.

Note:
Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;


class Solution
{
public:
    int singleNumber(vector<int>& nums)
    {
        int ret = 0;
        for(int i=0; i<nums.size(); i++) {
            ret ^= nums[i];
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
