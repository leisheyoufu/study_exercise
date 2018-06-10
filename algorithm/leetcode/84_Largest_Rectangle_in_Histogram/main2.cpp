/*
Largest Rectangle in Histogram

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.


Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].


The largest rectangle is shown in the shaded area, which has area = 10 unit.

For example,
Given heights = [2,1,5,6,2,3],
return 10.
*/
#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int largestRectangleArea(vector<int>& heights)
    {
        int n = heights.size();
        if (n == 0) {
            return 0;
        }
        heights.push_back(0);
        stack<int> s;
        int max_area = 0;
        for(int i=0; i<n ; i++) {
            int curr = heights[i];
            while(!s.empty() && heights[s.top()] > curr ) {
                int k = s.top();
                s.pop();
                int left;
                if (s.empty()) {
                    left = k+1;
                } else {
                    left = k-s.top();
                }
                int area = (left + i - k - 1) * heights[k] ;
                max_area = max(area, max_area);
            }
            s.push(i);
        }
        return max_area;
    }
};
int main()
{
    int a[] = {2,1,2};
    vector<int> v(a, a+ sizeof(a)/sizeof(int));
    Solution sln;
    cout << sln.largestRectangleArea(v) << endl;
    system("pause");
    return 0;
}
