/*
Distinct Subsequences

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
#include<conio.h>
#include<cstdlib>
using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int numDistinct(string s, string t)
    {

        int n1 = s.length();
        int n2 = t.length();
        if(n1<n2) {
            return 0;
        }
        int **dp = new int*[n1+1];
        for(int i=0; i<=n1; i++) {
            dp[i] = new int[n2+1];
        }
        dp[0][0] = 1;
        for(int i=1; i<=n1; i++) {
            dp[i][0] = 1;
        }
        for(int j=1; j<=n2; j++) {
            dp[0][j] = 0;
        }

        for(int i=1; i<=n1; i++) {
            for(int j=1; j<=n2; j++) {
                if(s[i-1] == t[j-1]) {
                    dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[n1][n2];
    }
};
int main()
{
    Solution sln;
    string s1 = "rabbbit";
    string s2 = "rabbit";

    printf("%d\n",sln.numDistinct(s1,s2));
    getch();
    return 0;
}
