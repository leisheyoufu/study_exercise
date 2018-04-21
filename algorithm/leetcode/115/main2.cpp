/*
115. Distinct Subsequences

Given a string S and a string T, count the number of distinct subsequences of T in S.

A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).

Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int numDistinct(string s, string t)
    {
        int n = s.length();
        int m = t.length();
        if(m > n) {
            return 0;
        }
        vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
        for(int i=0; i<=n; i++) {
            dp[i][0] = 1;
        }
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=m; j++) {
                if(s[i-1] == t[j-1]) {
                    // dp[i-1][j]  delete current, dp[i-1][j-1] keep current
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n][m];
    }
};
int main()
{
    Solution sln;
    string s1 = "rabbbit";
    string s2 = "rabbit";
    cout << sln.numDistinct(s1, s2) << endl;
    system("pause");
    return 0;
}
