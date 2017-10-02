/*
239. Sliding Window Maximum

Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].

Note:
You may assume k is always valid, ie: 1 ¡Ü k ¡Ü input array's size for non-empty array.

Follow up:
Could you solve it in linear time?


*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>
#include<list>

using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> ret;
        if(nums.empty()) {
            return ret;
        }
        list<int> l;
        l.push_back(0);
        for(int i=1; i<k; i++) {
            while(!l.empty() && nums[l.back()] <= nums[i]) {
                l.pop_back();
            }
            l.push_back(i);
        }
        ret.push_back(nums[l.front()]);
        for(int i=k; i<nums.size(); i++) {
            if (l.front() + k == i) {
                l.pop_front();
            }
            while(!l.empty() && nums[l.back()] <= nums[i]) {
                l.pop_back();
            }
            l.push_back(i);
            ret.push_back(nums[l.front()]);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int a[] = {5,3,4};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.maxSlidingWindow(v, 1);
    system("pause");
    return 0;
}
