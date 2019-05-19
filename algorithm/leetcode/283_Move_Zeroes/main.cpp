/*
283 Move Zeroes

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
Note:

You must do this in-place without making a copy of the array.
Minimize the total number of operations.

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

    void moveZeroes(vector<int>& nums)
    {
        int n = nums.size();
        int count = 0, curr = 0, i = 0;
        while(i < n) {
            if(nums[i] != 0) {
                nums[curr] = nums[i];
                curr ++;
            } else {
                count ++;
            }
            i++;
        }
        for(int i=n-count; i<n; i++) {
            nums[i] = 0;
        }
    }
};

int main()
{
    Solution sln;
    //int a[] = {0,1,0,3,12,0,-1,0};
    //int a[] = {0,1};
    //int a[] = {};
    //int a[] = {0};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    sln.moveZeroes(nums);
    for(int i =0; i<nums.size(); i++) {
        cout << nums[i] << " ";
    }
    system("pause");
    return 0;
}
