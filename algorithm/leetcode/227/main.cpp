/*
227. Basic Calculator II

Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
Example 1:
Input: "3+2*2"
Output: 7
Example 2:
Input: " 3/2 "
Output: 1
Example 3:
Input: " 3+5 / 2 "
Output: 5
Note:
You may assume that the given expression is always valid.
Do not use the eval built-in library function.
*/

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

class Solution
{
public:
    void cal(stack<int> &nums, char flag)
    {
        if (flag == ' ') {
            return;
        }
        int a = nums.top();
        nums.pop();
        int b = nums.top();
        nums.pop();
        if (flag == '*') {
            nums.push(a * b);
        } else if (flag == '/') {
            nums.push(b / a);
        }
    }
    int calculate(string s)
    {
        if (s.empty()) {
            return 0;
        }
        int num = 0, sign = 1, curr = 0;
        char flag = ' ';
        stack<int> nums;
        for (auto ch : s) {
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + ch - '0';
            } else {
                if (ch == ' ') {
                    continue;
                }
                nums.push(sign * num);
                num = 0;
                sign = 1;
                cal(nums, flag);
                flag = ' ';
                if (ch == '+') {
                    sign = 1;
                } else if (ch == '-') {
                    sign = -1;
                } else if (ch == '*' || ch == '/') {
                    flag = ch;
                }
            }
        }
        nums.push(sign * num);
        cal(nums, flag);
        int ret = 0;
        while (!nums.empty()) {
            ret += nums.top();
            nums.pop();
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.calculate("3+5 / 2") << endl;  // 5
    cout << sln.calculate("3+2*2") << endl;  // 7
    cout << sln.calculate("3/2-9*8-7*5") << endl; // -106
    system("pause");
    return 0;
}
