/*
40.  Combination Sum II

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
    void dfs(vector<int>& candidates, int target, int sum, int start, vector<int> curr, vector<vector<int>> &ret)
    {
        if(sum == target) {
            ret.push_back(curr);
            return;
        }
        for(int i=start; i<candidates.size(); i++) {
            if(sum + candidates[i] > target) {
                break;
            }
            if( i> 0 && candidates[i-1] == candidates[i] && i > start) {
                continue;  // if i>start, i-1 has been popped
            }
            curr.push_back(candidates[i]);
            dfs(candidates, target, sum + candidates[i], i + 1, curr, ret);
            curr.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        vector<int> curr;
        vector<vector<int>> ret;
        dfs(candidates, target, 0, 0, curr, ret);
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
