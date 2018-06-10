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
        unordered_map<int, int> cycle;
        if(numerator<0 ^ denominator<0 ) {
            ret+='-';
        }
        long long int n=numerator,d=denominator;
        n = abs(n);
        d = abs(d);
        if (n == 0) {
            return "0";
        }
        ret += to_string(n/d);
        long long int r = n %d;
        if (r != 0) {
            ret += '.';
        }
        while(r != 0) {
            if (cycle.find(r) != cycle.end()) {
                ret.insert(cycle[r],1,'(');
                ret += ')';
                break;
            }
            cycle[r] = ret.size();
            r*=10;
            ret += to_string(r/d);
            r = r % d;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    /*
    cout << sln.fractionToDecimal(20,3) << endl;
    cout << sln.fractionToDecimal(2,3) << endl;
    cout << sln.fractionToDecimal(1,2) << endl;
    cout << sln.fractionToDecimal(2,1) << endl;
    cout << sln.fractionToDecimal(-2,9) << endl;
    cout << sln.fractionToDecimal(1,333) << endl;
    cout << sln.fractionToDecimal(1,6) << endl;
    */
    cout << sln.fractionToDecimal(-1,-2147483648) << endl;
    system("pause");
    return 0;
}
