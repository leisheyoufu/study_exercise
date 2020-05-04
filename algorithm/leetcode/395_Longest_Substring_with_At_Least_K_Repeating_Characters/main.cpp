/*
395. Longest Substring with At Least K Repeating Characters

Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    int loggestSub(string &s, int k, int start, int end)
    {
        if (s.empty() || s.size() < k )
            return 0;
        unordered_map<char, int> m;
        for(int i=start; i<=end; i++) {
            m[s[i]]++;
        }
        int i = start;
        while(i<=end && m[s[i]] >= k) {
            i++;
        }
        if(i == end + 1) {
            return end-start +1;
        }
        int left = loggestSub(s, k, start, i-1);
        i++;
        while(i<=end && m[s[i]] < k) {
            i++;
        }
        int right = loggestSub(s, k, i, end);
        return max(left, right);
    }
    int longestSubstring(string s, int k)
    {
        if (s.empty() || s.size() < k )
            return 0;
        if (k <=1)
            return s.size();
        return loggestSub(s, k, 0, s.size()-1);
    }
};

int main()
{
    Solution sln;
    cout << sln.longestSubstring("ababbc", 2) << endl; // 5
    cout << sln.longestSubstring("aaabb", 3) << endl; // 3
    cout << sln.longestSubstring("aaabbb", 3) << endl; // 6
    system("pause");
    return 0;
}
