/*
97. Interleaving String

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        int n1 = s1.length();
        int n2 = s2.length();
        int n3 = s3.length();
        if(n1 + n2 != n3) {
            return false;
        }
        if (n3 == 0) {
            return true;
        }
        vector<vector<bool> > dp(n1+1, vector<bool>(n2+1, false));
        if(s1[0] == s3[0]) {
            dp[1][0] = true;
        }
        for(int i=1; i<n1; i++) {
            dp[i+1][0] = dp[i][0] && s1[i] == s3[i];
        }
        if(s2[0] == s3[0]) {
            dp[0][1] = true;
        }
        for(int j=1; j<n2; j++) {
            dp[0][j+1] = dp[0][j] && s2[j] == s3[j];
        }
        for(int i=1; i<=n1; i++) {
            for(int j=1; j<=n2; j++) {
                if(s3[i+j-1] == s1[i-1] && dp[i-1][j]) {
                    dp[i][j] = true;
                }
                if(s3[i+j-1] == s2[j-1] && dp[i][j-1]) {
                    dp[i][j] = true;
                }
            }
        }
        return dp[n1][n2];
    }
};
int main()
{
    Solution sln;
    string s1 = "db";
    string s2 = "b";
    string s3="cbb";
    //cout << sln.isInterleave(s1, s2, s3) << endl; // false
    cout << sln.isInterleave("aa", "ab", "abaa") << endl; // true
    return 0;
}
