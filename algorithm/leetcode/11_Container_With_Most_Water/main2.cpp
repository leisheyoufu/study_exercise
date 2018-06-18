/* 11. Container With Most Water
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Solution
{
public:
    int maxArea(vector<int>& height)
    {
        int n = height.size();
        if(n < 2) {
            return 0;
        }
        int l = 0, r = n-1;
        int area = 0;
        while(l < r) {
            int k = min(height[l], height[r]);
            area = max(area, (r-l) * k);
            while(l < r && height[l] <= k) {
                l++;
            }
            while(l < r && height[r] <= k) {
                r--;
            }
        }
        return area;
    }
};
int main()
{
    Solution sln;
    system("pause");
    return 0;
}
