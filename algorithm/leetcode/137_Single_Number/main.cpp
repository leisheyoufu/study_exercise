/*
137. Single Number II
Given a non-empty array of integers, every element appears three times except for one, which appears exactly once. Find that single one.

Note:

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

Example 1:

Input: [2,2,3,2]
Output: 3

Example 2:

Input: [0,1,0,1,0,1,99]
Output: 99

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
        for(int i=0; i<32; i++) {
            int sum = 0;
            for(int j=0; j<nums.size(); j++) {
                sum += (nums[j] >> i) & 1;
            }
            if(sum % 3 == 1) {
                ret |= 1 << i;
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<int> a = {2,2,3,2};
    cout << sln.singleNumber(a) << endl; //3
    vector<int> b = {0,1,0,1,0,1,99};
    cout << sln.singleNumber(b) << endl; // 99
    system("pause");
    return 0;
}
