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
    void dfs(vector<string> &ret, string s, int start, int end, int count)
    {
        if(start == end) {
            ret.push_back(s);
            return;
        }
        if(count*2 <= start) {
            dfs(ret, s+"(", start+1, end, count +1);
            return;
        }
        if(count*2 == end) {
            dfs(ret, s+")", start+1, end, count);
            return;
        }
        dfs(ret, s+"(", start+1, end, count+1);
        dfs(ret, s+")", start+1, end, count);
    }
    vector<string> generateParenthesis(int n)
    {
        vector<string> ret;
        dfs(ret, "", 0, n*2, 0);
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<string> ret = sln.generateParenthesis(3);
    for(auto s : ret) {
        cout << s << endl;
    }
    system("pause");
    return 0;
}
