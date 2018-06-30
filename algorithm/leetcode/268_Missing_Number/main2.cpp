/*
268. Missing Number

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

Example 1:

Input: [3,0,1]
Output: 2
Example 2:

Input: [9,6,4,2,3,5,7,0,1]
Output: 8
Note:
Your algorithm should run in linear runtime complexity. Could you implement it using only constant extra space complexity?
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        int n = nums.size();
        int sum1 = 0, sum2 = 0;
        for(int i=0; i<n; i++) {
            sum1 += i;
            sum2 += nums[i];
        }
        sum1 += n;
        return sum1 - sum2;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
