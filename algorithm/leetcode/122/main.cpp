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
        if(prices.empty()) {
            return 0;
        }
        bool has = false;
        int buy = 0;
        int p = 0;
        for(int i=0; i<prices.size()-1; i++) {
            if(prices[i+1] > prices[i] && !has) {
                buy = prices[i];
                has = true;
            } else if(prices[i+1] < prices[i]&& has) {
                p += prices[i] - buy;
                has = false;
            }
        }
        if(has) {
            p+=prices[prices.size()-1] - buy;
        }
        return p;
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