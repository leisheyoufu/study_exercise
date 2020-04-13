/*
336. Palindrome Pairs
Given a list of unique words, find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:

Input: ["abcd","dcba","lls","s","sssll"]
Output: [[0,1],[1,0],[3,2],[2,4]]
Explanation: The palindromes are ["dcbaabcd","abcddcba","slls","llssssll"]
Example 2:

Input: ["bat","tab","cat"]
Output: [[0,1],[1,0]]
Explanation: The palindromes are ["battab","tabbat"]
Accepted
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>
#include<set>

using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        int n = s.length();
        int left = 0, right = n-1;
        while(left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    vector<vector<int>> palindromePairs(vector<string>& words)
    {
        int n = words.size();
        vector<vector<int>> ret;
        unordered_map<string, int> dict;
        for(int i=0; i<n; i++) {
            string temp = words[i];
            reverse(temp.begin(), temp.end());
            dict[temp] = i;
        }
        for(int i=0; i<n; i++) {
            string word = words[i];
            for(int j=0; j<word.length(); j++) {
                string left = word.substr(0, j);
                string right = word.substr(j);
                if(dict.find(left) != dict.end() && dict[left] != i && isPalindrome(right)) {
                    ret.push_back({i, dict[left]});
                    if(left.empty()) {
                        ret.push_back({dict[left], i});
                    }
                }
                if(dict.find(right) != dict.end() && dict[right] !=i && isPalindrome(left)) {
                    ret.push_back({dict[right], i});
                }
            }
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    // vector<string> words = {"abcd","dcba","lls","s","sssll"}; // [1,0] [0,1] [3,2] [2,4]
    vector<string> words = {"bat","tab","cat"}; // [[0,1],[1,0]]
    vector<vector<int>> ret = sln.palindromePairs(words);
    for(auto pair: ret) {
        cout << "[" << pair[0] << "," << pair[1] << "]" << " ";
    }
    cout << endl;
    system("pause");
    return 0;
}
