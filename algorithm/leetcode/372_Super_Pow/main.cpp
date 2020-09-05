/*
372. Super Pow

Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

Example 1:

Input: a = 2, b = [3]
Output: 8
Example 2:

Input: a = 2, b = [1,0]
Output: 1024
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int superPow(int a, vector<int>& b)
    {
        if(b.size() == 0) {
            return 1;
        }
        int curr = b.back();
        b.pop_back();
        return powermod(superPow(a, b), 10) * powermod(a, curr) % base;
    }
private:
    const int base = 1337;
    int powermod(int a, int b)
    {
        int ret = 1;
        a %= base;
        for(int i=0; i<b; i++) {
            ret = (ret * a) % base;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    vector<int> b = {3};
    cout << sln.superPow(2, b) << endl; // 8
    b = {1, 0};
    cout << sln.superPow(2, b) << endl; // 1024
    system("pause");
    return 0;
}
