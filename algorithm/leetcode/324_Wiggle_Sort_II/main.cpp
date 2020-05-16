/*
324. Wiggle Sort II

Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....

Example 1:

Input: nums = [1, 5, 1, 1, 6, 4]
Output: One possible answer is [1, 4, 1, 5, 1, 6].
Example 2:

Input: nums = [1, 3, 2, 2, 3, 1]
Output: One possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.

Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?
*/

#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Solution
{
public:
    void wiggleSort(vector<int>& nums)
    {
        int n = nums.size();
        if(n == 0) {
            return;
        }
        vector<int> a(nums);
        sort(a.begin(), a.end());
        int mid = (n+1)/2 -1, right = n-1;
        int m = mid;
        for (int i = 0; i<n;) {
            if (m> -1)
                nums[i++] = a[m--];
            if(right > mid)
                nums[i++] = a[right--];
        }
    }
};
int main()
{
    Solution sln;
    //vector<int> nums = {1, 5, 1, 1, 6, 4, 3, 7};
    vector<int> nums = {1,3,1,3,2,2}; // [2,3,1,3,1,2]
    //vector<int> nums = {1,1,2,1,2,2,1}; // [1,2,1,2,1,2,1]
    //vector<int> nums = {1,1,2,1,2,2}; // [1,2,1,2,1,2,1]
    //vector<int> nums = {4,5,5,6}; // [5,6,4,5]
    sln.wiggleSort(nums);
    for(int num: nums) {
        cout << num << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
