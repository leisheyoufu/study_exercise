/*
174. Dungeon Game

The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).

In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.


Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.

For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.

-2 (K)	-3	3
-5	-10	1
10	30	-5 (P)

Notes:

The knight's health has no upper bound.
Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

class Solution
{
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon)
    {
        int m = dungeon.size();
        if(m == 0) {
            return 0;
        }
        int n = dungeon[0].size();
        if(n == 0) {
            return 0;
        }
        vector<vector<int> > dp(m, vector<int>(n, 0));
        dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1]);
        for(int i=m-2; i>=0; i--) {
            dp[i][n-1] = max(1, dp[i+1][n-1] - dungeon[i][n-1]);
        }
        for(int j=n-2; j>=0; j--) {
            dp[m-1][j] = max(1, dp[m-1][j+1] - dungeon[m-1][j]);
        }
        for(int i=m-2; i>=0; i--) {
            for(int j=n-2; j>=0; j--) {
                int temp = min(dp[i+1][j], dp[i][j+1]);
                dp[i][j] = max(1, temp - dungeon[i][j]);
            }
        }
        return dp[0][0];
    }
};

int main()
{
    Solution sln;
    int a1[] = {-2, -3, 3};
    int a2[] = {-5, -10, 1};
    int a3[] = {10,30,-5};
    vector<int> v1(a1, a1 + sizeof(a1)/sizeof(int));
    vector<int> v2(a2, a2 + sizeof(a2)/sizeof(int));
    vector<int> v3(a3, a3 + sizeof(a3)/sizeof(int));
    vector<vector<int>> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    cout << sln.calculateMinimumHP(v) << endl;
    system("pause");
    return 0;
}
