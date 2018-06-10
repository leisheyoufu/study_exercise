/*
131. Palindrome Partitioning
Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return

[
  ["aa","b"],
  ["a","a","b"]
]
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
    bool is_palindrome(string s, int start, int end)
    {
        while(start < end) {
            if(s[start] != s[end]) {
                return false;
            }
            start++;
            end --;
        }
        return true;
    }
    void dfs(vector<vector<string> > &ret, vector<string> line, string s, int start)
    {
        int n = s.length();
        if(start == n) {
            ret.push_back(line);
            return;
        }
        string path;
        for(int i=start; i<n; i++) {
            if (is_palindrome(s, start, i)) {
                path = s.substr(start, i-start +1);
                line.push_back(path);
                dfs(ret, line, s, i+1);
                line.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s)
    {
        vector<vector<string> > ret;
        vector<string> line;
        dfs(ret, line, s, 0);
        return ret;
    }
};

int main()
{
    Solution sln;
    string s="aab";
    sln.partition(s);
    system("pause");
    return 0;
}
