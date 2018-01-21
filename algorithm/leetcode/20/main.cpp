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
        stack<char> stk;
        for(int i=0; i<s.length(); i++) {
            switch(s[i]) {
            case '(':
            case '[':
            case '{':
                stk.push(s[i]);
                break;
            case ')':
                if(!stk.empty() && stk.top() == '(') {
                    stk.pop();
                    break;
                }
                return false;
            case ']':
                if(!stk.empty() && stk.top() == '[') {
                    stk.pop();
                    break;
                }
                return false;
            case '}':
                if(!stk.empty() && stk.top() == '{') {
                    stk.pop();
                    break;
                }
                return false;
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
    cout << sln.isValid("(){[[]]]}") << endl;//false
    cout << sln.isValid("]") << endl; // false
    system("pause");
    return 0;
}
