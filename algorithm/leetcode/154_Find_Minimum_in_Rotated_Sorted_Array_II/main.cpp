/*
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

What if duplicates are allowed?

Would this affect the run-time complexity? How and why?
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int findMin(vector<int>& nums)
    {
        if(nums.empty()) {
            return 0;
        }
        if (nums.size() == 1) {
            return nums[0];
        }
        int low = 0;
        int high = nums.size()-1;
        while(low < high && nums[low] >=nums[high]) {
            int mid = low + (high - low) /2;
            if (nums[mid] > nums[low]) {
                low = mid +1;
            } else if(nums[mid] < nums[low]) {
                high = mid;
            } else {
                low++;
            }
        }
        return nums[low];
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
