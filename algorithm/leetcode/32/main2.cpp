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
        int cnt = 0;
        vector<int> dp(n, 0);
        for(int i=n-2; i>=0; i--) {
            if(s[i] == '(') {
                int end = i + dp[i+1] + 1;
                if(end < n && s[end] == ')') {
                    dp[i] = 2 + dp[i+1];
                    if(end + 1 < n) {
                        dp[i] += dp[end + 1];
                    }
                }
            }
            if(dp[i] > cnt) {
                cnt = dp[i];
            }
        }
        return cnt;
    }
};

int main()
{
    Solution sln;
    cout << sln.longestValidParentheses(")(())"); // 4
    cout << sln.longestValidParentheses("(((()(()"); // 2
    system("pause");
    return 0;
}
