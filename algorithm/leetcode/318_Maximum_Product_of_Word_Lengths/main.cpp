/*
318. Maximum Product of Word Lengths

Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0
Explanation: No such pair of words.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>

using namespace std;

class Solution
{
public:
    int maxProduct(vector<string>& words)
    {
        int n = words.size();
        if(n == 0) {
            return 0;
        }
        vector<int> bits(n, 0);
        for(int i=0; i<n; i++) {
            for(int j=0; j<words[i].length(); j++) {
                bits[i] |= 1 << words[i][j] - 'a';
            }
        }
        int ret = 0;
        for(int i=0; i<n-1; i++) {
            for(int j=i+1; j<n; j++) {
                if((bits[i] & bits[j]) == 0) {  // cl: be carefull of priority
                    ret = max(ret, (int)words[i].length() * (int)words[j].length());
                }
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    //vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    //ector<string> words = {"a","aa","aaa","aaaa"};
    vector<string> words = {"a","ab","abc","d","cd","bcd","abcd"};
    cout << sln.maxProduct(words) << endl;
    system("pause");
    return 0;
}
