/*
91. Decode Ways

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.
*/
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    int numDecodings(string s)
    {
        if(s.empty()) {
            return 0;
        }
        int size = s.size();
        vector<int> d(size+1, 0);
        d[0] = 1;
        for(int i=1; i<=size; i++) {
            d[i] = s[i-1] == '0'?0: d[i-1];
            if(i>1 && (s[i-2] == '1' || s[i-2] == '2' && s[i-1] <='6')) {
                d[i] += d[i-2];
            }
        }
        return d.back();
    }
};

int main()
{
    Solution sln;
    cout << sln.numDecodings("1123");
    system("pause");
    return 0;
}
