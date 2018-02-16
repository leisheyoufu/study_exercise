/* 33. Search in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

You are given a target value to search. If found in the array return its index, otherwise return -1.

You may assume no duplicate exists in the array.
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
    int search(vector<int>& nums, int target)
    {
        int n = nums.size();
        if(n == 0) {
            return  -1;
        }
        int left = 0, right = n-1, mid;
        while(left <= right) {
            mid = (left + right) / 2;
            if(nums[mid] == target) {
                return mid;
            }
            if(nums[left] < nums[mid]) {
                if(target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if (nums[left] > nums[mid]) {
                if(target > nums[mid] && target < nums[left]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            } else {
                left ++;
            }
        }
        return -1;
    }
};
int main()
{
    Solution sln;
    int a[] = {4, 5, 6, 7, 0, 1, 2};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.search(nums,2);
    system("pause");
    return 0;
}
