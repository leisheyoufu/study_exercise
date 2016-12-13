#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

class Solution
{
public:
	double power(double x, int n)
	{
		if(n == 0) {
			return 1.0;
		}
		double half = power(x,n/2);
		if(n%2==1) {
			return half * half *x;
		}
		return half * half;
	}
	double myPow(double x, int n) {
        if(n<0) {
			if( n<INT_MIN) {
				return 0;
			} else if (n==INT_MIN) {
				return 1.0 / (pow(x, INT_MAX)*x);
			}
			return 1.0/power(x, -n);
		}
		if (n>INT_MAX) {
			return 0;
		}
		return power(x, n);
    }
};
int main()
{
	Solution sln;	
	printf("%f\n", sln.myPow(1.0,-2147483648));
    system("pause");
    return 0;
}