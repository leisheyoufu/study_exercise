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

class Solution
{
public:
    /*
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        int n = gas.size();
    	vector<int> diff(n, 0);
    	for(int i=0; i<n; i++) {
    		diff[i] = gas[i] - cost[i];
    	}
    	for(int start = 0; start <n; start++) {
    		int i = 0;
    		int sum = 0;
    		bool flag = true;
    		while( i < n ) {
    			int index = (i + start)%n;
    			sum += diff[index];
    			if(sum < 0) {
    				flag = false;
    				break;
    			}
    			i++;
    		}
    		if(!flag) {
    			continue;
    		}
    		return start;
    	}
    	return -1;
    }
    */

    int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
    {
        int n = gas.size();
        int remain = 0;
        int debt = 0;
        int start = 0;
        for(int i=0; i<n; i++) {
            remain += gas[i] - cost[i];
            if(remain <0) {
                debt +=remain;
                remain = 0;
                start = i+1;
            }
        }
        return remain + debt >=0 ? start:-1;

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
