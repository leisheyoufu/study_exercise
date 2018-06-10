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
#include<algorithm>
using namespace std;

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        int len = 0;
        int n = s.length();
        if (n==0) {
            return 0;
        }
        for(int i=n-1; i>=0; i--) {
            if(!len && s[i] == ' ') {
                continue;
            } else if(len && s[i] == ' ') {
                return len;
            }
            len++;
        }
        return len;
    }
};
int main()
{
    Solution sln;
    cout << sln.lengthOfLastWord("Hello world!") << endl;  // 6
    system("pause");
    return 0;
}
