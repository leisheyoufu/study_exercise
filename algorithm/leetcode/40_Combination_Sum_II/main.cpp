/*
Combination Sum II

Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.

Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8,
A solution set is:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
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
        if(target==0) {
            ret.push_back(cur); // cl, push back do not transfer reference ? if java, new should be used here to copy the item
            return;
        }
        for(int i=start; i<candidates.size(); i++) {
            if(candidates[i] > target) {
                return;
            }
            if(i >0 && candidates[i] == candidates[i-1] && i>start) {
                continue;   // avoid [1,7], [1,7]
            }
            cur.push_back(candidates[i]);
            dfs(ret,i+1,cur,candidates,target - candidates[i]);
            cur.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        vector<vector<int>> ret;
        vector<int> cur;
        sort(candidates.begin(), candidates.end());
        dfs(ret, 0, cur, candidates, target);
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {10, 1, 2, 7, 6, 1, 5};
    vector<int> v (a, a+ sizeof(a)/sizeof(int));
    sln.combinationSum2(v,8);
    system("pause");
    return 0;
}
