/*
Palindrome Partitioning
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
    void dfs(string s, vector<string> &path,vector<vector<string>>& res)
    {
        if(s.size()<1) {
            res.push_back(path);
            return;
        }
        int size = s.size();
        for(int i=0; i<size; i++) {
            int begin = 0;
            int end = i;
            while(begin <end) {
                if(s[begin] == s[end]) {
                    begin++;
                    end--;
                } else {
                    break;
                }
            }
            if(begin >= end) {
                path.push_back(s.substr(0, i+1));
                dfs(s.substr(i+1), path, res);
                path.pop_back();
            }
        }
    }


    vector<vector<string>> partition(string s)
    {
        vector<vector<string>> res;
        vector<string> path;
        dfs(s, path,res);
        return res;
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
