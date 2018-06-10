/*
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 ¡Ü k ¡Ü array's length.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    int findKthLargest(vector<int>& nums, int k)
    {
        return quick_sort(nums, k, 0, nums.size()-1);
    }
    int quick_sort(vector<int> &nums, int k, int start, int end)
    {
        int num = nums[start];
        int l = start;
        int r = end +1;
        do {
            while(l<r-1 && num < nums[++l]);
            while(l<r && num > nums[--r]);
            swap(nums[l], nums[r]);
        } while(l<r);
        if(nums[start] < nums[l]) {
            swap(nums[start], nums[l]);
        }
        if(l == k - 1) {
            return nums[l];
        } else if( l < k -1 ) {
            return quick_sort(nums, k, l+1, end);
        } else {
            return quick_sort(nums, k, start, l-1);
        }
    }
};
int main()
{
    Solution sln;
    int a[] = {3,2,1,5,6,4, 5,7};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.findKthLargest(v, 8) << endl;
    system("pause");
    return 0;
}
