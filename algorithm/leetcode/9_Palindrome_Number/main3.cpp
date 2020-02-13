/*
9. Palindrome Number
Determine whether an integer is a palindrome. Do this without extra space.

click to show spoilers.

Some hints:
Could negative integers be palindromes? (ie, -1)

If you are thinking of converting the integer to string, note the restriction of using extra space.

You could also try reversing an integer. However, if you have solved the problem "Reverse Integer", you know that the reversed integer might overflow. How would you handle such case?

There is a more generic way of solving this problem.
*/
#include<iostream>
#include<string>
#include<algorithm>

using namespace std;
class Solution
{
public:

    bool isPalindrome(int x)
    {
        if(x<0) {
            return false;
        }
        int m = 1;
        int temp = x;
        while(temp / m>= 10) {
            m*=10;
        }
        while(m) {
            //cout <<"x=" << x << " m=" << m << endl;
            if(x%10 != x / m) {
                return false;
            }
            x = x - x/m *m;
            x /= 10;
            m /=100;
        }
        return true;
    }
};
int main()
{
    Solution sln;
    cout << sln.isPalindrome(11)<< endl;  // 1
    cout << sln.isPalindrome(1001)<< endl;  // 1
    cout << sln.isPalindrome(10)<< endl;  // 0
    cout << sln.isPalindrome(99099) << endl;  // 1
    cout << sln.isPalindrome(987789) << endl;  // 1
    // cout << sln.isPalindrome(-2147447412) << endl;
    // cout << sln.isPalindrome(-2147483648) << endl;
    system("pause");
    return 0;
}
