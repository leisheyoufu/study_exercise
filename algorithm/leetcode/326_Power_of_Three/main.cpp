/*
326. Power of Three
Given an integer, write a function to determine if it is a power of three.

Example 1:

Input: 27
Output: true
Example 2:

Input: 0
Output: false
Example 3:

Input: 9
Output: true
Example 4:

Input: 45
Output: false
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Solution
{
public:
    bool isPowerOfThree(int n)
    {
        if(n<=0) {
            return false;
        }
        while(n != 1) {
            if(n%3 != 0) {
                return false;
            }
            n /= 3;
        }
        return true;
    }
};

int main()
{
    Solution sln;
    cout << sln.isPowerOfThree(1) << endl;  // 1
    cout << sln.isPowerOfThree(27) << endl;  // 1
    cout << sln.isPowerOfThree(45) << endl;  // 0
    system("pause");
    return 0;
}
