/*
Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.

Subscribe to see which companies asked this question.
*/
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdio>

using namespace std;


class Solution
{
public:
    int longestConsecutive(vector<int>& nums)
    {
        if (nums.empty()) {
            return 0;
        }
        map<int,int> m;
        for(int i=0; i<nums.size(); i++) {
            m[nums[i]] =1;
        }
        int ret = 1;
        for(int i=0; i<nums.size(); i++) {
            int num = 1;
            if(m.count(nums[i]) && m[nums[i]] !=0) {
                m[nums[i]] = 0;
                int left = nums[i] -1;
                while(m.count(left) && m[left] !=0) {
                    m[left] =0;
                    num++;
                    left--;
                }
                int right = nums[i] +1;
                while(m.count(right) && m[right] !=0) {
                    m[right] = 0;
                    num++;
                    right ++;
                }
            }
            ret = max(ret, num);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    //cout << sln.mySqrt(3) << endl;
    system("pause");
    return 0;
}
