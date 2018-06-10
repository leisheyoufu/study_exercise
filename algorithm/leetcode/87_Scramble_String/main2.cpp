/*
87. Scramble String
Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.

Below is one possible representation of s1 = "great":

    great
   /    \
  gr    eat
 / \    /  \
g   r  e   at
           / \
          a   t
To scramble the string, we may choose any non-leaf node and swap its two children.

For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".

    rgeat
   /    \
  rg    eat
 / \    /  \
r   g  e   at
           / \
          a   t
We say that "rgeat" is a scrambled string of "great".

Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".

    rgtae
   /    \
  rg    tae
 / \    /  \
r   g  ta  e
       / \
      t   a
We say that "rgtae" is a scrambled string of "great".

Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.

*/
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool isScramble(string s1, string s2)
    {
        int l1 = s1.length();
        int l2 = s2.length();
        if(l1 != l2) {
            return false;
        }
        if(s1 == s2) {
            return true;
        }
        vector<vector<vector<bool> > > dp(l1, vector<vector<bool> > (l1, vector<bool> (l1+1, false)));
        for(int i=0; i<l1; i++) {
            for(int j=0; j<l1; j++) {
                if(s1[i] == s2[j]) {
                    dp[i][j][1] = true;
                }
            }
        }
        for (int len =2; len <=l1; len++) {
            for(int i=0; i<l1-len+1; i++) {
                for(int j=0; j<l2-len+1; j++) {
                    for(int k=1; k<len; k++) {
                        dp[i][j][len] = dp[i][j][len] || dp[i][j][k] && dp[i+k][j+k][len-k] || dp[i+k][j][len-k] && dp[i][j+len-k][k];
                    }
                }
            }
        }
        return dp[0][0][l1];
    }
};
int main()
{
    Solution sln;
    cout << sln.isScramble("great","rgtae") << endl;
    system("pause");
    return 0;
}