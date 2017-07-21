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
        backtrack(ret, nums, s, 0, s.length()-1, -1);
        return ret;;
    }
    void backtrack(vector<string> &ret, vector<int> nums, string s, int start, int end, int temp)
    {
        if(start > end) {
            if (nums.size() == 4) {
                stringstream stream;
                stream << nums[0];
                for(int i=1; i<nums.size(); i++) {
                    stream << "." << nums[i];
                }
                string str;
                stream >> str;
                ret.push_back(str);
            }
            return;
        }
        if(nums.size() == 4) {
            return;
        }
        if (temp == 0) {
            return;
        }
        if(temp != -1) {
            int newtemp = temp*10 + (s[start] - '0');
            if (newtemp <= 255) {
                nums.push_back(newtemp);
                backtrack(ret, nums, s, start+1, end, -1);
                nums.pop_back();
            }
            if(newtemp < 255) {
                backtrack(ret, nums, s, start+1, end, newtemp);
            }
        } else {
            temp = s[start] - '0';
            nums.push_back(temp);
            backtrack(ret, nums, s, start+1, end, -1);
            nums.pop_back();
            backtrack(ret, nums, s, start+1, end, temp);
        }
    }
};

int main()
{
    Solution sln;
    sln.restoreIpAddresses("25525511135");
    system("pause");
    return 0;
}
