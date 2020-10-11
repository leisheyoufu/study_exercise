/*
394. Decode String

Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].



Example 1:

Input: s = "3[a]2[bc]"
Output: "aaabcbc"
Example 2:

Input: s = "3[a2[c]]"
Output: "accaccacc"
Example 3:

Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"
Example 4:

Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    bool is_digit(char ch)
    {
        if(ch >= '0' && ch <= '9') {
            return true;
        }
        return false;
    }
    string repeat_pattern(string pattern, int count)
    {
        string ret = "";
        for(int i=0; i<count; i++) {
            ret += pattern;
        }
        return ret;
    }
    string write_pattern(string &s, int &i)
    {
        int n = s.length();
        string ret = "";
        string pattern;
        int state = 0, count = 0;
        while(i<n) {
            char ch = s[i];
            if(state == 0) {
                if (is_digit(ch)) {
                    state = 1;
                    count = ch - '0';
                } else if( ch == ']') {
                    i++;
                    return ret;
                } else {
                    ret += ch;
                }
                i++;
            } else if (state == 1) {
                if(is_digit(ch)) {
                    count = count * 10 + ch - '0';
                    i++;
                } else if(ch == '[') {
                    i++;
                    ret = ret + repeat_pattern(write_pattern(s, i), count);
                    count = 0;
                    state = 0;
                } else {
                    state = 0;
                }
            }
        }
        return ret;
    }
    string decodeString(string s)
    {
        int i = 0;
        return write_pattern(s, i);
    }
};

int main()
{
    Solution sln;
    cout << sln.decodeString("abc3[cd]xyz") << endl; // "abccdcdcdxyz"
    cout << sln.decodeString("3[a2[c]]") << endl; // accaccacc
    system("pause");
    return 0;
}
