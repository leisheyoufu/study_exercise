/* Reverse Integer
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
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int reverse(int x) 
	{
		long long ret = 0;
		/*
		int sign = 1;
		if(x < 0) {
			sign = -1;
			x = -x;
		}
		*/
		while(x) {
			ret *= 10;
			ret += x % 10;
			if(ret > INT_MAX || ret < INT_MIN) {
				return 0;
			}
			x /= 10;
		}
		return (int)ret;
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
