/*
166. Fraction to Recurring Decimal
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.

If the fractional part is repeating, enclose the repeating part in parentheses.

For example,

Given numerator = 1, denominator = 2, return "0.5".
Given numerator = 2, denominator = 1, return "2".
Given numerator = 2, denominator = 3, return "0.(6)".
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <sstream>

using namespace std;

class Solution
{
public:
    string fractionToDecimal(int numerator, int denominator)
    {
        string ret;
        if (numerator == 0) {
            return "0";
        }
        if(numerator < 0 ^ denominator < 0) {
            ret += '-';
        }
        long long int n = abs((long long int)numerator), d = abs((long long int)denominator);
        ret += to_string(n/d);
        n %= d;
        if(n == 0) {
            return ret;
        }
        ret += '.';
        int m;
        unordered_map<int, int> cycle;
        do {
            n*=10;
            m = n % d;
            if(cycle.find(n) == cycle.end()) {
                cycle[n] = ret.length();
                ret += to_string(n/d);
            } else {
                ret.insert(cycle[n], 1, '(');
                ret += ')';
                return ret;
            }
            n = m;
        } while(n);
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.fractionToDecimal(1,6) << endl;
    /*
    cout << sln.fractionToDecimal(20,3) << endl;
    cout << sln.fractionToDecimal(2,3) << endl;
    cout << sln.fractionToDecimal(1,2) << endl;
    cout << sln.fractionToDecimal(2,1) << endl;
    cout << sln.fractionToDecimal(-2,9) << endl;
    cout << sln.fractionToDecimal(1,333) << endl; // 0.(003)
    cout << sln.fractionToDecimal(1,6) << endl;
    */
    //cout << sln.fractionToDecimal(-1,-2147483648) << endl;
    system("pause");
    return 0;
}
