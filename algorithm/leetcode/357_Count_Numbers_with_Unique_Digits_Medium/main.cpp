/*
357. Count Numbers with Unique Digits

Given a non-negative integer n, count all numbers with unique digits, x, where 0 ≤ x < 10n.

Example:

Input: 2
Output: 91
Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100,
             excluding 11,22,33,44,55,66,77,88,99
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    int countNumbersWithUniqueDigits(int n)
    {
        if(n==0) {
            return 1;
        }
        if(n==1) {
            return 10;
        }
        if(n==2) {
            return 9*9 + 10;
        }
        int ret = 9*9 + 10;
        int temp = 9*9;
        int end = min(8, n-2);
        for(int i=0; i<end; i++) {
            temp = temp * (8-i);
            ret += temp;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.countNumbersWithUniqueDigits(8) << endl;
    system("pause");
    return 0;
}
