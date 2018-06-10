/*
168. Excel Sheet Column Title
Given a positive integer, return its corresponding column title as appear in an Excel sheet.

For example:

    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
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
    string convertToTitle(int n)
    {
        /*
        if( n<= 0) {
            return "";
        }
        string ret;
        while(n) {
            ret += (n-1) % 26 + 'A';
            n = (n-1)/ 26;
        }
        reverse(ret.begin(), ret.end());
        return ret;
        */
        if( n<= 0) {
            return "";
        }
        string ret;
        while(n) {
            ret = char((n-1) % 26 + 'A') + ret;
            n = (n-1) / 26;
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    cout << sln.convertToTitle(27) << endl;
    system("pause");
    return 0;
}
