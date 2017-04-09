/*
58. Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    bool isNumber(string s)
    {
        int i=0;
        int n = s.length();
        for(; s[i] == ' ' && i!=n ; i++) {
        }
        if(i==n) {
            return false;
        }
        if( s[i] == '+' || s[i] == '-') {
            i++;
        }
        int dot_count=0;
        int digit_count = 0;
        for(; ((s[i] >='0' && s[i] <='9') || s[i]=='.') && i !=n; i++) {
            if (s[i] == '.') {
                dot_count++;
            } else {
                digit_count ++;
            }
        }
        if(dot_count >1 || digit_count == 0) {
            return false;
        }
        if (i == n) {
            return true;
        }
        if(s[i] == 'e' && digit_count >0) {
            i++;
            if(s[i] == '+' ||s[i] == '-') {
                i++;
            }
            digit_count = 0;

            for(; s[i]>='0' && s[i] <='9' && i !=n; i++) {
                digit_count++;
            }
            if (digit_count == 0) {
                return false;
            }
        }
        for(; s[i] == ' ' && i!=n; i++) {
        }
        return i == n;
    }
};
int main()
{
    Solution sln;
    cout << sln.isNumber(" ") << endl;
    system("pause");
    return 0;
}
