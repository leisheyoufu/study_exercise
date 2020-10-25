/*

435. Non-overlapping Intervals

Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Example 1:

Input: [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.
Example 2:

Input: [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.
Example 3:

Input: [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.


Note:

You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    static bool less(vector<int> &a, vector<int> &b)
    {
        return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        if(intervals.empty()) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), less);
        int n = intervals.size();
        int count = 1;
        int end = intervals[0][1];
        for (int i=1; i<n; i++) {
            if(intervals[i][0]>= end) {
                count++;
                end = intervals[i][1];
            }
        }
        return n - count;
    }
};

int main()
{
    Solution sln;
    vector<vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
    cout << sln.eraseOverlapIntervals(intervals) << endl; // 1
    intervals = {{1,2},{1,2},{1,2}};
    cout << sln.eraseOverlapIntervals(intervals) << endl; // 2
    intervals = {{1,2},{2,3}};
    cout << sln.eraseOverlapIntervals(intervals) << endl; // 0
    intervals = {{1,2},{2,3},{3,4},{1,3},{2,4},{1,6}};
    cout << sln.eraseOverlapIntervals(intervals) << endl; // 3
    system("pause");
    return 0;
}
