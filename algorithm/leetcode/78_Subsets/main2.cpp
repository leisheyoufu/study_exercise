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
    void dfs(vector<int> &nums, int s, vector<int> v, vector<vector<int> > &ret)
    {
        ret.push_back(v);
        int n = nums.size();
        for(int i=s; i<n; i++) {
            v.push_back(nums[i]);
            dfs(nums, i+1, v, ret);
            v.pop_back();
        }
    }
    vector<vector<int> > subsets(vector<int>& nums)
    {
        vector<vector<int> > ret;
        dfs(nums, 0, vector<int>(), ret);
        return ret;
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
