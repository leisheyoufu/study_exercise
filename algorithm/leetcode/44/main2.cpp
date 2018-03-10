/*
44. Wildcard Matching

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

class Solution
{
public:
    bool isMatch(string s, string p)
    {
        int i=0, j=0;
        int ii = -1, jj = -1;
        while(i<s.length()) {
            if(j < p.length() && (s[i] == p[j] || p[j] == '?')) {
                i++;
                j++;
            } else if (j < p.length() && p[j] == '*') {
                jj = j++;
                ii = i;
            } else if (jj != -1) {
                j = jj;
                i = ++ii;
            } else {
                return false;
            }
        }
        while(j < p.length()) {
            if(p[j] != '*') {
                return false;
            }
            j++;
        }
        return true;
    }
};

int main()
{
    Solution sln;
    cout << sln.isMatch("ab", "?*") << endl;  // 1
    cout << sln.isMatch("abc", "*") << endl; // 1
    cout << sln.isMatch("abc", "a*b*c*") << endl; // 1
    cout << sln.isMatch("a", "aa") << endl; // 0
    cout << sln.isMatch("aaaa", "***a") << endl; // 1
    system("pause");
    return 0;
}
