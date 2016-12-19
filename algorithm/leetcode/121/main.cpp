#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdio>

using namespace std;


class Solution
{
public:
	int maxProfit(vector<int>& prices) {
		int buy = INT_MAX;
		int sell = INT_MIN;
		int p = 0;
        for(int i=0;i<prices.size();i++) {
			if(prices[i] < buy) {
				buy = prices[i];
			}
			sell = prices[i];
			p = max(p, sell-buy);
		}
		return p;
    }
};

int main()
{	
	Solution sln;
	int a[] = {7, 6, 4, 3, 1};
	vector<int> v(a, a+ sizeof(a)/sizeof(int));
	cout << sln.maxProfit(v) << endl;
    system("pause");
    return 0;
}