/*
128. Longest Consecutive Sequence

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
#include<unordered_set>
#include<algorithm>
#include<cstdio>

using namespace std;


class Solution
{
public:
    int longestConsecutive(vector<int>& nums)
    {
        unordered_set<int> m;
        int ret = 0;
        for(auto num : nums) {
            m.insert(num);
        }
        for(auto num : nums) {
            if(m.find(num) == m.end()) {
                continue;
            }
            m.erase(num);
            int left = num;
            while(m.find(left-1) != m.end()) {
                left --;
                m.erase(left);
            }
            int right = num;
            while(m.find(right+1) != m.end()) {
                right ++;
                m.erase(right);
            }
            ret = max(ret, right-left + 1);
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
