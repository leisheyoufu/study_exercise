/*
214. Shortest Palindrome

Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

Example 1:

Input: "aacecaaa"
Output: "aaacecaaa"
Example 2:

Input: "abcd"
Output: "dcbabcd"
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<stack>

using namespace std;

class Solution
{
public:
    vector<int> getNext(string s)
    {
        int n = s.length();
        vector<int> next(n, 0);
        for(int i=1; i<n; i++) {
            int j = next[i-1];
            while(j>0 && s[j] != s[i]) {
                j = next[j-1];
            }
            next[i] = s[i] == s[j] ? j+1 :0;
        }
        return next;
    }
    string shortestPalindrome(string s)
    {
        int n = s.length();
        if(n == 0) {
            return s;
        }
        string r = s;
        reverse(r.begin(), r.end());
        string p = s + "#" + r;
        vector<int> next = getNext(p);
        return r.substr(0, r.length()-next.back()) + s;
    }
};
int main()
{
    Solution sln;
    cout << sln.shortestPalindrome("aacecaaa") << endl; // aaacecaaa
    cout << sln.shortestPalindrome("abcd") << endl; // dcbabcd
    system("pause");
    return 0;
}
