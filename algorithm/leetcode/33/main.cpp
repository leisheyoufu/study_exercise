#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    int search(vector<int>& nums, int target)
    {
        int n = nums.size();
        int left = 0, right = n-1;
        while(left<=right) {
            int mid = (left+right)/2;
            if(target == nums[mid]) {
                return mid;
            }
            if(nums[left] < nums[mid]) {
                if(target >=nums[left] && target <=nums[mid]) {
                    right = mid-1;
                } else {
                    left = mid+1;
                }
            } else if (nums[left] > nums[mid]) {
                if(target >=nums[left] || target <=nums[mid]) {
                    right = mid-1;
                } else {
                    left = mid+1;
                }
            } else {
                left +=1;
            }
        }
        return -1;
    }
};
int main()
{
    Solution sln;
    int a[] = {4, 5, 6, 7, 0, 1, 2};
    vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.search(nums,2);
    system("pause");
    return 0;
}
