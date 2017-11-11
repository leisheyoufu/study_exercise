/*
171. Excel Sheet Column Number
Related to question Excel Sheet Column Title

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28
*/
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include <sstream>

using namespace std;

class Solution
{
public:
    int titleToNumber(string s)
    {
        int num = 0;
        if (s.empty()) {
            return num;
        }
        num += (s[0] - 'A') % 26 + 1;
        for(int i=1; i<s.length(); i++) {
            num *= 26;
            num += (s[i] - 'A') % 26 + 1;
        }
        return num;
    }
};

int main()
{
    Solution sln;
    cout << sln.titleToNumber("AAA") << endl;
    system("pause");
    return 0;
}
