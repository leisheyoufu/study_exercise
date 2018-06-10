/*
150. Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, /. Each operand may be an integer or another expression.

Some examples:
  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<stack>
using namespace std;

class Solution
{
public:
    int evalRPN(vector<string>& tokens)
    {
        if(tokens.empty()) {
            return 0;
        }
        stack<int> s;
        for(int i=0; i<tokens.size(); i++) {
            int a, b;
            if(tokens[i] == "+") {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b+a);
            } else if( tokens[i] == "-") {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b-a);
            }  else if( tokens[i] == "*") {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(a*b);
            } else if( tokens[i] == "/") {
                a = s.top();
                s.pop();
                b = s.top();
                s.pop();
                s.push(b/a);
            } else {
                s.push(atoi(tokens[i].c_str()));
            }
        }
        return s.top();
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
