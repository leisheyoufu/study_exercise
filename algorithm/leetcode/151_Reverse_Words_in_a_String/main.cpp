/*
151. Reverse Words in a String
Given an input string, reverse the string word by word.

For example,
Given s = "the sky is blue",
return "blue is sky the".

Update (2015-02-12):
For C programmers: Try to solve it in-place in O(1) space.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    void trim(string &s)
    {
        if (s.empty()) {
            return;
        }
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
    void reverseWords(string &s)
    {
        trim(s);
        int len = s.length();
        bool has_space = false;
        for(int i=0; i<len; i++) {
            if(s[i] == ' ') {
                has_space = true;
                break;
            }
        }
        if(!has_space) {
            return;
        }
        for(int i=0; i<len/2; i++) {
            swap(s[i], s[len-1-i]);
        }
        int i = 0;
        string temp = "";
        int start = 0;
        while(i<len) {
            if(s[i] == ' ') {
                int l = i-start;
                for(int j=0; j<l/2; j++) {
                    swap(s[start+j], s[start+l-1-j]);
                }
                start = i+1;
            } else if(i == len-1) {
                int l = i-start+1;
                for(int j=0; j<l/2; j++) {
                    swap(s[start+j], s[start+l-1-j]);
                }
            }
            i++;
        }
        i =0;
        int j=0;
        while(i<s.length()) {
            while(s[i] == ' '&& i+1 < len && s[i+1] == ' ') {
                i++;
            }
            s[j++] = s[i++];
        }
        s = s.substr(0, j);
        //trim(s);
    }
};

int main()
{
    Solution sln;
    //string s = "theaskyisblueaoaa, ab";
    //string s = "a ";
    //string s = "   a      b";
    string s = "   a   b  c d   e  ";
    sln.reverseWords(s);
    cout << s;
    system("pause");
    return 0;
}
