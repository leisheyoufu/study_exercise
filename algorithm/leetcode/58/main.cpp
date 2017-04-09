/*
58. Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

For example,
Given s = "Hello World",
return 5.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        int count =0;
        int temp = 0;
        for(int i=0; i<s.length(); i++) {
            if(s[i] == ' ') {
                count = 0;
            } else {
                count++;
                temp = count;
            }
        }
        return temp;
    }


};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
