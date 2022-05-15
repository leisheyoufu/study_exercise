/*
473. Matchsticks to Square

You are given an integer array matchsticks where matchsticks[i] is the length of the ith matchstick. You want to use all the matchsticks to make one square. You should not break any stick, but you can link them up, and each matchstick must be used exactly one time.

Return true if you can make this square and false otherwise.



Example 1:

Input: matchsticks = [1,1,2,2,2]
Output: true
Explanation: You can form a square with length 2, one side of the square came two sticks with length 1.

Example 2:

Input: matchsticks = [3,3,3,3,4]
Output: false
Explanation: You cannot find a way to form a square with all the matchsticks.

Constraints:

    1 <= matchsticks.length <= 15
    1 <= matchsticks[i] <= 108

*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<stack>
#include<cmath>

using namespace std;

class Solution
{
public:
    bool makesquare(vector<int>& matchsticks)
    {
        int n = matchsticks.size();
        if (n <4) {
            return false;
        }
        int sum = 0;
        for(auto item: matchsticks) {
            sum += item;
        }
        if (sum % 4 != 0) {
            return false;
        }
        int edges[4] = {0};
        sort(matchsticks.begin(), matchsticks.end(), greater);
        return dfs(edges, matchsticks, 0, sum / 4);
    }

    static bool greater(int a, int b)
    {
        if (a > b) {
            return true;
        }
        return false;
    }

    bool dfs(int edges[], vector<int> &matchstics, int index, int target)
    {
        if (index == matchstics.size()) {
            return true;
        }
        for(int i=0; i<4; i++) {
            if (edges[i] + matchstics[index] > target) {
                continue;
            }
            edges[i] += matchstics[index];
            if (dfs(edges, matchstics, index + 1, target) == true) {
                return true;
            }
            edges[i] -= matchstics[index];
        }
        return false;
    }
};

int main()
{
    Solution sln;
    vector<int> matchstics = {1,1,2,2,2};
    cout << sln.makesquare(matchstics) << endl; // 1
    matchstics = {3,3,3,3,4};
    cout << sln.makesquare(matchstics) << endl; // 0
    matchstics = {3,3,3,3,4,4};
    cout << sln.makesquare(matchstics) << endl; // 0
    matchstics = {6035753,3826635,922363,6104805,1189018,6365253,364948,2725801,5577769,7857734,2860709,9554210,4883540,8712121,3545089};
    cout << sln.makesquare(matchstics) << endl; // 0
    system("pause");
    return 0;
}
