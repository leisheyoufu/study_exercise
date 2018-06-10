/* String to Integer (atoi)
Implement atoi to convert a string to an integer.

Hint: Carefully consider all possible input cases. If you want a challenge, please do not see below and ask yourself what are the possible input cases.

Notes: It is intended for this problem to be specified vaguely (ie, no given input specs). You are responsible to gather all the input requirements up front.

Update (2015-02-10):
The signature of the C++ function had been updated. If you still see your function signature accepts a const char * argument, please click the reload button  to reset your code definition.
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution
{
public:
    string& trim(std::string &s)
    {
        if (s.empty()) {
            return s;
        }

        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
        return s;
    }

    int myAtoi(string str)
    {
        long long ret = 0;
        int sign = 1;
        str = trim(str);
        if(str.length() == 0) {
            return 0;
        }
        if(str.length() == 1 && (str[0] < '0' || str[0] > '9')) {
            return 0;
        }
        if(str[0] == '-') {
            sign= -1;
        } else if(str[0] == '+') {
            sign = 1;
        } else if (str[0] < '0' || str[0] > '9') {
            return 0;
        } else {
            ret = str[0] - '0';
        }
        for(int i=1; i<str.size(); i++) {
            if(str[i] <'0' || str[i] > '9') {
                break;
            }
            ret *= 10;
            ret += str[i] - '0';
            if(ret*sign > INT_MAX) {
                return INT_MAX;
            }
            if(ret*sign < INT_MIN) {
                return INT_MIN;
            }
        }
        return (int)ret * sign;
    }
};
int main()
{
    Solution sln;
    cout << sln.myAtoi("abc") << endl; // result 0
    cout << sln.myAtoi("010") << endl;
    cout << sln.myAtoi("  010") << endl;
    cout << sln.myAtoi("  01 0") << endl; // result 1
    cout << sln.myAtoi("  -0012a42") << endl; // result -12

    cout << sln.myAtoi("+") << endl;
    cout << sln.myAtoi("+5") << endl;
    cout << sln.myAtoi("999999999999999999100909") << endl;
    cout << sln.myAtoi("-999999999999999999100909") << endl;
    cout << sln.myAtoi("--999999999999999999100909") << endl;
    cout << sln.myAtoi("210457") << endl;
    system("pause");
    return 0;
}
