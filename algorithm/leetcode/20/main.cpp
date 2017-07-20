/*
20. Valid Parentheses

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:

    bool isValid(string s)
    {
        unordered_map<char, pair<int,int>> char_map;
        char_map['{'] = pair<int,int>(0,1);
        char_map['}'] = pair<int,int>(0,-1);
        char_map['['] = pair<int,int>(1,1);
        char_map[']'] = pair<int,int>(1,-1);
        char_map['('] = pair<int,int>(2,1);
        char_map[')'] = pair<int,int>(2,-1);
        stack<char> stk;

        for(int i=0; i<s.length(); i++) {
            int index = char_map[s[i]].first;
            int change = char_map[s[i]].second;
            if(change >0) {
                stk.push(index);
            } else {
                if(stk.empty()) {
                    return false;
                }
                if(stk.top() != index) {
                    return false;
                }
                stk.pop();
            }
        }
        if(!stk.empty()) {
            return false;
        }
        return true;
    }
};
int main()
{
    Solution sln;
    cout << sln.isValid("(){[[]]]}");
    system("pause");
    return 0;
}
