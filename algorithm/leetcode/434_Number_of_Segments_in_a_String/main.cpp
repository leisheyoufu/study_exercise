/*

434. Number of Segments in a String

You are given a string s, return the number of segments in the string.

A segment is defined to be a contiguous sequence of non-space characters.



Example 1:

Input: s = "Hello, my name is John"
Output: 5
Explanation: The five segments are ["Hello,", "my", "name", "is", "John"]
Example 2:

Input: s = "Hello"
Output: 1
Example 3:

Input: s = "love live! mu'sic forever"
Output: 4
Example 4:

Input: s = ""
Output: 0
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int countSegments(string s)
    {
        if(s.empty()) {
            return 0;
        }
        int count = 0;
        char prev = s[0];
        if (prev != ' ') {
            count = 1;
        }
        for(int i=1; i<s.length(); i++) {
            if(s[i] != ' ' && prev == ' ') {
                count ++;
            }
            prev = s[i];
        }
        return count;
    }
};

int main()
{
    Solution sln;
    cout << sln.countSegments("Hello, my name is John") << endl; // 5
    cout << sln.countSegments("hello") << endl; // 1
    cout << sln.countSegments("love live! mu'sic forever") << endl; // 4
    cout << sln.countSegments("") << endl; // 0
    system("pause");
    return 0;
}
