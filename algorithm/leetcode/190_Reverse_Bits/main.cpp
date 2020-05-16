/*
190. Reverse Bits

Reverse bits of a given 32 bits unsigned integer.



Example 1:

Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.
Example 2:

Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10111111111111111111111111111111.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>
#include <bitset>

using namespace std;

class Solution
{
public:
    uint32_t reverseBits(uint32_t n)
    {
        int bits = 32;
        uint32_t ret = 0;
        while(bits) {
            bits--;
            ret = ret << 1 | (n&1);
            n = n >> 1;
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << bitset<32>(sln.reverseBits(0b00000010100101000001111010011100))<< endl; // 00111001011110000010100101000000
    cout << bitset<32>(sln.reverseBits(0b11111111111111111111111111111101))<< endl; // 10111111111111111111111111111111
    system("pause");
    return 0;
}
