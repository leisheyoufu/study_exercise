/*
224. Basic Calculator

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

Example 1:

Input: "1 + 1"
Output: 2
Example 2:

Input: " 2-1 + 2 "
Output: 3
Example 3:

Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23
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
    /*
    bool hasNextNum(string s, int i)
    {
        if (i +1 == s.length()) {
            return false;
        }
        if(s[i+1] >= '0' && s[i+1] <= '9') {
            return true;
        }
        return false;
    }
    void cal(stack<int> &nums, stack<char> &flags)
    {
        if(flags.empty()) {
            return;
        }
        char flag = flags.top();
        if(flag == ')') {
            flags.pop();
            if (flags.empty()) {
                return;
            }
            char nextFlag = flags.top();
            while(nextFlag != '(') {
                int a = nums.top();
                nums.pop();
                int b = nums.top();
                nums.pop();
                if(nextFlag == '+') {
                    nums.push(a+b);
                } else if(nextFlag == '-') {
                    nums.push(b-a);
                }
    			flags.pop();
                nextFlag = flags.top();
            }
            flags.pop();
    		while (!flags.empty()) {
    			flag = flags.top();
    			if (flag == '(') {
    				break;
    			}
    			flags.pop();
    			int a = nums.top();
    			nums.pop();
    			int b = nums.top();
    			nums.pop();
    			if (flag == '+') {
    				nums.push(a + b);
    			}
    			else if (flag == '-') {
    				nums.push(b - a);
    			}
    		}
        } else if(flag == '(') {
            return;
        } else if(flag == '+' || flag == '-') {
            flags.pop();
            int a = nums.top();
            nums.pop();
            int b = nums.top();
            nums.pop();
            if(flag == '+') {
                nums.push(a+b);
            } else if(flag == '-') {
                nums.push(b-a);
            }
        }
    }

    int calculate(string s)
    {
        stack<int> nums;
        stack<char> flags;
        int curr = 0, n = s.length();
        for(int i=0; i<n; i++) {
            if(s[i] >= '0' && s[i+1] <= '9') {
                curr = curr * 10 + s[i] - '0';
                if(!hasNextNum(s, i)) {
                    nums.push(curr);
                    curr = 0;
                    cal(nums, flags);
                }
            } else if(s[i] == ' ') {
                continue;
            } else if(s[i] == '+' || s[i] == '-' || s[i] == '(') {
                flags.push(s[i]);
            } else if(s[i] == ')') {
                flags.push(')');
                cal(nums, flags);
            }
        }
        while(!flags.empty()) {
            cal(nums, flags);
        }
        return nums.top();
    }
    */
    int calculate(string s)
    {
        if (s.length() == 0) {
            return 0;
        }
        stack<int> st;
        int num = 0, curr = 0, sign = 1;
        for (auto ch : s) {
            if (ch >= '0' && ch <= '9') {
                num = num * 10 + ch - '0';
            } else {
                curr += sign * num;
                num = 0;
                if (ch == '+') {
                    sign = 1;
                } else if (ch == '-') {
                    sign = -1;
                } else if (ch == '(') {
                    st.push(curr);
                    st.push(sign);
                    sign = 1;
                    curr = 0;
                } else if (ch == ')') {
                    sign = st.top();
                    st.pop();
                    curr = st.top() + sign * curr;
                    st.pop();
                }
            }
        }
        return curr + sign * num;
    }
};
int main()
{
    Solution sln;
    cout << sln.calculate("(1+(4+5+2)-3)+(6+8)") << endl;  // 23
    cout << sln.calculate("1 + 12 - (9 - 8 + (12 - 7)) + (0 + 8 - (2 + 1)) + 8") << endl;  // 20
    system("pause");
    return 0;
}
