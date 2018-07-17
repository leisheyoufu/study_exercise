/*
264. Ugly Number II

Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example:

Input: n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:

1 is typically treated as an ugly number.
n does not exceed 1690.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int nthUglyNumber(int n)
    {
        if(n<=0) {
            return 0;
        }
        vector<int> nums(n, 1);
        int index[3] = {0,0,0};
        int c_val[3] = {2,3,5};
        int val[3] = {2,3,5};
        for(int i=1; i<n; i++) {
            int min_index = 0;
            if(val[1] < val[min_index]) {
                min_index = 1;
            }
            if(val[2] < val[min_index]) {
                min_index = 2;
            }
            if(val[min_index] == nums[i-1]) {
                i--;
            } else {
                nums[i] = val[min_index];
                val[min_index] = c_val[min_index] * nums[index[min_index]];
            }
            index[min_index]++;
            val[min_index] = c_val[min_index] * nums[index[min_index]];
        }
        return nums[n-1];
    }
};
int main()
{
    Solution sln;
    cout << sln.nthUglyNumber(2) << endl; // 2
    cout << sln.nthUglyNumber(3) << endl; // 3
    cout << sln.nthUglyNumber(4) << endl; // 4
    cout << sln.nthUglyNumber(5) << endl; // 5
    cout << sln.nthUglyNumber(6) << endl; // 6
    cout << sln.nthUglyNumber(7) << endl; // 8
    cout << sln.nthUglyNumber(10) << endl; // 12
    system("pause");
    return 0;
}
