/*

Longest Substring Without Repeating Characters

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <map>
#include<conio.h>

using namespace std;

int lengthOfLongestSubstring(string s)
{
    map<char, int> m;
    int maxlen = 0;
    int temp = -1;
    for(int i=0; i<s.size(); i++) {
        if(m.find(s[i])!=m.end()&& temp < m[s[i]]) {
            temp=m[s[i]];
        }
        if (i-temp>maxlen) {
            maxlen = i-temp;
        }
        m[s[i]] = i;
    }
    return maxlen;
}
int main()
{
    printf("%d\n",lengthOfLongestSubstring("abba"));
    getch();
    return 0;
}
