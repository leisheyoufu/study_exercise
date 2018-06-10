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
        string ret = "";
        if (strs.empty()) {
            return ret;
        }
        if (strs.size() == 1) {
            return strs[0];
        }
        for(int j=0; j<strs[0].length(); j++) {
            for(int i=1; i<strs.size(); i++) {
                if(strs[i].length() == j) {
                    return ret;
                }
                if(strs[i][j] != strs[0][j]) {
                    return ret;
                }
            }
            ret = strs[0].substr(0,j+1);
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
