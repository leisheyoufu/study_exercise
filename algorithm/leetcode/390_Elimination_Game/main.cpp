/*
390. Elimination Game

There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.

Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.

We keep repeating the steps again, alternating left to right and right to left, until a single number remains.

Find the last number that remains starting with a list of length n.
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
    int helper(int n, bool left)
    {
        if(n == 1) {
            return 1;
        }
        if (left) {
            return 2 * helper(n/2, false);
        }
        return 2 * helper(n/2, true) -1 + n%2;
    }
    int lastRemaining(int n)
    {
        return helper(n, true);
    }
};


int main()
{
    Solution sln;
    cout << sln.lastRemaining(9) << endl; // 6
    cout << sln.lastRemaining(11) << endl; // 8
    cout << sln.lastRemaining(10) << endl; // 8
    cout << sln.lastRemaining(13) << endl; // 6
    return 0;
}
