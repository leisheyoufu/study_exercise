/*
10. Regular Expression Matching
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
// CL: The last one is better
class Solution
{
public:
    bool dfs(string &s, int i, string &p, int j)
    {
        if(i > s.length()) {
            return false;
        }
        while(i < s.length() && j< p.length() && (s[i] == p[j] || p[j] == '.')) {
            i++;
            j++;
        }
        if(i == s.length() && j == p.length()) {
            return true;
        }
        if(j < p.length() && p[j] == '*') {  // s[i] != p[j], but p[j] == '*'
            if (dfs(s, i, p, j+1)) {  // match once
                return true;
            }
            if(j> 0 && i<s.length() && (s[i] == p[j-1] || p[j-1] == '.')) {
                if (dfs(s, i+1, p, j)) { // multiple match
                    return true;
                }
            }
            return dfs(s, i-1, p, j+1);  // next match
        }
        if(j+1 < p.length() && p[j+1] == '*') {
            return dfs(s, i, p, j+2); // do not match
        }
        return false;
    }
    bool isMatch(string s, string p)
    {
        return dfs(s, 0, p, 0);
    }
};
int main()
{
    Solution sln;
    //cout << sln.isMatch("abc", ".bc") << endl; // 1
    //cout << sln.isMatch("abc", "abc") << endl;  // 1
    //cout << sln.isMatch("abcccc", ".bc*") << endl; // 1
    //cout << sln.isMatch("abcxxxbta", "abc**xb.a") << endl;  //1
    //cout << sln.isMatch("aab", "c*a*b") << endl; // 1
    //cout << sln.isMatch("a", "ab*") << endl; // 1
    cout << sln.isMatch("bbbba", ".*a*a") << endl; // 1
    system("pause");
    return 0;
}
