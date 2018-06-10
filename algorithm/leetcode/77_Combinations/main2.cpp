/*
77. Combinations

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

For example,
If n = 4 and k = 2, a solution is:

[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
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
    void dfs(int s, int n, int k, vector<int> v, vector<vector<int> > &ret)
    {
        if(v.size() == k) {
            ret.push_back(v);
            return;
        }
        for(int i=s; i<=n; i++) {
            v.push_back(i);
            dfs(i+1, n, k, v, ret);
            v.pop_back();
        }
    }
    vector<vector<int> > combine(int n, int k)
    {
        vector<vector<int> > ret;
        if(n<=0 || k <=0) {
            return ret;
        }
        dfs(1, n, k, vector<int>(), ret);
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<vector<int> > v (2, vector<int>(3, 1));
    v[0][1] = 0;
    sln.combine(4,2);
    system("pause");
    return 0;
}
