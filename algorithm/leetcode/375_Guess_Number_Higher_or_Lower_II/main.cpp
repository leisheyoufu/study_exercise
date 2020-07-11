/*
375. Guess Number Higher or Lower II

We are playing the Guess Game. The game is as follows:

I pick a number from 1 to n. You have to guess which number I picked.

Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.

However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<unordered_set>
#include<set>

using namespace std;

int guess(int num);

class Solution
{
public:
    int getMoneyAmount(int n)
    {
        vector<vector<int>> dp(n+1, vector<int>(n+1));
        for(int i=1; i<=n; i++) {
            if(i!=n) {
                dp[i][i+1] = i;
            }
            dp[i][i] = 0;
        }
        for(int k=3; k<=n; k++) { // 步长
            for(int i=1; i<=n-k+1; i++) {
                int curr = INT_MAX;
                for(int j=i+1; j < i + k - 1; j++) { // 中间切割点
                    curr = min(curr, j + max(dp[i][j-1],dp[j+1][i+k-1]));
                }
                dp[i][i+k-1] = curr;
            }
        }
        return dp[1][n];
    }
};

int main()
{
    Solution sln;
    cout << sln.getMoneyAmount(10) << endl; // 16
    cout << sln.getMoneyAmount(1) << endl; // 0
    system("pause");
    return 0;
}
