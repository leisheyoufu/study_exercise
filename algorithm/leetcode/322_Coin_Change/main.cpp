/*
322. Coin Change

You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:

Input: coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1
Example 2:

Input: coins = [2], amount = 3
Output: -1
Note:
You may assume that you have an infinite number of each kind of coin.
*/

#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

class Solution
{
public:
    int coinChange(vector<int>& coins, int amount)
    {
        int n = coins.size();
        if(amount ==0 && n == 0) {
            return 0;
        }
        if(amount <0 || n == 0) {
            return -1;
        }
        vector<int> dp(amount+1, amount+1);
        dp[amount] = 0;
        for(int curr = amount; curr >0; curr--) {
            for(int i=0; i<n; i++) {
                if(curr - coins[i] >=0) {
                    dp[curr - coins[i]] = min(dp[curr - coins[i]], dp[curr] + 1);
                }
            }
        }
        if(dp[0] == amount+1) {
            return -1;
        }
        return dp[0];
    }
};
int main()
{
    Solution sln;
    vector<int> coins = {1,2,5};
    cout << sln.coinChange(coins, 11) << endl;
    system("pause");
    return 0;
}
