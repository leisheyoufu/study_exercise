/*
397. Integer Replacement

Given a positive integer n and you can do operations as follow:

If n is even, replace n with n/2.
If n is odd, you can replace n with either n + 1 or n - 1.
What is the minimum number of replacements needed for n to become 1?

Example 1:

Input:
8

Output:
3

Explanation:
8 -> 4 -> 2 -> 1
Example 2:

Input:
7

Output:
4

Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    /*  错的
    int integerReplacement(int n)
    {
        if (n <=1) {
            return 0;
        }
        if(n == INT_MAX) {
            return 32;
        }
        vector<int> dp(n+2, INT_MAX);
        dp[1] = 0;
        for(int i = 1; i<=n+1; i++) {
            long long k = i*2;
            if(k <= n +1) {
                dp[k] = min(dp[k], dp[i] + 1);
            }
            k = i + 1;
            if(k <= n+1) {
                dp[k] = min(dp[k], dp[i] + 1);
            }
            k = i - 1;
            if(k <= n+1 && k >=2) {
                dp[k] = min(dp[k], dp[i] + 1);
            }
        }
        return dp[n];
    }
    */

    int integerReplacement(int n)
    {
        if (n <=1) {
            return 0;
        }
        if (n == INT_MAX) {
            return 32;
        }
        int count = 0;
        while( n != 1) {
            if( (n & 1) == 0) {
                n /= 2;
            } else if (n == 3 || ((n >> 1) & 1) == 0) {
                n--;
            } else {
                n++;
            }
            count ++;
        }
        return count;
    }
};

int main()
{
    Solution sln;
    cout << sln.integerReplacement(8) << endl;  // 3
    cout << sln.integerReplacement(7) << endl;  // 4
    cout << sln.integerReplacement(15) << endl;  // 5
    cout << sln.integerReplacement(66789443) << endl; // 32
    cout << sln.integerReplacement(INT_MAX) << endl; // 32
    system("pause");
    return 0;
}
