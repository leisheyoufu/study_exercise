/*
34. Search for a Range

Given an array of integers sorted in ascending order, find the starting and ending position of a given target value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the target is not found in the array, return [-1, -1].

For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
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
    vector<int> searchRange(vector<int>& nums, int target)
    {
        vector<int> ret;
        int n = nums.size();
        int left = 0, right = n - 1;
        int mid, found = -1;
        while(left <= right) {
            mid = (left+right) /2;
            if(nums[mid] == target) {
                found = mid;
                break;
            } else if(nums[mid] < target) {
                left = mid + 1;
            } else if(nums[mid] > target) {
                right = mid -1;
            }
        }
        if (found == -1) {
            ret.push_back(-1);
            ret.push_back(-1);
            return ret;
        }
        int i = 0;
        while(mid -i -1 >=0) {
            if(nums[mid-i-1] != target) {
                break;
            }
            i++;
        }
        ret.push_back(mid - i);
        i = 0;
        while(mid + i + 1 <n) {
            if(nums[mid + i + 1] != target) {
                break;
            }
            i++;
        }
        ret.push_back(mid + i);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {5, 7, 7, 8, 8, 10};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    sln.searchRange(nums,10);
    system("pause");
    return 0;
}
