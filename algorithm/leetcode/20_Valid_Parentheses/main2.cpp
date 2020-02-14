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
        if(s.empty()) {
            return true;
        }
        unordered_map<char, char> m;
        m['('] = ')';
        m['['] = ']';
        m['{'] = '}';
        m[')'] = 'x';
        m[']'] = 'x';
        m['}'] = 'x';
        stack<char> stk;
        for(char ch:s) {
            if(!stk.empty() && m[stk.top()] == ch) {
                stk.pop();
            } else if(m[ch] == 'x') {
                return false;
            } else {
                stk.push(ch);
            }
        }
        if(stk.empty()) {
            return true;
        }
        return false;
    }
};
int main()
{
    Solution sln;
    // cout << sln.isValid("(){[[]]]}") << endl;//false
    // cout << sln.isValid("]") << endl; // false
    cout << sln.isValid("()[]{}") << endl; // true

    system("pause");
    return 0;
}
