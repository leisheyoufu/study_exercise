#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

class Solution
{
public:
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
		int left =0, right = n-1;
		while(left<=right) {
			int mid = (left+right)/2;
			if(target == nums[mid]) {
				return mid;
			}
			if(target<nums[mid]) {
				right = mid-1;
			} else if(target > nums[mid]) {
				left = mid+1;
			}
		}
		if(right < 0) {
			return 0;
		}
		if(nums[right] > target) {
			if(right == 0 ) {
				return 0;
			} else {
				return right-1;
			}
		}
		return right+1;
    }
};
int main()
{
    Solution sln;
	int a[] = {1,3,5,6};
	vector<int> nums(a, a+sizeof(a)/sizeof(int));
    cout << sln.searchInsert(nums,0);
    system("pause");
    return 0;
}
