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
        int size = prices.size();
        if (size == 0 ) {
            return 0;
        }
        int ret = 0;
        int *b = new int[size];
        int *s = new int[size];
        memset(b,0, size*sizeof(int));
        memset(s,0, size*sizeof(int));
        int min_val = prices[0];
        for(int i=1; i<size-1; i++) {
            min_val = min(min_val, prices[i]);
            b[i] = max(b[i-1], prices[i] - min_val);
        }
        int max_val = prices[size-1];
        for(int i=size-2; i>=0; i--) {
            max_val = max(max_val, prices[i]);
            s[i] = min(s[i+1], prices[i] - max_val);
            ret = max(ret, b[i] - s[i]);
        }
        delete []b;
        delete []s;
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