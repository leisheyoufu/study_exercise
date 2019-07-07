/*
258. Add Digits

Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

Example:

Input: 38
Output: 2
Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
             Since 2 has only one digit, return it.

Follow up:
Could you do it without any loop/recursion in O(1) runtime?
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
    /*
    int addDigits(int num)
    {
        while(num >= 10) {
            int temp = 0;
            while(num) {
                temp += num % 10;
                num /= 10;
            }
            num = temp;
        }
        return num;
    }
    */
    int addDigits(int num)
    {
        return (num -1) % 9 +1;
    }
};
int main()
{
    Solution sln;
    cout << sln.addDigits(38) << endl;
    system("pause");
    return 0;
}
