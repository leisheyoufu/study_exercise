/*
Combination Sum

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
    string count(string say)
    {
        int count = 1;
        char num = say[0];
        stringstream ss;
        for(int i=1; i<say.size(); i++) {
            if(say[i-1] == say[i]) {
                count++;
            } else {
                ss << count << num;
                num = say[i];
                count = 1;
            }
        }
        ss << count << num;
        return ss.str();
    }
    string countAndSay(int n)
    {
        string temp = "1";
        for(int i=1; i<n; i++) {
            temp = count(temp);
        }
        return temp;
    }
};
int main()
{
    Solution sln;
    cout << sln.countAndSay(6) << endl;
    system("pause");
    return 0;
}
