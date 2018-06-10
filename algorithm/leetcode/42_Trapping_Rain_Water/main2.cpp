/*

42. Trapping Rain Water
Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

For example,
Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.

The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    int trap(vector<int>& height)
    {
        int n = height.size();
        if(n==0 || n == 1 || n ==2) {
            return 0;
        }
        int max_index = 0;
        for(int i=1; i<n; i++) {
            if(height[i] > height[max_index]) {
                max_index= i;
            }
        }
        int left = 0;
        int area = 0;
        for(int i=1; i<max_index; i++) {
            if(height[i] < height[left]) {
                area += height[left] - height[i];
            } else {
                left = i;
            }
        }
        int right = n-1;
        for(int i=n-2; i>max_index; i--) {
            if(height[i] < height[right]) {
                area += height[right] - height[i];
            } else {
                right = i;
            }
        }
        return area;
    }
};
int main()
{
    Solution sln;
    int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> v(a, a+sizeof(a)/sizeof(int));
    cout << sln.trap(v);
    system("pause");
    return 0;
}
