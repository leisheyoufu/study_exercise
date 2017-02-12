/*

Word Break II

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

    void dfs(string s, vector<vector<int>> &bitmap, vector<string> &ret, int cur, vector<string> &temp)
    {
        if(cur == 0) {
            string t;
            for(int k=temp.size()-1; k>0; k--) {
                t+=temp[k] + " ";
            }
            t +=temp[0];
            ret.push_back(t);
        }
        for(int i=0; i<bitmap[cur].size(); i++) {
            int d = bitmap[cur][i];
            temp.push_back(s.substr(d, cur-d));
            dfs(s,bitmap,ret,d, temp);
            temp.pop_back();
        }
    }

    vector<string> wordBreak(string s, vector<string>& wordDict)
    {
        int n = s.length();
        vector<bool> fit (n+1, false);
        vector<vector<int>> bitmap;
        vector<string> ret;
        bitmap.resize(n+1);
        fit[0] = true;
        for(int i=1; i<=n; i++) {
            for(int j=i-1; j>=0; j--) {
                if(fit[j] && canfind(s.substr(j, i-j), wordDict)) {
                    fit[i]= true;
                    bitmap[i].push_back(j);
                }
            }
        }
        if(!fit[n]) {
            return ret;
        }
        vector<string> temp;
        dfs(s, bitmap, ret, n, temp);
        return ret;
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
