/*
829. Consecutive Numbers Sum

Given a positive integer N, how many ways can we write it as a sum of consecutive positive integers?

Example 1:

Input: 5
Output: 2
Explanation: 5 = 5 = 2 + 3
Example 2:

Input: 9
Output: 3
Explanation: 9 = 9 = 4 + 5 = 2 + 3 + 4
Example 3:

Input: 15
Output: 4
Explanation: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
Note: 1 <= N <= 10 ^ 9.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

class Solution
{
public:
    int consecutiveNumbersSum(int N)
    {
        if(N == 0) {
            return 0;
        }
        int ret = 0;
        for(int i=1; i<=sqrt(2*N); i++) {
            int a = N - i*(i-1)/2;
            if(a <= 0) {
                break;
            }
            if(a % i == 0) {
                ret ++;
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.consecutiveNumbersSum(5) << endl; // 2
    cout << sln.consecutiveNumbersSum(15) << endl; // 4
    system("pause");
    return 0;
}
