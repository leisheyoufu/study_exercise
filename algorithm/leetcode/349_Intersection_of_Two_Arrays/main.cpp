/*
349. Intersection of Two Arrays

Given two arrays, write a function to compute their intersection.

Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].

Note:
Each element in the result must be unique.
The result can be in any order.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

class Solution
{
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        unordered_set<int> s;
        for(int num : nums1) {
            s.insert(num);
        }
        set<int> ret;
        for(int num : nums2) {
            if(s.find(num) != s.end()) {
                ret.insert(num);
            }
        }
        return vector<int>(ret.begin(), ret.end());
    }
};

int main()
{
    Solution sln;
    int a[] = {1, 2, 2, 1};
    int b[] = {2, 2};
    vector<int> v1 (a, a + sizeof(a)/ sizeof(int));
    vector<int> v2 (b, b+sizeof(b)/sizeof(int));
    sln.intersection(v1, v2);
    system("pause");
    return 0;
}
