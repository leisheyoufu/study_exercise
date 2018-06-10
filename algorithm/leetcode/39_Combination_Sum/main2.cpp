/*
39. Combination Sum

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
            curr.push_back(candidates[i]);
            dfs(candidates, target, sum + candidates[i], i, curr, ret);
            curr.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
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
    int a[] = {2, 3, 6, 7};
    vector<int> v (a, a+ sizeof(a)/sizeof(int));
    sln.combinationSum(v,7);
    system("pause");
    return 0;
}
