/*
215. Kth Largest Element in an Array

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

Note:
You may assume k is always valid, 1 �� k �� array's length.
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
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            int p = partition(nums, k, nums[right], left-1, right);
            swap(nums[right], nums[p]);
            if(p < k-1) {
                left = p + 1;
            } else if(p > k-1) {
                right = p -1;
            } else {
                break;
            }
        }
        return nums[k-1];

    }
    int partition(vector<int> &nums, int k, int pivot, int left, int right)
    {
        do {
            while(nums[++left] > pivot);
            while(right != 0 && nums[--right] < pivot);
            swap(nums[left], nums[right]);
        } while(left<right);
        swap(nums[left], nums[right]);
        return left;
    }
};
int main()
{
    Solution sln;
    int a[] = {3,2,1,5,6,4};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.findKthLargest(v, 5) << endl;
    system("pause");
    return 0;
}
