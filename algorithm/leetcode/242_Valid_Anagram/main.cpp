/*
242. Valid Anagram
Given two strings s and t , write a function to determine if t is an anagram of s.

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
Note:
You may assume the string contains only lowercase alphabets.

Follow up:
What if the inputs contain unicode characters? How would you adapt your solution to such case?
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        int n1 = s.size();
        int n2 = t.size();
        if(n1 != n2) {
            return false;
        }
        vector<int> count(26, 0);
        for(auto ch : s) {
            count[ch-'a']++;
        }
        for(auto ch : t) {
            count[ch-'a']--;
        }
        for(int i=0; i<26; i++) {
            if(count[i] != 0) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
