/*
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).

Find the minimum element.

You may assume no duplicate exists in the array.
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
        int n = nums.size();
        if(n == 0) {
            return 0;
        }
        int left = 0, right = n -1;
        while(left < right && nums[left] > nums[right] ) {
            int mid = left + (right-left)/2;
            if(nums[mid] > nums[left]) {
                left = mid + 1;
            } else if(nums[mid] < nums[left]) {
                right = mid; // important, not mid -1
            } else {
                left ++;  // mid == left
            }
        }
        return nums[left];
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
