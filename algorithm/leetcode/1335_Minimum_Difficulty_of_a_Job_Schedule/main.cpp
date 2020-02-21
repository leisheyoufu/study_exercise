/*
1335. Minimum Difficulty of a Job Schedule

You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the i-th job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule is the sum of difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a job done in that day.

Given an array of integers jobDifficulty and an integer d. The difficulty of the i-th job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs return -1.



Example 1:


Input: jobDifficulty = [6,5,4,3,2,1], d = 2
Output: 7
Explanation: First day you can finish the first 5 jobs, total difficulty = 6.
Second day you can finish the last job, total difficulty = 1.
The difficulty of the schedule = 6 + 1 = 7
Example 2:

Input: jobDifficulty = [9,9,9], d = 4
Output: -1
Explanation: If you finish a job per day you will still have a free day. you cannot find a schedule for the given jobs.
Example 3:

Input: jobDifficulty = [1,1,1], d = 3
Output: 3
Explanation: The schedule is one job per day. total difficulty will be 3.
Example 4:

Input: jobDifficulty = [7,1,7,1,7,1], d = 3
Output: 15
Example 5:

Input: jobDifficulty = [11,111,22,222,33,333,44,444], d = 6
Output: 843


Constraints:

1 <= jobDifficulty.length <= 300
0 <= jobDifficulty[i] <= 1000
1 <= d <= 10
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdio>

using namespace std;

class Solution
{
public:
    int minDifficulty(vector<int>& jobDifficulty, int d)
    {
        int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }
        // //前i= 0(第0天)完成前j项任务所需的最小难度
        vector<vector<int>> dp(d, vector<int>(n, INT_MAX));
        dp[0][0] = jobDifficulty[0];
        for(int j=1; j<n; j++) {
            dp[0][j] = max(dp[0][j-1], jobDifficulty[j]);
        }
        for(int i=1; i<d; i++) {
            for(int j=i; j<n; j++) {
                int currMax = jobDifficulty[j];
                for(int k=j; k>i-1; k--) {
                    currMax = max(currMax, jobDifficulty[k]);
                    dp[i][j] = min(dp[i][j], dp[i-1][k-1] + currMax);
                }
            }
        }
        return dp[d-1][n-1];
    }
};

int main()
{
    Solution sln;
    vector<int> jobs = {11,111,22,222,33,333,44,444};
    cout << sln.minDifficulty(jobs, 6) << endl;  // 843
    jobs = {1,1};
    cout << sln.minDifficulty(jobs, 2) << endl;  // 2
    system("pause");
    return 0;
}
