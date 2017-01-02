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
