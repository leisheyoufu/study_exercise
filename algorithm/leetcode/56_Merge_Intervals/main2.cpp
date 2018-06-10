/*

56. Merge Intervals

Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
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

    vector<Interval> merge(vector<Interval>& intervals)
    {
        vector<Interval> ret;
        if(intervals.empty()) {
            return ret;
        }
        sort(intervals.begin(), intervals.end(), comp);
        Interval curr = intervals[0];
        for(int i=1; i<intervals.size(); i++) {
            if(curr.end >= intervals[i].start) {
                curr.end = max(curr.end, intervals[i].end);
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
    Interval *n1 = new Interval(1,3);
    Interval *n2 = new Interval(5,7);
    Interval *n3 = new Interval(4, 6);
    intervals.push_back(*n1);
    intervals.push_back(*n2);
    intervals.push_back(*n3);
    vector<Interval> results = sln.merge(intervals);
    for(int i=0; i<results.size(); i++) {
        Interval temp = results[i];
        printf("[%d %d]",temp.start,temp.end);
    }
    getch();
    return 0;
}
