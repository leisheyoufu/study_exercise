/*
201. Bitwise AND of Numbers Range

Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.

Example 1:

Input: [5,7]
Output: 4
Example 2:

Input: [0,1]
Output: 0
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int rangeBitwiseAnd2(int m, int n)
    {
        int ret = 0;
        int i = 0;
        while(m || n) {
            if((m & 1) == (n &1)) {
                ret += (m&1)<< i;
            } else {
                ret = 0;
            }
            m >>= 1;
            n >>= 1;
            i++;
        }
        return ret;
    }

    int rangeBitwiseAnd(int m, int n)
    {
        int count = 0;
        while(n != m) {
            m >>= 1;
            n >>= 1;
            count++;
        }
        return (m<<count);
    }
};
int main()
{
    Solution sln;
    cout << sln.rangeBitwiseAnd(5, 7) << endl; // 4
    cout << sln.rangeBitwiseAnd(0, 1) << endl; // 0
    system("pause");
    return 0;
}
