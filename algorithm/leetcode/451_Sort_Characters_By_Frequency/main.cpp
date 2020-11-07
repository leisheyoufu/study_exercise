/*
451. Sort Characters By Frequency

Given a string, sort it in decreasing order based on the frequency of characters.

Example 1:

Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
Example 2:

Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
Example 3:

Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_map>


using namespace std;

class Solution
{
public:
    static bool comp(pair<char,int> &a, pair<char, int> &b)
    {
        if(a.second > b.second) {
            return true;
        }
        return false;
    }
    string frequencySort(string s)
    {
        if (s.empty()) {
            return "";
        }
        unordered_map<char,int> m;
        for(char c : s) {
            if(m.count(c) == 0) {
                m[c] = 1;
            } else {
                m[c]++;
            }
        }
        vector<pair<char,int>> freq;
        for(unordered_map<char,int>::iterator iter = m.begin(); iter!=m.end(); iter++) {
            freq.push_back(make_pair(iter->first, iter->second));
        }
        sort(freq.begin(), freq.end(),comp);
        string ret;
        for(auto item : freq) {
            for(int i=0; i<item.second; i++) {
                ret += item.first;
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    cout << sln.frequencySort("cccaaa") << endl; //cccaaa
    cout << sln.frequencySort("tree") << endl; //eert
    cout << sln.frequencySort("Aabb") << endl; //bbAa
    system("pause");
    return 0;
}
