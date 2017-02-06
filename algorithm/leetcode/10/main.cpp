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
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

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
};
int main()
{
    Solution sln;
    printf("%d\n",sln.isMatch("abc", ".bc"));
    getch();
    return 0;
}
