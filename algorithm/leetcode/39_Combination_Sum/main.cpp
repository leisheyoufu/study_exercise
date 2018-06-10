/*
Combination Sum

Given a set of candidate numbers (C) (without duplicates) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

The same repeated number may be chosen from C unlimited number of times.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [2, 3, 6, 7] and target 7,
A solution set is:
[
  [7],
  [2, 2, 3]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> &ret, int start, vector<int> &cur, vector<int> &candidates, int target)
    {
        if(target < 0) {
            return;
        }
        if(target==0) {
            ret.push_back(cur); // cl, push back do not transfer reference ?
            return;
        }
        for(int i=start; i<candidates.size(); i++) {
            cur.push_back(candidates[i]);
            dfs(ret,i,cur,candidates,target - candidates[i]);
            cur.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> ret;
        vector<int> cur;
        dfs(ret, 0, cur, candidates, target);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {2, 3, 6, 7};
    vector<int> v (a, a+ sizeof(a)/sizeof(int));
    sln.combinationSum(v,7);
    system("pause");
    return 0;
}
