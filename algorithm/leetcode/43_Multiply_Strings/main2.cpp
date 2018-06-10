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
        string ret;
        int n1 = num1.length();
        int n2 = num2.length();
        if (n1 == 1 && num1[0] == '0' || n2== 1 && num2[0]== '0') {
            return "0";
        }
        vector<int> result (n1+n2, 0);
        for(int i=0; i<n2; i++) {
            for(int j=0; j<n1; j++) {
                result[i+j] += (int)(num1[j] - '0')*(int)(num2[i] - '0');
            }
        }
        for(int i=n1+n2-2; i>=1; i--) {
            result[i-1] += result[i] / 10;
            result[i] = result[i] % 10;
            ret.push_back(result[i] + '0');
        }
        while(result[0] > 0) {
            ret.push_back(result[0] % 10 + '0');
            result[0] /= 10;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.multiply("0", "24");
    system("pause");
    return 0;
}
