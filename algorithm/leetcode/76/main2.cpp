/*
Minimum Window Substring
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        int n = s.length();
        int m = t.length();
        if(m == 0 || n == 0) {
            return "";
        }
        int t_hash[256] = {0};
        int s_hash[256] = {0};
        int characters = 0;
        for(int i=0; i<m; i++) {
            if (t_hash[t[i]] == 0) {
                characters++;
            }
            t_hash[t[i]]++;
        }
        int count = 0, left = 0, min_left = -1, min_right = -1;
        for(int i=0; i<n; i++) {
            int w = s[i];
            if (t_hash[w] > 0) {
                s_hash[w]++;
                if (s_hash[w] == t_hash[w]) {
                    count ++;
                }
            }
            while(count == characters) {
                if(min_left == -1) {
                    min_left = left;
                    min_right = i;
                } else if(i-left < min_right - min_left) {
                    min_left = left;
                    min_right = i;
                }
                w = s[left];
                if(t_hash[w]) {
                    s_hash[w]--;
                    if(s_hash[w] < t_hash[w]) {
                        count --;
                    }
                }
                left++;
            }
        }
        if (min_left == -1) {
            return "";
        }
        return s.substr(min_left, min_right-min_left+1);
    }
};
int main()
{
    Solution sln;
    //cout << sln.minWindow("ADOBECODEBANC", "ABC") << endl; // BANC
    //cout << sln.minWindow("abc", "b") << endl;
    // cout << sln.minWindow("cabwefgewcwaefgcf","cae") << endl; // cwae
    // cout << sln.minWindow("a","aa") << endl; // ""
    cout << sln.minWindow("aa","aa") << endl;
    return 0;
}
