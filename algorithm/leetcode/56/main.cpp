#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>
#include<cstdlib>
using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;

struct Interval {
   int start;
   int end;
   Interval() : start(0), end(0) {}
   Interval(int s, int e) : start(s), end(e) {}
};
int comp(Interval &val1, Interval &val2) {
		return val1.start< val2.start;
}
class Solution
{
public:
	
	vector<Interval> merge(vector<Interval>& intervals) {
		vector<Interval> result;
		if(intervals.size() == 0 ) {
			return result;
		}
		if(intervals.size() == 1) {
			result.push_back(intervals[0]);
			return result;
		}
		sort(intervals.begin(),intervals.end(),comp);
		
		Interval *val = &intervals[0];
		for(int i=1; i<intervals.size();i++) {
			if(val->end >= intervals[i].start) {
				val->end = max(val->end, intervals[i].end);
			} else {
				result.push_back(*val);
				val = &intervals[i];
			}
		}
		if (result.size() == 0) {
			result.push_back(*val);
		}
		else if(result.back().end != intervals[intervals.size()-1].end) {
			result.push_back( *val);
		}
		return result;
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
	for(int i=0;i<results.size();i++) {
		Interval temp = results[i];
		printf("[%d %d]",temp.start,temp.end);
	}   
    getch();
    return 0;
}
