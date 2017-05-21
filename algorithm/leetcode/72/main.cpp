/*
72. Edit Distance

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
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
    int minDistance(string word1, string word2)
    {
        int n1 = word1.length();
        int n2 = word2.length();
        vector<vector<int>> a(n1+1, vector<int>(n2+1, 0));
        for(int i=1; i<=n1; i++) {
            a[i][0] = i;
        }
        for(int j=1; j<=n2; j++) {
            a[0][j] = j;
        }
        for(int i=1; i<=n1; i++) {
            for(int j=1; j<=n2; j++) {
                if(word1[i-1] == word2[j-1]) {
                    a[i][j] = a[i-1][j-1];
                } else if(a[i-1][j-1] <= a[i-1][j] && a[i-1][j-1] <= a[i][j-1]) {
                    a[i][j] = a[i-1][j-1] + 1;
                } else if(a[i-1][j] < a[i-1][j-1] && a[i-1][j]<a[i][j-1]) {
                    a[i][j] = a[i-1][j] +1;
                } else {
                    a[i][j] = a[i][j-1]+1;
                }
            }
        }
        return a[n1][n2];
    }
};

int main()
{
    Solution sln;
    cout << sln.minDistance("abcd", "e") << endl;
    system("pause");
    return 0;
}
