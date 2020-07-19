/*
367. Valid Perfect Square
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Follow up: Do not use any built-in library function such as sqrt.



Example 1:

Input: num = 16
Output: true
Example 2:

Input: num = 14
Output: false


Constraints:

1 <= num <= 2^31 - 1

*/

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    bool isPerfectSquare(int num)
    {
        if(num <=0) {
            return false;
        }
        if(num == 1) {
            return true;
        }
        int l = 2, r = num / 2;
        while(l<=r) {
            long long mid=l+(r-l)/2;
            if(mid * mid == (long long) num) {
                return true;
            }
            if(mid*mid < num) {
                l = mid + 1;
            } else {
                r = mid -1;
            }
        }
        return false;
    }
};
int main()
{
    Solution sln;
    cout << sln.isPerfectSquare(63) << endl; // 0
    cout << sln.isPerfectSquare(4) << endl; // true
    cout << sln.isPerfectSquare(2000105819) << endl; // 0

    system("pause");
    return 0;
}
