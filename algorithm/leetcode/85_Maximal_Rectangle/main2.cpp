/*
85. Maximal Rectangle

Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6.
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
        stack<int> s;
        heights.push_back(0);
        s.push(0);
        int left_area, area, curr = 0;
        for(int i=1; i<n+1; i++) {
            while(!s.empty() && heights[i] < heights[s.top()]) {
                int index = s.top();
                s.pop();
                if(s.empty()) {
                    left_area = heights[index] * index;
                } else {
                    left_area = heights[index] * (index - s.top() - 1);
                }
                area = heights[index] * (i-index) + left_area;
                curr = max(area, curr);
            }
            s.push(i);
        }
        return curr;
    }

    void initLines(vector<vector<int>> &lines, vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        for(int j=0; j<n; j++) {
            if(matrix[0][j] == '1') {
                lines[0][j] = 1;
            }
        }
        for(int i=1; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(matrix[i][j] == '0') {
                    lines[i][j] = 0;
                } else {
                    lines[i][j] = lines[i-1][j] + 1;
                }
            }
        }
    }
    int maximalRectangle(vector<vector<char>>& matrix)
    {
        int m = matrix.size();
        if(m==0) {
            return 0;
        }
        int n = matrix[0].size();
        if(n==0) {
            return 0;
        }
        vector<vector<int>> lines(m, vector<int>(n, 0));
        initLines(lines, matrix);
        int area = 0;
        for(int i=0; i<m; i++) {
            area = max(largestRectangleArea(lines[i]), area);
        }
        return area;
    }
};
int main()
{
    vector<vector<char>> matrix = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    Solution sln;
    cout << sln.maximalRectangle(matrix) << endl; // 6
    system("pause");
    return 0;
}
