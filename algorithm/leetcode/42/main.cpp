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
        if(n==0) {
            return 0;
        }
        int max_index = 0, max_val = 0, area = 0;
        int root;
        for(int i=0; i<n; i++) {
            if(height[i] > max_val) {
                max_val = height[i];
                max_index = i;
            }
        }
        root= height[0];
        for(int i=0; i<max_index; i++) {
            if(height[i] > root) {
                root = height[i];
            } else {
                area += root - height[i];
            }
        }
        root = height[n-1];
        for(int i=n-1; i>max_index; i--) {
            if(height[i] > root) {
                root = height[i];
            } else {
                area +=root - height[i];
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
