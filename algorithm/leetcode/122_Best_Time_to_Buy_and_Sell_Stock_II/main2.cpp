/*
Best Time to Buy and Sell Stock II

Say you have an array for which the ith element is the price of a given stock on day i.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
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
        if(n == 0) {
            return 0;
        }
        int profit = 0;
        int buy = prices[0];
        for(int i = 1; i<n; i++) {
            if(prices[i] > buy) {
                profit += prices[i] - buy;
            }
            buy = prices[i];
        }
        return profit;
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
