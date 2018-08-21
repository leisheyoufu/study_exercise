/*
290. Word Pattern

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true
Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.
*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool wordPattern(string pattern, string str)
    {
        unordered_map<char, string> m;
        unordered_set<string> vis;
        int i=0, j = 0;
        for(i=0; i<pattern.size(); i++) {
            char ch = pattern[i];
            string s = "";
            while(j < str.length() && str[j] != ' ') {
                s += str[j];
                j++;
            }
            j++;
            if(m.find(ch) != m.end()) {
                if(s != m[ch]) {
                    return false;
                }
            } else {
                if(vis.find(s) != vis.end()) {
                    return false;
                }
                vis.insert(s);
                m[ch] = s;
            }
        }
        if(j-1 != str.length()) {
            return false;
        }
        return true;
    }
};
int main()
{
    Solution sln;
    cout << sln.wordPattern("abba", "dog cat cat dog") << endl;
    cout << sln.wordPattern("abba", "dog cat cat fish") << endl;
    cout << sln.wordPattern("abba", "dog dog dog dog") << endl;
    system("pause");
    return 0;
}
