/*
231. Power of Two
Given an integer, write a function to determine if it is a power of two.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    bool isPowerOfTwo(int n)
    {
        return n > 0 && !(n&(n-1));
    }
};

int main()
{
    Solution sln;
    system("pause");
    return 0;
}
