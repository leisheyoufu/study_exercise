/*
Substring with Concatenation of All Words

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.

For example, given:
s: "barfoothefoobarman"
words: ["foo", "bar"]

You should return the indices: [0,9].
(order does not matter).
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
    vector<int> findSubstring(string s, vector<string>& words)
    {
        vector<int> ret;
        if(words.empty()) {
            return ret;
        }
        unordered_map<string, int> dict;
        unordered_map<string, int> curr;
        for(int i=0; i<words.size(); i++) {
            dict[words[i]]++;
        }
        int word_size = words[0].length();
        int n = words.size();
        //int length = s.length() - n*
        for(int i=0; i<=(int)s.length() - n*word_size ; i++) {
            curr.clear();
            int j;
            for(j=0; j < n; j++) {
                string word = s.substr(i + j * word_size, word_size);
                if(dict.find(word) != dict.end()) {
                    curr[word] ++;
                    if(curr[word] > dict[word]) {
                        break;
                    }
                } else {
                    break;
                }
            }
            if(j ==n) {
                ret.push_back(i);
            }
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    string s = "a";
    string b = "a";
    vector<string> words;
    words.push_back("word");
    words.push_back("good");
    words.push_back("best");
    words.push_back("good");
    sln.findSubstring("wordgoodgoodgoodbestword", words);
    //cout << sln.countAndSay(6) << endl;
    system("pause");
    return 0;
}
