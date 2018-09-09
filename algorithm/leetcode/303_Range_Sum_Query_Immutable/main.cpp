/*
303. Range Sum Query - Immutable

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
Note:
You may assume that the array does not change.
There are many calls to sumRange function.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class NumArray
{

public:
    vector<int> nums;
    NumArray(vector<int> nums)
    {
        int n = nums.size();
        if(n == 0) {
            return;
        }
        this->nums.resize(n+1);
        this->nums[0] =0;
        for(int i=0; i<n; i++) {
            this->nums[i+1] = this->nums[i] + nums[i];
        }
    }

    int sumRange(int i, int j)
    {
        if(i<0 || j< i || j>=this->nums.size()) {
            return 0;
        }

        return this->nums[j+1] - this->nums[i];
    }
};

int main()
{
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray a(nums);

    cout << a.sumRange(0,2) << endl;  // 1
    cout << a.sumRange(2,5) << endl;
    cout << a.sumRange(0,5) << endl;
    return 0;
}
