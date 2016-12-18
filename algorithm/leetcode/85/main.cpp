#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
	int largestRectangleArea(vector<int>& heights) {
        stack<int> s;
		heights.push_back(0);
		int max_area = 0;
		for(int i=0;i<heights.size();i++) {
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

	vector<vector<int>> getRectagle(vector<vector<char>>& matrix) {
		int c_size = matrix[0].size();
		vector<vector<int>> lines;
		for(int i=0;i<matrix.size();i++) {
			vector<int> heights(c_size,0);
			for(int j=0;j<c_size;j++) {
				if(matrix[i][j] == '0') {
					heights[j] = 0;
				} else if (matrix[i][j] == '1') {
					if(i>0)
						heights[j] = 1 + lines[i-1][j];
					else 
						heights[j] = 1;
				}
			}
			lines.push_back(heights);
		}
		return lines;
	}

	int maximalRectangle(vector<vector<char>>& matrix) {
		if(matrix.empty()) {
			return 0;
		}
		vector<vector<int>> lines = getRectagle(matrix);
		int max_area = 0;
		for(int i=0;i<lines.size();i++) {
			max_area = max(max_area,largestRectangleArea(lines[i]));
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