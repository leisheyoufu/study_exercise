/*
Longest Common Prefix
Write a function to find the longest common prefix string amongst an array of strings.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    string longestCommonPrefix(vector<string>& strs)
    {
        int size = strs.size();
        string ret;
        if(size == 0) {
            return "";
        }
        for(int pos=0; pos<strs[0].size(); pos++) {
            for(int i=0; i<size; i++) {
                if(strs[i].size() < pos || strs[0][pos] != strs[i][pos]) {
                    return ret;
                }
            }
            ret.push_back(strs[0][pos]);
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    string strs[] = {"aaaab", "aaac", "aabc", "cacc"};
    vector<string> v(strs, strs+ sizeof(strs)/sizeof(string));
    cout << sln.longestCommonPrefix(v) << endl;
    system("pause");
    return 0;
}
