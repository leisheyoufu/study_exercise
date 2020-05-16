/*
191. Number of 1 Bits

Write a function that takes an unsigned integer and return the number of '1' bits it has (also known as the Hamming weight).



Example 1:

Input: 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.
Example 2:

Input: 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.
Example 3:

Input: 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.


Note:

Note that in some languages such as Java, there is no unsigned integer type. In this case, the input will be given as signed integer type and should not affect your implementation, as the internal binary representation of the integer is the same whether it is signed or unsigned.
In Java, the compiler represents the signed integers using 2's complement notation. Therefore, in Example 3 above the input represents the signed integer -3.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:
    int hammingWeight(uint32_t n)
    {
        int count = 0;
        while(n) {
            count ++;
            n = n&(n-1);
        }
        return count;
    }
};
int main()
{
    Solution sln;
    uint32_t n = 0b11111111111111111111111111111101;
    cout << sln.hammingWeight(n) << endl; // 31
    cout << sln.hammingWeight(0b00000000000000000000000010000000) << endl; // 1
    cout << sln.hammingWeight(0b00000000000000000000000000001011) << endl; // 3
    cout << sln.hammingWeight(0b00000000000000000000000000000000) << endl; // 0
    system("pause");
    return 0;
}
