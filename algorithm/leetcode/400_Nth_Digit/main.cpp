/*
400. Nth Digit

Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:

Input:
3

Output:
3
Example 2:

Input:
11

Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

class Solution
{
public:

    int findNthDigit(int n)
    {
        if(n<=0) {
            return 0;
        }
        long long count = 9, base = 1, bitNum = 1;
        while(n-count*bitNum > 0) {
            base += count;
            n -= count * bitNum;
            count *=10;
            bitNum++;
        }
        long long index = (n-1) / bitNum;
        long long seq = n - index * bitNum;
        return getDigit(base + index, bitNum - (seq-1));
    }

    int getDigit(long long  num, long long bit)
    {
        int ret;
        if (!bit) {
            return num % 10;
        }
        while(bit) {
            bit--;
            ret = num % 10;
            num /= 10;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.findNthDigit(13) << endl; // 1
    cout << sln.findNthDigit(14) << endl; // 1
    cout << sln.findNthDigit(88766375) << endl; // 6
    cout << sln.findNthDigit(1000000000) << endl; // 1
    system("pause");
    return 0;
}
