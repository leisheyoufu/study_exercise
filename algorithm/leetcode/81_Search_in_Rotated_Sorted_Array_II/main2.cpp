/*
Search in Rotated Sorted Array II

Follow up for "Search in Rotated Sorted Array":
What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Write a function to determine if a given target is in the array.

The array may contain duplicates.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool search(vector<int>& nums, int target)
    {
        int r = nums.size() -1;
        if(r== 0) {
            return false;
        }
        r--;
        int l =0;
        while(l <= r) {
            int mid = (l+r)/2;
            if (nums[mid] == target) {
                return true;
            }
            if(nums[mid] < nums[l]) {
                if(nums[mid] < target && nums[r] >= target) {
                    l = mid + 1;
                } else {
                    r = mid -1;
                }
            } else if(nums[mid] > nums[l]) {
                if(nums[mid] > target && nums[l] <= target) {
                    r = mid -1;
                } else {
                    l = mid +1;
                }
            } else {
                l = l + 1;
            }
        }
        return false;
    }
};
int main()
{
    Solution sln;
    // int a[] = {1,3,3,4,5,5,7,90,101,101,102};
    int a[] = {1};
    vector<int> nums(a,a+sizeof(a)/sizeof(int));
    cout << sln.search(nums,0) << endl;
    system("pause");
    return 0;
}
