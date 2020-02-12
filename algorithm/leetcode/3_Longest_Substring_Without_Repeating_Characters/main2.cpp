/*

3. Longest Substring Without Repeating Characters

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<unordered_map>


using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int ret = 1, n = s.size();
        if(n == 0 || n == 1) {
            return n;
        }
        unordered_map<char, int> m;
        m[s[0]] = 0;
        int curr = 0;
        for(int i=1; i<n; i++) {
            if(m.find(s[i]) != m.end() && m[s[i]] >= curr) {
                ret = max(ret, i-curr);
                curr = m[s[i]] + 1;
            }
            m[s[i]] = i;
        }
        ret = max(ret, n-curr);
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.lengthOfLongestSubstring("abba") << endl; // 2
    cout << sln.lengthOfLongestSubstring("abcabcbb") << endl; // 3
    cout << sln.lengthOfLongestSubstring("bbbbb") << endl; // 1
    cout << sln.lengthOfLongestSubstring("pwwkew") << endl; // 3
    cout << sln.lengthOfLongestSubstring("a") << endl; // 1
    cout << sln.lengthOfLongestSubstring("") << endl; // 0
    cout << sln.lengthOfLongestSubstring("au") << endl; // 2
    cout << sln.lengthOfLongestSubstring("dvdf") << endl; // 3
    system("pause");
    return 0;
}
