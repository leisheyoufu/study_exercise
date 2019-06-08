/*
352. Data Stream as Disjoint Intervals

Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals.

For example, suppose the integers from the data stream are 1, 3, 7, 2, 6, ..., then the summary will be:

[1, 1]
[1, 1], [3, 3]
[1, 1], [3, 3], [7, 7]
[1, 3], [7, 7]
[1, 3], [6, 7]
Follow up:
What if there are lots of merges and the number of disjoint intervals are small compared to the data stream's size?

NOTE: input types have been changed on April 15, 2019. Please reset to default code definition to get new method signature.
*/

#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include<set>

using namespace std;

class SummaryRanges
{
public:
    struct Interval {
        int start;
        int end;
        Interval()
        {
            start = 0;
            end = 0;
        }
        Interval(int s, int e)
        {
            start = s;
            end = e;
        }
    };
    struct Cmp {
        bool operator()(const Interval &a, const Interval &b) const
        {
            return a.start < b.start;
        }
    };
    set<Interval, Cmp> st;
    /** Initialize your data structure here. */
    SummaryRanges()
    {

    }

    void addNum(int val)
    {
        auto it = st.lower_bound(Interval(val, val));
        int start = val, end = val;
        if(it != st.begin() && (--it)->end+1 < val) {
            it++;
        }
        while(it != st.end() && val+1 >= it->start && val-1 <= it->end) {
            start = min(start, it->start);
            end = max(end, it->end);
            it = st.erase(it);
        }
        st.insert(it,Interval(start, end));
    }

    vector<vector<int>> getIntervals()
    {
        vector<vector<int>> ret;
        for(auto val: st) {
            vector<int> temp = {val.start, val.end};
            ret.push_back(temp);
        }
        return ret;
    }
};

int main()
{
    SummaryRanges summary;
    vector<int> a = {1, 3, 7, 2, 6};
    for(auto i : a) {
        summary.addNum(i);
        auto intervals = summary.getIntervals();
        for(auto interval:intervals) {
            cout << "[" << interval[0] << "," << interval[1] << "]" << ",";
        }
        cout << endl;
    }
    system("pause");
    return 0;
}
