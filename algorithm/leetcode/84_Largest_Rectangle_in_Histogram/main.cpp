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
        stack<int> s;
        heights.push_back(0);
        int max_area = 0;
        for(int i=0; i<heights.size(); i++) {
            while(!s.empty() && heights[s.top()] > heights[i]) {
                int k = s.top();
                s.pop();
                int width;
                if(s.empty()) {
                    width = k+1;
                } else {
                    width = k - s.top();
                }
                int left_area = width *heights[k];
                int right_area = (i-k-1) * heights[k];
                max_area = max(max_area, left_area + right_area);
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
