/*  Longest Valid Parentheses
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

For "(()", the longest valid parentheses substring is "()", which has length = 2.

Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

int longestValidParentheses(char* s)
{
    int len = strlen(s);
    int max_len = 0;
    int *dp = (int *)malloc(sizeof(int)*len);
    memset(dp,0,sizeof(int)*len);
    for(int i=len-2; i>=0; i--) {
        if(s[i] == '(') {
            int end = i+dp[i+1] + 1;
            if(s[end] == ')') {
                dp[i] = dp[i+1] +2;
                if(end + 1 < len) {
                    dp[i] += dp[end + 1];
                }
            }
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
        }
    }
    free(dp);
    return max_len;
}
int main()
{
    char *s ="()(())";
    printf("%d\n", longestValidParentheses(s));
    system("pause");
    return 0;
}
