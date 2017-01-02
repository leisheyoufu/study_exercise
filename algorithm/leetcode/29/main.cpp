#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    long long divideLong(long long dividend, long long divisor)
    {
        if(dividend == 0 ) {
            return 0;
        }
        if(divisor == 0) {
            return INT_MAX;
        }
        int sign = 1;
        if((dividend < 0) ^ (divisor < 0))
            sign = -1;
        dividend = abs(dividend);
        divisor = abs(divisor);
        long long ret = 0;
        while(dividend>=divisor) {
            int shift = 1;
            long long part = 2;
            while(dividend > divisor << shift) {
                shift++;
                part <<=1;
            }
            ret += part>>1;
            dividend -= divisor << shift -1;
        }
        return ret*sign;
    }
    int divide(int dividend, int divisor)
    {
        long long int ret = divideLong(dividend, divisor);
        if(ret > INT_MAX || ret < INT_MIN)
            return INT_MAX;
        return ret;
    }
};
int main()
{
    Solution sln;
    printf("%d", sln.divide(-2147483648, -1));
    system("pause");

    return 0;
}
