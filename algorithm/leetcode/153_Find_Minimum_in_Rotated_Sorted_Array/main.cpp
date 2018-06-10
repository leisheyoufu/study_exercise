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
        if(nums.empty()) {
            return 0;
        }
        int m = nums[0];
        for(int i=1; i<nums.size(); i++) {
            if(nums[i] < m) {
                return nums[i];
            }
        }
        return m;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
