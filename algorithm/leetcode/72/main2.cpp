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
        int m = word1.size();
        int n = word2.size();
        // m --> n
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        for(int i=0; i<=m; i++) {
            dp[i][0] = i;
        }
        for(int j=1; j<=n; j++) {
            dp[0][j] = j;
        }
        for(int i=1; i<=m; i++) {
            for(int j=1; j<=n; j++) {
                if(word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else if( dp[i-1][j] == dp[i][j-1]) { // upadte
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else if( dp[i-1][j] < dp[i][j-1]) {
                    dp[i][j] = dp[i-1][j] + 1;
                } else {
                    dp[i][j] = dp[i][j-1] + 1;
                }
            }
        }
        return dp[m][n];
    }
};

int main()
{
    Solution sln;
    cout << sln.minDistance("abcd", "e") << endl;  // 4
    cout << sln.minDistance("addf12343", "32890") << endl; // 8
    system("pause");
    return 0;
}
