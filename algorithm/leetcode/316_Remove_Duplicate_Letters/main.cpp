/*
316. Remove Duplicate Letters

Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    string removeDuplicateLetters(string s)
    {
        unordered_map<char, int> counter;
        unordered_map<char, bool> vis;
        string ret = "";
        for(auto c : s) {
            counter[c]++;
        }
        for(auto c : s) {
            counter[c]--;
            if(vis[c]) {
                continue;
            }
            while(!ret.empty() && c < ret.back() && counter[ret.back()] > 0) {
                vis[ret.back()] = false;
                ret.pop_back();
            }
            ret += c;
            vis[c] = true;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    //cout << sln.removeDuplicateLetters("bcabc") << endl;  // abc
    cout << sln.removeDuplicateLetters("cbacdcbc") << endl;  // acdb
    system("pause");
    return 0;
}
