/*
88. Merge Sorted Array

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

Note:
You may assume that nums1 has enough space (size that is greater or equal to m + n) to hold additional elements from nums2. The number of elements initialized in nums1 and nums2 are m and n respectively.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        if (n ==0) {
            return;
        }
        // shift all of the elements with n steps.
        for(int i=0; i<m; i++) {
            nums1[m+n-i-1] = nums1[m-i-1];
        }
        int i = n, j = 0, k = 0;
        while(k<m+n) {
            if(i == m+n) {
                nums1[k++] = nums2[j++];
            } else if(j == n) {
                nums1[k++] = nums1[i++];
            } else if(nums1[i]< nums2[j]) {
                nums1[k++] = nums1[i++];
            } else {
                nums1[k++] = nums2[j++];
            }
        }
    }
};

int main()
{
    Solution sln;
    int a[] = {4,5,7,10,12};
    int b[] = {1,6,8,9,13,14,15};
    vector<int> v1(a, a+sizeof(a)/sizeof(int));
    vector<int> v2(b, b+sizeof(b)/sizeof(int));
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    v1.resize(sizeof(a)/sizeof(int)+ sizeof(b)/sizeof(int), 0);
    sln.merge(v1, sizeof(a)/sizeof(int), v2, sizeof(b)/sizeof(int));
    for(int i=0; i<sizeof(a)/sizeof(int)+ sizeof(b)/sizeof(int); i++) {
        printf("%d ", v1[i]);
    }
    system("pause");
    return 0;
}
