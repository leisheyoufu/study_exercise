/*
Best Time to Buy and Sell Stock III
Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete at most two transactions.

Note:
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;


class Solution
{
public:
    int maxProfit(vector<int>& prices)
    {
        int n = prices.size();
        if (n == 0 || n == 1) {
            return 0;
        }
        int ret = 0;
        int buy = prices[0];
        vector<int> f(n, 0);
        for(int i=1; i<n; i++) {
            f[i] = max(f[i-1], prices[i] - buy);
            buy = min(buy, prices[i]);
        }
        vector<int> g(n, 0);
        int sell = prices[n-1];
        for(int i= n-2; i>=0; i--) {
            g[i] = max(sell - prices[i], g[i+1]);
            sell = max(sell, prices[i]);
            ret = max(f[i] + g[i], ret);
        }
        return ret;
    }
};

int main()
{
    Solution sln;
    int a[] = {3,2,6,5,0,3};
    vector<int> v(a, a+ sizeof(a)/sizeof(int));
    cout << sln.maxProfit(v) << endl;
    system("pause");
    return 0;
}
