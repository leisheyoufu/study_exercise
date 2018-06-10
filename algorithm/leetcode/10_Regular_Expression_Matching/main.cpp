/*
Regular Expression Matching
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

class Solution
{
public:
    /*
    // correct c solution

    bool isMatch(char *s, char *p)
    {
        if (*p == '\0') return *s == '\0';
        // next char is not '*': must match current character
        if (*(p+1) != '*') {
            return ((*p == *s) || (*p == '.' && *s != '\0')) && this->isMatch(s+1, p+1);
        }

        // next char is '*'
        while ((*p == *s) || (*p == '.' && *s != '\0')) {
            if (this->isMatch(s, p+2)) return true;
            s++;
        }
        return this->isMatch(s, p+2);
    }
    */
    bool match(string &s, int i, string &p, int j)
    {
        if (j == p.length()) {
            return i == s.length();
        }
        if (j>p.length()) {
            return false;
        }

        if(j+1 < p.length() && p[j+1] != '*'  || j+ 1 == p.length()) {
            if(s[i] == p[j] || p[j] == '.')
                return match(s, i+1, p, j+1);
            return false;
        }

        while( i< s.length() && (s[i] == p[j] || p[j] == '.')) {
            if(match(s, i, p, j+2)) {
                return true;
            }
            i++;
        }
        return match(s, i, p, j+2);
    }

    bool isMatch(string s, string p)
    {
        if(p.length() > 0 && p[0] == '*') {
            return false;
        }
        return match(s, 0, p, 0);
    }
};
int main()
{
    Solution sln;
    cout << sln.isMatch("abc", ".bc") << endl;
    cout << sln.isMatch("abc", "abc") << endl;
    cout << sln.isMatch("abcccc", ".bc*") << endl;
    cout << sln.isMatch("abcxxxbta", "abc**xb.a") << endl;
    cout << sln.isMatch("aab", "c*a*b") << endl;
    system("pause");
    return 0;
}
