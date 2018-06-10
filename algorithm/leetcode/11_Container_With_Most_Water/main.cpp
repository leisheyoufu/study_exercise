/* Container With Most Water
Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

Note: You may not slant the container and n is at least 2.
*/
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;
const int MAX = 0x7fffffff;
const int MIN = 0x80000000;
class Solution
{
public:

    int maxArea(vector<int>& height)
    {
        int l=0, r= height.size()-1;
        int res =0;
        while(l < r) {
            res = max(res, min(height[l], height[r]) * (r-l));
            if( height[l] <height[r]) {
                int k =l;
                while(k<r && height[k] <= height[l]) {
                    k++;
                }
                l =k;
            } else {
                int k = r;
                while(k>l && height[k] <= height[r]) {
                    k--;
                }
                r = k;
            }
        }
        return res;
    }
};
int main()
{
    Solution sln;
    printf("%d\n",sln.isMatch("abc", ".bc"));
    getch();
    return 0;
}
