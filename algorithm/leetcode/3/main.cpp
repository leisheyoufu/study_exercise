#include<iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cmath>
#include <map>
#include<conio.h>

using namespace std;

int lengthOfLongestSubstring(string s) {
    map<char, int> m;
	int maxlen = 0;
	int temp = -1;
	for(int i=0;i<s.size();i++) {
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
