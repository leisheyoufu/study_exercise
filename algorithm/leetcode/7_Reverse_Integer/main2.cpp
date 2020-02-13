/*
7. Reverse Integer
Reverse digits of an integer.

Example1: x = 123, return 321
Example2: x = -123, return -321

click to show spoilers.

Note:
The input is assumed to be a 32-bit signed integer. Your function should return 0 when the reversed integer overflows.
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Solution
{
public:

    int reverse(int x)
    {
        long long ret = 0;
        while(x) {
            ret = ret *10 + x % 10;
            x /= 10;
        }
        if(ret > INT_MAX || ret < INT_MIN) {
            return 0;
        }
        return int(ret);
    }
};
int main()
{
    Solution sln;
    cout<< sln.reverse(1534236469)<< endl;
    cout<< sln.reverse(-98)<< endl;
    cout<< sln.reverse(120)<< endl;
    system("pause");
    return 0;
}
