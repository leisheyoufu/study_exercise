/*

57. Insert Interval

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
int comp(Interval &val1, Interval &val2)
{
    return val1.start< val2.start;
}
class Solution
{
public:

    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        vector<Interval> ret;
        if(intervals.empty()) {
            return vector<Interval>(1, newInterval);
        }
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end(), comp);
        Interval curr = intervals[0];
        for(int i=1; i<intervals.size(); i++) {
            if(curr.end >= intervals[i].start) {
                curr.end = max(curr.end, intervals[i].end);
                curr.start = min(curr.start, intervals[i].start);
            } else {
                ret.push_back(curr);
                curr = intervals[i];
            }
        }
        ret.push_back(curr);
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<Interval> intervals;
    intervals.push_back(Interval (1,2));
    intervals.push_back(Interval (3,5));
    intervals.push_back(Interval (6,7));
    intervals.push_back(Interval (8,10));
    intervals.push_back(Interval (12,16));
    vector<Interval> ret;
    sln.insert(intervals, Interval (4,9));
    system("pause");
    return 0;
}
