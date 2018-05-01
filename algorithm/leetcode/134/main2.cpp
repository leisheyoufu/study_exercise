/*
134. Gas Station

There are N gas stations along a circular route, where the amount of gas at station i is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.

Note:
The solution is guaranteed to be unique.
*/
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<unordered_map>
using namespace std;

// CL: the solution 1 is better
class Solution
{
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        int cap = 0, debt = 0, ret = 0;
        int n = gas.size();
        if(n != cost.size()) {
            return -1;
        }
        for(int i=0; i<n; i++) {
            int temp = cap + gas[i] - cost[i];
            if(temp >= 0) {
                cap = temp;
            } else {
                debt = debt - temp;
                cap = 0;
                ret = i + 1;
            }
        }
        if (ret == n) {
            return -1;
        }
        if(cap - debt >=0) {
            return ret;
        }
        return -1;
    }
};

int main()
{
    Solution sln;
    int a[] = {4,3};
    int b[] = {5,2};
    vector<int> gas(a, a+ sizeof(a)/sizeof(int));
    vector<int> cost(b, b+sizeof(b)/sizeof(int));
    cout << sln.canCompleteCircuit(gas, cost);
    system("pause");
    return 0;
}
