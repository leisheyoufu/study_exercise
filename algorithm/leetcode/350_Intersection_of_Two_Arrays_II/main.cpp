/*
350. Intersection of Two Arrays II

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2].

Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
Follow up:
What if the given array is already sorted? How would you optimize your algorithm?
What if nums1's size is small compared to nums2's size? Which algorithm is better?
What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
    {
        unordered_map<int, int> m;
        for(int num : nums1) {
            if(m.find(num) != m.end()) {
                m[num]++;
            } else {
                m[num] = 1;
            }
        }
        vector<int> ret;
        for(int num : nums2) {
            if(m.find(num) != m.end() && m[num]) {
                ret.push_back(num);
                m[num]--;
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int a[] = {1, 2, 2, 1};
    int b[] = {2, 2};
    vector<int> v1 (a, a + sizeof(a)/ sizeof(int));
    vector<int> v2 (b, b+sizeof(b)/sizeof(int));
    sln.intersect(v1, v2);
    system("pause");
    return 0;
}
