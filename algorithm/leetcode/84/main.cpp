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
