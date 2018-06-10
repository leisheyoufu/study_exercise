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
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> ret;
        vector<int> line;
        backtrack(n, k, 0, ret, line);
        return ret;
    }
    void backtrack(int n, int k, int start, vector<vector<int>> &ret, vector<int> line)
    {
        if(k==start) {
            ret.push_back(line);
            return;
        }
        int tail = 0;
        if (!line.empty()) {
            tail = line[line.size()-1];
        }
        for(int i=tail; i<n; i++) {
            line.push_back(i+1);
            backtrack(n, k, start+1, ret, line);
            line.pop_back();
        }
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> v (2, vector<int>(3, 1));
    v[0][1] = 0;
    sln.combine(4,2);
    system("pause");
    return 0;
}
