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
    // k = 0 , the first one
    int findKth(vector<int> &nums1, int s1, vector<int> &nums2, int s2, int k)
    {
        int n1 = nums1.size(), n2 = nums2.size();
        if(s1 == n1) {
            return nums2[k];
        }
        if(s2 == n2) {
            return nums1[k];
        }
        if (k==0) {
            return min(nums1[s1], nums2[s2]);
        }
        if (s1 + 1 == n1) {
            if(nums1[s1] > nums2[s2+k-1]) {
                if (s2+k ==n2) {
                    return nums1[s1];
                }
                return min(nums1[s1], nums2[s2+k]);
            }
            return nums2[s2+k-1];
        }
        if (s2 + 1 == n2) {
            if(nums2[s2] > nums1[s1+k-1]) {
                if(s1+k == n1) {
                    return nums2[s2];
                }
                return min(nums2[s2], nums1[s1+k]);
            }
            return nums1[s1+k-1];
        }
        if (k == 1) {
            return min(max(nums1[s1], nums2[s2]), min(nums1[s1+1], nums2[s2+1]));
        }
        int p1 = s1 + k/2, p2 = s2 + k/2;
        if(s1 + k/2 >= n1) {
            p1 = n1-1;
        } else if(s2 + k/2 >= n2) {
            p2 = n2 - 1;
        }
        if (nums1[p1] < nums2[p2]) {
            return findKth(nums1, p1, nums2, s2, k - (p1-s1));
        }
        return findKth(nums1, s1, nums2, p2, k - (p2-s2));
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        int n1 = nums1.size(), n2 = nums2.size();
        int n = n1 + n2;
        if(n & 0x1) {
            return findKth(nums1, 0, nums2, 0, n/2);
        }
        int ret1 = findKth(nums1, 0, nums2, 0, n/2);
        int ret2 = findKth(nums1, 0, nums2, 0, n/2-1);
        return (ret1 + ret2)/2.0;
    }
};

int main()
{
    Solution sln;
    int a1[] = {1,5};
    int a2[] = {2,3,4,6,7,8};  // 4.5
    //int a2[] = {2,4}; // 2.5
    vector<int> nums1(a1, a1+sizeof(a1)/sizeof(int));
    vector<int> nums2(a2, a2+sizeof(a2)/sizeof(int));
    cout << sln.findMedianSortedArrays(nums1, nums2) << endl;  // 4.5
    system("pause");
    return 0;
}
