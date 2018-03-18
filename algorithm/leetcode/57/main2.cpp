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
    bool overlap(Interval a, Interval b)
    {
        if(a.end >= b.start && a.start <=b.start || b.end >= a.start && b.start <=a.start
           || a.start<=b.start && a.end >=b.end || b.start<=a.start && b.end >=a.end ) {
            return true;
        }
        return false;
    }
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        vector<Interval> ret;
        if(intervals.empty()) {
            return vector<Interval>(1, newInterval);
        }
        Interval curr = intervals[0];
        if (intervals.size() == 1) {
            if(overlap(curr, newInterval)) {
                curr.end = max(curr.end, newInterval.end);
                curr.start = min(curr.start, newInterval.start);
                ret.push_back(curr);
            } else {
                ret.push_back(curr);
                ret.push_back(newInterval);
            }
            sort(ret.begin(), ret.end(), comp);
            return ret;
        }
        bool merged = false;
        for(int i=1; i<intervals.size(); i++) {
            if(!merged && overlap(curr, newInterval)) {
                curr.end = max(curr.end, newInterval.end);
                curr.start = min(curr.start, newInterval.start);
                merged = true;
            }
            if(overlap(curr, intervals[i])) {
                curr.end = max(curr.end, intervals[i].end);
                curr.start = min(curr.start, intervals[i].start);
            } else {
                ret.push_back(curr);
                curr = intervals[i];
            }
        }
        if (!merged) {
            if (overlap(curr, newInterval)) {
                curr.end = max(curr.end, newInterval.end);
                curr.start = min(curr.start, newInterval.start);
                ret.push_back(curr);
            } else {
                ret.push_back(newInterval);
            }
        } else {
            ret.push_back(curr);
        }
        sort(ret.begin(), ret.end(), comp);
        return ret;
    }
};
int main()
{
    Solution sln;
    vector<Interval> intervals;
    Interval n1(1,5);
    Interval n2(12,15);
    Interval n3(6,6);
    vector<Interval> ret;
    ret = sln.insert(intervals, n1);
    ret = sln.insert(ret, n2);
    ret = sln.insert(ret, n3);

    system("pause");
    return 0;
}
