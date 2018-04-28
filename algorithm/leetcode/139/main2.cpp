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
#include<unordered_set>

using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string>& wordDict)
    {
        unordered_set<string> dict;
        for(auto word : wordDict) {
            dict.insert(word);
        }
        int n = s.length();
        if (n == 0) {
            return false;
        }
        vector<bool> fit(n, false);
        for(int i=0; i<n; i++) {
            string temp = s.substr(0, i+1);
            if(dict.find(temp) != dict.end()) {
                fit[i] = true;
            } else {
                for(int j=i; j>0; j--) {
                    if(fit[j-1]) {
                        temp = s.substr(j, i-j+1);
                        if(dict.find(temp) != dict.end()) {
                            fit[i] = true;
                        }
                    }
                }
            }
        }
        return fit[n-1];
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
