/*
371. Sum of Two Integers

Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

Example 1:

Input: a = 1, b = 2
Output: 3
Example 2:

Input: a = -2, b = 3
Output: 1
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int getSum(int a, int b)
    {
        if(b == 0) {
            return a;
        }
        int sum = a ^ b;
        int c = (unsigned int)(a & b) << 1;
        return getSum(sum, c);
    }
};

int main()
{
    Solution sln;
    cout << sln.getSum(1,2) << endl; // 3
    cout << sln.getSum(-2,3) << endl; // 1
    cout << sln.getSum(-2,-7) << endl; // -9
    cout << sln.getSum(5, -9) << endl; // -4
    cout << sln.getSum(-1, 1) << endl; // 0

    printf("%x\n", (unsigned int)(-3));  // 负数补码是符号位不变，正数 -1后再取反
    printf("%x\n", (unsigned int)(3));
    system("pause");
    return 0;
}
