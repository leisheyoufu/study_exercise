/*

Word Break

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool canfind(string s, vector<string> &dict)
    {
        for(int i=0; i<dict.size(); i++) {
            if(s == dict[i]) {
                return true;
            }
        }
        return false;
    }

    bool wordBreak(string s, vector<string>& wordDict)
    {
        int n = s.length();
        vector<bool> fit (n+1, false);
        fit[0] = true;
        for(int i=1; i<=n; i++) {
            for(int j=i-1; j>=0; j--) {
                if(fit[j] && canfind(s.substr(j, i-j), wordDict)) {
                    fit[i]= true;
                    break;
                }
            }
        }
        return fit[n];
    }

};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
