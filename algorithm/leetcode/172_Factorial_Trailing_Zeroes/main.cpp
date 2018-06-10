/*
172. Factorial Trailing Zeroes
Given an integer n, return the number of trailing zeroes in n!.

Note: Your solution should be in logarithmic time complexity.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:

    int trailingZeroes(int n)
    {
        if(n < 5) {
            return 0;
        }
        int count = 0;
        while(n/5 != 0) {
            n /= 5;
            count +=n;
        }
        return count;
    }
};

int main()
{
    Solution sln;
    cout << sln.trailingZeroes(1808548329);
    system("pause");
    return 0;
}
