/*
Implement strStr().

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
        vector<int> f(n+1,0);
        f[0] = f[1] = 0;
        int j=0;
        for(int i=1; i<n; i++) {
            j = f[i];
            while(j>0 && needle[j] != needle[i]) {
                j = f[j];
            }
            f[i+1] = needle[j] == needle[i]? j+1:0;
        }
        return f;
    }
    int strStr(string haystack, string needle)
    {
        int n = haystack.length();
        int m = needle.length();
        if( m == 0) {
            return 0;
        }
        vector<int> f = getFail(needle);
        int j = 0;
        for(int i=0; i<n; i++) {
            while( j && needle[j] != haystack[i]) {
                j = f[j];
            }
            j = needle[j] == haystack[i]? j+1:0;
            if (j==m) {
                return i - m +1;
            }
        }
        return -1;
    }
};
int main()
{

    Solution sln;
    cout << sln.strStr("hello", "ll") << endl;
    system("pause");
    return 0;
}
