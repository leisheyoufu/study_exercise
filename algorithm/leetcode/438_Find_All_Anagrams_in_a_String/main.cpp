/*

438. Find All Anagrams in a String

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int n1 = s.length();
        int n2 = p.length();
        vector<int> ret;
        if(n1 == 0 || n2 ==0) {
            return ret;
        }
        int m1[26] = {0}, m2[26] = {0};
        for(int i=0; i<n2; i++) {
            int elem = p[i] - 'a';
            m1[elem]++;
        }
        int match = 0, j = 0;
        for(int i=0; i<n1; i++) {
            if (i>=n2) {
                int start_elem = s[j] - 'a';
                if (m2[start_elem] > 0) {
                    m2[start_elem] --;
                    if (m2[start_elem] < m1[start_elem]) {
                        match --;
                    }
                }
                j++;
            }
            int elem = s[i] - 'a';

            if (m1[elem] >0) {
                m2[elem]++;
                if(m2[elem] <= m1[elem]) {
                    match++;
                }
            }
            if(match == n2) {
                ret.push_back(i-n2+1);
            }
        }
        return ret;
    }
};

void print_array(vector<int> v)
{
    for(auto e:v) {
        cout << e << " ";
    }
    cout << endl;
}

int main()
{
    Solution sln;
    vector<int> v = sln.findAnagrams("cbaebabacd", "abc");
    print_array(v);  // [0, 6]
    v = sln.findAnagrams("abab", "ab");
    print_array(v);  // [0, 1, 2]
    system("pause");
    return 0;
}
