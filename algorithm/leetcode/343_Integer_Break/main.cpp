/*
343. Integer Break

Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

Example 1:

Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.
Example 2:

Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
Note: You may assume that n is not less than 2 and not larger than 58.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Solution
{
public:
    int integerBreak(int n)
    {
        if(n == 1) {
            return 1;
        }
        if( n ==2) {
            return 1;
        }
        if( n ==3) {
            return 2;
        }
        if( n == 4) {
            return 4;
        }
        int product = 1;
        while(n > 4) {
            product *= 3;
            n -=3;
        }
        product *=n;
        return product;
    }
};

int main()
{
    Solution sln;
    cout << sln.integerBreak(2) << endl; // 1
    cout << sln.integerBreak(10) << endl; // 36
    cout << sln.integerBreak(58) << endl; // 36
    system("pause");
    return 0;
}
