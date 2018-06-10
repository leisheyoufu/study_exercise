/* Divide Two Integers
Divide two integers without using multiplication, division and mod operator.

If it is overflow, return MAX_INT.
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        if(dividend == 0) {
            return 0;
        }
        if(divisor == 0) {
            return INT_MAX;
        }
        int sign = 1;
        if( (dividend <0) ^(divisor <0)) {
            sign = -1;
        }
        long long ret = divide_long(dividend, divisor);

        if ( ret == INT_MAX + (long long)1 && sign == -1) {
            return -ret;
        } else if(ret >= INT_MAX && sign == 1) {
            return INT_MAX;
        } else if( ret > INT_MAX + (long long)1) {
            return INT_MAX;
        }
        if (sign == 1) {
            return ret;
        }
        return -ret;
    }

    long long divide_long(long long dividend, long long divisor)
    {
        long long ret = 0;
        dividend = abs(dividend);
        divisor = abs(divisor);
        while(dividend > 0) {
            int cnt = 1;
            int temp;
            while(dividend - (divisor << cnt) > 0) {
                cnt++;
            }
            if(dividend - (divisor << cnt) == 0) {
                temp = cnt;
            } else {
                temp = cnt - 1;
            }
            dividend -= divisor << temp;
            if(dividend >= 0) {
                ret += (long long)1 << temp;
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.divide(-2147483648, -1) << endl;  // 2147483647
    cout << sln.divide(-24, -3) << endl;  // 8
    cout << sln.divide(-24, -5) << endl; // 4
    cout << sln.divide(65, 11) << endl; // 5
    // printf("%ld", sln.divide(-2147483648, -1));
    system("pause");

    return 0;
}
