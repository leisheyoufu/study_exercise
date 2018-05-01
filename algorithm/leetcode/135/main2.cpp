/*
Candy

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int candy(vector<int>& ratings)
    {
        int n = ratings.size();
        if(n ==0) {
            return 0;
        }
        vector<int> count(n, 1);
        for(int i=1; i<n; i++) {
            if(ratings[i] > ratings[i-1]) {
                count[i] = count[i-1] + 1;
            }
        }
        for(int i=n-2; i>=0; i--) {
            if(ratings[i] > ratings[i+1]) {
                count[i] = max(count[i+1] + 1, count[i]);
            }
        }
        int ret = 0;
        for(int i=0; i<n; i++) {
            ret += count[i];
        }
        return ret;
    }
};
int main()
{
    Solution sln;
    int a[] = {0,1,2,3,0};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.candy(v) << endl; // 11
    system("pause");
    return 0;
}
