#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
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
    /*
    bool intersect(Interval a, Interval b)  // b is new
    {
    	if(b.start <= a.start && b.end >=a.start) {
    		return true;
    	} else if(b.start >=a.start && b.start <= a.end) {
    		return true;
    	}
    	return false;
    }
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    	int s = -1, e=0, times = 0;
    	int size = intervals.size();
    	for(int i=0;i<size;i++) {
    		if(intersect(intervals[i], newInterval)) {
    			if (s== -1) {
    				s = i;
    			}
    			intervals[s].start = min(intervals[i].start, newInterval.start);
    			intervals[s].end = max(intervals[i].end, newInterval.end);
    			newInterval = intervals[s];
    			times ++;
    		}
    		if(s == -1 && newInterval.start < intervals[i].start) {
    			e = i;
    		} else if(s== -1 && i==size-1) {
    			e = size;
    		}
    	}
    	if(s!=-1) {
    		int resize = size - times +1;
    		intervals.resize(resize);
    		while(e<size-1) {
    			intervals[++s] = intervals[++e];
    		}
    	} else {
    		int k = size;
    		intervals.resize(size+1);
    		while(k>e) {
    			intervals[k] = intervals[k-1];
    			k--;
    		}
    		intervals[e] = newInterval;
    	}
    	return intervals;
    }
    */
    bool overlap(Interval a, Interval b)  // b is new
    {
        if(b.start <= a.start && b.end >=a.start) {
            return true;
        } else if(b.start >=a.start && b.start <= a.end) {
            return true;
        }
        return false;
    }
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
    {
        vector<Interval> ret;
        int size = intervals.size();
        bool merge = false;
        for(int i=0; i<size; i++) {
            if(overlap(intervals[i],newInterval)) {
                newInterval.start = min(intervals[i].start, newInterval.start);
                newInterval.end = max(intervals[i].end, newInterval.end);
            } else {
                if(intervals[i].start < newInterval.start) {
                    ret.push_back(intervals[i]);
                } else {
                    if (!merge) {
                        ret.push_back(newInterval);
                        merge = true;
                    }
                    ret.push_back(intervals[i]);
                }
            }
        }
        if(!merge) {
            ret.push_back(newInterval);
        }
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
