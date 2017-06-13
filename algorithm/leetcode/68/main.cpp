/*
68. Text Justification

Given an array of words and a length L, format the text such that each line has exactly L characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly L characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

For example,
words: ["This", "is", "an", "example", "of", "text", "justification."]
L: 16.

Return the formatted lines as:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Note: Each word is guaranteed not to exceed L in length.

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
    void append_space(string &temp, int spaces, int &extra, int maxWidth)
    {
        int num = spaces;
        if (extra) {
            num ++;
            extra --;
        }
        if (temp.length() + num > maxWidth) {
            num = maxWidth - temp.length();
        }
        temp += string(num, ' ');
    }
    vector<string> fullJustify(vector<string>& words, int maxWidth)
    {
        vector<vector<int>> lines;
        vector<int> line;
        vector<string> ret;
        int line_size = 0;
        int i=0;
        while( true) {
            int width = line_size + words[i].length() + line.size()+1-1;
            if(width <= maxWidth) {
                line.push_back(i);
                line_size += words[i].length();
                i++;
            } else {
                vector<int> temp = line;
                lines.push_back(temp);
                line.clear();
                line_size = 0;
            }
            if (i == words.size()) {
                vector<int> temp = line;
                lines.push_back(temp);
                break;
            }
        }
        for(int i=0; i<lines.size(); i++) {
            line = lines[i];
            int word_length = 0;
            for(int j=0; j<line.size(); j++) {
                word_length += words[line[j]].length();
            }
            int interval = line.size() -1;
            int spaces = 0;
            int extra = 0;
            if (interval == 0) {
                spaces = maxWidth - words[line[0]].size();
            } else {
                spaces = (maxWidth - word_length) / (line.size()-1);
                extra = (maxWidth - word_length) % (line.size()-1);
            }
            string temp = words[line[0]];
            for(int j=0; j<line.size(); j++) {
                append_space(temp, spaces, extra, maxWidth);
                if(j != line.size() -1) {
                    temp += words[line[j+1]];
                }
            }
            ret.push_back(temp);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    string words[]= {"This", "is", "an", "example", "of", "text", "justification."};
    //string words[]= {"a", "b", "c", "d"};
    //string words[]= {""};
    vector<string> v(words, words + sizeof(words)/sizeof(string));
    vector<string> ret = sln.fullJustify(v, 16);
    for(int i=0; i<ret.size(); i++) {
        cout << ret[i] << endl;
    }
    system("pause");
    return 0;
}
