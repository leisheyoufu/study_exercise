/*
287. Find the Duplicate Number

Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

Note:
You must not modify the array (assume the array is read only).
You must use only constant, O(1) extra space.
Your runtime complexity should be less than O(n2).
There is only one duplicate number in the array, but it could be repeated more than once.


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
    int findDuplicate(vector<int>& nums)
    {
        if(nums.empty() || nums.size()==1) {
            return -1;
        }
        for(int i=0; i<nums.size(); i++) {
            int j = i;
            int k = nums[j];
            while(j >0 && nums[j] < j+1 && nums[k-1] != k) {
                swap(nums[j], nums[k-1]);
                k = nums[j];
            }

        }
        return nums[nums.size()-1];
    }
};
int main()
{
    Solution sln;
    int a[] = {7,1,2,8,4,5,6,7,3};
    //int a[] = {4,3,1,4,2};
    //int a[] = {14,16,12,1,16,17,6,8,5,19,16,13,16,3,11,16,4,16,9,7};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.findDuplicate(nums);
    system("pause");
    return 0;
}
