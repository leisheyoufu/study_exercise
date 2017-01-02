#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;

/*
class Solution
{
public:
	bool isMatch(string s, string p) {
		if(s.length() ==0 && p.length() == 0) {
			return true;
		}
		if(p.length() == 0) {
			return false;
		}
		if(s.length() == 0) {
			if(p[0] == '*') {
				return isMatch(s,p.substr(1,p.length()-1));
			}
			return false;
		}
		if(s[0] == p[0] || p[0] == '?') {
			return isMatch(s.substr(1,s.length()), p.substr(1, p.length()));
		} else if(p[0] == '*') {
			if(isMatch(s.substr(1,s.length()), p.substr(0,  p.length()))) {
				return true;
			} else if(isMatch(s.substr(1,s.length()), p.substr(1,  p.length()))){
				return true;
			}
			return isMatch(s.substr(0,s.length()), p.substr(1,  p.length()));
		}
		return false;
    }
};
*/
bool isMatch(const char *s, const char *p)
{
    char *ss = NULL, *pp = NULL;
    while(*s!= '\0') {
        if(*s == *p || *p == '?') {
            s++;
            p++;
        } else if(*p == '*') {
            ss = (char*)s;
            pp = (char*)p++;
        } else if(pp != NULL) {
            p = pp;
            s = ++ss;
        } else {
            return false;
        }
    }
    while(*p == '*') {
        p++;
    }
    return *p=='\0';
}


int main()
{
    cout << isMatch("ab", "?*") << endl;
    system("pause");
    return 0;
}