/*
Word Ladder

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.

Note:
Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.
UPDATE (2017/1/20):
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.

CL:
"hit"
"cog"
["hot","dot","dog","lot","log"]
my output is 5, expected is 0 why?
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>
#include<unordered_map>

using namespace std;

class Solution
{
public:
    bool oneDiff(string s1, string s2)
    {
        int diff = 0;
        for(int i=0; i<s1.length(); i++) {
            if(s1[i] != s2[i]) {
                diff++;
            }
        }
        if(diff == 1) {
            return true;
        }
        return false;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList)
    {
        if(beginWord.empty() || endWord.empty() ||
           beginWord.length() != endWord.length() || beginWord ==endWord) {
            return 0;
        }
        if(oneDiff(beginWord,endWord)) {
            return 2;
        }
        queue<string> q;
        unordered_map<string,int> map;
        q.push(beginWord);
        map[beginWord] = 1;
        while(!q.empty()) {
            string head = q.front();
            q.pop();
            for(int i=0; i<head.length(); i++) {
                for(int k='a'; k<='z'; k++) {
                    if(head[i] == k) {
                        continue;
                    }
                    string temp(head);
                    temp[i] = k;
                    if(temp == endWord) {
                        return map[head] + 1;
                    }
                    if(find(wordList.begin(), wordList.end(),temp)!= wordList.end() && map.find(temp) == map.end()) {
                        q.push(temp);
                        map[temp] = map[head] +1;
                    }
                }
            }
        }
        return 0;
    }
};
int main()
{
    Solution sln;
    string start = "hit";
    string end= "cog";
    string dict[] = {"hot","dot","dog","lot","log","cog"};
    vector<string> v(dict, dict+sizeof(dict)/sizeof(string));
    sln.ladderLength(start, end,v);
    system("pause");
    return 0;
}
