/*
84. Largest Rectangle in Histogram

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
        if(n == 0) {
            return 0;
        }
        stack<int> s;
        heights.push_back(0);
        int left_area, area, curr = 0;
        s.push(0);
        for(int i=1; i<n + 1; i++) {
            while(!s.empty() && heights[i] < heights[s.top()]) {
                int index = s.top();
                s.pop();
                if(s.empty()) {
                    left_area = index * heights[index];
                } else {
                    left_area = (index - s.top() -1) * heights[index];
                }
                area = heights[index] * (i- index) + left_area;
                curr =max(curr, area);
                //cout <<  left_area << " " << curr << endl;
            }
            s.push(i);
        }
        return curr;
    }
};
int main()
{
    vector<int> v = {100, 2,1,5,6,2,3};
    Solution sln;
    cout << sln.largestRectangleArea(v) << endl; // 100
    v = {2, 1, 2};
    cout << sln.largestRectangleArea(v) << endl; // 3
    v = {1, 3, 2, 3};
    cout << sln.largestRectangleArea(v) << endl; // 3
    system("pause");
    return 0;
}
