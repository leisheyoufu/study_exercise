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

    vector<vector<string> > groupAnagrams(vector<string>& strs)
    {
        vector<vector<string> > ret;
        unordered_map<string, vector<string> > m;
        for(string str: strs) {
            string temp = str;
            sort(temp.begin(), temp.end());
            m[temp].push_back(str);
        }
        for(unordered_map<string, vector<string> >::iterator iter=m.begin(); iter!=m.end(); iter++) {
            ret.push_back(iter->second);
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    string strs[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> v(strs, strs+sizeof(strs)/sizeof(string));
    sln.groupAnagrams(v);
    system("pause");
    return 0;
}
