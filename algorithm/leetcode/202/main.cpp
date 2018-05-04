/*
202. Happy Number

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example:

Input: 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
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
    int sum(int num)
    {
        int sum = 0;
        while(num) {
            sum += (num % 10) * (num % 10);
            num /= 10;
        }
        return sum;
    }
    bool isHappy(int n)
    {
        unordered_set<int> s;
        while(s.find(n) == s.end()) {
            s.insert(n);
            n = sum(n);
            if(n == 1) {
                return true;
            }
        }
        return false;
    }
};
int main()
{
    Solution sln;
    cout << sln.isHappy(19) << endl;
    system("pause");
    return 0;
}
