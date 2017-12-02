/*
5. Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:

Input: "babad"

Output: "bab"

Note: "aba" is also a valid answer.
Example:

Input: "cbbd"

Output: "bb"

*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_set>
using namespace std;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int max_len = 1;
        int index = 0;
        int n = s.length();
        if (n <= 1) {
            return s;
        }
        vector<vector<int>> dp(n+1, vector<int>(n, 0));
        for(int j=0; j<n; j++) {
            dp[0][j] = 0;
        }
        for(int j=0; j<n; j++) {
            dp[1][j] = 1;
        }
        for(int i=2; i<=n; i++) {
            for(int j=0; j<n; j++) {
                int e = j+i -1;
                if (e>=n) {
                    break;
                }
                if(s[j] == s[e] && (i==2 || dp[i-2][j+1])) {
                    dp[i][j] = dp[i-2][j+1] + 2;
                    if(dp[i][j] > max_len) {
                        max_len = dp[i][j];
                        index = j;
                    }
                }
            }
        }
        return s.substr(index, max_len);
    }
};

int main()
{
    Solution sln;
    //cout << sln.longestPalindrome("babad") << endl;
    //cout << sln.longestPalindrome("b") << endl;
    // cout << sln.longestPalindrome("banana") << endl;
    //cout << sln.longestPalindrome("bbbb") << endl;
    //cout << sln.longestPalindrome("abcda") << endl;
    system("pause");
    return 0;
}
