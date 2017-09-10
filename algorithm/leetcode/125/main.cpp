/*
125. Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

For example,
"A man, a plan, a canal: Panama" is a palindrome.
"race a car" is not a palindrome.

Note:
Have you consider that the string might be empty? This is a good question to ask during an interview.

For the purpose of this problem, we define empty string as valid palindrome.
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
    bool isPalindrome(string s)
    {
        string t = string(s.size(),'\0');
        int j =0;
        for(int i=0; i<s.size(); i++) {
            if(s[i] <= 'z' && s[i] >='a') {
                t[j++] = s[i];
            } else if(s[i] <= 'Z' && s[i] >= 'A') {
                t[j++] = s[i] + 32;
            } else if(s[i] >= '0' && s[i] <='9') {
                t[j++] = s[i];
            }
        }
        t = t.substr(0,j);

        for(int i=0; i<j/2; i++) {
            if(t[i] != t[j-i-1]) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution sln;
    cout << sln.isPalindrome("0P0") << endl;
    system("pause");
    return 0;
}
