/*
93. Restore IP Addresses

Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",

return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
#include<sstream>
using namespace std;

class Solution
{
public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> ret;
        vector<int> nums;
        dfs(ret, s, nums, 0);
        return ret;
    }
    void dfs(vector<string> &ret, string s, vector<int> nums, int pos)
    {
        if(nums.size() == 4) {
            if (pos != s.length()) {
                return;
            }
            stringstream stream;
            stream << nums[0];
            for(int i=1; i<nums.size(); i++) {
                stream << "." << nums[i];
            }
            string str;
            stream >> str;
            ret.push_back(str);
            return;
        }
        int temp = 0;
        int p = pos;
        while(p < s.length()) {
            if (p == pos) {
                temp = s[p] - '0';
            } else if(temp == 0) {
                break;
            } else {
                temp = temp * 10 + s[p] - '0';
            }
            if(temp > 255) {
                break;
            }
            nums.push_back(temp);
            dfs(ret, s, nums, p+1);
            nums.pop_back();
            p++;
        }
    }
};

int main()
{
    Solution sln;
    // sln.restoreIpAddresses("25525511135");
    sln.restoreIpAddresses("010010"); // ["0.10.0.10","0.100.1.0"]
    system("pause");
    return 0;
}
