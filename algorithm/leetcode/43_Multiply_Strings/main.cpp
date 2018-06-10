/*
43. Multiply Strings

Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2.

Note:

The length of both num1 and num2 is < 110.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        vector<int> result (num1.size() + num2.size()+1, 0);
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        int a, b;
        for(int i=0; i<num1.size(); i++) {
            int a = num1[i] - '0';
            for(int j=0; j<num2.size(); j++) {
                int b = num2[j] - '0';
                result[i+j] += a*b;
            }
        }
        int count = 1;
        for(int i=0; i<result.size()-1; i++) {
            result[i+1] += result[i] / 10;
            result[i] %= 10;
            if (result[i] > 0) {
                count = i + 1;
            }

        }
        string ret(count, '0');
        for(int i=0; i< count; i++) {
            ret[count -1 - i] = '0' + result[i];
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.multiply("999", "0");
    system("pause");
    return 0;
}
