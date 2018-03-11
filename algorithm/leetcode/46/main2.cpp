/*
46. Permutations
Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    void dfs(vector<int> nums, int s, vector<vector<int>> &ret)
    {
        if( s == nums.size()) {
            ret.push_back(nums);
            return;
        }
        for(int i=s; i<nums.size(); i++) {
            swap(nums[i], nums[s]);
            dfs(nums, s+1, ret);
            swap(nums[i], nums[s]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> ret;
        dfs(nums, 0, ret);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {1,2,3,4,5};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.permute(v);
    system("pause");
    return 0;
}
