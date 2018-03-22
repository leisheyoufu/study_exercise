/*
746. Min Cost Climbing Stairs

On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).

Once you pay the cost, you can either climb one or two steps. You need to find minimum cost to reach the top of the floor, and you can either start from the step with index 0, or the step with index 1.

Example 1:
Input: cost = [10, 15, 20]
Output: 15
Explanation: Cheapest is start on cost[1], pay that cost and go to the top.
Example 2:
Input: cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]
Output: 6
Explanation: Cheapest is start on cost[0], and only step on 1s, skipping cost[3].
Note:
cost will have a length in the range [2, 1000].
Every cost[i] will be an integer in the range [0, 999].
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution
{
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        int n = cost.size();
        if(n == 1 || n == 0) {
            return 0;
        }
        vector<int> f(n+1, 0);
        for(int i=2; i<=n; i++) {
            f[i] = min(cost[i-1] + f[i-1], cost[i-2] + f[i-2]);
        }
        return f[n];
    }
};
int main()
{
    Solution sln;
    int a[] = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    vector<int> v(a, a+ sizeof(a)/sizeof(int));
    cout << sln.minCostClimbingStairs(v) << endl;
    system("pause");
    return 0;
}
