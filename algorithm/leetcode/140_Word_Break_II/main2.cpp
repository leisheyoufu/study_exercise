/*

140. Word Break II

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.
*/
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>
#include<unordered_set>

using namespace std;

class Solution
{
public:
    string join(vector<string> strs)
    {
        if(strs.empty()) {
            return "";
        }
        string ret;
        for(int i=0; i<strs.size()-1; i++) {
            ret = ret + strs[i] + " ";
        }
        return ret + strs[strs.size()-1];
    }
    void dfs(vector<string> curr, vector<string> &ret, int start, string s, unordered_set<string> &dict, vector<vector<int> > &jump)
    {
        if(start == s.length()) {
            ret.push_back(join(curr));
            return;
        }

        for(int k=0; k < jump[start].size(); k++) {
            string temp = s.substr(start, jump[start][k]);
            if(dict.find(temp) != dict.end()) {
                curr.push_back(temp);
                dfs(curr, ret, start+jump[start][k], s, dict, jump);
                curr.pop_back();
            }
        }
    }
    vector<string> wordBreak(string s, vector<string>& wordDict)
    {
        if(s.empty() || wordDict.empty()) {
            return vector<string>();
        }
        unordered_set<string> dict;
        for(auto word : wordDict) {
            dict.insert(word);
        }
        vector<bool> fit(s.length()+1, false);
        vector<vector<int> >jump(s.length()+1, vector<int>());
        initJump(s, dict, fit, jump);
        if(!fit[s.length()]) {
            return vector<string>();
        }
        vector<string> ret, curr;
        dfs(curr, ret, 0, s, dict, jump);
        return ret;
    }
    void initJump(string s, unordered_set<string> &dict, vector<bool> &fit, vector<vector<int> > &jump)
    {
        int n = s.length();
        for(int i=1; i<=n; i++) {
            if(dict.find(s.substr(0, i)) != dict.end()) {
                fit[i] = true;
                jump[0].push_back(i);
            }
            for(int j=1; j<i; j++) {
                if(fit[j]) {
                    string temp = s.substr(j, i-j);
                    if(dict.find(temp) != dict.end()) {
                        fit[i] = true;
                        jump[j].push_back(i-j);
                    }
                }
            }
        }
    }
};

int main()
{
    Solution sln;
    string s("catsanddog");
    string d[] = {"cat","cats","and","sand","dog"};
    //string s("aaaaaaa");
    //string d[] = {"aaaa","aaa"};
    //string s("aaaaaaa");
    //string d[] = {"aaaa","aa","a"};
    vector<string> dict(d, d+sizeof(d)/sizeof(string));
    vector<string> r = sln.wordBreak(s,dict);
    system("pause");
    return 0;
}
