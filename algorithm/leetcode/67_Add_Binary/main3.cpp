/*
67. Add Binary

Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<sstream>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {
        string num1 = (a.length() > b.length())? a : b;
        string num2 = (a.length() > b.length())? b : a;
        int n1 = num1.length();
        int n2 = num2.length();
        int n = min(n1, n2);
        int c = 0;
        string ret;
        for(int i=0; i<n; i++) {
            int val = num1[n1-i-1] - '0' + num2[n2-i-1] - '0' + c;
            ret.push_back(val % 2 + '0');
            if (val >=2) {
                c = 1;
            } else {
                c = 0;
            }
        }
        for(int i=n; i< n1; i++) {
            int val = num1[n1-i-1] - '0' + c;
            ret.push_back(val % 2 + '0');
            if (val >=2) {
                c = 1;
            } else {
                c = 0;
            }
        }
        if (c == 1) {
            ret.push_back('1');
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.addBinary("100", "110010") << endl; // "110110"
    cout << sln.addBinary("1", "111") << endl; // 1000
    cout << sln.addBinary("1", "") << endl; // 1
    cout << sln.addBinary("1", "11") << endl; // 100
    cout << sln.addBinary("10", "111") << endl; // 1001
    cout << sln.addBinary("1010", "1011") << endl; // 10101
    system("pause");
    return 0;
}
