/*
233. Number of Digit One
Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.

For example:
Given n = 13,
Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int countDigitOne(int n)
    {
        int ones = 0;
        for(long i=1; i<=n; i*=10) {
            long a = n / i;
            long b = n % i;
            ones += (a+8) / 10 * i;
            if ( a % 10 == 1) {
                ones += b + 1;
            }
        }
        return ones;
    }
};

int main()
{
    Solution sln;
    cout << sln.countDigitOne(1410065408);
    system("pause");
    return 0;
}
