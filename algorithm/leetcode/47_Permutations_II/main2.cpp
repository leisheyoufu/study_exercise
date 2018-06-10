/*
Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
#include<iostream>
#include<string>
/* 47. Permutations II

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/

#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    void dfs(vector<int> nums, int s, set<vector<int>> &ret)
    {
        if(s == nums.size()) {
            ret.insert(nums);
            return;
        }
        for(int i=s; i<nums.size(); i++) {
            if (i!=s && nums[i] == nums[s]) {
                continue;
            }
            swap(nums[i], nums[s]);
            dfs(nums, s+1, ret);
            swap(nums[i], nums[s]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums)
    {
        set<vector<int>> ret;
        dfs(nums, 0, ret);
        return vector<vector<int>> (ret.begin(), ret.end());;
    }
};
int main()
{
    Solution sln;
    int a[] = {1,1,2};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.permuteUnique(v);
    system("pause");
    return 0;
}
