/*  32. Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.length();
        if (n <= 1) {
            return 0;
        }
        int ret = 0;
        vector<int> dp(n, 0);

        for(int i=1; i<n; i++) {
            if (s[i] == ')') {
                int j = i-dp[i-1] -1; // if s[i-1] == '(', dp[i-1] = 0
                if(j >=0 && s[j] == '(') {
                    dp[i] = 2 + dp[i-1];
                }
                if (i- dp[i] > 0) {
                    dp[i] += dp[i-dp[i]];
                }
            }
            ret = max(ret, dp[i]);
        }
        return ret;
        /*
        for(int i=1; i<n; i++) {
            if (s[i-1] == '('  && s[i] == ')' ){
                dp[i] = 2;
                if (i-2 >= 0) {
                    dp[i] += dp[i-2];
                }
            } else if (s[i-1] == ')' && s[i] == ')') {
                int j = i - dp[i-1] -1;
                if (j>=0 && s[j] == '(') {
                    dp[i] = 2;
                }
                dp[i] += dp[i-1];
                if(i - dp[i] > 0) {
                    dp[i] += dp[i-dp[i]];
                }
            }
            ret = max(ret, dp[i]);
        }
        */
    }
};

int main()
{
    Solution sln;
    cout << sln.longestValidParentheses(")(())") << endl; // 4
    cout << sln.longestValidParentheses("(((()(()") <<endl; // 2
    cout << sln.longestValidParentheses("()()()") <<endl; // 6
    cout << sln.longestValidParentheses("((())") <<endl; // 4
    cout << sln.longestValidParentheses("()(())") <<endl; // 6
    cout << sln.longestValidParentheses("()()(())") <<endl; // 8
    cout << sln.longestValidParentheses("") <<endl; // 0
    cout << sln.longestValidParentheses("(()") <<endl; // 2
    system("pause");
    return 0;
}
