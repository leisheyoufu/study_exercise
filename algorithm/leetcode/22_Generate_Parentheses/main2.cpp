/*
22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>

using namespace std;

class Solution
{
public:
    void dfs(string s, vector<string> &ret, int cnt, int n)
    {
        int l = s.length();
        if(l == n) {
            ret.push_back(s);
            return;
        }
        if(cnt == 0) {
            dfs(s + '(', ret, 1, n);
            return;
        }
        if(n-l == cnt) {
            dfs(s+')', ret, cnt-1, n);
            return;
        }
        dfs(s+'(', ret, cnt+1, n);
        dfs(s+')', ret, cnt-1, n);
    }
    vector<string> generateParenthesis(int n)
    {
        if(n < 0) {
            return vector<string>();
        }
        vector<string> ret;
        dfs("", ret, 0, 2*n);
        return ret;
    }
};
int main()
{
    Solution sln;
    sln.generateParenthesis(3);
    system("pause");
    return 0;
}
