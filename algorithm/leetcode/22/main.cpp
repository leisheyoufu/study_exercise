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
    void generate(int left, int right, string str, vector<string> &res)
    {
        if(left>right) {
            return;
        }
        if(left ==0 && right ==0) {
            res.push_back(str);
            return;
        }
        if (left > 0) {
            generate(left-1, right, str+'(', res);
        }
        if (right > 0) {
            generate(left, right-1, str+')', res);
        }
    }


    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        generate(n,n,"",res);
        return res;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
