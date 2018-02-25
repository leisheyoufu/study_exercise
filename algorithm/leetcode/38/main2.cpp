/*
38. Count and Say

The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.

Note: The sequence of integers will be represented as a string.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include <sstream>
using namespace std;

class Solution
{
public:
    string int2str(int num)
    {
        string s;
        while(num) {
            s += num % 10 + '0';
            num /= 10;
        }
        reverse(s.begin(), s.end());
        return s;
    }
    string countAndSay(int n)
    {
        if(n<1) {
            return "";
        }
        string s = "1";
        for(int i=2; i<=n; i++) {
            int count = 1;
            int j = 1;
            char c = s[0];
            string tmp;
            while(j<s.length()) {
                if(s[j] == s[j-1]) {
                    count ++;
                } else {
                    tmp += int2str(count);
                    tmp += c;
                    c = s[j];
                    count = 1;
                }
                j++;
            }
            tmp += int2str(count);
            tmp += c;
            s = tmp;
        }
        return s;
    }
};
int main()
{
    Solution sln;
    cout << sln.countAndSay(1) << endl;  // 1
    cout << sln.countAndSay(2) << endl;  // 11
    cout << sln.countAndSay(4) << endl;  // 1211
    cout << sln.countAndSay(6) << endl;  // 312211
    system("pause");
    return 0;
}
