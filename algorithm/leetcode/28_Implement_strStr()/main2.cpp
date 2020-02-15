/*
2 Implement strStr().

Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.

Subscribe to see which companies asked this question.
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

class Solution
{
public:
    vector<int> getFail(string needle)
    {
        int n = needle.length();
        vector<int> fail (n+1);
        fail[0] = fail[1] = 0;
        for(int i=1; i<n; i++) {
            int j = fail[i];
            while(j && needle[i] != needle[j]) {
                j = fail[j];
            }
            fail[i+1] = needle[i] == needle[j] ? j+1 : 0;
        }
        return fail;
    }
    int strStr(string haystack, string needle)
    {
        int n = haystack.length();
        int m = needle.length();
        if(m==0) {
            return 0;
        }
        vector<int> fail = getFail(needle);
        cout << fail.size() << endl;
        int j = 0;
        for(int i=0; i<n; i++) {
            while(j && haystack[i] != needle[j]) {
                j = fail[j];
            }
            j =  haystack[i] == needle[j] ? j+1:0;
            if (j == m) {
                return i-m+1;
            }
        }
        return -1;
    }
};
int main()
{
    Solution sln;
    // cout << sln.strStr("eabc","cbc") << endl;  // -1
    // cout << sln.strStr("eabc","ab") << endl;  // 1
    cout << sln.strStr("mississippi","issip") << endl;

    system("pause");
    return 0;
}
