/*
220. Contains Duplicate III
Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference
between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

Example 1:

Input: [1,2,3,1], k = 4, t = 0
Output: true
Example 2:

Input: [1,0,1,1], k = 1, t = 0
Output: true
Example 3:

Input: [4,2], k = 2, t = 1
Output: false
*/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
    {
        map<long, int> m;
        int j = 0;
        for(int i=0; i<nums.size(); i++) {
            if(i - j > k) {
                m.erase(nums[j]);
                j++;
            }
            auto iter = m.lower_bound((long)nums[i] - t);
            if(iter != m.end()) {
                // cl: fist is the value like nums[i], second is the index i
                if(abs(nums[i] -(*iter).first) <=t) {
                    return true;
                }
            }
            m[nums[i]] = i;
        }
        return false;
    }
};
int main()
{
    Solution sln;
    int a[] = {2147483647, -2147483647};
    vector<int> v(a, a + sizeof(a)/ sizeof(int));
    cout << sln.containsNearbyAlmostDuplicate(v, 1, 2147483647) << endl; // false
    system("pause");
    return 0;
}
