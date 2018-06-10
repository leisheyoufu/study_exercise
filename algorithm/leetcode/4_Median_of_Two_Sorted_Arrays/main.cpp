/*
Median of Two Sorted Arrays
There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]

The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <map>

using namespace std;

class Solution
{
public:
    int findKth(vector<int> &nums1, int start1, vector<int> &nums2, int start2, int k)
    {
        if(start1 == nums1.size()) {
            return nums2[start2 + k];
        }
        if(start2 == nums2.size()) {
            return nums1[start1+ k];
        }
        if (k == 0) {
            return min(nums1[start1], nums2[start2]);
        }
        if( k == 1) {
            if(nums1[start1] < nums2[start2]) {
                if(start1 + 1 == nums1.size() || nums1[start1 + 1] > nums2[start2]) {
                    return nums2[start2];
                }
                return nums1[start1 + 1];
            } else {
                if(start2 + 1 == nums2.size() || nums2[start2 + 1] > nums1[start1]) {
                    return nums1[start1];
                }
                return nums2[start2 + 1];
            }
        }
        int p = k/2;
        int skip = p;
        if(start1 + p >= nums1.size()) {
            p = nums1.size() - start1 -1;
            skip = p + 1;
        }
        if(start2 + p >= nums2.size()) {
            p = nums2.size() - start2 -1;
            skip = p + 1;
        }
        if(nums1[start1 + p] < nums2[start2 + p]) {
            return findKth(nums1, start1 + skip, nums2, start2, k-skip);
        }
        return findKth(nums1, start1, nums2, start2 + skip, k-skip);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int count = nums1.size() + nums2.size();
        if(count & 0x01) {
            return (double)findKth(nums1, 0, nums2, 0, count/2);
        }
        //int a = findKth(nums1, 0, nums2, 0, count/2 -1);
        //int b = findKth(nums1, 0, nums2, 0, count/2);
        return ((double)findKth(nums1, 0, nums2, 0, count/2 -1) + (double)findKth(nums1, 0, nums2, 0, count/2)) /2;
    }
};

int main()
{
    Solution sln;
    int a1[] = {1,3};
    int a2[] = {8,9,10,12,14,16,17,118};
    //int a2[] = {2,4};
    vector<int> nums1(a1, a1+sizeof(a1)/sizeof(int));
    vector<int> nums2(a2, a2+sizeof(a2)/sizeof(int));
    cout << sln.findMedianSortedArrays(nums1, nums2) << endl;
    system("pause");
    return 0;
}
