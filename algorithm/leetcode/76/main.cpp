#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        int ssize = s.length();
        int tsize = t.length();
        if(ssize < tsize) {
            return "";
        }
        int *thash = new int[256];
        int *fhash = new int[256];   // to find hash
        memset(thash, 0, sizeof(int)*256);
        memset(fhash, 0,sizeof(int)*256);
        int count = 0, curr = 0, end, min_start;
        int window = INT_MAX;
        for(int i=0; i<tsize; i++) {
            thash[t[i]] ++;
        }
        for(int i=0; i<ssize; i++) {
            if(!thash[s[i]]) {
                continue;
            }

            if(fhash[s[i]] < thash[s[i]]) {
                count ++;
            }
            fhash[s[i]] ++;
            if(count == tsize) {
                end = i;
                while(count == tsize) {
                    if(!thash[s[curr]]) {
                        curr++;
                        continue;
                    }
                    if(fhash[s[curr]] == thash[s[curr]]) {
                        count--;
                        if(end-curr+1 < window) {
                            window = end- curr +1;
                            min_start = curr;
                        }
                    }
                    fhash[s[curr]]--;
                    curr++;
                }
            }
        }
        if(window == INT_MAX) {
            return "";
        }
        return s.substr(min_start, window);
    }
};
int main()
{
    Solution sln;
    //cout << sln.minWindow("ADOBECODEBANC", "ABC") << endl;
    //cout << sln.minWindow("abc", "b") << endl;
    cout << sln.minWindow("cabwefgewcwaefgcf","cae") << endl;
    system("pause");
    return 0;
}