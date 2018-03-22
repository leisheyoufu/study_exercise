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
        int l1 = a.length();
        int l2 = b.length();
        int l = max(l1,l2);
        string s(l, 0);
        int i = 0;
        int num1, num2, c=0;
        while(i<l) {
            if(l1-1-i >=0) {
                num1 = a[l1-1-i] - '0';
            } else {
                num1 = 0;
            }
            if(l2-1-i >=0) {
                num2 = b[l2-1-i] - '0';
            } else {
                num2 = 0;
            }
            int sum = num1 + num2 + c;
            if(sum >= 2) {
                c = 1;
                sum -= 2;
            } else {
                c = 0;
            }
            s[i++] = sum + '0';
        }
        if (c > 0) {
            s.push_back('1');
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
int main()
{
    Solution sln;
    cout << sln.addBinary("1", "11") << endl; // 100
    cout << sln.addBinary("10", "111") << endl; // 1001
    cout << sln.addBinary("1010", "1011") << endl; // 10101
    system("pause");
    return 0;
}
