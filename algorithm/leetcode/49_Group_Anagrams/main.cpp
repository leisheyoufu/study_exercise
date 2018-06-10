/*
49. Group Anagrams

Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"],
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note: All inputs will be in lower-case.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:

    /*
    bool find_word(unordered_map<char, int> &words, string str, string pattern)
    {
    	int n = str.length();
    	int p = pattern.length();
    	if (n != p) {
    		return false;
    	}
    	words.clear();
    	for(int i=0;i<n;i++) {
    		words[str[i]]++;
    	}
    	for(int i=0;i<p;i++) {
    		if( words.find(pattern[i]) == words.end() || words[pattern[i]] == 0) {
    			return false;
    		} else {
    			 words[pattern[i]]--;
    		}
    	}
    	return true;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<char, int> words;
    	int n = strs.size();
    	vector<int> mask(n,0);
    	vector<vector<string>> ret;
    	for(int i=0; i<n;i++) {
    		if(mask[i] != 0) {
    			continue;
    		}
    		mask[i] = 1;
    		vector<string> r;
    		r.push_back(strs[i]);
    		for(int j=i+1;j<n;j++) {
    			if( !mask[j] && find_word(words, strs[i], strs[j])) {
    				mask[j] = 1;
    				r.push_back(strs[j]);
    			}
    		}
    		ret.push_back(r);
    	}
    	return ret;
    }
    */
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> ret;
        unordered_map<string, vector<string>> groups;
        int n = strs.size();
        for(int i=0; i<n; i++) {
            string temp = strs[i];
            sort(strs[i].begin(), strs[i].end());
            groups[strs[i]].push_back(temp);
        }
        for(unordered_map<string, vector<string>>::iterator iter=groups.begin(); iter!=groups.end(); iter++) {
            ret.push_back(iter->second);
        }
        return ret;
    }


};
int main()
{
    Solution sln;

    system("pause");
    return 0;
}
