/*
78. Subsets

Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:

[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
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
    vector<vector<int>> subsets(vector<int>& nums)
    {
        vector<vector<int>> ret;
        vector<int> line;
        backtrack(nums, ret, line, 0, nums.size());
        return ret;
    }
    void backtrack(vector<int> &nums, vector<vector<int>> &ret, vector<int> line, int start, int end)
    {
        ret.push_back(line);
        if(start == end) {
            return;
        }
        for(int i=start; i<end; i++) {
            line.push_back(nums[i]);
            backtrack(nums, ret, line, i+1, end);
            line.pop_back();
        }
    }
};

int main()
{
    Solution sln;
    int a[] = {1,2,3};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.subsets(v);
    system("pause");
    return 0;
}
