/*
17. Letter Combinations of a Phone Number

Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.



Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    void dfs(vector<string> &res, unordered_map<int, string> &map, string digits, string val, int index)
    {
        int n = digits.size();
        if(index == n) {
            if (!val.empty()) {
                res.push_back(val);
            }
            return;
        }
        string temp = map[digits[index] - '0'];
        for(int i=0; i<temp.size(); i++) {
            dfs(res,map,digits,val+temp[i], index+1);
        }
    }
    vector<string> letterCombinations(string digits)
    {
        unordered_map<int,string> map;
        map[0] = "";
        map[1] = "";
        map[2] = "abc";
        map[3] = "def";
        map[4] = "ghi";
        map[5] = "jkl";
        map[6] = "mno";
        map[7] = "pqrs";
        map[8] = "tuv";
        map[9] = "wxyz";
        vector<string> res;
        dfs(res,map,digits,"",0);
        return res;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
