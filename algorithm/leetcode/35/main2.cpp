/*
35. Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
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
    int searchInsert(vector<int>& nums, int target)
    {
        int n = nums.size();
        if(n < 1) {
            return 0;
        }
        int left = 0, right = n-1, mid;
        while(left <= right) {
            mid = (left+ right)/2;
            if(nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else if(nums[mid] > target) {
                right = mid - 1;
            }
        }
        return left;
    }
};
int main()
{
    Solution sln;
    int a[] = {1,3,5,6};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.searchInsert(nums,5);  // 2
    cout << sln.searchInsert(nums,2);  // 1
    cout << sln.searchInsert(nums,7);  // 4
    cout << sln.searchInsert(nums,0);  // 0
    system("pause");
    return 0;
}
