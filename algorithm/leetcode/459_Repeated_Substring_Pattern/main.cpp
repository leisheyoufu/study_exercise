/*
459. Repeated Substring Pattern

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.



Example 1:

Input: "abab"
Output: True
Explanation: It's the substring "ab" twice.
Example 2:

Input: "aba"
Output: False
Example 3:

Input: "abcabcabcabc"
Output: True
Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    bool repeatedSubstringPattern(string s)
    {
        // 我们对给定的字符串进行重叠，然后再找这个字符串（第二次出现的位置），如果小于它的长度，则说明这个字符串是由一个字符重复构成的。详细过程见代码
        return (s+s).find(s, 1) != s.size();
    }
};
int main()
{
    Solution sln;
    cout << sln.repeatedSubstringPattern("abcabc") << endl; // true
    cout << sln.repeatedSubstringPattern("aba") << endl; // false
    system("pause");
    return 0;
}
