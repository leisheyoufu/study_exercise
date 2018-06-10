/*
Permutations
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
    void backtrack(vector<int> &nums, vector<vector<int>> &ret, vector<int> &result, vector<bool> &vis, int count)
    {
        if(count == 0) {
            ret.push_back(result);
        }
        for(int i=0; i<nums.size(); i++) {
            if(!vis[i]) {
                vis[i] = true;
                result.push_back(nums[i]);
                backtrack(nums, ret, result, vis, count-1);
                vis[i] = false;
                result.pop_back();
            }
        }

    }
    vector<vector<int>> permute(vector<int>& nums)
    {
        vector<vector<int>> ret;
        int count = nums.size();
        if(count ==0) {
            return ret;
        }
        vector<int> result;
        vector<bool> vis(count, false);
        backtrack(nums, ret, result, vis,count);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {3,3,0,0,2,3,2};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    sln.permute(v);
    system("pause");
    return 0;
}
